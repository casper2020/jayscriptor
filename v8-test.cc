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
    fprintf(stderr, "       -%c: %s\n", 's' , "script to load.");
    fprintf(stderr, "       -%c: %s\n", 'j' , "data to load, json file.");
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
int parse_args (int a_argc, char** a_argv, std::string& o_script_file, std::string& o_json_file)
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
    while ( -1 != ( opt = getopt(a_argc, a_argv, "hvs:j:") ) ) {
        switch (opt) {
            case 'h':
                show_help(a_argv[0]);
                return 0;
            case 'v':
                show_version(a_argv[0]);
                return 0;
            case 's':
                o_script_file = optarg;
                break;
            case 'j':
                o_json_file = optarg;
                break;
            default:
                fprintf(stderr, "llegal option %s:\n", optarg);
                show_help(a_argv[0]);
                return -1;
        }
    }

    return 0;
}

// Reads a file into a v8 string.
v8::MaybeLocal<v8::String> ReadFileToV8String (v8::Isolate* isolate, const char* name)
{
    FILE* file = fopen(name, "rb");
    if (file == NULL) return v8::MaybeLocal<v8::String>();

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    char* chars = new char[size + 1];
    chars[size] = '\0';
    for (size_t i = 0; i < size;) {
        i += fread(&chars[i], 1, size - i, file);
        if (ferror(file)) {
            fclose(file);
            return v8::MaybeLocal<v8::String>();
        }
    }
    fclose(file);
    v8::MaybeLocal<v8::String> result = v8::String::NewFromUtf8(isolate, chars, v8::NewStringType::kNormal, static_cast<int>(size));
    delete[] chars;
    return result;
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
    
    int result = -1;

    {
        casper::v8::Context* casper_context = new casper::v8::Context();
        
        ::v8::Isolate::Scope isolate_scope (casper_context->isolate_);
        ::v8::HandleScope    handle_scope  (casper_context->isolate_);
        
        // Create a template for the global object where we set the
        // built-in global functions.
        //::v8::Local<::v8::ObjectTemplate> global = ::v8::ObjectTemplate::New(casper_context->isolate_);
        
        //::v8::Local<::v8::Context> casper_context->context_ = v8::Context::New(casper_context->isolate_, NULL, global);
        //casper_context->context_.Reset(casper_context->isolate_, casper_context->context_);
//
//        if (casper_context->context_.IsEmpty()) {
//            fprintf(stderr, "Error creating casper_context->context_\n");
//            return 1;
//        }
        
        //v8::Context::Scope context_scope(casper_context->context_);
        std::string script_file;
        std::string json_file;
        
        const int arg_rv = parse_args(argc, argv, script_file, json_file);
        if ( 0 != arg_rv ) {
            return arg_rv;
        }
        
        // Use all other arguments as names of files to load and run.
        v8::Local<v8::String> source;
        if ( ! ReadFileToV8String(casper_context->isolate_, script_file.c_str()).ToLocal(&source) ) {
            fprintf(stderr, "Error reading '%s'\n", script_file.c_str());
            return -1;
        }
        
        const std::vector<::casper::v8::Context::Function> functions = {
            { /* name_ */ "evaluate_expression" }
        };
        
        if ( false == casper_context->Compile(source) ) {
            fprintf(stderr, "Error while compiling JS '%s'\n", script_file.c_str());
            return -1;
        }
        
        if ( false == casper_context->LoadFunctions(functions) ) {
            fprintf(stderr, "Error while loading functions from '%s'\n", script_file.c_str());
            return -1;
        }

        //Declarations
        /*  v8::Local<v8::String> func_name2 =
         v8::String::NewFromUtf8(context->GetIsolate(), "convert_json", v8::NewStringType::kNormal).ToLocalChecked();
         v8::Local<v8::Value> value2 = global->Get(context, func_name2).ToLocalChecked();;
         v8::Local<v8::Function> convert_json = v8::Local<v8::Function>::Cast(value2);
         v8::Local<v8::Value> json_args[1];
         v8::Local<v8::Value> json_data_final;*/
        
        //Load JSON-----------------------------------------------------------------
        
        // auto start1 = std::chrono::high_resolution_clock::now();
        //
         //std::ifstream ifs("jsonapi.json");
         std::ifstream ifs(json_file);
         std::string content( (std::istreambuf_iterator<char>(ifs)),
                             (std::istreambuf_iterator<char>()) );
                
        ::v8::Local<::v8::ObjectTemplate> global = ::v8::ObjectTemplate::New(casper_context->isolate_);
        ::v8::Local<::v8::Context> context = v8::Context::New(casper_context->isolate_, NULL, global);
        
//        ::v8::Local<::v8::Context> context = v8::Context::New(casper_context->isolate_, NULL, global);
        
//        casper_context->context_.Reset(casper_context->isolate_, context);
        
        ::v8::Local<::v8::Value> json_data = ::v8::JSON::Parse(context,
                                                          v8::String::NewFromUtf8(casper_context->isolate_, content.c_str(), v8::NewStringType::kNormal).ToLocalChecked()).ToLocalChecked();
        // auto end1 = std::chrono::high_resolution_clock::now();
        // auto duration = std::chrono::duration_cast<std::chrono::microseconds>( end1 - start1 ).count();
        // std::cout << "\nTime for JSON Parse: " << (duration)/1000.0 << "ms\n\n";
        
        //Convert JSON
        //  json_args[0]=json_data;
        //  if (!convert_json->Call(context, context->Global(), 1, json_args).ToLocal(&json_data_final))
        //    printf("error..\n");
        
        
        //Calculate the expressions-------------------------------------------------
        
        int cnt0=10000;
        int cnt1=10;
        int cnt2=4;
        
        //  auto start = std::chrono::high_resolution_clock::now();
        
        v8::Local<v8::Value>      args[3];
        v8::Persistent<v8::Value> js_result;
        
        
        
        
//        for(int ii=0; ii<cnt0; ii++){
//            for(int i=0; i<cnt1; i++){
//
                //const char* arg1 = "dados1";
//                const char* arg2 = std::to_string(i).c_str();
                //args[1] = v8::String::NewFromUtf8(context->GetIsolate(), arg1, v8::NewStringType::kNormal).ToLocalChecked();
                //args[1] = json_data_final;
                args[1] = json_data;
                //args[1] = v8::String::NewFromUtf8(casper_context->isolate_, arg2, v8::NewStringType::kNormal).ToLocalChecked();
                args[2] = v8::String::NewFromUtf8(casper_context->isolate_, "3", v8::NewStringType::kNormal).ToLocalChecked();
                
//                for(int l=0; l<cnt2; l++){
        
//                    const char* arg0 = std::to_string(l+1).c_str();
        
                    args[0] = v8::Integer::NewFromUnsigned(casper_context->isolate_, 2);

//        if ( true == casper_context->CallFunction("evaluate_expression", 3, args, js_result,
//                                                  [&](const char* const a_message) {
//                                                      fprintf(stderr, "Error while evaluating expression:\n%s\n", a_message);
//                                                  }
//        ) ) {
//            const char* cstr = casper::v8::Context::ToCString(::v8::String::Utf8Value(js_result.Get(casper_context->isolate_)));
//            printf("\t%s\n", cstr);
//        }
        
        const auto start1 = std::chrono::high_resolution_clock::now();
        for(int i=0; i<cnt0; i++){
            (void)casper_context->CallFunction("evaluate_expression", 3, args, js_result);
        }
        
        const auto start2 = std::chrono::high_resolution_clock::now();
        for(int i=0; i<cnt0; i++){
            (void) casper_context->CallFunction(context, "evaluate_expression", 3, args, js_result);
        }
        
        const auto start3 = std::chrono::high_resolution_clock::now();
        
        const auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>( start2 - start1 ).count();
        const auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>( start3 - start2 ).count();
        
        std::cout << "\nEternal Context: " << (duration1) << "us\n";
        std::cout << "Local Context:   " << (duration2) << "us\n";

        
//                    if ( false == f1 ) {
//                        printf("error..\n");
//                    } else {
//                        v8::String::Utf8Value str_2(js_result);
//                        const char* cstr = casper::v8::Context::ToCString(str_2);
//                        printf("%s\n", cstr);
//                    }
//
//                }
//            }
//        }
        
//        if ( false == casper_context->ExecuteFunction("calc_tipo1", 3, args, js_result) ) {
//            printf("error..\n");
//        } else {
//            v8::String::Utf8Value str_2(js_result);
//            const char* cstr = casper::v8::Context::ToCString(str_2);
//            printf("%s\n", cstr);
//        }
        
        // auto end = std::chrono::high_resolution_clock::now();
        // printf("%s\n", resultado);
        // std::cout << "------Output:\n\n" << resultado.GetText() << "\n\n------------\n";
        // auto elapsed_seconds = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();
        // std::cout << "\nV8 ---> nr of operations: " << cnt1 * cnt2 * cnt0
        // << "\nTime for each operation: " << (elapsed_seconds/1000.0)/(cnt1*cnt2*cnt0) << " ms\n";

    }
    return result;
}
