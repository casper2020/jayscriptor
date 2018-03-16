/**
 * @file string_attr.h declaration of StringAttr attribute
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
#ifndef NRS_CASPER_CASPER_JRXML_STRING_ATTR_H
#define NRS_CASPER_CASPER_JRXML_STRING_ATTR_H

#include <string>

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Simple read-only string attribute for JRXML model nodes
         */
        class StringAttr
        {
        protected: // Data
            
            std::string value_;
            bool        is_set_;
            
        public: // Methods
            
            StringAttr ()
            {
                is_set_ = false;
            }
            
            void Set (const char* a_value)
            {
                value_  = a_value;
                is_set_ = true;
            }
            
            void Set (std::string a_value)
            {
                value_  = a_value;
                is_set_ = false;
            }
   
            /**
             * @brief Convert from text to integer enum, does not validate, empty
             *        text is a no-op meaning the attribute is not present in the XML
             *
             * @param a_value text string to be parsed
             */
            void FromStr (const pugi::char_t* a_value)
            {
                if ( a_value[0] == 0) {
                    return;
                } else {
                    is_set_ = true;
                    value_ = a_value;
                }
            }
            
            bool IsSet () const
            {
                return is_set_;
            }
            
            void operator = (const StringAttr& a_attr)
            {
                value_  = a_attr.value_;
                is_set_ = a_attr.is_set_;
            }
            
            operator const char* () const
            {
                return value_.c_str();
            }
            
            const char* c_str() const
            {
                return value_.c_str();
            }
            
            const std::string& Value () const
            {
                return value_;
            }
            
            static std::string Trim (const std::string& a_string)
            {
                const auto string_begin = a_string.find_first_not_of(" ");
                if ( std::string::npos == string_begin ) {
                    return ""; // no content
                }
                const auto string_end   = a_string.find_last_not_of(" ");
                const auto string_range = string_end - string_begin + 1;
                // remove whie spaces
                return a_string.substr(string_begin, string_range);
            }
            
        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_STRING_ATTR_H
