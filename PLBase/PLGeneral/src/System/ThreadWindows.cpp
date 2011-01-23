/*********************************************************\
 *  File: ThreadWindows.cpp                              *
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
#include "PLGeneral/System/ThreadWindows.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
extern DWORD g_nTlsIndex; // 'Thread Local Storage' (TLS), TLS_OUT_OF_INDEXES on error


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ThreadWindows::ThreadWindows(Thread &cThread, bool bThreadID, uint32 nThreadID) :
	ThreadImpl(cThread, bThreadID, nThreadID),
	m_hThread(nullptr),
	m_nThreadID(0)
{
	// Open exisiting thread?
	if (bThreadID) {
		// Given thread ID or current thread?
		if (nThreadID == 0) {
			// Duplicate current thread handle
			HANDLE hThread = GetCurrentThread();
			if (DuplicateHandle(GetCurrentProcess(), hThread,
								GetCurrentProcess(), &m_hThread,
								0, false, DUPLICATE_SAME_ACCESS)) {
				// Success
				m_nThreadID = GetCurrentThreadId();
			}
		} else {
			// Open thread handle by ID
			m_hThread	= OpenThread(THREAD_ALL_ACCESS, false, nThreadID);
			m_nThreadID	= nThreadID;
		}
	}
}

/**
*  @brief
*    Destructor
*/
ThreadWindows::~ThreadWindows()
{
	// Close thread handle
	if (m_hThread)
		CloseHandle(m_hThread);
}


//[-------------------------------------------------------]
//[ Private virtual ThreadImpl functions                  ]
//[-------------------------------------------------------]
uint32 ThreadWindows::GetID() const
{
	// Return thread ID
	return m_nThreadID;
}

bool ThreadWindows::IsActive() const
{
	// Check if the thread is active
	return (m_hThread != nullptr);
}

bool ThreadWindows::Start()
{
	// Check if the thread has already been started
	if (!m_hThread) {
		// Create thread
		m_hThread = ::CreateThread(nullptr, 0, ThreadProc, static_cast<void*>(&GetThread()), 0, &m_nThreadID);
		if (m_hThread)
			return true; // Done
	}

	// Error, could not start thread
	return false;
}

bool ThreadWindows::Terminate()
{
	// Check if the thread has been started
	if (m_hThread) {
		// Terminate thread - we warned the user within the method documentation that this does not allow proper thread clean up...
		if (TerminateThread(m_hThread, 0)) {
			// Termination successful
			m_hThread = nullptr;
			return true;
		}
	}

	// Error, could not terminate thread
	return false;
}

