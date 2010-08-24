/*********************************************************\
 *  File: Mutex.h                                        *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLGENERAL_MUTEX_H__
#define __PLGENERAL_MUTEX_H__
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
class MutexImpl;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mutex (Mutual Exclusion, binary semaphore) class
*/
class Mutex {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API Mutex();

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API ~Mutex();

		/**
		*  @brief
		*    Locks the mutex
		*
		*  @return
		*    'true' if successful, 'false' on error
		*
		*  @note
		*    - Blocking if already locked
		*    - Use the lock method with a timeout to avoid potential deadlocks
		*/
		PLGENERAL_API bool Lock();

		/**
		*  @brief
		*    Locks the mutex, but only wait until timeout
		*
		*  @param[in] nTimeout
		*    Timeout in milliseconds
		*
		*  @return
		*    'true' if successful, 'false' on error
		*
		*  @note
		*    - 'nTimeout = 0' means: Return immediately if already locked
		*
		*  @see
		*    - Lock()
		*/
		PLGENERAL_API bool Lock(uint32 nTimeout);

		/**
		*  @brief
		*    Unlocks the mutex
		*
		*  @return
		*    'true' if successful, 'false' on error
		*/
		PLGENERAL_API bool Unlock();


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
		Mutex(const Mutex &cSource);

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
		Mutex &operator =(const Mutex &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		MutexImpl *m_pMutexImpl;	/**< Pointer to the system specific implementation (assumed to be never NULL!) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_MUTEX_H__
