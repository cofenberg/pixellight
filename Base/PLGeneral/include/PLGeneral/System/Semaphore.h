/*********************************************************\
 *  File: Semaphore.h                                    *
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


#ifndef __PLGENERAL_SEMAPHORE_H__
#define __PLGENERAL_SEMAPHORE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/PLGeneral.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class SemaphoreImpl;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Counting semaphore class
*
*  @note
*    - Implementation of the bridge design pattern, this class is the abstraction
*/
class Semaphore {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nValue
		*    Initial value of the semaphore (usually >0)
		*  @param[in] nMaxValue
		*    Maximum value of the semaphore
		*/
		PLGENERAL_API Semaphore(uint32 nValue, uint32 nMaxValue);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API ~Semaphore();

		/**
		*  @brief
		*    Locks the semaphore
		*
		*  @return
		*    'true' if successful, 'false' on error
		*
		*  @note
		*    - Other known names for this operation: p, wait, acquire, down
		*    - Blocking if no 'signal' left
		*    - Use the lock method with a timeout to avoid potential deadlocks
		*/
		PLGENERAL_API bool Lock();

		/**
		*  @brief
		*    Locks the semaphore, but only wait until timeout
		*
		*  @param[in] nTimeout
		*    Timeout in milliseconds
		*
		*  @return
		*    'true' if successful, 'false' on error
		*
		*  @note
		*    - 'nTimeout = 0' means: Return immediately if no 'signal' left
		*
		*  @see
		*    - Lock()
		*/
		PLGENERAL_API bool TryLock(uint64 nTimeout);

		/**
		*  @brief
		*    Unlocks the semaphore
		*
		*  @return
		*    'true' if successful, 'false' on error
		*
		*  @note
		*    - Other known names for this operation: v, signal, release, up
		*/
		PLGENERAL_API bool Unlock();

		/**
		*  @brief
		*    Gets the current value of the semaphore
		*
		*  @return
		*    Current semaphore value (number of 'signals' left)
		*/
		PLGENERAL_API uint32 GetValue() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Semaphore(const Semaphore &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Semaphore &operator =(const Semaphore &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		SemaphoreImpl *m_pSemaphoreImpl;	/**< Pointer to the system specific implementation (assumed to be never a null pointer!) */
		uint32         m_nValue;			/**< Current value of the semaphore */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_SEMAPHORE_H__
