/**
 * @file fake_java_expression.h
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

#ifndef NRS_CASPER_CASPER_JAVA_FAKE_JAVA_EXPRESSION_H_
#define NRS_CASPER_CASPER_JAVA_FAKE_JAVA_EXPRESSION_H_

#include "casper/java/fake_java_scanner.h"
#include "casper/java/fake_java_parser.hh"
#include "casper/java/ast.h"

#include <sstream>

namespace casper
{
    
    namespace java
    {
        
        /**
         * @brief Expression evaluator for JAVA subset used in the report expressions
         */
        class FakeJavaExpression
        {
            
        friend class FakeJavaParser;

        public: //protected: // data
            
            Ast             ast_;     //!<
            FakeJavaScanner scanner_; //!< Scanner for a small subset of JAVA used in the report expressions
            FakeJavaParser  parser_;  //!< Expression parser for a restricted subset of the JAVA language
            
        private: // Data
            
            std::stringstream tmp_ss_;
            std::string       tmp_expression_;

        public: // Methods

            FakeJavaExpression ();
            virtual ~FakeJavaExpression ();

            const std::string& Convert (const std::string& a_expression);
            const std::string& Convert (const char* a_expression, size_t a_len);
            
        protected: // Method(s) / Function(s)
            
            void BuildString (casper::java::AstNode* a_node);

        }; // end of class 'FakeJavaExpression'
        
    } // end of namespace 'java'

} // end of namespace 'casper'

#endif // NRS_CASPER_CASPER_JAVA_FAKE_JAVA_EXPRESSION_H_
