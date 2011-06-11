/*********************************************************\
 *  File: LayoutBox.h                                    *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


#ifndef __PLGUI_LAYOUT_LAYOUTBOX_H__
#define __PLGUI_LAYOUT_LAYOUTBOX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2i.h>
#include "PLGui/Layout/Layout.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Box layout
*/
class LayoutBox : public Layout {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, LayoutBox, "PLGui", PLGui::Layout, "Box layout")
		// Attributes
		pl_attribute(Orientation,	pl_enum_type(EOrientation),	Horizontal,	ReadWrite,	GetSet,	"Box orientation",	"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLGUI_API EOrientation GetOrientation() const;
		PLGUI_API void SetOrientation(EOrientation nOrientation);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nOrientation
		*    Orientation
		*/
		PLGUI_API LayoutBox(EOrientation nOrientation = Horizontal);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~LayoutBox();


	//[-------------------------------------------------------]
	//[ Protected virtual Layout functions                    ]
	//[-------------------------------------------------------]
	protected:
		virtual void ApplyLayout();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Exported variables
		EOrientation	  m_nOrientation;	/**< Box orientation (horizontal or vertical) */

		// Internal data
		PLMath::Vector2i *m_pSizes;			/**< Data space used for calculations */
		PLGeneral::uint32 m_nWidgets;		/**< Number of widgets that are in the layout */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_LAYOUT_LAYOUTBOX_H__
