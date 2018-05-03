/**
 * @file fake_java_parser.yy
 *
 * Copyright (c) 2011-2018 Cloudware S.A. All rights reserved.
 *
 * This file is part of jayscriptor.
 *
 * jayscriptor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * jayscriptor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with jayscriptor.  If not, see <http://www.gnu.org/licenses/>.
 */

%skeleton "lalr1.cc"
%require "3.0"
%defines
%define api.namespace  { casper::java }
%define api.value.type { class AstNode* }
%define parser_class_name { FakeJavaParser }

%code requires {
  namespace casper {
      namespace java {
          class FakeJavaScanner;
          class FakeJavaExpression;
      }
  }
  #include <cmath>
  #include <iostream>
  #include "casper/java/ast.h"
  #include <stdio.h>
  #include <exception>
}

%parse-param { Ast& ast } { casper::java::FakeJavaScanner& scanner_ } { casper::java::FakeJavaExpression& expr_ }

%code {
  #include "casper/java/fake_java_scanner.h"
  #include "casper/java/fake_java_expression.h"
  #define yylex scanner_.Scan
}

%token END           0
%token abs           "abs"
%token Double        "Double"
%token Boolean       "Boolean"
%token Integer       "Integer"
%token String        "String"
%token TK_TRUE       "TRUE"
%token TK_FALSE      "FALSE"
%token TK_true       "true"
%token TK_false      "false"
%token TK_null       "null"
%token valueOf       "valueOf"
%token parseDouble   "parseDouble"
%token parseBoolean  "parseBoolean"
%token parseInt      "parseInt"
%token parse         "parse"
%token isEmpty       "isEmpty"
%token length        "length"
%token toUpperCase   "toUpperCase"
%token toLowerCase   "toLowerCase"
%token replace       "replace"
%token equals        "equals"
%token substring     "substring"
%token format        "format"
%token startsWith    "startsWith"
%token endsWith      "endsWith"
%token indexOf       "indexOf"
%token toString      "toString"
%token intValue      "intValue"
%token longValue     "longValue"
%token doubleValue   "doubleValue"
%token floatValue    "floatValue"
%token to_i          "to_i"
%token to_f          "to_f"
%token isNaN         "isNaN"
%token Math          "Math"
%token NUM           "Number"
%token VAR           "Variable"
%token TEXTLITERAL   "Literal string"
%token LE            "<="
%token GE            ">="
%token NE            "!="
%token EQ            "=="
%token OR            "||"
%token AND           "&&"
%token VARIABLE      "$V{"
%token PARAMETER     "$P{"
%token FIELD         "$F{"
%token TK_NEW        "new"
%token TK_DATE       "Date"
%token TK_DATE_FORMAT "DateFormat"

%right '?' ':'
%left  OR
%left  AND
%left  '|'
%left  '^'
%left  '&'
%left  EQ NE
%left  '<' '>' LE GE
%left  '-' '+'
%left  '*' '/' '%'
%right '!' UMINUS UPLUS
%left  '.'

/*
 * The grammar follows
 */
