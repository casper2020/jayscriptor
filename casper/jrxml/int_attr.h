/**
 * @file int_attr.h declaration of IntAttr simple enum
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
#ifndef NRS_CASPER_CASPER_JRXML_INT_ATTR_H
#define NRS_CASPER_CASPER_JRXML_INT_ATTR_H

#include "casper/jrxml/enum_attr.h"
#include "casper/number_parser.h"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Enumerated attribute for @TODO description
         */
        class IntAttr
        {
        protected: // data
            
            int  value_;
            bool is_set_;
                
        public: // methods
            
            IntAttr ()
            {
                value_  = 0;
                is_set_ = false;
            }
            
            void Set (int a_value)
            {
                value_  = a_value;
                is_set_ = true;
            }
            
            operator bool () const
            {
                return value_;
            }

            bool IsSet () const
            {
                return is_set_;
            }

            /**
             * @brief Convert from text to integer enum, does not validate, empty
             *        text is a no-op meaning the attribute is not present in the XML
             *
             * @param a_value text string to be parsed
             */
            void FromStr (const pugi::char_t* a_value)
            {
                int tmp;
                
                if ( true == NumberParser::ParseInt(a_value, tmp) ) {
                    is_set_ = true;
                    value_  = tmp;
                }
            }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_INT_ATTR_H
