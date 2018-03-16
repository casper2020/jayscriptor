/**
 * @file page_footer.h JRXML Container for PageFooter sub-bands.
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
#ifndef NRS_CASPER_CASPER_JRXML_PAGE_FOOTER_H
#define NRS_CASPER_CASPER_JRXML_PAGE_FOOTER_H

#include "casper/jrxml/node.h"
#include "pugixml.hpp"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Container for PageFooter sub-bands
         */
        class PageFooter : public Node
        {
        public: // Methods

                     PageFooter (Node* a_parent);
            virtual ~PageFooter ();

            virtual bool       ParseXml      (pugi::xml_node a_xml_node);
            virtual void       PrintNodeInfo (FILE* a_stream, int a_depth) const;

            static PageFooter* CreateFromXml (pugi::xml_node a_node, Node* a_parent);

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_PAGE_FOOTER_H