/**
 * @file variable.h declaration of Variable model node
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
#ifndef NRS_CASPER_CASPER_MODEL_VARIABLE_H
#define NRS_CASPER_CASPER_MODEL_VARIABLE_H

#include "casper/calculation_phase.h"
#include "casper/jrxml/node.h"
#include "casper/jrxml/string_attr.h"
#include "casper/jrxml/reset_type_attr.h"
#include "casper/jrxml/calculation_attr.h"
#include "pugixml.hpp"

namespace casper
{
    namespace jrxml
    {
        class InitialValueExpression;
        class VariableExpression;
        
        /**
         * @brief Represents the definition of a report variable. 
         *
         * Variables are objects that store the values of their associated expressions or perform various calculations 
         * on those expression values. Expressions are java expressions build on top of fields and variables 
         * declared in the report. They are evaluated at runtime, when filling the report.
         */
        class Variable  : public Node
        {
        public: // Attributes
            
            StringAttr       name_;                //!< Parameter name
            StringAttr       class_;               //!< Parameter class or object type
            StringAttr       incrementer_factory_; //!< Hijacked to implement optional features
            ResetTypeAttr    reset_type_;          //!< Reset level for variables that perform calculations
            StringAttr       reset_group_;         //!< Name of the group at which the variable is reinitialized, when resetType is "Group".
            CalculationAttr  calculation_;         //!< Calculation to perform on the variable expression when filling the report
            CalculationPhase calc_phase_;          //!< When the variable should be calculated
                
        protected: // Child Elements
            
            InitialValueExpression* initial_value_expression_;
            VariableExpression*     variable_expression_;
            
        public: // Methods
            
                    Variable  (Node* a_parent);
            virtual ~Variable ();
            
            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;
            
            static Variable* CreateFromXml (pugi::xml_node a_node, Node* a_parent);
            
        public: // Attribute accessors
            
            const StringAttr&      Name        () const { return name_;        }
            const StringAttr&      Class       () const { return class_;       }
            const ResetTypeAttr&   ResetType   () const { return reset_type_;  }
            const StringAttr&      ResetGroup  () const { return reset_group_; }
            const CalculationAttr& Calculation () const { return calculation_; }
            const CalculationPhase CalcPhase   () const { return calc_phase_;  }
            
        public: // Element accessors
            
            InitialValueExpression& GetInitialValueExpression () const { return *initial_value_expression_; }
            VariableExpression&     GetVariableExpression     () const { return *variable_expression_;      }
            
            bool HasInitialValueExpression () const { return initial_value_expression_ != nullptr; }
            bool HasVariableExpression     () const { return variable_expression_      != nullptr; }
            
        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_MODEL_VARIABLE_H
