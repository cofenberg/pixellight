/*********************************************************\
 *  File: Semaphore.inl                                  *
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
#include "PLCore/System/SemaphoreImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Locks the semaphore
*/
inline bool Semaphore::Lock()
{
	// Lock semaphore
	if (m_pSemaphoreImpl->Lock()) {
		// Success
		m_nValue--;
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Locks the semaphore, but only wait until timeout
*/
inline bool Semaphore::TryLock(uint64 nTimeout)
{
	// Lock semaphore
	if (m_pSemaphoreImpl->TryLock(nTimeout)) {
		// Success
		m_nValue--;
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Unlocks the semaphore
*/
inline bool Semaphore::Unlock()
{
	// Release semaphore
	m_nValue++;
	if (m_pSemaphoreImpl->Unlock()) {
		// Success
		return true;
	}

	// Error!
	m_nValue--;
	return false;
}

/**
*  @brief
*    Gets the current value of the semaphore
*/
inline uint32 Semaphore::GetValue() const
{
	// Return semaphore value
	return m_nValue;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
