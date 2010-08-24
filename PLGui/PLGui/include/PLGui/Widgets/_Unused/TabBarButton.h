/*********************************************************\
 *  File: TabBarButton.h                                 *
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


#ifndef __PLGUI_TABBARBUTTON_H__
#define __PLGUI_TABBARBUTTON_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Widgets/Base/AbstractButton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Tab bar button
*/
class TabBarButton : public AbstractButton {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, TabBarButton, "PLGui", PLGui::AbstractButton, "Tab bar button")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class TabBar;
	friend class TabBarEntry;


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
		PLGUI_API TabBarButton(Widget *pParent = NULL);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~TabBarButton();

		/**
		*  @brief
		*    Get TabBar
		*
		*  @return
		*    TabBar
		*/
		PLGUI_API TabBar *GetTabBar() const;

		/**
		*  @brief
		*    Get TabBarEntry
		*
		*  @return
		*    TabBarEntry
		*/
		PLGUI_API TabBarEntry *GetTabBarEntry() const;

		/**
		*  @brief
		*    Get tab-bar function
		*
		*  @return
		*    Function
		*/
		PLGUI_API ETabBarFunction GetFunction() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Set TabBar
		*
		*  @param[in] pTabBar
		*    TabBar
		*/
		PLGUI_API void SetTabBar(TabBar *pTabBar);

		/**
		*  @brief
		*    Set TabBarEntry
		*
		*  @param[in] pEntry
		*    TabBarEntry
		*/
		PLGUI_API void SetTabBarEntry(TabBarEntry *pEntry);

		/**
		*  @brief
		*    Set tab-bar function
		*
		*  @param[in] nFunction
		*    Function
		*/
		PLGUI_API void SetFunction(ETabBarFunction nFunction);


	//[-------------------------------------------------------]
	//[ Protected virtual Widget functions                    ]
	//[-------------------------------------------------------]
	protected:
		virtual void OnMouseEnter();
		virtual void OnMouseLeave();


	//[-------------------------------------------------------]
	//[ Private virtual AbstractButton functions              ]
	//[-------------------------------------------------------]
	private:
		virtual void OnButtonClicked();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Internal data (only to be set from TabBar itself!)
		TabBar			  *m_pTabBar;		/**< TabBar to which the entry belongs */
		TabBarEntry		  *m_pTabBarEntry;	/**< TabBarEntry to which the entry belongs */
		ETabBarFunction	   m_nFunction;		/**< TabBar function */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_TABBARBUTTON_H__
