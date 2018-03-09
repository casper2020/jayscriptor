/**
 * @file variable.cc Implementation of Variable model node
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

#include "casper/jrxml/variable.h"
#include "casper/jrxml/value_expression.h"
#include "osal/osalite.h"

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
casper::jrxml::Variable::Variable (Node* a_parent) : Node(a_parent)
{
    node_type_                = EVariable;
    calc_phase_               = CalculationPhase::ENormalCalculation;
    initial_value_expression_ = nullptr;
    variable_expression_      = nullptr;
    calculation_.Set(jrxml::CalculationAttr::ENothing);
}

/**
 * @brief Destructor
 */
casper::jrxml::Variable::~Variable ()
{
    initial_value_expression_ = nullptr;
    variable_expression_      = nullptr;
}

/**
 * @brief Parse XML DOM to the memory model
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true for success, false if an error is detected
 */
bool casper::jrxml::Variable::ParseXml (pugi::xml_node a_xml_node)
{
    /*
     * Parse attributes
     */
    name_.FromStr(a_xml_node.attribute("name").value());
    class_.FromStr(a_xml_node.attribute("class").value());
    reset_type_.FromStr(a_xml_node.attribute("resetType").value());
    reset_group_.FromStr(a_xml_node.attribute("resetGroup").value());
    calculation_.FromStr(a_xml_node.attribute("calculation").value());
    incrementer_factory_.FromStr(a_xml_node.attribute("incrementerFactoryClass").value());
    
    if ( strcmp(incrementer_factory_.c_str(), "PreCalculate") == 0 ) {
        calc_phase_ = CalculationPhase::EPreCalculation;
    }
    /*
     * Parse child elements
     */
    initial_value_expression_ = InitialValueExpression::CreateFromXml(a_xml_node.child("initialValueExpression"), this);
    variable_expression_      = VariableExpression::CreateFromXml(a_xml_node.child("variableExpression"), this);
    return true;
}

/**
 * @brief Factory method to create a Variable from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return NULL if the element is not present in the DOM node
 */
casper::jrxml::Variable* casper::jrxml::Variable::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( a_xml_node != NULL ) {
        casper::jrxml::Variable* node = new casper::jrxml::Variable(a_parent);
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
void casper::jrxml::Variable::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] Variable", a_depth * 2, a_depth * 2, " ", child_index_);
    if ( name_.IsSet() ) {
        fprintf(a_stream, " name='%s'", (const char*) name_);
    }
    if ( class_.IsSet() ) {
        fprintf(a_stream, " class='%s'", (const char*) class_);
    }
    if ( reset_type_.IsSet() ) {
        fprintf(a_stream, " resetType='%s'", (const char*) reset_type_);
    }
    if ( reset_group_.IsSet() ) {
        fprintf(a_stream, " resetGroup='%s'", (const char*) reset_group_);
    }
    if ( calculation_.IsSet() ) {
        fprintf(a_stream, " calculation='%s'", (const char*) calculation_);
    }
    if ( incrementer_factory_.IsSet() ) {
        fprintf(a_stream, " incrementerFactoryClass='%s'", (const char*) incrementer_factory_);
    }
    fprintf(a_stream, "\n");
}
