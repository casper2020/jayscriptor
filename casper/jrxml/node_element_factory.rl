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

    %%{
        machine element_factory;

        main := |*
            'band'         => { node = Band::CreateFromXml(a_xml_node, a_parent);         };
            'box'          => { node = Box::CreateFromXml(a_xml_node, a_parent);          };
            'break'        => { node = Break::CreateFromXml(a_xml_node, a_parent);        };
            'elementGroup' => { node = ElementGroup::CreateFromXml(a_xml_node, a_parent); };
            'group'        => { node = Group::CreateFromXml(a_xml_node, a_parent);        };
            'groupHeader'  => { node = GroupHeader::CreateFromXml(a_xml_node, a_parent);  };
            'groupFooter'  => { node = GroupFooter::CreateFromXml(a_xml_node, a_parent);  };
            'title'        => { node = Title::CreateFromXml(a_xml_node, a_parent);        };
            'ellipse'      => { node = Ellipse::CreateFromXml(a_xml_node, a_parent);      };
            'field'        => { node = Field::CreateFromXml(a_xml_node, a_parent);        };
            'font'         => { node = Font::CreateFromXml(a_xml_node, a_parent);         };
            'frame'        => { node = Frame::CreateFromXml(a_xml_node, a_parent);        };
            'image'        => { node = Image::CreateFromXml(a_xml_node, a_parent);        };
            'line'         => { node = Line::CreateFromXml(a_xml_node, a_parent);         };
            'pen'          => { node = Pen::CreateFromXml(a_xml_node, a_parent);          };
            'topPen'       => { node = Pen::CreateFromXml(a_xml_node, a_parent);          };
            'leftPen'      => { node = Pen::CreateFromXml(a_xml_node, a_parent);          };
            'rightPen'     => { node = Pen::CreateFromXml(a_xml_node, a_parent);          };
            'bottomPen'    => { node = Pen::CreateFromXml(a_xml_node, a_parent);          };
            'rectangle'    => { node = Rectangle::CreateFromXml(a_xml_node, a_parent);    };
            'parameter'    => { node = Parameter::CreateFromXml(a_xml_node, a_parent);    };
            'staticText'   => { node = StaticText::CreateFromXml(a_xml_node, a_parent);   };
            'style'        => { node = Style::CreateFromXml(a_xml_node, a_parent);        };
            'textField'    => { node = TextField::CreateFromXml(a_xml_node, a_parent);    };
            'text'         => { node = Text::CreateFromXml(a_xml_node, a_parent);         };
            'textElement'  => { node = TextElement::CreateFromXml(a_xml_node, a_parent);  };
            'textField'    => { node = TextField::CreateFromXml(a_xml_node, a_parent);    };
            'variable'     => { node = Variable::CreateFromXml(a_xml_node, a_parent);     };
        *|;

        write data;
        write init;
        write exec;
    }%%

    OSAL_UNUSED_PARAM(element_factory_error);
    OSAL_UNUSED_PARAM(element_factory_en_main);
    OSAL_UNUSED_PARAM(element_factory_first_final);
    OSAL_UNUSED_PARAM(act);
    OSAL_UNUSED_PARAM(ts);
    OSAL_UNUSED_PARAM(te);

    return node;
}
