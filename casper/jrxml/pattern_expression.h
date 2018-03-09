/**
 * @file pattern_expression.h declaration of PatternExpression model node
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
#ifndef NRS_CASPER_CASPER_JRXML_PATTERN_EXPRESSION_H
#define NRS_CASPER_CASPER_JRXML_PATTERN_EXPRESSION_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/string_attr.h"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Defines the pattern expression to use for this textField
         */
        class PatternExpression  : public Node
        {
        protected: // Attributes

            StringAttr expression_;

        public: // Methods

            PatternExpression (Node* a_parent);
            virtual ~PatternExpression ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;

            static PatternExpression* CreateFromXml (pugi::xml_node a_node, Node* a_parent) ;
            
        public: // Attribute accessors
            
            const char*        c_str    () const { return expression_.c_str(); }
            const std::string& ToString () const { return expression_.Value(); }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_PATTERN_EXPRESSION_H

