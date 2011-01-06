/*********************************************************\
 *  File: ToggleButton.h                                 *
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


#ifndef __PLGUI_TOGGLEBUTTON_H__
#define __PLGUI_TOGGLEBUTTON_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Widgets/Base/AbstractToggleButton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A standard button that can be toggled (binary state)
*/
class ToggleButton : public AbstractToggleButton {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, ToggleButton, "PLGui", PLGui::AbstractToggleButton, "A standard button that can be toggled (binary state)")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pParent
		*    Pointer to the parent widget
		*/
		PLGUI_API ToggleButton(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~ToggleButton();


	//[-------------------------------------------------------]
	//[ Private virtual Widget functions                      ]
	//[-------------------------------------------------------]
	private:
		PLGUI_API virtual void OnDraw(Graphics &cGraphics);
		PLGUI_API virtual PLMath::Vector2i OnPreferredSize(const PLMath::Vector2i &vRefSize) const;
		PLGUI_API virtual void OnMouseEnter();
		PLGUI_API virtual void OnMouseLeave();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_TOGGLEBUTTON_H__
