/*********************************************************\
 *  File: Thread.cpp                                     *
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
#if defined(WIN32)
	#include "PLCore/System/ThreadWindows.h"
#elif defined(LINUX)
	#include "PLCore/System/ThreadLinux.h"
#endif
#include "PLCore/System/Thread.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Thread::Thread() :
	m_pThreadImpl(nullptr),
	m_pThreadFunction(nullptr),
	m_pStaticFunction(nullptr),
	m_pStaticData(nullptr)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pThreadImpl = new ThreadWindows(*this, false, 0);
	#elif defined(LINUX)
		// Create Linux implementation
		m_pThreadImpl = new ThreadLinux(*this, false, 0);
	#else
		// Unknown system
		#error "Unsupported platform"
	#endif
}

/**
*  @brief
*    Constructor
*/
Thread::Thread(ThreadFunction *pThreadFunction) :
	m_pThreadImpl(nullptr),
	m_pThreadFunction(pThreadFunction),
	m_pStaticFunction(nullptr),
	m_pStaticData(nullptr)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pThreadImpl = new ThreadWindows(*this, false, 0);
	#elif defined(LINUX)
		// Create Linux implementation
		m_pThreadImpl = new ThreadLinux(*this, false, 0);
	#else
		// Unknown system
		#error "Unsupported platform"
	#endif
}

/**
*  @brief
*    Constructor
*/
Thread::Thread(THREADFUNCTION pStaticFunction, void *pData) :
	m_pThreadImpl(nullptr),
	m_pThreadFunction(nullptr),
	m_pStaticFunction(pStaticFunction),
	m_pStaticData(pData)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pThreadImpl = new ThreadWindows(*this, false, 0);
	#elif defined(LINUX)
		// Create Linux implementation
		m_pThreadImpl = new ThreadLinux(*this, false, 0);
	#else
		// Unknown system
		#error "Unsupported platform"
	#endif
}

/**
*  @brief
*    Constructor
*/
Thread::Thread(uint32 nThreadID) :
	m_pThreadImpl(nullptr),
	m_pThreadFunction(nullptr),
	m_pStaticFunction(nullptr),
	m_pStaticData(nullptr)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pThreadImpl = new ThreadWindows(*this, true, nThreadID);
	#elif defined(LINUX)
		// Create Linux implementation
		m_pThreadImpl = new ThreadLinux(*this, true, nThreadID);
	#else
		// Unknown system
		#error "Unsupported platform"
	#endif
}

/**
*  @brief
*    Destructor
*/
Thread::~Thread()
{
	// Destroy system specific implementation
	if (m_pThreadImpl)
		delete m_pThreadImpl;
}

/**
*  @brief
*    Returns the name of the thread
*/
String Thread::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Sets the name of the thread
*/
void Thread::SetName(const String &sName)
{
	m_sName = sName;
}

/**
*  @brief
*    Returns the unique system ID of the thread
*/
handle Thread::GetID() const
{
	// Call system implementation
	return m_pThreadImpl->GetID();
}

/**
*  @brief
*    Returns whether the thread is active
*/
bool Thread::IsActive() const
{
	// Call system implementation
	return m_pThreadImpl->IsActive();
}

/**
*  @brief
*    Starts the execution of the thread
*/
bool Thread::Start()
{
	// Call system implementation
	return m_pThreadImpl->Start();
}

/**
*  @brief
*    Stops the execution of the thread
*/
bool Thread::Terminate()
{
	// Call system implementation
	return m_pThreadImpl->Terminate();
}

/**
*  @brief
*    Waits until the thread has been stopped
*/
bool Thread::Join()
{
	// Call system implementation
	return m_pThreadImpl->Join();
}

/**
*  @brief
*    Waits until the thread has been stopped
*/
bool Thread::Join(uint64 nTimeout)
{
	// Call system implementation
	return m_pThreadImpl->Join(nTimeout);
}

/**
*  @brief
*    Returns the priority class the thread is in
*/
Thread::EPriorityClass Thread::GetPriorityClass() const
{
	// Call system implementation
	return m_pThreadImpl->GetPriorityClass();
}

/**
*  @brief
*    Sets the priority class the thread is in
*/
bool Thread::SetPriorityClass(EPriorityClass nPriorityClass)
{
	// Call system implementation
	return m_pThreadImpl->SetPriorityClass(nPriorityClass);
}

/**
*  @brief
*    Returns the thread priority within the priority class it is in
*/
Thread::EPriority Thread::GetPriority() const
{
	// Call system implementation
	return m_pThreadImpl->GetPriority();
}

/**
*  @brief
*    Sets the thread priority within the priority class it is in
*/
bool Thread::SetPriority(EPriority nPriority)
{
	// Call system implementation
	return m_pThreadImpl->SetPriority(nPriority);
}


//[-------------------------------------------------------]
//[ Public virtual ThreadFunction functions               ]
//[-------------------------------------------------------]
int Thread::Run()
{
	// Determine type of thread function
	if (m_pThreadFunction) {
		// Call Run() method of thread function
		return m_pThreadFunction->Run();
	} else if (m_pStaticFunction) {
		// Call static thread function
		return m_pStaticFunction(m_pStaticData);
	} else {
		// Empty thread
		return 0;
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Thread::Thread(const Thread &cSource) :
	m_pThreadImpl(nullptr),
	m_pThreadFunction(nullptr),
	m_pStaticFunction(nullptr),
	m_pStaticData(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Thread &Thread::operator =(const Thread &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
