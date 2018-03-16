/**
 * @file image.h declaration of Image model node
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
#ifndef NRS_CASPER_CASPER_JRXML_IMAGE_H
#define NRS_CASPER_CASPER_JRXML_IMAGE_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/bool_attr.h"
#include "casper/jrxml/scale_image_attr.h"
#include "casper/jrxml/h_align_attr.h"
#include "casper/jrxml/v_align_attr.h"

namespace casper
{
    namespace jrxml
    {
        class Box;
        class ReportElement;
        class GraphicElement;
        class ImageExpression;

        /**
         * @brief JRXML model node for @TODO description
         */
        class Image  : public Node
        {
        protected: // Attributes

            ScaleImageAttr scale_image_;     //!< Image displaying type
            HAlignAttr     h_align_;         //!< Horizontal image alignment
            VAlignAttr     v_align_;         //!< Vertical image alignment
            BoolAttr       is_using_cache_;  //!< If true, tells the report engine to cache the images that are loaded from the same location

        protected: // Elements

            ReportElement*    report_element_;   //!< Mandatory
            Box*              box_;              //!< Optional
            GraphicElement*   graphic_element_;  //!< Optional
            ImageExpression*  image_expression_; //!< Optional

        public: // Methods

            Image (Node* a_parent);
            virtual ~Image ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;


            static Image* CreateFromXml (pugi::xml_node a_node, Node* a_parent);

        public: // Attribute accessors

            const BoolAttr&       IsUsingCache () const { return is_using_cache_; }
            const HAlignAttr&     Halign       () const { return h_align_;        }
            const VAlignAttr&     Valign       () const { return v_align_;        }
            const ScaleImageAttr& ScaleImage   () const { return scale_image_;    }

        public: // Element accessors

            class Box&             GetBox             () const { return *box_;              }
            class ReportElement&   GetReportElement   () const { return *report_element_;   }
            class GraphicElement&  GetGraphicElement  () const { return *graphic_element_;  }
            class ImageExpression& GetImageExpression () const { return *image_expression_; }

            bool HasBox             () const { return box_              != NULL; }
            bool HasReportElement   () const { return report_element_   != NULL; }
            bool HasGraphicElement  () const { return graphic_element_  != NULL; }
            bool HasImageExpression () const { return image_expression_ != NULL; }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_IMAGE_H
