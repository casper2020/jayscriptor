
#line 1 "src/casper/jrxml/complex_evaluation_time_attr.rl"
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

    
#line 42 "src/casper/jrxml/complex_evaluation_time_attr.cc"
static const int complex_evaluation_time_attr_start = 26;
static const int complex_evaluation_time_attr_first_final = 26;
static const int complex_evaluation_time_attr_error = 0;

static const int complex_evaluation_time_attr_en_main = 26;


#line 50 "src/casper/jrxml/complex_evaluation_time_attr.cc"
	{
	cs = complex_evaluation_time_attr_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 58 "src/casper/jrxml/complex_evaluation_time_attr.cc"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr3:
#line 49 "src/casper/jrxml/complex_evaluation_time_attr.rl"
	{te = p+1;{ value_ = EAuto;   }}
	goto st26;
tr6:
#line 48 "src/casper/jrxml/complex_evaluation_time_attr.rl"
	{te = p+1;{ value_ = EBand;   }}
	goto st26;
tr11:
#line 46 "src/casper/jrxml/complex_evaluation_time_attr.rl"
	{te = p+1;{ value_ = EColumn; }}
	goto st26;
tr15:
#line 47 "src/casper/jrxml/complex_evaluation_time_attr.rl"
	{te = p+1;{ value_ = EGroup;  }}
	goto st26;
tr17:
#line 43 "src/casper/jrxml/complex_evaluation_time_attr.rl"
	{te = p+1;{ value_ = ENow;    }}
	goto st26;
tr20:
#line 45 "src/casper/jrxml/complex_evaluation_time_attr.rl"
	{te = p+1;{ value_ = EPage;   }}
	goto st26;
tr25:
#line 44 "src/casper/jrxml/complex_evaluation_time_attr.rl"
	{te = p+1;{ value_ = EReport; }}
	goto st26;
st26:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof26;
case 26:
#line 1 "NONE"
	{ts = p;}
#line 100 "src/casper/jrxml/complex_evaluation_time_attr.cc"
	switch( (*p) ) {
		case 65: goto st1;
		case 66: goto st4;
		case 67: goto st7;
		case 71: goto st12;
		case 78: goto st16;
		case 80: goto st18;
		case 82: goto st21;
	}
	goto st0;
st0:
cs = 0;
	goto _out;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) == 117 )
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
	if ( (*p) == 111 )
		goto tr3;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 97 )
		goto st5;
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 110 )
		goto st6;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 100 )
		goto tr6;
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 111 )
		goto st8;
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 108 )
		goto st9;
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 117 )
		goto st10;
	goto st0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	if ( (*p) == 109 )
		goto st11;
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	if ( (*p) == 110 )
		goto tr11;
	goto st0;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	if ( (*p) == 114 )
		goto st13;
	goto st0;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	if ( (*p) == 111 )
		goto st14;
	goto st0;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	if ( (*p) == 117 )
		goto st15;
	goto st0;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	if ( (*p) == 112 )
		goto tr15;
	goto st0;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	if ( (*p) == 111 )
		goto st17;
	goto st0;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	if ( (*p) == 119 )
		goto tr17;
	goto st0;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	if ( (*p) == 97 )
		goto st19;
	goto st0;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	if ( (*p) == 103 )
		goto st20;
	goto st0;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	if ( (*p) == 101 )
		goto tr20;
	goto st0;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	if ( (*p) == 101 )
		goto st22;
	goto st0;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	if ( (*p) == 112 )
		goto st23;
	goto st0;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	if ( (*p) == 111 )
		goto st24;
	goto st0;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	if ( (*p) == 114 )
		goto st25;
	goto st0;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	if ( (*p) == 116 )
		goto tr25;
	goto st0;
	}
	_test_eof26: cs = 26; goto _test_eof; 
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
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 55 "src/casper/jrxml/complex_evaluation_time_attr.rl"


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
