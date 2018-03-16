/**
 * @file band.cc Implementation of Band model node
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

#include "casper/jrxml/band.h"
#include "casper/jrxml/print_when_expression.h"
#include "casper/jrxml/property.h"
#include "osal/osalite.h"

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
casper::jrxml::Band::Band (Node* a_parent) : Node(a_parent)
{
    node_type_ = EBand;
    band_type_ = "DT";

    /* By default all attributes will be unset */
    
    /*
     * Init pointers to child elements
     */
    print_when_expression_ = nullptr;
}

/**
 * @brief Destructor
 */
casper::jrxml::Band::~Band ()
{
    /*
     * child nodes will be deleted by base class constructor, just nullptr the pointers
     */
    print_when_expression_ = nullptr;
    properties_.clear();
}

/**
 * @brief Parse XML DOM to the memory model
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true for success, false if an error is detected
 */
bool casper::jrxml::Band::ParseXml (pugi::xml_node a_xml_node)
{
    /*
     * Parse attributes
     */
    split_type_.FromStr(a_xml_node.attribute("splitType").value());
    height_.FromStr(a_xml_node.attribute("height").value());
    
    /*
     * Parse child elements
     */
    for (pugi::xml_node child = a_xml_node.first_child(); child; child = child.next_sibling()) {
        if ( strcmp(child.name(), "printWhenExpression") == 0 ) {
            print_when_expression_ = PrintWhenExpression::CreateFromXml(child, this);
        } else if ( strcmp(child.name(), "property") == 0 ) {
            Property* property = Property::CreateFromXml(child, this);
            if ( nullptr != property ) {
                properties_[property->Name().Value()] = property;
            }
        } else {
OSALITE_TODO("ADD PropertyExpression")
            ElementFactory(child.name(), child, this);
        }
    }
    
    return true;
}

/**
 * @brief Factory method to create a Band from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return nullptr if the element is not present in the DOM node
 */
casper::jrxml::Band* casper::jrxml::Band::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( a_xml_node != nullptr ) {
        casper::jrxml::Band* node = new casper::jrxml::Band(a_parent);
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
 * @brief Factory method to create a Background from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return nullptr if the element is not present in the DOM node
 */
casper::jrxml::BackgroundBand* casper::jrxml::BackgroundBand::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( nullptr != a_xml_node ) {
        casper::jrxml::BackgroundBand* node = new casper::jrxml::BackgroundBand(a_parent);
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
 * @brief Factory method to create a Title from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return nullptr if the element is not present in the DOM node
 */
casper::jrxml::TitleBand* casper::jrxml::TitleBand::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( nullptr != a_xml_node ) {
        casper::jrxml::TitleBand* node = new casper::jrxml::TitleBand(a_parent);
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
 * @brief Factory method to create a PageHeader from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return nullptr if the element is not present in the DOM node
 */
casper::jrxml::PageHeaderBand* casper::jrxml::PageHeaderBand::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( nullptr != a_xml_node ) {
        casper::jrxml::PageHeaderBand* node = new casper::jrxml::PageHeaderBand(a_parent);
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
 * @brief Factory method to create a ColumnHeader from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return nullptr if the element is not present in the DOM node
 */
casper::jrxml::ColumnHeaderBand* casper::jrxml::ColumnHeaderBand::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( nullptr != a_xml_node ) {
        casper::jrxml::ColumnHeaderBand* node = new casper::jrxml::ColumnHeaderBand(a_parent);
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
 * @brief Factory method to create a ColumnFooter from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return nullptr if the element is not present in the DOM node
 */
casper::jrxml::ColumnFooterBand* casper::jrxml::ColumnFooterBand::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( nullptr != a_xml_node ) {
        casper::jrxml::ColumnFooterBand* node = new casper::jrxml::ColumnFooterBand(a_parent);
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
 * @brief Factory method to create a PageFooter from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return nullptr if the element is not present in the DOM node
 */
casper::jrxml::PageFooterBand* casper::jrxml::PageFooterBand::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( nullptr != a_xml_node ) {
        casper::jrxml::PageFooterBand* node = new casper::jrxml::PageFooterBand(a_parent);
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
 * @brief Factory method to create a LastPageFooter from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return nullptr if the element is not present in the DOM node
 */
casper::jrxml::LastPageFooterBand* casper::jrxml::LastPageFooterBand::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( nullptr != a_xml_node ) {
        casper::jrxml::LastPageFooterBand* node = new casper::jrxml::LastPageFooterBand(a_parent);
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
 * @brief Factory method to create a Summary from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return nullptr if the element is not present in the DOM node
 */
casper::jrxml::SummaryBand* casper::jrxml::SummaryBand::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( nullptr != a_xml_node ) {
        casper::jrxml::SummaryBand* node = new casper::jrxml::SummaryBand(a_parent);
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
 * @brief Factory method to create a GroupHeaderBand from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return nullptr if the element is not present in the DOM node
 */
casper::jrxml::GroupHeaderBand* casper::jrxml::GroupHeaderBand::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( nullptr != a_xml_node ) {
        casper::jrxml::GroupHeaderBand* node = new casper::jrxml::GroupHeaderBand(a_parent);
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
 * @brief Factory method to create a GroupFooterBand from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return nullptr if the element is not present in the DOM node
 */
casper::jrxml::GroupFooterBand* casper::jrxml::GroupFooterBand::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( nullptr != a_xml_node ) {
        casper::jrxml::GroupFooterBand* node = new casper::jrxml::GroupFooterBand(a_parent);
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
void casper::jrxml::Band::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] %s", a_depth * 2, a_depth * 2, " ", child_index_, band_type_);
    if ( height_.IsSet() ) {
        fprintf(a_stream, " height=%.2f", (float) height_);
    }
    if ( split_type_.IsSet() ) {
        fprintf(a_stream, " split_type='%s'", (const char*) split_type_);
    }
    fprintf(a_stream, "\n");
}


/**
 * @brief Factory method to create a NoData from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return nullptr if the element is not present in the DOM node
 */
casper::jrxml::NoDataBand* casper::jrxml::NoDataBand::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( nullptr != a_xml_node ) {
        casper::jrxml::NoDataBand* node = new casper::jrxml::NoDataBand(a_parent);
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
