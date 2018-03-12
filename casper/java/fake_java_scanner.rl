/**
 * @file fake_java_scanner.cc Implementation of FakeJavaScanner
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

 #include "casper/java/fake_java_scanner.h"
 #include "osal/osalite.h"
#include "osal/osal_types.h"
#include "osal/osal_time.h"
#include "osal/osal_date.h"
#include "osal/utils/pow10.h"
#include "osal/exception.h"

 %%{
     machine casper_fake_java_scanner;
     include generic_number_parser "../../../osal/src/osal/ragelib/generic_number_parser.rlh";
     alphtype char;
     write data;

     ws = [ \t\n];

    variable_ref  = '$V' [{(] [a-zA-Z_][a-zA-Z0-9#_\-?]* [})];

    field_ref     = '$F' [{(] [a-zA-Z_][a-zA-Z0-9#_\-?]* [})];

    parameter_ref = '$P' [{(] [a-zA-Z_][a-zA-Z0-9#_\-?]* [})];

    escaped_quote = ('""' %{ has_quotes = true; });

    not_quote     = [^\"];

    text_literal = '"' ( escaped_quote | not_quote )* '"';

    main := |*

        #
        # Keywords
        #
        'Double'        => { ret = FakeJavaParser::token::Double       ; fbreak; };
        'Boolean'       => { ret = FakeJavaParser::token::Boolean      ; fbreak; };
        'Integer'       => { ret = FakeJavaParser::token::Integer      ; fbreak; };
        'String'        => { ret = FakeJavaParser::token::String       ; fbreak; };
        'TRUE'          => { ret = FakeJavaParser::token::TK_TRUE      ; fbreak; };
        'FALSE'         => { ret = FakeJavaParser::token::TK_FALSE     ; fbreak; };
        'true'          => { ret = FakeJavaParser::token::TK_true      ; fbreak; };
        'false'         => { ret = FakeJavaParser::token::TK_false     ; fbreak; };
        'null'          => { ret = FakeJavaParser::token::TK_null      ; fbreak; };
        'valueOf'       => { ret = FakeJavaParser::token::valueOf      ; fbreak; };
        'parseDouble'   => { ret = FakeJavaParser::token::parseDouble  ; fbreak; };
        'parseBoolean'  => { ret = FakeJavaParser::token::parseBoolean ; fbreak; };
        'parseInt'      => { ret = FakeJavaParser::token::parseInt     ; fbreak; };
        'parse'         => { ret = FakeJavaParser::token::parse        ; fbreak; };
        'isEmpty'       => { ret = FakeJavaParser::token::isEmpty      ; fbreak; };
        'length'        => { ret = FakeJavaParser::token::length       ; fbreak; };
        'toUpperCase'   => { ret = FakeJavaParser::token::toUpperCase  ; fbreak; };
        'toLowerCase'   => { ret = FakeJavaParser::token::toLowerCase  ; fbreak; };
        'equals'        => { ret = FakeJavaParser::token::equals       ; fbreak; };
        'substring'     => { ret = FakeJavaParser::token::substring    ; fbreak; };
        'replace'       => { ret = FakeJavaParser::token::replace      ; fbreak; };
        'format'        => { ret = FakeJavaParser::token::format       ; fbreak; };
        'startsWith'    => { ret = FakeJavaParser::token::startsWith   ; fbreak; };
        'endsWith'      => { ret = FakeJavaParser::token::endsWith     ; fbreak; };
        'toString'      => { ret = FakeJavaParser::token::toString     ; fbreak; };
        'intValue'      => { ret = FakeJavaParser::token::intValue     ; fbreak; };
        'longValue'     => { ret = FakeJavaParser::token::longValue    ; fbreak; };
        'doubleValue'   => { ret = FakeJavaParser::token::doubleValue  ; fbreak; };
        'floatValue'    => { ret = FakeJavaParser::token::doubleValue  ; fbreak; };
        'to_i'          => { ret = FakeJavaParser::token::to_i         ; fbreak; };
        'to_f'          => { ret = FakeJavaParser::token::to_f         ; fbreak; };
        'isNaN'         => { ret = FakeJavaParser::token::isNaN        ; fbreak; };
        'Math'          => { ret = FakeJavaParser::token::Math         ; fbreak; };
        'abs'           => { ret = FakeJavaParser::token::abs          ; fbreak; };
        'indexOf'       => { ret = FakeJavaParser::token::indexOf      ; fbreak; };
        'Date'          => { ret = FakeJavaParser::token::TK_DATE      ; fbreak; };
        'DateFormat'    => { ret = FakeJavaParser::token::TK_DATE_FORMAT; fbreak; };
        'new'           => { ret = FakeJavaParser::token::TK_NEW        ; fbreak; };

        #
        # Operators and other "atomics" that we like to see as they are in the grammar
        #
        '('   => { ret = (FakeJavaParser::token_type) '(' ; fbreak; };
        ')'   => { ret = (FakeJavaParser::token_type) ')' ; fbreak; };
        '+'   => { ret = (FakeJavaParser::token_type) '+' ; fbreak; };
        '-'   => { ret = (FakeJavaParser::token_type) '-' ; fbreak; };
        '*'   => { ret = (FakeJavaParser::token_type) '*' ; fbreak; };
        '/'   => { ret = (FakeJavaParser::token_type) '/' ; fbreak; };
        ':'   => { ret = (FakeJavaParser::token_type) ':' ; fbreak; };
        '!'   => { ret = (FakeJavaParser::token_type) '!' ; fbreak; };
        '?'   => { ret = (FakeJavaParser::token_type) '?' ; fbreak; };
        '>'   => { ret = (FakeJavaParser::token_type) '>' ; fbreak; };
        '<'   => { ret = (FakeJavaParser::token_type) '<' ; fbreak; };
        '.'   => { ret = (FakeJavaParser::token_type) '.' ; fbreak; };
        ','   => { ret = (FakeJavaParser::token_type) ',' ; fbreak; };
        '}'   => { ret = (FakeJavaParser::token_type) '}' ; fbreak; };

        '<='  => { ret = FakeJavaParser::token::LE        ; fbreak; };
        '>='  => { ret = FakeJavaParser::token::GE        ; fbreak; };
        '!='  => { ret = FakeJavaParser::token::NE        ; fbreak; };
        '=='  => { ret = FakeJavaParser::token::EQ        ; fbreak; };
        '&&'  => { ret = FakeJavaParser::token::AND       ; fbreak; };
        '||'  => { ret = FakeJavaParser::token::OR        ; fbreak; };

        #
        # Tokens that rely on regular expressions
        #
        variable_ref    => {
                                ret = FakeJavaParser::token::VARIABLE;
                                *o_val = std::string(ts_ + 3, te_ - ts_ - 4);
                                fbreak;
                           };

        field_ref       => {
                                ret = FakeJavaParser::token::FIELD;
                                *o_val = std::string(ts_ + 3, te_ - ts_ - 4);
                                fbreak;
                           };

        parameter_ref   => {
                                ret = FakeJavaParser::token::PARAMETER;
                                *o_val = std::string(ts_ + 3, te_ - ts_ - 4);
                                fbreak;
                           };

        positive_number => {
                                ret = FakeJavaParser::token::NUM;
                                *o_val = double_value_;
                                fbreak;
                           };

        text_literal    => {
                             if ( (int)(te_ - ts_) - 2 < 0 ) {
                                *o_val = "";
                                ret = (FakeJavaParser::token_type) '"';
                                fbreak;
                             } else {
                                if ( has_quotes ) {
                                    char* buf = (char*) malloc(te_ - ts_ - 1);
                                    if ( buf == NULL ) {
                                        ret = (FakeJavaParser::token_type) '"'; // Ooops we got out of memory, force parse error
                                    }

                                    char* src = (char*) ts_ + 1;
                                    char* dst = buf;
                                    while ( src <= te_ ) {
                                       if ( *(src) == '"' ) {
                                          ++src;
                                          *(dst++) = *(src++);
                                       } else {
                                          *(dst++) = *(src++);
                                       }
                                    }
                                    *(dst) = 0;
                                    *o_val = buf;
                                    free(buf);
                                } else {
                                    *o_val = std::string(ts_ + 1, te_ - ts_ - 2);
                                }
                                ret = FakeJavaParser::token::TEXTLITERAL;
                                fbreak;
                             }
                           };
        ws;

    *|;
}%%

/**
 * @brief Constructor
 */
