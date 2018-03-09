
#line 1 "src/casper/jrxml/color_attr.rl"
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

    
#line 43 "src/casper/jrxml/color_attr.cc"
static const int color_parser_start = 1;
static const int color_parser_first_final = 61;
static const int color_parser_error = 0;

static const int color_parser_en_main = 1;


#line 51 "src/casper/jrxml/color_attr.cc"
	{
	cs = color_parser_start;
	}

#line 56 "src/casper/jrxml/color_attr.cc"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	switch( (*p) ) {
		case 35: goto st2;
		case 98: goto st8;
		case 99: goto st13;
		case 100: goto st16;
		case 103: goto st23;
		case 108: goto st28;
		case 109: goto st36;
		case 111: goto st42;
		case 112: goto st47;
		case 114: goto st50;
		case 119: goto st52;
		case 121: goto st56;
	}
	goto st0;
st0:
cs = 0;
	goto _out;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr13;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr15;
	} else
		goto tr14;
	goto st0;
tr13:
#line 42 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - '0'      ; }
	goto st3;
tr14:
#line 44 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - 'A' + 10 ; }
	goto st3;
tr15:
#line 43 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - 'a' + 10 ; }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 110 "src/casper/jrxml/color_attr.cc"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr16;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr18;
	} else
		goto tr17;
	goto st0;
tr16:
#line 42 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - '0'      ; }
	goto st4;
tr17:
#line 44 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - 'A' + 10 ; }
	goto st4;
tr18:
#line 43 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - 'a' + 10 ; }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 136 "src/casper/jrxml/color_attr.cc"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr19;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr21;
	} else
		goto tr20;
	goto st0;
tr19:
#line 42 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - '0'      ; }
	goto st5;
tr20:
#line 44 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - 'A' + 10 ; }
	goto st5;
tr21:
#line 43 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - 'a' + 10 ; }
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 162 "src/casper/jrxml/color_attr.cc"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr22;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr24;
	} else
		goto tr23;
	goto st0;
tr22:
#line 42 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - '0'      ; }
	goto st6;
tr23:
#line 44 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - 'A' + 10 ; }
	goto st6;
tr24:
#line 43 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - 'a' + 10 ; }
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 188 "src/casper/jrxml/color_attr.cc"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr25;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr27;
	} else
		goto tr26;
	goto st0;
tr25:
#line 42 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - '0'      ; }
	goto st7;
tr26:
#line 44 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - 'A' + 10 ; }
	goto st7;
tr27:
#line 43 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - 'a' + 10 ; }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 214 "src/casper/jrxml/color_attr.cc"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr28;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr30;
	} else
		goto tr29;
	goto st0;
tr28:
#line 42 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - '0'      ; }
	goto st61;
tr29:
#line 44 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - 'A' + 10 ; }
	goto st61;
tr30:
#line 43 "src/casper/jrxml/color_attr.rl"
	{ val <<= 4; val += (*p) - 'a' + 10 ; }
	goto st61;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
