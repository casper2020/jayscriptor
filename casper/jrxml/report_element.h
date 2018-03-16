/**
 * @file report_element.h declaration of ReportElement model node
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
#ifndef NRS_CASPER_CASPER_JRXML_REPORT_ELEMENT_H
#define NRS_CASPER_CASPER_JRXML_REPORT_ELEMENT_H

#include "json/json.h"
#include "casper/jrxml/node.h"
#include "casper/jrxml/pos_attr.h"
#include "casper/jrxml/dim_attr.h"
#include "casper/jrxml/color_attr.h"
#include "casper/jrxml/position_type_attr.h"
#include "casper/jrxml/stretch_type_attr.h"
#include "casper/jrxml/mode_attr.h"
#include "casper/jrxml/string_attr.h"

#include <map>

namespace casper
{
    namespace jrxml
    {
        class PrintWhenExpression;
        class Property;
        class PropertyExpression;

        /**
         * @brief Element used to specify the common properties of an object on the report
         */
        class ReportElement  : public Node
        {
        protected: // Attributes

            PositionTypeAttr  position_type_;   //!< Specifies the object position when the report section is affected by stretch
            StretchTypeAttr   stretch_type_;    //!< Specifies the graphic element stretch behavior when the report section is affected by
            ModeAttr          mode_;            //!< Specifies whether the background of an object is transparent or opaque
            PosAttr           x_;               //!< Specifies the x coordinate for the object within the band, normalized to pixels
            PosAttr           y_;               //!< Specifies the y coordinate for the object within the band, normalized to pixels
            DimAttr           width_;           //!< Width of the object normalized to pixels
            DimAttr           height_;          //!< Height of the object normalized to pixels
            ColorAttr         forecolor_;       //!< Fore color to use when drawing the object
            ColorAttr         backcolor_;       //!< Back color to use when drawing the object
            StringAttr        style_;           //!< Name of the report level style to use as base style

        protected: // Child Elements

            PrintWhenExpression*                       print_when_expression_; //!< Optional
            std::map<std::string, Property*          > properties_;            //!< Optional
            std::map<std::string, PropertyExpression*> property_expressions_;  //!< Optional
            Json::Value                                casper_binding_;        //!< Binding specified via JSON object

        public: // Methods

            ReportElement (Node* a_parent);
            virtual ~ReportElement ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;

            static ReportElement* CreateFromXml (pugi::xml_node a_node, Node* a_parent) ;

        public: // Attribute accessors

            const PositionTypeAttr& PositionType     () const { return position_type_;  }
            const StretchTypeAttr&  StretchType      () const { return stretch_type_;   }
            const ModeAttr&         Mode             () const { return mode_;           }
            const PosAttr&          X                () const { return x_;              }
            const PosAttr&          Y                () const { return y_;              }
            const DimAttr&          Width            () const { return width_;          }
            const DimAttr&          Height           () const { return height_;         }
            const ColorAttr&        Forecolor        () const { return forecolor_;      }
            const ColorAttr&        Backcolor        () const { return backcolor_;      }
            const StringAttr&       StyleName        () const { return style_;          }
            const Json::Value&      GetCasperBinding () const { return casper_binding_; }

        public: // Element accessors

            PrintWhenExpression& GetPrintWhenExpression () const { return *print_when_expression_;    }

            bool HasPrintWhenExpression () const { return print_when_expression_ != NULL; }
            
            const Property*           GetProperty           (const std::string& a_name) const;
            const PropertyExpression* GetPropertyExpression (const std::string& a_name) const;

        protected: // Methods
            
            void ParseJsonBinding ();
        };
        
        inline const Property* ReportElement::GetProperty (const std::string& a_name) const
        {
            if ( 0 == properties_.size() ) {
                return nullptr;
            }
            auto it = properties_.find(a_name);
            if ( properties_.end() != it ) {
                return it->second;
            }
            return nullptr;
        }
        
        inline const PropertyExpression* ReportElement::GetPropertyExpression (const std::string& a_name) const
        {
            if ( 0 == property_expressions_.size() ) {
                return nullptr;
            }
            auto it = property_expressions_.find(a_name);
            if ( property_expressions_.end() != it ) {
                return it->second;
            }
            return nullptr;
        }


    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_REPORT_ELEMENT_H
