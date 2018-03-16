/**
 * @file text.h declaration of Text model node
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
#ifndef NRS_CASPER_CASPER_JRXML_TEXT_H
#define NRS_CASPER_CASPER_JRXML_TEXT_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/string_attr.h"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Specifies the text to print for a static text object.
         */
        class Text  : public Node
        {
        public: // Attributes

            StringAttr text_;  //!< The text to print

        public: // Methods

            Text (Node* a_parent);
            virtual ~Text ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;

            static Text* CreateFromXml (pugi::xml_node a_node, Node* a_parent) ;

            operator const char* () const
            {
                return text_;
            }
            
            const char* c_str () const
            {
                return (const char*) text_;
            }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_TEXT_H
