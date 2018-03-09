/**
 * @file color_attr.h declaration of ColorAttr simple enum
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
#ifndef NRS_CASPER_CASPER_JRXML_COLOR_ATTR_H
#define NRS_CASPER_CASPER_JRXML_COLOR_ATTR_H

#include "pugixml.hpp"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Attribute to hold colors
         */
        class ColorAttr
        {
        protected: // data
            
            bool     is_set_;
            uint32_t argb_;

        public: // Methods

            ColorAttr ()
            {
                is_set_ = false;
                argb_   = 0;
            }

            void Set (uint32_t a_argb)
            {
                is_set_ = true;
                argb_   = a_argb;
            }

            operator uint32_t () const
            {
                return argb_;
            }

            float Alpha () const
            {
                return (float) ((argb_ & 0xFF000000) >> 24) / 255.0f;
            }

            float Red () const
            {
                return (float) ((argb_ & 0x00FF0000) >> 16) / 255.0f;
            }

            float Green () const
            {
                return (float) ((argb_ & 0x0000FF00) >> 8) / 255.0f;
            }
            
            float Blue () const
            {
                return (float) ((argb_ & 0x000000FF)     ) / 255.0f ;
            }

            bool IsSet () const
            {
                return is_set_;
            }

            void FromStr (const pugi::char_t* a_value);
        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_COLOR_ATTR_H
