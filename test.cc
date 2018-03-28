//
//  main.cpp
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
#include "v8_shell.h"

namespace casper
{
    namespace V8 {
        
        namespace Wrapper
        {
            
            class Singleton
            {
                
            public:
                
                static Singleton& GetInstance()
                {
                    static Singleton instance;
                    return instance;
                }
                
            public: // Data
                
                v8::Isolate*  isolate_;

            private: // Data

                v8::Platform* platform_;
                
                v8::Isolate::CreateParams create_params_;
                
            public:
                
                Singleton()
                {
                    platform_ = nullptr;
                    isolate_ = nullptr;
                }
                
                virtual ~Singleton ()
                {
                    isolate_->Dispose();
                    isolate_ = nullptr;
                    v8::V8::Dispose();
                    v8::V8::ShutdownPlatform();
                    delete platform_;
                    delete create_params_.array_buffer_allocator;
                }
                
                Singleton(Singleton const&)       = delete;
                void operator=(Singleton const&)  = delete;
                
            public: //
                
                void Startup (const char* a_config_path)
                {
                    v8::V8::InitializeICUDefaultLocation(a_config_path);
                    v8::V8::InitializeExternalStartupData(a_config_path);
                    platform_ = v8::platform::CreateDefaultPlatform();
                    v8::V8::InitializePlatform(platform_);
                    v8::V8::Initialize();
                    
                    create_params_.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
                    
                    isolate_ = v8::Isolate::New(create_params_);

                }
                
            };
            
            
            class GlobalContext
            {
                
            public: // Data
                
                v8::Isolate*           isolate_;
                v8::Local<v8::Context> context_;
                
            public: // Constructor(s) / Destructor
                
                GlobalContext (v8::Isolate* a_isolate)
                {
                    // Create a template for the global object.
                    v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(a_isolate);
                    
                    // Bind the global 'print' function to the C++ Print callback.
                    global->Set(v8::String::NewFromUtf8(a_isolate, "print", v8::NewStringType::kNormal).ToLocalChecked(), v8::FunctionTemplate::New(a_isolate, Print));
                    
                    isolate_ = a_isolate;
                    context_ = v8::Context::New(a_isolate, NULL, global);
                }
                
            public: // Method(s) / Function(s)
                
                bool ExecuteFunction (v8::Local<v8::Context>& a_context, const char* a_name, const int a_n_args, v8::Local<v8::Value> a_args[], v8::Local<v8::Value>& o_result)
                {
                    v8::Local<v8::String>   func_name = v8::String::NewFromUtf8(context_->GetIsolate(), a_name, v8::NewStringType::kNormal).ToLocalChecked();
                    
                    // G
                    v8::Local<v8::Object>   global    = context_->Global();
                    v8::Local<v8::Value>    value     = global->Get(context_, func_name).ToLocalChecked();
                    v8::Local<v8::Function> func      = v8::Local<v8::Function>::Cast(value);
                    
                    // C
                    return func->Call(a_context, global, a_n_args, a_args).ToLocal(&o_result);
                    
                }
                
            public: // Static Method(s) / Function(s)
                
                // The callback that is invoked by v8 whenever the JavaScript 'print'
                // function is called.  Prints its arguments on stdout separated by
                // spaces and ending with a newline.
                static void Print (const v8::FunctionCallbackInfo<v8::Value>& args)
                {
                    bool first = true;
                    for (int i = 0; i < args.Length(); i++) {
                        v8::HandleScope handle_scope(args.GetIsolate());
                        if (first) {
                            first = false;
                        } else {
                            printf(" ");
                        }
                        v8::String::Utf8Value str(args[i]);
                        const char* cstr = casper::V8::Wrapper::GlobalContext::ToCString(str);
                        printf("%s", cstr);
                    }
                    printf("\n");
                    fflush(stdout);
                }
                
                // Extracts a C string from a V8 Utf8Value.
                static const char* ToCString (const v8::String::Utf8Value& a_value)
                {
                    return *a_value ? *a_value : "<string conversion failed>";
                }

                
            };
            
            class ClientContext
            {
                
            private: // Data
                
                v8::Local<v8::Context> context_;
                
            private: //
                
                GlobalContext* global_context_ptr_;
                
            public: // Constructor(s) / Destructor
                
                ClientContext (v8::Isolate* a_isolate, GlobalContext* a_global_context_ptr)
                {
                    // Create a template for the global object.
                    v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(a_isolate);
                    
//                    // Bind the global 'print' function to the C++ Print callback.
//                    global->Set(v8::String::NewFromUtf8(a_isolate, "print", v8::NewStringType::kNormal).ToLocalChecked(), v8::FunctionTemplate::New(a_isolate, Print));
//
                    context_= v8::Context::New(a_isolate, NULL, global);
                    
                    global_context_ptr_ = a_global_context_ptr;
                }
           
