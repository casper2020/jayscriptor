/**
 * @file fake_java_expression.h Expression evaluator for JAVA subset used in the report expressions
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
#ifndef NRS_CASPER_CASPER_JAVA_FAKE_JAVA_EXPRESSION_H
#define NRS_CASPER_CASPER_JAVA_FAKE_JAVA_EXPRESSION_H

#include "casper/java/fake_java_scanner.h"
#include "casper/java/fake_java_parser.hh"
#include "casper/java/fake_java_term.h"
#include "casper/abstract_data_source.h"
#include "casper/java/interpreter.h"

#if !defined(CASPER_NO_ICU)
    #include "unicode/locid.h"
#endif

namespace casper
{
    namespace java
    {
        /**
         * @brief Expression evaluator for JAVA subset used in the report expressions
         */
        class FakeJavaExpression
        {
            friend class FakeJavaParser;

        public:

            static const char* const k_java_number_types_ [];
            static const char* const k_java_string_types_ [];
            static const char* const k_boolean_string_types_ [];

        public: //protected: // data

            std::vector<SymbolTable>  variables_;       //!< Symbol table that contains the report variables
            SymbolTable               param_defaults_;  //!< Default values of the report paramaters
            Term                      result_;          //!< Result of the expression calculation
            FakeJavaScanner           scanner_;         //!< Scanner for a small subset of JAVA used in the report expressions
            FakeJavaParser            parser_;          //!< Expression parser for a restricted subset of the JAVA language
            AbstractDataSource*       data_source_;     //!< Pointer to the data source that feeds the expressions
            Term                      null_term_;       //!< Use to return a constant NULL term
            IntHash                   field_type_map_;  //!< Stores the Term type enumeration of each report field
            IntHash                   param_type_map_;  //!< Stores the Term type enumeration of each report parameter

#if !defined(CASPER_NO_ICU)
            const U_ICU_NAMESPACE::Locale* locale_ptr_;       //!< Pointer to the currently setted localed.
#endif
            bool                use_data_source_variables_;
            bool                use_data_source_param_types_;

        protected: // Methods

            void GetParameter         (Term& o_term, const char* a_param_name);
            void GetField             (Term& o_term, const char* a_field_name);

        public: // Methods

#if !defined(CASPER_NO_ICU)
            FakeJavaExpression (const U_ICU_NAMESPACE::Locale* a_locale);
#else
            FakeJavaExpression ();
#endif
            virtual ~FakeJavaExpression ();

            void                SetDataSource (AbstractDataSource* a_data_source);
            AbstractDataSource* GetDataSource () const;

            const Term& Calculate           (const std::string& a_expression);
            const Term& Calculate           (const char* a_expression, size_t a_len);
            void       Convert           (const std::string& a_expression);
            void       Convert           (const char* a_expression, size_t a_len);
            const Term& GetVariable         (const char* a_varname) const;
            void        SetDoubleVariable   (const char* a_varname, double a_double);
            void        SetStringVariable   (const char* a_varname, const char* a_value);
            void        GetVariable         (Term& a_result, Term& a_varname);
            void        GetVariable         (Term& a_result, const char* a_varname);
            void        ClearVariable       (const char* a_varname);

            void        SetFieldType        (const char* a_field_name, const char* a_class_name);
            void        SetParameterDefault (const char* a_param_name, const char* a_class_name, const char* a_default_expr);
            Term&       GetExpressionResult ();

            int  JavaToTermTypeMapper (const char* a_what, const char* a_class_name);
            int  GetParameterType           (const char* a_param_name);
            int  GetFieldType               (const char* a_field_name);

#if !defined(CASPER_NO_ICU)
            const U_ICU_NAMESPACE::Locale* GetLocale () const;
            void                           ToDate (const casper::Term* a_term, casper::Term& o_term);
#endif
            void                  SetUseDataSourceVariables  (bool a_use);
            void                  SetUseDataSourceParamTypes (bool a_use);
            void                  CloneDataRowVariables      (int a_data_source_index);
            void                  ResetRowVariablesAtIndex   (int a_index);
        };

        inline void FakeJavaExpression::SetDataSource (AbstractDataSource* a_data_source)
        {
            data_source_ = a_data_source;
            field_type_map_.clear();
            param_type_map_.clear();
            param_defaults_.clear();
            variables_.clear();
            variables_.push_back(SymbolTable());
            null_term_.SetNull();
            result_.SetNull();
        }

        inline Term& FakeJavaExpression::GetExpressionResult ()
        {
            return result_;
        }

        inline AbstractDataSource* FakeJavaExpression::GetDataSource () const
        {
            return data_source_;
        }

        inline int casper::java::FakeJavaExpression::GetParameterType (const char* a_param_name)
        {
            IntHash::iterator it = param_type_map_.find(a_param_name);
            if ( param_type_map_.end() == it ) {
                return Term::EUndefined;
            }
            return it->second;
        }

        inline int casper::java::FakeJavaExpression::GetFieldType (const char* a_field_name)
        {
            IntHash::iterator it = field_type_map_.find(a_field_name);
            if ( field_type_map_.end() == it ) {
                return Term::EUndefined;
            }
            return it->second;
        }

        inline void FakeJavaExpression::SetDoubleVariable (const char* a_varname, double a_double)
        {
            Term val;

            val = a_double;

            if ( true == use_data_source_variables_ && nullptr != data_source_ && true == data_source_->VariableExists(a_varname) ) {
                data_source_->SetVariable(a_varname, val);
            } else {
                variables_[data_source_->DataRowIndex()][a_varname] = val;
            }
        }

        inline void FakeJavaExpression::SetStringVariable (const char* a_varname, const char* a_value)
        {
            Term val;

            val = a_value;

            if ( true == use_data_source_variables_ && nullptr != data_source_ && true == data_source_->VariableExists(a_varname) ) {
                data_source_->SetVariable(a_varname, val);
            } else {
                variables_[data_source_->DataRowIndex()][a_varname] = val;
            }
        }

        inline void FakeJavaExpression::GetVariable (Term& a_result, Term& a_varname)
        {
            const std::string variable_name       = a_varname.ToString();
            const char* const variable_name_c_str = variable_name.c_str();

            if ( true == use_data_source_variables_ && nullptr != data_source_ && true == data_source_->VariableExists(variable_name_c_str) ) {
                const Term* result = data_source_->GetVariable(variable_name_c_str);
                if ( nullptr != result ) {
                    a_result = *result;
                } else {
                    a_result.SetNull();
                }
            } else {
                SymbolTable::iterator it = variables_[data_source_->DataRowIndex()].find(variable_name_c_str);
                if ( it == variables_[data_source_->DataRowIndex()].end() ) {
                    a_result.SetNull();
                } else {
                    a_result = it->second;
                }
            }
        }

        inline void FakeJavaExpression::GetVariable  (Term& a_result, const char* a_varname)
        {
            SymbolTable::iterator it = variables_[data_source_->DataRowIndex()].find(a_varname);

            if ( it == variables_[data_source_->DataRowIndex()].end() ) {
                if ( true == use_data_source_variables_ &&  nullptr != data_source_ ) {
                    const Term* result = data_source_->GetVariable(a_varname);
                    if ( nullptr != result ) {
                        a_result = *result;
                    } else {
                        a_result.SetNull();
                    }
                } else {
                    a_result.SetNull();
                }
            } else {
                a_result = it->second;
            }
        }

        inline const Term& FakeJavaExpression::GetVariable(const char* a_varname) const
        {
            SymbolTable::const_iterator it = variables_[data_source_->DataRowIndex()].find(a_varname);

            if ( it == variables_[data_source_->DataRowIndex()].end() ) {
                if ( true == use_data_source_variables_ && nullptr != data_source_ ) {
                    const Term* result = data_source_->GetVariable(a_varname);
                    if ( nullptr != result ) {
                        return *result;
                    } else {
                        return null_term_;
                    }
                } else {
                    return null_term_;
                }
            } else {
                return it->second;
            }
        }


        inline void FakeJavaExpression::ClearVariable (const char* a_varname)
        {
            variables_[data_source_->DataRowIndex()].erase(a_varname);
        }

#if !defined(CASPER_NO_ICU)
        inline const U_ICU_NAMESPACE::Locale* FakeJavaExpression::GetLocale () const
        {
            return locale_ptr_;
        }
#endif

        inline void FakeJavaExpression::SetUseDataSourceVariables (bool a_use)
        {
            use_data_source_variables_ = a_use;
        }

        inline void FakeJavaExpression::SetUseDataSourceParamTypes (bool a_use)
        {
            use_data_source_param_types_ = a_use;
        }

    } // namespace java

} // namespace casper

#endif // NRS_CASPER_CASPER_JAVA_FAKE_JAVA_EXPRESSION_H
