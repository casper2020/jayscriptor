/**
 * @file Node.h declaration of Node object
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
#ifndef NRS_CASPER_CASPER_JRXML_NODE_H
#define NRS_CASPER_CASPER_JRXML_NODE_H

#include "pugixml.hpp"

#include <vector>

namespace casper
{
    namespace jrxml
    {
        class Node;
        class Detail;
        class GroupHeader;
        class GroupFooter;
        class JasperReport;

        typedef std::vector<Node*> NodeList;

        /**
         * @brief Base class for all the JRXML model nodes
         */
        class Node
        {
            friend class Detail;
            friend class GroupHeader;
            friend class GroupFooter;
            
        public: // Datatypes

            enum NodeTypeEnum
            {
                ENone,
                ENode,
                EStaticText,
                ETextField,
                EImage,
                EEllipse,
                ERectangle,
                ELine,
                EField,
                EFrame,
                EStyle,
                EBox,
                EDefaultValueExpression,
                EInitialValueExpression,
                EVariableExpression,
                EImageExpression,
                EGroupExpression,
                EFont,
                EGraphicElement,
                EJasperReport,
                EParagraph,
                EParameter,
                EProperty,
                EPropertyExpression,
                EVariable,
                EPatternExpression,
                EPen,
                EPrintWhenExpression,
                EReportElement,
                EText,
                ETextElement,
                ETextFieldExpression,
                EElementGroup,
                EBand,
                EGroup,
                EGroupHeader,
                EGroupFooter,
                EBackground,
                ETitle,
                EPageHeader,
                EColumnHeader,
                EColumnFooter,
                EPageFooter,
                ELastPageFooter,
                ESummary,
                ENoData,
                EBackgroundBand,
                ETitleBand,
                EPageHeaderBand,
                EColumnHeaderBand,
                EDetailBand,
                EColumnFooterBand,
                EPageFooterBand,
                ELastPageFooterBand,
                ESummaryBand,
                ENoDataBand,
                EGroupHeaderBand,
                EGroupFooterBand,
                EBreak
            };

        protected: // Attributes

            Node*        parent_;       //!< The parent node of this node, NULL for root
            NodeList     children_;     //!< Array with the node's children
            int          child_index_;  //!< Index of child in the parent's children array
            NodeTypeEnum node_type_;    //!< Tag that identifies node type

        protected: // methods

            Node* ElementFactory (const char* a_element_name, pugi::xml_node a_xml_node, Node* a_node);
            bool  ParseElements  (pugi::xml_node a_xml_node);

        public: // Methods

            Node (Node* a_parent);

            const NodeList&     Children   () const;
                  Node*         Parent     () const;
                  JasperReport* Report     () const;
                  int           ChildIndex () const;
                  NodeTypeEnum  NodeType   () const;

            void  PrintTreeInfo (FILE* a_stream, int a_depth = 0);

            virtual ~Node ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;
        };

        inline const NodeList& Node::Children() const
        {
            return children_;
        }

        inline Node* Node::Parent () const
        {
            return parent_;
        }

        inline int Node::ChildIndex () const
        {
            return child_index_;
        }

        inline Node::NodeTypeEnum Node::NodeType () const
        {
            return node_type_;
        }

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_NODE_H
