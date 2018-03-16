
#line 1 "src/casper/jrxml/node_element_factory.rl"
/**
 * @file node_element_factory.rl element factory for JRXML parser
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
#include "casper/jrxml/band.h"
#include "casper/jrxml/box.h"
#include "casper/jrxml/break.h"
#include "casper/jrxml/element_group.h"
#include "casper/jrxml/ellipse.h"
#include "casper/jrxml/field.h"
#include "casper/jrxml/font.h"
#include "casper/jrxml/group.h"
#include "casper/jrxml/group_header.h"
#include "casper/jrxml/group_footer.h"
#include "casper/jrxml/style.h"
#include "casper/jrxml/frame.h"
#include "casper/jrxml/image.h"
#include "casper/jrxml/line.h"
#include "casper/jrxml/pen.h"
#include "casper/jrxml/parameter.h"
#include "casper/jrxml/rectangle.h"
#include "casper/jrxml/static_text.h"
#include "casper/jrxml/text.h"
#include "casper/jrxml/text_element.h"
#include "casper/jrxml/text_field.h"
#include "casper/jrxml/variable.h"
#include "casper/jrxml/title.h"
#include "osal/osalite.h"

/**
 * @brief
 *
 *
 * @param  a_parent Parent node of the element node created
 * @return
 */
