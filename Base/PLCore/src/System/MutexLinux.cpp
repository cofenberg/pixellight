/*********************************************************\
 *  File: MutexLinux.cpp                                 *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/System/MutexLinux.h"


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
MutexLinux::MutexLinux()
{
	// Create system mutex
	pthread_mutex_init(&m_sMutex, nullptr);
}

/**
*  @brief
*    Destructor
*/
MutexLinux::~MutexLinux()
{
	// Destroy system mutex
	pthread_mutex_destroy(&m_sMutex);
}


//[-------------------------------------------------------]
//[ Private virtual MutexImpl functions                   ]
//[-------------------------------------------------------]
bool MutexLinux::Lock()
{
	// Lock mutex
	return !pthread_mutex_lock(&m_sMutex);
}

bool MutexLinux::TryLock(uint64 nTimeout)
{
	#if (ANDROID || APPLE)
		// There's no implementation of "pthread_mutex_timedlock()" within the Android NDK, even
		// if the function is listed within the headers. Depending on the API level, it's defined
		// out, meaning no compiler error when using API level 8, but a compiler error when using API
		// level 9 (some sources stating this is an error within the shipped "pthread.h"-header).

		// Apple has no "pthread_mutex_lock()", too

		// Lock mutex - just use the version without timeout :/
		return !pthread_mutex_lock(&m_sMutex);
	#else
		// Setup timeout structure
		struct timespec timeout;
		timeout.tv_sec  = nTimeout/1000;
		timeout.tv_nsec = (nTimeout-timeout.tv_sec)*1000;

		// Lock mutex
		return !pthread_mutex_timedlock(&m_sMutex, &timeout);
	#endif
}

bool MutexLinux::Unlock()
{
	// Release mutex
	return !pthread_mutex_unlock(&m_sMutex);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
