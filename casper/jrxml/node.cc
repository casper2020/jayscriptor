/**
 * @file Node.cc Implementation of Node base class
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
#include "osal/osalite.h"

casper::jrxml::Node::Node (Node* a_parent)
{
    node_type_ = ENode;
    parent_    = a_parent;
    
    if ( NULL != a_parent ) {
        child_index_ = (int) a_parent->children_.size();
        a_parent->children_.push_back(this);
    } else {
        child_index_ = -1;
    }
}

/**
 * @brief Dummy virtual base class Destructor
 */
casper::jrxml::Node::~Node ()
{
    for ( NodeList::iterator it = children_.begin(); it != children_.end(); ++it ) {
        delete *it;
    }
}

casper::jrxml::JasperReport* casper::jrxml::Node::Report () const
{
    const Node* p;
    
    p = this;
    while (p != nullptr) {
        if ( EJasperReport == p->NodeType() ) {
            return (JasperReport*) p;
        }
        p = p->Parent();
    }
    throw OSAL_EXCEPTION_NA("Malformed report! one of the nodes does not belong to a report");
}

/**
 * @brief Dummy virtual base method
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true
 */
bool casper::jrxml::Node::ParseXml (pugi::xml_node a_xml_node)
{
    for (pugi::xml_node xml_node = a_xml_node.first_child(); xml_node; xml_node = xml_node.next_sibling()) {
        ElementFactory(xml_node.name(), xml_node, this);
    }
    return true;
}

void casper::jrxml::Node::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] Node\n", a_depth * 2, a_depth * 2, " ", child_index_);
}

void casper::jrxml::Node::PrintTreeInfo (FILE* a_stream, int a_depth)
{
    PrintNodeInfo(a_stream, a_depth);
    for ( size_t i = 0; i < children_.size(); ++i ) {
        children_[i]->PrintTreeInfo(a_stream, a_depth + 1);
    }
}

