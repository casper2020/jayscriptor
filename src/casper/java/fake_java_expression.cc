/**
 * @file fake_java_expression.cc
 *
 * Copyright (c) 2011-2018 Cloudware S.A. All rights reserved.
 *
 * This file is part of jayscriptor.
 *
 * jayscriptor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * jayscriptor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with jayscriptor.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "casper/java/fake_java_expression.h"

#include <string.h> // strchr

casper::java::FakeJavaExpression::FakeJavaExpression ()
    : scanner_(ast_),
      parser_(ast_, scanner_, *this)
{
    /* empty */
}

casper::java::FakeJavaExpression::~FakeJavaExpression ()
{
    /* empty */
}


const std::string& casper::java::FakeJavaExpression::Convert (const std::string& a_expression, const std::string& a_relationship)
{
    return Convert(a_expression.c_str(), a_expression.size(), a_relationship);
}

const std::string& casper::java::FakeJavaExpression::Convert (const char* a_expression, size_t a_len, const std::string& a_relationship)
{
    tmp_ss_.str("");
    tmp_expression_ = "";

    relationship_ = a_relationship.length() ? a_relationship : "lines";

    try {
        ast_.Reset();
        scanner_.SetInput(a_expression, a_len);
        parser_.parse();
        BuildString(ast_.root_);
        tmp_expression_ = tmp_ss_.str();
        ast_.Reset();
    } catch (const std::runtime_error& a_error) {
        ast_.Reset();
        throw a_error;
    }

    return tmp_expression_;
}

