/**
 * @file field.cc Implementation of Field model node
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

#include "casper/jrxml/field.h"
#include "casper/jrxml/property.h"
#include "osal/osalite.h"

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
casper::jrxml::Field::Field (Node* a_parent) : Node(a_parent)
{
    node_type_ = EField;
    
    /* By default all attributes are unset */
}

/**
 * @brief Destructor
 */
casper::jrxml::Field::~Field ()
{
    /* empty */
    properties_.clear();
}

/**
 * @brief Parse XML DOM to the memory model
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true for success, false if an error is detected
 */
bool casper::jrxml::Field::ParseXml (pugi::xml_node a_xml_node)
{
    /*
     * Parse attributes
     */
    name_.FromStr(a_xml_node.attribute("name").value());
    class_.FromStr(a_xml_node.attribute("class").value());
    
    /*
     * Parse child elements
     */
    for (pugi::xml_node xml_node = a_xml_node.first_child(); xml_node; xml_node = xml_node.next_sibling()) {
        if ( strcmp(xml_node.name(), "property") == 0 ) {
            Property* property = Property::CreateFromXml(xml_node, this);
            if ( NULL != property ) {
                properties_[property->Name().Value()] = property;
            }
        }
    }
    
    return true;
}

/**
 * @brief Factory method to create a Field from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return NULL if the element is not present in the DOM node
 */
casper::jrxml::Field* casper::jrxml::Field::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( a_xml_node != NULL ) {
        casper::jrxml::Field* node = new casper::jrxml::Field(a_parent);
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
void casper::jrxml::Field::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] Field", a_depth * 2, a_depth * 2, " ", child_index_);
    if ( name_.IsSet() ) {
        fprintf(a_stream, " name='%s'", (const char*) name_);
    }
    if ( class_.IsSet() ) {
        fprintf(a_stream, " class='%s'", (const char*) class_);
    }
    fprintf(a_stream, "\n");
}
