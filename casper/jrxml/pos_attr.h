/**
 * @file pos_attr.h declaration of PosAttr elementary attribute
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
#ifndef NRS_CASPER_CASPER_JRXML_POS_ATTR_H
#define NRS_CASPER_CASPER_JRXML_POS_ATTR_H

#include "pugixml.hpp"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Attribute to store element positions normalized to pixels
         */
        class PosAttr
        {
        protected: // data
            
            float value_;
            bool  is_set_;
            
        public: // Methods
            
            PosAttr ()
            {
                value_  = 0.0f;
                is_set_ = false;
            }
            
            void Set (float a_value)
            {
                value_  = a_value;
                is_set_ = true;
            }

            
            bool IsSet () const
            {
                return is_set_;
            }

            operator float () const
            {
                return value_;
            }
            
            void FromStr (const pugi::char_t* a_value);
        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_POS_ATTR_H
