/**
 * @file pen.h declaration of Pen model node
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
#ifndef NRS_CASPER_CASPER_JRXML_PEN_H
#define NRS_CASPER_CASPER_JRXML_PEN_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/dim_attr.h"
#include "casper/jrxml/line_style_attr.h"
#include "casper/jrxml/color_attr.h"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Groups the properties of the pen used to draw lines or borders
         */
        class Pen  : public Node
        {
        protected: // Attributes

            DimAttr       line_width_;  //!< The line width of the pen
            LineStyleAttr line_style_;  //!< The line style of the pen
            ColorAttr     line_color_;  //!< Line color for the pen

        public: // Methods

            Pen (Node* a_parent);
            virtual ~Pen ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;

            static Pen* CreateFromXml (pugi::xml_node a_node, Node* a_parent) ;

        public: // Attribte accessors

            const DimAttr&       LineWidth () const { return line_width_; }
            const LineStyleAttr& LineStyle () const { return line_style_; }
            const ColorAttr&     LineColor () const { return line_color_; }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_PEN_H
