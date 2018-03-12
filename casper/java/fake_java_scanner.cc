
#line 1 "casper/java/fake_java_scanner.rl"
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

 
#line 34 "casper/java/fake_java_scanner.cc"
static const int casper_fake_java_scanner_start = 202;
static const int casper_fake_java_scanner_first_final = 202;
static const int casper_fake_java_scanner_error = 0;

static const int casper_fake_java_scanner_en_main = 202;


#line 181 "casper/java/fake_java_scanner.rl"


/**
 * @brief Constructor
 */
casper::java::FakeJavaScanner::FakeJavaScanner ()
{
    
#line 51 "casper/java/fake_java_scanner.cc"
	{
	(    cs_) = casper_fake_java_scanner_start;
	(    ts_) = 0;
	(    te_) = 0;
	(   act_) = 0;
	}

#line 189 "casper/java/fake_java_scanner.rl"
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
    
#line 83 "casper/java/fake_java_scanner.cc"
	{
	(    cs_) = casper_fake_java_scanner_start;
	(    ts_) = 0;
	(    te_) = 0;
	(   act_) = 0;
	}

#line 212 "casper/java/fake_java_scanner.rl"
}

casper::java::FakeJavaParser::token_type casper::java::FakeJavaScanner::Scan (casper::java::FakeJavaParser::semantic_type* o_val, casper::java::location* a_location)
{
    casper::java::FakeJavaParser::token_type ret = casper::java::FakeJavaParser::token::END;
    bool has_quotes = false;

    
#line 100 "casper/java/fake_java_scanner.cc"
	{
	if ( (     p_) == (    pe_) )
		goto _test_eof;
	switch ( (    cs_) )
	{
tr0:
#line 1 "NONE"
	{	switch( (   act_) ) {
	case 0:
	{{goto st0;}}
	break;
	case 63:
	{{(     p_) = (((    te_)))-1;}
                             if ( (int)(te_ - ts_) - 2 < 0 ) {
                                *o_val = "";
                                ret = (FakeJavaParser::token_type) '"';
                                {(     p_)++; (    cs_) = 202; goto _out;}
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
                                {(     p_)++; (    cs_) = 202; goto _out;}
                             }
                           }
	break;
	}
	}
	goto st202;
tr3:
#line 146 "casper/java/fake_java_scanner.rl"
	{{(     p_) = (((    te_)))-1;}{
                             if ( (int)(te_ - ts_) - 2 < 0 ) {
                                *o_val = "";
                                ret = (FakeJavaParser::token_type) '"';
                                {(     p_)++; (    cs_) = 202; goto _out;}
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
                                {(     p_)++; (    cs_) = 202; goto _out;}
                             }
                           }}
	goto st202;
tr12:
#line 128 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{
                                ret = FakeJavaParser::token::FIELD;
                                *o_val = std::string(ts_ + 3, te_ - ts_ - 4);
                                {(     p_)++; (    cs_) = 202; goto _out;}
                           }}
	goto st202;
tr15:
#line 134 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{
                                ret = FakeJavaParser::token::PARAMETER;
                                *o_val = std::string(ts_ + 3, te_ - ts_ - 4);
                                {(     p_)++; (    cs_) = 202; goto _out;}
                           }}
	goto st202;
tr18:
#line 122 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{
                                ret = FakeJavaParser::token::VARIABLE;
                                *o_val = std::string(ts_ + 3, te_ - ts_ - 4);
                                {(     p_)++; (    cs_) = 202; goto _out;}
                           }}
	goto st202;
tr19:
#line 116 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::AND       ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr20:
#line 140 "casper/java/fake_java_scanner.rl"
	{{(     p_) = (((    te_)))-1;}{
                                ret = FakeJavaParser::token::NUM;
                                *o_val = double_value_;
                                {(     p_)++; (    cs_) = 202; goto _out;}
                           }}
	goto st202;
tr24:
#line 115 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::EQ        ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr30:
#line 56 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::Boolean      ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr35:
#line 90 "casper/java/fake_java_scanner.rl"
	{{(     p_) = (((    te_)))-1;}{ ret = FakeJavaParser::token::TK_DATE      ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr40:
#line 91 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::TK_DATE_FORMAT; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr44:
#line 55 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::Double       ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr48:
#line 60 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::TK_FALSE     ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr54:
#line 57 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::Integer      ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr57:
#line 87 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::Math         ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr62:
#line 58 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::String       ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr65:
#line 59 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::TK_TRUE      ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr67:
#line 88 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::abs          ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr77:
#line 82 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::doubleValue  ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr85:
#line 78 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::endsWith     ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr89:
#line 73 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::equals       ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr95:
#line 62 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::TK_false     ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr103:
#line 83 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::doubleValue  ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr107:
#line 76 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::format       ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr115:
#line 89 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::indexOf      ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr120:
#line 80 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::intValue     ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr126:
#line 69 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::isEmpty      ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr128:
#line 86 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::isNaN        ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr134:
#line 70 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::length       ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr141:
#line 81 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::longValue    ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr144:
#line 92 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::TK_NEW        ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr146:
#line 63 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::TK_null      ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr151:
#line 68 "casper/java/fake_java_scanner.rl"
	{{(     p_) = (((    te_)))-1;}{ ret = FakeJavaParser::token::parse        ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr157:
#line 66 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::parseBoolean ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr162:
#line 65 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::parseDouble  ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr164:
#line 67 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::parseInt     ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr170:
#line 75 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::replace      ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr180:
#line 77 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::startsWith   ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr187:
#line 74 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::substring    ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr201:
#line 72 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::toLowerCase  ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr206:
#line 79 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::toString     ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr214:
#line 71 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::toUpperCase  ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr215:
#line 85 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::to_f         ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr216:
#line 84 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::to_i         ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr218:
#line 61 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::TK_true      ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr224:
#line 64 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::valueOf      ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr225:
#line 117 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::OR        ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr226:
#line 178 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;}
	goto st202;
tr230:
#line 97 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = (FakeJavaParser::token_type) '(' ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr231:
#line 98 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = (FakeJavaParser::token_type) ')' ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr232:
#line 101 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = (FakeJavaParser::token_type) '*' ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr233:
#line 99 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = (FakeJavaParser::token_type) '+' ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr234:
#line 109 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = (FakeJavaParser::token_type) ',' ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr235:
#line 100 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = (FakeJavaParser::token_type) '-' ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr236:
#line 108 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = (FakeJavaParser::token_type) '.' ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr237:
#line 102 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = (FakeJavaParser::token_type) '/' ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr239:
#line 103 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = (FakeJavaParser::token_type) ':' ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr243:
#line 105 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = (FakeJavaParser::token_type) '?' ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr264:
#line 110 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = (FakeJavaParser::token_type) '}' ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr265:
#line 104 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_);(     p_)--;{ ret = (FakeJavaParser::token_type) '!' ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr266:
#line 114 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::NE        ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr267:
#line 146 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_);(     p_)--;{
                             if ( (int)(te_ - ts_) - 2 < 0 ) {
                                *o_val = "";
                                ret = (FakeJavaParser::token_type) '"';
                                {(     p_)++; (    cs_) = 202; goto _out;}
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
                                {(     p_)++; (    cs_) = 202; goto _out;}
                             }
                           }}
	goto st202;
tr269:
#line 87 "casper/java/../../../osal/src/osal/ragelib/generic_number_parser.rlh"
	{
        if ( divider_ == 1 && exponent_ == 0 ) {
            integer_value_ = negative_ ? -integer_ : integer_;
            double_value_  = integer_value_;
        } else {
            if ( negative_ == false ) {
                double_value_ = integer_ + (double) fractional_ / (double) divider_;
            } else {
                double_value_ = -(integer_ + (double) fractional_ / (double) divider_);
            }
            if ( exponent_ != 0 ) {
                if ( negative_exponent_ == false ) {
                    double_value_ *= (double) osal::utils::Pow10((int)exponent_);
                } else {
                    double_value_ /= (double) osal::utils::Pow10((int)exponent_);
                }
            }
        }
    }
#line 140 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_);(     p_)--;{
                                ret = FakeJavaParser::token::NUM;
                                *o_val = double_value_;
                                {(     p_)++; (    cs_) = 202; goto _out;}
                           }}
	goto st202;
