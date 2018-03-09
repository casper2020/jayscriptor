/**
 * @file fake_java_expression.cc Implementation of FakeJavaExpression
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

#include "casper/java/fake_java_expression.h"
#include "casper/jrxml/parameter.h"
#include "casper/abstract_data_source.h"
#include "osal/osalite.h"

const char* const casper::java::FakeJavaExpression::k_java_number_types_ [] = { "java.lang.Integer", "java.lang.Long", "java.lang.Double", "java.lang.Float", "java.lang.Byte", nullptr };
const char* const casper::java::FakeJavaExpression::k_java_string_types_ [] = { "java.lang.String", nullptr };
const char* const casper::java::FakeJavaExpression::k_boolean_string_types_ [] = { "java.lang.Boolean", nullptr };
extern AstNode root;

/**
 * @brief Constructor
 */
#if !defined(CASPER_NO_ICU)
casper::java::FakeJavaExpression::FakeJavaExpression (const U_ICU_NAMESPACE::Locale* a_locale)
    : parser_(scanner_, *this), locale_ptr_(a_locale), use_data_source_variables_(false), use_data_source_param_types_(false)
{
    data_source_ = nullptr;
}
#else
/**
 * @brief Constructor
 */
casper::java::FakeJavaExpression::FakeJavaExpression ()
    : parser_(scanner_, *this), use_data_source_variables_(false)
{
    data_source_ = nullptr;
}
#endif

/**
 * @brief Destructor
 */
casper::java::FakeJavaExpression::~FakeJavaExpression ()
{
    /* empty */
}


//move this to other file....
void printAstTree(AstNode* node, int ntabs){
  //Numbers
  if(node->getType()==1){
    for(int i=0; i<ntabs; i++){
      std::cout << "\t";
    }
    std::cout << node->getVal() << "\n";
  }
  //Text
  else if(node->getType()==2){
    for(int i=0; i<ntabs; i++){
        std::cout << "\t";
    }
    std::cout  << node->getText() << "\n";
  }
  //Expressions
  else if(node->getType()==3){
    for(int i=0; i<ntabs; i++){
        std::cout << "\t";
    }
    std::cout  << node->getOp() << "\n";
    printAstTree(node->getLeft(), ++ntabs);
    printAstTree(node->getRight(), ntabs++);
  }
  //Operations
  else if(node->getType()==4){
    for(int i=0; i<ntabs; i++){
        std::cout << "\t";
    }
    std::cout  << node->getOp() << "\n";
    printAstTree(node->getLeft(), ++ntabs);
    if(nullptr != node->getRight())
      printAstTree(node->getRight(), ntabs++);
  }

  else if(node->getType()==5){
    for(int i=0; i<ntabs; i++){
        std::cout << "\t";
    }
    std::cout  << node->getOp() << "\n";
  //  std::cout << "between " << node->getBIndex() << " " << node->getEIndex() << "\n";
    printAstTree(node->getLeft(), ++ntabs);
    if(nullptr != node->getRight())
      printAstTree(node->getRight(), ntabs++);
  }
}


void casper::java::FakeJavaExpression::Convert (const std::string& a_expression){
    Convert(a_expression.c_str(), a_expression.size());
}

void casper::java::FakeJavaExpression::Convert (const char* a_expression, size_t a_len){
    try {
        result_.SetNull();
        root = ast_null();
        scanner_.SetInput(a_expression, a_len);
        parser_.parse();

        printJS(&root);

    } catch (osal::Exception& a_exception) {
        if ( a_exception .IsNull() ) {
            result_.SetNull();
        } else {
            throw a_exception;
        }
    }
}

const casper::Term& casper::java::FakeJavaExpression::Calculate (const std::string& a_expression)
{
    return Calculate(a_expression.c_str(), a_expression.size());
}

const casper::Term& casper::java::FakeJavaExpression::Calculate (const char* a_expression, size_t a_len)
{
    try {
        result_.SetNull();
        scanner_.SetInput(a_expression, a_len);
        parser_.parse();

    } catch (osal::Exception& a_exception) {
        if ( a_exception .IsNull() ) {
            result_.SetNull();
        } else {
            throw a_exception;
        }
    }
    return result_;
}

void casper::java::FakeJavaExpression::SetParameterDefault(const char* a_param_name,
                                                          const char* a_class_name,
                                                          const char* a_default_expr)
{
    if ( true == use_data_source_param_types_ ) {
        throw OSAL_EXCEPTION_NA("This expression calculator instance is not ready to store default parameters properties!");
    }

    int type = JavaToTermTypeMapper("parameter", a_class_name);

    param_type_map_[a_param_name] = type;
    if ( a_default_expr != NULL ) {
        Calculate(a_default_expr, strlen(a_default_expr));

        switch (type) {

            case Term::EText:
                param_defaults_[a_param_name] = result_.ToString();
                break;

            case Term::ENumber:
                param_defaults_[a_param_name] = result_.ToNumber();
                break;

            case Term::EBoolean:
                param_defaults_[a_param_name] = result_.ToBoolean();
                break;

#if !defined(CASPER_NO_ICU)
            case Term::EDate:
                param_defaults_[a_param_name] = result_.ToNow();
                break;
#endif

            default:
                break;

        }
    }
}

