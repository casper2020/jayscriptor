/**
 * @file fake_java_term.cc Implementation of FakeJavaTerm
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

#include "casper/java/fake_java_term.h"
#include "osal/exception.h"

/**
 * @brief Constructor
 */
casper::java::FakeJavaTerm::FakeJavaTerm ()
{
    /* empty */
}

/**
 * @brief Destructor
 */
casper::java::FakeJavaTerm::~FakeJavaTerm ()
{
    /* empty */
}

void casper::java::FakeJavaTerm::SetAndHandleError (int a_error)
{
    const char* flt;
    
    Term::SetAndHandleError(a_error);
    switch (type_ & EErrorMask ) {
        case ENan:        // "#N/A"
            flt = "NumberFormat";
            break;
        case EDiv0:       // "#DIV/0"
        case EValue:      // "#VALUE!"
        case ENumError:   // "#NUM!"
            flt = "ArithmeticException";
            break;
        case ERef:        // "#REF!"
        case ENullError:  // "#NULL!"
            flt = "NullPointer";
            throw OSAL_NULL_EXCEPTION("Exception '%s'", flt);
        case ENameError:  // "#NAME?"
            flt = "UnknownVariable";
            break;
        case EInvalidType:
            flt = "TypeError";
            break;
        case EIndexError:
            flt = "IndexOutOfBounds";
            break;
        default:
            flt = "Unknown";
            break;
    }
    throw OSAL_EXCEPTION("Exception '%s'", flt);
}
