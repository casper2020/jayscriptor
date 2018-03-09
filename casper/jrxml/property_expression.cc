/**
 * @file property_expression.h Implementation of PrintWhenExpression model node
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

#include "casper/jrxml/property_expression.h"
#include "osal/osalite.h"

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
casper::jrxml::PropertyExpression::PropertyExpression (Node* a_parent) : Node(a_parent)
{
    node_type_ = EPropertyExpression;
}

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 *
 * @param a_parent Parent node in the XML tree
 * @param a_name property name
 * @param a_expression property value
 */
casper::jrxml::PropertyExpression::PropertyExpression (Node* a_parent, const char* a_name, const char* a_expression) : Node(a_parent)
{
    node_type_ = EProperty;
    name_.FromStr(a_name);
    expression_.FromStr(a_expression);
}

/**
 * @brief Destructor
 */
casper::jrxml::PropertyExpression::~PropertyExpression ()
{
    /* empty */
}

/**
 * @brief Parse XML DOM to the memory model
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true for success, false if an error is detected
 */
bool casper::jrxml::PropertyExpression::ParseXml (pugi::xml_node a_xml_node)
{
    expression_.Set(a_xml_node.child_value()); // @TODO check if this the PCDATA

    name_.FromStr(a_xml_node.attribute("name").value());
    
    return true;
}

/**
 * @brief Factory method to create a PrintWhenExpression from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return NULL if the element is not present in the DOM node
 */
casper::jrxml::PropertyExpression* casper::jrxml::PropertyExpression::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( a_xml_node != NULL ) {
        casper::jrxml::PropertyExpression* node = new casper::jrxml::PropertyExpression(a_parent);
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
void casper::jrxml::PropertyExpression::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] PropertyExpression '%s'\n", a_depth * 2, a_depth * 2, " ", child_index_, (const char*) expression_);
}

