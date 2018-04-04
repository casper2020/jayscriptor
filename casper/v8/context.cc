/**
 * @file context.h
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

#include "casper/v8/context.h"

/**
 * @brief Default constructor.
 */
casper::v8::Context::Context ()
{
    // https://github.com/v8/v8/wiki/Embedder%27s-Guide

    ::v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = ::v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    // prepare isotale
    isolate_                                  = ::v8::Isolate::New(create_params);
    // prepare context
    ::v8::HandleScope                 handle_scope (isolate_);
    // add debug function
    ::v8::Local<::v8::ObjectTemplate> global  = ::v8::ObjectTemplate::New(isolate_);
    global->Set(::v8::String::NewFromUtf8(isolate_,
                                          "DebugLog",
                                          ::v8::NewStringType::kNormal).ToLocalChecked(),
                                          ::v8::FunctionTemplate::New(isolate_, DebugLog
        )
    );
    // make it eternal
    ::v8::Local<::v8::Context> context = ::v8::Context::New(isolate_, NULL, global);
    context_.Set(isolate_, context);
}

/**
 * @brief Destructor constructor.
 */
casper::v8::Context::~Context ()
{
    // release isolate and context
    isolate_->Dispose();
}

#ifdef __APPLE__
#pragma mark -
#endif

/**
 * @brief Compile a script and ( optionaly ) load some functions from it.
 *
 * @param a_script
 * @param a_functions
 * @param a_on_error
 *
 * @return
 */
