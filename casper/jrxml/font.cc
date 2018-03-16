/**
 * @file font.cc Implementation of Font model node
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

#include "casper/jrxml/font.h"
#include "osal/osalite.h"

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
casper::jrxml::Font::Font (Node* a_parent) : Node(a_parent)
{
    node_type_ = EFont;
    
    /* By default all attributes will be unset */
}

/**
 * @brief Destructor
 */
casper::jrxml::Font::~Font ()
{
    /* empty */
}

/**
 * @brief Parse XML DOM to the memory model
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true for success, false if an error is detected
 */
bool casper::jrxml::Font::ParseXml (pugi::xml_node a_xml_node)
{
    /*
     * Parse attributes
     */
    font_name_.FromStr(a_xml_node.attribute("fontName").value());
    size_.FromStr(a_xml_node.attribute("size").value());
    is_bold_.FromStr(a_xml_node.attribute("isBold").value());
    is_italic_.FromStr(a_xml_node.attribute("isItalic").value());
    is_underline_.FromStr(a_xml_node.attribute("isUnderline").value());
    is_strike_through_.FromStr(a_xml_node.attribute("isStrikeThrough").value());
    return true;
}

/**
 * @brief Factory method to create a Font from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return NULL if the element is not present in the DOM node
 */
casper::jrxml::Font* casper::jrxml::Font::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( a_xml_node != NULL ) {
        casper::jrxml::Font* node = new casper::jrxml::Font(a_parent);
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
void casper::jrxml::Font::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] Font", a_depth * 2, a_depth * 2, " ", child_index_);
    if ( font_name_.IsSet() ) {
        fprintf(a_stream, " fontName='%s'", FontName().c_str());
    }
    if ( size_.IsSet() ) {
        fprintf(a_stream, " size=%g", (float) Size());
    }
    if ( is_bold_.IsSet() ) {
        fprintf(a_stream, " isBold=%s", IsBold() ? "true" : "false");
    }
    if ( is_italic_.IsSet() ) {
        fprintf(a_stream, " isItalic=%s", IsItalic() ? "true" : "false");
    }
    if ( is_underline_.IsSet() ) {
        fprintf(a_stream, " isUnderline=%s", IsUnderLine() ? "true" : "false");
    }
    if ( is_strike_through_.IsSet() ) {
        fprintf(a_stream, " isStrikeThrough=%s", IsStrikeThrough() ? "true" : "false");
    }
    fprintf(a_stream, "\n");
}
