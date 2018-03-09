/**
 * @file image.cc Implementation of Image model node
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

#include "casper/jrxml/image.h"
#include "casper/jrxml/box.h"
#include "casper/jrxml/report_element.h"
#include "casper/jrxml/graphic_element.h"
#include "casper/jrxml/value_expression.h"
#include "osal/osalite.h"

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
casper::jrxml::Image::Image (Node* a_parent) : Node(a_parent)
{
    node_type_ = EImage;
    
    /* by default all attributes are unset */

    /*
     * Init pointers to child elements
     */
    report_element_   = NULL;
    box_              = NULL;
    graphic_element_  = NULL;
    image_expression_ = NULL;
}

/**
 * @brief Destructor
 */
casper::jrxml::Image::~Image ()
{
    /*
     * child nodes will be deleted by base class constructor, just NULL the pointers
     */
    report_element_   = NULL;
    box_              = NULL;
    graphic_element_  = NULL;
    image_expression_ = NULL;
}

/**
 * @brief Parse XML DOM to the memory model
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true for success, false if an error is detected
 */
bool casper::jrxml::Image::ParseXml (pugi::xml_node a_node)
{
    /*
     * Parse attributes
     */
    scale_image_.FromStr(a_node.attribute("scaleImage").value());
    h_align_.FromStr(a_node.attribute("hAlign").value());
    v_align_.FromStr(a_node.attribute("vAlign").value());
    is_using_cache_.FromStr(a_node.attribute("isUsingCache").value());

    /*
     * Parse child elements
     */
    box_              = Box::CreateFromXml(a_node.child("box"), this);
    report_element_   = ReportElement::CreateFromXml(a_node.child("reportElement"), this);
    graphic_element_  = GraphicElement::CreateFromXml(a_node.child("graphicElement"), this);
    image_expression_ = ImageExpression::CreateFromXml(a_node.child("imageExpression"), this);
    return true;
}

/**
 * @brief Factory method to create a Image from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return NULL if the element is not present in the DOM node
 */
casper::jrxml::Image* casper::jrxml::Image::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( a_xml_node != NULL ) {
        casper::jrxml::Image* node = new casper::jrxml::Image(a_parent);
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
void casper::jrxml::Image::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] Image", a_depth * 2, a_depth * 2, " ", child_index_);
    
    if ( scale_image_.IsSet() ) {
        fprintf(a_stream, " scaleImage='%s", (const char*) scale_image_);
    }
    if ( h_align_.IsSet() ) {
        fprintf(a_stream, " hAlign='%s", (const char*) h_align_);
    }
    if ( v_align_.IsSet() ) {
        fprintf(a_stream, " vAlign='%s", (const char*) v_align_);
    }
    if ( is_using_cache_.IsSet() ) {
        fprintf(a_stream, " isUsingCache=%s", IsUsingCache() ? "true" : "false");
    }
    fprintf(a_stream, "\n");
}
