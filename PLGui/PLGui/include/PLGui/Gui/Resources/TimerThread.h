/*********************************************************\
 *  File: TimerThread.h                                  *
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


#ifndef __PLGUI_TIMERTHREAD_H__
#define __PLGUI_TIMERTHREAD_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/System/Thread.h>
#include "PLGui/PLGui.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class Mutex;
}
namespace PLGui {
	class Timer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Timer operation thread
*/
class TimerThread : public PLGeneral::Thread {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cTimer
		*    Reference to the owning Timer object
		*  @param[in] nTimeout
		*    Timeout (in milliseconds)
		*  @param[in] bOnce
		*    'true' if the timer shall fire only once, else 'false'
		*/
		PLGUI_API TimerThread(Timer &cTimer, PLGeneral::uint32 nTimeout, bool bOnce);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~TimerThread();

		/**
		*  @brief
		*    Stop timer thread
		*/
		PLGUI_API void StopTimer();

		/**
		*  @brief
		*    Fire timer
		*/
		PLGUI_API void Fire();


	//[-------------------------------------------------------]
	//[ Private virtual PLGeneral::ThreadFunction functions   ]
	//[-------------------------------------------------------]
	private:
		virtual int Run();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Timer			  &m_cTimer;	/**< Timer to that this thread belongs */
		PLGeneral::Mutex  *m_pMutex;	/**< Timer mutex (always valid!) */
		PLGeneral::uint32  m_nTimeout;	/**< Timeout value */
		bool			   m_bOnce;		/**< Timer is firing only once? */
		volatile bool	   m_bShutdown;	/**< Shutdown thread? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_TIMERTHREAD_H__