casper::java::FakeJavaScanner::FakeJavaScanner ()
{
    %% write init;
    OSAL_UNUSED_PARAM(casper_fake_java_scanner_first_final);
    OSAL_UNUSED_PARAM(casper_fake_java_scanner_error);
    OSAL_UNUSED_PARAM(casper_fake_java_scanner_en_main);
}

/**
 * @brief Destructor
 */
casper::java::FakeJavaScanner::~FakeJavaScanner ()
{
    /* empty */
}

/**
* @brief Set input.
*
* @param a_expression
* @param a_length
*/
void casper::java::FakeJavaScanner::SetInput (const char* a_expression, size_t a_lenght)
{
    casper::Scanner::SetInput(a_expression, a_lenght);
    %% write init;
}

casper::java::FakeJavaParser::token_type casper::java::FakeJavaScanner::Scan (casper::java::FakeJavaParser::semantic_type* o_val, casper::java::location* a_location)
{
    casper::java::FakeJavaParser::token_type ret = casper::java::FakeJavaParser::token::END;
    bool has_quotes = false;

    %% write exec;
    a_location->begin.line   = 1;
    a_location->begin.column = (int)(ts_ - input_);
    a_location->end.line     = 1;
    a_location->end.column   = (int)(te_ - input_ - 1);
    return ret;
}
