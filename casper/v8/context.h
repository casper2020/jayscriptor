
#pragma once
#ifndef NRS_CASPER_V8_CONTEXT_H_
#define NRS_CASPER_V8_CONTEXT_H_

#include "libplatform/libplatform.h"
#include "v8.h"

namespace casper
{
    
    namespace v8
    {
        
        class Context
        {
            
        public: // Data
            
            ::v8::Isolate*               isolate_;
            ::v8::Isolate::CreateParams  create_params_;
            
            ::v8::Global<::v8::Context>  context_;
            ::v8::Local<::v8::String>    script_;
            ::v8::Local<::v8::String>    compiled_script_;
            
        public: // Constructor(s) / Destructor
            
            Context ()
            {
                create_params_.array_buffer_allocator = ::v8::ArrayBuffer::Allocator::NewDefaultAllocator();
                isolate_ = ::v8::Isolate::New(create_params_);
            }
            
            virtual ~Context ()
            {
                isolate_->Dispose();
                delete create_params_.array_buffer_allocator;
                context_.Reset();
            }
            
        public: // Method(s) / Function(s)
            
            bool Compile (const ::v8::Local<::v8::String>& a_script)
            {
                script_ = a_script;
                
                ::v8::HandleScope handle_scope (isolate_);
                
                // We're just about to compile the script; set up an error handler to
                // catch any exceptions the script might throw.
                ::v8::TryCatch try_catch(isolate_);
                
                ::v8::Local<::v8::Context> context(isolate_->GetCurrentContext());
                
                // Compile the script and check for errors.
                ::v8::Local<::v8::Script> compiled_script;
                if ( ! ::v8::Script::Compile(context, script_).ToLocal(&compiled_script) ) {
                    ::v8::String::Utf8Value error(try_catch.Exception());
//                    Log(*error);
                    // The script failed to compile; bail out.
                    return false;
                }
                
                // Run the script!
                ::v8::Local<::v8::Value> result;
                if ( ! compiled_script->Run(context).ToLocal(&result) ) {
                    // The TryCatch above is still in effect and will have caught the error.
                    ::v8::String::Utf8Value error(try_catch.Exception());
//                    Log(*error);
                    // Running the script failed; bail out.
                    return false;
                }
                
                return true;
            }
            
            bool ExecuteFunction (const char* a_name, const int a_n_args, ::v8::Local<::v8::Value> a_args[], ::v8::Local<::v8::Value>& o_result)
            {
//                ::v8::Isolate::Scope isolate_scope(isolate_);
                ::v8::HandleScope    handle_scope(isolate_);
                
                // create a function local context
                ::v8::Local<::v8::Context> context = ::v8::Local<::v8::Context>::New(isolate_, context_);

                ::v8::Local<::v8::String>   func_name = ::v8::String::NewFromUtf8(isolate_, a_name, ::v8::NewStringType::kNormal).ToLocalChecked();
                
                // G
                ::v8::Local<::v8::Object>   global = context->Global();
                ::v8::Local<::v8::Value>    value = global->Get(context, func_name).ToLocalChecked();
                ::v8::Local<::v8::Function> func  = ::v8::Local<::v8::Function>::Cast(value);
                
                // C
                return func->Call(context, global, a_n_args, a_args).ToLocal(&o_result);
            }
            
            
            // Executes a string within the current v8 context.
            bool ExecuteString(::v8::Local<::v8::String> source, ::v8::Local<::v8::Value> name, bool print_result, bool report_exceptions) {
                ::v8::HandleScope handle_scope(isolate_);
                ::v8::TryCatch try_catch(isolate_);
                ::v8::ScriptOrigin origin(name);
                ::v8::Local<::v8::Context> context(isolate_->GetCurrentContext());
                ::v8::Local<::v8::Script> script;
                if (!::v8::Script::Compile(context, source, &origin).ToLocal(&script)) {
                    // Print errors that happened during compilation.
                    if (report_exceptions)
                        ReportException(isolate_, &try_catch);
                    return false;
                } else {
                    ::v8::Local<::v8::Value> result;
                    if (!script->Run(context).ToLocal(&result)) {
                        //assert(try_catch.HasCaught());
                        // Print errors that happened during execution.
                        if (report_exceptions)
                            ReportException(isolate_, &try_catch);
                        return false;
                    } else {
                        //assert(!try_catch.HasCaught());
                        if (print_result && !result->IsUndefined()) {
                            // If all went well and the result wasn't undefined then print
                            // the returned value.
                            ::v8::String::Utf8Value str(result);
                            const char* cstr = casper::v8::Context::ToCString(str);
                            printf("%s\n", cstr);
                        }
                        return true;
                    }
                }
            }
            
            
            void ReportException(::v8::Isolate* isolate, ::v8::TryCatch* try_catch) {
                ::v8::HandleScope handle_scope(isolate);
                ::v8::String::Utf8Value exception(try_catch->Exception());
                const char* exception_string = casper::v8::Context::ToCString(exception);
                ::v8::Local<::v8::Message> message = try_catch->Message();
                if (message.IsEmpty()) {
                    // V8 didn't provide any extra information about this error; just
                    // print the exception.
                    fprintf(stderr, "%s\n", exception_string);
                } else {
                    // Print (filename):(line number): (message).
                    ::v8::String::Utf8Value filename(message->GetScriptOrigin().ResourceName());
                    ::v8::Local<::v8::Context> context(isolate->GetCurrentContext());
                    const char* filename_string = casper::v8::Context::ToCString(filename);
                    int linenum = message->GetLineNumber(context).FromJust();
                    fprintf(stderr, "%s:%i: %s\n", filename_string, linenum, exception_string);
                    // Print line of source code.
                    ::v8::String::Utf8Value sourceline(
                                                       message->GetSourceLine(context).ToLocalChecked());
                    const char* sourceline_string = casper::v8::Context::ToCString(sourceline);
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
                    ::v8::Local<::v8::Value> stack_trace_string;
                    if (try_catch->StackTrace(context).ToLocal(&stack_trace_string) &&
                        stack_trace_string->IsString() &&
                        ::v8::Local<::v8::String>::Cast(stack_trace_string)->Length() > 0) {
                        ::v8::String::Utf8Value stack_trace(stack_trace_string);
                        const char* stack_trace_string = casper::v8::Context::ToCString(stack_trace);
                        fprintf(stderr, "%s\n", stack_trace_string);
                    }
                }
            }
            
            
            // The callback that is invoked by v8 whenever the JavaScript 'print'
            // function is called.  Prints its arguments on stdout separated by
            // spaces and ending with a newline.
            static void Print (const ::v8::FunctionCallbackInfo<::v8::Value>& args)
            {
                bool first = true;
                for (int i = 0; i < args.Length(); i++) {
                    ::v8::HandleScope handle_scope(args.GetIsolate());
                    if (first) {
                        first = false;
                    } else {
                        printf(" ");
                    }
                    ::v8::String::Utf8Value str(args[i]);
                    const char* cstr = casper::v8::Context::ToCString(str);
                    printf("%s", cstr);
                }
                printf("\n");
                fflush(stdout);
            }
            
            // Extracts a C string from a V8 Utf8Value.
            static const char* ToCString (const ::v8::String::Utf8Value& a_value)
            {
                return *a_value ? *a_value : "<string conversion failed>";
            }
            
        }; // end of class 'ClientContext'
        
    } // end of namespace 'v8'
    
} // end of namespace 'casper'

#endif // NRS_CASPER_V8_CONTEXT_H_