tr273:
#line 107 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_);(     p_)--;{ ret = (FakeJavaParser::token_type) '<' ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr274:
#line 112 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::LE        ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr275:
#line 106 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_);(     p_)--;{ ret = (FakeJavaParser::token_type) '>' ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr276:
#line 113 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_)+1;{ ret = FakeJavaParser::token::GE        ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr277:
#line 90 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_);(     p_)--;{ ret = FakeJavaParser::token::TK_DATE      ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
tr279:
#line 68 "casper/java/fake_java_scanner.rl"
	{(    te_) = (     p_);(     p_)--;{ ret = FakeJavaParser::token::parse        ; {(     p_)++; (    cs_) = 202; goto _out;} }}
	goto st202;
st202:
#line 1 "NONE"
	{(    ts_) = 0;}
#line 1 "NONE"
	{(   act_) = 0;}
	if ( ++(     p_) == (    pe_) )
		goto _test_eof202;
case 202:
#line 1 "NONE"
	{(    ts_) = (     p_);}
#line 533 "casper/java/fake_java_scanner.cc"
	switch( (*(     p_)) ) {
		case 32: goto tr226;
		case 33: goto st203;
		case 34: goto st1;
		case 36: goto st3;
		case 38: goto st13;
		case 40: goto tr230;
		case 41: goto tr231;
		case 42: goto tr232;
		case 43: goto tr233;
		case 44: goto tr234;
		case 45: goto tr235;
		case 46: goto tr236;
		case 47: goto tr237;
		case 58: goto tr239;
		case 60: goto st208;
		case 61: goto st17;
		case 62: goto st209;
		case 63: goto tr243;
		case 66: goto st18;
		case 68: goto st24;
		case 70: goto st36;
		case 73: goto st40;
		case 77: goto st46;
		case 83: goto st49;
		case 84: goto st54;
		case 97: goto st57;
		case 100: goto st59;
		case 101: goto st69;
		case 102: goto st80;
		case 105: goto st96;
		case 108: goto st114;
		case 110: goto st126;
		case 112: goto st130;
		case 114: goto st147;
		case 115: goto st153;
		case 116: goto st169;
		case 118: goto st195;
		case 124: goto st201;
		case 125: goto tr264;
	}
	if ( (*(     p_)) > 10 ) {
		if ( 48 <= (*(     p_)) && (*(     p_)) <= 57 )
			goto tr238;
	} else if ( (*(     p_)) >= 9 )
		goto tr226;
	goto st0;
st0:
(    cs_) = 0;
	goto _out;
st203:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof203;
case 203:
	if ( (*(     p_)) == 61 )
		goto tr266;
	goto tr265;
tr4:
#line 44 "casper/java/fake_java_scanner.rl"
	{ has_quotes = true; }
	goto st1;
st1:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof1;
case 1:
#line 599 "casper/java/fake_java_scanner.cc"
	if ( (*(     p_)) == 34 )
		goto tr2;
	goto st1;
tr2:
#line 1 "NONE"
	{(    te_) = (     p_)+1;}
#line 146 "casper/java/fake_java_scanner.rl"
	{(   act_) = 63;}
	goto st204;
tr5:
#line 1 "NONE"
	{(    te_) = (     p_)+1;}
#line 44 "casper/java/fake_java_scanner.rl"
	{ has_quotes = true; }
#line 146 "casper/java/fake_java_scanner.rl"
	{(   act_) = 63;}
	goto st204;
st204:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof204;
case 204:
#line 621 "casper/java/fake_java_scanner.cc"
	if ( (*(     p_)) == 34 )
		goto st2;
	goto tr267;
st2:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof2;
case 2:
	if ( (*(     p_)) == 34 )
		goto tr5;
	goto tr4;
st3:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof3;
case 3:
	switch( (*(     p_)) ) {
		case 70: goto st4;
		case 80: goto st7;
		case 86: goto st10;
	}
	goto st0;
st4:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof4;
case 4:
	switch( (*(     p_)) ) {
		case 40: goto st5;
		case 123: goto st5;
	}
	goto st0;
st5:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof5;
case 5:
	if ( (*(     p_)) == 95 )
		goto st6;
	if ( (*(     p_)) > 90 ) {
		if ( 97 <= (*(     p_)) && (*(     p_)) <= 122 )
			goto st6;
	} else if ( (*(     p_)) >= 65 )
		goto st6;
	goto st0;
st6:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof6;
case 6:
	switch( (*(     p_)) ) {
		case 35: goto st6;
		case 41: goto tr12;
		case 45: goto st6;
		case 63: goto st6;
		case 95: goto st6;
		case 125: goto tr12;
	}
	if ( (*(     p_)) < 65 ) {
		if ( 48 <= (*(     p_)) && (*(     p_)) <= 57 )
			goto st6;
	} else if ( (*(     p_)) > 90 ) {
		if ( 97 <= (*(     p_)) && (*(     p_)) <= 122 )
			goto st6;
	} else
		goto st6;
	goto st0;
st7:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof7;
case 7:
	switch( (*(     p_)) ) {
		case 40: goto st8;
		case 123: goto st8;
	}
	goto st0;
st8:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof8;
case 8:
	if ( (*(     p_)) == 95 )
		goto st9;
	if ( (*(     p_)) > 90 ) {
		if ( 97 <= (*(     p_)) && (*(     p_)) <= 122 )
			goto st9;
	} else if ( (*(     p_)) >= 65 )
		goto st9;
	goto st0;
st9:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof9;
case 9:
	switch( (*(     p_)) ) {
		case 35: goto st9;
		case 41: goto tr15;
		case 45: goto st9;
		case 63: goto st9;
		case 95: goto st9;
		case 125: goto tr15;
	}
	if ( (*(     p_)) < 65 ) {
		if ( 48 <= (*(     p_)) && (*(     p_)) <= 57 )
			goto st9;
	} else if ( (*(     p_)) > 90 ) {
		if ( 97 <= (*(     p_)) && (*(     p_)) <= 122 )
			goto st9;
	} else
		goto st9;
	goto st0;
st10:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof10;
case 10:
	switch( (*(     p_)) ) {
		case 40: goto st11;
		case 123: goto st11;
	}
	goto st0;
