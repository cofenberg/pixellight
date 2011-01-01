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
#include <sys/sem.h>
#include <sys/types.h>
#include "PLGeneral/System/SemaphoreLinux.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
#if defined(_SEM_SEMUN_UNDEFINED)
	union semun {
		int val;
		struct semid_ds *buf;
		ushort *array;
	};
#endif

// The access permissions for the semaphore. By default only the creator has access to it.
static const int SemiPermission = 0600;


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SemaphoreLinux::SemaphoreLinux(uint32 nValue, uint32 nMaxValue) :
	m_hSemaphore(semget(IPC_PRIVATE, 1, SemiPermission)),
	m_nMaxValue(nMaxValue)
{
	// [DEBUG]
#ifdef DEBUG
	if (m_hSemaphore < 0)
		fprintf(stderr, "Could not create semaphore\n errorcode: %d(%s)", errno, strerror(errno));
#endif
}

/**
*  @brief
*    Destructor
*/
SemaphoreLinux::~SemaphoreLinux()
{
	// Destroy system semaphore
	if (m_hSemaphore > 0) semctl(m_hSemaphore, 0, IPC_RMID, 0);
}


//[-------------------------------------------------------]
//[ Private virtual SemaphoreImpl functions               ]
//[-------------------------------------------------------]
bool SemaphoreLinux::Lock()
{
	// Setup control structure
	struct sembuf op_semlock = { 0, -1, SEM_UNDO };

	// Lock semaphore
	return (m_hSemaphore > 0 && semop(m_hSemaphore, &op_semlock, 1) > 0);
}

bool SemaphoreLinux::TryLock(uint32 nTimeout)
{
	// Setup control structure
	struct sembuf op_semlock = { 0, -1, SEM_UNDO };
	struct timespec timeout;
	timeout.tv_sec  = nTimeout/1000;
	timeout.tv_nsec = (nTimeout-timeout.tv_sec)*1000;

	// Lock semaphore
	return (m_hSemaphore > 0 && semtimedop(m_hSemaphore, &op_semlock, 1, &timeout) > 0);
}

bool SemaphoreLinux::Unlock()
{
	// Setup control structure
	struct sembuf op_semunlock = { 0, 1, (IPC_NOWAIT|SEM_UNDO) };

	// Get the current value of the semaphore
	union semun arg;
	arg.val = 0;
	int32 sem_val = semctl(m_hSemaphore, 0, GETVAL, arg);

	// Is the value -1 or greater or equal to the maximum value?
	// Note: If the value is greater or equal to the maximum value, then no unlock is needed because
	// the semaphore is already unlocked.
	if (sem_val >= 0 && m_nMaxValue > (uint32)sem_val) {
		// Release semaphore
		if (m_hSemaphore > 0 && semop(m_hSemaphore, &op_semunlock, 1) > 0)
			return true; // Success
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
