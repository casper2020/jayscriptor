/**
 * @file fake_java_term.h Specialization of term that throws faults
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
#ifndef NRS_CASPER_CASPER_JAVA_FAKE_JAVA_TERM_H
#define NRS_CASPER_CASPER_JAVA_FAKE_JAVA_TERM_H

#include "casper/term.h"


namespace casper
{
    namespace java
    {
        /**
         * @brief Specialization of term that throws faults
         */
        class FakeJavaTerm : public Term
        {
        public: // Methods

                     FakeJavaTerm      ();
            virtual ~FakeJavaTerm      ();

            virtual void  SetAndHandleError  (int a_error);
            void          operator          =(const char* a_string);
            void          operator          =(std::string a_string);
            void          operator          =(double a_value);

        };

        inline void FakeJavaTerm::operator =(const char* a_string)
        {
            text_ = a_string;
            type_ = EText;
        }

        inline void FakeJavaTerm::operator =(std::string a_string)
        {
            text_ = a_string;
            type_ = EText;
        }

        inline void FakeJavaTerm::operator =(double a_value)
        {
            number_ = a_value;
            type_   = ENumber;
        }

    } // namespace see
} // namespace casper

#endif // NRS_CASPER_CASPER_JAVA_FAKE_JAVA_TERM_H