            public: // Method(s) / Function(s)
                
                bool ExecuteFunction (const char* a_name, const int a_n_args, v8::Local<v8::Value> a_args[], v8::Local<v8::Value>& o_result)
                {
                    return global_context_ptr_->ExecuteFunction(context_, a_name, a_n_args, a_args, o_result);
                }
                
            };
            
            
        }
        
    }
}

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
    v8::MaybeLocal<v8::String> result = v8::String::NewFromUtf8(
                                                                isolate, chars, v8::NewStringType::kNormal, static_cast<int>(size));
    delete[] chars;
    return result;
}


// Executes a string within the current v8 context.
bool ExecuteString(v8::Isolate* isolate, v8::Local<v8::String> source,
                   v8::Local<v8::Value> name, bool print_result,
                   bool report_exceptions) {
    v8::HandleScope handle_scope(isolate);
    v8::TryCatch try_catch(isolate);
    v8::ScriptOrigin origin(name);
    v8::Local<v8::Context> context(isolate->GetCurrentContext());
    v8::Local<v8::Script> script;
    if (!v8::Script::Compile(context, source, &origin).ToLocal(&script)) {
        // Print errors that happened during compilation.
        if (report_exceptions)
            ReportException(isolate, &try_catch);
        return false;
    } else {
        v8::Local<v8::Value> result;
        if (!script->Run(context).ToLocal(&result)) {
            assert(try_catch.HasCaught());
            // Print errors that happened during execution.
            if (report_exceptions)
                ReportException(isolate, &try_catch);
            return false;
        } else {
            assert(!try_catch.HasCaught());
            if (print_result && !result->IsUndefined()) {
                // If all went well and the result wasn't undefined then print
                // the returned value.
                v8::String::Utf8Value str(result);
                const char* cstr = casper::V8::Wrapper::GlobalContext::ToCString(str);
                printf("%s\n", cstr);
            }
            return true;
        }
    }
}


void ReportException(v8::Isolate* isolate, v8::TryCatch* try_catch) {
    v8::HandleScope handle_scope(isolate);
    v8::String::Utf8Value exception(try_catch->Exception());
    const char* exception_string = casper::V8::Wrapper::GlobalContext::ToCString(exception);
    v8::Local<v8::Message> message = try_catch->Message();
    if (message.IsEmpty()) {
        // V8 didn't provide any extra information about this error; just
        // print the exception.
        fprintf(stderr, "%s\n", exception_string);
    } else {
        // Print (filename):(line number): (message).
        v8::String::Utf8Value filename(message->GetScriptOrigin().ResourceName());
        v8::Local<v8::Context> context(isolate->GetCurrentContext());
        const char* filename_string = casper::V8::Wrapper::GlobalContext::ToCString(filename);
        int linenum = message->GetLineNumber(context).FromJust();
        fprintf(stderr, "%s:%i: %s\n", filename_string, linenum, exception_string);
        // Print line of source code.
        v8::String::Utf8Value sourceline(
                                         message->GetSourceLine(context).ToLocalChecked());
        const char* sourceline_string = casper::V8::Wrapper::GlobalContext::ToCString(sourceline);
        fprintf(stderr, "%s\n", sourceline_string);
        // Print wavy underline (GetUnderline is deprecated).
        int start = message->GetStartColumn(context).FromJust();
        for (int i = 0; i < start; i++) {
            fprintf(stderr, " ");
        }
        int end = message->GetEndColumn(context).FromJust();
        for (int i = start; i < end; i++) {
            fprintf(stderr, "^");
        }
        fprintf(stderr, "\n");
        v8::Local<v8::Value> stack_trace_string;
        if (try_catch->StackTrace(context).ToLocal(&stack_trace_string) &&
            stack_trace_string->IsString() &&
            v8::Local<v8::String>::Cast(stack_trace_string)->Length() > 0) {
            v8::String::Utf8Value stack_trace(stack_trace_string);
            const char* stack_trace_string = casper::V8::Wrapper::GlobalContext::ToCString(stack_trace);
            fprintf(stderr, "%s\n", stack_trace_string);
        }
    }
}

