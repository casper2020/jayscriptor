/**
 * @file band.h declaration of Band model node
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
#ifndef NRS_CASPER_CASPER_JRXML_band_H
#define NRS_CASPER_CASPER_JRXML_band_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/dim_attr.h"
#include "casper/jrxml/split_type_attr.h"
#include "pugixml.hpp"

#include <map>

namespace casper
{
    namespace jrxml
    {
        class PrintWhenExpression;
        class Property;

        /**
         * @brief Generic definition of a report section.
         */
        class Band : public Node
        {
        protected: // Attributes

            const char*   band_type_;  //!< Type of band as string, used for debug onlyb
            DimAttr       height_;     //!< Height of the band. normalized to pixels
            SplitTypeAttr split_type_; //!< Specifies the band split behavior.

        protected: // Child Elements

            PrintWhenExpression*             print_when_expression_; //!< Optional
            std::map<std::string, Property*> properties_;            //!< Optional

        public: // Methods

            Band (Node* a_parent);
            virtual ~Band ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;

            static Band* CreateFromXml (pugi::xml_node a_node, Node* a_parent) ;

        public: // Attribute accessors
            
            const DimAttr&       Height    () const { return height_;     }
            const SplitTypeAttr& SplitType () const { return split_type_; }

        public: // Element accessors

            PrintWhenExpression& GetPrintWhenExpression () const { return *print_when_expression_;  }
            
            bool HasPrintWhenExpression () const { return print_when_expression_ != NULL; }
            
            const char* BandType () const { return band_type_; }
            
            const Property* GetProperty (const std::string& a_name) const;
            
        };
        
        inline const Property* Band::GetProperty (const std::string& a_name) const
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

        /**
         * @brief Definition of the page background section for this report.
         *
         * The background section is displayed on every page and cannot overflow to the next page.
         * Elements placed on this section are evaluated at page initialization time and are displayed in the back.
         * All other page elements are displayed on top of the background elements.
         * This section allows creating watermark or other similar effects in documents.
         */
        class BackgroundBand : public Band
        {
        public: // methods

            BackgroundBand (Node* a_parent) : Band(a_parent)
            {
                band_type_ = "BG";
                node_type_ = EBackgroundBand;
            }

            static BackgroundBand* CreateFromXml (pugi::xml_node a_node, Node* a_parent);
        };

        /**
         * @brief Definition of the title section for this report.
         *
         * The title section appears only once at the beginning of the report.
         */
        class TitleBand : public Band
        {
        public: // methods

            TitleBand (Node* a_parent) : Band(a_parent)
            {
                band_type_ = "TL";
                node_type_ = ETitleBand;
            }

            static TitleBand* CreateFromXml (pugi::xml_node a_node, Node* a_parent);
        };

        /**
         * @brief Definition of the page header section for this report.
         *
         * The page header is printed at the beginning of each page on the report
         */
        class PageHeaderBand : public Band
        {
        public: // methods

            PageHeaderBand (Node* a_parent) : Band(a_parent)
            {
                band_type_ = "PH";
                node_type_ = EPageHeaderBand;
            }

            static PageHeaderBand* CreateFromXml (pugi::xml_node a_node, Node* a_parent);

        };

        /**
         * @brief Definition of the column header section for this report. 
         *
         * The column header is printed at the beginning of each column on the report. If the report's column count 
         * is 1, column  header and footer sections are ignored.
         */
        class ColumnHeaderBand : public Band
        {
        public: // methods
            
            ColumnHeaderBand (Node* a_parent) : Band(a_parent)
            {
                band_type_ = "CH";
                node_type_ = EColumnHeaderBand;
            }
            
            static ColumnHeaderBand* CreateFromXml (pugi::xml_node a_node, Node* a_parent);
        };

        /**
         * @brief Definition of the column footer section for this report. 
         *
         * The column footer is printed at the bottom of each column on the r1.0rt. If the report's 
         * column count is 1, column header   and footer sections are ignored.
         */
        class ColumnFooterBand : public Band
        {
        public: // methods
            
            ColumnFooterBand (Node* a_parent) : Band(a_parent)
            {
                band_type_ = "CF";
                node_type_ = EColumnFooterBand;
            }
            
            static ColumnFooterBand* CreateFromXml (pugi::xml_node a_node, Node* a_parent);
        };
        
        /**
         * @brief Definition of the page footer section for this report.
         *
         * The page footer is printed at the bottom of each page on the report
         */
        class PageFooterBand : public Band
        {
        public: // methods

            PageFooterBand (Node* a_parent) : Band(a_parent)
            {
                band_type_ = "PF";
                node_type_ = EPageFooterBand;
            }

            static PageFooterBand* CreateFromXml (pugi::xml_node a_node, Node* a_parent);
        };

        /**
         * @brief The page footer section to use on the last page instead of the normal page footer.
         *
         * This might not be the very last page of the document in case the summary section is also present.
         * This section is sometimes useful when summary information has to be displayed at the bottom of the last page.
         */
        class LastPageFooterBand : public Band
        {
        public: // method

            LastPageFooterBand (Node* a_parent) : Band(a_parent)
            {
                band_type_ = "LPF";
                node_type_ = ELastPageFooterBand;
            }
            static LastPageFooterBand* CreateFromXml (pugi::xml_node a_node, Node* a_parent);
        };

        /**
         * @brief Definition of the summary section for this report.
         *
         * The summary section is printed only once at the end of the report.
         */
        class SummaryBand : public Band
        {
        public: // method
            
            SummaryBand (Node* a_parent) : Band(a_parent)
            {
                band_type_ = "SU";
                node_type_ = ESummaryBand;
            }
            static SummaryBand* CreateFromXml (pugi::xml_node a_node, Node* a_parent);
        };

        /**
         * @brief Definition of the noData section for this report.
         *
         * The noData section is printed only if whenNoDataType attribute is set to "NoDataSection".
         */
        class NoDataBand : public Band
        {
        public: // method
            
            NoDataBand (Node* a_parent) : Band(a_parent)
            {
                band_type_ = "ND";
                node_type_ = ENoDataBand;
            }
            static NoDataBand* CreateFromXml (pugi::xml_node a_node, Node* a_parent);
        };
        
        /**
         * @brief Definition of a group header band
         */
        class GroupHeaderBand : public Band
        {
        public: // method
            
            GroupHeaderBand (Node* a_parent) : Band(a_parent)
            {
                band_type_ = "GH";
                node_type_ = EGroupHeaderBand;
            }
            static GroupHeaderBand* CreateFromXml (pugi::xml_node a_node, Node* a_parent);
        };

        /**
         * @brief Definition of a group footer band
         */
        class GroupFooterBand : public Band
        {
        public: // method
            
            GroupFooterBand (Node* a_parent) : Band(a_parent)
            {
                band_type_ = "GF";
                node_type_ = EGroupFooterBand;
            }
            
            static GroupFooterBand* CreateFromXml (pugi::xml_node a_node, Node* a_parent);
        };


    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_band_H
