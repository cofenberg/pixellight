/*********************************************************\
 *  File: TabContainer.h                                 *
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


#ifndef __PLGUI_TABCONTAINER_H__
#define __PLGUI_TABCONTAINER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Widgets/Containers/WindowContainer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class TabBar;
class TabBarEntry;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Tab container
*/
class TabContainer : public WindowContainer {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, TabContainer, "PLGui", PLGui::WindowContainer, "Tab container")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public events                                         ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<> EventCreateWindow;		/**< New window shall be created */


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
		PLGUI_API TabContainer(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~TabContainer();

		/**
		*  @brief
		*    Get side the tabbar is positioned on
		*
		*  @return
		*    Side
		*/
		PLGUI_API ESide GetSide() const;

		/**
		*  @brief
		*    Set side the tabbar is positioned on
		*
		*  @param[in] nSide
		*    Side
		*/
		PLGUI_API void SetSide(ESide nSide);

		/**
		*  @brief
		*    Get TabBar options
		*
		*  @return
		*    TabBar options (combination of ETabBarOption values)
		*/
		PLGUI_API PLGeneral::uint32 GetOptions() const;

		/**
		*  @brief
		*    Set TabBar options
		*
		*  @param[in] nOptions
		*    TabBar options
		*/
		PLGUI_API void SetOptions(PLGeneral::uint32 nOptions);

		/**
		*  @brief
		*    Get tab width
		*
		*  @return
		*    Tab width
		*
		*  @remarks
		*    see SetTabWidth()
		*/
		PLGUI_API PLGeneral::uint32 GetTabWidth() const;

		/**
		*  @brief
		*    Set tab width
		*
		*  @param[in] nWidth
		*    Tab width
		*
		*  @notes
		*    - If side is SideTop or SideBottom and StaticTabSize is *not* set, tabs have a floating size.
		*      In that case, the width set by nWidth is the maximum size that a tab can have.
		*    - If side is SideLeft or SideRight, or StaticTabSize is set, tabs have a static size.
		*      In that case, every tab will get exactly the width set by nWidth.
		*/
		PLGUI_API void SetTabWidth(PLGeneral::uint32 nWidth);

		/**
		*  @brief
		*    Get tab height
		*
		*  @return
		*    Tab height
		*/
		PLGUI_API PLGeneral::uint32 GetTabHeight() const;

		/**
		*  @brief
		*    Set tab height
		*
		*  @param[in] nHeight
		*    Tab height
		*/
		PLGUI_API void SetTabHeight(PLGeneral::uint32 nHeight);


	//[-------------------------------------------------------]
	//[ Protected virtual TabContainer functions              ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called when a new window shall be created
		*/
		PLGUI_API void OnCreateWindow();


	//[-------------------------------------------------------]
	//[ Protected virtual WindowContainer functions           ]
	//[-------------------------------------------------------]
	protected:
		PLGUI_API virtual void OnAddWindow(Widget *pWindow);
		PLGUI_API virtual void OnRemoveWindow(Widget *pWindow);
		PLGUI_API virtual void OnSelectWindow(int nWindow);


	//[-------------------------------------------------------]
	//[ Protected virtual Widget functions                    ]
	//[-------------------------------------------------------]
	protected:
		PLGUI_API virtual void OnAdjustContent();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when a tab to be is closed
		*
		*  @param[in] pTab
		*    Tab
		*/
		void OnTabBarCloseTab(TabBarEntry *pTab);

		/**
		*  @brief
		*    Called when the current selection has been changed
		*
		*  @param[in] nTab
		*    Index of currently selected tab
		*/
		void OnTabBarSelectTab(int nTab);

		/**
		*  @brief
		*    Called when a new tab shall be created
		*/
		void OnTabBarCreateTab();

		/**
		*  @brief
		*    Find tab that belongs to a certain window
		*
		*  @param[in] pWindow
		*    Window
		*
		*  @return
		*    Tab entry belonging to the window (or a null pointer)
		*/
		TabBarEntry *FindTab(Widget *pWindow) const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	public:
		// Event handlers
		PLCore::EventHandler<TabBarEntry*>	EventHandlerCloseTab;
		PLCore::EventHandler<int>			EventHandlerSelectTab;
		PLCore::EventHandler<>				EventHandlerCreateTab;

		// Widgets
		TabBar *m_pTabBar;		/**< Tab-bar */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_TABCONTAINER_H__
