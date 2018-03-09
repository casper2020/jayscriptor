/**
 * @file text_alignment_attr.h declaration of TextAlignmentAttr simple enum
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
#ifndef NRS_CASPER_CASPER_JRXML_TEXT_ALIGNMENT_ATTR_H
#define NRS_CASPER_CASPER_JRXML_TEXT_ALIGNMENT_ATTR_H

#include "casper/jrxml/enum_attr.h"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Type of alignment for the text object
         */
        class TextAlignmentAttr  : public EnumAttr
        {
        public: // Enum values

            enum
            {
                ELeft,     //!< Text is aligned to the left
                ECenter,   //!< Text is centered
                ERight,    //!< Text is aligned to the right
                EJustified //!< Text is justified.
            };

        public: // Methods

            void        FromStr     (const pugi::char_t* a_value);
            const char* ToStr       () const;
            operator    const char* () const { return ToStr(); }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_TEXT_ALIGNMENT_ATTR_H

