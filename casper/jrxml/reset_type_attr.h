/**
 * @file reset_type_attr.h declaration of ResetTypeAttr simple enum
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
#ifndef NRS_CASPER_CASPER_JRXML_RESET_TYPE_ATTR_H
#define NRS_CASPER_CASPER_JRXML_RESET_TYPE_ATTR_H

#include "casper/jrxml/enum_attr.h"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Reset level for variables that perform calculations.
         */
        class ResetTypeAttr  : public EnumAttr
        {
        public: // Enum values

            enum
            {
                ENone,   //!< Variable is never initialized using the initial value expression and only holds the values obtained by evaluating its main expression.
                EReport, //!< Variable is initialized only once, at the beginning of the report.</documentation>
                EPage,   //!< Variable is initialized at the beginning of each page.</documentation>
                EColumn, //!< Variable is initialized at the beginning of each column.</documentation>
                EGroup   //!< Variable is initialized when the group specified by the <code>resetGroup</code> attribute changes.</documentation>
            };

        public: // Methods

            void        FromStr     (const pugi::char_t* a_value);
            const char* ToStr       () const;
            operator    const char* () const { return ToStr(); }
        };

    } // namespace model
} // namespace jrxml

#endif // NRS_CASPER_CASPER_JRXML_RESET_TYPE_ATTR_H
