/*********************************************************\
 *  File: SemaphoreLinux.cpp                             *
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
#ifdef ANDROID
	#include <sys/types.h>	// For "time_t" used within "linux/time.h" required for "timespec" (yyyeeeehhhaaa! *g*)
	#include <linux/time.h>	// For "timespec", else we get the error "error: aggregate 'timespec timeout' has incomplete type and cannot be defined"
#endif
#include "PLCore/System/SemaphoreLinux.h"


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
SemaphoreLinux::SemaphoreLinux(uint32 nValue, uint32 nMaxValue) :
	m_nMaxValue(nMaxValue),
	m_bCreated(sem_init(&m_hSemaphore, 0, nValue) == 0)
{
}

/**
*  @brief
*    Destructor
*/
SemaphoreLinux::~SemaphoreLinux()
{
	// Destroy system semaphore
	if (m_bCreated)
		sem_destroy(&m_hSemaphore);
}


//[-------------------------------------------------------]
//[ Private virtual SemaphoreImpl functions               ]
//[-------------------------------------------------------]
bool SemaphoreLinux::Lock()
{
	// Lock semaphore
	return (m_bCreated && sem_wait(&m_hSemaphore) == 0);
}

bool SemaphoreLinux::TryLock(uint64 nTimeout)
{
	#ifdef APPLE
		// Apple doesn't provide "sem_timedwait()"

		// Lock semaphore
		return (m_bCreated && sem_wait(&m_hSemaphore) == 0);
	#else
		// Setup control structure
		struct timespec timeout;
		timeout.tv_sec  = nTimeout/1000;
		timeout.tv_nsec = (nTimeout-timeout.tv_sec)*1000;

		// Lock semaphore
		return (m_bCreated && sem_timedwait(&m_hSemaphore, &timeout) == 0);
	#endif
}

bool SemaphoreLinux::Unlock()
{
	// Get the current value of the semaphore
	int32 nSemaphoreValue = 0;
	const int nResult = sem_getvalue(&m_hSemaphore, &nSemaphoreValue);

	// Is the value -1 or greater or equal to the maximum value?
	// Note: If the value is greater or equal to the maximum value, then no unlock is needed because
	// the semaphore is already unlocked.
	if (nResult == 0 && nSemaphoreValue >= 0 && m_nMaxValue > static_cast<uint32>(nSemaphoreValue)) {
		// Release semaphore
		if (m_bCreated && sem_post(&m_hSemaphore) == 0)
			return true; // Success
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
