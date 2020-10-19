/**
 * @file scanner.cc
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


#include "casper/scanner.h"

#include <stdlib.h>

const uint8_t casper::Scanner::k_max_fractional_digits_ = 18;


/**
 * @brief Default constructor.
 */
casper::Scanner::Scanner ()
    : p_(NULL), pe_(NULL), eof_(NULL)
{
    negative_              = false;
    integer_               = 0;
    fractional_            = 0;
    fractional_digits_cnt_ = 0;
    divider_               = 1;
    negative_exponent_     = false;
    exponent_              = 0;
    valid_read_            = false;
}

/**
 * @brief Destructor.
 */
casper::Scanner::~Scanner ()
{
    /* Sanitary base destructor */
}

/**
 * @brief Set input.
 *
 * @param a_expression
 * @param a_length
 */
void casper::Scanner::SetInput (const char* a_expression, size_t a_lenght)
{
    input_ = a_expression;
    p_     = a_expression;
    pe_    = a_expression + a_lenght;
    eof_   = pe_;    
}

/**
 * @brief Throw a \link std::runtime_error \link with input message and error location.
 *
 * @param a_title
 * @param a_column
 */
void casper::Scanner::ThrowParsingError (const std::string& a_title, const unsigned int& a_column)
{
    const size_t l1 = a_title.length() + ( ( pe_ - input_ ) + ( a_column + 20 ) ) * sizeof(char);
    char* b1        = new char[l1]; b1[0] = '\0';
    
    snprintf(b1, l1 - sizeof(char),
             "%s:\n"
             "   %*.*s\n"
             "   %*.*s^~~~~~\n",
             a_title.c_str(),
             (int)(pe_ - input_), (int)(pe_ - input_), input_,
             a_column, a_column, " "
    );
    
    const std::string msg = std::string(b1);
    
    delete [] b1;
    
    throw std::runtime_error(msg);
}
