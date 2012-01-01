/*********************************************************\
 *  File: AbstractTooltip.h                              *
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


#ifndef __PLGUI_ABSTRACTTOOLTIP_H__
#define __PLGUI_ABSTRACTTOOLTIP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/Event.h>
#include "PLGui/Gui/Resources/Timer.h"
#include "PLGui/Widgets/Widget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Base class for tooltip windows
*/
class AbstractTooltip : public Widget {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, AbstractTooltip, "PLGui", PLGui::Widget, "Base class for tooltip windows")
		// Attributes
		pl_attribute(Text,		PLCore::String,	"",		ReadWrite,	GetSet,	"Tooltip text",											"")
		pl_attribute(Timeout,	PLCore::uint64,	5000,	ReadWrite,	GetSet,	"Time (in ms) after which the tooltip is blended out",	"")
		// Signals
		pl_signal_0(SignalTimeout,	"Timeout has been reached",	"")
		// Slots
		pl_slot_0(OnTimer,	"Timer callback",	"")
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
		PLGUI_API AbstractTooltip(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~AbstractTooltip();

		/**
		*  @brief
		*    Get tooltip text
		*
		*  @return
		*    Tooltip text
		*/
		PLGUI_API PLCore::String GetText() const;

		/**
		*  @brief
		*    Set tooltip text
		*
		*  @param[in] sTooltip
		*    Tooltip text
		*/
		PLGUI_API void SetText(const PLCore::String &sTooltip);

		/**
		*  @brief
		*    Get tooltip timeout
		*
		*  @return
		*    Timeout (in ms)
		*/
		PLGUI_API PLCore::uint64 GetTimeout() const;

		/**
		*  @brief
		*    Set tooltip timeout
		*
		*  @param[in] nTimeout
		*    Timeout (in ms)
		*/
		PLGUI_API void SetTimeout(PLCore::uint64 nTimeout);

		/**
		*  @brief
		*    Show tooltip
		*
		*  @param[in] vPos
		*    Position of tooltip
		*/
		PLGUI_API void ShowTooltip(const PLMath::Vector2i &vPos);

		/**
		*  @brief
		*    Blend out tooltip
		*/
		PLGUI_API void BlendOut();


	//[-------------------------------------------------------]
	//[ Protected virtual AbstractTooltip functions           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called on display of the tooltip
		*/
		virtual void OnShowTooltip();

		/**
		*  @brief
		*    Called on timeout
		*/
		virtual void OnTimeout();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the timer has fired
		*/
		void OnTimer();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::String	m_sTooltip;	/**< Tooltip text */
		PLCore::uint64	m_nTimeout;	/**< Timeout (in ms) */
		Timer			m_cTimer;	/**< Timer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_ABSTRACTTOOLTIP_H__
