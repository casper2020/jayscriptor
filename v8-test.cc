//
//  test.cc
//  v8_teste
//
//  Created by Bruno Carvalho on 28/03/18.
//  Copyright © 2018 Bruno Carvalho. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip> // std::setw
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include "casper/v8/singleton.h"
#include "casper/v8/context.h"

/**
 * @brief Show version.
 *
 * @param a_name Tool name.
 */
void show_version (const char* a_name = "test")
{
    fprintf(stderr, "%s v0.0.1\n", a_name);
}

/**
 * @brief Show help.
 *
 * @param a_name Tool name.
 */
void show_help (const char* a_name = "test")
{
    fprintf(stderr, "usage: %s [-s <script file>] [-j <json file>]\n", a_name);
    fprintf(stderr, "       -%c: %s\n", 'e' , "expressions to load, json file.");
    fprintf(stderr, "       -%c: %s\n", 'd' , "data to load, json file.");
    fprintf(stderr, "       -%c: %s\n", 'h' , "show help.");
    fprintf(stderr, "       -%c: %s\n", 'v' , "show version.");
}

/**
 * @brief Parse arguments.
 *
 * @param a_argc
 * @param a_argv
 *
 * @param o_script_file
 * @param o_json_file
 *
 * @return 0 on success, < 0 on error.
 */
int parse_args (int a_argc, char** a_argv, std::string& o_expressions_file, std::string& o_data_file)
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
    while ( -1 != ( opt = getopt(a_argc, a_argv, "hve:d:") ) ) {
        switch (opt) {
            case 'h':
                show_help(a_argv[0]);
                return 0;
            case 'v':
                show_version(a_argv[0]);
                return 0;
            case 'e':
                o_expressions_file = optarg;
                break;
            case 'd':
                o_data_file = optarg;
                break;
            default:
                fprintf(stderr, "llegal option %s:\n", optarg);
                show_help(a_argv[0]);
                return -1;
        }
    }
    
    return 0;
}

int use_eternal_context (const std::string& a_expressions_file, const std::string& a_data_file, const size_t a_lines, const size_t a_rounds,
                         size_t& o_number_of_functions, size_t& o_elapsed)
{
    fprintf(stdout, "//\n// Using C++ object\n//\n");
    
    casper::v8::Context* casper_context = new casper::v8::Context();
    
    if ( false == casper_context->Initialize() ) {
        fprintf(stderr,
                "Error initializing 'casper' context\n"
        );
        return -1;
    }
    
    // TODO avoid casper_context->isolate_ calls
    
    ::v8::Isolate::Scope isolate_scope (casper_context->isolate_);
    ::v8::HandleScope    handle_scope  (casper_context->isolate_);
    
    casper::v8::Context::Expressions expressions;
    
    ::v8::Persistent<::v8::Value>  json_data;
    ::v8::Persistent<::v8::Object> json_obj;
    if ( false == casper_context->Parse(a_expressions_file.c_str(), json_obj, json_data) ) {
        fprintf(stderr,
                "Error while parsing expressions file '%s'\n",
                a_expressions_file.c_str()
                );
        return -1;
    }
    
    ::v8::Local<::v8::Object>       local_obj   = json_obj.Get(casper_context->isolate_);
    const ::v8::Handle<::v8::Value> array_value = local_obj->Get(::v8::String::NewFromUtf8(local_obj->GetIsolate(), "expressions"));
    if ( false == array_value->IsArray() ) {
        fprintf(stderr,
                "Error while parsing expressions file '%s' - array 'expressions' not found!\n",
                a_expressions_file.c_str()
                );
        return -1;
    }
    
    const ::v8::Local<::v8::Array> array_object = array_value.As<::v8::Array>();
    for ( unsigned int idx = 0 ; idx < array_object->Length() ; ++idx ) {
        const auto expression_value = array_object->Get(idx);
        if ( false == expression_value->IsString() ) {
            continue;
        }
        
        const char* const expression_c_str = casper::v8::Context::ToCString(::v8::String::Utf8Value(/*casper_context->isolate_,*/  expression_value));
        expressions.push_back(expression_c_str);
    }
    
    if ( false == casper_context->LoadExpressions("evaluate_expression", expressions)) {
        fprintf(stderr, "Error while compiling expressions function '%s'\n", "evaluate_expressions");
        return -1;
    }
    
    ::v8::Persistent<::v8::Value>  data_value;
    
    if ( false == casper_context->LoadData("data_object", a_data_file.c_str(), nullptr, nullptr, &data_value) ) {
        fprintf(stderr, "Error while loading data from '%s'\n", a_data_file.c_str());
        return -1;
    }
    
    v8::Persistent<v8::Value> js_result;
    v8::Local<v8::Value> fc_result;
    v8::Local<v8::Value>      args[3] = {};
    bool                      success = false;
    
    args[1] = /* data object    */ data_value.Get(casper_context->isolate_);
    args[2] = /* data row index */ v8::Integer::NewFromUnsigned(casper_context->isolate_, 0);
    
    casper::v8::Context::LoadedFunction::Callable callable {
        /* name_   */ "evaluate_expression",
        /* argc_   */ ( sizeof(args) / sizeof(args[0]) ),
        /* argv_   */ args
    };
    
    CASPER_V8_CHRONO_START(eternal_context);
    for ( unsigned int l = 0; l < static_cast<unsigned>(a_lines); l++ ) {
        args[2] = /* data row index */ v8::Integer::NewFromUnsigned(casper_context->isolate_, l);
        for ( size_t i = 0; i < a_rounds; i++ ) {
            for ( size_t e = 0 ; e < expressions.size() ; ++e ) {
                args[0] = /* expr number */    v8::Integer::NewFromUnsigned(casper_context->isolate_, static_cast<unsigned int>(e));
                success =  casper_context->CallFunction(callable, js_result);
                if ( false == success ) {
                    fprintf(stderr,
                            "Error while evaluating expression #%zd\n", e
                            );
                    return -1;
                } else {
                  //fprintf(stdout, "%zd: %s\n", e, casper::v8::Context::ToCString(v8::String::Utf8Value(casper_context->isolate_, js_result.Get(casper_context->isolate_))));
//                    fc_result = js_result.Get(casper_context->isolate_);
//                    ::v8::String::Utf8Value str_2(fc_result);
//                    const char* cstr = casper::v8::Context::ToCString(str_2);
                   // printf("%s\n", cstr);
                    
                  }
            }
        }
    }
    o_number_of_functions = static_cast<size_t>(array_object->Length());
    o_elapsed             = CASPER_V8_CHRONO_END(eternal_context, "evaluate %zd expression(s) for %zd round(s)", expressions.size(), a_rounds);
    
    fprintf(stdout, "\tTook %.3f ms per function call\n",
            ( static_cast<double>(o_elapsed) / 1000.0f ) / ( a_rounds * a_lines * o_number_of_functions )
            );

    
    delete casper_context;
    
    return 0;
}