int main(int argc, char* argv[]) {
    
    casper::V8::Wrapper::Singleton& singleton = casper::V8::Wrapper::Singleton::GetInstance();
    
    singleton.Startup(argv[0]);
    
    int result = -1;
    
    {
//        v8::Isolate::Scope isolate_scope(singleton.isolate_);
//        v8::HandleScope handle_scope(singleton.isolate_);
        
        casper::V8::Wrapper::GlobalContext* global_context = new casper::V8::Wrapper::GlobalContext(singleton.isolate_);
        
        casper::V8::Wrapper::ClientContext* client_context = new casper::V8::Wrapper::ClientContext(singleton.isolate_, global_context);
        
        v8::Local<v8::Context> context = global_context->context_;
        if (context.IsEmpty()) {
            fprintf(stderr, "Error creating context\n");
            return 1;
        }
        
        std::string script_file;
        std::string json_file;
        
        const int arg_rv = parse_args(argc, argv, script_file, json_file);
        if ( 0 != arg_rv ) {
            return arg_rv;
        }

        
        //------------------------------------------------------------------------------
        
        /*
         static const int kBufferSize = 256;
         char buffer[kBufferSize];
         char* str = fgets(buffer, kBufferSize, stdin);
         v8::String::NewFromUtf8(context->GetIsolate(), str,
         v8::NewStringType::kNormal).ToLocalChecked()
         */
        
        v8::Context::Scope context_scope(context);
        //Compile files given in stdin
//        result = RunMain(isolate, platform, argc, argv);
        
        // Use all other arguments as names of files to load and run.
        v8::Local<v8::String> source;
        if ( ! ReadFileToV8String(singleton.isolate_, script_file.c_str()).ToLocal(&source) ) {
            fprintf(stderr, "Error reading '%s'\n", script_file.c_str());
            return -1;
        }
        
        v8::Local<v8::String> file_name = v8::String::NewFromUtf8(singleton.isolate_, script_file.c_str(), v8::NewStringType::kNormal).ToLocalChecked();

        if ( false == ExecuteString(context->GetIsolate(), source, file_name, false, true) ) {
            fprintf(stderr, "Error while compiling JS '%s'\n", script_file.c_str());
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
        
        auto start1 = std::chrono::high_resolution_clock::now();
        
        //std::ifstream ifs("jsonapi.json");
        std::ifstream ifs("/Users/bruno/work/jayscriptor/test.json");
        std::string content( (std::istreambuf_iterator<char>(ifs)),
                            (std::istreambuf_iterator<char>()) );
        
        v8::Local<v8::Value> json_data = v8::JSON::Parse(context,
                                                         v8::String::NewFromUtf8(context->GetIsolate(), content.c_str(), v8::NewStringType::kNormal).ToLocalChecked()).ToLocalChecked();
        auto end1 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( end1 - start1 ).count();
        std::cout << "\nTime for JSON Parse: " << (duration)/1000.0 << "ms\n\n";
        
        //Convert JSON
        //  json_args[0]=json_data;
        //  if (!convert_json->Call(context, context->Global(), 1, json_args).ToLocal(&json_data_final))
        //    printf("error..\n");
        
        
        //Calculate the expressions-------------------------------------------------
        
        int cnt0=1;
        int cnt1=1;
        int cnt2=4;
        
      //  auto start = std::chrono::high_resolution_clock::now();
        
                v8::Local<v8::Value>     args[3];
                v8::Local<v8::Value>     js_result;

        
        for(int ii=0; ii<cnt0; ii++){
            for(int i=0; i<cnt1; i++){
                
                //const char* arg1 = "dados1";
                const char* arg2 = std::to_string(i).c_str();
                //args[1] = v8::String::NewFromUtf8(context->GetIsolate(), arg1, v8::NewStringType::kNormal).ToLocalChecked();
                //args[1] = json_data_final;
                args[1] = json_data;
                args[2] = v8::String::NewFromUtf8(context->GetIsolate(), arg2, v8::NewStringType::kNormal).ToLocalChecked();
                
                for(int l=0; l<cnt2; l++){
                    
                    const char* arg0 = std::to_string(l+1).c_str();
                    args[0] = v8::String::NewFromUtf8(context->GetIsolate(), arg0, v8::NewStringType::kNormal).ToLocalChecked();
                    
                    if ( false == client_context->ExecuteFunction("calc_tipo1", 3, args, js_result) ) {
                        printf("error..\n");
                    } else {
                        v8::String::Utf8Value str_2(js_result);
                        const char* cstr = casper::V8::Wrapper::GlobalContext::ToCString(str_2);
                        printf("%s\n", cstr);
                    }

                }
            }
        }
       // auto end = std::chrono::high_resolution_clock::now();
       // printf("%s\n", resultado);
       // std::cout << "------Output:\n\n" << resultado.GetText() << "\n\n------------\n";
       // auto elapsed_seconds = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();
       // std::cout << "\nV8 ---> nr of operations: " << cnt1 * cnt2 * cnt0
       // << "\nTime for each operation: " << (elapsed_seconds/1000.0)/(cnt1*cnt2*cnt0) << " ms\n";
        
        
    }
    return result;
}

