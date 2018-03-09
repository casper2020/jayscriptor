/**
 * @file box.cc Implementation of Box model node
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

#include "casper/jrxml/box.h"
#include "casper/jrxml/pen.h"
#include "osal/osalite.h"

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
casper::jrxml::Box::Box (Node* a_parent) : Node(a_parent)
{
    node_type_ = EBox;
    
    /* By default all attributes will be unset */

    /*
     * Init pointers to child elements
     */
    pen_        = NULL;
    top_pen_    = NULL;
    left_pen_   = NULL;
    bottom_pen_ = NULL;
    right_pen_  = NULL;
}

/**
 * @brief Destructor
 */
casper::jrxml::Box::~Box ()
{
    /*
     * delete contained objects
     */
    pen_        = NULL;
    top_pen_    = NULL;
    left_pen_   = NULL;
    bottom_pen_ = NULL;
    right_pen_  = NULL;
}

/**
 * @brief Parse XML DOM to the memory model
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true for success, false if an error is detected
 */
bool casper::jrxml::Box::ParseXml (pugi::xml_node a_xml_node)
{
    /*
     * Parse attributes
     */
    padding_.FromStr(a_xml_node.attribute("padding").value());
    top_padding_.FromStr(a_xml_node.attribute("topPadding").value());
    left_padding_.FromStr(a_xml_node.attribute("leftPadding").value());
    bottom_padding_.FromStr(a_xml_node.attribute("bottomPadding").value());
    right_padding_.FromStr(a_xml_node.attribute("rightPadding").value());

    /*
     * Parse child elements
     */
    pen_        = Pen::CreateFromXml(a_xml_node.child("pen"), this);
    top_pen_    = Pen::CreateFromXml(a_xml_node.child("topPen"), this);
    left_pen_   = Pen::CreateFromXml(a_xml_node.child("leftPen"), this);
    bottom_pen_ = Pen::CreateFromXml(a_xml_node.child("bottomPen"), this);
    right_pen_  = Pen::CreateFromXml(a_xml_node.child("rightPen"), this);
    return true;
}

/**
 * @brief Factory method to create a Box from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return NULL if the element is not present in the DOM node
 */
casper::jrxml::Box* casper::jrxml::Box::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( a_xml_node != NULL ) {
        casper::jrxml::Box* node = new casper::jrxml::Box(a_parent);
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
void casper::jrxml::Box::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] Box", a_depth * 2, a_depth * 2, " ", child_index_);
    if ( padding_.IsSet() ) {
        fprintf(a_stream, " padding=%.2f", (float) padding_);
    }
    if ( top_padding_.IsSet() ) {
        fprintf(a_stream, " topPadding=%.2f", (float) top_padding_);
    }
    if ( left_padding_.IsSet() ) {
        fprintf(a_stream, " leftPadding=%.2f", (float) left_padding_);
    }
    if ( bottom_padding_.IsSet() ) {
        fprintf(a_stream, " bottomPadding=%.2f", (float) bottom_padding_);
    }
    if ( right_padding_.IsSet() ) {
        fprintf(a_stream, " rightPadding=%.2f", (float) right_padding_);
    }
    fprintf(a_stream, "\n");
}
