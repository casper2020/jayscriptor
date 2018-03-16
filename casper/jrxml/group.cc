/**
 * @file group.cc Implementation of Group jrxml node
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

#include "casper/jrxml/group.h"
#include "casper/jrxml/group_header.h"
#include "casper/jrxml/group_footer.h"
#include "casper/jrxml/value_expression.h"
#include "osal/osalite.h"

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
casper::jrxml::Group::Group (Node* a_parent) : Node(a_parent)
{
    node_type_ = EGroup;
    
    /* by default all attributes are unset */
    
    /*
     * Init pointers to child elements
     */
    group_expression_ = nullptr;
    group_header_     = nullptr;
    group_footer_     = nullptr;
}

/**
 * @brief Destructor
 */
casper::jrxml::Group::~Group ()
{
    group_expression_ = nullptr;
    group_header_     = nullptr;
    group_footer_     = nullptr;
}

/**
 * @brief Parse XML DOM to the memory jrxml
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true for success, false if an error is detected
 */
bool casper::jrxml::Group::ParseXml (pugi::xml_node a_xml_node)
{
    // ... Parse attributes ...
    name_.FromStr(a_xml_node.attribute("name").value());
    keep_together_.FromStr(a_xml_node.attribute("keepTogether").value());
    is_start_new_page_.FromStr(a_xml_node.attribute("isStartNewPage").value());
    is_reprint_header_on_each_page_.FromStr(a_xml_node.attribute("isReprintHeaderOnEachPage").value());

    // ... Parse child elements ...
    group_expression_ = GroupExpression::CreateFromXml(a_xml_node.child("groupExpression"), this);
    group_header_     = GroupHeader::CreateFromXml(a_xml_node.child("groupHeader"), this);
    group_footer_     = GroupFooter::CreateFromXml(a_xml_node.child("groupFooter"), this);
    return true;
}

/**
 * @brief Factory method to create a Group from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the jrxml
 * @return NULL if the element is not present in the DOM node
 */
casper::jrxml::Group* casper::jrxml::Group::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( nullptr != a_xml_node ) {
        casper::jrxml::Group* node = new casper::jrxml::Group(a_parent);
        if ( nullptr != node ) {
            if ( node->ParseXml(a_xml_node) == false ) {
                delete node;
            } else {
                return node;
            }
        } else {
            throw OSAL_EXCEPTION_NA("out of memory");
        }
    }
    return nullptr;
}

/**
 * @brief Print node information for debug
 *
 * @param a_stream the output handle
 * @param a_depth tree depth for indentation
 */
void casper::jrxml::Group::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] Group", a_depth * 2, a_depth * 2, " ", child_index_);
    
    if ( name_.IsSet() ) {
        fprintf(a_stream, " name='%s'", (const char*) name_);
    }
    if ( keep_together_.IsSet() ) {
        fprintf(a_stream, " isUsingCache=%s", KeepTogether() ? "true" : "false");
    }
    if ( is_start_new_page_.IsSet() ) {
        fprintf(a_stream, " isStartNewPage=%s", IsStartNewPage() ? "true" : "false");
    }
    if ( is_reprint_header_on_each_page_.IsSet() ) {
        fprintf(a_stream, " isReprintHeaderOnEachPage=%s", IsReprintHeaderOnEachPage() ? "true" : "false");
    }
    fprintf(a_stream, "\n");
}
