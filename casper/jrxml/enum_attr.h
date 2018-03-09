/**
 * @file enum_attr.h declaration of EnumAttr base class for all simple enum attributes
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
#ifndef NRS_CASPER_CASPER_JRXML_ENUM_ATTR_H
#define NRS_CASPER_CASPER_JRXML_ENUM_ATTR_H

#include "casper/jrxml/node.h"
#include "pugixml.hpp"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief base class for all simple enum attributes
         */
        class EnumAttr
        {
        protected: // Attributes
            
            int value_;
            
        public:

            enum
            {
                EUndefined = -1
            };
            
            EnumAttr ()
            {
                value_ = EUndefined;
            }
            
            void Set (int a_value)
            {
                value_ = a_value;
            }
            
            bool IsSet () const
            {
                return value_ != EUndefined;
            }
            
            operator int () const
            {
                return value_;
            }
        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_ENUM_ATTR_H
