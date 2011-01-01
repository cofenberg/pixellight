/*********************************************************\
 *  File: ModSnap.h                                      *
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


#ifndef __PLGUI_MODSNAP_H__
#define __PLGUI_MODSNAP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2i.h>
#include "PLGui/Modifiers/Modifier.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Modifier that snaps a widget to window borders
*/
class ModSnap : public Modifier {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, ModSnap, "PLGui", PLGui::Modifier, "Modifier that snaps a widget to window borders")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGUI_API ModSnap();

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~ModSnap();


	//[-------------------------------------------------------]
	//[ Protected virtual Modifier functions                  ]
	//[-------------------------------------------------------]
	protected:
		virtual void OnAttach(Widget &cWidget);
		virtual void OnDetach(Widget &cWidget);


	//[-------------------------------------------------------]
	//[ Protected virtual WidgetFunctions functions           ]
	//[-------------------------------------------------------]
	protected:
		void OnMove(const PLMath::Vector2i &vPos);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Try to unsnap the widget from it's current snap-targets
		*
		*  @param[in] vPos
		*    Position
		*/
		void TryUnsnap(const PLMath::Vector2i &vPos);

		/**
		*  @brief
		*    Try to snap to a specific widget
		*
		*  @param[in] vPos
		*    Position
		*  @param[in] pSnapWidget
		*    Widget to snap to, can be either the parent or a sibling widget
		*  @param[in] bParent
		*    'true', if pWidget is the parent window of this widget, else 'false'
		*/
		void TrySnap(const PLMath::Vector2i &vPos, Widget *pSnapWidget, bool bParent);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Event handlers
		PLCore::EventHandler<const PLMath::Vector2i&> EventHandlerMove;		/**< Widget gets moved, new widget position as parameter */

		// State
		PLMath::Vector2i  m_vPos;			/**< Current position */
		Widget			 *m_pSnappedLeft;	/**< Widget to which we are currently snapped on our left side */
		Widget			 *m_pSnappedRight;	/**< Widget to which we are currently snapped on our right side */
		Widget			 *m_pSnappedTop;	/**< Widget to which we are currently snapped on our top side */
		Widget			 *m_pSnappedBottom;	/**< Widget to which we are currently snapped on our bottom side */
		bool			  m_bPerformedSnap;	/**< Widget has performed a snap in the last cycle */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_MODSNAP_H__
