/*********************************************************\
 *  File: SemaphoreLinux.h                               *
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


#ifndef __PLCORE_SEMAPHORE_LINUX_H__
#define __PLCORE_SEMAPHORE_LINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/System/SemaphoreImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linux 'Semaphore' implementation
*/
class SemaphoreLinux : public SemaphoreImpl {


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
		SemaphoreLinux(uint32 nValue, uint32 nMaxValue);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SemaphoreLinux();


	//[-------------------------------------------------------]
	//[ Private virtual SemaphoreImpl functions               ]
	//[-------------------------------------------------------]
	private:
		virtual bool Lock() override;
		virtual bool TryLock(uint64 nTimeout) override;
		virtual bool Unlock() override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		int    m_hSemaphore;	/**< System semaphore handle */
		uint32 m_nMaxValue;		/**< Maximum value of the semaphore */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_SEMAPHORE_LINUX_H__
