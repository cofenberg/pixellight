/*********************************************************\
 *  File: RefCount.inl                                   *
 *      Reference counter template implementation
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
template <class AType>
RefCount<AType>::RefCount() :
	m_nRefCount(0)
{
}

/**
*  @brief
*    Destructor
*/
template <class AType>
RefCount<AType>::~RefCount()
{
}

/**
*  @brief
*    Get a pointer to the object
*/
template <class AType>
AType *RefCount<AType>::GetPointer() const
{
	return (AType*)this;
}

/**
*  @brief
*    Increases the reference count
*/
template <class AType>
uint32 RefCount<AType>::AddReference()
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
template <class AType>
uint32 RefCount<AType>::Release()
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
template <class AType>
uint32 RefCount<AType>::GetRefCount() const
{
	// Return current reference count
	return m_nRefCount;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