bool ThreadWindows::Join()
{
	// Check if the thread has been started
	if (m_hThread) {
		// Wait for thread to stop
		if (WaitForSingleObject(m_hThread, INFINITE) == WAIT_OBJECT_0) {
			// Release thread
			CloseHandle(m_hThread);
			m_hThread = nullptr;

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool ThreadWindows::Join(uint32 nTimeout)
{
	// Check if the thread has been started
	if (m_hThread) {
		// Wait for thread to stop
		if (WaitForSingleObject(m_hThread, nTimeout) == WAIT_OBJECT_0) {
			// Release thread
			CloseHandle(m_hThread);
			m_hThread = nullptr;

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

Thread::EPriorityClass ThreadWindows::GetPriorityClass() const
{
	// Call OS function
	const DWORD dwPriorityClass = ::GetPriorityClass(m_hThread);

	// Wrap the priority setting
	switch (dwPriorityClass) {
		case IDLE_PRIORITY_CLASS:			return Thread::IdlePriorityClass;
		case BELOW_NORMAL_PRIORITY_CLASS:	return Thread::BelowNormalPriorityClass;
		case NORMAL_PRIORITY_CLASS:			return Thread::NormalPriorityClass;
		case ABOVE_NORMAL_PRIORITY_CLASS:	return Thread::AboveNormalPriorityClass;
		case HIGH_PRIORITY_CLASS:			return Thread::HighPriorityClass;
		case REALTIME_PRIORITY_CLASS:		return Thread::RealtimePriorityClass;
		default:							return Thread::NormalPriorityClass; // Error!
	}
}

bool ThreadWindows::SetPriorityClass(Thread::EPriorityClass nPriorityClass)
{
	// Wrap the priority setting
	DWORD dwPriorityClass;
	switch (nPriorityClass) {
		case Thread::IdlePriorityClass:			dwPriorityClass = IDLE_PRIORITY_CLASS;			break;
		case Thread::BelowNormalPriorityClass:	dwPriorityClass = BELOW_NORMAL_PRIORITY_CLASS;	break;
		case Thread::NormalPriorityClass:		dwPriorityClass = NORMAL_PRIORITY_CLASS;		break;
		case Thread::AboveNormalPriorityClass:	dwPriorityClass = ABOVE_NORMAL_PRIORITY_CLASS;	break;
		case Thread::HighPriorityClass:			dwPriorityClass = HIGH_PRIORITY_CLASS;			break;
		case Thread::RealtimePriorityClass:		dwPriorityClass = REALTIME_PRIORITY_CLASS;		break;
		default:								return false; // Error!
	}

	// Call OS function
	return (::SetPriorityClass(m_hThread, dwPriorityClass) != 0);
}

Thread::EPriority ThreadWindows::GetPriority() const
{
	// Call OS function
	const int nPriority = ::GetThreadPriority(m_hThread);

	// Wrap the priority setting
	switch (nPriority) {
		case THREAD_PRIORITY_IDLE:			return Thread::IdlePriority;
		case THREAD_PRIORITY_LOWEST:		return Thread::LowestPriority;
		case THREAD_PRIORITY_BELOW_NORMAL:	return Thread::BelowNormalPriority;
		case THREAD_PRIORITY_NORMAL:		return Thread::NormalPriority;
		case THREAD_PRIORITY_ABOVE_NORMAL:	return Thread::AboveNormalPriority;
		case THREAD_PRIORITY_HIGHEST:		return Thread::HighestPriority;
		case THREAD_PRIORITY_TIME_CRITICAL:	return Thread::TimeCriticalPriority;
		default:							return Thread::NormalPriority; // Error!
	}
}

bool ThreadWindows::SetPriority(Thread::EPriority nPriority)
{
	// Wrap the priority setting
	int nWindowsPriority;
	switch (nPriority) {
		case Thread::IdlePriority:			nWindowsPriority = THREAD_PRIORITY_IDLE;			break;
		case Thread::LowestPriority:		nWindowsPriority = THREAD_PRIORITY_LOWEST;			break;
		case Thread::BelowNormalPriority:	nWindowsPriority = THREAD_PRIORITY_BELOW_NORMAL;	break;
		case Thread::NormalPriority:		nWindowsPriority = THREAD_PRIORITY_NORMAL;			break;
		case Thread::AboveNormalPriority:	nWindowsPriority = THREAD_PRIORITY_ABOVE_NORMAL;	break;
		case Thread::HighestPriority:		nWindowsPriority = THREAD_PRIORITY_HIGHEST;			break;
		case Thread::TimeCriticalPriority:	nWindowsPriority = THREAD_PRIORITY_TIME_CRITICAL;	break;
		default:							return false; // Error!
	}

	// Call OS function
	return (::SetThreadPriority(m_hThread, nWindowsPriority) != 0);
}


//[-------------------------------------------------------]
//[ Private static functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static thread callback function
*/
DWORD WINAPI ThreadWindows::ThreadProc(LPVOID lpParameter)
{
	// Get the PixelLight thread instance
	Thread *pThread = static_cast<Thread*>(lpParameter);
	if (pThread) {
		// Initialize the TLS index for this thread so we can find out the PixelLight
		// thread instance within 'SystemWindows::GetCurrentThread()'
		if (g_nTlsIndex != TLS_OUT_OF_INDEXES && TlsSetValue(g_nTlsIndex, pThread)) {
			// Run the thread
			return pThread->Run();
		}
	}

	// Error!
	return 0;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
