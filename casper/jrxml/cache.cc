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

#include "casper/jrxml/cache.h"

#include "osal/osalite.h"

#if defined(OSALITE_DEBUG)
    #include "osal/utils/swatch.h"
#endif

/**
 * @brief This method should only be called once to initialize this cache.
 */
void casper::jrxml::Cache::Startup()
{
    linger_on_ = true;
}

/**
 * @brief Load a JRXML.
 *
 * @param a_entry The entry that will contain the loaded JRXML and it's cache info.
 * @param a_uri   The JRXML file uri.
 *
 * @throw On failure, an \link osal::Exception \link witch describes the failure reason.
 */
void casper::jrxml::Cache::Load (casper::Cache<casper::jrxml::JasperReport>::Entry* a_entry, const std::string& a_uri)
{
    pugi::xml_document           doc;
    const pugi::xml_parse_result result = doc.load_file(a_uri.c_str());
    
    // ... load failure?
    if ( pugi::status_ok != result.status ) {
        throw OSAL_EXCEPTION("Error while loading '%s' : %s",
                             a_uri.c_str(), result.description());
    }
    
    // ... already exists or create a new one?
    if ( nullptr != a_entry->item_ ) {
        // ... alread exists, just clean up ...
        a_entry->item_->Clear();
    } else {
        // ... new instance ...
        a_entry->item_ = new casper::jrxml::JasperReport(nullptr);
    }

#if defined(OSALITE_DEBUG)
    osal::utils::Swatch swatch;
    swatch.Start();
#endif // OSALITE_DEBUG

    // ... load JRXML ...
    a_entry->item_->ParseXml(doc.child("jasperReport"));

#if defined(OSALITE_DEBUG)
    swatch.Stop();
    OSALITE_DEBUG_TRACE("cache_load", "[%-8s] : [%dms] %s",
                        "LOAD", ( swatch.Ticks() / 1000 ), a_uri.c_str());
    OSALITE_DEBUG_IF("jrxml_debug") {
        a_entry->item_->PrintTreeInfo(stdout);
    }
#endif // OSALITE_DEBUG
    
    // ... set linger property ...
    a_entry->item_->SetLinger(linger_on_);
}
