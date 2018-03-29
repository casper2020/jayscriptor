
#pragma once
#ifndef NRS_CASPER_V8_CONTEXT_H_
#define NRS_CASPER_V8_CONTEXT_H_

#include "libplatform/libplatform.h"
#include "v8.h"

#include <map>
#include <string>

namespace casper
{
    
    namespace v8
    {
        
        class Context
        {
            
        public: // Data Type(s)
            
            typedef struct
            {
                const char* name_;
            } Function;
            
        private: // Data Type(s)
            
            class LoadedFunction
            {
                
            public: // Const Data
                
                const std::string name_;

            public:
                
                ::v8::Global<::v8::Function> f_;
                
            public: // Constructor(s) / Destructor
                
                LoadedFunction (const char* const a_name)
                    : name_(a_name)
                {
                    /* empty */
                }
                
            } ;
            
        public: // Data
            
            ::v8::Isolate*               isolate_;
            ::v8::Isolate::CreateParams  create_params_;
            
            ::v8::Global<::v8::Context>  context_;
            
            std::map<std::string, LoadedFunction*> functions_;
            
            
            ::v8::Local<::v8::String>    script_;
            ::v8::Local<::v8::String>    compiled_script_;
            
        public: // Constructor(s) / Destructor
            
            Context ()
            {
                create_params_.array_buffer_allocator = ::v8::ArrayBuffer::Allocator::NewDefaultAllocator();
                isolate_       = ::v8::Isolate::New(create_params_);                
            }
            
            virtual ~Context ()
            {
                isolate_->Dispose();
                delete create_params_.array_buffer_allocator;
                context_.Reset();
            }
            
        public: // Method(s) / Function(s)
            
            bool Compile (const ::v8::Local<::v8::String>& a_script, const std::vector<Function>* a_functions = nullptr)
            {
                script_ = a_script;
                
                
//                Local<ObjectTemplate> global = ObjectTemplate::New(GetIsolate());
                
                // We're just about to compile the script; set up an error handler to
                // catch any exceptions the script might throw.
                ::v8::TryCatch try_catch(isolate_);
                
                // Each processor gets its own context so different processors don't
                // affect each other. Context::New returns a persistent handle which
                // is what we need for the reference to remain after we return from
                // this method. That persistent handle has to be disposed in the
                // destructor.
                ::v8::Local<::v8::ObjectTemplate> global = ::v8::ObjectTemplate::New(isolate_);
                
                global->Set(::v8::String::NewFromUtf8(isolate_,
                                                      "DebugLog",
                                                      ::v8::NewStringType::kNormal).ToLocalChecked(),
                            ::v8::FunctionTemplate::New(isolate_, DebugLog)
                );
                
                ::v8::Local<::v8::Context> context = ::v8::Context::New(isolate_, NULL, global);
                context_.Reset(isolate_, context);
                
                ::v8::Context::Scope context_scope(context);
                
                //
                // Compile the script and check for errors.
                //
                ::v8::HandleScope         handle_scope (isolate_);

                ::v8::Local<::v8::Script> compiled_script;
                if ( ! ::v8::Script::Compile(context, script_).ToLocal(&compiled_script) ) {
                    // write to log
                    LogException(isolate_, &try_catch);
                    // The script failed to compile; bail out.
                    return false;
                }
                
                //
                // Run the script!
                //
                ::v8::Local<::v8::Value> result;
                if ( ! compiled_script->Run(context).ToLocal(&result) ) {
                    // write to log
                    LogException(isolate_, &try_catch);
                    // Running the script failed; bail out.
                    return false;
                }
                
                //
                // Load functions
                //
                if ( nullptr != a_functions ) {
                    return LoadFunctions(*a_functions, context, context_scope);
                } else {
                    return true;
                }
            }
            
            bool LoadFunctions (const std::vector<Function>& a_functions)
            {
                // Create a handle scope to keep the temporary object references.
                ::v8::HandleScope handle_scope(isolate_);
                
                // Create a new local context
                ::v8::Local<::v8::Context> context = ::v8::Local<::v8::Context>::New(isolate_, context_);
                
                // Enter this function's context so all the remaining operations take place there
                ::v8::Context::Scope context_scope(context);
                
                return LoadFunctions(a_functions, context, context_scope);
            }
            

            bool ExecuteFunction (const char* a_name, const int a_n_args, ::v8::Local<::v8::Value> a_args[], ::v8::Local<::v8::Value>& o_result)
            {
                // pick function info
                const auto it = functions_.find(a_name);
                if ( functions_.end() == it ) {
                    // not found
                    return false;
                }

                // Create a handle scope to keep the temporary object references.
                ::v8::HandleScope handle_scope(isolate_);

                // Create a new local context
                ::v8::Local<::v8::Context> context = ::v8::Local<::v8::Context>::New(isolate_, context_);

                // Enter this function's context so all the remaining operations take place there
                ::v8::Context::Scope context_scope(context);

                // Set up an exception handler before calling the function
                ::v8::TryCatch try_catch(isolate_);

                // Grab 'local' function
                ::v8::Local<::v8::Function> local_function = ::v8::Local<::v8::Function>::New(isolate_, it->second->f_);

                // Call function
                const bool rv = local_function->Call(context, context->Global(), a_n_args, a_args).ToLocal(&o_result);
                if ( false == rv ) {
                    LogException(isolate_, &try_catch);
                }
                return rv;
            }
            
