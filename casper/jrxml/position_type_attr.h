/**
 * @file position_type_attr.h declaration of PositionTypeAttr simple enum
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
#ifndef NRS_CASPER_CASPER_JRXML_POSITION_TYPE_ATTR_H
#define NRS_CASPER_CASPER_JRXML_POSITION_TYPE_ATTR_H

#include "casper/jrxml/enum_attr.h"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Specifies the object position when the report section is affected by stretch.
         */
        class PositionTypeAttr  : public EnumAttr
        {
        public: // Enum values

            enum
            {
                EFloat,              //!< The element moves relative to the size of the surrounding elements
                EFixRelativeToTop,   //!< The element maintains its position relative to the top of the band
                EFixRelativeToBottom //!< The element maintains its position relative to the bottom of the band
            };

        public: // Methods

            void        FromStr     (const pugi::char_t* a_value);
            const char* ToStr       () const;
            operator    const char* () const { return ToStr(); }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_POSITION_TYPE_ATTR_H
