/**
 * @file group.h Definition of a group on the report.
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
#ifndef NRS_CASPER_CASPER_JRXML_GROUP_H
#define NRS_CASPER_CASPER_JRXML_GROUP_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/string_attr.h"
#include "casper/jrxml/bool_attr.h"
#include "pugixml.hpp"

namespace casper
{
    namespace jrxml
    {
        class GroupExpression;
        class GroupHeader;
        class GroupFooter;

        /**
         * @brief Definition of a group on the report.
         *
         *
         */
        class Group  : public Node
        {
        protected: // Attributes

            StringAttr  name_;                           //!< Name of the group
            BoolAttr    keep_together_;                  //!< Flag that prevents the group from splitting on two separate pages/columns, but only on the first break
            BoolAttr    is_start_new_page_;              //!< Flag that signals if the group header should be printed always on a new page
            BoolAttr    is_reprint_header_on_each_page_; //!< Flag that signals if the group header should be reprinted at the beginning of each page
            
        protected: // Elements

            GroupExpression* group_expression_;  //!< Specifies the expression that will be evaluated at runtime to determine the group ruptures.
            GroupHeader*     group_header_;      //!< List of bands used at the start of each group value
            GroupFooter*     group_footer_;      //!< List of bands used at the end of each group values

        protected: // Child Elements

        public: // Methods

            Group (Node* a_parent);
            virtual ~Group ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;

            static Group* CreateFromXml (pugi::xml_node a_node, Node* a_parent);

        public: // Attribute accessors

            const StringAttr& Name                      () const { return name_;                           }
            const BoolAttr&   KeepTogether              () const { return keep_together_;                  }
            const BoolAttr&   IsStartNewPage            () const { return is_start_new_page_;              }
            const BoolAttr&   IsReprintHeaderOnEachPage () const { return is_reprint_header_on_each_page_; }

        public: // Element accessors

            class GroupExpression& GetGroupExpression () const { return *group_expression_; }
            class GroupHeader&     GetGroupHeader     () const { return *group_header_;     }
            class GroupFooter&     GetGroupFooter     () const { return *group_footer_;     }

            bool HasGroupExpression () const { return group_expression_!= nullptr; }
            bool HasGroupHeader     () const { return group_header_    != nullptr; }
            bool HasGroupFooter     () const { return group_footer_    != nullptr; }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_GROUP_H
