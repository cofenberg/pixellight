/*********************************************************\
 *  File: TabsAndMenuWindow.h                            *
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


#ifndef __PLSAMPLE99_TABSANDMENUWINDOW_H__
#define __PLSAMPLE99_TABSANDMENUWINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include <PLGui/Gui/Resources/Menu.h>
#include <PLGui/Widgets/Windows/Window.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGui {
	class MenuBar;
	class TabContainer;
};


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Test window with a menu and a tab container
*/
class TabsAndMenuWindow : public PLGui::Window {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, TabsAndMenuWindow, "", PLGui::Window, "Test window with a menu and a tab container")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
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
		TabsAndMenuWindow(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~TabsAndMenuWindow();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when a new tab shall be created
		*/
		void OnTabContainerCreateWindow();

		/**
		*  @brief
		*    Called when a menu item has been clicked
		*/
		void OnMenuItemClicked(PLGui::MenuItem *pItem);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Event handlers
		PLCore::EventHandler<>					EventHandlerCreateWindow;
		PLCore::EventHandler<PLGui::MenuItem*>	EventHandlerMenuItemClicked;

		// Widgets
		PLGui::MenuBar		*m_pMenuBar;		/**< Menu bar */
		PLGui::TabContainer *m_pTabContainer;	/**< Main tabs */
		int					 m_nNextWindow;		/**< New window ID */

		// Data
		PLGui::Menu			 m_cMenu;			/**< Main menu */


};


#endif // __PLSAMPLE99_TABSANDMENUWINDOW_H__
