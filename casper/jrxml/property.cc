/**
 * @file property.cc Implementation of Property model node
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

#include "casper/jrxml/property.h"
#include "casper/jrxml/value_expression.h"
#include "osal/osalite.h"

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
casper::jrxml::Property::Property (Node* a_parent) : Node(a_parent)
{
    node_type_ = EProperty;
}

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 *
 * @param a_parent Parent node in the XML tree
 * @param a_name property name
 * @param a_value property value
 */
casper::jrxml::Property::Property (Node* a_parent, const char* a_name, const char* a_value) : Node(a_parent)
{
    node_type_ = EProperty;
    name_.FromStr(a_name);
    value_.FromStr(a_value);
}

/**
 * @brief Destructor
 */
casper::jrxml::Property::~Property ()
{
    /* empty */
}

/**
 * @brief Parse XML DOM to the memory model
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true for success, false if an error is detected
 */
bool casper::jrxml::Property::ParseXml (pugi::xml_node a_xml_node)
{
    /*
     * Parse attributes
     */
    name_.FromStr(a_xml_node.attribute("name").value());
    value_.FromStr(a_xml_node.attribute("value").value());
    
    return true;
}

/**
 * @brief Factory method to create a Variable from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return NULL if the element is not present in the DOM node
 */
casper::jrxml::Property* casper::jrxml::Property::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( a_xml_node != NULL ) {
        casper::jrxml::Property* node = new casper::jrxml::Property(a_parent);
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
void casper::jrxml::Property::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] Property", a_depth * 2, a_depth * 2, " ", child_index_);
    if ( name_.IsSet() ) {
        fprintf(a_stream, " name='%s'", (const char*) name_);
    }
    if ( value_.IsSet() ) {
        fprintf(a_stream, " value='%s'", (const char*) value_);
    }
    fprintf(a_stream, "\n");
}
