/*********************************************************\
 *  File: MutexGuard.h                                   *
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


#ifndef __PLCORE_MUTEXGUARD_H__
#define __PLCORE_MUTEXGUARD_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/PLCore.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Mutex;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mutex guard class ("Scoped Locking"-idiom, also known as "synchronized block")
*
*  @remarks
*    When using a mutex in more complex situations there's the risk that one forgets the unlock a locked mutex. To avoid this
*    situation it's a good idea to use this mutex guard on the runtime stack (the runtime stack is your friend!) in order to
*    lock the mutex and automatically unlock it as soon as the critical scope is left.
*/
class MutexGuard {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cMutex
		*    Mutex to use, just referenced, must stay valid as long as this mutex guard exists!
		*
		*  @note
		*    - Blocking if the mutex is already locked
		*    - Use the constructor with a timeout to avoid potential deadlocks
		*/
		inline MutexGuard(Mutex &cMutex);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cMutex
		*    Mutex to use, just referenced, must stay valid as long as this mutex guard exists!
		*  @param[in] nTimeout
		*    Timeout in milliseconds
		*
		*  @note
		*    - 'nTimeout = 0' means: Return immediately if the mutex is already locked
		*/
		inline MutexGuard(Mutex &cMutex, uint64 nTimeout);

		/**
		*  @brief
		*    Destructor
		*/
		inline ~MutexGuard();

		/**
		*  @brief
		*    Returns whether the used mutex was locked successfully
		*
		*  @return
		*    'true' if the used mutex was locked successfully, else 'false'
		*/
		inline bool IsLocked() const;

		/**
		*  @brief
		*    Returns the used mutex
		*
		*  @return
		*    The used mutex
		*/
		inline Mutex &GetMutex() const;


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
		inline MutexGuard(const MutexGuard &cSource);

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
		inline MutexGuard &operator =(const MutexGuard &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Mutex *m_pMutex;	/**< Pointer to the used mutex, always valid! */
		bool   m_bLocked;	/**< 'true' if the used mutex was locked successfully, else 'false' */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/System/MutexGuard.inl"


#endif // __PLCORE_MUTEXGUARD_H__
