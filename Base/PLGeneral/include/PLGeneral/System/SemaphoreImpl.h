/*********************************************************\
 *  File: SemaphoreImpl.h                                *
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


#ifndef __PLGENERAL_SEMAPHORE_IMPL_H__
#define __PLGENERAL_SEMAPHORE_IMPL_H__
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
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract base class for platform specific 'Semaphore' implementations
*
*  @note
*    - Implementation of the bridge design pattern, this class is the implementor of the 'Semaphore' abstraction
*/
class SemaphoreImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Semaphore;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		SemaphoreImpl();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SemaphoreImpl();


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Locks the semaphore
		*
		*  @return
		*    'true' if successful, 'false' on error
		*/
		virtual bool Lock() = 0;

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
		*    - 'nTimeout = 0' means no timeout at all
		*/
		virtual bool TryLock(uint64 nTimeout) = 0;

		/**
		*  @brief
		*    Unlocks the semaphore
		*
		*  @return
		*    'true' if successful, 'false' on error
		*/
		virtual bool Unlock() = 0;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_SEMAPHORE_IMPL_H__
