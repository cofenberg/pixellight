/*********************************************************\
 *  File: MutexWindows_CriticalSection.cpp               *
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
#include "PLCore/System/MutexWindows_CriticalSection.h"


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
MutexWindows_CriticalSection::MutexWindows_CriticalSection()
{
	// Initialize system critical section
	InitializeCriticalSectionAndSpinCount(&m_hCriticalSection, 0x00000400);
}

/**
*  @brief
*    Destructor
*/
MutexWindows_CriticalSection::~MutexWindows_CriticalSection()
{
	// Release system critical section
	DeleteCriticalSection(&m_hCriticalSection);
}


//[-------------------------------------------------------]
//[ Private virtual MutexImpl functions                   ]
//[-------------------------------------------------------]
bool MutexWindows_CriticalSection::Lock()
{
	// Lock critical section
	EnterCriticalSection(&m_hCriticalSection);

	// Done
	return true;
}

bool MutexWindows_CriticalSection::TryLock(uint64 nTimeout)
{
	// Lock critical section - there's no timeout version of critical section lock
	EnterCriticalSection(&m_hCriticalSection);

	// Done
	return true;
}

bool MutexWindows_CriticalSection::Unlock()
{
	// Release critical section
	LeaveCriticalSection(&m_hCriticalSection);

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
