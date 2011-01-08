/*********************************************************\
 *  File: Stopwatch.h                                    *
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


#ifndef __PLGENERAL_STOPWATCH_H__
#define __PLGENERAL_STOPWATCH_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/PLGeneral.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Stopwatch
*/
class Stopwatch {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		inline Stopwatch();

		/**
		*  @brief
		*    Destructor
		*/
		inline ~Stopwatch();

		/**
		*  @brief
		*    Starts the stopwatch
		*
		*  @note
		*    - If the stopwatch is already running it's restarted
		*/
		PLGENERAL_API void Start();

		/**
		*  @brief
		*    Stops the stopwatch
		*
		*  @return
		*    The ellapsed time in microseconds since Start()
		*/
		PLGENERAL_API uint32 Stop();

		/**
		*  @brief
		*    Returns the number of weeks since the stopwatch was started
		*
		*  @return
		*    Number of weeks elapsed since the stopwatch was started
		*/
		inline float GetWeeks() const;

		/**
		*  @brief
		*    Returns the number of days since the stopwatch was started
		*
		*  @return
		*    Number of days elapsed since the stopwatch was started
		*/
		inline float GetDays() const;

		/**
		*  @brief
		*    Returns the number of hours since the stopwatch was started
		*
		*  @return
		*    Number of hours elapsed since the stopwatch was started
		*/
		inline float GetHours() const;

		/**
		*  @brief
		*    Returns the number of minutes since the stopwatch was started
		*
		*  @return
		*    Number of minutes elapsed since the stopwatch was started
		*/
		inline float GetMinutes() const;

		/**
		*  @brief
		*    Returns the number of seconds since the stopwatch was started
		*
		*  @return
		*    Number of seconds elapsed since the stopwatch was started
		*/
		inline float GetSeconds() const;

		/**
		*  @brief
		*    Returns the number of milliseconds since the stopwatch was started
		*
		*  @return
		*    Number of milliseconds elapsed since the stopwatch was started
		*/
		inline float GetMilliseconds() const;

		/**
		*  @brief
		*    Retrieves the number of microseconds since the stopwatch was started
		*
		*  @return
		*    Number of microseconds elapsed since the stopwatch was started
		*/
		PLGENERAL_API uint32 GetMicroseconds() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool   m_bRunning;	/**< Is the stopwatch currently running? */
		uint32 m_nStart;	/**< Stopwatch start time (microseconds) */
		uint32 m_nStop;		/**< Stopwatch stop time (microseconds) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Tools/Stopwatch.inl"


#endif // __PLGENERAL_STOPWATCH_H__
