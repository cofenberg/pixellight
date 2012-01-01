/*********************************************************\
 *  File: Semaphore.cpp                                  *
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
#if defined(WIN32)
	#include "PLCore/System/SemaphoreWindows.h"
#elif defined(LINUX)
	#include "PLCore/System/SemaphoreLinux.h"
#endif
#include "PLCore/System/Semaphore.h"


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
Semaphore::Semaphore(uint32 nValue, uint32 nMaxValue) :
	m_pSemaphoreImpl(nullptr),
	m_nValue(0)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pSemaphoreImpl = new SemaphoreWindows(nValue, nMaxValue);
	#elif defined(LINUX)
		// Create Linux implementation
		m_pSemaphoreImpl = new SemaphoreLinux(nValue, nMaxValue);
	#else
		// Unknown system
		#error "Unsupported platform"
	#endif
}

/**
*  @brief
*    Destructor
*/
Semaphore::~Semaphore()
{
	// Destroy system specific implementation
	if (m_pSemaphoreImpl)
		delete m_pSemaphoreImpl;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Semaphore::Semaphore(const Semaphore &cSource) :
	m_pSemaphoreImpl(nullptr),
	m_nValue(0)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Semaphore &Semaphore::operator =(const Semaphore &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
