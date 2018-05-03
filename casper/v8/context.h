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


#if ( defined(CASPER_V8_CHRONO_ENABLED) || defined(DEBUG) || defined(_DEBUG) || defined(ENABLE_DEBUG) )
    #define CASPER_V8_CHRONO_START(a_name) \
        const auto debug_##a_name## _start_tp = std::chrono::high_resolution_clock::now();
    #define CASPER_V8_CHRONO_ELPASED(a_name)[&]() -> size_t { \
        const auto debug_##a_name##_end_tp = std::chrono::high_resolution_clock::now(); \
        return static_cast<size_t>(std::chrono::duration_cast<std::chrono::microseconds>( debug_##a_name##_end_tp - debug_##a_name##_start_tp ).count()); \
    }()
    #define CASPER_V8_CHRONO_END(a_name, a_format, ...)[&]() -> size_t { \
        const auto debug_##a_name##_end_tp = std::chrono::high_resolution_clock::now(); \
        const auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>( debug_##a_name##_end_tp - debug_##a_name##_start_tp ).count(); \
        fprintf(stdout, \
                "%s:%d\n\tTook %lld us to " a_format "\n", \
                __PRETTY_FUNCTION__, __LINE__, \
                elapsed, \
                __VA_ARGS__ \
        ); \
        return static_cast<size_t>(elapsed); \
    }()
    #define CASPER_V8_SILENCE_UNUSED_VARIABLE __attribute__((unused))
#else
    #undef CASPER_V8_CHRONO_START
    #undef CASPER_V8_CHRONO_ELPASED
    #undef CASPER_V8_CHRONO_END
    #undef CASPER_V8_CHRONO_LOG
    #undef CASPER_V8_SILENCE_UNUSED_VARIABLE
#endif


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
            
        public: // Data Type(s)
            
            class LoadedFunction
            {
                
            public: // Data Type(s)
                
                typedef struct {
                    
                    const char* const          name_;
                    int                        argc_;
                    ::v8::Local<::v8::Value>*  argv_;
                    
                } Callable;
                
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
            
            typedef std::map<std::string, LoadedFunction*> LoadedFunctionsMap;
            
        public: // Data Type(s)
            
            typedef std::vector<std::string> Expressions;
            
        public: // Data
            
            ::v8::Isolate*               isolate_;
            ::v8::Eternal<::v8::Context> context_;
            ::v8::Eternal<::v8::Script>  script_;           // TODO do we need this?
            
        private: // Data
            
            LoadedFunctionsMap functions_;
            std::stringstream  tmp_trace_ss_;
            
        public: // Constructor(s) / Destructor
                        
            Context ();
            virtual ~Context ();
            
        public: // Method(s) / Function(s)
            
            bool Initialize    ();
            
            bool Parse         (const std::string& a_uri,
                                ::v8::Persistent<::v8::Object>& o_object, ::v8::Persistent<::v8::Value>& o_data);
            
            bool Compile       (const ::v8::Local<::v8::String>& a_script, const FunctionsVector* a_functions = nullptr, const TraceCallback a_on_error = nullptr);
            
            bool LoadFunctions (const FunctionsVector& a_functions, const TraceCallback a_on_error = nullptr);
            
            bool CallFunction  (const LoadedFunction::Callable& a_callable,
                                ::v8::Persistent<::v8::Value>& o_result,
                                const TraceCallback a_on_error = nullptr);
            
            bool LoadExpressions (const char* const a_name,
                                  const Expressions& a_expressions,
                                  const TraceCallback a_on_error = nullptr);
            
            bool LoadData       (const char* const a_name, const std::string& a_uri,
                                 const TraceCallback a_on_error = nullptr,
                                 ::v8::Persistent<::v8::Value>* o_object = nullptr,  ::v8::Persistent<::v8::Value>* o_value = nullptr);
            
            bool SetVar         (const ::v8::Local<::v8::Value> a_key,
                                 const ::v8::Local<::v8::Value> a_value, ::v8::Local<::v8::Value> a_json);
            
            const char* GetVar  (const ::v8::Local<::v8::Value> a_key,
                                 ::v8::Local<::v8::Value> a_json);


        private: // Method(s) / Function(s)
            
            static bool LoadFunctions (::v8::Local<::v8::Context>& a_context, ::v8::Context::Scope& a_scope, ::v8::TryCatch& a_try_catch,
                                       const FunctionsVector& a_functions, LoadedFunctionsMap& o_functions);

            static bool CallFunction  (::v8::Local<::v8::Context>& a_context, ::v8::Context::Scope& a_scope, ::v8::TryCatch& a_try_catch,
                                       const LoadedFunctionsMap& a_functions,
                                       const LoadedFunction::Callable& a_callable,
                                       ::v8::Persistent<::v8::Value>& o_result);
            
            void TraceException (::v8::TryCatch* a_try_catch, const TraceCallback a_on_error);
            bool TraceException (::v8::TryCatch* a_try_catch, std::string& o_trace);
            void LogException   (::v8::TryCatch* a_try_catch);            
            
        private: // Static Method(s) / Function(s)

            static void DebugLog (const ::v8::FunctionCallbackInfo<::v8::Value>& a_args);
            
        public: // Static Method(s) / Function(s)
            
            static bool LoadJSONAPIConversionFunction ();
            
            // Extracts a C string from a V8 Utf8Value.
            static const char* ToCString (const ::v8::String::Utf8Value& a_value)
            {
                return *a_value ? *a_value : "<string conversion failed>";
            }
            
        }; // end of class 'ClientContext'
        
    } // end of namespace 'v8'
    
} // end of namespace 'casper'

#endif // NRS_CASPER_V8_CONTEXT_H_
