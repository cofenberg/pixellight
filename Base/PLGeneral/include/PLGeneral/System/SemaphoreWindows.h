/*********************************************************\
 *  File: SemaphoreWindows.h                             *
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


#ifndef __PLGENERAL_SEMAPHORE_WINDOWS_H__
#define __PLGENERAL_SEMAPHORE_WINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/PLGeneralWindowsIncludes.h"
#include "PLGeneral/System/SemaphoreImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Windows 'Semaphore' implementation
*/
class SemaphoreWindows : public SemaphoreImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Semaphore;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nValue
		*    Initial value of the semaphore
		*  @param[in] nMaxValue
		*    Maximum value of the semaphore
		*/
		SemaphoreWindows(uint32 nValue, uint32 nMaxValue);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SemaphoreWindows();


	//[-------------------------------------------------------]
	//[ Private virtual SemaphoreImpl functions               ]
	//[-------------------------------------------------------]
	private:
		virtual bool Lock();
		virtual bool TryLock(uint64 nTimeout);
		virtual bool Unlock();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		HANDLE m_hSemaphore;	/**< System semaphore handle */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_SEMAPHORE_WINDOWS_H__
