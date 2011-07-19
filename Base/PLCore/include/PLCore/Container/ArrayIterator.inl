/*********************************************************\
 *  File: ArrayIterator.inl                              *
 *      Array iterator template implementation
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
#include "PLCore/Container/Array.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
template <class ValueType>
ArrayIterator<ValueType>::ArrayIterator(const Container<ValueType> &lstContainer, uint32 nIndex) :
	m_plstContainer(&lstContainer),
	m_nNextID((nIndex > lstContainer.GetNumOfElements()-1) ? lstContainer.GetNumOfElements()-1 : nIndex)
{
}

/**
*  @brief
*    Constructor
*/
template <class ValueType>
ArrayIterator<ValueType>::ArrayIterator(const Container<ValueType> &lstContainer) :
	m_plstContainer(&lstContainer),
	m_nNextID(lstContainer.GetNumOfElements())
{
}

/**
*  @brief
*    Copy constructor
*/
template <class ValueType>
ArrayIterator<ValueType>::ArrayIterator(const ArrayIterator<ValueType> &cSource) :
	m_plstContainer(cSource.m_plstContainer),
	m_nNextID(cSource.m_nNextID)
{
}

/**
*  @brief
*    Destructor
*/
template <class ValueType>
ArrayIterator<ValueType>::~ArrayIterator()
{
}


//[-------------------------------------------------------]
//[ Private virtual IteratorImpl functions                ]
//[-------------------------------------------------------]
template <class ValueType>
IteratorImpl<ValueType> *ArrayIterator<ValueType>::Clone() const
{
	return new ArrayIterator<ValueType>(*this);
}

template <class ValueType>
bool ArrayIterator<ValueType>::HasNext() const
{
	return (m_nNextID < m_plstContainer->GetNumOfElements());
}

template <class ValueType>
ValueType &ArrayIterator<ValueType>::Next()
{
	return (m_nNextID < m_plstContainer->GetNumOfElements()) ? m_plstContainer->Get(m_nNextID++) : Container<ValueType>::Null;
}

template <class ValueType>
bool ArrayIterator<ValueType>::HasPrevious() const
{
	return (m_nNextID != 0);
}

template <class ValueType>
ValueType &ArrayIterator<ValueType>::Previous()
{
	return m_nNextID ? m_plstContainer->Get(--m_nNextID) : Container<ValueType>::Null;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
