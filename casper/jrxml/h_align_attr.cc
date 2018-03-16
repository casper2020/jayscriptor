
#line 1 "src/casper/jrxml/h_align_attr.rl"
/**
 * @file h_align_attr.rl implementation of HAlignAttr simple enum
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

#include "casper/jrxml/h_align_attr.h"
#include "osal/osalite.h"

/**
 * @brief Convert from text to integer enum, does not validate, empty
 *        text is a no-op meaning the attribute is not present in the XML
 *
 * @param a_value text string to be parsed
 */
void casper::jrxml::HAlignAttr::FromStr (const pugi::char_t* a_value)
{
    int   cs, act;
    char* ts, *te;
    char* p   = (char*) a_value;
    char* pe  = (char*) a_value + strlen(a_value);

    
#line 42 "src/casper/jrxml/h_align_attr.cc"
static const int HAlignAttr_start = 13;
static const int HAlignAttr_first_final = 13;
static const int HAlignAttr_error = 0;

static const int HAlignAttr_en_main = 13;


#line 50 "src/casper/jrxml/h_align_attr.cc"
	{
	cs = HAlignAttr_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 58 "src/casper/jrxml/h_align_attr.cc"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr5:
#line 44 "src/casper/jrxml/h_align_attr.rl"
	{te = p+1;{ value_ = ECenter; }}
	goto st13;
tr8:
#line 43 "src/casper/jrxml/h_align_attr.rl"
	{te = p+1;{ value_ = ELeft;   }}
	goto st13;
tr12:
#line 45 "src/casper/jrxml/h_align_attr.rl"
	{te = p+1;{ value_ = ERight;  }}
	goto st13;
st13:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 1 "NONE"
	{ts = p;}
#line 84 "src/casper/jrxml/h_align_attr.cc"
	switch( (*p) ) {
		case 67: goto st1;
		case 76: goto st6;
		case 82: goto st9;
	}
	goto st0;
st0:
cs = 0;
	goto _out;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) == 101 )
		goto st2;
	goto st0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 110 )
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
	if ( (*p) == 101 )
		goto st5;
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 114 )
		goto tr5;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 101 )
		goto st7;
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 102 )
		goto st8;
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 116 )
		goto tr8;
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 105 )
		goto st10;
	goto st0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	if ( (*p) == 103 )
		goto st11;
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	if ( (*p) == 104 )
		goto st12;
	goto st0;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	if ( (*p) == 116 )
		goto tr12;
	goto st0;
	}
	_test_eof13: cs = 13; goto _test_eof; 
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

	_test_eof: {}
	_out: {}
	}

#line 51 "src/casper/jrxml/h_align_attr.rl"


    OSAL_UNUSED_PARAM(HAlignAttr_error);
    OSAL_UNUSED_PARAM(HAlignAttr_en_main);
    OSAL_UNUSED_PARAM(HAlignAttr_first_final);
    OSAL_UNUSED_PARAM(act);
    OSAL_UNUSED_PARAM(ts);
    OSAL_UNUSED_PARAM(te);
}

/**
 * @brief Convert internal numerical value to string
 *
 * @return the current enumeration value as string
 */
const char* casper::jrxml::HAlignAttr::ToStr () const
{
    static const char * str_values[] = {
        "",
        "Left",
        "Center",
        "Right"
    };
    return str_values[value_ + 1];
}