st11:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof11;
case 11:
	if ( (*(     p_)) == 95 )
		goto st12;
	if ( (*(     p_)) > 90 ) {
		if ( 97 <= (*(     p_)) && (*(     p_)) <= 122 )
			goto st12;
	} else if ( (*(     p_)) >= 65 )
		goto st12;
	goto st0;
st12:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof12;
case 12:
	switch( (*(     p_)) ) {
		case 35: goto st12;
		case 41: goto tr18;
		case 45: goto st12;
		case 63: goto st12;
		case 95: goto st12;
		case 125: goto tr18;
	}
	if ( (*(     p_)) < 65 ) {
		if ( 48 <= (*(     p_)) && (*(     p_)) <= 57 )
			goto st12;
	} else if ( (*(     p_)) > 90 ) {
		if ( 97 <= (*(     p_)) && (*(     p_)) <= 122 )
			goto st12;
	} else
		goto st12;
	goto st0;
st13:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof13;
case 13:
	if ( (*(     p_)) == 38 )
		goto tr19;
	goto st0;
tr238:
#line 1 "NONE"
	{(    te_) = (     p_)+1;}
#line 75 "casper/java/../../../osal/src/osal/ragelib/generic_number_parser.rlh"
	{
        negative_              = false;
        integer_               = 0;
        fractional_            = 0;
        fractional_digits_cnt_ = 0;
        fractional_digits_cnt_ = 0;
        divider_               = 1;
        negative_exponent_     = false;
        exponent_              = 0;
    }
#line 45 "casper/java/../../../osal/src/osal/ragelib/generic_number_parser.rlh"
	{
        integer_ *= 10;
        integer_ += ((*(     p_)) - '0');
    }
	goto st205;
tr271:
#line 1 "NONE"
	{(    te_) = (     p_)+1;}
#line 45 "casper/java/../../../osal/src/osal/ragelib/generic_number_parser.rlh"
	{
        integer_ *= 10;
        integer_ += ((*(     p_)) - '0');
    }
	goto st205;
st205:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof205;
case 205:
#line 808 "casper/java/fake_java_scanner.cc"
	switch( (*(     p_)) ) {
		case 46: goto st14;
		case 69: goto st15;
		case 101: goto st15;
	}
	if ( 48 <= (*(     p_)) && (*(     p_)) <= 57 )
		goto tr271;
	goto tr269;
st14:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof14;
case 14:
	if ( 48 <= (*(     p_)) && (*(     p_)) <= 57 )
		goto tr21;
	goto tr20;
tr21:
#line 1 "NONE"
	{(    te_) = (     p_)+1;}
#line 51 "casper/java/../../../osal/src/osal/ragelib/generic_number_parser.rlh"
	{
        if ( ( fractional_digits_cnt_ + 1 ) < k_max_fractional_digits_ ) {
            fractional_ *= 10;
            divider_    *= 10;
            fractional_ += ((*(     p_)) - '0');
            fractional_digits_cnt_++;
        }
    }
	goto st206;
st206:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof206;
case 206:
#line 841 "casper/java/fake_java_scanner.cc"
	switch( (*(     p_)) ) {
		case 69: goto st15;
		case 101: goto st15;
	}
	if ( 48 <= (*(     p_)) && (*(     p_)) <= 57 )
		goto tr21;
	goto tr269;
st15:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof15;
case 15:
	if ( (*(     p_)) == 45 )
		goto tr22;
	if ( 48 <= (*(     p_)) && (*(     p_)) <= 57 )
		goto tr23;
	goto tr20;
tr22:
#line 67 "casper/java/../../../osal/src/osal/ragelib/generic_number_parser.rlh"
	{
        if ( (*(     p_)) == '-' ) {
            negative_exponent_ = true;
        }
    }
	goto st16;
st16:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof16;
case 16:
#line 870 "casper/java/fake_java_scanner.cc"
	if ( 48 <= (*(     p_)) && (*(     p_)) <= 57 )
		goto tr23;
	goto tr20;
tr23:
#line 61 "casper/java/../../../osal/src/osal/ragelib/generic_number_parser.rlh"
	{
        exponent_ *= 10;
        exponent_ += ((*(     p_)) - '0');
    }
	goto st207;
st207:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof207;
case 207:
#line 885 "casper/java/fake_java_scanner.cc"
	if ( 48 <= (*(     p_)) && (*(     p_)) <= 57 )
		goto tr23;
	goto tr269;
st208:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof208;
case 208:
	if ( (*(     p_)) == 61 )
		goto tr274;
	goto tr273;
st17:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof17;
case 17:
	if ( (*(     p_)) == 61 )
		goto tr24;
	goto st0;
st209:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof209;
case 209:
	if ( (*(     p_)) == 61 )
		goto tr276;
	goto tr275;
st18:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof18;
case 18:
	if ( (*(     p_)) == 111 )
		goto st19;
	goto st0;
st19:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof19;
case 19:
	if ( (*(     p_)) == 111 )
		goto st20;
	goto st0;
st20:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof20;
case 20:
	if ( (*(     p_)) == 108 )
		goto st21;
	goto st0;
st21:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof21;
case 21:
	if ( (*(     p_)) == 101 )
		goto st22;
	goto st0;
st22:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof22;
case 22:
	if ( (*(     p_)) == 97 )
		goto st23;
	goto st0;
st23:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof23;
case 23:
	if ( (*(     p_)) == 110 )
		goto tr30;
	goto st0;
st24:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof24;
case 24:
	switch( (*(     p_)) ) {
		case 97: goto st25;
		case 111: goto st32;
	}
	goto st0;
st25:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof25;
case 25:
	if ( (*(     p_)) == 116 )
		goto st26;
	goto st0;
st26:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof26;
case 26:
	if ( (*(     p_)) == 101 )
		goto tr34;
	goto st0;
tr34:
#line 1 "NONE"
	{(    te_) = (     p_)+1;}
	goto st210;
st210:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof210;
case 210:
#line 983 "casper/java/fake_java_scanner.cc"
	if ( (*(     p_)) == 70 )
		goto st27;
	goto tr277;
st27:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof27;
case 27:
	if ( (*(     p_)) == 111 )
		goto st28;
	goto tr35;
st28:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof28;
case 28:
	if ( (*(     p_)) == 114 )
		goto st29;
	goto tr35;
st29:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof29;
case 29:
	if ( (*(     p_)) == 109 )
		goto st30;
	goto tr35;
st30:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof30;
case 30:
	if ( (*(     p_)) == 97 )
		goto st31;
	goto tr35;
st31:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof31;
case 31:
	if ( (*(     p_)) == 116 )
		goto tr40;
	goto tr35;
st32:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof32;
case 32:
	if ( (*(     p_)) == 117 )
		goto st33;
	goto st0;
st33:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof33;
case 33:
	if ( (*(     p_)) == 98 )
		goto st34;
	goto st0;
st34:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof34;
case 34:
	if ( (*(     p_)) == 108 )
		goto st35;
	goto st0;
st35:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof35;
case 35:
	if ( (*(     p_)) == 101 )
		goto tr44;
	goto st0;
