/*********************************************************\
 *  File: TestWindow.h                                   *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLSAMPLE_21_TESTWINDOW_H__
#define __PLSAMPLE_21_TESTWINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Gui/Data/ButtonGroup.h>
#include <PLGui/Gui/Resources/Menu.h>
#include <PLGui/Gui/TrayIcon.h>
#include <PLGui/Widgets/Windows/Window.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGui {
	class Label;
	class Button;
	class ToggleButton;
	class CheckBox;
	class RadioButton;
	class Window;
	class BitmapButton;
	class BitmapToggleButton;
	class MenuBar;
//	class TabBar;
	class PopupMenu;
};


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Test window
*/
class TestWindow : public PLGui::Window {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pParent
		*    Parent widget, can be a null pointer
		*/
		TestWindow(PLGui::Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~TestWindow();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		void ButtonClicked();
		void ButtonPressed();
		void ButtonReleased();
		void MenuClicked(PLCore::uint32 nID);
		void TrayClicked(PLCore::uint32 nButton, const PLMath::Vector2i &vPos);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Event handlers
		PLCore::EventHandler<PLCore::uint32, const PLMath::Vector2i&>	EventHandlerTrayClicked;
		PLCore::EventHandler<>											EventHandlerClicked;
		PLCore::EventHandler<>											EventHandlerPressed;
		PLCore::EventHandler<>											EventHandlerReleased;
		PLCore::EventHandler<PLCore::uint32>							EventHandlerMenu;

		// Widgets
		PLGui::Label				*m_pLabel;
		PLGui::Button				*m_pButton;
		PLGui::ToggleButton			*m_pToggleButton;
		PLGui::ButtonGroup			 m_cCheckGroup;
		PLGui::ButtonGroup			 m_cRadioGroup;
		PLGui::CheckBox				*m_pCheckBoxes[4];
		PLGui::RadioButton			*m_pRadioButtons[4];
		PLGui::Widget				*m_pClickTest;
		PLGui::Widget				*m_pPressedTest;
		PLGui::BitmapButton			*m_pBitmapButton;
		PLGui::BitmapToggleButton	*m_pBitmapToggleButton;
		PLGui::Menu					 m_cMenu;
		PLGui::MenuBar				*m_pMenuBar;
//		PLGui::TabBar				*m_pTabBar;
		PLGui::PopupMenu			*m_pPopupMenu;

		// Tray icon
		PLGui::TrayIcon				 m_cTrayIcon;

		// State
		bool						 m_bClicked;


};


#endif // __PLSAMPLE_21_TESTWINDOW_H__
