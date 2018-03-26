/**
 * @file ast.cc
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

#include <iostream>
#include "casper/java/ast.h"

#ifdef __APPLE__
#pragma mark -
#endif

casper::java::Ast::Ast ()
{
    root_ = nullptr;
}

casper::java::Ast::~Ast ()
{
    Reset();
}

#ifdef __APPLE__
#pragma mark -
#endif

casper::java::AstNode* casper::java::Ast::NewAstNode ()
{
    AstNode* node = new AstNode();
    
    allocated_nodes_.push_back(node);
    
    return node;
}

casper::java::AstNode* casper::java::Ast::NewAstNode (const int a_num)
{
    AstNode* node = new AstNode(a_num);
    
    allocated_nodes_.push_back(node);
    
    return node;
}

casper::java::AstNode* casper::java::Ast::NewAstNode (const std::string& a_text)
{
    AstNode* node = new AstNode(a_text);
    
    allocated_nodes_.push_back(node);
    
    return node;
}


casper::java::AstNode* casper::java::Ast::NewAstNode (const casper::java::AstNode::Type a_type, const std::string& a_text)
{
    AstNode* node = new AstNode(a_type, a_text);
    
    allocated_nodes_.push_back(node);
    
    return node;
}

casper::java::AstNode* casper::java::Ast::Expression (const std::string& a_op, casper::java::AstNode* a_left, casper::java::AstNode* a_right)
{
#if 1
    
    AstNode* node = new AstNode(AstNode::TExpr, a_left, a_right);
    
    node->setOp(a_op);
    
    allocated_nodes_.push_back(node);
    
    return node;
    
#else
    AstNode node;
    AstNode* tr = NewNode(a_right);
    AstNode* tl = NewNode(a_left);

    node.setRight(tr);
    node.setLeft(tl);
    node.setOp(a_op);
    node.setType(AstNode::TExpr);

    return node;
#endif
}

casper::java::AstNode* casper::java::Ast::Operation (const std::string& a_op, casper::java::AstNode* a_left)
{
#if 1
    
    AstNode* node = new AstNode(AstNode::TOps, a_left);
    
    node->setOp(a_op);
    
    allocated_nodes_.push_back(node);
    
    return node;
    
#else
    AstNode node;
    AstNode* tl = NewNode(a_left);
    node.setLeft(tl);
    node.setOp(a_op);
    node.setType(AstNode::TOps);

    return node;
#endif
}

casper::java::AstNode* casper::java::Ast::StrOp (const std::string& a_op, casper::java::AstNode* a_left)
{
#if 1
    
    AstNode* node = new AstNode(AstNode::TStrOps, a_left);
    
    node->setOp(a_op);
    
    allocated_nodes_.push_back(node);
    
    return node;
    
#else

    AstNode node;
    AstNode* tl = NewNode(a_left);
    node.setLeft(tl);
    node.setOp(a_op);
    node.setType(AstNode::TStrOps);

    return node;
#endif
}

casper::java::AstNode* casper::java::Ast::StrOp (const std::string& a_op, casper::java::AstNode* a_left, casper::java::AstNode* a_right)
{
#if 1
    
    AstNode* node = new AstNode(AstNode::TStrOps, a_left);
    
    node->setOp(a_op);
    node->setArg1(a_right);
    
    allocated_nodes_.push_back(node);
    
    return node;
    
#else

    AstNode node;
    AstNode* tr = NewNode(a_right);
    AstNode* tl = NewNode(a_left);

    node.setLeft(tl);
    node.setOp(a_op);
    node.setType(AstNode::TStrOps);
    node.setArg1(tr);

    return node;
#endif
}

casper::java::AstNode* casper::java::Ast::StrOp (const std::string& a_op, casper::java::AstNode* a_left, casper::java::AstNode* a_right_1, casper::java::AstNode* a_right_2)
{
#if 1
    
    AstNode* node = new AstNode(AstNode::TStrOps, a_left);
    
    node->setOp(a_op);
    node->setArg1(a_right_1);
    node->setArg2(a_right_2);
    
    allocated_nodes_.push_back(node);
    
    return node;
    
#else

    AstNode node;
    AstNode* tl = NewNode(a_left);

    node.setLeft(tl);
    node.setOp(a_op);
    node.setType(AstNode::TStrOps);
    AstNode* tr1 = NewNode(a_right_1);
    AstNode* tr2 = NewNode(a_right_2);

    node.setArg1(tr1);
    node.setArg2(tr2);

    return node;
#endif
}

casper::java::AstNode* casper::java::Ast::If (casper::java::AstNode* a_left, casper::java::AstNode* a_right_1, casper::java::AstNode* a_right_2)
{
#if 1
    
    AstNode* node = new AstNode(AstNode::TIf, a_left);
    
    node->setOp("if");
    node->setArg1(a_right_1);
    node->setArg2(a_right_2);
    
    allocated_nodes_.push_back(node);
    
    return node;
    
#else

    AstNode node;
    AstNode* tl = NewNode(a_left);

    node.setLeft(tl);
    node.setOp("if");
    node.setType(AstNode::TIf);

    AstNode* tr1 = NewNode(a_right_1);
    AstNode* tr2 = NewNode(a_right_2);

    node.setArg1(tr1);
    node.setArg2(tr2);

    return node;
#endif
}

casper::java::AstNode* casper::java::Ast::Bool(bool a_bool)
{
#if 1
    
    AstNode* node = new AstNode(AstNode::TBool);
    node->setBool(a_bool);
    node->setVal(true == a_bool ? 1 : 0);
    
    allocated_nodes_.push_back(node);

    return node;
#else

    AstNode node(AstNode::TBool);
    node.setBool(a_bool);
    if ( true == a_bool ) {
        node.setVal(1);
    } else {
        node.setVal(0);
    }
    return node;
#endif
}
