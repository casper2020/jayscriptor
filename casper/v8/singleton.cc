/**
 * @file singleton.cc
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

#include "casper/v8/singleton.h"

/**
 * @brief Default constructor.
 */
casper::v8::Singleton::Singleton()
{
    platform_    = nullptr;
    initialized_ = false;
}

/**
 * @brief Destructor.
 */
casper::v8::Singleton::~Singleton ()
{
    ::v8::V8::Dispose();
    ::v8::V8::ShutdownPlatform();
    if ( nullptr != platform_ ) {
        delete platform_;
    }
}

/**
 * @brief This method must ( and can only ) be called once to initialize V8 engine.
 *
 * @param a_exec_uri
 * @param a_natives_blog_uri
 * @param a_snapshot_blob_uri
 * @param a_icu_data_uri
 */
void casper::v8::Singleton::Startup (const char* const a_exec_uri, const char* const a_natives_blob_uri, const char* const a_snapshot_blob_uri, const char* const a_icu_data_uri)
{
    if ( true == initialized_ ) {
        throw std::runtime_error("v8 singleton already initialized!");
    }
    if ( false == ::v8::V8::InitializeICUDefaultLocation(a_exec_uri, a_icu_data_uri) ) {
        throw std::runtime_error("v8 ICU initialization failure!");
    }
    ::v8::V8::InitializeExternalStartupData(a_natives_blob_uri, a_snapshot_blob_uri);
    platform_ = ::v8::platform::CreateDefaultPlatform();
    if ( nullptr == platform_ ) {
        throw std::runtime_error("v8 default platform creation failure!");
    }
    ::v8::V8::InitializePlatform(platform_);
    if ( false == ::v8::V8::Initialize() ) {
        throw std::runtime_error("v8 ICU default platform initialization failure!");
    }
    initialized_ = true;
}
