/**
 * @file style.h declaration of style model node
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
#ifndef NRS_CASPER_CASPER_JRXML_STYLE_H
#define NRS_CASPER_CASPER_JRXML_STYLE_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/dim_attr.h"
#include "casper/jrxml/string_attr.h"
#include "casper/jrxml/bool_attr.h"
#include "casper/jrxml/color_attr.h"
#include "casper/jrxml/text_alignment_attr.h"
#include "casper/jrxml/vertical_alignment_attr.h"
#include "casper/jrxml/rotation_attr.h"
#include "casper/jrxml/line_spacing_attr.h"
#include "casper/jrxml/scale_image_attr.h"
#include "casper/jrxml/mode_attr.h"
#include "pugixml.hpp"

namespace casper
{
    namespace jrxml
    {
        class Paragraph;
        class Box;
        class Pen;

        /**
         * @brief JRXML model node for @TODO description
         */
        class Style  : public Node
        {
        protected: // data

            Style*                parent_style_;       //!< The sytle from which defaults are inherited

        protected: // Attributes

            ModeAttr              mode_;               //!< Specifies whether the background of an object is transparent or opaque
            ColorAttr             forecolor_;          //!< Fore color to use when drawing the object
            ColorAttr             backcolor_;          //!< Back color to use when drawing the object
            StringAttr            name_;               //!< Name of the report style definition
            BoolAttr              is_default_;         /** The default report style is used as base style for all the elements
                                                           that do not explicitly reference a report style definition */
            StringAttr            style_;              //!< Parent style reference.
            StringAttr            fill_;               //!< only value is Solid
            TextAlignmentAttr     h_align_;            //!< Horizontal text alignment
            VerticalAlignmentAttr v_align_;            //!< Vertical text alignment
            ScaleImageAttr        scale_image_;        //!< How to scale the image
            RotationAttr          rotation_;           //!< Text orientation inside the box
            LineSpacingAttr       line_spacing_;       //!< Spacing between paragraph lines
            StringAttr            font_name_;          //!< Name of the font
            DimAttr               font_size_;          //!< Font size in points
            BoolAttr              is_bold_;            //!< "true" | "false" to apply bold
            BoolAttr              is_italic_;          //!< "true" | "false" to apply italic
            BoolAttr              is_underline_;       //!< "true" | "false" to underline
            BoolAttr              is_strike_trought_;  //!< "true" | "false" to strike out the darn text
            StringAttr            pattern_;            //!< Pattern to format expression
            BoolAttr              is_blank_when_null_; //!< if "true" null are not printed

        protected: // Child Elements

            Box*       box_;
            Paragraph* paragraph_;
            Pen*       pen_;

        public: // Methods

            Style (Node* a_parent);
            virtual ~Style ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;

            static Style* CreateFromXml (pugi::xml_node a_node, Node* a_parent);

            void SetParentStyle (Style* a_parent_style) { parent_style_ = a_parent_style;  }

        public: // Attribute accessors

            const ModeAttr&              Mode             () const { return mode_;               }
            const ColorAttr&             Forecolor        () const { return forecolor_;          }
            const ColorAttr&             Backcolor        () const { return backcolor_;          }
            const StringAttr&            Name             () const { return name_;               }
            const BoolAttr&              IsDefault        () const { return is_default_;         }
            const StringAttr&            ParentStyle      () const { return style_;              }
            const StringAttr&            Fill             () const { return fill_;               }
            const TextAlignmentAttr&     Halign           () const { return h_align_;            }
            const VerticalAlignmentAttr& Valign           () const { return v_align_;            }
            const ScaleImageAttr&        ScaleImage       () const { return scale_image_;        }
            const RotationAttr&          Rotation         () const { return rotation_;           }
            const LineSpacingAttr&       LineSpacing      () const { return line_spacing_;       }
            const StringAttr&            FontName         () const { return font_name_;          }
            const DimAttr&               FontSize         () const { return font_size_;          }
            const BoolAttr&              IsBold           () const { return is_bold_;            }
            const BoolAttr&              IsItalic         () const { return is_italic_;          }
            const BoolAttr&              IsUnderline      () const { return is_underline_;       }
            const BoolAttr&              IsStrikeTrought  () const { return is_strike_trought_;  }
            const StringAttr&            Pattern          () const { return pattern_;            }
            const BoolAttr&              IsBlankWhenNull  () const { return is_blank_when_null_; }

        public: // Element accessors

            class Box&       GetBox         () const { return *box_;          }
            class Paragraph& GetParagraph   () const { return *paragraph_;    }
            class Pen&       GetPen         () const { return *pen_;          }
            const Style&     GetParentStyle () const { return *parent_style_; }

            bool HasBox         () const { return box_       != NULL; }
            bool HasParagraph   () const { return paragraph_ != NULL; }
            bool HasPen         () const { return pen_       != NULL; }
            bool HasParentStyle () const                { return parent_style_ != nullptr; }
            
        };


    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_STYLE_H
