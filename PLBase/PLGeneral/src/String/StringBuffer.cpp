/*********************************************************\
 *  File: StringBuffer.cpp                               *
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
#include "PLGeneral/String/StringBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Protected static data                                 ]
//[-------------------------------------------------------]
StringBufferManager StringBuffer::Manager;


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
StringBuffer::StringBuffer(uint32 nLength, uint32 nMaxLength, uint8 nType) :
	m_nRefCount(0),
#ifdef _DEBUG
	m_nType(nType),
#endif
	m_nLength(nLength),
	m_nMaxLength(nMaxLength)
{
}

/**
*  @brief
*    Destructor
*/
StringBuffer::~StringBuffer()
{
}

/**
*  @brief
*    Returns the length of the string buffer (excluding the terminating zero)
*/
uint32 StringBuffer::GetLength() const
{
	return m_nLength;
}

/**
*  @brief
*    Increases the reference count
*/
uint32 StringBuffer::AddReference()
{
	// Increment reference count
	m_nRefCount++;

	// Return current reference count
	return m_nRefCount;
}

/**
*  @brief
*    Decreases the reference count
*/
uint32 StringBuffer::Release()
{
	// Decrement reference count
	if (m_nRefCount > 1) {
		m_nRefCount--;

		// Return current reference count
		return m_nRefCount;

	// Destroy object when no references are left
	} else {
		delete this;

		// This object is no longer
		return 0;
	}
}

/**
*  @brief
*    Gets the current reference count
*/
uint32 StringBuffer::GetRefCount() const
{
	// Return current reference count
	return m_nRefCount;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
