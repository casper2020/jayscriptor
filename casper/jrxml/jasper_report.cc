/**
 * @file jasper_report.cc Implementation of JasperReport model node
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

#include "casper/jrxml/jasper_report.h"
#include "casper/jrxml/band.h"
#include "casper/jrxml/detail.h"
#include "casper/jrxml/group.h"
#include "casper/jrxml/style.h"
#include "casper/jrxml/property.h"
#include "casper/jrxml/background.h"
#include "casper/jrxml/title.h"
#include "casper/jrxml/page_header.h"
#include "casper/jrxml/column_header.h"
#include "casper/jrxml/summary.h"
#include "casper/jrxml/column_footer.h"
#include "casper/jrxml/page_footer.h"
#include "casper/jrxml/last_page_footer.h"
#include "casper/jrxml/no_data.h"
#include "osal/osalite.h"

#include <limits>

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
casper::jrxml::JasperReport::JasperReport (Node* a_parent) : Node(a_parent)
{
    node_type_ = EJasperReport;
    Init();
}

/**
 * @brief Deletes all contained children and resets object to defaults
 *
 * This is used to recycle the object
 */
void casper::jrxml::JasperReport::Clear ()
{
    for ( size_t i = 0; i < children_.size(); ++i ) {
        delete children_[i];
    }
    children_.clear();
    report_variables_.clear();
    style_index_.clear();
    groups_.clear();
    Init();
}

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
void casper::jrxml::JasperReport::Init ()
{
    /*
     * Attribute defaults
     */
    language_.Set("java");
    column_count_.Set(1);
    page_width_.Set(595);
    page_height_.Set(842);
    column_width_.Set(555);
    column_spacing_.Set(0);
    left_margin_.Set(20);
    right_margin_.Set(20);
    top_margin_.Set(30);
    bottom_margin_.Set(30);
    is_title_new_page_.Set(false);
    is_float_column_footer_.Set(false);
    is_ignore_pagination_.Set(false);

    /*
     * Init pointers to child elements
     */
    background_        = nullptr;
    title_             = nullptr;
    page_header_       = nullptr;
    column_header_     = nullptr;
    detail_            = nullptr;
    column_footer_     = nullptr;
    page_footer_       = nullptr;
    last_page_footer_  = nullptr;
    summary_           = nullptr;
    no_data_           = nullptr;
    when_no_data_type_ = jrxml::JasperReport::WhenNoDataType::Null;
}

/**
 * @brief Destructor
 */
casper::jrxml::JasperReport::~JasperReport ()
{
    /*
     * child nodes will be deleted by base class constructor, just nullptr the pointers
     */
    background_       = nullptr;
    title_            = nullptr;
    page_header_      = nullptr;
    column_header_    = nullptr;
    detail_           = nullptr;
    column_footer_    = nullptr;
    page_footer_      = nullptr;
    last_page_footer_ = nullptr;
    summary_          = nullptr;
    no_data_          = nullptr;
    properties_.clear();
}

/**
 * @brief Parse XML DOM to the memory model
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true for success, false if an error is detected
 */
