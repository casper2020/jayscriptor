/**
 * @file scale_image_attr.rl implementation of ScaleImageAttr simple enum
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

#include "casper/jrxml/scale_image_attr.h"
#include "osal/osalite.h"

/**
 * @brief Convert from text to integer enum, does not validate, empty
 *        text is a no-op meaning the attribute is not present in the XML
 *
 * @param a_value text string to be parsed
 */
void casper::jrxml::ScaleImageAttr::FromStr (const pugi::char_t* a_value)
{
    int   cs, act;
    char* ts, *te;
    char* p   = (char*) a_value;
    char* pe  = (char*) a_value + strlen(a_value);

    %%{
        machine scale_image_attr;

        main := |*
            ''
            'Clip'        => { value_ = EClip;        };
            'FillFrame'   => { value_ = EFillFrame;   };
            'RetainShape' => { value_ = ERetainShape; };
            'RealHeight'  => { value_ = ERealHeight;  };
            'RealSize'    => { value_ = ERealSize;    };
        *|;

        write data;
        write init;
        write exec;
    }%%

    OSAL_UNUSED_PARAM(scale_image_attr_error);
    OSAL_UNUSED_PARAM(scale_image_attr_en_main);
    OSAL_UNUSED_PARAM(scale_image_attr_first_final);
    OSAL_UNUSED_PARAM(act);
    OSAL_UNUSED_PARAM(ts);
    OSAL_UNUSED_PARAM(te);
}

/**
 * @brief Convert internal numerical value to string
 *
 * @return the current enumeration value as string
 */
const char* casper::jrxml::ScaleImageAttr::ToStr () const
{
    static const char * str_values[] = {
        "",
        "Clip",
        "FillFrame",
        "RetainShape",
        "RealHeight",
        "RealSize"
    };
    return str_values[value_ + 1];
}