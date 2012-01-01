/*********************************************************\
 *  File: MutexGuard.inl                                 *
 *      Mutex guard implementation
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
MutexGuard::MutexGuard(Mutex &cMutex) :
	m_pMutex(&cMutex)
{
	// Lock the given mutex, or at least try it! ("usually", this lock is ensuring that we're getting only out of here if we've got a lock!)
	m_bLocked = cMutex.Lock();
}

/**
*  @brief
*    Constructor
*/
MutexGuard::MutexGuard(Mutex &cMutex, uint64 nTimeout) :
	m_pMutex(&cMutex)
{
	// Lock the given mutex, or at least try it!
	m_bLocked = cMutex.TryLock(nTimeout);
}

/**
*  @brief
*    Destructor
*/
MutexGuard::~MutexGuard()
{
	// If the mutex was locked successfully, unlock it right now!
	if (m_bLocked)
		m_pMutex->Unlock();
}

/**
*  @brief
*    Returns whether the used mutex was locked successfully
*/
bool MutexGuard::IsLocked() const
{
	return m_bLocked;
}

/**
*  @brief
*    Returns the used mutex
*/
Mutex &MutexGuard::GetMutex() const
{
	return *m_pMutex;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
MutexGuard::MutexGuard(const MutexGuard &cSource) :
	m_pMutex(nullptr),
	m_bLocked(false)
{
	// Not implemented
}

/**
*  @brief
*    Copy operator
*/
MutexGuard &MutexGuard::operator =(const MutexGuard &cSource)
{
	// Not implemented
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
