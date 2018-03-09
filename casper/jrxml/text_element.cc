/**
 * @file text_element.cc Implementation of TextElement model node
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

#include "casper/jrxml/text_element.h"
#include "casper/jrxml/font.h"
#include "casper/jrxml/paragraph.h"
#include "osal/osalite.h"

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
casper::jrxml::TextElement::TextElement (Node* a_parent) : Node(a_parent)
{
    node_type_ = ETextElement;
    
    /* by default all attributes are unset */
    
    /*
     * Init pointers to child elements
     */
    font_      = NULL;
    paragraph_ = NULL;
}

/**
 * @brief Destructor
 */
casper::jrxml::TextElement::~TextElement ()
{
    /*
     * child nodes will be deleted by base class constructor, just NULL the pointers
     */
    font_      = NULL;
    paragraph_ = NULL;
}

/**
 * @brief Parse XML DOM to the memory model
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true for success, false if an error is detected
 */
bool casper::jrxml::TextElement::ParseXml (pugi::xml_node a_xml_node)
{
    /*
     * Parse attributes
     */
    text_alignment_.FromStr(a_xml_node.attribute("textAlignment").value());
    vertical_alignment_.FromStr(a_xml_node.attribute("verticalAlignment").value());
    rotation_.FromStr(a_xml_node.attribute("rotation").value());
    line_spacing_.FromStr(a_xml_node.attribute("lineSpacing").value());

    /*
     * Parse child elements
     */
    font_      = Font::CreateFromXml(a_xml_node.child("font"), this);
    paragraph_ = Paragraph::CreateFromXml(a_xml_node.child("paragraph"), this);
    return true;
}

/**
 * @brief Factory method to create a TextElement from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return NULL if the element is not present in the DOM node
 */
casper::jrxml::TextElement* casper::jrxml::TextElement::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( a_xml_node != NULL ) {
        casper::jrxml::TextElement* node = new casper::jrxml::TextElement(a_parent);
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
void casper::jrxml::TextElement::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] TextElement", a_depth * 2, a_depth * 2, " ", child_index_);
    if ( text_alignment_.IsSet() ) {
        fprintf(a_stream, " textAlignment='%s'", (const char*) text_alignment_);
    }
    if ( vertical_alignment_.IsSet() ) {
        fprintf(a_stream, " verticalAlignment='%s'", (const char*) vertical_alignment_);
    }
    if ( rotation_.IsSet() ) {
        fprintf(a_stream, " rotation='%s'", (const char*) rotation_);
    }
    if ( line_spacing_.IsSet() ) {
        fprintf(a_stream, " lineSpacing='%s'", (const char*) line_spacing_);
    }
    fprintf(a_stream, "\n");
}