st36:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof36;
case 36:
	if ( (*(     p_)) == 65 )
		goto st37;
	goto st0;
st37:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof37;
case 37:
	if ( (*(     p_)) == 76 )
		goto st38;
	goto st0;
st38:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof38;
case 38:
	if ( (*(     p_)) == 83 )
		goto st39;
	goto st0;
st39:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof39;
case 39:
	if ( (*(     p_)) == 69 )
		goto tr48;
	goto st0;
st40:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof40;
case 40:
	if ( (*(     p_)) == 110 )
		goto st41;
	goto st0;
st41:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof41;
case 41:
	if ( (*(     p_)) == 116 )
		goto st42;
	goto st0;
st42:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof42;
case 42:
	if ( (*(     p_)) == 101 )
		goto st43;
	goto st0;
st43:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof43;
case 43:
	if ( (*(     p_)) == 103 )
		goto st44;
	goto st0;
st44:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof44;
case 44:
	if ( (*(     p_)) == 101 )
		goto st45;
	goto st0;
st45:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof45;
case 45:
	if ( (*(     p_)) == 114 )
		goto tr54;
	goto st0;
st46:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof46;
case 46:
	if ( (*(     p_)) == 97 )
		goto st47;
	goto st0;
st47:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof47;
case 47:
	if ( (*(     p_)) == 116 )
		goto st48;
	goto st0;
st48:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof48;
case 48:
	if ( (*(     p_)) == 104 )
		goto tr57;
	goto st0;
st49:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof49;
case 49:
	if ( (*(     p_)) == 116 )
		goto st50;
	goto st0;
st50:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof50;
case 50:
	if ( (*(     p_)) == 114 )
		goto st51;
	goto st0;
st51:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof51;
case 51:
	if ( (*(     p_)) == 105 )
		goto st52;
	goto st0;
st52:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof52;
case 52:
	if ( (*(     p_)) == 110 )
		goto st53;
	goto st0;
st53:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof53;
case 53:
	if ( (*(     p_)) == 103 )
		goto tr62;
	goto st0;
st54:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof54;
case 54:
	if ( (*(     p_)) == 82 )
		goto st55;
	goto st0;
st55:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof55;
case 55:
	if ( (*(     p_)) == 85 )
		goto st56;
	goto st0;
st56:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof56;
case 56:
	if ( (*(     p_)) == 69 )
		goto tr65;
	goto st0;
st57:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof57;
case 57:
	if ( (*(     p_)) == 98 )
		goto st58;
	goto st0;
st58:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof58;
case 58:
	if ( (*(     p_)) == 115 )
		goto tr67;
	goto st0;
st59:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof59;
case 59:
	if ( (*(     p_)) == 111 )
		goto st60;
	goto st0;
st60:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof60;
case 60:
	if ( (*(     p_)) == 117 )
		goto st61;
	goto st0;
st61:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof61;
case 61:
	if ( (*(     p_)) == 98 )
		goto st62;
	goto st0;
st62:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof62;
case 62:
	if ( (*(     p_)) == 108 )
		goto st63;
	goto st0;
st63:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof63;
case 63:
	if ( (*(     p_)) == 101 )
		goto st64;
	goto st0;
st64:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof64;
case 64:
	if ( (*(     p_)) == 86 )
		goto st65;
	goto st0;
st65:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof65;
case 65:
	if ( (*(     p_)) == 97 )
		goto st66;
	goto st0;
st66:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof66;
case 66:
	if ( (*(     p_)) == 108 )
		goto st67;
	goto st0;
st67:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof67;
case 67:
	if ( (*(     p_)) == 117 )
		goto st68;
	goto st0;
st68:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof68;
case 68:
	if ( (*(     p_)) == 101 )
		goto tr77;
	goto st0;
st69:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof69;
case 69:
	switch( (*(     p_)) ) {
		case 110: goto st70;
		case 113: goto st76;
	}
	goto st0;
st70:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof70;
case 70:
	if ( (*(     p_)) == 100 )
		goto st71;
	goto st0;
st71:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof71;
case 71:
	if ( (*(     p_)) == 115 )
		goto st72;
	goto st0;
st72:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof72;
case 72:
	if ( (*(     p_)) == 87 )
		goto st73;
	goto st0;
st73:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof73;
case 73:
	if ( (*(     p_)) == 105 )
		goto st74;
	goto st0;
st74:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof74;
case 74:
	if ( (*(     p_)) == 116 )
		goto st75;
	goto st0;
st75:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof75;
case 75:
	if ( (*(     p_)) == 104 )
		goto tr85;
	goto st0;
st76:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof76;
case 76:
	if ( (*(     p_)) == 117 )
		goto st77;
	goto st0;
st77:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof77;
case 77:
	if ( (*(     p_)) == 97 )
		goto st78;
	goto st0;
st78:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof78;
case 78:
	if ( (*(     p_)) == 108 )
		goto st79;
	goto st0;
st79:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof79;
case 79:
	if ( (*(     p_)) == 115 )
		goto tr89;
	goto st0;
st80:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof80;
case 80:
	switch( (*(     p_)) ) {
		case 97: goto st81;
		case 108: goto st84;
		case 111: goto st92;
	}
	goto st0;
st81:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof81;
case 81:
	if ( (*(     p_)) == 108 )
		goto st82;
	goto st0;
st82:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof82;
case 82:
	if ( (*(     p_)) == 115 )
		goto st83;
	goto st0;
st83:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof83;
case 83:
	if ( (*(     p_)) == 101 )
		goto tr95;
	goto st0;
st84:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof84;
case 84:
	if ( (*(     p_)) == 111 )
		goto st85;
	goto st0;
st85:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof85;
case 85:
	if ( (*(     p_)) == 97 )
		goto st86;
	goto st0;
st86:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof86;
case 86:
	if ( (*(     p_)) == 116 )
		goto st87;
	goto st0;
st87:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof87;
case 87:
	if ( (*(     p_)) == 86 )
		goto st88;
	goto st0;
st88:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof88;
case 88:
	if ( (*(     p_)) == 97 )
		goto st89;
	goto st0;
st89:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof89;
case 89:
	if ( (*(     p_)) == 108 )
		goto st90;
	goto st0;
st90:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof90;
case 90:
	if ( (*(     p_)) == 117 )
		goto st91;
	goto st0;
st91:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof91;
case 91:
	if ( (*(     p_)) == 101 )
		goto tr103;
	goto st0;
st92:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof92;
case 92:
	if ( (*(     p_)) == 114 )
		goto st93;
	goto st0;
st93:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof93;
case 93:
	if ( (*(     p_)) == 109 )
		goto st94;
	goto st0;
st94:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof94;
case 94:
	if ( (*(     p_)) == 97 )
		goto st95;
	goto st0;
st95:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof95;
case 95:
	if ( (*(     p_)) == 116 )
		goto tr107;
	goto st0;
st96:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof96;
case 96:
	switch( (*(     p_)) ) {
		case 110: goto st97;
		case 115: goto st107;
	}
	goto st0;
st97:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof97;
case 97:
	switch( (*(     p_)) ) {
		case 100: goto st98;
		case 116: goto st102;
	}
	goto st0;
