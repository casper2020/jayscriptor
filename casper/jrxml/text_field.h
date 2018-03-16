/**
 * @file text_field.h declaration of TextField model node
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
#ifndef NRS_CASPER_CASPER_JRXML_TEXT_FIELD_H
#define NRS_CASPER_CASPER_JRXML_TEXT_FIELD_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/string_attr.h"
#include "casper/jrxml/bool_attr.h"
#include "casper/jrxml/complex_evaluation_time_attr.h"

namespace casper
{
    namespace jrxml
    {
        class ReportElement;
        class Box;
        class TextElement;
        class TextFieldExpression;
        class PatternExpression;
        class PrintWhenExpression;

        /**
         * @brief Definition of a text field object
         */
        class TextField  : public Node
        {
        public: // Attributes

            BoolAttr                  is_stretch_with_overflow_;  /** Instructs the report engine to allow the text field to stretch downwards
                                                                   *  in order to display all its text when it doesn't fit in the defined text field height. */
            ComplexEvaluationTimeAttr evaluation_time_;           /** Text to be printed is supplied by the text field associated expression.
                                                                   *   This expression can be evaluated at a specified moment. This could be useful,
                                                                   *   for example, when we want to have on the first page the total number of pages.
                                                                   *   The total number of pages is known only after filling the entire report,
                                                                   *   so we can specify that the text filed that will represent the total number of
                                                                   *   pages placed at the beginning of the report should be evaluated only
                                                                   *   when reaching the end of the report. */
            StringAttr                pattern_;                   /** Pattern to use when formatting the output of the text field expression. */
            BoolAttr                  is_blank_when_null_;        /** Specifies that the text field should display a blank character instead of
                                                                   *  &quot;null&quot; when the text field expression evaluates to null. */

        protected: // Child Elements

            ReportElement*       report_element_;        //!< Mandatory
            Box*                 box_;                   //!< Optional
            TextElement*         text_element_;          //!< Optional
            TextFieldExpression* text_field_expression_; //!< Optional
            PatternExpression*   pattern_expression_;    //!< Optional

        public: // Methods

            TextField (Node* a_parent);
            virtual ~TextField ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;


            static TextField* CreateFromXml (pugi::xml_node a_node, Node* a_parent) ;

        public: // Attribute accessors

            const BoolAttr&                  IsStretchWithOverflow () const { return is_stretch_with_overflow_; }
            const ComplexEvaluationTimeAttr& EvaluationTime        () const { return evaluation_time_;          }
            const StringAttr&                Pattern               () const { return pattern_;                  }
            const BoolAttr&                  IsBlankWhenNull       () const { return is_blank_when_null_;       }

        public: // Element accessors

            ReportElement&       GetReportElement       () const { return *report_element_;        }
            Box&                 GetBox                 () const { return *box_;                   }
            TextElement&         GetTextElement         () const { return *text_element_;          }
            TextFieldExpression& GetTextFieldExpression () const { return *text_field_expression_; }
            PatternExpression&   GetPatternExpression   () const { return *pattern_expression_;    }

            bool HasBox                 () const { return box_                   != NULL; }
            bool HasTextElement         () const { return text_element_          != NULL; }
            bool HasTextFieldExpression () const { return text_field_expression_ != NULL; }
            bool HasPatternExpression   () const { return pattern_expression_    != NULL; }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_TEXT_FIELD_H

