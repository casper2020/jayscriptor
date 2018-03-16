/**
 * @file report_element.cc Implementation of ReportElement model node
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

#include "casper/jrxml/report_element.h"
#include "casper/jrxml/print_when_expression.h"
#include "casper/jrxml/property_expression.h"
#include "casper/jrxml/property.h"
#include "osal/osalite.h"

/**
 * @brief Constructor, sets attributes default values and resets contained objects
 */
casper::jrxml::ReportElement::ReportElement (Node* a_parent) : Node(a_parent)
{
    node_type_ = EReportElement;
    
    /* By default all parameters are unset */
    
    print_when_expression_ = nullptr;
}

/**
 * @brief Destructor
 */
casper::jrxml::ReportElement::~ReportElement ()
{
    /*
     * child nodes will be deleted by base class constructor, just NULL the pointers
     */
    print_when_expression_ = NULL;
    properties_.clear();
    property_expressions_.clear();
    casper_binding_.clear();
}

/**
 * @brief Parse XML DOM to the memory model
 *
 * @param a_xml_node DOM node the with XML spec
 * @return true for success, false if an error is detected
 */
bool casper::jrxml::ReportElement::ParseXml (pugi::xml_node a_xml_node)
{
    /*
     * Parse attributes
     */
    position_type_.FromStr(a_xml_node.attribute("positionType").value());
    stretch_type_.FromStr(a_xml_node.attribute("stretchType").value());
    mode_.FromStr(a_xml_node.attribute("mode").value());
    x_.FromStr(a_xml_node.attribute("x").value());
    y_.FromStr(a_xml_node.attribute("y").value());
    width_.FromStr(a_xml_node.attribute("width").value());
    height_.FromStr(a_xml_node.attribute("height").value());
    forecolor_.FromStr(a_xml_node.attribute("forecolor").value());
    backcolor_.FromStr(a_xml_node.attribute("backcolor").value());
    style_.FromStr(a_xml_node.attribute("style").value());
    
    /*
     * Parse child elements
     */
    for (pugi::xml_node xml_node = a_xml_node.first_child(); xml_node; xml_node = xml_node.next_sibling()) {        
        if ( strcmp(xml_node.name(), "propertyExpression") == 0 ) {
            PropertyExpression* property_expression = PropertyExpression::CreateFromXml(xml_node, this);
            if ( NULL != property_expression ) {
                property_expressions_[property_expression->Name()] = property_expression;
            }
        } else if ( strcmp(xml_node.name(), "property") == 0 ) {
            Property* property = Property::CreateFromXml(xml_node, this);
            if ( NULL != property ) {
                properties_[property->Name().Value()] = property;
            }
        }
    }
    
    ParseJsonBinding();
    print_when_expression_ = PrintWhenExpression::CreateFromXml(a_xml_node.child("printWhenExpression"), this);

    return true;
}

