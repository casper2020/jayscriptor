/**
 * @file position_type.h declaration of PositionType simple enum
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
#ifndef NRS_CASPER_JRXML_MODEL_position_type_H
#define NRS_CASPER_JRXML_MODEL_position_type_H

#include "jrxml/jrxml/enum_attr.h"

namespace jrxml
{
    namespace jrxml
    {
        /**
         * @brief Enumerated attribute for @TODO description
         */
        class PositionType  : public EnumAttr
        {
            enum
            {
                //!<
            };

        public: // Methods

            void FromStr (const pugi::char_t* a_value);
        };

    } // namespace jrxml
} // namespace jrxml

#endif // NRS_CASPER_JRXML_MODEL_position_type_H