void casper::java::FakeJavaExpression::BuildString (casper::java::AstNode* a_node)
{

    if ( nullptr == a_node ) {
        return;
    }

    if ( a_node->getType()==casper::java::AstNode::TNum ) {

        //
        // Numbers
        //

        tmp_ss_ << a_node->getVal();

    } else if ( a_node->getType()==casper::java::AstNode::TText ) {

        //
        // Text
        //

        tmp_ss_  << "(\"";
        tmp_ss_  << a_node->getText();
        tmp_ss_  << "\")";

    } else if ( a_node->getType()==casper::java::AstNode::TBool ) {

        //
        // Bool
        //
        tmp_ss_ << ( a_node->getBool() ? "true" : "false" );

    }else if ( a_node->getType()==casper::java::AstNode::TExpr ) {

        //
        // Expressions
        //    
        if ( ! a_node->getOp().compare("!") ) {
            tmp_ss_  << " !(";
            BuildString(a_node->getLeft());
            tmp_ss_  << ')';
        } else if ( ! a_node->getOp().compare("UM") ) {
            tmp_ss_  << " -";
            BuildString(a_node->getLeft());
        } else {
            if ( a_node->getPare() ) {
                tmp_ss_  << "(";
                BuildString(a_node->getLeft());
                tmp_ss_  << " " << a_node->getOp() << " ";
                BuildString(a_node->getRight());
                tmp_ss_  << ")";
            } else {
                BuildString(a_node->getLeft());
                tmp_ss_  << " " << a_node->getOp() << " ";
                BuildString(a_node->getRight());
            }
        }

    } else if ( a_node->getType()==casper::java::AstNode::TOps ) {

        //
        // Operations
        //

        if ( ! a_node->getOp().compare("toString") ) {
            tmp_ss_  << "(";
            BuildString(a_node->getLeft());
            tmp_ss_  << ").toString()";
        } else if ( ! a_node->getOp().compare("valueOf") ) {
            tmp_ss_  << "(";
            BuildString(a_node->getLeft());
            tmp_ss_  << ").valueOf()";
        } else if ( ! a_node->getOp().compare("parseBool") ) {
            BuildString(a_node->getLeft());
            tmp_ss_  << " == \"true\" ? true : false";
        } else if ( 0 == a_node->getOp().compare("to_i") ) {
            if ( casper::java::AstNode::TText != a_node->getLeft()->getType() ) {
                tmp_ss_ << "( ";
                BuildString(a_node->getLeft());
                tmp_ss_ << " ? parseFloat(";
                BuildString(a_node->getLeft());
                tmp_ss_   << ") : 0.0 )";
            } else {
                tmp_ss_ << "parseInt";
                BuildString(a_node->getLeft());
            }
        } else if ( 0 == a_node->getOp().compare("to_f") ) {
            if ( casper::java::AstNode::TText != a_node->getLeft()->getType() ) {
                tmp_ss_ << "( ";
                BuildString(a_node->getLeft());
                tmp_ss_ << " ? parseFloat(";
                BuildString(a_node->getLeft());
                tmp_ss_   << ") : 0.0 )";
            } else {
                tmp_ss_ << "parseFloat";
                BuildString(a_node->getLeft());
            }
        } else {
            tmp_ss_ << a_node->getOp() << "(";
            BuildString(a_node->getLeft());
            tmp_ss_   << ")";
        }

    } else if ( a_node->getType()==casper::java::AstNode::TStrOps ) {

        //
        // String Ops
        //

        if ( ! a_node->getOp().compare("IsEmpty") ) {
            tmp_ss_ << '(';
            BuildString(a_node->getLeft());
            tmp_ss_ << " === undefined || ";
            BuildString(a_node->getLeft());
            tmp_ss_ << " === null || ";
            BuildString(a_node->getLeft());
            tmp_ss_ << ".length === 0";
            tmp_ss_ << ')';
        } else if ( ! a_node->getOp().compare("length") ) {
            BuildString(a_node->getLeft());
            tmp_ss_  << ".length";
        } else if ( a_node->getOp().compare("toUpperCase") == 0 || a_node->getOp().compare("toLowerCase") == 0 ) {
            BuildString(a_node->getLeft());
            tmp_ss_  << "." << a_node->getOp() << "()";
        } else if ( ! a_node->getOp().compare("substring") ) {
            if ( a_node->getArg2() == nullptr ) {
                BuildString(a_node->getLeft());
                tmp_ss_  << "." << a_node->getOp() << "(";
                BuildString(a_node->getArg1());
                tmp_ss_ << ")";
            } else {
                BuildString(a_node->getLeft());
                tmp_ss_  << "." << a_node->getOp() << "(";
                BuildString(a_node->getArg1());
                tmp_ss_  << " , ";
                BuildString(a_node->getArg2());
                tmp_ss_  << ")";
            }
        } else if ( ! a_node->getOp().compare("indexOf") ) {
            BuildString(a_node->getLeft());
            tmp_ss_  << "." << a_node->getOp() << "(";
            BuildString(a_node->getArg1());
            tmp_ss_ << ")";
        } else if ( ! a_node->getOp().compare("replace") ) {
            BuildString(a_node->getLeft());
            tmp_ss_  << "." << a_node->getOp() << "(";
            BuildString(a_node->getArg1());
            tmp_ss_ << " , ";
            BuildString(a_node->getArg2());
            tmp_ss_ << ")";
        } else tmp_ss_ << "error";

    } else if ( a_node->getType()==casper::java::AstNode::TIf ) {

        //
        //Ifs
        //

        tmp_ss_ << "(";
        BuildString(a_node->getLeft());
        tmp_ss_ << " ? ";
        BuildString(a_node->getArg1());
        tmp_ss_ << " : ";
        BuildString(a_node->getArg2());
        tmp_ss_ << ")";

    } else if ( a_node->getType()==casper::java::AstNode::TVar ) {

        //
        // Vars
        //

        tmp_ss_ << "$.$$VARIABLES[index]." << a_node->getText();

    } else if ( a_node->getType()==casper::java::AstNode::TParam ) {

        //
        // Params
        //
        if ( nullptr != strchr(a_node->getText().c_str(), '-') ) {
            tmp_ss_ << "$[\"" << a_node->getText() << "\"]";
        } else {
            tmp_ss_ << "$." << a_node->getText();
        }

    } else if ( a_node->getType()==casper::java::AstNode::TField ) {

        //
        // Fields
        //
        if ( nullptr != strchr(a_node->getText().c_str(), '-') ) {
            tmp_ss_ << "$[\"" << relationship_ << "\"][index]." <<  a_node->getText();
        } else {
            tmp_ss_ << "$." << relationship_ << "[index]." <<  a_node->getText();
        }
        
    } else if ( a_node->getType()==casper::java::AstNode::TNull ) {

        //
        // Numbers
        //

        tmp_ss_ << "null";

    } else if ( a_node->getType()==casper::java::AstNode::TDate ) {

        //
        // Date
        //

        if(a_node->getOp().compare("newDate") == 0){
            tmp_ss_ << "new Date";
        } else if ( 0 == a_node->getOp().compare("DateFormat.parse") ) {
            tmp_ss_ << "NativeParseDate(";
            BuildString(a_node->getArg1());
            tmp_ss_ << ", \"" << a_node->getArg2()->getText() << "\",$.$$VARIABLES[index].LOCALE)";
        }
    }
}