void casper::jrxml::ReportElement::ParseJsonBinding ()
{
    PropertyExpression* property_expression;
    Property* property;
    
    casper_binding_.clear();
    /*
     * Migration hack, this is used to bridge bettween the current loose configuration with many properties to the upcoming JSON based configuration
     */
    auto it = properties_.find("casper.binding");
    if ( it != properties_.end() ) {
        const char* json_binding = it->second->Value();
        Json::Reader reader;
        
        if ( reader.parse(json_binding, casper_binding_, false) == false) {
            throw OSAL_EXCEPTION("error parsing json binding: '%s'", json_binding);
        }
        
        if ( casper_binding_.isMember("load") ) {
            Json::Value load = casper_binding_["load"];
            
            if ( load.isMember("filter") ) {
                Json::Value filter = load["filter"];
                
                if ( filter.isMember("field") ) {
                    property = new Property(this, "epaper.casper.text.field.load.uri.filter.field", filter["field"].asCString());
                    properties_[property->Name().Value()] = property;
                }
                if ( filter.isMember("id") ) {
                    property = new Property(this, "epaper.casper.text.field.load.uri.filter.id", filter["id"].asCString());
                    properties_[property->Name().Value()] = property;
                }
                if ( filter.isMember("name")) {
                    property = new Property(this, "epaper.casper.text.field.load.uri.filter.name", filter["name"].asCString());
                    properties_[property->Name().Value()] = property;
                }
            }
        }

        if ( casper_binding_.isMember("hint") ) {
            Json::Value hint = casper_binding_["hint"];
            
            if ( hint.isMember("expression" ) ) {
                property_expression = new PropertyExpression(this, "epaper.casper.text.field.hint.expression", hint["expression"].asCString());
                property_expressions_[property_expression->Name()] = property_expression;

            }
            if ( hint.isMember("field") ) {
                Json::Value field = hint["field"];
                
                if (field.isMember("name") ) {
                    property = new Property(this, "epaper.casper.text.field.hint.field", field["name"].asCString());
                    properties_[property->Name().Value()] = property;
                }
            }
        }
        
        if ( casper_binding_.isMember("editable") ) {
            Json::Value editable = casper_binding_["editable"];
            bool is_editable;

            if ( editable.isMember("is") ) {
                is_editable = editable["is"].asBool();
            } else {
                is_editable = true;
            }
            property = new Property(this, "epaper.casper.text.field.editable", is_editable ? "true" : "false");
            properties_[property->Name().Value()] = property;
            
            if ( editable.isMember("expression") ) {
                property = new Property(this, "epaper.casper.text.field.editable.expression.field", editable["expression"].asCString());
                properties_[property->Name().Value()] = property;
            }
            if ( editable.isMember("field") ) {
                Json::Value field = editable["field"];
                
                if ( field.isMember("name")) {
                    property = new Property(this, "epaper.casper.text.field.editable.field_name", field["name"].asCString());
                    properties_[property->Name().Value()] = property;
                }
            }
            if ( editable.isMember("patch") ) {
                Json::Value patch = editable["patch"];
                
                if ( patch.isMember("field") ) {
                    Json::Value field = patch["field"];
                    
                    if ( field.isMember("name") ) {
                        property = new Property(this, "epaper.casper.text.field.patch.name", field["name"].asCString());
                        properties_[property->Name().Value()] = property;
                    }
                    if ( field.isMember("pattern") ) {
                        property = new Property(this, "epaper.casper.text.field.patch.pattern", field["pattern"].asCString());
                        properties_[property->Name().Value()] = property;
                    }
                    if ( field.isMember("type") ) {
                        property = new Property(this, "epaper.casper.text.field.patch.type", field["type"].asCString());
                        properties_[property->Name().Value()] = property;
                    }
                }
            }
            if ( editable.isMember("conditionals") ) {
                Json::Value conditionals = editable["conditionals"];
                
                if ( conditionals.isMember("locked") ) {
                    property_expression = new PropertyExpression(this, "epaper.casper.text.field.editable.locked", conditionals["locked"].asCString());
                    property_expressions_[property_expression->Name()] = property_expression;

                }
                if ( conditionals.isMember("enabled") ) {
                    property_expression = new PropertyExpression(this, "epaper.casper.text.field.editable.if", conditionals["enabled"].asCString());
                     property_expressions_[property_expression->Name()] = property_expression;
                }
                if ( conditionals.isMember("disabled") ) {
                    property_expression = new PropertyExpression(this, "epaper.casper.text.field.disabled.if", conditionals["disabled"].asCString());
                    property_expressions_[property_expression->Name()] = property_expression;
                }
                if ( conditionals.isMember("reload") ) {
                    property = new Property(this, "epaper.casper.text.field.reload.if_changed", conditionals["reload"].asBool() ? "true" : "false");
                    properties_[property->Name().Value()] = property;
                }
            }
        }
        
        if ( casper_binding_.isMember("style") ) {
            Json::Value style = casper_binding_["style"];
            
            if ( style.isMember("overload") ) {
                Json::Value overload = style["overload"];
                
                if ( overload.isMember("condition") ) {
                    property = new Property(this, "epaper.casper.style.condition", overload["condition"].asCString());
                    properties_[property->Name().Value()] = property;
                }
            }
        }

        if ( casper_binding_.isMember("layout") ) {
            Json::Value layout = casper_binding_["layout"];
            
            if ( layout.isMember("properties") ) {
                Json::Value properties = layout["properties"];
                
                if ( properties.isMember("translationY") ) {
                    property = new Property(this, "epaper.casper.translation.y", properties["translation_y"].asCString());
                    properties_[property->Name().Value()] = property;
                }
                if ( properties.isMember("minBottomMargin") ) {
                    property = new Property(this, "epaper.casper.minimum.bottom.margin", properties["min_bottom_margin"].asCString());
                    properties_[property->Name().Value()] = property;
                }
            }
        }
        
        if ( casper_binding_.isMember("attachment") ) {
            Json::Value attachment = casper_binding_["attachment"];
            const char* type;
            
            if ( not (attachment.isMember("type") && attachment["type"].isString()) ) {
                throw OSAL_EXCEPTION("attachment object does not have a \"type\": '%s'", json_binding);
            }
            type = attachment["type"].asCString();
            property = new Property(this, "epaper.casper.text.field.attach", type);
            properties_[property->Name().Value()] = property;
            
            if ( 0 == strcmp(type, "dropDownList") || 0 == strcmp(type, "dropDownTree") ) {

                if ( attachment.isMember("mapping") ) {
                    Json::Value mapping = attachment["mapping"];
                    
                    if ( mapping.isMember("fields") ) {
                        Json::Value fields = mapping["fields"];
                        
                        if ( fields.isMember("id") ) {
                            property = new Property(this, "epaper.casper.text.field.attach.drop-down_list.field.id", fields["id"].asCString());
                            properties_[property->Name().Value()] = property;
                        }
                        if ( fields.isMember("name") ) {
                            property = new Property(this, "epaper.casper.text.field.attach.drop-down_list.field.name", fields["name"].asCString());
                            properties_[property->Name().Value()] = property;
                        }
                    }
                }
                if ( attachment.isMember("controller") ) {
                    property = new Property(this, "epaper.casper.text.field.attach.drop-down_list.controller", attachment["controller"].asCString());
                    properties_[property->Name().Value()] = property;
                }
                if ( attachment.isMember("display") ) {
                    std::stringstream ss;
                    Json::Value display = attachment["display"];
                    
                    for ( Json::Value::iterator it2 = display.begin(); it2 != display.end(); ++it2 ) {
                        if (it2 != display.begin() ) {
                            ss << ',';
                        } else {
                            ss << "[";
                        }
                        ss << (*it2);
                    }
                    ss << "]";
                    property = new Property(this, "epaper.casper.text.field.attach.drop-down_list.controller.display", ss.str().c_str());
                    properties_[property->Name().Value()] = property;
                }
                if ( attachment.isMember("addEmptyLine") ) {
                    property = new Property(this, "epaper.casper.text.field.attach.drop-down_list.controller.add.empty_line", attachment["addEmptyLine"].asBool() ? "true" : "false");
                    properties_[property->Name().Value()] = property;
                }
                if ( attachment.isMember("pickFirstIfEmpty") ) {
                    property = new Property(this, "epaper.casper.text.field.attach.drop-down_list.controller.pick.first_if_empty", attachment["pickFirstIfEmpty"].asBool() ? "true" : "false");
                    properties_[property->Name().Value()] = property;
                }
                if ( attachment.isMember("open") ) {
                    Json::Value open = attachment["open"];
                    
                    if ( open.isMember("route") ) {
                        property = new Property(this, "epaper.casper.text.field.attach.drop-down_list.controller.open.uri", open["route"].asCString());
                        properties_[property->Name().Value()] = property;
                    }
                    if ( open.isMember("jrxml") ) {
                        property = new Property(this, "epaper.casper.text.field.attach.drop-down_list.controller.open.jrxml", open["jrxml"].asCString());
                        properties_[property->Name().Value()] = property;
                    }
                }
                if ( attachment.isMember("version") ) {
                    char szTmp[50];
                    sprintf(szTmp, "%d", attachment["version"].asInt());
                    
                    property = new Property(this, "epaper.casper.text.field.attach.drop-down_list.version", szTmp);
                    properties_[property->Name().Value()] = property;
                }
            } else if ( 0 == strcmp(type, "treeList") ) {
                if ( attachment.isMember("mapping") ) {
                    Json::Value mapping = attachment["mapping"];
                    
                    if ( mapping.isMember("field") ) {
                        Json::Value field = mapping["field"];
                    
                        if ( field.isMember("id") ) {
                            property = new Property(this, "epaper.casper.text.field.attach.tree_list.field.id", field["id"].asCString());
                            properties_[property->Name().Value()] = property;
                        }
                        if ( field.isMember("name") ) {
                            property = new Property(this, "epaper.casper.text.field.attach.tree_list.field.name", field["name"].asCString());
                            properties_[property->Name().Value()] = property;
                        }
                    }
                }
            } else if ( 0 == strcmp(type, "checkbox" ) ) {
                Json::Value value = attachment["value"];
                    
                if ( value.isMember("type") ) {
                    property = new Property(this, "epaper.casper.text.field.attach.checkbox.value.type", value["type"].asCString());
                    properties_[property->Name().Value()] = property;
                }
                if ( value.isMember("on") ) {
                    property = new Property(this, "epaper.casper.text.field.attach.checkbox.value.on", value["on"].asCString());
                    properties_[property->Name().Value()] = property;
                }
                if ( value.isMember("off") ) {
                    property = new Property(this, "epaper.casper.text.field.attach.checkbox.value.off", value["off"].asCString());
                    properties_[property->Name().Value()] = property;
                }
            } else if ( 0 == strcmp(type, "radioButton") ) {
                Json::Value value = attachment["value"];
                    
                if ( value.isMember("type") ) {
                    property = new Property(this, "epaper.casper.text.field.attach.radio_button.value.type", value["type"].asCString());
                    properties_[property->Name().Value()] = property;
                }
                if ( value.isMember("on") ) {
                    property = new Property(this, "epaper.casper.text.field.attach.radio_button.value.on", value["on"].asCString());
                    properties_[property->Name().Value()] = property;
                }
                if ( value.isMember("off") ) {
                    property = new Property(this, "epaper.casper.text.field.attach.radio_button.value.off", value["off"].asCString());
                    properties_[property->Name().Value()] = property;
                }
            } else if ( 0 == strcmp(type, "button") ) {
                if ( not attachment.isMember("value") ) {
                    throw OSAL_EXCEPTION("button attachment must specify value: '%s'", json_binding);
                }
                Json::Value value = attachment["value"];

                if ( value.isMember("route") ) {
                    property = new Property(this, "epaper.casper.text.field.attach.button.open.uri", value["route"].asCString());
                    properties_[property->Name().Value()] = property;
                }
                if ( value.isMember("jrxml") ) {
                    property = new Property(this, "epaper.casper.text.field.attach.button.open.jrxml", value["jrxml"].asCString());
                    properties_[property->Name().Value()] = property;
                }
            } else if ( 0 == strcmp(type, "band" ) ) {
                if ( not attachment.isMember("add") ) {
                    throw OSAL_EXCEPTION("button attachment must specify value: '%s'", json_binding);
                    
                }
                Json::Value add = attachment["add"];
                
                if ( add.isMember("attr") ) {
                    property = new Property(this, "epaper.casper.band.patch.op.add.attribute.name", add["add"].asCString());
                    properties_[property->Name().Value()] = property;
                }
                if ( add.isMember("enabled" ) ) {
                    property = new Property(this, "epaper.casper.band.patch.op.add.enabled", add["enabled"].asCString());
                    properties_[property->Name().Value()] = property;
                }
                if ( add.isMember("seqno") ) {
                    property = new Property(this, "epaper.casper.band.patch.op.add.attribute.seqno.name", add["seqno"].asCString());
                    properties_[property->Name().Value()] = property;
                }
            } else if ( 0 == strcmp(type, "report" ) ) {
              // TODO styles???
            }
            if ( attachment.isMember("route") ) {
                property_expression = new PropertyExpression(this, "epaper.casper.text.field.load.uri", attachment["route"].asCString());
                property_expressions_[property_expression->Name()] = property_expression;
            }
        }
        fprintf(stdout, "----------------------------------------------------------------------------------\n");
        for ( auto prop: properties_) {
            fprintf(stdout, "PR -- %s -> %s\n", prop.first.c_str(), prop.second->Value().c_str());
        }
        for ( auto prop: property_expressions_) {
            fprintf(stdout, "PE -- %s -> %s\n", prop.first.c_str(), prop.second->c_str());
        }
    }
}