st98:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof98;
case 98:
	if ( (*(     p_)) == 101 )
		goto st99;
	goto st0;
st99:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof99;
case 99:
	if ( (*(     p_)) == 120 )
		goto st100;
	goto st0;
st100:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof100;
case 100:
	if ( (*(     p_)) == 79 )
		goto st101;
	goto st0;
st101:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof101;
case 101:
	if ( (*(     p_)) == 102 )
		goto tr115;
	goto st0;
st102:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof102;
case 102:
	if ( (*(     p_)) == 86 )
		goto st103;
	goto st0;
st103:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof103;
case 103:
	if ( (*(     p_)) == 97 )
		goto st104;
	goto st0;
st104:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof104;
case 104:
	if ( (*(     p_)) == 108 )
		goto st105;
	goto st0;
st105:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof105;
case 105:
	if ( (*(     p_)) == 117 )
		goto st106;
	goto st0;
st106:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof106;
case 106:
	if ( (*(     p_)) == 101 )
		goto tr120;
	goto st0;
st107:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof107;
case 107:
	switch( (*(     p_)) ) {
		case 69: goto st108;
		case 78: goto st112;
	}
	goto st0;
st108:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof108;
case 108:
	if ( (*(     p_)) == 109 )
		goto st109;
	goto st0;
st109:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof109;
case 109:
	if ( (*(     p_)) == 112 )
		goto st110;
	goto st0;
st110:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof110;
case 110:
	if ( (*(     p_)) == 116 )
		goto st111;
	goto st0;
st111:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof111;
case 111:
	if ( (*(     p_)) == 121 )
		goto tr126;
	goto st0;
st112:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof112;
case 112:
	if ( (*(     p_)) == 97 )
		goto st113;
	goto st0;
st113:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof113;
case 113:
	if ( (*(     p_)) == 78 )
		goto tr128;
	goto st0;
st114:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof114;
case 114:
	switch( (*(     p_)) ) {
		case 101: goto st115;
		case 111: goto st119;
	}
	goto st0;
st115:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof115;
case 115:
	if ( (*(     p_)) == 110 )
		goto st116;
	goto st0;
st116:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof116;
case 116:
	if ( (*(     p_)) == 103 )
		goto st117;
	goto st0;
st117:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof117;
case 117:
	if ( (*(     p_)) == 116 )
		goto st118;
	goto st0;
st118:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof118;
case 118:
	if ( (*(     p_)) == 104 )
		goto tr134;
	goto st0;
st119:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof119;
case 119:
	if ( (*(     p_)) == 110 )
		goto st120;
	goto st0;
st120:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof120;
case 120:
	if ( (*(     p_)) == 103 )
		goto st121;
	goto st0;
st121:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof121;
case 121:
	if ( (*(     p_)) == 86 )
		goto st122;
	goto st0;
st122:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof122;
case 122:
	if ( (*(     p_)) == 97 )
		goto st123;
	goto st0;
st123:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof123;
case 123:
	if ( (*(     p_)) == 108 )
		goto st124;
	goto st0;
st124:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof124;
case 124:
	if ( (*(     p_)) == 117 )
		goto st125;
	goto st0;
st125:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof125;
case 125:
	if ( (*(     p_)) == 101 )
		goto tr141;
	goto st0;
st126:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof126;
case 126:
	switch( (*(     p_)) ) {
		case 101: goto st127;
		case 117: goto st128;
	}
	goto st0;
st127:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof127;
case 127:
	if ( (*(     p_)) == 119 )
		goto tr144;
	goto st0;
st128:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof128;
case 128:
	if ( (*(     p_)) == 108 )
		goto st129;
	goto st0;
st129:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof129;
case 129:
	if ( (*(     p_)) == 108 )
		goto tr146;
	goto st0;
st130:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof130;
case 130:
	if ( (*(     p_)) == 97 )
		goto st131;
	goto st0;
st131:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof131;
case 131:
	if ( (*(     p_)) == 114 )
		goto st132;
	goto st0;
st132:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof132;
case 132:
	if ( (*(     p_)) == 115 )
		goto st133;
	goto st0;
st133:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof133;
case 133:
	if ( (*(     p_)) == 101 )
		goto tr150;
	goto st0;
tr150:
#line 1 "NONE"
	{(    te_) = (     p_)+1;}
	goto st211;
st211:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof211;
case 211:
#line 1759 "casper/java/fake_java_scanner.cc"
	switch( (*(     p_)) ) {
		case 66: goto st134;
		case 68: goto st140;
		case 73: goto st145;
	}
	goto tr279;
st134:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof134;
case 134:
	if ( (*(     p_)) == 111 )
		goto st135;
	goto tr151;
st135:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof135;
case 135:
	if ( (*(     p_)) == 111 )
		goto st136;
	goto tr151;
st136:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof136;
case 136:
	if ( (*(     p_)) == 108 )
		goto st137;
	goto tr151;
st137:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof137;
case 137:
	if ( (*(     p_)) == 101 )
		goto st138;
	goto tr151;
st138:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof138;
case 138:
	if ( (*(     p_)) == 97 )
		goto st139;
	goto tr151;
st139:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof139;
case 139:
	if ( (*(     p_)) == 110 )
		goto tr157;
	goto tr151;
st140:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof140;
case 140:
	if ( (*(     p_)) == 111 )
		goto st141;
	goto tr151;
st141:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof141;
case 141:
	if ( (*(     p_)) == 117 )
		goto st142;
	goto tr151;
st142:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof142;
case 142:
	if ( (*(     p_)) == 98 )
		goto st143;
	goto tr151;
st143:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof143;
case 143:
	if ( (*(     p_)) == 108 )
		goto st144;
	goto tr151;
st144:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof144;
case 144:
	if ( (*(     p_)) == 101 )
		goto tr162;
	goto tr151;
st145:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof145;
case 145:
	if ( (*(     p_)) == 110 )
		goto st146;
	goto tr151;
st146:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof146;
case 146:
	if ( (*(     p_)) == 116 )
		goto tr164;
	goto tr151;
st147:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof147;
case 147:
	if ( (*(     p_)) == 101 )
		goto st148;
	goto st0;
st148:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof148;
case 148:
	if ( (*(     p_)) == 112 )
		goto st149;
	goto st0;
st149:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof149;
case 149:
	if ( (*(     p_)) == 108 )
		goto st150;
	goto st0;
st150:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof150;
case 150:
	if ( (*(     p_)) == 97 )
		goto st151;
	goto st0;
st151:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof151;
case 151:
	if ( (*(     p_)) == 99 )
		goto st152;
	goto st0;
st152:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof152;
case 152:
	if ( (*(     p_)) == 101 )
		goto tr170;
	goto st0;
st153:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof153;
case 153:
	switch( (*(     p_)) ) {
		case 116: goto st154;
		case 117: goto st162;
	}
	goto st0;
st154:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof154;
case 154:
	if ( (*(     p_)) == 97 )
		goto st155;
	goto st0;
st155:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof155;
case 155:
	if ( (*(     p_)) == 114 )
		goto st156;
	goto st0;
st156:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof156;
case 156:
	if ( (*(     p_)) == 116 )
		goto st157;
	goto st0;