casper::jrxml::Node* casper::jrxml::Node::ElementFactory (const char* a_element_name, pugi::xml_node a_xml_node, Node* a_parent)
{
    int   cs, act;
    char* ts, *te;
    char* p    = (char*) a_element_name;
    char* pe   = (char*) a_element_name + strlen(a_element_name);
    char* eof  = pe;
    Node* node = NULL;

    
#line 68 "src/casper/jrxml/node_element_factory.cc"
static const int element_factory_start = 125;
static const int element_factory_first_final = 125;
static const int element_factory_error = 0;

static const int element_factory_en_main = 125;


#line 76 "src/casper/jrxml/node_element_factory.cc"
	{
	cs = element_factory_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 84 "src/casper/jrxml/node_element_factory.cc"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr5:
#line 68 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Band::CreateFromXml(a_xml_node, a_parent);         }}
	goto st125;
tr7:
#line 69 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Box::CreateFromXml(a_xml_node, a_parent);          }}
	goto st125;
tr13:
#line 86 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Pen::CreateFromXml(a_xml_node, a_parent);          }}
	goto st125;
tr16:
#line 70 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Break::CreateFromXml(a_xml_node, a_parent);        }}
	goto st125;
tr28:
#line 71 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = ElementGroup::CreateFromXml(a_xml_node, a_parent); }}
	goto st125;
tr32:
#line 76 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Ellipse::CreateFromXml(a_xml_node, a_parent);      }}
	goto st125;
tr38:
#line 77 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Field::CreateFromXml(a_xml_node, a_parent);        }}
	goto st125;
tr40:
#line 78 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Font::CreateFromXml(a_xml_node, a_parent);         }}
	goto st125;
tr43:
#line 79 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Frame::CreateFromXml(a_xml_node, a_parent);        }}
	goto st125;
tr48:
#line 72 "src/casper/jrxml/node_element_factory.rl"
	{{p = ((te))-1;}{ node = Group::CreateFromXml(a_xml_node, a_parent);        }}
	goto st125;
tr53:
#line 74 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = GroupFooter::CreateFromXml(a_xml_node, a_parent);  }}
	goto st125;
tr58:
#line 73 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = GroupHeader::CreateFromXml(a_xml_node, a_parent);  }}
	goto st125;
tr62:
#line 80 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Image::CreateFromXml(a_xml_node, a_parent);        }}
	goto st125;
tr69:
#line 84 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Pen::CreateFromXml(a_xml_node, a_parent);          }}
	goto st125;
tr71:
#line 81 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Line::CreateFromXml(a_xml_node, a_parent);         }}
	goto st125;
tr80:
#line 88 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Parameter::CreateFromXml(a_xml_node, a_parent);    }}
	goto st125;
tr81:
#line 82 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Pen::CreateFromXml(a_xml_node, a_parent);          }}
	goto st125;
tr90:
#line 87 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Rectangle::CreateFromXml(a_xml_node, a_parent);    }}
	goto st125;
tr96:
#line 85 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Pen::CreateFromXml(a_xml_node, a_parent);          }}
	goto st125;
tr106:
#line 89 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = StaticText::CreateFromXml(a_xml_node, a_parent);   }}
	goto st125;
tr108:
#line 90 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Style::CreateFromXml(a_xml_node, a_parent);        }}
	goto st125;
tr114:
#line 92 "src/casper/jrxml/node_element_factory.rl"
	{{p = ((te))-1;}{ node = Text::CreateFromXml(a_xml_node, a_parent);         }}
	goto st125;
tr120:
#line 93 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = TextElement::CreateFromXml(a_xml_node, a_parent);  }}
	goto st125;
tr124:
#line 91 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = TextField::CreateFromXml(a_xml_node, a_parent);    }}
	goto st125;
tr127:
#line 75 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Title::CreateFromXml(a_xml_node, a_parent);        }}
	goto st125;
tr131:
#line 83 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Pen::CreateFromXml(a_xml_node, a_parent);          }}
	goto st125;
tr138:
#line 95 "src/casper/jrxml/node_element_factory.rl"
	{te = p+1;{ node = Variable::CreateFromXml(a_xml_node, a_parent);     }}
	goto st125;
tr150:
#line 72 "src/casper/jrxml/node_element_factory.rl"
	{te = p;p--;{ node = Group::CreateFromXml(a_xml_node, a_parent);        }}
	goto st125;
tr153:
#line 92 "src/casper/jrxml/node_element_factory.rl"
	{te = p;p--;{ node = Text::CreateFromXml(a_xml_node, a_parent);         }}
	goto st125;
st125:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof125;
case 125:
#line 1 "NONE"
	{ts = p;}
#line 214 "src/casper/jrxml/node_element_factory.cc"
	switch( (*p) ) {
		case 98: goto st1;
		case 101: goto st14;
		case 102: goto st29;
		case 103: goto st38;
		case 105: goto st52;
		case 108: goto st56;
		case 112: goto st64;
		case 114: goto st73;
		case 115: goto st87;
		case 116: goto st98;
		case 118: goto st118;
	}
	goto st0;
st0:
cs = 0;
	goto _out;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	switch( (*p) ) {
		case 97: goto st2;
		case 111: goto st4;
		case 114: goto st11;
	}
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
	if ( (*p) == 100 )
		goto tr5;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	switch( (*p) ) {
		case 116: goto st5;
		case 120: goto tr7;
	}
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 116 )
		goto st6;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 111 )
		goto st7;
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 109 )
		goto st8;
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 80 )
		goto st9;
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 101 )
		goto st10;
	goto st0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	if ( (*p) == 110 )
		goto tr13;
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	if ( (*p) == 101 )
		goto st12;
	goto st0;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	if ( (*p) == 97 )
		goto st13;
	goto st0;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	if ( (*p) == 107 )
		goto tr16;
	goto st0;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	if ( (*p) == 108 )
		goto st15;
	goto st0;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	switch( (*p) ) {
		case 101: goto st16;
		case 108: goto st25;
	}
	goto st0;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	if ( (*p) == 109 )
		goto st17;
	goto st0;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	if ( (*p) == 101 )
		goto st18;
	goto st0;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	if ( (*p) == 110 )
		goto st19;
	goto st0;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	if ( (*p) == 116 )
		goto st20;
	goto st0;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	if ( (*p) == 71 )
		goto st21;
	goto st0;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	if ( (*p) == 114 )
		goto st22;
	goto st0;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	if ( (*p) == 111 )
		goto st23;
	goto st0;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	if ( (*p) == 117 )
		goto st24;
	goto st0;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	if ( (*p) == 112 )
		goto tr28;
	goto st0;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	if ( (*p) == 105 )
		goto st26;
	goto st0;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	if ( (*p) == 112 )
		goto st27;
	goto st0;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	if ( (*p) == 115 )
		goto st28;
	goto st0;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	if ( (*p) == 101 )
		goto tr32;
	goto st0;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
	switch( (*p) ) {
		case 105: goto st30;
		case 111: goto st33;
		case 114: goto st35;
	}
	goto st0;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	if ( (*p) == 101 )
		goto st31;
	goto st0;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	if ( (*p) == 108 )
		goto st32;
	goto st0;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	if ( (*p) == 100 )
		goto tr38;
	goto st0;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	if ( (*p) == 110 )
		goto st34;
	goto st0;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	if ( (*p) == 116 )
		goto tr40;
	goto st0;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	if ( (*p) == 97 )
		goto st36;
	goto st0;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	if ( (*p) == 109 )
		goto st37;
	goto st0;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	if ( (*p) == 101 )
		goto tr43;
	goto st0;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	if ( (*p) == 114 )
		goto st39;
	goto st0;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	if ( (*p) == 111 )
		goto st40;
	goto st0;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	if ( (*p) == 117 )
		goto st41;
	goto st0;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	if ( (*p) == 112 )
		goto tr47;
	goto st0;
