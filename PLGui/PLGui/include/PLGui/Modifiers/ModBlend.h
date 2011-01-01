/*********************************************************\
 *  File: ModBlend.h                                     *
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


#ifndef __PLGUI_MODBLEND_H__
#define __PLGUI_MODBLEND_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Modifiers/Modifier.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Timer;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Modifier that blends a widget in and out according to the mouse cursor
*/
class ModBlend : public Modifier {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, ModBlend, "PLGui", PLGui::Modifier, "Modifier that blends a widget in and out according to the mouse cursor")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_slot_0		(OnTimer, "Timer callback", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGUI_API ModBlend();

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~ModBlend();

		/**
		*  @brief
		*    Get blend animation time
		*
		*  @return
		*    Time in millisenconds for the blend animation
		*/
		PLGUI_API PLGeneral::uint32 GetBlendTime() const;

		/**
		*  @brief
		*    Set blend animation time
		*
		*  @param[in] nBlendTime
		*    Time in millisenconds for the blend animation
		*/
		PLGUI_API void SetBlendTime(PLGeneral::uint32 nBlendTime);


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
		virtual void OnMouseOver(bool bMouseOver);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called when the timer has fired
		*/
		void OnTimer();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::uint32  m_nTimeout;		/**< Timeout for blend animation (in milliseconds) */
		float			   m_fTrans;		/**< Current transparency (0.0f - 1.0f) */
		float			   m_fTransDest;	/**< Destination transparency (0.0f - 1.0f) */
		Timer			  *m_pTimer;		/**< Timer used for fading */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_MODBLEND_H__
