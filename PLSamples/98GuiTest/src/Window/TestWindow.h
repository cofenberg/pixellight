/*********************************************************\
 *  File: TestWindow.h                                   *
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


#ifndef __PLSAMPLE99_TESTWINDOW_H__
#define __PLSAMPLE99_TESTWINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Widgets/Windows/Window.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGui {
	class Button;
	class ToggleButton;
};


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Test window that show some functionality of class Window
*/
class TestWindow : public PLGui::Window {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, TestWindow, "", PLGui::Window, "Test window that show some functionality of class Window")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_slot_0(OnToggleFullscreen,						"Button callback", "")
		pl_slot_0(OnToggleTitleBar,							"Button callback", "")
		pl_slot_0(OnToggleBorder,							"Button callback", "")
		pl_slot_1(OnToggleTopmost,		PLGui::ECheckState, "Button callback", "")
		pl_slot_1(OnToggleTaskbar,		PLGui::ECheckState, "Button callback", "")
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
		TestWindow(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~TestWindow();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Toggle fullscreen mode
		*/
		void OnToggleFullscreen();

		/**
		*  @brief
		*    Toggle title bar visibility
		*/
		void OnToggleTitleBar();

		/**
		*  @brief
		*    Toggle border visibility
		*/
		void OnToggleBorder();

		/**
		*  @brief
		*    Toggle topmost state
		*/
		void OnToggleTopmost(PLGui::ECheckState nState);

		/**
		*  @brief
		*    Toggle taskbar visibility
		*/
		void OnToggleTaskbar(PLGui::ECheckState nState);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Buttons
		PLGui::Button		*m_pButtonFullscreen;
		PLGui::Button		*m_pButtonTitleBar;
		PLGui::Button		*m_pButtonBorder;
		PLGui::ToggleButton *m_pButtonTopmost;
		PLGui::ToggleButton *m_pButtonTaskbar;


};


#endif // __PLSAMPLE99_TESTWINDOW_H__