tr47:
#line 1 "NONE"
	{te = p+1;}
	goto st126;
st126:
	if ( ++p == pe )
		goto _test_eof126;
case 126:
#line 537 "src/casper/jrxml/node_element_factory.cc"
	switch( (*p) ) {
		case 70: goto st42;
		case 72: goto st47;
	}
	goto tr150;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	if ( (*p) == 111 )
		goto st43;
	goto tr48;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	if ( (*p) == 111 )
		goto st44;
	goto tr48;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	if ( (*p) == 116 )
		goto st45;
	goto tr48;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	if ( (*p) == 101 )
		goto st46;
	goto tr48;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	if ( (*p) == 114 )
		goto tr53;
	goto tr48;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
	if ( (*p) == 101 )
		goto st48;
	goto tr48;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	if ( (*p) == 97 )
		goto st49;
	goto tr48;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	if ( (*p) == 100 )
		goto st50;
	goto tr48;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	if ( (*p) == 101 )
		goto st51;
	goto tr48;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	if ( (*p) == 114 )
		goto tr58;
	goto tr48;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	if ( (*p) == 109 )
		goto st53;
	goto st0;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	if ( (*p) == 97 )
		goto st54;
	goto st0;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	if ( (*p) == 103 )
		goto st55;
	goto st0;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	if ( (*p) == 101 )
		goto tr62;
	goto st0;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	switch( (*p) ) {
		case 101: goto st57;
		case 105: goto st62;
	}
	goto st0;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	if ( (*p) == 102 )
		goto st58;
	goto st0;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	if ( (*p) == 116 )
		goto st59;
	goto st0;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	if ( (*p) == 80 )
		goto st60;
	goto st0;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	if ( (*p) == 101 )
		goto st61;
	goto st0;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	if ( (*p) == 110 )
		goto tr69;
	goto st0;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	if ( (*p) == 110 )
		goto st63;
	goto st0;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	if ( (*p) == 101 )
		goto tr71;
	goto st0;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	switch( (*p) ) {
		case 97: goto st65;
		case 101: goto st72;
	}
	goto st0;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	if ( (*p) == 114 )
		goto st66;
	goto st0;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	if ( (*p) == 97 )
		goto st67;
	goto st0;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	if ( (*p) == 109 )
		goto st68;
	goto st0;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	if ( (*p) == 101 )
		goto st69;
	goto st0;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	if ( (*p) == 116 )
		goto st70;
	goto st0;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	if ( (*p) == 101 )
		goto st71;
	goto st0;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	if ( (*p) == 114 )
		goto tr80;
	goto st0;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	if ( (*p) == 110 )
		goto tr81;
	goto st0;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	switch( (*p) ) {
		case 101: goto st74;
		case 105: goto st81;
	}
	goto st0;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	if ( (*p) == 99 )
		goto st75;
	goto st0;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	if ( (*p) == 116 )
		goto st76;
	goto st0;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	if ( (*p) == 97 )
		goto st77;
	goto st0;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	if ( (*p) == 110 )
		goto st78;
	goto st0;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	if ( (*p) == 103 )
		goto st79;
	goto st0;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	if ( (*p) == 108 )
		goto st80;
	goto st0;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	if ( (*p) == 101 )
		goto tr90;
	goto st0;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	if ( (*p) == 103 )
		goto st82;
	goto st0;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	if ( (*p) == 104 )
		goto st83;
	goto st0;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	if ( (*p) == 116 )
		goto st84;
	goto st0;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	if ( (*p) == 80 )
		goto st85;
	goto st0;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	if ( (*p) == 101 )
		goto st86;
	goto st0;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
	if ( (*p) == 110 )
		goto tr96;
	goto st0;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	if ( (*p) == 116 )
		goto st88;
	goto st0;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	switch( (*p) ) {
		case 97: goto st89;
		case 121: goto st96;
	}
	goto st0;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
	if ( (*p) == 116 )
		goto st90;
	goto st0;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
	if ( (*p) == 105 )
		goto st91;
	goto st0;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
	if ( (*p) == 99 )
		goto st92;
	goto st0;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
	if ( (*p) == 84 )
		goto st93;
	goto st0;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
	if ( (*p) == 101 )
		goto st94;
	goto st0;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
	if ( (*p) == 120 )
		goto st95;
	goto st0;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
	if ( (*p) == 116 )
		goto tr106;
	goto st0;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	if ( (*p) == 108 )
		goto st97;
	goto st0;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	if ( (*p) == 101 )
		goto tr108;
	goto st0;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
	switch( (*p) ) {
		case 101: goto st99;
		case 105: goto st111;
		case 111: goto st114;
	}
	goto st0;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	if ( (*p) == 120 )
		goto st100;
	goto st0;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
	if ( (*p) == 116 )
		goto tr113;
	goto st0;
