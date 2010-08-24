/*********************************************************\
 *  File: GuiTestWindow.h                                *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLSAMPLE99_GUITESTWINDOW_H__
#define __PLSAMPLE99_GUITESTWINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Gui/TrayIcon.h>
#include <PLGui/Widgets/Windows/Window.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    GuiTest main window
*/
class GuiTestWindow : public PLGui::Window {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, GuiTestWindow, "", PLGui::Window, "GuiTest main window")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_slot_2(OnTrayIcon, PLGeneral::uint32, const PLMath::Vector2i&, "Tray icon callback",	"")
		pl_slot_0(OnNotify,				"Button callback", "")
		pl_slot_0(OnWindow,				"Button callback", "")
		pl_slot_0(OnSimpleTest,			"Button callback", "")
		pl_slot_0(OnWindowTest,			"Button callback", "")
		pl_slot_0(OnMouseOverTest,		"Button callback", "")
		pl_slot_0(OnFocusTest,			"Button callback", "")
		pl_slot_0(OnWidgetTest,			"Button callback", "")
		pl_slot_0(OnDragDropTest,		"Button callback", "")
		pl_slot_0(OnTabsAndMenuTest,	"Button callback", "")
		pl_slot_0(OnSlimTest,			"Button callback", "")
		pl_slot_0(OnThemeTest,			"Button callback", "")
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
		GuiTestWindow(Widget *pParent = NULL);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~GuiTestWindow();


	//[-------------------------------------------------------]
	//[ Protected virtual WidgetFunctions functions           ]
	//[-------------------------------------------------------]
	protected:
		virtual void OnShow();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		void OnTrayIcon(PLGeneral::uint32, const PLMath::Vector2i&);
		void OnNotify();
		void OnWindow();
		void OnSimpleTest();
		void OnWindowTest();
		void OnMouseOverTest();
		void OnFocusTest();
		void OnWidgetTest();
		void OnDragDropTest();
		void OnTabsAndMenuTest();
		void OnSlimTest();
		void OnThemeTest();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGui::TrayIcon m_cTrayIcon;	/**< Tray icon */


};


#endif // __PLSAMPLE99_GUITESTWINDOW_H__
