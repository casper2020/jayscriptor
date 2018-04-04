/**
 * @file singleton.h
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
#ifndef NRS_CASPER_V8_SINGLETON_H_
#define NRS_CASPER_V8_SINGLETON_H_

#include "libplatform/libplatform.h"
#include "v8.h"

namespace casper
{
    
    namespace v8
    {
        
        class Singleton final
        {
            
        public: // Static Data
            
            static Singleton& GetInstance()
            {
                static Singleton instance;
                return instance;
            }
            
        private: // Data
            
            bool initialized_;
            
        private: // Data
            
            ::v8::Platform* platform_;

        public: // Constructor(s) / Destructor
            
                     Singleton();
                     Singleton(Singleton const&) = delete; // copies are not allowed
            virtual ~Singleton ();
            
        public: // Overloaded Operator(s)
            
            void operator=(Singleton const&)  = delete;  // assignment is not allowed
            
        public: // Method(s) / Function(s) - Oneshot call only!!!
            
            void Startup (const char* const a_exec_uri, const char* const a_natives_blob_uri, const char* const a_snapshot_blob_uri, const char* const a_icu_data_uri);
            
        }; // end of class 'Singleton'
        
    } // end of namespace 'v8'
    
} // end of namespace 'casper'

#endif // NRS_CASPER_V8_SINGLETON_H_
