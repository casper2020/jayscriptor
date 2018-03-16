/**
 * @file scale_image_attr.h declaration of ScaleImageAttr simple enum
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
 */
#pragma once
#ifndef NRS_CASPER_CASPER_JRXML_scale_image_attr_H
#define NRS_CASPER_CASPER_JRXML_scale_image_attr_H

#include "casper/jrxml/enum_attr.h"

namespace casper
{
    namespace jrxml
    {
        /**
         * @brief Image displaying type
         */
        class ScaleImageAttr  : public EnumAttr
        {
        public: // enum values
            
            enum
            {
                EClip,        //!< Only the portion of the image that fits the specified object width and height will be printed. Image is not stretched.
                EFillFrame,   //!< Image will be stretched to adapt to the specified object width and height.
                ERetainShape, //!< Image will adapt to the specified object width or height keeping its original shape.
                ERealHeight,  //!< A scale image type that instructs the engine to stretch the image height to fit the actual height of the image.
                ERealSize     //!< A scale image type that stretches the images height in the same way as RealHeight and in addition it changes the image width to the actual with of the image.
            };

        public: // Methods

            void        FromStr     (const pugi::char_t* a_value);
            const char* ToStr       () const;
            operator    const char* () const { return ToStr(); }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_scale_image_attr_H
