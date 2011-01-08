/*********************************************************\
 *  File: Timer.h                                        *
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


#ifndef __PLGUI_TIMER_H__
#define __PLGUI_TIMER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/Event.h>
#include "PLGui/PLGui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Gui;
class TimerThread;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Timer class
*/
class Timer {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Gui;
	friend class TimerThread;


	//[-------------------------------------------------------]
	//[ Public events                                         ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<> EventStart;		/**< The timer has been started */
		PLCore::Event<> EventStop;		/**< The timer has been stopped */
		PLCore::Event<> EventFire;		/**< The timer has fired */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cGui
		*    Owner GUI
		*/
		PLGUI_API Timer(Gui &cGui);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API ~Timer();

		/**
		*  @brief
		*    Get owner GUI
		*
		*  @return
		*    Pointer to GUI object (never a null pointer)
		*/
		PLGUI_API Gui *GetGui() const;

		/**
		*  @brief
		*    Get timer ID
		*
		*  @return
		*    Timer ID
		*/
		PLGUI_API PLGeneral::uint32 GetID() const;

		/**
		*  @brief
		*    Set timer ID
		*
		*  @param[in] nID
		*    Timer ID
		*/
		PLGUI_API void SetID(PLGeneral::uint32 nID);

		/**
		*  @brief
		*    Check if timer is active
		*
		*  @return
		*    'true' if timer is currently active
		*/
		PLGUI_API bool IsActive() const;

		/**
		*  @brief
		*    Check if timer fires only once
		*
		*  @return
		*    'true' if once
		*/
		PLGUI_API bool IsOnce() const;

		/**
		*  @brief
		*    Get timeout interval
		*
		*  @return
		*    Timeout interval
		*/
		PLGUI_API PLGeneral::uint32 GetTimeout() const;

		/**
		*  @brief
		*    Start timer
		*
		*  @param[in] nTimeout
		*    Timeout in milliseconds after which the timer fires repeatedly
		*
		*  @note
		*    - If the timer is already running it's stopped and started again
		*/
		PLGUI_API void Start(PLGeneral::uint32 nTimeout);

		/**
		*  @brief
		*    Start timer only once, not periodically
		*
		*  @param[in] nTimeout
		*    Timeout in milliseconds after which the timer fires
		*
		*  @note
		*    - If the timer is already running it's stopped and started again
		*/
		PLGUI_API void StartOnce(PLGeneral::uint32 nTimeout);

		/**
		*  @brief
		*    Stop timer
		*/
		PLGUI_API void Stop();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Fire timer
		*/
		PLGUI_API void Fire();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Gui				  *m_pGui;		/**< Pointer to owner GUI */
		PLGeneral::uint32  m_nID;		/**< Timer ID */
		TimerThread		  *m_pThread;	/**< Current timer thread */
		bool			   m_bActive;	/**< Timer is active? */
		bool			   m_bOnce;		/**< Timer is firing only once? */
		PLGeneral::uint32  m_nTimeout;	/**< Timeout value */


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		static PLGeneral::uint32 m_nNextID;	/**< ID counter */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_TIMER_H__
