/**
 * @file graphic_element.h declaration of GraphicElement model node
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
#ifndef NRS_CASPER_CASPER_JRXML_GRAPHIC_ELEMENT_H
#define NRS_CASPER_CASPER_JRXML_GRAPHIC_ELEMENT_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/stretch_type_attr.h"

namespace casper
{
    namespace jrxml
    {
        class Pen;

        /**
         * @brief Element used to specify the common properties of a graphic object on the report (line, rectangle, ellipse or image)
         */
        class GraphicElement  : public Node
        {
        protected: // Attributes

            StretchTypeAttr stretch_type_; //!< The element will be printed when the specified group changes.

        protected: // Elements

            Pen* pen_;   //!< Properties of the pen used to draw lines or borders.

        public: // Methods

            GraphicElement (Node* a_parent);
            virtual ~GraphicElement ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;

            static GraphicElement* CreateFromXml (pugi::xml_node a_node, Node* a_parent) ;

        public: // Attribute accessors

            const StretchTypeAttr& StretchType () const { return stretch_type_; }

        public: // Element accessors

            Pen& GetPen () const { return *pen_; }

            bool HasPen () const { return pen_ != NULL; }
        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_GRAPHIC_ELEMENT_H