int use_local_context (const std::string& a_expressions_file, const std::string& a_data_file, const size_t a_lines, const size_t a_rounds,
                       size_t& o_number_of_functions, size_t& o_elapsed)
{
    //fprintf(stdout, "//\n// Using LOCAL variables\n//\n");
    
    ::v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = ::v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    
    // prepare isolate
    ::v8::Isolate* isolate = ::v8::Isolate::New(create_params);
    
    // enter isolate scope
    v8::Isolate::Scope isolate_scope(isolate);
    
    // create a stack-allocated handle scope.
    v8::HandleScope handle_scope(isolate);
    
    // add debug function
    ::v8::Local<::v8::ObjectTemplate> global = ::v8::ObjectTemplate::New(isolate);
    
    // make a context
    ::v8::Local<::v8::Context> context = ::v8::Context::New(isolate, NULL, global);
    
    // enter the context for compiling and running the hello world script.
    v8::Context::Scope context_scope(context);
    
    std::ifstream ef_is(a_expressions_file);
    std::string   ef_c((std::istreambuf_iterator<char>(ef_is)), (std::istreambuf_iterator<char>()));
    
    std::ifstream df_is(a_data_file);
    std::string   df_c((std::istreambuf_iterator<char>(df_is)), (std::istreambuf_iterator<char>()));
    
    //
    ::v8::MaybeLocal<::v8::String> expressions_string = ::v8::String::NewFromUtf8(isolate, ef_c.c_str(), ::v8::NewStringType::kNormal);
    
    //CASPER_V8_CHRONO_START(local_data_parsing);
    ::v8::MaybeLocal<::v8::Value> expression_as_json_value = ::v8::JSON::Parse(context, expressions_string.ToLocalChecked());
    //CASPER_V8_CHRONO_END(local_data_parsing, "parse %zd byte(s) of JSON data", ef_c.length());
    
    //
    ::v8::Local<::v8::Object>       local_obj   = expression_as_json_value.ToLocalChecked()->ToObject(context).ToLocalChecked();
    const ::v8::Handle<::v8::Value> array_value = local_obj->Get(::v8::String::NewFromUtf8(isolate, "expressions"));
    if ( false == array_value->IsArray() ) {
        fprintf(stderr,
                "Error while parsing expressions file '%s' - array 'expressions' not found!\n",
                a_expressions_file.c_str()
                );
        return -1;
    }
    
    std::vector<std::string> expressions;
    
    const ::v8::Local<::v8::Array> array_object = array_value.As<::v8::Array>();
    for ( unsigned int idx = 0 ; idx < array_object->Length() ; ++idx ) {
        ::v8::Local<v8::Value> expression_value = array_object->Get(idx);
        if ( false == expression_value->IsString() ) {
            continue;
        }
        
        ::v8::Isolate::Scope isolate_scope (isolate);
        ::v8::HandleScope    handle_scope  (isolate);
        
        ::v8::String::Utf8Value teste2(expression_value);
        
        const char* const expression_c_str = casper::v8::Context::ToCString(teste2);
        expressions.push_back(expression_c_str);
    }
    
    //
    //Get the results
    //
    
    const ::v8::Handle<::v8::Value> array_results = local_obj->Get(::v8::String::NewFromUtf8(isolate, "results"));
    if ( false == array_results->IsArray() ) {
        fprintf(stderr,
                "Error while parsing expressions file '%s' - array 'results' not found!\n",
                a_expressions_file.c_str()
                );
        return -1;
    }
    
    std::vector<std::string> results;
    
    const ::v8::Local<::v8::Array> array_object_res = array_results.As<::v8::Array>();
    for ( unsigned int idx = 0 ; idx < array_object_res->Length() ; ++idx ) {
        ::v8::Local<v8::Value> result_value = array_object_res->Get(idx);
        if ( false == result_value->IsString() ) {
            continue;
        }
        
        ::v8::Isolate::Scope isolate_scope (isolate);
        ::v8::HandleScope    handle_scope  (isolate);
        
        ::v8::String::Utf8Value teste2(result_value);
        
        const char* const result_c_str = casper::v8::Context::ToCString(teste2);
        results.push_back(result_c_str);
    }
    
//    for(int i=0; i<results.size(); i++){
//        std::cout << results[i] << "\n";
//    }
    
    //
    // Create script
    //
    
    const char* const func_name_c_str = "evaluate_expression";
    
    std::stringstream ss;
    
    //    ss << "\"use strict\";\n";
    ss << "function " << func_name_c_str << "(number, $, index) {\n";
    ss << std::setw(4) << ' ' << "switch (number) {\n";
    for ( size_t idx = 0 ; idx < expressions.size() ; ++idx ) {
        ss << std::setw(8) << ' ' << "case " << idx << " : return " << expressions[idx] << ";\n";
    }
    ss << std::setw(8) << ' ' << "default: return index;\n";
    ss << std::setw(4) << ' ' << "}\n"; // end of case
    ss << "}";   // end of function
    
    const ::v8::Local<::v8::String> script_payload = ::v8::String::NewFromUtf8(isolate, ss.str().c_str(), ::v8::NewStringType::kNormal).ToLocalChecked();
    
    //fprintf(stdout, "\n%s\n", ss.str().c_str());
    
    //
    // Compile the script and check for errors.
    //
    ::v8::Local<::v8::Script> local_compiled_script;
    if ( false == ::v8::Script::Compile(context, script_payload).ToLocal(&local_compiled_script) ) {
        return -1;
    }
    
    //
    // Run the script
    //
    ::v8::Local<::v8::Value> result;
    if ( false == local_compiled_script->Run(context).ToLocal(&result) ) {
        return -1;
    }
    
    //
    // Load function
    //
    const ::v8::Local<::v8::String> func_name = ::v8::String::NewFromUtf8(isolate, func_name_c_str, ::v8::NewStringType::kNormal).ToLocalChecked();
    ::v8::Local<::v8::Value>  process_val;
    // If there is no function, or if it is not a function, bail out
    if ( ! context->Global()->Get(context, func_name).ToLocal(&process_val) || ! process_val->IsFunction() ) {
        return -1;
    }
    
    // It is a function; cast it to a Function
    const ::v8::Local<::v8::Function> local_function = ::v8::Local<::v8::Function>::Cast(process_val);
    
    //
    // Load data
    //
    //
    
//    ::v8::Local<::v8::Object> data_object = ::v8::Object::New(isolate);
    
//    const ::v8::Local<::v8::String> key      = ::v8::String::NewFromUtf8(isolate, "data_object", ::v8::NewStringType::kNormal).ToLocalChecked();
    const ::v8::Local<::v8::String> payload = ::v8::String::NewFromUtf8(isolate, df_c.c_str(), ::v8::NewStringType::kNormal).ToLocalChecked();
    //CASPER_V8_CHRONO_START(local_data_file_parsing);
    const ::v8::Local<::v8::Value>  value   = ::v8::JSON::Parse(context, payload).ToLocalChecked();
    //CASPER_V8_CHRONO_END(local_data_file_parsing, "parse %zd byte(s) of JSON data", df_c.length());
    
//    data_object->Set(key, value);
    
    //
    // Call function
    //
    v8::Local<v8::Value> fc_result;
    v8::Local<v8::Value> args[3] = {};
    bool                 success = false;
    
    args[1] = /* data object */    value;
    int wrong_flag = 0;
    
   CASPER_V8_CHRONO_START(local_context);
    
   for ( unsigned int l = 0; l < static_cast<unsigned>(a_lines); l++ ) {
        args[2] = /* data row index */ v8::Integer::NewFromUnsigned(isolate, l);
        for ( size_t i = 0; i < a_rounds; i++ ) {
            for ( size_t e = 0 ; e < expressions.size() ; ++e ) {
                
                args[0] = /* expr number */ v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned int>(e));
                
                ::v8::MaybeLocal<::v8::Value> ml_value = local_function->Call(context, context->Global(), 3, args);
                success = ml_value.ToLocal(&fc_result);
                if ( false == success ) {
                    fprintf(stderr,
                            "Error while evaluating expression #%zd\n", e
                    );
                    return -1;
                }else {
                    ::v8::String::Utf8Value str_2(fc_result);
                    const char* cstr = casper::v8::Context::ToCString(str_2);
                    if(results[e] != cstr){
                        printf("Expression %d:\n\n", e+1);
                        std::cout << "Expected:  " << results[e] << "\n";
                        printf("Got:  %s\n\n\n", cstr);
                        wrong_flag=1;
                    }
                    
                }
                /* else {
                 fprintf(stdout, "%zd: %s\n", e, casper::v8::Context::ToCString(v8::String::Utf8Value(isolate, fc_result)));
                 }
                 */
            }
        }
    }
    
    if(wrong_flag==0) printf("All good!\n\n");
    
