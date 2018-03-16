/**
 * @file Style.cc Implementation of Style model node
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

#include "casper/jrxml/style.h"
#include "casper/jrxml/box.h"
#include "casper/jrxml/pen.h"
#include "casper/jrxml/paragraph.h"
#include "osal/osalite.h"

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
casper::jrxml::Style::Style (Node* a_parent) : Node(a_parent)
{
    parent_style_ = nullptr;
    node_type_    = EStyle;
    
    /* By default all attributes are unset */

    /*
     * Init pointers to child elements
     */
    pen_       = nullptr;
    box_       = nullptr;
    paragraph_ = nullptr;
}

/**
 * @brief Destructor
 */
casper::jrxml::Style::~Style ()
{
    /* empty */
}

/**
 * @brief Parse XML DOM to the memory model
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true for success, false if an error is detected
 */
bool casper::jrxml::Style::ParseXml (pugi::xml_node a_xml_node)
{
    /*
     * Parse attributes
     */
    mode_.FromStr(a_xml_node.attribute("mode").value());
    forecolor_.FromStr(a_xml_node.attribute("forecolor").value());
    backcolor_.FromStr(a_xml_node.attribute("backcolor").value());
    name_.FromStr(a_xml_node.attribute("name").value());
    is_default_.FromStr(a_xml_node.attribute("isDefault").value());
    style_.FromStr(a_xml_node.attribute("style").value());
    fill_.FromStr(a_xml_node.attribute("fill").value());
    h_align_.FromStr(a_xml_node.attribute("hTextAlign").value());
    v_align_.FromStr(a_xml_node.attribute("vTextAlign").value());
    scale_image_.FromStr(a_xml_node.attribute("scaleImage").value());
    rotation_.FromStr(a_xml_node.attribute("rotation").value());
    line_spacing_.FromStr(a_xml_node.attribute("lineSpacing").value());
    font_name_.FromStr(a_xml_node.attribute("fontName").value());
    font_size_.FromStr(a_xml_node.attribute("fontSize").value());
    is_bold_.FromStr(a_xml_node.attribute("isBold").value());
    is_italic_.FromStr(a_xml_node.attribute("isItalic").value());
    is_underline_.FromStr(a_xml_node.attribute("isUnderline").value());
    is_strike_trought_.FromStr(a_xml_node.attribute("isStrikeThrough").value());
    pattern_.FromStr(a_xml_node.attribute("pattern").value());
    is_blank_when_null_.FromStr(a_xml_node.attribute("isBlankWhenNull").value());

    /*
     * Parse child elements
     */
    box_       = Box::CreateFromXml(a_xml_node.child("box"), this);
    pen_       = Pen::CreateFromXml(a_xml_node.child("pen"), this);
    paragraph_ = Paragraph::CreateFromXml(a_xml_node.child("paragraph"), this);
    return true;
}

/**
 * @brief Factory method to create a Style from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return NULL if the element is not present in the DOM node
 */
casper::jrxml::Style* casper::jrxml::Style::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( a_xml_node != NULL ) {
        casper::jrxml::Style* node = new casper::jrxml::Style(a_parent);
        if ( NULL != node ) {
            if ( node->ParseXml(a_xml_node) == false ) {
                delete node;
            } else {
                return node;
            }
        } else {
            throw OSAL_EXCEPTION_NA("out of memory");
        }
    }
    return NULL;
}

/**
 * @brief Print node information for debug
 *
 * @param a_stream the output handle
 * @param a_depth tree depth for indentation
 */
void casper::jrxml::Style::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] Style '%s'",
            a_depth * 2, a_depth * 2, " ", child_index_, (const char*) name_);
    if ( style_.IsSet() ) {
        fprintf(a_stream, " < '%s'", (const char*) style_);
    }
    if ( font_name_.IsSet() ) {
        fprintf(a_stream, " fontName='%s'", (const char*) font_name_);
    }
    if ( is_bold_.IsSet() ) {
        fprintf(a_stream, " isBold=%s", IsBold() ? "true" : "false");
    }
    if ( is_italic_.IsSet() ) {
        fprintf(a_stream, " isItalic=%s", IsItalic() ? "true" : "false");
    }
    if ( is_default_.IsSet() ) {
        fprintf(a_stream, " isDefault=%s", IsDefault() ? "true" : "false");
    }
    if ( mode_.IsSet() ) {
        fprintf(a_stream, " mode='%s'", (const char*) mode_);
    }
    if ( fill_.IsSet() ) {
        fprintf(a_stream, " fill='%s'", (const char*) fill_);
    }
    if ( h_align_.IsSet() ) {
        fprintf(a_stream, " hTextAlign='%s'", (const char*) h_align_);
    }
    if ( v_align_.IsSet() ) {
        fprintf(a_stream, " vTextAlign='%s'", (const char*) v_align_);
    }
    if ( scale_image_.IsSet() ) {
        fprintf(a_stream, " scaleImage_='%s'", (const char*) scale_image_);
    }
    if ( rotation_.IsSet() ) {
        fprintf(a_stream, " rotation='%s'", (const char*) rotation_);
    }
    if ( line_spacing_.IsSet() ) {
        fprintf(a_stream, " lineSpacing='%s'", (const char*) line_spacing_);
    }
    if ( pattern_.IsSet() ) {
        fprintf(a_stream, " pattern='%s'", (const char*) pattern_);
    }
    if ( is_blank_when_null_.IsSet() ) {
        fprintf(a_stream, " isBlankWhenNull=%s", IsBlankWhenNull() ? "true" : "false");
    }
    fprintf(a_stream, "\n");
}
