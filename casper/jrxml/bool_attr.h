/**
 * @file bool_attr.h declaration of BoolAttr simple enum
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
#ifndef NRS_CASPER_CASPER_JRXML_BOOL_ATTR_H
#define NRS_CASPER_CASPER_JRXML_BOOL_ATTR_H

#include "casper/jrxml/node.h"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Enumerated attribute for @TODO description
         */
        class BoolAttr
        {
        protected: // data

            bool value_;
            bool is_set_;
            
        public: // Methods
            
            BoolAttr ()
            {
                is_set_ = false;
                value_  = false;
            }
            
            void Set (bool a_value)
            {
                value_ = a_value;
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
            
            void FromStr (const pugi::char_t* a_value);
        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_BOOL_ATTR_H
