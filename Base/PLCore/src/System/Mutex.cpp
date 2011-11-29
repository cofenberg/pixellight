/*********************************************************\
 *  File: Mutex.cpp                                      *
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
	#include "PLCore/System/MutexWindows_Mutex.h"
	#include "PLCore/System/MutexWindows_CriticalSection.h"
#elif defined(LINUX)
	#include "PLCore/System/MutexLinux.h"
#endif
#include "PLCore/System/Mutex.h"


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
Mutex::Mutex() :
	m_pMutexImpl(nullptr)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation - Windows has two different mutex implementations:
		// - "Mutex":            Lock/unlock across multiple processes
		// - "Critical Section": Lock/unlock only inside the same process
		// -> Default has to be "Mutex" to be on the safe universal side
		m_pMutexImpl = new MutexWindows_Mutex();
	#elif defined(LINUX)
		// Create Linux implementation
		m_pMutexImpl = new MutexLinux();
	#else
		// Unknown system
		#error "Unsupported platform"
	#endif
}

/**
*  @brief
*    Constructor
*/
Mutex::Mutex(bool bCriticalSection)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation - Windows has two different mutex implementations:
		// - "Mutex":            Lock/unlock across multiple processes
		// - "Critical Section": Lock/unlock only inside the same process
		if (bCriticalSection)
			m_pMutexImpl = new MutexWindows_CriticalSection();
		else
			m_pMutexImpl = new MutexWindows_Mutex();
	#elif defined(LINUX)
		// Create Linux implementation
		m_pMutexImpl = new MutexLinux();
	#else
		// Unknown system
		#error "Unsupported platform"
	#endif
}

/**
*  @brief
*    Destructor
*/
Mutex::~Mutex()
{
	// Destroy system specific implementation
	if (m_pMutexImpl)
		delete m_pMutexImpl;
}

/**
*  @brief
*    Locks the mutex
*/
bool Mutex::Lock()
{
	// Call system implementation
	return m_pMutexImpl->Lock();
}

/**
*  @brief
*    Locks the mutex, but only wait until timeout
*/
bool Mutex::TryLock(uint64 nTimeout)
{
	// Call system implementation
	return m_pMutexImpl->TryLock(nTimeout);
}

/**
*  @brief
*    Unlocks the mutex
*/
bool Mutex::Unlock()
{
	// Call system implementation
	return m_pMutexImpl->Unlock();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Mutex::Mutex(const Mutex &cSource) :
	m_pMutexImpl(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Mutex &Mutex::operator =(const Mutex &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
