/*********************************************************\
 *  File: TabBar.h                                       *
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


#ifndef __PLGUI_TABBAR_H__
#define __PLGUI_TABBAR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/Event.h>
#include <PLGeneral/Container/List.h>
#include "PLGui/Widgets/Widget.h"
#include "PLGui/Widgets/Controls/TabBarEntry.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Tab bar widget
*/
class TabBar : public Widget {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, TabBar, "PLGui", PLGui::Widget, "Tab bar widget")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class TabBarEntry;
	friend class TabBarButton;


	//[-------------------------------------------------------]
	//[ Public events                                         ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<TabBarEntry*>	EventAddTab;		/**< New tab is added */
		PLCore::Event<TabBarEntry*>	EventRemoveTab;		/**< Tab is removed */
		PLCore::Event<TabBarEntry*>	EventCloseTab;		/**< Tab is to be closed */
		PLCore::Event<int>			EventSelectTab;		/**< Current selection has been changed */
		PLCore::Event<>				EventCreateTab;		/**< New tab shall be created */


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
		PLGUI_API TabBar(Widget *pParent = NULL);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~TabBar();

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

		/**
		*  @brief
		*    Create a new tab
		*
		*  @remarks
		*    CreateTab creates an event saying that a new tab shall be created.
		*    This does not do anything automatically, so you have to catch the
		*    event and call AddTab() to actually create a new tab.
		*/
		PLGUI_API void CreateTab();

		/**
		*  @brief
		*    Close tab
		*
		*  @param[in] pTab
		*    Tab
		*
		*  @remarks
		*    See CloseTab(PLGeneral::uint32 nTab)
		*/
		PLGUI_API void CloseTab(TabBarEntry *pTab);

		/**
		*  @brief
		*    Close tab
		*
		*  @param[in] nTab
		*    Tab index
		*
		*  @remarks
		*    CloseTab creates an event saying that the given tab shall
		*    be closed (the same as when the used has actually clicked
		*    on the tab's 'x'-button). This does not automatically remove
		*    the tab but only generate the event. Do actually remove a tab,
		*    use RemoveTab().
		*/
		PLGUI_API void CloseTab(PLGeneral::uint32 nTab);

		/**
		*  @brief
		*    Get list of tabs
		*
		*  @return
		*    List of tabs
		*/
		PLGUI_API const PLGeneral::Container<TabBarEntry*> &GetTabs() const;

		/**
		*  @brief
		*    Add tab
		*
		*  @param[in] sText
		*    Tab text
		*
		*  @return
		*    New tab entry
		*/
		PLGUI_API TabBarEntry *AddTab(const PLGeneral::String &sText);

		/**
		*  @brief
		*    Add tab
		*
		*  @param[in] sText
		*    Tab text
		*  @param[in] cIcon
		*    Image
		*
		*  @return
		*    New tab entry
		*/
		PLGUI_API TabBarEntry *AddTab(const PLGeneral::String &sText, const Image &cIcon);

		/**
		*  @brief
		*    Remove tab
		*
		*  @param[in] pTab
		*    Tab
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLGUI_API bool RemoveTab(TabBarEntry *pTab);

		/**
		*  @brief
		*    Remove tab
		*
		*  @param[in] nTab
		*    Tab index
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLGUI_API bool RemoveTab(PLGeneral::uint32 nTab);

		/**
		*  @brief
		*    Get currently selected tab
		*
		*  @return
		*    Index of currently selected tab
		*/
		PLGUI_API int GetSelection() const;

		/**
		*  @brief
		*    Set currently selected tab
		*
		*  @param[in] nTab
		*    Index of currently selected tab
		*/
		PLGUI_API void SetSelection(int nTab);

		/**
		*  @brief
		*    Get scrolling position
		*
		*  @return
		*    Index of first visible tab
		*/
		PLGUI_API int GetScrollingPos() const;

		/**
		*  @brief
		*    Set scrolling position
		*
		*  @param[in] nTab
		*    Index of first visible tab
		*/
		PLGUI_API void SetScrollingPos(int nTab);

		/**
		*  @brief
		*    Get tab that is currently selected by the mouse
		*
		*  @return
		*    Index of currently selected tab
		*/
		PLGUI_API int GetMouseSelection() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Redraw tab
		*
		*  @param[in] nTab
		*    Index of tab
		*/
		PLGUI_API void RedrawTab(int nTab);

		/**
		*  @brief
		*    Set tab that is currently selected by the mouse
		*
		*  @param[in] nTab
		*    Index of currently selected tab
		*/
		PLGUI_API void SetMouseSelection(int nTab);


	//[-------------------------------------------------------]
	//[ Protected virtual Widget functions                    ]
	//[-------------------------------------------------------]
	protected:
		PLGUI_API virtual PLMath::Vector2i OnPreferredSize(const PLMath::Vector2i &vRefSize) const;
		PLGUI_API virtual void OnAdjustContent();


	//[-------------------------------------------------------]
	//[ Protected virtual TabBar functions                    ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called when a new tab is added
		*
		*  @param[in] pTab
		*    Tab
		*/
		PLGUI_API virtual void OnAddTab(TabBarEntry *pTab);

		/**
		*  @brief
		*    Called when a tab is removed
		*
		*  @param[in] pTab
		*    Tab
		*/
		PLGUI_API virtual void OnRemoveTab(TabBarEntry *pTab);

		/**
		*  @brief
		*    Called when a tab shall be closed
		*
		*  @param[in] pTab
		*    Tab
		*/
		PLGUI_API virtual void OnCloseTab(TabBarEntry *pTab);

		/**
		*  @brief
		*    Called when the current selection has been changed
		*
		*  @param[in] nTab
		*    Index of currently selected tab
		*/
		PLGUI_API virtual void OnSelectTab(int nTab);

		/**
		*  @brief
		*    Called when a new tab shall be created
		*/
		PLGUI_API virtual void OnCreateTab();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	public:
		// TabBar data
		ESide							m_nSide;			/**< Side the tabbar is positioned on */
		PLGeneral::uint32				m_nOptions;			/**< TabBar options (ETabBarOption) */
		PLGeneral::uint32				m_nTabWidth;		/**< Tab width */
		PLGeneral::uint32				m_nTabHeight;		/**< Tab height */
		PLGeneral::List<TabBarEntry*>	m_lstTabs;			/**< List of tabs */
		int								m_nSelection;		/**< Index of currently selected tab */
		int								m_nMouseSelection;	/**< Index of tab currently selected by the mouse */
		int								m_nScrollingPos;	/**< First displayed tab (scrolling) */

		// Child widgets
		TabBarButton				   *m_pButtonCreate;	/**< Button to create a new tab */
		TabBarButton				   *m_pButtonNext;		/**< Button to scroll (next) */
		TabBarButton				   *m_pButtonPrev;		/**< Button to scroll (previous) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_TABBAR_H__
