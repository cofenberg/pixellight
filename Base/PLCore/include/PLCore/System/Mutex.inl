/*********************************************************\
 *  File: Mutex.inl                                      *
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
#include "PLCore/System/MutexImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Locks the mutex
*/
inline bool Mutex::Lock()
{
	// Call system implementation
	return m_pMutexImpl->Lock();
}

/**
*  @brief
*    Locks the mutex, but only wait until timeout
*/
inline bool Mutex::TryLock(uint64 nTimeout)
{
	// Call system implementation
	return m_pMutexImpl->TryLock(nTimeout);
}

/**
*  @brief
*    Unlocks the mutex
*/
inline bool Mutex::Unlock()
{
	// Call system implementation
	return m_pMutexImpl->Unlock();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