st157:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof157;
case 157:
	if ( (*(     p_)) == 115 )
		goto st158;
	goto st0;
st158:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof158;
case 158:
	if ( (*(     p_)) == 87 )
		goto st159;
	goto st0;
st159:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof159;
case 159:
	if ( (*(     p_)) == 105 )
		goto st160;
	goto st0;
st160:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof160;
case 160:
	if ( (*(     p_)) == 116 )
		goto st161;
	goto st0;
st161:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof161;
case 161:
	if ( (*(     p_)) == 104 )
		goto tr180;
	goto st0;
st162:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof162;
case 162:
	if ( (*(     p_)) == 98 )
		goto st163;
	goto st0;
st163:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof163;
case 163:
	if ( (*(     p_)) == 115 )
		goto st164;
	goto st0;
st164:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof164;
case 164:
	if ( (*(     p_)) == 116 )
		goto st165;
	goto st0;
st165:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof165;
case 165:
	if ( (*(     p_)) == 114 )
		goto st166;
	goto st0;
st166:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof166;
case 166:
	if ( (*(     p_)) == 105 )
		goto st167;
	goto st0;
st167:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof167;
case 167:
	if ( (*(     p_)) == 110 )
		goto st168;
	goto st0;
st168:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof168;
case 168:
	if ( (*(     p_)) == 103 )
		goto tr187;
	goto st0;
st169:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof169;
case 169:
	switch( (*(     p_)) ) {
		case 111: goto st170;
		case 114: goto st193;
	}
	goto st0;
st170:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof170;
case 170:
	switch( (*(     p_)) ) {
		case 76: goto st171;
		case 83: goto st179;
		case 85: goto st184;
		case 95: goto st192;
	}
	goto st0;
st171:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof171;
case 171:
	if ( (*(     p_)) == 111 )
		goto st172;
	goto st0;
st172:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof172;
case 172:
	if ( (*(     p_)) == 119 )
		goto st173;
	goto st0;
st173:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof173;
case 173:
	if ( (*(     p_)) == 101 )
		goto st174;
	goto st0;
st174:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof174;
case 174:
	if ( (*(     p_)) == 114 )
		goto st175;
	goto st0;
st175:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof175;
case 175:
	if ( (*(     p_)) == 67 )
		goto st176;
	goto st0;
st176:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof176;
case 176:
	if ( (*(     p_)) == 97 )
		goto st177;
	goto st0;
st177:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof177;
case 177:
	if ( (*(     p_)) == 115 )
		goto st178;
	goto st0;
st178:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof178;
case 178:
	if ( (*(     p_)) == 101 )
		goto tr201;
	goto st0;
st179:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof179;
case 179:
	if ( (*(     p_)) == 116 )
		goto st180;
	goto st0;
st180:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof180;
case 180:
	if ( (*(     p_)) == 114 )
		goto st181;
	goto st0;
st181:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof181;
case 181:
	if ( (*(     p_)) == 105 )
		goto st182;
	goto st0;
st182:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof182;
case 182:
	if ( (*(     p_)) == 110 )
		goto st183;
	goto st0;
st183:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof183;
case 183:
	if ( (*(     p_)) == 103 )
		goto tr206;
	goto st0;
st184:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof184;
case 184:
	if ( (*(     p_)) == 112 )
		goto st185;
	goto st0;
st185:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof185;
case 185:
	if ( (*(     p_)) == 112 )
		goto st186;
	goto st0;
st186:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof186;
case 186:
	if ( (*(     p_)) == 101 )
		goto st187;
	goto st0;
st187:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof187;
case 187:
	if ( (*(     p_)) == 114 )
		goto st188;
	goto st0;
st188:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof188;
case 188:
	if ( (*(     p_)) == 67 )
		goto st189;
	goto st0;
st189:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof189;
case 189:
	if ( (*(     p_)) == 97 )
		goto st190;
	goto st0;
st190:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof190;
case 190:
	if ( (*(     p_)) == 115 )
		goto st191;
	goto st0;
st191:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof191;
case 191:
	if ( (*(     p_)) == 101 )
		goto tr214;
	goto st0;
st192:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof192;
case 192:
	switch( (*(     p_)) ) {
		case 102: goto tr215;
		case 105: goto tr216;
	}
	goto st0;
st193:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof193;
case 193:
	if ( (*(     p_)) == 117 )
		goto st194;
	goto st0;
st194:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof194;
case 194:
	if ( (*(     p_)) == 101 )
		goto tr218;
	goto st0;
st195:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof195;
case 195:
	if ( (*(     p_)) == 97 )
		goto st196;
	goto st0;
st196:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof196;
case 196:
	if ( (*(     p_)) == 108 )
		goto st197;
	goto st0;
st197:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof197;
case 197:
	if ( (*(     p_)) == 117 )
		goto st198;
	goto st0;
st198:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof198;
case 198:
	if ( (*(     p_)) == 101 )
		goto st199;
	goto st0;
st199:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof199;
case 199:
	if ( (*(     p_)) == 79 )
		goto st200;
	goto st0;
st200:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof200;
case 200:
	if ( (*(     p_)) == 102 )
		goto tr224;
	goto st0;
st201:
	if ( ++(     p_) == (    pe_) )
		goto _test_eof201;
