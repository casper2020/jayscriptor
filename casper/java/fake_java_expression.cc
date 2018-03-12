/**
 * @file fake_java_expression.cc Implementation of FakeJavaExpression
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

#include "casper/java/fake_java_expression.h"
#include "osal/osalite.h"

extern AstNode root;


casper::java::FakeJavaExpression::FakeJavaExpression () : parser_(scanner_, *this)
{
    /* empty */
}

casper::java::FakeJavaExpression::~FakeJavaExpression ()
{
    /* empty */
}


void casper::java::FakeJavaExpression::Convert (const std::string& a_expression){
    Convert(a_expression.c_str(), a_expression.size());
}

void casper::java::FakeJavaExpression::Convert (const char* a_expression, size_t a_len){
    try {
        root = ast_null();
        scanner_.SetInput(a_expression, a_len);
        parser_.parse();

        printJS(&root);

    } catch (osal::Exception& a_exception) {
        if ( a_exception .IsNull() ) {
            root = ast_null();
        } else {
            throw a_exception;
        }
    }
}
