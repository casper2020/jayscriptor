/**
 * @file complex_evaluation_time_attr.rl implementation of ComplexEvaluationTimeAttr simple enum
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

#include "casper/jrxml/complex_evaluation_time_attr.h"
#include "osal/osalite.h"

/**
 * @brief Convert from text to integer enum, does not validate, empty
 *        text is a no-op meaning the attribute is not present in the XML
 *
 * @param a_value text string to be parsed
 */
void casper::jrxml::ComplexEvaluationTimeAttr::FromStr (const pugi::char_t* a_value)
{
    int   cs, act;
    char* ts, *te;
    char* p   = (char*) a_value;
    char* pe  = (char*) a_value + strlen(a_value);

    %%{
        machine complex_evaluation_time_attr;

        main := |*
            ''
            'Now'    => { value_ = ENow;    };
            'Report' => { value_ = EReport; };
            'Page'   => { value_ = EPage;   };
            'Column' => { value_ = EColumn; };
            'Group'  => { value_ = EGroup;  };
            'Band'   => { value_ = EBand;   };
            'Auto'   => { value_ = EAuto;   };
        *|;

        write data;
        write init;
        write exec;
    }%%

    OSAL_UNUSED_PARAM(complex_evaluation_time_attr_error);
    OSAL_UNUSED_PARAM(complex_evaluation_time_attr_en_main);
    OSAL_UNUSED_PARAM(complex_evaluation_time_attr_first_final);
    OSAL_UNUSED_PARAM(act);
    OSAL_UNUSED_PARAM(ts);
    OSAL_UNUSED_PARAM(te);
}

/**
 * @brief Convert internal numerical value to string
 *
 * @return the current enumeration value as string
 */
const char* casper::jrxml::ComplexEvaluationTimeAttr::ToStr () const
{
    static const char * str_values[] = {
        "",
        "Now",
        "Report",
        "Page",
        "Column",
        "Group",
        "Band",
        "Auto"
    };
    return str_values[value_ + 1];
}
