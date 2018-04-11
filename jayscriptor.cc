/**
 * @file jayscriptor.cc
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

#include <iostream>
#include <fstream>

#include <unistd.h>

#include "casper/java/fake_java_expression.h"

/**
 * @brief Show version.
 *
 * @param a_name Tool name.
 */
void show_version (const char* a_name = "jayscriptor")
{
    fprintf(stderr, "%s v0.0.1\n", a_name);
}

/**
 * @brief Show help.
 *
 * @param a_name Tool name.
 */
void show_help (const char* a_name = "jayscriptor")
{
    fprintf(stderr, "usage: %s [-f <configuration file>] [-s <string>]\n", a_name);
    fprintf(stderr, "       -%c: %s\n", 'f' , "from file.");
    fprintf(stderr, "       -%c: %s\n", 's' , "from string.");
    fprintf(stderr, "       -%c: %s\n", 'h' , "show help.");
    fprintf(stderr, "       -%c: %s\n", 'v' , "show version.");
}

/**
 * @brief Parse arguments.
 *
 * @param a_argc
 * @param a_argv
 *
 * @param o_file
 * @param o_string
 *
 * @return 0 on success, < 0 on error.
 */
int parse_args (int a_argc, char** a_argv, std::string& o_file, std::string& o_string, std::string& o_entity)
{
    // ... not enough arguments?
    if ( a_argc < 3 ) {
        // ... show error ...
        fprintf(stderr, "invalid number of arguments: got %d, expected at least %d!\n", a_argc, 1);
        // ... and help ...
        show_help(a_argv[0]);
        // ... can't proceed ...
        return -1;
    }

    // ... parse arguments ...
    char opt;
    while ( -1 != ( opt = getopt(a_argc, a_argv, "hvf:s:e:") ) ) {
        switch (opt) {
            case 'h':
                show_help(a_argv[0]);
                return 0;
            case 'v':
                show_version(a_argv[0]);
                return 0;
            case 'f':
                o_file = optarg;
                break;
            case 's':
                o_string = optarg;
                break;
            case 'e':
                o_entity = optarg;
                break;
            default:
                fprintf(stderr, "llegal option %s:\n", optarg);
                show_help(a_argv[0]);
                return -1;
        }
    }

    return 0;
}



int main(int argc, char* argv[])
{

    casper::java::FakeJavaExpression exp;

    std::string file;
    std::string java_expression;
    std::string entity;


    const int arg_rv = parse_args(argc, argv, file, java_expression, entity);
    if ( 0 != arg_rv ) {
        return arg_rv;
    }

    if ( file.length() > 0 ) {

        std::ifstream in(file);

        std::string expression;

        if ( !in ) {
            std::cout<< "Cannot open input file!\n";
            return 1;
        }

        std::string line;
        int n=0;

        //std::cout << "var t0 = performance.now();\n";

        while ( getline(in, line) ) {
            try{
                //fprintf(stdout, "console.log(");
                expression = exp.Convert(line, entity);
                if ( 0 == expression.length() ) {
                    throw std::runtime_error("Invalid 'java' expression: " + line);
                }
                fprintf(stdout, "%s", expression.c_str());
                //fprintf(stdout, ")");
            } catch (const std::runtime_error& a_error) {
                fprintf(stderr, "%s", a_error.what());
                return -1;
            }
            fprintf(stdout, "\n");
            n++;
        }
        in.close();


        //std::cout << "var t1 = performance.now();\n";
        //std::cout << "console.log(\"nr of operations: "<< n <<"\")\n";
        //std::cout << "console.log(\"elapsed time: \" + (t1 - t0)/1000 + \"s\\n\")\n";

        return 0;

    } else {
        try{
            const std::string js_expression = exp.Convert(java_expression, entity);
            if ( 0 == js_expression.length() ) {
                fprintf(stdout, "%s\n", java_expression.c_str());
                return 0;
            } else {
                fprintf(stdout, "%s\n", js_expression.c_str());
                return 0;
            }
          }catch (const std::runtime_error& a_error) {
              fprintf(stderr, "%s", a_error.what());
              return -1;
          }

    }

    return -1;
}
