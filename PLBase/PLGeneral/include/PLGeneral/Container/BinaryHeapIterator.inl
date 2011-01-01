/*********************************************************\
 *  File: BinaryHeapIterator.inl                         *
 *      Binary heap iterator template implementation
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
#include "PLGeneral/Container/BinaryHeap.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
template <class KeyType, class ValueType, class Comparer>
BinaryHeapIterator<KeyType, ValueType, Comparer>::BinaryHeapIterator(const BinaryHeap<KeyType, ValueType, Comparer> &cHeapOwner, uint32 nIndex) :
	m_pHeapOwner(&cHeapOwner),
	m_nNextID((nIndex > m_pHeapOwner->GetNumOfElements()-1) ? m_pHeapOwner->GetNumOfElements()-1 : nIndex)
{
}

/**
*  @brief
*    Constructor
*/
template <class KeyType, class ValueType, class Comparer>
BinaryHeapIterator<KeyType, ValueType, Comparer>::BinaryHeapIterator(const BinaryHeap<KeyType, ValueType, Comparer> &cHeapOwner) :
	m_pHeapOwner(&cHeapOwner),
	m_nNextID(cHeapOwner.GetNumOfElements())
{
}

/**
*  @brief
*    Copy constructor
*/
template <class KeyType, class ValueType, class Comparer>
BinaryHeapIterator<KeyType, ValueType, Comparer>::BinaryHeapIterator(const BinaryHeapIterator<KeyType, ValueType, Comparer> &cSource) :
	m_pHeapOwner(cSource.m_pHeapOwner),
	m_nNextID(cSource.m_nNextID)
{
}

/**
*  @brief
*    Destructor
*/
template <class KeyType, class ValueType, class Comparer>
BinaryHeapIterator<KeyType, ValueType, Comparer>::~BinaryHeapIterator()
{
}


//[-------------------------------------------------------]
//[ Private virtual IteratorImpl functions                ]
//[-------------------------------------------------------]
template <class KeyType, class ValueType, class Comparer>
IteratorImpl<ValueType> *BinaryHeapIterator<KeyType, ValueType, Comparer>::Clone() const
{
	return new BinaryHeapIterator<KeyType, ValueType, Comparer>(*this);
}

template <class KeyType, class ValueType, class Comparer>
bool BinaryHeapIterator<KeyType, ValueType, Comparer>::HasNext() const
{
	return (m_nNextID < m_pHeapOwner->GetNumOfElements());
}

template <class KeyType, class ValueType, class Comparer>
ValueType &BinaryHeapIterator<KeyType, ValueType, Comparer>::Next()
{
	return (m_nNextID < m_pHeapOwner->GetNumOfElements()) ? m_pHeapOwner->m_pData[m_nNextID++].Value : BinaryHeap<KeyType, ValueType, Comparer>::Null;
}

template <class KeyType, class ValueType, class Comparer>
bool BinaryHeapIterator<KeyType, ValueType, Comparer>::HasPrevious() const
{
	return (m_nNextID != 0);
}

template <class KeyType, class ValueType, class Comparer>
ValueType &BinaryHeapIterator<KeyType, ValueType, Comparer>::Previous()
{
	return m_nNextID ? m_pHeapOwner->m_pData[--m_nNextID].Value : BinaryHeap<KeyType, ValueType, Comparer>::Null;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
