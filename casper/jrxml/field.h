/**
 * @file field.h declaration of Field model node
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
#ifndef NRS_CASPER_CASPER_JRXML_FIELD_H
#define NRS_CASPER_CASPER_JRXML_FIELD_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/string_attr.h"
#include "pugixml.hpp"

#include <map>

namespace casper
{
    namespace jrxml
    {
        class Property;
        
        /**
         * @brief JRXML model node for @TODO description
         */
        class Field  : public Node
        {
        protected: // Attributes

            StringAttr name_;                             //!< Name of the field
            StringAttr class_;                            //!< Class of the field values.
            std::map<std::string, Property*> properties_; //!< Optional
            
        public: // Methods

            Field (Node* a_parent);
            virtual ~Field ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;

            static Field* CreateFromXml (pugi::xml_node a_node, Node* a_parent);

            /*
             * Attribute accessors
             */
            const StringAttr& Name  () const { return name_ ; }
            const StringAttr& Class () const { return class_; }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_FIELD_H
