/**
 * @file fake_java_expression.h Expression evaluator for JAVA subset used in the report expressions
 *
 * Copyright (c) 2010-2016 Neto Ranito & Seabra LDA. All rights reserved.
 *
 * This file is part of casper.
 *
 * casper is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * casper  is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with casper.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#ifndef NRS_CASPER_CASPER_JAVA_FAKE_JAVA_EXPRESSION_H
#define NRS_CASPER_CASPER_JAVA_FAKE_JAVA_EXPRESSION_H

#include "casper/java/fake_java_scanner.h"
#include "casper/java/fake_java_parser.hh"
#include "casper/java/interpreter.h"

namespace casper{
    namespace java{
        /**
         * @brief Expression evaluator for JAVA subset used in the report expressions
         */
        class FakeJavaExpression{
            friend class FakeJavaParser;

        public: //protected: // data
        
            FakeJavaScanner           scanner_;         //!< Scanner for a small subset of JAVA used in the report expressions
            FakeJavaParser            parser_;          //!< Expression parser for a restricted subset of the JAVA language

        public: // Methods

            FakeJavaExpression ();
            virtual ~FakeJavaExpression ();

            void       Convert           (const std::string& a_expression);
            void       Convert           (const char* a_expression, size_t a_len);

        };
    } // namespace java

} // namespace casper
#endif
