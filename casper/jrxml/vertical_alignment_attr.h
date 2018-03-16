/**
 * @file vertical_alignment_attr.h declaration of VerticalAlignmentAttr simple enum
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
#ifndef NRS_CASPER_CASPER_JRXML_VERTICAL_ALIGNMENT_ATTR_H
#define NRS_CASPER_CASPER_JRXML_VERTICAL_ALIGNMENT_ATTR_H

#include "casper/jrxml/enum_attr.h"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Type of vertical alignment for the text object
         */
        class VerticalAlignmentAttr  : public EnumAttr
        {
        public: // Enum values

            enum
            {
                ETop,     //!< Text is aligned to the top
                EMiddle,  //!< Text is vertically centered
                EBottom   //!< Text is aligned to the bottom
            };

        public: // Methods

            void        FromStr     (const pugi::char_t* a_value);
            const char* ToStr       () const;
            operator    const char* () const { return ToStr(); }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_VERTICAL_ALIGNMENT_ATTR_H