tr113:
#line 1 "NONE"
	{te = p+1;}
	goto st127;
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
#line 975 "src/casper/jrxml/node_element_factory.cc"
	switch( (*p) ) {
		case 69: goto st101;
		case 70: goto st107;
	}
	goto tr153;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
	if ( (*p) == 108 )
		goto st102;
	goto tr114;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
	if ( (*p) == 101 )
		goto st103;
	goto tr114;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
	if ( (*p) == 109 )
		goto st104;
	goto tr114;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
	if ( (*p) == 101 )
		goto st105;
	goto tr114;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
	if ( (*p) == 110 )
		goto st106;
	goto tr114;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
	if ( (*p) == 116 )
		goto tr120;
	goto tr114;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
	if ( (*p) == 105 )
		goto st108;
	goto tr114;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
	if ( (*p) == 101 )
		goto st109;
	goto tr114;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
	if ( (*p) == 108 )
		goto st110;
	goto tr114;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
	if ( (*p) == 100 )
		goto tr124;
	goto tr114;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
	if ( (*p) == 116 )
		goto st112;
	goto st0;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
	if ( (*p) == 108 )
		goto st113;
	goto st0;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
	if ( (*p) == 101 )
		goto tr127;
	goto st0;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
	if ( (*p) == 112 )
		goto st115;
	goto st0;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
	if ( (*p) == 80 )
		goto st116;
	goto st0;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
	if ( (*p) == 101 )
		goto st117;
	goto st0;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
	if ( (*p) == 110 )
		goto tr131;
	goto st0;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
	if ( (*p) == 97 )
		goto st119;
	goto st0;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
	if ( (*p) == 114 )
		goto st120;
	goto st0;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
	if ( (*p) == 105 )
		goto st121;
	goto st0;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
	if ( (*p) == 97 )
		goto st122;
	goto st0;
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
	if ( (*p) == 98 )
		goto st123;
	goto st0;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
	if ( (*p) == 108 )
		goto st124;
	goto st0;
