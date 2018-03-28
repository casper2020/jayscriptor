/**
 * @file ast.h
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

#pragma once

#ifndef CASPER_JAVA_AST_H_
#define CASPER_JAVA_AST_H_

#include <vector>
#include "casper/java/ast_node.h"

namespace casper
{

    namespace java
    {
        class FakeJavaParser;
        class FakeJavaExpression;

        class Ast
        {

            friend class FakeJavaParser;
            friend class FakeJavaExpression;

        protected: // Data

            std::vector<AstNode*> allocated_nodes_;
            AstNode*              root_;

        public: // Constructor(s) / Destructor

            Ast ();
            virtual ~Ast();

        public: // Function(s) / Method(s)

            AstNode* Expression (const std::string& a_op, AstNode* a_left, AstNode* a_right);
            AstNode* Operation  (const std::string& a_op, AstNode* a_left);
            AstNode* StrOp      (const std::string& a_op, AstNode* a_left);
            AstNode* StrOp      (const std::string& a_op, AstNode* a_left, AstNode* a_right);
            AstNode* StrOp      (const std::string& a_op, AstNode* a_left, AstNode* a_right_1, AstNode* a_right_2);
            AstNode* If         (AstNode* a_left, AstNode* a_right_1, AstNode* a_right_2);
            AstNode* Bool       (bool a_bool);

            AstNode* NewAstNode ();
            AstNode* NewAstNode (const casper::java::AstNode::Type a_type);
            AstNode* NewAstNode (const double a_num);
            AstNode* NewAstNode (const std::string& a_text);
            AstNode* NewAstNode (const casper::java::AstNode::Type a_type, const std::string& a_text);

        protected:

            void     Reset   ();

        }; // end of class 'Ast'

        inline void Ast::Reset ()
        {
            root_ = nullptr;
            for ( auto it : allocated_nodes_ ) {
                delete it;
            }
            allocated_nodes_.clear();
        }

    } // end of namespace 'java'

} // end of namespace 'casper'

#endif // CASPER_JAVA_AST_H_
