/*********************************************************\
 *  File: Buffer.cpp                                     *
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
#include "PLRenderer/Renderer/Buffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
Buffer::~Buffer()
{
}

/**
*  @brief
*    Returns the number of buffer elements
*/
uint32 Buffer::GetNumOfElements() const
{
	return m_nElements;
}

/**
*  @brief
*    Returns the buffer size
*/
uint32 Buffer::GetSize() const
{
	return m_nSize;
}

/**
*  @brief
*    Returns the usage flag
*/
Usage::Enum Buffer::GetUsage() const
{
	return m_nUsage;
}

/**
*  @brief
*    Returns whether the buffer is managed or not
*/
bool Buffer::IsManaged() const
{
	return m_bManaged;
}

/**
*  @brief
*    Returns the lock count
*/
uint16 Buffer::GetLockCount() const
{
	return m_nLockCount;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Buffer::Buffer(Renderer &cRenderer, EType nType) : Resource(cRenderer, nType),
	m_nElements(0),
	m_nSize(0),
	m_nUsage(Usage::Unknown),
	m_bManaged(false),
	m_nLockCount(0),
	m_nLockStartTime(0)
{
}

/**
*  @brief
*    Forces immediately vertex buffer unlock
*/
bool Buffer::ForceUnlock()
{
	// Is the buffer locked?
	if (!m_nLockCount)
		return false; // Error!

	// Force unlock now!
	m_nLockCount = 1;
	return Unlock();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Buffer::Buffer(const Buffer &cSource) : Resource(cSource.GetRenderer(), cSource.GetType()),
	m_nElements(0),
	m_nSize(0),
	m_nUsage(Usage::Unknown),
	m_bManaged(false),
	m_nLockCount(0),
	m_nLockStartTime(0)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Buffer &Buffer::operator =(const Buffer &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
