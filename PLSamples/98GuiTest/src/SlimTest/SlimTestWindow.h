/*********************************************************\
 *  File: SlimTestWindow.h                               *
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


#ifndef __PLSAMPLE99_SLIMTESTWINDOW_H__
#define __PLSAMPLE99_SLIMTESTWINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Widgets/Windows/Window.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGui {
	class ScrollWidget;
	class Box;
	class Button;
};


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Test window that show the new slim widgets
*/
class SlimTestWindow : public PLGui::Window {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SlimTestWindow, "", PLGui::Window, "Test window that show the new slim widgets")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_slot_0		(OnLeft,			 "Button callback", "")
		pl_slot_0		(OnRight,			 "Button callback", "")
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
		SlimTestWindow(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SlimTestWindow();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Left button pressed
		*/
		void OnLeft();

		/**
		*  @brief
		*    Right button pressed
		*/
		void OnRight();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Containers
		PLGui::ScrollWidget	*m_pContainerLeft;
		PLGui::ScrollWidget	*m_pContainerRight;

		// Buttons
		PLGui::Box			*m_pButtonBox;
		PLGui::Button		*m_pButtonLeft;
		PLGui::Button		*m_pButtonRight;


};


#endif // __PLSAMPLE99_SLIMTESTWINDOW_H__
