/*********************************************************\
 *  File: TestWindow.h                                   *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Slots
		pl_slot_0(OnToggleFullscreen,						"Button callback",	"")
		pl_slot_0(OnToggleTitleBar,							"Button callback",	"")
		pl_slot_0(OnToggleBorder,							"Button callback",	"")
		pl_slot_1(OnToggleTopmost,		PLGui::ECheckState,	"Button callback",	"")
		pl_slot_1(OnToggleTaskbar,		PLGui::ECheckState,	"Button callback",	"")
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
