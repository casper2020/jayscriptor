/**
 * @file jasper_report.h declaration of JasperReport model node
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
#ifndef NRS_CASPER_CASPER_JRXML_JASPER_REPORT_H
#define NRS_CASPER_CASPER_JRXML_JASPER_REPORT_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/orientation_attr.h"
#include "casper/jrxml/string_attr.h"
#include "casper/jrxml/int_attr.h"
#include "casper/jrxml/dim_attr.h"
#include "casper/jrxml/bool_attr.h"
#include "casper/cacheable_object.h"
#include <stdlib.h>

#include <set>
#include <map>
#include <vector>
#include <string>

namespace casper
{
    namespace jrxml
    {
        class Background;
        class Title;
        class PageHeader;
        class ColumnHeader;
        class Detail;
        class ColumnFooter;
        class PageFooter;
        class LastPageFooter;
        class Summary;
        class NoData;
        class Variable;
        class Style;
        class Group;
        class Property;

        typedef std::map<std::string, Style*>    StyleIndex;
        typedef std::set<Variable*>              VariableSet;
        typedef std::vector<Group*>              GroupList;
        typedef std::map<std::string, Property*> PropertiesArray;

        /**
         * @brief JRXML model node for @TODO description
         */
        class JasperReport : public Node, public casper::CacheableObject
        {
            
        public: // Enum(s)
            
            enum WhenNoDataType
            {
                Null,
                NoPages,
                NoDataSection,
                BlankPage,
                AllSectionsNoDetail
            };
            
        protected: // Data

            StyleIndex       style_index_;            //!< Map of the report styles
            VariableSet      report_variables_;       //!< The report variables
            GroupList        groups_;
            WhenNoDataType   when_no_data_type_;
            
        protected: // Attributes

            StringAttr       name_;                   //!< Name of the report
            StringAttr       language_;               //!< Specifies the language used for the report expressions
            IntAttr          column_count_;           //!< Number of cols, currently only one is supported
            DimAttr          page_width_;             //!< Page width normalized to pixels
            DimAttr          page_height_;            //!< Page height normalized to pixels
            OrientationAttr  orientation_;            //!< Page printing orientation
            DimAttr          column_width_;           //!< Column width normalized to pixels
            DimAttr          column_spacing_;         //!< Space between columns normalized to pixels
            DimAttr          left_margin_;            //!< Left margin normalized to pixels
            DimAttr          right_margin_;           //!< Right margin normalized to pixels
            DimAttr          top_margin_;             //!< Top margin normalized to pixels
            DimAttr          bottom_margin_;          //!< Bottom margin normalized to pixels
            BoolAttr         is_title_new_page_;      //!< Flag used to specify if the title section should be printed on a separate initial page
            BoolAttr         is_float_column_footer_; //!< Place column footer bellow the last detail band
            BoolAttr         is_ignore_pagination_;   //!< When true a single "infinite" page will be used
            
        protected: // Child Elements

            Background*      background_;
            Title*           title_;
            PageHeader*      page_header_;
            ColumnHeader*    column_header_;
            Detail*          detail_;
            ColumnFooter*    column_footer_;
            PageFooter*      page_footer_;
            LastPageFooter*  last_page_footer_;
            Summary*         summary_;
            NoData*          no_data_;
            PropertiesArray  properties_;

        protected: // Methods

            void Init  ();

        public: // Methods

                    JasperReport       (Node* a_parent);
            virtual ~JasperReport      ();
            
                    void   Clear            ();
            virtual bool   ParseXml         (pugi::xml_node a_xml_node);
            virtual void   PrintNodeInfo    (FILE* a_stream, int a_depth) const;
            const  Style&  GetStyleByName   (const char* a_style_name) const;
            
            static JasperReport* CreateFromXml (pugi::xml_node a_node, Node* a_parent) ;
            
            const Property* GetProperty (const std::string& a_name) const;


        public: // Attribute accessors

            const StringAttr&      Name                () const { return name_;                   }
            const StringAttr&      Language            () const { return language_;               }
            const IntAttr&         ColumnCount         () const { return column_count_;           }
            const DimAttr&         PageWidth           () const { return page_width_;             }
            const DimAttr&         PageHeight          () const { return page_height_;            }
            const OrientationAttr& Orientation         () const { return orientation_;            }
            const DimAttr&         ColumnWidth         () const { return column_width_;           }
            const DimAttr&         ColumnSpacing       () const { return column_spacing_;         }
            const DimAttr&         LeftMargin          () const { return left_margin_;            }
            const DimAttr&         RightMargin         () const { return right_margin_;           }
            const DimAttr&         TopMargin           () const { return top_margin_;             }
            const DimAttr&         BottomMargin        () const { return bottom_margin_;          }
            const BoolAttr&        IsTitleNewPage      () const { return is_title_new_page_;      }
            const BoolAttr&        IsFloatColumnFooter () const { return is_float_column_footer_; }
            const BoolAttr&        IsIgnorePagination  () const { return is_ignore_pagination_;   }
            const VariableSet&     Variables           () const { return report_variables_;       }
            const GroupList&       Groups              () const { return groups_;                 }
            
        public: // Element accessors

            const Background*      GetBackground       () const { return background_;        }
            const Title*           GetTitle            () const { return title_;             }
            const PageHeader*      GetPageHeader       () const { return page_header_;       }
            const ColumnHeader*    GetColumnHeader     () const { return column_header_;     }
            const Detail*          GetDetail           () const { return detail_;            }
            const ColumnFooter*    GetColumnFooter     () const { return column_footer_;     }
            const PageFooter*      GetPageFooter       () const { return page_footer_;       }
            const LastPageFooter*  GetLastPageFooter   () const { return last_page_footer_;  }
            const Summary*         GetSummary          () const { return summary_;           }
            const WhenNoDataType   GetWhenNoDataType   () const { return when_no_data_type_; }
            const NoData*          GetNoData           () const { return no_data_;           }

            bool HasBackground     () const { return background_       != NULL; }
            bool HasTitle          () const { return title_            != NULL; }
            bool HasPageHeader     () const { return page_header_      != NULL; }
            bool HasColumnHeader   () const { return column_header_    != NULL; }
            bool HasDetail         () const { return detail_           != NULL; }
            bool HasPageFooter     () const { return page_footer_      != NULL; }
            bool HasColumnFooter   () const { return column_footer_    != NULL; }
            bool HasLastPageFooter () const { return last_page_footer_ != NULL; }
            bool HasSummary        () const { return summary_          != NULL; }
            bool HasNoData         () const { return no_data_          != NULL; }

        };
        
        inline const Property* JasperReport::GetProperty (const std::string& a_name) const
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

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_JASPER_REPORT_H
