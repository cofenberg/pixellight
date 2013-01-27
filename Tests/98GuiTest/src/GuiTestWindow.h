/*********************************************************\
 *  File: GuiTestWindow.h                                *
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
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Slots
		pl_slot_2(OnTrayIcon,			PLCore::uint32,	const PLMath::Vector2i&,	"Tray icon callback",	"")
		pl_slot_0(OnNotify,															"Button callback",		"")
		pl_slot_0(OnWindow,															"Button callback",		"")
		pl_slot_0(OnSimpleTest,														"Button callback",		"")
		pl_slot_0(OnWindowTest,														"Button callback",		"")
		pl_slot_0(OnMouseOverTest,													"Button callback",		"")
		pl_slot_0(OnFocusTest,														"Button callback",		"")
		pl_slot_0(OnWidgetTest,														"Button callback",		"")
		pl_slot_0(OnDragDropTest,													"Button callback",		"")
		pl_slot_0(OnTabsAndMenuTest,												"Button callback",		"")
		pl_slot_0(OnSlimTest,														"Button callback",		"")
		pl_slot_0(OnThemeTest,														"Button callback",		"")
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
		GuiTestWindow(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~GuiTestWindow();


	//[-------------------------------------------------------]
	//[ Protected virtual PLGui::WidgetFunctions functions    ]
	//[-------------------------------------------------------]
	protected:
		virtual void OnShow() override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		void OnTrayIcon(PLCore::uint32, const PLMath::Vector2i&);
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
