/**
 * @file line.h declaration of Line model node
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
#ifndef NRS_CASPER_CASPER_JRXML_LINE_H
#define NRS_CASPER_CASPER_JRXML_LINE_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/direction_attr.h"

namespace casper
{
    namespace jrxml
    {
        class ReportElement;
        class GraphicElement;

        /**
         * @brief Definition of a line object.
         */
        class Line  : public Node
        {
        public: // Attributes

            DirectionAttr   direction_;       //!< Diagonal direction

        protected: // Child Elements

            ReportElement*  report_element_;  //!< Mandatory
            GraphicElement* graphic_element_; //!< Optional

        public: // Methods

            Line (Node* a_parent);
            virtual ~Line ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;

            static Line* CreateFromXml (pugi::xml_node a_node, Node* a_parent) ;

        public: // Attribute accessors

            int Direction () const { return direction_; }

        public: // Element accessors

            ReportElement&  GetReportElement  () const { return *report_element_;  }
            GraphicElement& GetGraphicElement () const { return *graphic_element_; }

            bool HasReportElement  () const { return  report_element_ != NULL; }
            bool HasGraphicElement () const { return  graphic_element_ != NULL; }
        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_LINE_H
