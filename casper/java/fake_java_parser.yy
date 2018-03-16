%skeleton "lalr1.cc"
%require "3.0"
%defines
%define api.namespace  { casper::java }
%define api.value.type {class casper::java::FakeJavaTerm }
%define parser_class_name { FakeJavaParser }

%code requires {
  namespace casper {
      namespace java {
          class FakeJavaScanner;
          class FakeJavaExpression;
          class FakeJavaTerm;
      }
  }
  #include <cmath>
  #include <iostream>
  #include "casper/java/fake_java_term.h"
}

%parse-param { casper::java::FakeJavaScanner& scanner_ } { casper::java::FakeJavaExpression& expr_ }

%code {
  #include "casper/java/fake_java_scanner.h"
  #include "casper/java/fake_java_expression.h"
  #include "osal/exception.h"
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
         | term END                          {  expr_.result_ = $1; (void) @1;             }
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
                  | NUM                      { $$ = $1;                                       }
                  | TEXTLITERAL              { $$.SetString($1);                              }
                  | TK_null                  { $$.SetNull();                                  }
                  | VARIABLE                 { expr_.GetVariable($$, $1);                     }
                  | FIELD                    { expr_.GetField($$, $1.ToString().c_str());     }
                  | PARAMETER                { expr_.GetParameter($$, $1.ToString().c_str()); }
                  ;

    expressions:
                '(' term ')'                 { $$ = $2;                            }
              | term '+' term                { $$.AddNumOrText($1,$3);             }
              | term '-' term                { $$.Subtract($1,$3);                 }
              | term '*' term                { $$.Multiply($1,$3);                 }
              | term '/' term                { $$.Divide($1,$3);                   }
              | term '^' term                { $$.Pow($1,$3);                      }
              | term '%' term                { printf("TODO %%\n");                }
              | term '>' term                { $$.Greater($1, $3);                 }
              | term '<' term                { $$.Less($1, $3);                    }
              | term  GE term                { $$.GreaterOrEqual($1, $3);          }
              | term  LE term                { $$.LessOrEqual($1, $3);             }
              | term  NE term                { $$.NotEqual($1,$3);                 }
              | term  EQ term                { $$.Equal($1,$3);                    }
              | term  OR term                { $$.Or($1,$3);                       }
              | term AND term                { $$.And($1,$3);                      }
              | term '?' term ':' term       { $$.If($1, $3, $5);                  }
              | '-' term %prec UMINUS        { $$.UnaryMinus($2);                  }
              | '+' term %prec UPLUS         { $$ = $2;                            }
              | '!' term                     { $$.Not($2);                         }
              ;

    generic_ops:
                 term '.' equals      '(' term ')'         { $$.Equal($1, $5);                   }
               | term '.' toString    '(' ')'              { $$ = $1.ToString().c_str();         }
               | term '.' intValue    '(' ')'              { $$.ParseInteger($1);                }
               | term '.' to_i        '(' ')'              { $$.ToI($1);                         }
               | term '.' to_f        '(' ')'              { $$.ToF($1);                         }
               | term '.' doubleValue '(' ')'              { $$.ParseDouble($1);                 }
               | term '.' isNaN       '(' ')'              { $$.IsNan($1);                       }
               ;

    string_ops:
                term '.' isEmpty     '(' ')'               { $$.IsEmpty($1);                     }
              | term '.' length      '(' ')'               { $$.Length($1);                      }
              | term '.' toUpperCase '(' ')'               { $$.ToUpperCase($1);                 }
              | term '.' toLowerCase '(' ')'               { $$.ToLowerCase($1);                 }
              | term '.' substring   '(' term ',' term ')' { $$.Substring($1, $5, $7);           }
              | term '.' substring   '(' term ')'          { $$.Substring($1, $5);               }
              | term '.' indexOf     '(' term ')'          { $$.IndexOf($1, $5);                 }
              | term '.' replace     '(' term ',' term ')' { $$.Replace($1, $5, $7);             }
              ;

    boolean_ops:
                 Boolean '.' parseBoolean '(' term ')'     { $$.ParseBoolean($5);                }
               | Boolean '.' valueOf      '(' term ')'     { $$.If($5);                          }
               | Boolean '.' TK_TRUE                       { $$.BooleanTrue();                   }
               | Boolean '.' TK_FALSE                      { $$.BooleanFalse();                  }
               | TK_true                                   { $$.BooleanTrue();                   }
               | TK_false                                  { $$.BooleanFalse();                  }
               ;

    double_ops:
                Double  '.' valueOf     '(' term ')'       { $$.ParseDouble($5);                 }
              | Double  '.' parseDouble '(' term ')'       { $$.ParseDouble($5);                 }
              | Double  '.' isNaN       '(' term ')'       { $$.IsNan($5);                       }
              | Double  '.' toString    '(' term ')'       { $$.DoubleToString($5);              }
              | Math    '.' abs         '(' term ')'       { $$.FakeJavaAbs($5);                 }
              ;

    integer_ops:
                 Integer '.' valueOf    '(' term ')'       { $$.ParseInteger($5);                }
               | Integer '.' parseInt   '(' term ')'       { $$.ParseInteger($5);                }
               | Integer '.' toString   '(' term ')'       { $$.IntegerToString($5);             }
               ;

    date_ops:
                 TK_NEW         '.' TK_DATE '(' ')'               { $$.NewDate();               }
               | TK_DATE_FORMAT '.' parse   '(' term ',' term ')' {
#if !defined(CASPER_NO_ICU)
                 $$.ParseDate($5, $7, expr_);
#else
  $$ = $5; // TODO Martelada
#endif
               }
               ;

%%

void casper::java::FakeJavaParser::error (const location_type& a_location, const std::string& a_msg)
{
    throw OSAL_EXCEPTION("%s:\n"
                         "   %*.*s\n"
                         "   %*.*s^~~~~~\n",
                         a_msg.c_str(),
                         scanner_.pe_ - scanner_.input_, scanner_.pe_ - scanner_.input_, scanner_.input_,
                         a_location.begin.column, a_location.begin.column, " ");
}
