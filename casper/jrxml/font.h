/**
 * @file font.h declaration of Font model node
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
#ifndef NRS_CASPER_CASPER_JRXML_FONT_H
#define NRS_CASPER_CASPER_JRXML_FONT_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/string_attr.h"
#include "casper/jrxml/bool_attr.h"
#include "casper/jrxml/dim_attr.h"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Defines the font to use with the text element
         */
        class Font  : public Node
        {
        private: // Attributes

            StringAttr font_name_;         //!< Name of the font
            DimAttr    size_;              //!< Size normalized to pixels
            BoolAttr   is_bold_;           //!< True to "boldrize" the letters
            BoolAttr   is_italic_;         //!< True to "italianize" the letters
            BoolAttr   is_underline_;      //!< True to enable underline
            BoolAttr   is_strike_through_; //!< True to enable strike out

        public: // Methods

            Font (Node* a_parent);
            virtual ~Font ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;

        public: // Static methods

            static Font* CreateFromXml (pugi::xml_node a_node, Node* a_parent) ;

        public: // Attribute accessors

            const StringAttr& FontName        () const { return font_name_;         }
            const DimAttr&    Size            () const { return size_;              }
            const BoolAttr&   IsBold          () const { return is_bold_;           }
            const BoolAttr&   IsItalic        () const { return is_italic_;         }
            const BoolAttr&   IsUnderLine     () const { return is_underline_;      }
            const BoolAttr&   IsStrikeThrough () const { return is_strike_through_; }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_FONT_H


