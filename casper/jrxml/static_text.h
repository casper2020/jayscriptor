/**
 * @file static_text.h declaration of StaticText model node
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
#ifndef NRS_CASPER_CASPER_JRXML_STATIC_TEXT_H
#define NRS_CASPER_CASPER_JRXML_STATIC_TEXT_H

#include "casper/jrxml/node.h"

namespace casper
{
    namespace jrxml
    {
        class ReportElement;
        class Box;
        class TextElement;
        class Text;

        /**
         * @brief JRXML model node for @TODO description
         */
        class StaticText  : public Node
        {
        protected: // Child Elements

            ReportElement* report_element_;  //!< Mandatory
            Box*           box_;             //!< Optional
            TextElement*   text_element_;    //!< Optional
            Text*          text_;            //!< Optional

        public: // Methods

            StaticText (Node* a_parent);
            virtual ~StaticText ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;

            static StaticText* CreateFromXml (pugi::xml_node a_node, Node* a_parent) ;

        public: // Element accessors

            ReportElement& GetReportElement () const { return *report_element_; }
            Box&           GetBox           () const { return *box_;            }
            TextElement&   GetTextElement   () const { return *text_element_;   }
            Text&          GetText          () const { return *text_;           }

            bool HasBox         () const { return box_          != NULL; }
            bool HasTextElement () const { return text_element_ != NULL; }
            bool HasText        () const { return text_         != NULL; }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_STATIC_TEXT_H
