/**
 * @file box.h declaration of Box model node
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
#ifndef NRS_CASPER_CASPER_JRXML_box_H
#define NRS_CASPER_CASPER_JRXML_box_H

#include "casper/jrxml/node.h"
#include "casper/jrxml/dim_attr.h"

namespace casper
{
    namespace jrxml
    {
        class Pen;

        /**
         * @brief Tag used to specify the border and padding properties of a report element
         */
        class Box  : public Node
        {
        protected: // Attributes

            DimAttr padding_;        //!< The amount of empty space between the border and the element's content, normalized to pixels @TODO<check coexistence with other box's paddings>
            DimAttr top_padding_;    //!< The amount of empty space between the top border and the element's content, normalized to pixels
            DimAttr left_padding_;   //!< The amount of empty space between the left border and the element's content, normalized to pixels
            DimAttr bottom_padding_; //!< The amount of empty space between the bottom border and the element's content, normalized to pixels
            DimAttr right_padding_;  //!< The amount of empty space between the right border and the element's content, normalized to pixels

        protected: // Child Elements

            Pen* pen_;        //!< Pen to be used for the whole box, optional @TODO<check coexistence with other box's pens>
            Pen* top_pen_;    //!< Pen for the box top edge, optional
            Pen* left_pen_;   //!< Pen for the box left edge, optional
            Pen* bottom_pen_; //!< Pen for the box bottom edge, optional
            Pen* right_pen_;  //!< Pen for the box right edge, optional

        public: // Methods

            Box (Node* a_parent);
            virtual ~Box ();

            virtual bool ParseXml      (pugi::xml_node a_xml_node);
            virtual void PrintNodeInfo (FILE* a_stream, int a_depth) const;

            static Box* CreateFromXml (pugi::xml_node a_node, Node* a_parent) ;

        public: // Attribute accessors

            const DimAttr& Padding       () const { return padding_;        }
            const DimAttr& TopPadding    () const { return top_padding_;    }
            const DimAttr& LeftPadding   () const { return left_padding_;   }
            const DimAttr& BottomPadding () const { return bottom_padding_; }
            const DimAttr& RightPadding  () const { return right_padding_;  }

        public: // Element accesors

            class Pen&  GetPen       () const { return *pen_;        }
            class Pen&  GetTopPen    () const { return *top_pen_;    }
            class Pen&  GetLeftPen   () const { return *left_pen_;   }
            class Pen&  GetBottomPen () const { return *bottom_pen_; }
            class Pen&  GetRightPen  () const { return *right_pen_;  }

            bool HasPen       () const { return pen_        != NULL; }
            bool HasTopPen    () const { return top_pen_    != NULL; }
            bool HasLeftPen   () const { return left_pen_   != NULL; }
            bool HasBottomPen () const { return bottom_pen_ != NULL; }
            bool HasRightPen  () const { return right_pen_  != NULL; }

        };

    } // namespace jrxml
} // namespace casper

#endif // NRS_CASPER_CASPER_JRXML_box_H
