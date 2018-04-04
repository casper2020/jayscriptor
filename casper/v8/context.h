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

#pragma once
#ifndef NRS_CASPER_V8_CONTEXT_H_
#define NRS_CASPER_V8_CONTEXT_H_

#include "libplatform/libplatform.h"
#include "v8.h"

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

namespace casper
{
    
    namespace v8
    {
        
        class Context
        {
            
        public: // Data Type(s)
            
            typedef struct
            {
                const char* const name_;
            } Function;
            
            typedef std::vector<Function>                            FunctionsVector;
            typedef std::function<void(const char* const a_message)> TraceCallback;
            
        private: // Data Type(s)
            
            class LoadedFunction
            {
                
            public: // Const Data
                
                const std::string name_;

            public:
                
                ::v8::Eternal<::v8::Function> f_;
                
            public: // Constructor(s) / Destructor
                
                LoadedFunction (const char* const a_name)
                    : name_(a_name)
                {
                    /* empty */
                }
                
            } ;
            
        public: // Data Type(s)
            
            typedef std::vector<std::string> Expressions;
            
        public: // Data
            
            ::v8::Isolate*               isolate_;
            ::v8::Eternal<::v8::Context> context_;
            ::v8::Eternal<::v8::String>  raw_script_;       // TODO do we need this?
            ::v8::Eternal<::v8::String>  compiled_script_;  // TODO do we need this?
            ::v8::Eternal<::v8::Script>  script_;           // TODO do we need this?
            
        private: // Data
            
            std::map<std::string, LoadedFunction*> functions_;
            std::stringstream                      tmp_trace_ss_;
            
        public: // Constructor(s) / Destructor
                        
            Context ();
            virtual ~Context ();
            
        public: // Method(s) / Function(s)
            
            bool Compile       (const ::v8::Local<::v8::String>& a_script, const FunctionsVector* a_functions = nullptr, const TraceCallback a_on_error = nullptr);
            
            bool LoadFunctions (const FunctionsVector& a_functions, const TraceCallback a_on_error = nullptr);
            bool LoadFunctions (const FunctionsVector& a_functions, ::v8::Local<::v8::Context>& a_context, ::v8::Context::Scope& a_scope,
                                const TraceCallback a_on_error = nullptr);

            bool CallFunction  (const char* a_name, const int a_n_args, ::v8::Local<::v8::Value>* a_argv,
                                ::v8::Persistent<::v8::Value>& o_result,
                                const TraceCallback a_on_error = nullptr);
            
            bool CallFunction (::v8::Local<::v8::Context>& a_context, const char* a_name, const int a_n_args, ::v8::Local<::v8::Value>* a_argv,
                               ::v8::Persistent<::v8::Value>& o_result,
                               const TraceCallback a_on_error = nullptr);
            
            bool LoadExpressions (const char* const a_name,
                                  const Expressions& a_expressions,
                                  const TraceCallback a_on_error = nullptr);
            
            bool LoadData       (const char* const a_name, const char* const a_data,
                                 const TraceCallback a_on_error = nullptr,
                                 ::v8::Persistent<::v8::Value>* o_object = nullptr);

        private: // Method(s) / Function(s)
            
            void TraceException (::v8::TryCatch* a_try_catch, const TraceCallback a_on_error);
            bool TraceException (::v8::TryCatch* a_try_catch, std::string& o_trace);
            void LogException   (::v8::TryCatch* a_try_catch);            
            
        private: // Static Method(s) / Function(s)

            static void DebugLog (const ::v8::FunctionCallbackInfo<::v8::Value>& a_args);
            
        public: // Static Method(s) / Function(s)
            
            // Extracts a C string from a V8 Utf8Value.
            static const char* ToCString (const ::v8::String::Utf8Value& a_value)
            {
                return *a_value ? *a_value : "<string conversion failed>";
            }
            
        }; // end of class 'ClientContext'
        
    } // end of namespace 'v8'
    
} // end of namespace 'casper'

#endif // NRS_CASPER_V8_CONTEXT_H_
