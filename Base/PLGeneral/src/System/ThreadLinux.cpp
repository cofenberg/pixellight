/*********************************************************\
 *  File: ThreadLinux.cpp                                *
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
#include <signal.h>
#include "PLGeneral/System/Mutex.h"
#include "PLGeneral/System/ThreadLinux.h"

// [DEBUG]
#ifdef DEBUG
	#include <stdio.h>
#endif


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
ThreadLinux::ThreadLinux(Thread &cThread, bool bThreadID, uint32 nThreadID) :
	ThreadImpl(cThread, bThreadID, nThreadID),
	m_nThreadID(0),
	m_pMutex(nullptr),
	m_nPriorityClass(Thread::NormalPriorityClass),
	m_nPriority(Thread::NormalPriority)
{
	// Shall the current thread ID be obtained?
	// [TODO] Implement nThreadID != 0 to open existing threads
	if (bThreadID && nThreadID == 0) {
		// Get current thread
		m_nThreadID = pthread_self();
	} else {
		// Create mutex
		m_pMutex = new Mutex();
	}
}

/**
*  @brief
*    Destructor
*/
ThreadLinux::~ThreadLinux()
{
	// Delete mutex
	if (m_pMutex)
		delete m_pMutex;
}


//[-------------------------------------------------------]
//[ Private virtual ThreadImpl functions                  ]
//[-------------------------------------------------------]
uint32 ThreadLinux::GetID() const
{
	// Return thread ID
	return m_nThreadID;
}

bool ThreadLinux::IsActive() const
{
	// Check if the thread is active
	return (m_nThreadID > 0);
}

bool ThreadLinux::Start()
{
	// Check if the thread has already been started
	if (!m_nThreadID) {
		// Create thread
		const int nStatus = pthread_create(&m_nThreadID, nullptr, &RunThread, static_cast<void*>(&GetThread()));
		if (!nStatus) {
			// Success
			return true;
		}
	}

	// Error, could not start thread
	return false;
}

bool ThreadLinux::Terminate()
{
	// Check if the thread has been started
	if (m_nThreadID) {
		// [DEBUG]
		#ifdef DEBUG
			printf("\n\n[DEBUG] Terminate thread %d\n\n", m_nThreadID);
		#endif
		pthread_cancel(m_nThreadID);
		m_nThreadID = 0;

		// Unlock the execution mutex because the thread was terminated
		// -> the thread didn't unlock the mutex itself on exiting
		if (m_pMutex)
			m_pMutex->Unlock();

		// Done
		return true;
	}

	// Error, could not terminate thread
	return false;
}

bool ThreadLinux::Join()
{
	// Check if the thread has been started
	if (m_nThreadID) {
		// Wait for thread to stop
		if (!pthread_join(m_nThreadID, nullptr)) {
			// Release thread
			m_nThreadID = 0;

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool ThreadLinux::Join(uint64 nTimeout)
{
	// [TODO] We need a timed join here, which can be implemented e.g. like this:
	//        http://www.opengroup.org/onlinepubs/000095399/xrat/xsh_chap02.html#tag_03_02_08_21
	return Join();

	/*
	if (m_nThreadID) {
		if (m_pMutex && m_pMutex->Lock(nTimeout)) {
			// Unlock the execution mutex after locking it, because
			// if we could lock the mutex, the thread itself has stopped
			m_pMutex->Unlock();

			// Wait for thread to stop
			if (!pthread_join(m_nThreadID, nullptr)) {
				// Release thread
				m_nThreadID = 0;

				// Done
				return true;
			}
		}
	}

	// Error!
	return false;
	*/
}

Thread::EPriorityClass ThreadLinux::GetPriorityClass() const
{
	return m_nPriorityClass;
}

bool ThreadLinux::SetPriorityClass(Thread::EPriorityClass nPriorityClass)
{
	// Backup given setting
	m_nPriorityClass = nPriorityClass;

	// pthread_setschedparam: No implementation because by default the priority is managed directly by the kernel

	// Done
	return true;
}

Thread::EPriority ThreadLinux::GetPriority() const
{
	return m_nPriority;
}

bool ThreadLinux::SetPriority(Thread::EPriority nPriority)
{
	// Backup given setting
	m_nPriority = nPriority;

	// pthread_setschedparam: No implementation because by default the priority is managed directly by the kernel

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Private static functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static thread callback function
*/
void *ThreadLinux::RunThread(void *pParameter)
{
	if (pParameter) {
		// Get thread object
		Thread *pThread = static_cast<Thread*>(pParameter);

		// Lock the thread's execution mutex
		Mutex *pMutex = static_cast<ThreadLinux*>(pThread->m_pThreadImpl)->m_pMutex;
		pMutex->Lock();

		// Run thread
		int nRetVal = pThread->Run();

		// Unlock the thread's execution mutex
		pMutex->Unlock();

		// Done
		return reinterpret_cast<void*>(nRetVal);
	} else {
		// No return value
		return nullptr;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