void casper::java::FakeJavaExpression::GetParameter (Term& o_term, const char* a_param_name)
{
    const Term* param = data_source_->GetParameter(a_param_name);
    if ( param != NULL ) {

        int parameter_type;

        if ( true == use_data_source_param_types_ ) {
            parameter_type = param->GetType();
        } else {
            IntHash::iterator it = param_type_map_.find(a_param_name);
            if ( it == param_type_map_.end() ) {
                throw OSAL_EXCEPTION("Parameter '%s' type is not defined", a_param_name);
            }
            parameter_type = it->second;
        }

        if ( true == param->IsNull() ) {
            o_term.SetNull();
            return;
        }

        switch (parameter_type) {
            case Term::EText:
                o_term = param->ToStringBoolAsNum();
                break;
            case Term::ENumber:
                o_term = param->ToNumber();
                break;
            case Term::EBoolean:
                o_term = param->ToBoolean();
                break;
#if !defined(CASPER_NO_ICU)
            case Term::EDate:
                ToDate(param, o_term);
                break;
#endif
        }
    } else {
        SymbolTable::iterator it = param_defaults_.find(a_param_name);
        if ( it == param_defaults_.end() ) {
            o_term.SetNull();
        } else {
            o_term = it->second;
        }
    }
}

void casper::java::FakeJavaExpression::GetField (Term& o_term, const char* a_field_name)
{
    const Term* field = data_source_->GetField(a_field_name);
    if ( field != NULL ) {
        IntHash::iterator typ_it = field_type_map_.find(a_field_name);

        if (typ_it == field_type_map_.end() ) {
            throw OSAL_EXCEPTION("Field '%s' type is not defined", a_field_name);
        }

        if ( true == field->IsNull() ) {
            o_term.SetNull();
            return;
        }

        switch (typ_it->second) {
            case Term::EText:
                o_term = field->ToStringBoolAsNum();
                break;
            case Term::ENumber:
                o_term = field->ToNumber();
                break;

            case Term::EBoolean:
                o_term = field->ToBoolean();
                break;
#if !defined(CASPER_NO_ICU)
            case Term::EDate:
                ToDate(field, o_term);
                break;
#endif
        }
    } else {
        o_term.SetNull();
    }
}

void casper::java::FakeJavaExpression::SetFieldType (const char* a_field_name, const char* a_class_name)
{
    field_type_map_[a_field_name] = JavaToTermTypeMapper("field", a_class_name);
}

int casper::java::FakeJavaExpression::JavaToTermTypeMapper (const char* a_what, const char* a_class_name)
{
    if ( strcmp(a_class_name, "java.lang.String") == 0 ) {
        return Term::EText;
    } else if (strcmp(a_class_name, "java.lang.Integer") == 0 ) {
        return Term::ENumber;
    } else if (strcmp(a_class_name, "java.math.BigDecimal") == 0 ) {
        return Term::ENumber;
    } else if (strcmp(a_class_name, "java.lang.Long") == 0 ) {
        return Term::ENumber;
    } else if (strcmp(a_class_name, "java.lang.Double") == 0 ) {
        return Term::ENumber;
    } else if (strcmp(a_class_name, "java.lang.Float") == 0 ) {
        return Term::ENumber;
    } else if (strcmp(a_class_name, "java.lang.Boolean") == 0 ) {
        return Term::EBoolean;
    } else if (strcmp(a_class_name, "java.lang.Byte") == 0 ) {
        return Term::ENumber;
    }
#if !defined(CASPER_NO_ICU)
        else if( strcmp(a_class_name, "java.util.Date") == 0 ) {
            return Term::EDate;
        }
#endif
        else {
        throw OSAL_EXCEPTION("%s type '%s' is not supported by this data source", a_what, a_class_name);
    }
}

void casper::java::FakeJavaExpression::ResetRowVariablesAtIndex (int a_index)
{
    if ( a_index > 0 ) {
        for (auto vit : variables_[a_index - 1]) {
            variables_[a_index][vit.first] = vit.second;
        }
    }
}

void casper::java::FakeJavaExpression::CloneDataRowVariables (int a_data_source_index)
{
    if ( a_data_source_index == (int) variables_.size() - 1 ) {
        variables_.push_back(variables_[variables_.size() - 1]);
    } else {
        ResetRowVariablesAtIndex(a_data_source_index + 1);
    }
}

#if !defined(CASPER_NO_ICU)

void casper::java::FakeJavaExpression::ToDate (const casper::Term* a_term, casper::Term& o_term)
{
    o_term.type_ = casper::Term::EUndefined;

    static const char  k_known_short_date_separators_ [] = { '-', '/'                   };
    static const char* k_known_short_date_format_     [] = { "yyyy-MM-dd", "MM-dd-yyyy" };

    for ( auto separator : k_known_short_date_separators_ ) {

        for ( auto format : k_known_short_date_format_ ) {

            std::string pattern = format;
            std::replace(pattern.begin(), pattern.end(), '-', separator);
            o_term = a_term->ToDate(pattern.c_str(), *locale_ptr_);
            if ( casper::Term::EDate == o_term.type_ ) {
                break;
            }

        }

        if ( casper::Term::EDate == o_term.type_ ) {
            break;
        }

    }

    if ( Term::EDate != o_term.type_ ) {
        if ( casper::Term::EText == a_term->type_ ) {
            throw OSAL_EXCEPTION("Don't know how to parse date from text '%s'!",
                                 a_term->text_.c_str());
        } else {
            throw OSAL_EXCEPTION("Don't know how to parse date from type %d!",
                                 a_term->type_);
        }
    }
}

#endif
