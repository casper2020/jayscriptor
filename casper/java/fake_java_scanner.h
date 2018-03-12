/**
 * @file fake_java_scanner.h declaration of FakeJavaScanner model node
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
#ifndef NRS_CASPER_CASPER_JAVA_FAKE_JAVA_SCANNER_H
#define NRS_CASPER_CASPER_JAVA_FAKE_JAVA_SCANNER_H

#include "casper/scanner.h"
#include "casper/java/fake_java_parser.hh"

namespace casper
{
    namespace java
    {
        /**
         * @brief Scanner for the subset of JAVA used in the report engine expressions
         */
        class FakeJavaScanner : public casper::Scanner
        {
            friend class FakeJavaParser;

        public: // methods

            FakeJavaScanner ();
            virtual ~FakeJavaScanner ();

        public: // methods

            virtual void SetInput (const char* a_expression, size_t a_lenght);

            FakeJavaParser::token_type Scan (FakeJavaParser::semantic_type*, casper::java::location* a_location);

            void SetDoubleVar (const char* a_var_name, double a_double);
            void SetStringVar (const char* a_var_name, const char* a_value);

        };

    } // namespace java
} // namespace casper

#endif // NRS_CASPER_CASPER_JAVA_FAKE_JAVA_SCANNER_H