            bool ExecuteFunction (::v8::Local<::v8::Context>& a_context, const char* a_name, const int a_n_args, ::v8::Local<::v8::Value> a_args[], ::v8::Local<::v8::Value>& o_result)
            {
                // pick function info
                const auto it = functions_.find(a_name);
                if ( functions_.end() == it ) {
                    // not found
                    return false;
                }
                
                // Set up an exception handler before calling the function
                ::v8::TryCatch try_catch(isolate_);
                
                // Grab 'local' function
                ::v8::Local<::v8::Function> local_function = ::v8::Local<::v8::Function>::New(isolate_, it->second->f_);
                
                const bool rv = local_function->Call(a_context, a_context->Global(), a_n_args, a_args).ToLocal(&o_result);
                if ( false == rv ) {
                    LogException(isolate_, &try_catch);
                }
                return rv;
            }
            
            
            
            // The callback that is invoked by v8 whenever the JavaScript 'DebugLog'
            // function is called.
            // Prints its arguments on stdout separated by spaces and ending with a newline.
            static void DebugLog (const ::v8::FunctionCallbackInfo<::v8::Value>& args)
            {
                bool first = true;
                for ( int i = 0; i < args.Length(); i++ ) {
                    ::v8::HandleScope handle_scope(args.GetIsolate());
                    if ( true == first ) {
                        first = false;
                    } else {
                        fprintf(stdout, " ");
                    }
                    ::v8::String::Utf8Value str(args[i]);
                    const char* cstr = casper::v8::Context::ToCString(str);
                    fprintf(stdout, "%s", cstr);
                }
                fprintf(stdout, "\n");
                fflush(stdout);
            }
            
            // Extracts a C string from a V8 Utf8Value.
            static const char* ToCString (const ::v8::String::Utf8Value& a_value)
            {
                return *a_value ? *a_value : "<string conversion failed>";
            }
            
        private: // Method(s) / Function(s)
            
            bool LoadFunctions (const std::vector<Function>& a_functions, ::v8::Local<::v8::Context>& a_context, ::v8::Context::Scope& a_scope)
            {
                // catch any exceptions the script might throw.
                ::v8::TryCatch try_catch(isolate_);
                
                for ( auto it : a_functions ) {
                    ::v8::Local<::v8::String> func_name = ::v8::String::NewFromUtf8(isolate_, it.name_, ::v8::NewStringType::kNormal).ToLocalChecked();
                    ::v8::Local<::v8::Value>  process_val;
                    // If there is no function, or if it is not a function, bail out
                    if ( ! a_context->Global()->Get(a_context, func_name).ToLocal(&process_val) || ! process_val->IsFunction() ) {
                        const std::string msg = std::string("Unable to load function ") + it.name_;
                        // write to log
                        LogException(isolate_, &try_catch, &msg);
                        // Failed to load function; bail out.
                        return false;
                    }
                    // It is a function; cast it to a Function
                    ::v8::Local<::v8::Function> process_fun = ::v8::Local<::v8::Function>::Cast(process_val);
                    
                    // Keep track of new funcion
                    LoadedFunction* function = new LoadedFunction(it.name_);
                    
                    functions_[it.name_] = function;
                    
                    // Store the function in a Global handle, since we also want
                    // that to remain after this call returns
                    function->f_.Reset(isolate_, process_fun);
                }
                
                return true;
            }
            
            void LogException (::v8::Isolate* a_isolate, ::v8::TryCatch* a_try_catch, const std::string* a_where = nullptr)
            {
                ::v8::HandleScope       handle_scope(a_isolate);
                ::v8::String::Utf8Value exception(a_try_catch->Exception());
                
                const char* exception_string;
                if ( 0 == exception.length() ) {
                    exception_string = ( a_where ? a_where->c_str() : "???" );
                } else {
                    exception_string = casper::v8::Context::ToCString(exception);
                }
                
                ::v8::Local<::v8::Message> message = a_try_catch->Message();
                if ( message.IsEmpty() ) {
                    // V8 didn't provide any extra information about this error; just print the exception.
                    fprintf(stderr, "%s\n", exception_string);
                } else {
                    // Print (filename):(line number): (message).
                    ::v8::String::Utf8Value    filename(message->GetScriptOrigin().ResourceName());
                    ::v8::Local<::v8::Context> context(a_isolate->GetCurrentContext());
                    
                    const char* filename_string = casper::v8::Context::ToCString(filename);
                    const int linenum = message->GetLineNumber(context).FromJust();
                    fprintf(stderr, "%s:%i: %s\n", filename_string, linenum, exception_string);
                    
                    // Print line of source code.
                    ::v8::String::Utf8Value sourceline(message->GetSourceLine(context).ToLocalChecked());
                    const char* sourceline_string = casper::v8::Context::ToCString(sourceline);
                    fprintf(stderr, "%s\n", sourceline_string);
                    
                    // Print wavy underline (GetUnderline is deprecated).
                    const int start = message->GetStartColumn(context).FromJust();
                    for ( int i = 0; i < start; i++ ) {
                        fprintf(stderr, " ");
                    }
                    
                    const int end = message->GetEndColumn(context).FromJust();
                    for ( int i = start; i < end; i++ ) {
                        fprintf(stderr, "^");
                    }
                    fprintf(stderr, "\n");
                    
                    ::v8::Local<::v8::Value> stack_trace_string;
                    if ( a_try_catch->StackTrace(context).ToLocal(&stack_trace_string) && stack_trace_string->IsString() && ::v8::Local<::v8::String>::Cast(stack_trace_string)->Length() > 0 ) {
                        ::v8::String::Utf8Value stack_trace(stack_trace_string);
                        const char* stack_trace_string = casper::v8::Context::ToCString(stack_trace);
                        fprintf(stderr, "%s\n", stack_trace_string);
                    }
                }
            }
            
        }; // end of class 'ClientContext'
        
    } // end of namespace 'v8'
    
} // end of namespace 'casper'

#endif // NRS_CASPER_V8_CONTEXT_H_
