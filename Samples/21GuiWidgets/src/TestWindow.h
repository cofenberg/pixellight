/*********************************************************\
 *  File: TestWindow.h                                   *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
