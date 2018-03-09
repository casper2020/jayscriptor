/**
 * @file split_type_attr.h declaration of SplitTypeAttr simple enum
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
#ifndef NRS_CASPER_CASPER_JRXML_SPLIT_TYPE_ATTR_H
#define NRS_CASPER_CASPER_JRXML_SPLIT_TYPE_ATTR_H

#include "casper/jrxml/enum_attr.h"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Specifies the band split behavior
         */
        class SplitTypeAttr  : public EnumAttr
        {
        public: // values
            
            enum
            {
                EStretch,   //!< The band is allowed to split, but never within its declared height. This means the band splits only when its content stretches.
                EPrevent,   //!< Prevents the band from splitting on first break attempt. On subsequent pages/columns, the band is allowed to split, to avoid infinite loops.
                EImmediate  //!< The band is allowed to split anywhere, as early as needed, but not before at least one element being printed on the current page/column.
            };

        public: // Methods

            void        FromStr     (const pugi::char_t* a_value);
            const char* ToStr       () const;
            operator    const char* () const { return ToStr(); }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_SPLIT_TYPE_ATTR_H