/**
 * @brief Factory method to create a ReportElement from it's XML representation
 *
 * @param a_xml_node DOM node the with XML spec
 * @param a_parent parent node of the model
 * @return NULL if the element is not present in the DOM node
 */
casper::jrxml::ReportElement* casper::jrxml::ReportElement::CreateFromXml (pugi::xml_node a_xml_node, Node* a_parent)
{
    if ( a_xml_node != NULL ) {
        casper::jrxml::ReportElement* node = new casper::jrxml::ReportElement(a_parent);
        if ( NULL != node ) {
            if ( node->ParseXml(a_xml_node) == false ) {
                delete node;
            } else {
                return node;
            }
        } else {
            throw OSAL_EXCEPTION_NA("out of memory");
        }
    }
    return NULL;
}

/**
 * @brief Print node information for debug
 *
 * @param a_stream the output handle
 * @param a_depth tree depth for indentation
 */
void casper::jrxml::ReportElement::PrintNodeInfo (FILE* a_stream, int a_depth) const
{
    fprintf(a_stream, "%*.*s[%d] ReportElement", a_depth * 2, a_depth * 2, " ", child_index_);
    if ( style_.IsSet() ) {
        fprintf(a_stream, " style='%s'", (const char*) style_);
    }
    if ( position_type_.IsSet() ) {
        fprintf(a_stream, " positionType='%s'", (const char*) position_type_);
    }
    if ( stretch_type_.IsSet() ) {
        fprintf(a_stream, " stretchType='%s'", (const char*) stretch_type_);
    }
    if ( mode_.IsSet() ) {
        fprintf(a_stream, " mode='%s'", (const char*) mode_);
    }
    if ( x_.IsSet() ) {
        fprintf(a_stream, " x=%.2f", (float) x_);
    }
    if ( y_.IsSet() ) {
        fprintf(a_stream, " y=%.2f", (float) y_);
    }
    if ( width_.IsSet() ) {
        fprintf(a_stream, " width=%.2f", (float) width_);
    }
    if ( height_.IsSet() ) {
        fprintf(a_stream, " height=%.2f", (float) height_);
    }
    if ( forecolor_.IsSet() ) {
        fprintf(a_stream, " forecolor=%08x", (uint32_t) forecolor_);
    }
    if ( backcolor_.IsSet() ) {
        fprintf(a_stream, " backcolor=%08x", (uint32_t) backcolor_);
    }
    fprintf(a_stream, "\n");
}