bool casper::v8::Context::Compile (const ::v8::Local<::v8::String>& a_script,
                                   const casper::v8::Context::FunctionsVector* a_functions, const casper::v8::Context::TraceCallback a_on_error)
{
    // set up an error handler to catch any exceptions the script might throw.
    ::v8::TryCatch try_catch(isolate_);
    
    raw_script_.Set(isolate_, a_script);
    
    // Each processor gets its own context so different processors don't
    // affect each other. Context::New returns a persistent handle which
    // is what we need for the reference to remain after we return from
    // this method. That persistent handle has to be disposed in the
    // destructor.
    
    ::v8::Local<::v8::Context> context = context_.Get(isolate_);
    
    ::v8::Context::Scope       context_scope(context);
    ::v8::HandleScope          handle_scope (isolate_);
    
    //
    // Compile the script and check for errors.
    //
    ::v8::Local<::v8::Script> local_compiled_script;
    if ( false == ::v8::Script::Compile(context, raw_script_.Get(isolate_)).ToLocal(&local_compiled_script) ) {
        //
        // the script failed to compile
        //
        // ... report it ...
        if ( nullptr != a_on_error ) {
            TraceException(&try_catch, a_on_error);
        } else {
            LogException(&try_catch);
        }
        // ... and bail out
        return false;
    }
    // make it permanent
    script_.Set(isolate_, local_compiled_script);
    
    //
    // Run the script
    //
    ::v8::Local<::v8::Value> result;
    if ( false == script_.Get(isolate_)->Run(context).ToLocal(&result) ) {
        //
        // the script failed to run
        //
        // ... report it ...
        if ( nullptr != a_on_error ) {
            TraceException(&try_catch, a_on_error);
        } else {
            LogException(&try_catch);
        }
        // ... and bail out
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

/**
 * @brief Load some functions previously compiled.
 *
 * @param a_functions
 * @param a_on_error
 *
 * @return
 */
bool casper::v8::Context::LoadFunctions (const casper::v8::Context::FunctionsVector& a_functions,
                                         const casper::v8::Context::TraceCallback a_on_error)
{
    // set up an error handler to catch any exceptions the script might throw.
    ::v8::TryCatch try_catch(isolate_);
    
    // Create a handle scope to keep the temporary object references.
    ::v8::HandleScope handle_scope(isolate_);
    
    // Create a new local context
    ::v8::Local<::v8::Context> context = context_.Get(isolate_);
    
    // Enter this function's context so all the remaining operations take place there
    ::v8::Context::Scope context_scope(context);
    
    return LoadFunctions(a_functions, context, context_scope);
}

/**
 * @brief Load some functions previously compiled for a specific context and scope.
 *
 * @param a_functions
 * @param a_context
 * @param a_scope
 * @param a_on_error
 *
 * @return
 */
bool casper::v8::Context::LoadFunctions (const FunctionsVector& a_functions, ::v8::Local<::v8::Context>& a_context,
                                         ::v8::Context::Scope& a_scope,
                                         const casper::v8::Context::TraceCallback a_on_error)
{
    // catch any exceptions the script might throw.
    ::v8::TryCatch try_catch(isolate_);
    
    for ( auto it : a_functions ) {
        
        const ::v8::Local<::v8::String> func_name = ::v8::String::NewFromUtf8(isolate_, it.name_, ::v8::NewStringType::kNormal).ToLocalChecked();
        ::v8::Local<::v8::Value>  process_val;
        // If there is no function, or if it is not a function, bail out
        if ( ! a_context->Global()->Get(a_context, func_name).ToLocal(&process_val) || ! process_val->IsFunction() ) {
            //
            // failed to load function
            //
            // ... report it ...
            if ( nullptr != a_on_error ) {
                TraceException(&try_catch, a_on_error);
            } else {
                LogException(&try_catch);
            }
            // ... and bail out
            return false;
        }
        // It is a function; cast it to a Function
        const ::v8::Local<::v8::Function> process_fun = ::v8::Local<::v8::Function>::Cast(process_val);
        
        // create a new \link LoadedFunction \link
        LoadedFunction* function = new LoadedFunction(it.name_);
        
        // keep track of new funcion
        functions_[it.name_] = function;
        
        // store the function in a Global handle,
        // since we also want that to remain after this call returns
        function->f_.Set(isolate_, process_fun);
        
    }
    
    // done
    return true;
}

#ifdef __APPLE__
#pragma mark -
#endif

/**
 * @brief Execute a previously load function.
 *
 * @param a_name
 * @param a_n_args
 * @param a_args
 * @param o_result
 * @param a_on_error
 *
 * @return
 */
bool casper::v8::Context::CallFunction (const char* a_name, const int a_argc, ::v8::Local<::v8::Value>* a_argv,
                                        ::v8::Persistent<::v8::Value>& o_result,
                                        const casper::v8::Context::TraceCallback a_on_error)
{
    // pick function info
    const auto it = functions_.find(a_name);
    if ( functions_.end() == it ) {
        // not found
        return false;
    }
    
    // set up an error handler to catch any exceptions the script might throw.
    ::v8::TryCatch try_catch(isolate_);
    
    // create a handle scope to keep the temporary object references.
    ::v8::HandleScope handle_scope(isolate_);
    
    // create a new local context
    ::v8::Local<::v8::Context> context = context_.Get(isolate_);
    
    // enter this function's context so all the remaining operations take place there
    ::v8::Context::Scope context_scope(context);
    
    // grab function
    ::v8::Local<::v8::Function> local_function = it->second->f_.Get(isolate_);
    
    // call function
//    auto a = local_function->Call(context, context->Global(), a_argc, a_argv);
    ::v8::Local<::v8::Value> local_result;
    const bool rv = local_function->Call(context, context->Global(), a_argc, a_argv).ToLocal(&local_result);
    if ( false == rv ) {
        if ( nullptr != a_on_error ) {
            TraceException(&try_catch, a_on_error);
        } else {
            LogException(&try_catch);
        }
    } else {
        o_result.Reset(isolate_, local_result);
    }
    
    // done
    return rv;
}

/**
 * @brief Execute a previously load function for a specific context.
 *
 * @param a_name
 * @param a_n_args
 * @param a_args
 * @param o_result
 * @param a_on_error
 *
 * @return
 */
bool casper::v8::Context::CallFunction (::v8::Local<::v8::Context>& a_context, const char* a_name, const int a_n_args, ::v8::Local<::v8::Value>* a_args,
                                        ::v8::Persistent<::v8::Value>& o_result,
                                        const casper::v8::Context::TraceCallback a_on_error)
{
    // pick function info
    const auto it = functions_.find(a_name);
    if ( functions_.end() == it ) {
        // not found
        return false;
    }
    
    // set up an error handler to catch any exceptions the script might throw.
    ::v8::TryCatch try_catch(isolate_);
    
    // grab function
    ::v8::Local<::v8::Function> local_function = it->second->f_.Get(isolate_);
    
    // call function
    ::v8::Local<::v8::Value> local_result;
    const bool rv = local_function->Call(a_context, a_context->Global(), a_n_args, a_args).ToLocal(&local_result);
    if ( false == rv ) {
        if ( nullptr != a_on_error ) {
            TraceException(&try_catch, a_on_error);
        } else {
            LogException(&try_catch);
        }
    } else {
        o_result.Reset(isolate_, local_result);
    }
    
    // done
    return rv;
}

#ifdef __APPLE__
#pragma mark -
#endif

/**
 * @brief Collect all available data about an exception and peform a callback.
 *
 * @param a_try_catch
 * @param a_on_error
 */
void casper::v8::Context::TraceException (::v8::TryCatch* a_try_catch, const casper::v8::Context::TraceCallback a_on_error)
{
    std::string trace_str;
    if ( true == casper::v8::Context::TraceException(a_try_catch, trace_str) ) {
        a_on_error(trace_str.c_str());
    } else {
        a_on_error("An untraceable exception occurred while calleing a function at V8 context!\n");
    }
}

/**
 * @brief Collect all available data about an exception and return it as a string.
 *
 * @param a_try_catch
 * @param a_on_error
 */
bool casper::v8::Context::TraceException (::v8::TryCatch* a_try_catch, std::string& o_trace)
{
    ::v8::HandleScope       handle_scope(isolate_);
    ::v8::String::Utf8Value exception(a_try_catch->Exception());
    
    //
    // Data provided?
    //
    if ( 0 == exception.length() ) {
        // no - can't trace it
        return false;
    }
    
    const char* const exception_c_str = casper::v8::Context::ToCString(exception);
    
    //
    // Message provided?
    //
    const ::v8::Local<::v8::Message> message = a_try_catch->Message();
    if ( true == message.IsEmpty() ) {
        //
        // no, v8 DIDN'T provide any extra information about this error - just print the exception
        //
        o_trace = exception_c_str;
        return true;
    }
    
    tmp_trace_ss_.str("");
    
    //
    // v8 DID provide any extra information about this error - collect all available info
    //
    const ::v8::String::Utf8Value filename(message->GetScriptOrigin().ResourceName());

    // grab context
    ::v8::Local<::v8::Context> context = context_.Get(isolate_);
    
    // <filename>:<line number>: <message>
    tmp_trace_ss_ << casper::v8::Context::ToCString(filename) << ':' << message->GetLineNumber(context).FromJust() << ": " << exception_c_str << '\n';
    
    // line of source code.
    const ::v8::String::Utf8Value source_line(message->GetSourceLine(context).ToLocalChecked());
    
    tmp_trace_ss_ << casper::v8::Context::ToCString(source_line) << '\n';
    
    // print wavy underline (GetUnderline is deprecated).
    const int start = message->GetStartColumn(context).FromJust();
    for ( int i = 0; i < start; i++ ) {
        tmp_trace_ss_ << '~';
    }
    
    const int end = message->GetEndColumn(context).FromJust();
    for ( int i = start; i < end; i++ ) {
        tmp_trace_ss_ << '^';
    }
    
    ::v8::Local<::v8::Value> stack_trace_v8_string;
    if ( a_try_catch->StackTrace(context).ToLocal(&stack_trace_v8_string)
        &&
        stack_trace_v8_string->IsString()
        &&
        ::v8::Local<::v8::String>::Cast(stack_trace_v8_string)->Length() > 0
    ) {
        ::v8::String::Utf8Value stack_trace_utf8_str(stack_trace_v8_string);
        tmp_trace_ss_ << casper::v8::Context::ToCString(stack_trace_utf8_str);
    }
    
    // grab string
    o_trace = tmp_trace_ss_.str();
    
    // success if string is not empty
    return ( o_trace.length() > 0 );
}

/**
 * @brief Collect all available data about an exception and log it.
 *
 * @param a_try_catch
 * @param a_on_error
 */
void casper::v8::Context::LogException (::v8::TryCatch* a_try_catch)
{
    std::string trace_str;
    if ( true == casper::v8::Context::TraceException(a_try_catch, trace_str) ) {
        fprintf(stderr, "%s\n", trace_str.c_str());
    } else {
        fprintf(stderr, "An untraceable exception occurred while calleing a function at V8 context!\n");
    }
}

#ifdef __APPLE__
#pragma mark -
#endif

/**
 * @brief The callback that is invoked by v8 whenever the JavaScript 'DebugLog' function is called.
 *
 * @param a_args
 */
void casper::v8::Context::DebugLog (const ::v8::FunctionCallbackInfo<::v8::Value>& a_args)
{
    if ( 0 == a_args.Length() ) {
        return;
    }
    const ::v8::HandleScope handle_scope(a_args.GetIsolate());
    for ( int i = 0; i < a_args.Length(); i++ ) {
        ::v8::String::Utf8Value str(a_args[i]);
        const char* cstr = casper::v8::Context::ToCString(str);
        fprintf(stdout, " ");
        fprintf(stdout, "%s", cstr);
    }
    fprintf(stdout, " ");
    fprintf(stdout, "\n");
    fflush(stdout);
}
