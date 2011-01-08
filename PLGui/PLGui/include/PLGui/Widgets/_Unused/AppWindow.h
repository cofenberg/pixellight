/*********************************************************\
 *  File: AppWindow.h                                    *
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


#ifndef __PLGUI_APPWINDOW_H__
#define __PLGUI_APPWINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Widgets/Windows/Window.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    An application window is usually a top-level window with a border and a title bar
*/
class AppWindow : public Window {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, AppWindow, "PLGui", PLGui::Window, "An application window is usually a top-level window with a border and a title bar")
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
		*    Pointer to parent widget
		*/
		PLGUI_API AppWindow(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~AppWindow();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_APPWINDOW_H__