bool casper::jrxml::JasperReport::ParseXml (pugi::xml_node a_xml_node)
{
    /*
     * Parse attributes
     */
    name_.FromStr(a_xml_node.attribute("name").value());
    language_.FromStr(a_xml_node.attribute("language").value());
    column_count_.FromStr(a_xml_node.attribute("columnCount").value());
    page_width_.FromStr(a_xml_node.attribute("pageWidth").value());
    page_height_.FromStr(a_xml_node.attribute("pageHeight").value());
    orientation_.FromStr(a_xml_node.attribute("orientation").value());
    column_width_.FromStr(a_xml_node.attribute("columnWidth").value());
    column_spacing_.FromStr(a_xml_node.attribute("columnSpacing").value());
    left_margin_.FromStr(a_xml_node.attribute("leftMargin").value());
    right_margin_.FromStr(a_xml_node.attribute("rightMargin").value());
    top_margin_.FromStr(a_xml_node.attribute("topMargin").value());
    bottom_margin_.FromStr(a_xml_node.attribute("bottomMargin").value());
    is_title_new_page_.FromStr(a_xml_node.attribute("isTitleNewPage").value());
    is_float_column_footer_.FromStr(a_xml_node.attribute("isFloatColumnFooter").value());
    is_ignore_pagination_.FromStr(a_xml_node.attribute("isIgnorePagination").value());
    
    /*
     * Parse child elements
     */
    for (pugi::xml_node child = a_xml_node.first_child(); child; child = child.next_sibling()) {
        Node* node;

        if ( strcmp(child.name(), "background") == 0 ) {
            background_ = Background::CreateFromXml(child, this);
        } else if ( strcmp(child.name(), "title") == 0 ) {
            title_ = Title::CreateFromXml(child, this);
        } else if ( strcmp(child.name(), "pageHeader") == 0 ) {
            page_header_ = PageHeader::CreateFromXml(child, this);
        } else if ( strcmp(child.name(), "columnHeader") == 0 ) {
            column_header_ = ColumnHeader::CreateFromXml(child, this);
        } else if ( strcmp(child.name(), "detail") == 0 ) {
            detail_ = Detail::CreateFromXml(child, this);
        } else if ( strcmp(child.name(), "columnFooter") == 0 ) {
            column_footer_ = ColumnFooter::CreateFromXml(child, this);
        } else if ( strcmp(child.name(), "pageFooter") == 0 ) {
            page_footer_ = PageFooter::CreateFromXml(child, this);
        } else if ( strcmp(child.name(), "lastPageFooter") == 0 ) {
            last_page_footer_ = LastPageFooter::CreateFromXml(child, this);
        } else if ( strcmp(child.name(), "summary") == 0 ) {
            summary_ = Summary::CreateFromXml(child, this);
        } else if ( strcmp(child.name(), "noData") == 0 ) {
            no_data_ = NoData::CreateFromXml(child, this);
        } else if ( strcmp(child.name(), "style") == 0 ) {
            node = ElementFactory(child.name(), child, this);
            style_index_[((Style*) node)->Name().c_str()] = (Style*) node;
        } else if ( strcmp(child.name(), "group") == 0 ) {
            node = Group::CreateFromXml(child, this);
            groups_.push_back((Group*) node);
        } else if ( strcmp(child.name(), "variable") == 0 ) {
            node = ElementFactory(child.name(), child, this);
            report_variables_.insert((Variable*) node);
        } else if ( strcmp(child.name(), "property") == 0 ) {
            Property* property = Property::CreateFromXml(child, this);
            if ( nullptr != property ) {
                properties_[property->Name().Value()] = property;
            }
        } else {
            node = ElementFactory(child.name(), child, this);
        }
    }
    
    for ( auto style: style_index_ ) {
        if ( style.second->ParentStyle()[0] ) {
            auto parent = style_index_.find(style.second->ParentStyle().c_str());
            if ( parent == style_index_.end() ){
                throw OSAL_EXCEPTION("Sytle '%s' requires parent sytle '%s' that does not exist!", style.second->Name().c_str(), style.second->ParentStyle().c_str());
            }
            style.second->SetParentStyle(parent->second);
        }
    }
    if ( is_ignore_pagination_ ) {
        page_height_.Set(std::numeric_limits<float>::max());
    }
    
    const pugi::xml_attribute no_data_attr = a_xml_node.attribute("whenNoDataType");
    if ( 0 == strcmp("BlankPage", no_data_attr.value()) ) {
        when_no_data_type_ = jrxml::JasperReport::WhenNoDataType::BlankPage;
    } else if ( 0 == strcmp("AllSectionsNoDetail", no_data_attr.value()) ) {
        when_no_data_type_ = jrxml::JasperReport::WhenNoDataType::AllSectionsNoDetail;
    } else if ( 0 == strcmp("NoDataSection", no_data_attr.value()) ) {
        when_no_data_type_ = jrxml::JasperReport::WhenNoDataType::NoDataSection;
    } // else { /* NULL or NoPages */ }
    
    return true;
}

/**
 * @brief Factory method to create a JasperReport from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return nullptr if the element is not present in the DOM node
 */
casper::jrxml::JasperReport* casper::jrxml::JasperReport::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( nullptr != a_xml_node ) {
        casper::jrxml::JasperReport* node = new casper::jrxml::JasperReport(a_parent);
        if ( nullptr != node ) {
            if ( node->ParseXml(a_xml_node) == false ) {
                delete node;
            } else {
                return node;
            }
        } else {
            throw OSAL_EXCEPTION_NA("out of memory");
        }
    }
    return nullptr;
}

/**
 * @brief Print node information for debug
 *
 * @param a_stream the output handle
 * @param a_depth tree depth for indentation
 */
void casper::jrxml::JasperReport::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] JasperReport name='%s'\n", a_depth * 2, a_depth * 2, " ", child_index_, (const char*) name_);
}

/**
 * @brief Retrive a sytle object by name
 *
 * @param a_style_name name of the style to retrieve, this is case sensitive
 *
 * @return the style object or blow the shop if it does not exist
 */
const casper::jrxml::Style& casper::jrxml::JasperReport::GetStyleByName (const char* a_style_name) const
{
    auto style_it = style_index_.find(a_style_name);
    if ( style_it == style_index_.end() ) {
        throw OSAL_EXCEPTION("style '%s' is not defined!", a_style_name);
    }
    return *(style_it->second);
}