st124:
	if ( ++p == pe )
		goto _test_eof124;
case 124:
	if ( (*p) == 101 )
		goto tr138;
	goto st0;
	}
	_test_eof125: cs = 125; goto _test_eof; 
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
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof27: cs = 27; goto _test_eof; 
	_test_eof28: cs = 28; goto _test_eof; 
	_test_eof29: cs = 29; goto _test_eof; 
	_test_eof30: cs = 30; goto _test_eof; 
	_test_eof31: cs = 31; goto _test_eof; 
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof33: cs = 33; goto _test_eof; 
	_test_eof34: cs = 34; goto _test_eof; 
	_test_eof35: cs = 35; goto _test_eof; 
	_test_eof36: cs = 36; goto _test_eof; 
	_test_eof37: cs = 37; goto _test_eof; 
	_test_eof38: cs = 38; goto _test_eof; 
	_test_eof39: cs = 39; goto _test_eof; 
	_test_eof40: cs = 40; goto _test_eof; 
	_test_eof41: cs = 41; goto _test_eof; 
	_test_eof126: cs = 126; goto _test_eof; 
	_test_eof42: cs = 42; goto _test_eof; 
	_test_eof43: cs = 43; goto _test_eof; 
	_test_eof44: cs = 44; goto _test_eof; 
	_test_eof45: cs = 45; goto _test_eof; 
	_test_eof46: cs = 46; goto _test_eof; 
	_test_eof47: cs = 47; goto _test_eof; 
	_test_eof48: cs = 48; goto _test_eof; 
	_test_eof49: cs = 49; goto _test_eof; 
	_test_eof50: cs = 50; goto _test_eof; 
	_test_eof51: cs = 51; goto _test_eof; 
	_test_eof52: cs = 52; goto _test_eof; 
	_test_eof53: cs = 53; goto _test_eof; 
	_test_eof54: cs = 54; goto _test_eof; 
	_test_eof55: cs = 55; goto _test_eof; 
	_test_eof56: cs = 56; goto _test_eof; 
	_test_eof57: cs = 57; goto _test_eof; 
	_test_eof58: cs = 58; goto _test_eof; 
	_test_eof59: cs = 59; goto _test_eof; 
	_test_eof60: cs = 60; goto _test_eof; 
	_test_eof61: cs = 61; goto _test_eof; 
	_test_eof62: cs = 62; goto _test_eof; 
	_test_eof63: cs = 63; goto _test_eof; 
	_test_eof64: cs = 64; goto _test_eof; 
	_test_eof65: cs = 65; goto _test_eof; 
	_test_eof66: cs = 66; goto _test_eof; 
	_test_eof67: cs = 67; goto _test_eof; 
	_test_eof68: cs = 68; goto _test_eof; 
	_test_eof69: cs = 69; goto _test_eof; 
	_test_eof70: cs = 70; goto _test_eof; 
	_test_eof71: cs = 71; goto _test_eof; 
	_test_eof72: cs = 72; goto _test_eof; 
	_test_eof73: cs = 73; goto _test_eof; 
	_test_eof74: cs = 74; goto _test_eof; 
	_test_eof75: cs = 75; goto _test_eof; 
	_test_eof76: cs = 76; goto _test_eof; 
	_test_eof77: cs = 77; goto _test_eof; 
	_test_eof78: cs = 78; goto _test_eof; 
	_test_eof79: cs = 79; goto _test_eof; 
	_test_eof80: cs = 80; goto _test_eof; 
	_test_eof81: cs = 81; goto _test_eof; 
	_test_eof82: cs = 82; goto _test_eof; 
	_test_eof83: cs = 83; goto _test_eof; 
	_test_eof84: cs = 84; goto _test_eof; 
	_test_eof85: cs = 85; goto _test_eof; 
	_test_eof86: cs = 86; goto _test_eof; 
	_test_eof87: cs = 87; goto _test_eof; 
	_test_eof88: cs = 88; goto _test_eof; 
	_test_eof89: cs = 89; goto _test_eof; 
	_test_eof90: cs = 90; goto _test_eof; 
	_test_eof91: cs = 91; goto _test_eof; 
	_test_eof92: cs = 92; goto _test_eof; 
	_test_eof93: cs = 93; goto _test_eof; 
	_test_eof94: cs = 94; goto _test_eof; 
	_test_eof95: cs = 95; goto _test_eof; 
	_test_eof96: cs = 96; goto _test_eof; 
	_test_eof97: cs = 97; goto _test_eof; 
	_test_eof98: cs = 98; goto _test_eof; 
	_test_eof99: cs = 99; goto _test_eof; 
	_test_eof100: cs = 100; goto _test_eof; 
	_test_eof127: cs = 127; goto _test_eof; 
	_test_eof101: cs = 101; goto _test_eof; 
	_test_eof102: cs = 102; goto _test_eof; 
	_test_eof103: cs = 103; goto _test_eof; 
	_test_eof104: cs = 104; goto _test_eof; 
	_test_eof105: cs = 105; goto _test_eof; 
	_test_eof106: cs = 106; goto _test_eof; 
	_test_eof107: cs = 107; goto _test_eof; 
	_test_eof108: cs = 108; goto _test_eof; 
	_test_eof109: cs = 109; goto _test_eof; 
	_test_eof110: cs = 110; goto _test_eof; 
	_test_eof111: cs = 111; goto _test_eof; 
	_test_eof112: cs = 112; goto _test_eof; 
	_test_eof113: cs = 113; goto _test_eof; 
	_test_eof114: cs = 114; goto _test_eof; 
	_test_eof115: cs = 115; goto _test_eof; 
	_test_eof116: cs = 116; goto _test_eof; 
	_test_eof117: cs = 117; goto _test_eof; 
	_test_eof118: cs = 118; goto _test_eof; 
	_test_eof119: cs = 119; goto _test_eof; 
	_test_eof120: cs = 120; goto _test_eof; 
	_test_eof121: cs = 121; goto _test_eof; 
	_test_eof122: cs = 122; goto _test_eof; 
	_test_eof123: cs = 123; goto _test_eof; 
	_test_eof124: cs = 124; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 126: goto tr150;
	case 42: goto tr48;
	case 43: goto tr48;
	case 44: goto tr48;
	case 45: goto tr48;
	case 46: goto tr48;
	case 47: goto tr48;
	case 48: goto tr48;
	case 49: goto tr48;
	case 50: goto tr48;
	case 51: goto tr48;
	case 127: goto tr153;
	case 101: goto tr114;
	case 102: goto tr114;
	case 103: goto tr114;
	case 104: goto tr114;
	case 105: goto tr114;
	case 106: goto tr114;
	case 107: goto tr114;
	case 108: goto tr114;
	case 109: goto tr114;
	case 110: goto tr114;
	}
	}

	_out: {}
	}

#line 101 "src/casper/jrxml/node_element_factory.rl"


    OSAL_UNUSED_PARAM(element_factory_error);
    OSAL_UNUSED_PARAM(element_factory_en_main);
    OSAL_UNUSED_PARAM(element_factory_first_final);
    OSAL_UNUSED_PARAM(act);
    OSAL_UNUSED_PARAM(ts);
    OSAL_UNUSED_PARAM(te);

    return node;
}
