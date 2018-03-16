/**
 * @file default_value_expression.h declaration of DefaultValueExpression model node
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
#pragma once
#ifndef NRS_CASPER_CASPER_JRXML_DEFAULT_VALUE_EXPRESSION_H
#define NRS_CASPER_CASPER_JRXML_DEFAULT_VALUE_EXPRESSION_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/string_attr.h"
#include "pugixml.hpp"

namespace casper
{
    namespace jrxml
    {
        class ValueExpression  : public Node
        {
        protected: // Attributes

            const char* expression_type_;
            StringAttr  expression_;

        public: // Methods

            ValueExpression (Node* a_parent);
            virtual ~ValueExpression ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;
            
        public: // Attribute accessors
            
            const char*        c_str    () const { return expression_.c_str(); }
            const std::string& ToString () const { return expression_.Value(); }

        };

        /**
         * @brief Specifies the parameter default value to use when not supplied by the parent application at runtime
         */
        class DefaultValueExpression : public ValueExpression
        {
            DefaultValueExpression (Node* a_parent) : ValueExpression(a_parent)
            {
                node_type_       = EDefaultValueExpression;
                expression_type_ = "DefaultValueExpression";
            }
            
        public: // methods
            
            static DefaultValueExpression* CreateFromXml (pugi::xml_node a_node, Node* a_parent);
        };

        /**
         * @brief Definition of the expression that will be used to calculate the initial value of the variable,
         *        before any calculations are made.
         */
        class InitialValueExpression : public ValueExpression
        {
            InitialValueExpression (Node* a_parent) : ValueExpression(a_parent)
            {
                node_type_       = EInitialValueExpression;
                expression_type_ = "InitialValueExpression";
            }
         
        public: // methods
            
            static InitialValueExpression* CreateFromXml (pugi::xml_node a_node, Node* a_parent);
        };

        /**
         * @brief Definition of the expression associated with the variable.
         *
         * The value of this expression will be calculated at runtime and will represent the value of the corresponding 
         * variable or it will be used in calculation to obtain the value of the calculated variable.
         */
        class VariableExpression : public ValueExpression
        {
            VariableExpression (Node* a_parent) : ValueExpression(a_parent)
            {
                node_type_       = EVariableExpression;
                expression_type_ = "VariableExpression";
            }
            
        public: // methods
            
            static VariableExpression* CreateFromXml (pugi::xml_node a_node, Node* a_parent);
        };

        /**
         * @brief Definition of the expression associated with an image.
         *
         * The value of this expression will be calculated at runtime and will contain the URL of the image.
         */
        class ImageExpression : public ValueExpression
        {
            ImageExpression (Node* a_parent) : ValueExpression(a_parent)
            {
                node_type_       = EImageExpression;
                expression_type_ = "ImageExpression";
            }
            
        public: // methods
            
            static ImageExpression* CreateFromXml (pugi::xml_node a_node, Node* a_parent);
        };
        
        /**
         * @brief Specifies the expression that will be evaluated at runtime to determine the group ruptures.
         */
        class GroupExpression : public ValueExpression
        {
            GroupExpression (Node* a_parent) : ValueExpression(a_parent)
            {
                node_type_       = EGroupExpression;
                expression_type_ = "GroupExpression";
            }

        public: // methods
            
            static GroupExpression* CreateFromXml (pugi::xml_node a_node, Node* a_parent);

        };
        

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_DEFAULT_VALUE_EXPRESSION_H
