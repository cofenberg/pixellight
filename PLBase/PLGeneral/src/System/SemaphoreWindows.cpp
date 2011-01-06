/*********************************************************\
 *  File: SemaphoreWindows.cpp                           *
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
#include "PLGeneral/System/SemaphoreWindows.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SemaphoreWindows::SemaphoreWindows(uint32 nValue, uint32 nMaxValue) :
	m_hSemaphore(::CreateSemaphore(nullptr, nValue, nMaxValue, nullptr))
{
}

/**
*  @brief
*    Destructor
*/
SemaphoreWindows::~SemaphoreWindows()
{
	// Destroy system semaphore
	if (m_hSemaphore)
		CloseHandle(m_hSemaphore);
}


//[-------------------------------------------------------]
//[ Private virtual SemaphoreImpl functions               ]
//[-------------------------------------------------------]
bool SemaphoreWindows::Lock()
{
	// Lock semaphore
	return (m_hSemaphore && WaitForSingleObject(m_hSemaphore, INFINITE) == WAIT_OBJECT_0);
}

bool SemaphoreWindows::TryLock(uint32 nTimeout)
{
	// Lock semaphore
	return (m_hSemaphore && WaitForSingleObject(m_hSemaphore, nTimeout) == WAIT_OBJECT_0);
}

bool SemaphoreWindows::Unlock()
{
	// Release semaphore
	return (m_hSemaphore && ReleaseSemaphore(m_hSemaphore, 1, nullptr));
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
