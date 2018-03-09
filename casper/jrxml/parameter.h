/**
 * @file parameter.h declaration of Parameter model node
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
#ifndef NRS_CASPER_CASPER_JRXML_PARAMETER_H
#define NRS_CASPER_CASPER_JRXML_PARAMETER_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/string_attr.h"
#include "pugixml.hpp"

namespace casper
{
    namespace jrxml
    {
        class DefaultValueExpression;

        /**
         * @brief Represents the definition of a report parameter.
         *
         * Parameters are very useful for passing data to the report engine ed in the
         * expressions or in the query string of the report.
         */
        class Parameter  : public Node
        {
        public: // Attributes

            StringAttr name_;   //!< Parameter name
            StringAttr class_;  //!< Parameter class or object type

        protected: // Child Elements

            DefaultValueExpression* default_value_expression_;

        public: // Methods

            Parameter (Node* a_parent);
            virtual ~Parameter ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;

            static Parameter* CreateFromXml (pugi::xml_node a_node, Node* a_parent);

        public: // Attribute accessors

            const char* Name  () const { return name_;  }
            const char* Class () const { return class_; }

        public: // Element accessors

            DefaultValueExpression& GetDefaultValueExpression () const { return *default_value_expression_; }

            bool HasDefaultValueExpression () const { return default_value_expression_ != NULL; }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_PARAMETER_H