//    o_number_of_functions = static_cast<size_t>(array_object->Length());
//    o_elapsed             = CASPER_V8_CHRONO_END(local_context, "evaluate %zd expression(s) for %zd round(s)", expressions.size(), a_rounds);
//
//    fprintf(stdout, "\tTook %.3f ms per function call\n",
//            ( static_cast<double>(o_elapsed) / 1000.0f ) / ( a_rounds * a_lines * o_number_of_functions )
//            );
    return 0;
}


int main(int argc, char* argv[]) {
    
    casper::v8::Singleton& singleton = casper::v8::Singleton::GetInstance();
    
    const std::string uri   = argv[0];
    const std::size_t found = uri.find_last_of("/\\");
    const std::string path  = uri.substr(0, found);
    
    singleton.Startup(
                      /* a_exec_uri          */  argv[0],
                      /* a_natives_blob_uri */  ( path + "/natives_blob.bin" ).c_str(),
                      /* a_snapshot_blob_uri */ ( path + "/snapshot_blob.bin" ).c_str(),
                      /* a_icu_data_uri      */ ( path + "/icudtl.dat" ).c_str()
                      );
    std::string expressions_file;
    std::string data_file;
    
    const int arg_rv = parse_args(argc, argv, expressions_file, data_file);
    if ( 0 != arg_rv ) {
        return arg_rv;
    }
    
    
    int result;
    
    const size_t lines  = 1;
    const size_t rounds = 1;
    
    size_t eternal_elapsed = 0;
    size_t eternal_num_func = 0;
    size_t local_elapsed   = 0;
    size_t local_num_func = 0;
    
    if ( 0 != ( result = use_local_context(expressions_file, data_file, lines, rounds, local_num_func, local_elapsed) ) ) {
        fprintf(stderr, "Error while running local rounds!\n");
    } else if ( 0 != ( result = use_eternal_context(expressions_file, data_file, lines, rounds, eternal_num_func, eternal_elapsed) ) ) {
       fprintf(stderr, "Error while running eternal rounds!\n");
    }
//
//    if ( 0 == result ) {
//        const size_t diff = ( eternal_elapsed < local_elapsed ? ( local_elapsed - eternal_elapsed ) : ( eternal_elapsed - local_elapsed ) );
//        fprintf(stdout, "==\n= %s %zd us / %.4f ms faster!\n==\n",
//                local_elapsed < eternal_elapsed ? "LOCAL" : "C++ Object", diff, ( static_cast<double>(diff) / 1000.0 )
//                );
//    }
    
    return result;
}



