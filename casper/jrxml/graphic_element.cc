/**
 * @file graphic_element.cc Implementation of GraphicElement model node
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

#include "casper/jrxml/graphic_element.h"
#include "casper/jrxml/pen.h"
#include "osal/osalite.h"

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
casper::jrxml::GraphicElement::GraphicElement (Node* a_parent) : Node(a_parent)
{
    /* by default all attributes are unset */
}

/**
 * @brief Destructor
 */
casper::jrxml::GraphicElement::~GraphicElement ()
{
    /* empty */
}

/**
 * @brief Parse XML DOM to the memory model
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true for success, false if an error is detected
 */
bool casper::jrxml::GraphicElement::ParseXml (pugi::xml_node a_xml_node)
{
    node_type_ = EGraphicElement;
    
    /*
     * Parse attributes
     */
    stretch_type_.FromStr(a_xml_node.attribute("stretchType").value());

    /*
     * Parse child elements
     */
    pen_ = Pen::CreateFromXml(a_xml_node.child("pen"), this);
    return true;
}

/**
 * @brief Factory method to create a GraphicElement from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return NULL if the element is not present in the DOM node
 */
casper::jrxml::GraphicElement* casper::jrxml::GraphicElement::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( a_xml_node != NULL ) {
        casper::jrxml::GraphicElement* node = new casper::jrxml::GraphicElement(a_parent);
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
void casper::jrxml::GraphicElement::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] GraphicElement", a_depth * 2, a_depth * 2, " ", child_index_);
    if ( stretch_type_.IsSet() ) {
        fprintf(a_stream, " stretchType='%s'", (const char*) stretch_type_);
    }
    fprintf(a_stream, "\n");

}
