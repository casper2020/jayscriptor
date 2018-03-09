/**
 * @file calculation_attr.h declaration of CalculationAttr simple enum
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
#ifndef NRS_CASPER_CASPER_JRXML_CALCULATION_ATTR_H
#define NRS_CASPER_CASPER_JRXML_CALCULATION_ATTR_H

#include "casper/jrxml/enum_attr.h"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Enumerated attribute for @TODO description
         */
        class CalculationAttr  : public EnumAttr
        {
        public: // Enum values

            enum
            {
                ENothing,           //!< No calculations are performed.
                ECount,             //!< Variable stores the number of the not null values encountered for the variable expression.
                EDistinctCount,     //!< Variable stores the number of distinct not null values encountered for the variable expression.
                ESum,               //!< Variable stores the sum of the not null values encountered for the variable expression. Numeric variables only.
                EAverage,           //!< Variable stores the average of the not null values encountered for the variable expression. Numeric variables only.
                ELowest,            //!< Variable stores the lowest value encountered for the variable expression.
                EHighest,           //!< Variable stores the highest value encountered for the variable expression.
                EStandardDeviation, //!< Variable stores the standard deviation of the not null values encountered for the variable expression. Numeric variables only.
                EVariance,          //!< Variable stores the variance of the not null values encountered for the variable expression. Numeric variables only.
                ESystem,            //!< Variable stores a system (custom) calculated value.
                EFirst              //!< Variable stores the first value encountered and ignores subsequent values.
            };

        public: // Methods

            void        FromStr     (const pugi::char_t* a_value);
            const char* ToStr       () const;
            operator    const char* () const { return ToStr(); }
        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_CALCULATION_ATTR_H
