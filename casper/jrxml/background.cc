/**
 * @file back_ground.cc JRXML Container for Background sub-bands.
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

#include "casper/jrxml/background.h"
#include "casper/jrxml/band.h"
#include "osal/osalite.h"

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
casper::jrxml::Background::Background (Node* a_parent) : Node(a_parent)
{
    node_type_ = EBackground;

    /* by default all attributes are unset */
}

/**
 * @brief Destructor
 */
casper::jrxml::Background::~Background ()
{
    /* empty */
}

/**
 * @brief Parse XML DOM to the memory jrxml
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true for success, false if an error is detected
 */
bool casper::jrxml::Background::ParseXml (pugi::xml_node a_xml_node)
{
    for (pugi::xml_node child = a_xml_node.first_child(); child; child = child.next_sibling()) {

        if ( strcmp(child.name(), "band") ) {
            throw OSAL_EXCEPTION("Background element children must be a Band, %s is not allowed", child.name());
        }
        BackgroundBand::CreateFromXml(child, this);
    }
    return true;
}

/**
 * @brief Factory method to create a Background from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the jrxml
 * @return NULL if the element is not present in the DOM node
 */
casper::jrxml::Background* casper::jrxml::Background::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( a_xml_node != NULL ) {
        casper::jrxml::Background* node = new casper::jrxml::Background(a_parent);
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
void casper::jrxml::Background::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] Background\n", a_depth * 2, a_depth * 2, " ", child_index_);
}