case 201:
	if ( (*(     p_)) == 124 )
		goto tr225;
	goto st0;
	}
	_test_eof202: (    cs_) = 202; goto _test_eof; 
	_test_eof203: (    cs_) = 203; goto _test_eof; 
	_test_eof1: (    cs_) = 1; goto _test_eof; 
	_test_eof204: (    cs_) = 204; goto _test_eof; 
	_test_eof2: (    cs_) = 2; goto _test_eof; 
	_test_eof3: (    cs_) = 3; goto _test_eof; 
	_test_eof4: (    cs_) = 4; goto _test_eof; 
	_test_eof5: (    cs_) = 5; goto _test_eof; 
	_test_eof6: (    cs_) = 6; goto _test_eof; 
	_test_eof7: (    cs_) = 7; goto _test_eof; 
	_test_eof8: (    cs_) = 8; goto _test_eof; 
	_test_eof9: (    cs_) = 9; goto _test_eof; 
	_test_eof10: (    cs_) = 10; goto _test_eof; 
	_test_eof11: (    cs_) = 11; goto _test_eof; 
	_test_eof12: (    cs_) = 12; goto _test_eof; 
	_test_eof13: (    cs_) = 13; goto _test_eof; 
	_test_eof205: (    cs_) = 205; goto _test_eof; 
	_test_eof14: (    cs_) = 14; goto _test_eof; 
	_test_eof206: (    cs_) = 206; goto _test_eof; 
	_test_eof15: (    cs_) = 15; goto _test_eof; 
	_test_eof16: (    cs_) = 16; goto _test_eof; 
	_test_eof207: (    cs_) = 207; goto _test_eof; 
	_test_eof208: (    cs_) = 208; goto _test_eof; 
	_test_eof17: (    cs_) = 17; goto _test_eof; 
	_test_eof209: (    cs_) = 209; goto _test_eof; 
	_test_eof18: (    cs_) = 18; goto _test_eof; 
	_test_eof19: (    cs_) = 19; goto _test_eof; 
	_test_eof20: (    cs_) = 20; goto _test_eof; 
	_test_eof21: (    cs_) = 21; goto _test_eof; 
	_test_eof22: (    cs_) = 22; goto _test_eof; 
	_test_eof23: (    cs_) = 23; goto _test_eof; 
	_test_eof24: (    cs_) = 24; goto _test_eof; 
	_test_eof25: (    cs_) = 25; goto _test_eof; 
	_test_eof26: (    cs_) = 26; goto _test_eof; 
	_test_eof210: (    cs_) = 210; goto _test_eof; 
	_test_eof27: (    cs_) = 27; goto _test_eof; 
	_test_eof28: (    cs_) = 28; goto _test_eof; 
	_test_eof29: (    cs_) = 29; goto _test_eof; 
	_test_eof30: (    cs_) = 30; goto _test_eof; 
	_test_eof31: (    cs_) = 31; goto _test_eof; 
	_test_eof32: (    cs_) = 32; goto _test_eof; 
	_test_eof33: (    cs_) = 33; goto _test_eof; 
	_test_eof34: (    cs_) = 34; goto _test_eof; 
	_test_eof35: (    cs_) = 35; goto _test_eof; 
	_test_eof36: (    cs_) = 36; goto _test_eof; 
	_test_eof37: (    cs_) = 37; goto _test_eof; 
	_test_eof38: (    cs_) = 38; goto _test_eof; 
	_test_eof39: (    cs_) = 39; goto _test_eof; 
	_test_eof40: (    cs_) = 40; goto _test_eof; 
	_test_eof41: (    cs_) = 41; goto _test_eof; 
	_test_eof42: (    cs_) = 42; goto _test_eof; 
	_test_eof43: (    cs_) = 43; goto _test_eof; 
	_test_eof44: (    cs_) = 44; goto _test_eof; 
	_test_eof45: (    cs_) = 45; goto _test_eof; 
	_test_eof46: (    cs_) = 46; goto _test_eof; 
	_test_eof47: (    cs_) = 47; goto _test_eof; 
	_test_eof48: (    cs_) = 48; goto _test_eof; 
	_test_eof49: (    cs_) = 49; goto _test_eof; 
	_test_eof50: (    cs_) = 50; goto _test_eof; 
	_test_eof51: (    cs_) = 51; goto _test_eof; 
	_test_eof52: (    cs_) = 52; goto _test_eof; 
	_test_eof53: (    cs_) = 53; goto _test_eof; 
	_test_eof54: (    cs_) = 54; goto _test_eof; 
	_test_eof55: (    cs_) = 55; goto _test_eof; 
	_test_eof56: (    cs_) = 56; goto _test_eof; 
	_test_eof57: (    cs_) = 57; goto _test_eof; 
	_test_eof58: (    cs_) = 58; goto _test_eof; 
	_test_eof59: (    cs_) = 59; goto _test_eof; 
	_test_eof60: (    cs_) = 60; goto _test_eof; 
	_test_eof61: (    cs_) = 61; goto _test_eof; 
	_test_eof62: (    cs_) = 62; goto _test_eof; 
	_test_eof63: (    cs_) = 63; goto _test_eof; 
	_test_eof64: (    cs_) = 64; goto _test_eof; 
	_test_eof65: (    cs_) = 65; goto _test_eof; 
	_test_eof66: (    cs_) = 66; goto _test_eof; 
	_test_eof67: (    cs_) = 67; goto _test_eof; 
	_test_eof68: (    cs_) = 68; goto _test_eof; 
	_test_eof69: (    cs_) = 69; goto _test_eof; 
	_test_eof70: (    cs_) = 70; goto _test_eof; 
	_test_eof71: (    cs_) = 71; goto _test_eof; 
	_test_eof72: (    cs_) = 72; goto _test_eof; 
	_test_eof73: (    cs_) = 73; goto _test_eof; 
	_test_eof74: (    cs_) = 74; goto _test_eof; 
	_test_eof75: (    cs_) = 75; goto _test_eof; 
	_test_eof76: (    cs_) = 76; goto _test_eof; 
	_test_eof77: (    cs_) = 77; goto _test_eof; 
	_test_eof78: (    cs_) = 78; goto _test_eof; 
	_test_eof79: (    cs_) = 79; goto _test_eof; 
	_test_eof80: (    cs_) = 80; goto _test_eof; 
	_test_eof81: (    cs_) = 81; goto _test_eof; 
	_test_eof82: (    cs_) = 82; goto _test_eof; 
	_test_eof83: (    cs_) = 83; goto _test_eof; 
	_test_eof84: (    cs_) = 84; goto _test_eof; 
	_test_eof85: (    cs_) = 85; goto _test_eof; 
	_test_eof86: (    cs_) = 86; goto _test_eof; 
	_test_eof87: (    cs_) = 87; goto _test_eof; 
	_test_eof88: (    cs_) = 88; goto _test_eof; 
	_test_eof89: (    cs_) = 89; goto _test_eof; 
	_test_eof90: (    cs_) = 90; goto _test_eof; 
	_test_eof91: (    cs_) = 91; goto _test_eof; 
	_test_eof92: (    cs_) = 92; goto _test_eof; 
	_test_eof93: (    cs_) = 93; goto _test_eof; 
	_test_eof94: (    cs_) = 94; goto _test_eof; 
	_test_eof95: (    cs_) = 95; goto _test_eof; 
	_test_eof96: (    cs_) = 96; goto _test_eof; 
	_test_eof97: (    cs_) = 97; goto _test_eof; 
	_test_eof98: (    cs_) = 98; goto _test_eof; 
	_test_eof99: (    cs_) = 99; goto _test_eof; 
	_test_eof100: (    cs_) = 100; goto _test_eof; 
	_test_eof101: (    cs_) = 101; goto _test_eof; 
	_test_eof102: (    cs_) = 102; goto _test_eof; 
	_test_eof103: (    cs_) = 103; goto _test_eof; 
	_test_eof104: (    cs_) = 104; goto _test_eof; 
	_test_eof105: (    cs_) = 105; goto _test_eof; 
	_test_eof106: (    cs_) = 106; goto _test_eof; 
	_test_eof107: (    cs_) = 107; goto _test_eof; 
	_test_eof108: (    cs_) = 108; goto _test_eof; 
	_test_eof109: (    cs_) = 109; goto _test_eof; 
	_test_eof110: (    cs_) = 110; goto _test_eof; 
	_test_eof111: (    cs_) = 111; goto _test_eof; 
	_test_eof112: (    cs_) = 112; goto _test_eof; 
	_test_eof113: (    cs_) = 113; goto _test_eof; 
	_test_eof114: (    cs_) = 114; goto _test_eof; 
	_test_eof115: (    cs_) = 115; goto _test_eof; 
	_test_eof116: (    cs_) = 116; goto _test_eof; 
	_test_eof117: (    cs_) = 117; goto _test_eof; 
	_test_eof118: (    cs_) = 118; goto _test_eof; 
	_test_eof119: (    cs_) = 119; goto _test_eof; 
	_test_eof120: (    cs_) = 120; goto _test_eof; 
	_test_eof121: (    cs_) = 121; goto _test_eof; 
	_test_eof122: (    cs_) = 122; goto _test_eof; 
	_test_eof123: (    cs_) = 123; goto _test_eof; 
	_test_eof124: (    cs_) = 124; goto _test_eof; 
	_test_eof125: (    cs_) = 125; goto _test_eof; 
	_test_eof126: (    cs_) = 126; goto _test_eof; 
	_test_eof127: (    cs_) = 127; goto _test_eof; 
	_test_eof128: (    cs_) = 128; goto _test_eof; 
	_test_eof129: (    cs_) = 129; goto _test_eof; 
	_test_eof130: (    cs_) = 130; goto _test_eof; 
	_test_eof131: (    cs_) = 131; goto _test_eof; 
	_test_eof132: (    cs_) = 132; goto _test_eof; 
	_test_eof133: (    cs_) = 133; goto _test_eof; 
	_test_eof211: (    cs_) = 211; goto _test_eof; 
	_test_eof134: (    cs_) = 134; goto _test_eof; 
	_test_eof135: (    cs_) = 135; goto _test_eof; 
	_test_eof136: (    cs_) = 136; goto _test_eof; 
	_test_eof137: (    cs_) = 137; goto _test_eof; 
	_test_eof138: (    cs_) = 138; goto _test_eof; 
	_test_eof139: (    cs_) = 139; goto _test_eof; 
	_test_eof140: (    cs_) = 140; goto _test_eof; 
	_test_eof141: (    cs_) = 141; goto _test_eof; 
	_test_eof142: (    cs_) = 142; goto _test_eof; 
	_test_eof143: (    cs_) = 143; goto _test_eof; 
	_test_eof144: (    cs_) = 144; goto _test_eof; 
	_test_eof145: (    cs_) = 145; goto _test_eof; 
	_test_eof146: (    cs_) = 146; goto _test_eof; 
	_test_eof147: (    cs_) = 147; goto _test_eof; 
	_test_eof148: (    cs_) = 148; goto _test_eof; 
	_test_eof149: (    cs_) = 149; goto _test_eof; 
	_test_eof150: (    cs_) = 150; goto _test_eof; 
	_test_eof151: (    cs_) = 151; goto _test_eof; 
	_test_eof152: (    cs_) = 152; goto _test_eof; 
	_test_eof153: (    cs_) = 153; goto _test_eof; 
	_test_eof154: (    cs_) = 154; goto _test_eof; 
	_test_eof155: (    cs_) = 155; goto _test_eof; 
	_test_eof156: (    cs_) = 156; goto _test_eof; 
	_test_eof157: (    cs_) = 157; goto _test_eof; 
	_test_eof158: (    cs_) = 158; goto _test_eof; 
	_test_eof159: (    cs_) = 159; goto _test_eof; 
	_test_eof160: (    cs_) = 160; goto _test_eof; 
	_test_eof161: (    cs_) = 161; goto _test_eof; 
	_test_eof162: (    cs_) = 162; goto _test_eof; 
	_test_eof163: (    cs_) = 163; goto _test_eof; 
	_test_eof164: (    cs_) = 164; goto _test_eof; 
	_test_eof165: (    cs_) = 165; goto _test_eof; 
	_test_eof166: (    cs_) = 166; goto _test_eof; 
	_test_eof167: (    cs_) = 167; goto _test_eof; 
	_test_eof168: (    cs_) = 168; goto _test_eof; 
	_test_eof169: (    cs_) = 169; goto _test_eof; 
	_test_eof170: (    cs_) = 170; goto _test_eof; 
	_test_eof171: (    cs_) = 171; goto _test_eof; 
	_test_eof172: (    cs_) = 172; goto _test_eof; 
	_test_eof173: (    cs_) = 173; goto _test_eof; 
	_test_eof174: (    cs_) = 174; goto _test_eof; 
	_test_eof175: (    cs_) = 175; goto _test_eof; 
	_test_eof176: (    cs_) = 176; goto _test_eof; 
	_test_eof177: (    cs_) = 177; goto _test_eof; 
	_test_eof178: (    cs_) = 178; goto _test_eof; 
	_test_eof179: (    cs_) = 179; goto _test_eof; 
	_test_eof180: (    cs_) = 180; goto _test_eof; 
	_test_eof181: (    cs_) = 181; goto _test_eof; 
	_test_eof182: (    cs_) = 182; goto _test_eof; 
	_test_eof183: (    cs_) = 183; goto _test_eof; 
	_test_eof184: (    cs_) = 184; goto _test_eof; 
	_test_eof185: (    cs_) = 185; goto _test_eof; 
	_test_eof186: (    cs_) = 186; goto _test_eof; 
	_test_eof187: (    cs_) = 187; goto _test_eof; 
	_test_eof188: (    cs_) = 188; goto _test_eof; 
	_test_eof189: (    cs_) = 189; goto _test_eof; 
	_test_eof190: (    cs_) = 190; goto _test_eof; 
	_test_eof191: (    cs_) = 191; goto _test_eof; 
	_test_eof192: (    cs_) = 192; goto _test_eof; 
	_test_eof193: (    cs_) = 193; goto _test_eof; 
	_test_eof194: (    cs_) = 194; goto _test_eof; 
	_test_eof195: (    cs_) = 195; goto _test_eof; 
	_test_eof196: (    cs_) = 196; goto _test_eof; 
	_test_eof197: (    cs_) = 197; goto _test_eof; 
	_test_eof198: (    cs_) = 198; goto _test_eof; 
	_test_eof199: (    cs_) = 199; goto _test_eof; 
	_test_eof200: (    cs_) = 200; goto _test_eof; 
	_test_eof201: (    cs_) = 201; goto _test_eof; 

	_test_eof: {}
	if ( (     p_) == (   eof_) )
	{
	switch ( (    cs_) ) {
	case 203: goto tr265;
	case 1: goto tr0;
	case 204: goto tr267;
	case 2: goto tr3;
	case 205: goto tr269;
	case 14: goto tr20;
	case 206: goto tr269;
	case 15: goto tr20;
	case 16: goto tr20;
	case 207: goto tr269;
	case 208: goto tr273;
	case 209: goto tr275;
	case 210: goto tr277;
	case 27: goto tr35;
	case 28: goto tr35;
	case 29: goto tr35;
	case 30: goto tr35;
	case 31: goto tr35;
	case 211: goto tr279;
	case 134: goto tr151;
	case 135: goto tr151;
	case 136: goto tr151;
	case 137: goto tr151;
	case 138: goto tr151;
	case 139: goto tr151;
	case 140: goto tr151;
	case 141: goto tr151;
	case 142: goto tr151;
	case 143: goto tr151;
	case 144: goto tr151;
	case 145: goto tr151;
	case 146: goto tr151;
	}
	}

	_out: {}
	}

#line 220 "casper/java/fake_java_scanner.rl"
    a_location->begin.line   = 1;
    a_location->begin.column = (int)(ts_ - input_);
    a_location->end.line     = 1;
    a_location->end.column   = (int)(te_ - input_ - 1);
    return ret;
}
