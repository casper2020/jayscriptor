
#line 1 "src/casper/jrxml/direction_attr.rl"
/**
 * @file direction_attr.rl implementation of DirectionAttr simple enum
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

#include "casper/jrxml/direction_attr.h"
#include "osal/osalite.h"

/**
 * @brief Convert from text to integer enum, does not validate, empty
 *        text is a no-op meaning the attribute is not present in the XML
 *
 * @param a_value text string to be parsed
 */
void casper::jrxml::DirectionAttr::FromStr (const pugi::char_t* a_value)
{
    int   cs, act;
    char* ts, *te;
    char* p   = (char*) a_value;
    char* pe  = (char*) a_value + strlen(a_value);

    
#line 42 "src/casper/jrxml/direction_attr.cc"
static const int direction_attr_start = 14;
static const int direction_attr_first_final = 14;
static const int direction_attr_error = 0;

static const int direction_attr_en_main = 14;


#line 50 "src/casper/jrxml/direction_attr.cc"
	{
	cs = direction_attr_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 58 "src/casper/jrxml/direction_attr.cc"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr7:
#line 44 "src/casper/jrxml/direction_attr.rl"
	{te = p+1;{ value_ = EBottomUp; }}
	goto st14;
tr13:
#line 43 "src/casper/jrxml/direction_attr.rl"
	{te = p+1;{ value_ = ETopDown;  }}
	goto st14;
st14:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof14;
case 14:
#line 1 "NONE"
	{ts = p;}
#line 80 "src/casper/jrxml/direction_attr.cc"
	switch( (*p) ) {
		case 66: goto st1;
		case 84: goto st8;
	}
	goto st0;
st0:
cs = 0;
	goto _out;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) == 111 )
		goto st2;
	goto st0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 116 )
		goto st3;
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 116 )
		goto st4;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 111 )
		goto st5;
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 109 )
		goto st6;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 85 )
		goto st7;
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 112 )
		goto tr7;
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 111 )
		goto st9;
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 112 )
		goto st10;
	goto st0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	if ( (*p) == 68 )
		goto st11;
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	if ( (*p) == 111 )
		goto st12;
	goto st0;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	if ( (*p) == 119 )
		goto st13;
	goto st0;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	if ( (*p) == 110 )
		goto tr13;
	goto st0;
	}
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 50 "src/casper/jrxml/direction_attr.rl"


    OSAL_UNUSED_PARAM(direction_attr_error);
    OSAL_UNUSED_PARAM(direction_attr_en_main);
    OSAL_UNUSED_PARAM(direction_attr_first_final);
    OSAL_UNUSED_PARAM(act);
    OSAL_UNUSED_PARAM(ts);
    OSAL_UNUSED_PARAM(te);
}

/**
 * @brief Convert internal numerical value to string
 *
 * @return the current enumeration value as string
 */
const char* casper::jrxml::DirectionAttr::ToStr () const
{
    static const char * str_values[] = {
        "",
        "TopDown",
        "BottomUp"
    };
    return str_values[value_ + 1];
}