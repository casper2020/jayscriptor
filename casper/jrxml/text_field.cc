/**
 * @file text_field.cc Implementation of TextField model node
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

#include "casper/jrxml/text_field.h"
#include "casper/jrxml/report_element.h"
#include "casper/jrxml/box.h"
#include "casper/jrxml/text_element.h"
#include "casper/jrxml/text_field_expression.h"
#include "casper/jrxml/pattern_expression.h"
#include "casper/jrxml/print_when_expression.h"
#include "osal/osalite.h"


/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
casper::jrxml::TextField::TextField (Node* a_parent) : Node(a_parent)
{
    node_type_ = ETextField;

    /* by default all attributes are unset */
    
    /*
     * Init pointers to child elements
     */
    report_element_        = NULL;
    box_                   = NULL;
    text_element_          = NULL;
    text_field_expression_ = NULL;
    pattern_expression_    = NULL;
}

/**
 * @brief Destructor
 */
casper::jrxml::TextField::~TextField ()
{
    /*
     * child nodes will be deleted by base class constructor, just NULL the pointers
     */
    report_element_        = NULL;
    box_                   = NULL;
    text_element_          = NULL;
    text_field_expression_ = NULL;
    pattern_expression_    = NULL;
}

/**
 * @brief Parse XML DOM to the memory model
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true for success, false if an error is detected
 */
bool casper::jrxml::TextField::ParseXml (pugi::xml_node a_xml_node)
{
    /*
     * Parse attributes
     */
    is_stretch_with_overflow_.FromStr(a_xml_node.attribute("isStretchWithOverflow").value());
    evaluation_time_.FromStr(a_xml_node.attribute("evaluationTime").value());
    pattern_.FromStr(a_xml_node.attribute("pattern").value());
    is_blank_when_null_.FromStr(a_xml_node.attribute("isBlankWhenNull").value());

    /*
     * Parse child elements
     */
    report_element_        = ReportElement::CreateFromXml(a_xml_node.child("reportElement"), this);
    box_                   = Box::CreateFromXml(a_xml_node.child("box"), this);
    text_element_          = TextElement::CreateFromXml(a_xml_node.child("textElement"), this);
    text_field_expression_ = TextFieldExpression::CreateFromXml(a_xml_node.child("textFieldExpression"), this);
    pattern_expression_    = PatternExpression::CreateFromXml(a_xml_node.child("patternExpression"), this);
    return true;
}

/**
 * @brief Factory method to create a TextField from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return NULL if the element is not present in the DOM node
 */
casper::jrxml::TextField* casper::jrxml::TextField::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( a_xml_node != NULL ) {
        casper::jrxml::TextField* node = new casper::jrxml::TextField(a_parent);
        if ( NULL != node ) {
            if ( node->ParseXml(a_xml_node) == false ) {
                delete node;
            } else {
                return node;
            }
        } else {
            OSAL_EXCEPTION_NA("out-of-memory");
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
void casper::jrxml::TextField::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] TextField", a_depth * 2, a_depth * 2 , " ", child_index_);
    if ( is_stretch_with_overflow_.IsSet() ) {
        fprintf(a_stream, " isStretchWithOverflow=%s", IsStretchWithOverflow() ? "true" : "false");
    }
    if ( evaluation_time_.IsSet() ) {
        fprintf(a_stream, " evaluationTime='%s'", (const char*) evaluation_time_);
    }
    if ( pattern_.IsSet() ) {
        fprintf(a_stream, " pattern='%s'", (const char*) pattern_);
    }
    if ( is_blank_when_null_.IsSet() ) {
        fprintf(a_stream, " isBlankWhenNull=%s", IsBlankWhenNull() ? "true" : "false");
    }
    fprintf(a_stream, "\n");
}
