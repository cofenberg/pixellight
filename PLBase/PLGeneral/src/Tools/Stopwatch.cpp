/*********************************************************\
 *  File: Stopwatch.cpp                                  *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/System/System.h"
#include "PLGeneral/Tools/Stopwatch.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Starts the stopwatch
*/
void Stopwatch::Start()
{
	m_bRunning = true;
	m_nStart   = System::GetInstance()->GetMicroseconds();
}

/**
*  @brief
*    Stops the stopwatch
*/
uint32 Stopwatch::Stop()
{
	// Is the stopwatch currently running?
	if (m_bRunning) {
		m_nStop    = System::GetInstance()->GetMicroseconds();
		m_bRunning = false;
		return m_nStop-m_nStart;
	} else {
		return 0;
	}
}

/**
*  @brief
*    Retrieves the number of microseconds since the stopwatch was started
*/
uint32 Stopwatch::GetMicroseconds() const
{
	return m_bRunning ? (System::GetInstance()->GetMicroseconds()-m_nStart) : (m_nStop-m_nStart);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
