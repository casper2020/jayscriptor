/**
 * @file text_element.h declaration of TextElement model node
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
#ifndef NRS_CASPER_CASPER_JRXML_TEXT_ELEMENT_H
#define NRS_CASPER_CASPER_JRXML_TEXT_ELEMENT_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/text_alignment_attr.h"
#include "casper/jrxml/vertical_alignment_attr.h"
#include "casper/jrxml/rotation_attr.h"
#include "casper/jrxml/line_spacing_attr.h"

namespace casper
{
    namespace jrxml
    {
        class Font;
        class Paragraph;

        /**
         * @brief Element used to specify the common properties of a text object on the report staticText or textField
         */
        class TextElement  : public Node
        {
        public: // Attributes

            TextAlignmentAttr     text_alignment_;     //!< Type of alignment for the text object
            VerticalAlignmentAttr vertical_alignment_; //!< Type of vertical alignment for the text object
            RotationAttr          rotation_;           //!< Type of rotation for the text object
            LineSpacingAttr       line_spacing_;       //!< Type of line spacing for the text object

        protected: // Child Elements

            Font*      font_;      //!< Optional
            Paragraph* paragraph_; //!< Optional

        public: // Methods

            TextElement (Node* a_parent);
            virtual ~TextElement ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;

            static TextElement* CreateFromXml (pugi::xml_node a_node, Node* a_parent) ;

        public: // Attribute accessors

            const TextAlignmentAttr&     TextAlignment     () const { return text_alignment_;     }
            const VerticalAlignmentAttr& VerticalAlignment () const { return vertical_alignment_; }
            const RotationAttr&          Rotation          () const { return rotation_;           }
            const LineSpacingAttr&       LineSpacing       () const { return line_spacing_;       }

        public: // Element accessors

            Font&      GetFont      () const { return *font_;      }
            Paragraph& GetParagraph () const { return *paragraph_; }

            bool HasFont      () const { return font_      != NULL; }
            bool HasParagraph () const { return paragraph_ != NULL; }
        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_TEXT_ELEMENT_H