#line 240 "src/casper/jrxml/color_attr.cc"
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
	switch( (*p) ) {
		case 97: goto st10;
		case 117: goto st12;
	}
	goto st0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	if ( (*p) == 99 )
		goto st11;
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	if ( (*p) == 107 )
		goto st62;
	goto st0;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	goto st0;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	if ( (*p) == 101 )
		goto st63;
	goto st0;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	goto st0;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	if ( (*p) == 121 )
		goto st14;
	goto st0;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	if ( (*p) == 97 )
		goto st15;
	goto st0;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	if ( (*p) == 110 )
		goto st64;
	goto st0;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	goto st0;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	if ( (*p) == 97 )
		goto st17;
	goto st0;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	if ( (*p) == 114 )
		goto st18;
	goto st0;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	if ( (*p) == 107 )
		goto st19;
	goto st0;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	if ( (*p) == 71 )
		goto st20;
	goto st0;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	if ( (*p) == 114 )
		goto st21;
	goto st0;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	if ( (*p) == 97 )
		goto st22;
	goto st0;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	if ( (*p) == 121 )
		goto st65;
	goto st0;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	goto st0;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	if ( (*p) == 114 )
		goto st24;
	goto st0;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	switch( (*p) ) {
		case 97: goto st25;
		case 101: goto st26;
	}
	goto st0;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	if ( (*p) == 121 )
		goto st66;
	goto st0;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	goto st0;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	if ( (*p) == 101 )
		goto st27;
	goto st0;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	if ( (*p) == 110 )
		goto st67;
	goto st0;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	goto st0;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	if ( (*p) == 105 )
		goto st29;
	goto st0;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
	if ( (*p) == 103 )
		goto st30;
	goto st0;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	if ( (*p) == 104 )
		goto st31;
	goto st0;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	if ( (*p) == 116 )
		goto st32;
	goto st0;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	if ( (*p) == 71 )
		goto st33;
	goto st0;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	if ( (*p) == 114 )
		goto st34;
	goto st0;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	if ( (*p) == 97 )
		goto st35;
	goto st0;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	if ( (*p) == 121 )
		goto st68;
	goto st0;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	goto st0;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	if ( (*p) == 97 )
		goto st37;
	goto st0;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	if ( (*p) == 103 )
		goto st38;
	goto st0;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	if ( (*p) == 101 )
		goto st39;
	goto st0;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	if ( (*p) == 110 )
		goto st40;
	goto st0;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	if ( (*p) == 116 )
		goto st41;
	goto st0;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	if ( (*p) == 97 )
		goto st69;
	goto st0;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	goto st0;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	if ( (*p) == 114 )
		goto st43;
	goto st0;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	if ( (*p) == 97 )
		goto st44;
	goto st0;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	if ( (*p) == 110 )
		goto st45;
	goto st0;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	if ( (*p) == 103 )
		goto st46;
	goto st0;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	if ( (*p) == 101 )
		goto st70;
	goto st0;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	goto st0;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
	if ( (*p) == 105 )
		goto st48;
	goto st0;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	if ( (*p) == 110 )
		goto st49;
	goto st0;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	if ( (*p) == 107 )
		goto st71;
	goto st0;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	goto st0;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	if ( (*p) == 101 )
		goto st51;
	goto st0;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	if ( (*p) == 100 )
		goto st72;
	goto st0;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	goto st0;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	if ( (*p) == 104 )
		goto st53;
	goto st0;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	if ( (*p) == 105 )
		goto st54;
	goto st0;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	if ( (*p) == 116 )
		goto st55;
	goto st0;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	if ( (*p) == 101 )
		goto st73;
	goto st0;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	goto st0;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	if ( (*p) == 101 )
		goto st57;
	goto st0;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	if ( (*p) == 108 )
		goto st58;
	goto st0;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	if ( (*p) == 108 )
		goto st59;
	goto st0;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	if ( (*p) == 111 )
		goto st60;
	goto st0;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	if ( (*p) == 119 )
		goto st74;
	goto st0;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	goto st0;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof61: cs = 61; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof62: cs = 62; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof63: cs = 63; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof64: cs = 64; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof65: cs = 65; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof66: cs = 66; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof27: cs = 27; goto _test_eof; 
	_test_eof67: cs = 67; goto _test_eof; 
	_test_eof28: cs = 28; goto _test_eof; 
	_test_eof29: cs = 29; goto _test_eof; 
	_test_eof30: cs = 30; goto _test_eof; 
	_test_eof31: cs = 31; goto _test_eof; 
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof33: cs = 33; goto _test_eof; 
	_test_eof34: cs = 34; goto _test_eof; 
	_test_eof35: cs = 35; goto _test_eof; 
	_test_eof68: cs = 68; goto _test_eof; 
	_test_eof36: cs = 36; goto _test_eof; 
	_test_eof37: cs = 37; goto _test_eof; 
	_test_eof38: cs = 38; goto _test_eof; 
	_test_eof39: cs = 39; goto _test_eof; 
	_test_eof40: cs = 40; goto _test_eof; 
	_test_eof41: cs = 41; goto _test_eof; 
	_test_eof69: cs = 69; goto _test_eof; 
	_test_eof42: cs = 42; goto _test_eof; 
	_test_eof43: cs = 43; goto _test_eof; 
	_test_eof44: cs = 44; goto _test_eof; 
	_test_eof45: cs = 45; goto _test_eof; 
	_test_eof46: cs = 46; goto _test_eof; 
	_test_eof70: cs = 70; goto _test_eof; 
	_test_eof47: cs = 47; goto _test_eof; 
	_test_eof48: cs = 48; goto _test_eof; 
	_test_eof49: cs = 49; goto _test_eof; 
	_test_eof71: cs = 71; goto _test_eof; 
	_test_eof50: cs = 50; goto _test_eof; 
	_test_eof51: cs = 51; goto _test_eof; 
	_test_eof72: cs = 72; goto _test_eof; 
	_test_eof52: cs = 52; goto _test_eof; 
	_test_eof53: cs = 53; goto _test_eof; 
	_test_eof54: cs = 54; goto _test_eof; 
	_test_eof55: cs = 55; goto _test_eof; 
	_test_eof73: cs = 73; goto _test_eof; 
	_test_eof56: cs = 56; goto _test_eof; 
	_test_eof57: cs = 57; goto _test_eof; 
	_test_eof58: cs = 58; goto _test_eof; 
	_test_eof59: cs = 59; goto _test_eof; 
	_test_eof60: cs = 60; goto _test_eof; 
	_test_eof74: cs = 74; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 61: 