%%
    input:
           END
         | term END                       { ast.root_ = $1;                          }
         ;

    term:
           expressions
         | generic_ops
         | string_ops
         | integer_ops
         | boolean_ops
         | double_ops
         | date_ops
         | leaf_terminals
         ;

   leaf_terminals:
                 NUM                      { $$ = ast.NewAstNode($1->num_);                                       }
                 | TEXTLITERAL            { $$ = ast.NewAstNode($1->text_);                                      }
                 | TK_null                { $$ = ast.NewAstNode(casper::java::AstNode::Type::TNull);             }
                 | VARIABLE               { $$ = ast.NewAstNode(casper::java::AstNode::Type::TVar, $1->text_);   }
                 | FIELD                  { $$ = ast.NewAstNode(casper::java::AstNode::Type::TField, $1->text_); }
                 | PARAMETER              { $$ = ast.NewAstNode(casper::java::AstNode::Type::TParam, $1->text_); }
                 ;

    expressions:
                '(' term ')'              { $2->pare_ = true; $$ = $2;          }
              | term '+' term             { $$ = ast.Expression("+",$1,$3);     }
              | term '-' term             { $$ = ast.Expression("-",$1,$3);     }
              | term '*' term             { $$ = ast.Expression("*",$1,$3);     }
              | term '/' term             { $$ = ast.Expression("/",$1,$3);     }
              | term '^' term             { $$ = ast.Expression("^",$1,$3);     }
              | term '%' term             { $$ = ast.Expression("%",$1,$3);     }
              | term '>' term             { $$ = ast.Expression(">",$1,$3);     }
              | term '<' term             { $$ = ast.Expression("<",$1,$3);     }
              | term  GE term             { $$ = ast.Expression(">=",$1,$3);    }
              | term  LE term             { $$ = ast.Expression("<=",$1,$3);    }
              | term  NE term             { $$ = ast.Expression("!=",$1,$3);    }
              | term  EQ term             { $$ = ast.Expression("==",$1,$3);    }
              | term  OR term             { $$ = ast.Expression("||",$1,$3);    }
              | term AND term             { $$ = ast.Expression("&&",$1,$3);    }
              | term '?' term ':' term    { $$ = ast.If($1, $3, $5);            }
              | '-' term %prec UMINUS     { $$ = ast.Expression("UM",$2,$2);    }
              | '+' term %prec UPLUS      { $$ = $2;                            }
              | '!' term                  { $$ = ast.Expression("!",$2,$2);     }
              ;
    generic_ops:
                 term '.' equals      '(' term ')'  { $$=ast.Expression("==",$1,$5);            }
               | term '.' toString    '(' ')'       { $$=ast.Operation("toString",$1);          }
               | term '.' intValue    '(' ')'       { $$=ast.Operation("parseInt",$1);          }
               | term '.' to_i        '(' ')'       { $$=ast.Operation("to_i",$1);              }
               | term '.' to_f        '(' ')'       { $$=ast.Operation("to_f",$1);              }
               | term '.' doubleValue '(' ')'       { $$=ast.Operation("parseFloat",$1);        }
               | term '.' isNaN       '(' ')'       { $$=ast.Operation("isNan",$1);             }
               ;

    string_ops:
                term '.' isEmpty     '(' ')'               { $$=ast.StrOp("IsEmpty",$1);        }
              | term '.' length      '(' ')'               { $$=ast.StrOp("length",$1);         }
              | term '.' toUpperCase '(' ')'               { $$=ast.StrOp("toUpperCase",$1);    }
              | term '.' toLowerCase '(' ')'               { $$=ast.StrOp("toLowerCase",$1);    }
              | term '.' substring   '(' term ',' term ')' { $$=ast.StrOp("substring",$1,$5,$7);}
              | term '.' substring   '(' term ')'          { $$=ast.StrOp("substring",$1,$5);   }
              | term '.' indexOf     '(' term ')'          { $$=ast.StrOp("indexOf",$1,$5);     }
              | term '.' replace     '(' term ',' term ')' { $$=ast.StrOp("replace",$1,$5,$7);  }
              ;
    boolean_ops:
                Boolean '.' parseBoolean '(' term ')'    { $$ = ast.Operation("parseBool",$5);  }
              | Boolean '.' valueOf      '(' term ')'    { $$ = ast.Operation("valueOf",$5);    }
              | Boolean '.' TK_TRUE                      { $$ = ast.Bool(true);                 }
              | Boolean '.' TK_FALSE                     { $$ = ast.Bool(false);                }
              | TK_true                                  { $$ = ast.Bool(true);                 }
              | TK_false                                 { $$ = ast.Bool(false);                }
              ;

    double_ops:
                Double  '.' valueOf     '(' term ')'     { $$ = ast.Operation("parseFloat",$5); }
              | Double  '.' parseDouble '(' term ')'     { $$ = ast.Operation("parseFloat",$5); }
              | Double  '.' isNaN       '(' term ')'     { $$ = ast.Operation("isNan",$5);      }
              | Double  '.' toString    '(' term ')'     { $$ = ast.Operation("toString",$5);   }
              | Math    '.' abs         '(' term ')'     { $$ = ast.Operation("Math.abs",$5);   }
              ;

    integer_ops:
                 Integer '.' valueOf    '(' term ')'    { $$ = ast.Operation("parseInt",$5);    }
               | Integer '.' parseInt   '(' term ')'    { $$ = ast.Operation("parseInt",$5);    }
               | Integer '.' toString   '(' term ')'    { $$ = ast.Operation("toString",$5);    }
               ;
    date_ops:
                TK_NEW         '.' TK_DATE '(' ')'                { $$ = ast.DateOp("newDate");          }
               | TK_DATE_FORMAT '.' parse   '(' term ',' term ')' { $$ = ast.DateOp("DateFormat.parse",$5, $7); }
               ;

%%

void casper::java::FakeJavaParser::error (const location_type& a_location, const std::string& a_msg)
{
    scanner_.ThrowParsingError("Parsing error", a_location.begin.column);
}
