%skeleton "lalr1.cc"
%require "3.0"
%defines
%define api.namespace  { casper::java }
%define api.value.type { class AstNode }
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
}

%parse-param { casper::java::FakeJavaScanner& scanner_ } { casper::java::FakeJavaExpression& expr_ }

%code {
  #include "casper/java/fake_java_scanner.h"
  #include "casper/java/fake_java_expression.h"
  #include "osal/exception.h"
  #define yylex scanner_.Scan
  AstNode root;
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
         | term END                       { root = $1;                          }
         ;

    term:
           expressions
         | generic_ops
         | string_ops
         | integer_ops
         | boolean_ops
         | double_ops
         | leaf_terminals
         ;

   leaf_terminals:
                 NUM                      { $$ = $1;                            }
                 | TEXTLITERAL            { $$ = $1;                            }
                 | TK_null                { $$ = ast_null();                    }
                 | VARIABLE               { $$ = mkVar($1);                     }
                 | FIELD                  { $$ = mkField($1);                   }
                 | PARAMETER              { $$ = mkParam($1);                   }
                 ;

    expressions:
                '(' term ')'              { $$ = $2;                            }
              | term '+' term             { $$ = ast_expression("+",$1,$3);     }
              | term '-' term             { $$ = ast_expression("-",$1,$3);     }
              | term '*' term             { $$ = ast_expression("*",$1,$3);     }
              | term '/' term             { $$ = ast_expression("/",$1,$3);     }
              | term '^' term             { $$ = ast_expression("^",$1,$3);     }
              | term '%' term             { $$ = ast_expression("%",$1,$3);     }
              | term '>' term             { $$ = ast_expression(">",$1,$3);     }
              | term '<' term             { $$ = ast_expression("<",$1,$3);     }
              | term  GE term             { $$ = ast_expression(">=",$1,$3);    }
              | term  LE term             { $$ = ast_expression("<=",$1,$3);    }
              | term  NE term             { $$ = ast_expression("!=",$1,$3);    }
              | term  EQ term             { $$ = ast_expression("==",$1,$3);    }
              | term  OR term             { $$ = ast_expression("||",$1,$3);    }
              | term AND term             { $$ = ast_expression("&&",$1,$3);    }
              | term '?' term ':' term    { $$ = ast_if($1, $3, $5);            }
              | '-' term %prec UMINUS     { $$ = ast_expression("UM",$2,$2);    }
              | '+' term %prec UPLUS      { $$ = $2;                            }
              | '!' term                  { $$ = ast_expression("!",$2,$2);     }
              ;
    generic_ops:
                 term '.' equals      '(' term ')'  { $$=ast_expression("==",$1,$5);            }
               | term '.' toString    '(' ')'       { $$=ast_operation("toString",$1);          }
               | term '.' intValue    '(' ')'       { $$=ast_operation("parseInt",$1);          }
               | term '.' to_i        '(' ')'       { $$=ast_operation("parseInt",$1);          }
               | term '.' to_f        '(' ')'       { $$=ast_operation("parseFloat",$1);        }
               | term '.' doubleValue '(' ')'       { $$=ast_operation("parseFloat",$1);        }
               | term '.' isNaN       '(' ')'       { $$=ast_operation("isNan",$1);             }
               ;

    string_ops:
                term '.' isEmpty     '(' ')'               { $$=ast_strOp("IsEmpty",$1);        }
              | term '.' length      '(' ')'               { $$=ast_strOp("length",$1);         }
              | term '.' toUpperCase '(' ')'               { $$=ast_strOp("toUpperCase",$1);    }
              | term '.' toLowerCase '(' ')'               { $$=ast_strOp("toLowerCase",$1);    }
              | term '.' substring   '(' term ',' term ')' { $$=ast_strOp("substring",$1,$5,$7);}
              | term '.' substring   '(' term ')'          { $$=ast_strOp("substring",$1,$5);   }
              | term '.' indexOf     '(' term ')'          { $$=ast_strOp("indexOf",$1,$5);     }
              | term '.' replace     '(' term ',' term ')' { $$=ast_strOp("replace",$1,$5,$7);  }
              ;
    boolean_ops:
                Boolean '.' parseBoolean '(' term ')'    { $$ = ast_operation("parseBool",$5);  }
              | Boolean '.' valueOf      '(' term ')'    { $$ = ast_operation("valueOf",$5);    }
              | Boolean '.' TK_TRUE                      { $$ = ast_bool(true);                 }
              | Boolean '.' TK_FALSE                     { $$ = ast_bool(false);                }
              | TK_true                                  { $$ = ast_bool(true);                 }
              | TK_false                                 { $$ = ast_bool(false);                }
              ;

    double_ops:
                Double  '.' valueOf     '(' term ')'     { $$ = ast_operation("parseFloat",$5); }
              | Double  '.' parseDouble '(' term ')'     { $$ = ast_operation("parseFloat",$5); }
              | Double  '.' isNaN       '(' term ')'     { $$ = ast_operation("isNan",$5);      }
              | Double  '.' toString    '(' term ')'     { $$ = ast_operation("toString",$5);   }
              | Math    '.' abs         '(' term ')'     { $$ = ast_operation("Math.abs",$5);   }
              ;

    integer_ops:
                 Integer '.' valueOf    '(' term ')'    { $$ = ast_operation("parseInt",$5);    }
               | Integer '.' parseInt   '(' term ')'    { $$ = ast_operation("parseInt",$5);    }
               | Integer '.' toString   '(' term ')'    { $$ = ast_operation("toString",$5);    }
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