#line 44 "src/casper/jrxml/color_attr.rl"
	{ val |= 0xFF000000; }
	break;
	case 62: 
#line 46 "src/casper/jrxml/color_attr.rl"
	{ val = 0xFF000000; }
	break;
	case 63: 
#line 47 "src/casper/jrxml/color_attr.rl"
	{ val = 0xFF0000FF; }
	break;
	case 64: 
#line 48 "src/casper/jrxml/color_attr.rl"
	{ val = 0xFF00FFFF; }
	break;
	case 65: 
#line 49 "src/casper/jrxml/color_attr.rl"
	{ val = 0xFFA9A9A9; }
	break;
	case 66: 
#line 50 "src/casper/jrxml/color_attr.rl"
	{ val = 0xFF808080; }
	break;
	case 67: 
#line 51 "src/casper/jrxml/color_attr.rl"
	{ val = 0xFF00FF00; }
	break;
	case 68: 
#line 52 "src/casper/jrxml/color_attr.rl"
	{ val = 0xFFC0C0C0; }
	break;
	case 69: 
#line 53 "src/casper/jrxml/color_attr.rl"
	{ val = 0xFFFF00FF; }
	break;
	case 70: 
#line 54 "src/casper/jrxml/color_attr.rl"
	{ val = 0xFFFFA500; }
	break;
	case 71: 
#line 55 "src/casper/jrxml/color_attr.rl"
	{ val = 0xFFFFC0CB; }
	break;
	case 72: 
#line 56 "src/casper/jrxml/color_attr.rl"
	{ val = 0xFFFF0000; }
	break;
	case 74: 
#line 57 "src/casper/jrxml/color_attr.rl"
	{ val = 0xFFFFFF00; }
	break;
	case 73: 
#line 58 "src/casper/jrxml/color_attr.rl"
	{ val = 0xFFFFFFFF; }
	break;
#line 817 "src/casper/jrxml/color_attr.cc"
	}
	}

	_out: {}
	}

#line 65 "src/casper/jrxml/color_attr.rl"


    if ( cs >= color_parser_first_final ) {
        is_set_ = true;
        argb_   = val;
    }

    OSAL_UNUSED_PARAM(color_parser_error);
    OSAL_UNUSED_PARAM(color_parser_en_main);
}
