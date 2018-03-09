/**
 * @file color_attr.rl implementation of ColorAttr simple enum
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

#include "osal/osalite.h"
#include "casper/jrxml/color_attr.h"

/**
 * @brief Convert from text to integer enum, does not validate, empty
 *        text is a no-op meaning the attribute is not present in the XML
 *
 * @param a_value text string to be parsed
 */
void casper::jrxml::ColorAttr::FromStr (const pugi::char_t* a_value)
{
    int   cs;
    int   val = 0;
    char* p   = (char*) a_value;
    char* pe  = (char*) a_value + strlen(a_value);
    char* eof = pe;

    %%{
        machine color_parser;

        hex_color     = ( '#' ([0-9] ${ val <<= 4; val += fc - '0'      ; } |
                               [a-f] ${ val <<= 4; val += fc - 'a' + 10 ; } |
                               [A-F] ${ val <<= 4; val += fc - 'A' + 10 ; }  ){6}  %{ val |= 0xFF000000; } );

        color_literal = ( 'black'      %{ val = 0xFF000000; } ) |
                        ( 'blue'       %{ val = 0xFF0000FF; } ) |
                        ( 'cyan'       %{ val = 0xFF00FFFF; } ) |
                        ( 'darkGray'   %{ val = 0xFFA9A9A9; } ) |
                        ( 'gray'       %{ val = 0xFF808080; } ) |
                        ( 'green'      %{ val = 0xFF00FF00; } ) |
                        ( 'lightGray'  %{ val = 0xFFC0C0C0; } ) |
                        ( 'magenta'    %{ val = 0xFFFF00FF; } ) |
                        ( 'orange'     %{ val = 0xFFFFA500; } ) |
                        ( 'pink'       %{ val = 0xFFFFC0CB; } ) |
                        ( 'red'        %{ val = 0xFFFF0000; } ) |
                        ( 'yellow'     %{ val = 0xFFFFFF00; } ) |
                        ( 'white'      %{ val = 0xFFFFFFFF; } ) ;

        main := color_literal | hex_color;

        write data;
        write init;
        write exec;
    }%%

    if ( cs >= color_parser_first_final ) {
        is_set_ = true;
        argb_   = val;
    }

    OSAL_UNUSED_PARAM(color_parser_error);
    OSAL_UNUSED_PARAM(color_parser_en_main);
}
