
#line 1 "src/casper/jrxml/bool_attr.rl"
/**
 * @file bool_attr.rl implementation of BoolAttr model attribute
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

#include "casper/jrxml/node.h"
#include "casper/jrxml/bool_attr.h"
#include "osal/osalite.h"

/**
 * @brief Convert from text to integer enum, does not validate, empty
 *        text is a no-op meaning the attribute is not present in the XML
 *
 * @param a_value text string to be parsed
 */
void casper::jrxml::BoolAttr::FromStr (const pugi::char_t* a_value)
{
    int   cs, act;
    char* ts, *te;
    char* p   = (char*) a_value;
    char* pe  = (char*) a_value + strlen(a_value);

    
#line 43 "src/casper/jrxml/bool_attr.cc"
static const int BoolAttr_start = 8;
static const int BoolAttr_first_final = 8;
static const int BoolAttr_error = 0;

static const int BoolAttr_en_main = 8;


#line 51 "src/casper/jrxml/bool_attr.cc"
	{
	cs = BoolAttr_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 59 "src/casper/jrxml/bool_attr.cc"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr4:
#line 45 "src/casper/jrxml/bool_attr.rl"
	{te = p+1;{ value_ = false; is_set_ = true; }}
	goto st8;
tr7:
#line 44 "src/casper/jrxml/bool_attr.rl"
	{te = p+1;{ value_ = true;  is_set_ = true; }}
	goto st8;
st8:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 1 "NONE"
	{ts = p;}
#line 81 "src/casper/jrxml/bool_attr.cc"
	switch( (*p) ) {
		case 102: goto st1;
		case 116: goto st5;
	}
	goto st0;
st0:
cs = 0;
	goto _out;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) == 97 )
		goto st2;
	goto st0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 108 )
		goto st3;
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 115 )
		goto st4;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 101 )
		goto tr4;
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 114 )
		goto st6;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 117 )
		goto st7;
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 101 )
		goto tr7;
	goto st0;
	}
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 51 "src/casper/jrxml/bool_attr.rl"


    OSAL_UNUSED_PARAM(BoolAttr_error);
    OSAL_UNUSED_PARAM(BoolAttr_en_main);
    OSAL_UNUSED_PARAM(BoolAttr_first_final);
    OSAL_UNUSED_PARAM(act);
    OSAL_UNUSED_PARAM(ts);
    OSAL_UNUSED_PARAM(te);
}
