/**
 * @file column_footer.h JRXML Container for ColumnFooter sub-bands.
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
#ifndef NRS_CASPER_CASPER_JRXML_COLUMN_FOOTER_H
#define NRS_CASPER_CASPER_JRXML_COLUMN_FOOTER_H

#include "casper/jrxml/node.h"
#include "pugixml.hpp"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Container for ColumnFooter sub-bands
         */
        class ColumnFooter : public Node
        {
        public: // Methods

                     ColumnFooter (Node* a_parent);
            virtual ~ColumnFooter ();

            virtual bool         ParseXml      (pugi::xml_node a_xml_node);
            virtual void         PrintNodeInfo (FILE* a_stream, int a_depth) const;

            static ColumnFooter* CreateFromXml (pugi::xml_node a_node, Node* a_parent);

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_COLUMN_FOOTER_H
