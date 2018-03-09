/**
 * @file property.h declaration of Property model node
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
#ifndef NRS_CASPER_CASPER_MODEL_PROPERTY_H
#define NRS_CASPER_CASPER_MODEL_PROPERTY_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/string_attr.h"
#include "casper/jrxml/reset_type_attr.h"
#include "casper/jrxml/calculation_attr.h"
#include "pugixml.hpp"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Represents the definition of a report property.
         */
        class Property  : public Node
        {
        public: // Attributes
            
            StringAttr      name_;        //!< Required
            StringAttr      value_;       //!< Optional
            
        public: // Methods
            
                     Property (Node* a_parent);
                     Property (Node* a_parent, const char* a_name, const char* a_value);
            virtual ~Property ();
            
            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;
            
            static Property* CreateFromXml (pugi::xml_node a_node, Node* a_parent);
            
        public: // Attribute accessors
            
            const StringAttr&      Name        () const { return name_;        }
            const StringAttr&      Value       () const { return value_;       }           
        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_MODEL_PROPERTY_H
