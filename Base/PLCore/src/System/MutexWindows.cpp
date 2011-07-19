/*********************************************************\
 *  File: MutexWindows.cpp                               *
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
#include "PLCore/System/MutexWindows.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MutexWindows::MutexWindows() :
	m_hMutex(::CreateMutex(nullptr, false, nullptr))
{
}

/**
*  @brief
*    Destructor
*/
MutexWindows::~MutexWindows()
{
	// Destroy system mutex
	if (m_hMutex)
		CloseHandle(m_hMutex);
}


//[-------------------------------------------------------]
//[ Private virtual MutexImpl functions                   ]
//[-------------------------------------------------------]
bool MutexWindows::Lock()
{
	// Lock mutex
	return (m_hMutex && WaitForSingleObject(m_hMutex, INFINITE) == WAIT_OBJECT_0);
}

bool MutexWindows::TryLock(uint64 nTimeout)
{
	// Lock mutex
	return (m_hMutex && WaitForSingleObject(m_hMutex, static_cast<DWORD>(nTimeout)) == WAIT_OBJECT_0);
}

bool MutexWindows::Unlock()
{
	// Release mutex
	return (m_hMutex && ReleaseMutex(m_hMutex));
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
