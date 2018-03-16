/**
 * @file cache.h - In-memory JRXML cache.
 *
 * Copyright (c) 2010-2016 Neto Ranito & Seabra LDA. All rights reserved.
 *
 * This file is part of casper.
 *
 * casper is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * casper  is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with casper.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once
#ifndef NRS_CASPER_JRXML_CACHE_H_
#define NRS_CASPER_JRXML_CACHE_H_

#include "casper/cache.h"
#include "casper/jrxml/jasper_report.h"

#include "osal/osal_singleton.h"

namespace casper
{
    
    namespace jrxml
    {
        
        /**
         * @brief A singleton to manage JRXML in-memory cache.
         */
        class Cache final : public casper::Cache<JasperReport>, public osal::Singleton<Cache>
        {
            
        public: // Method(s) / Function(s)
            
            void Startup ();

        protected: // Inherited virtual method(s) / function(s)
            
            virtual void Load (casper::Cache<JasperReport>::Entry* a_entry, const std::string& a_uri);
            
        }; // end of class Cache
        
    } // end of namespace jrxml
    
} // end of namespace casper

#endif // NRS_CASPER_JRXML_CACHE_H_
