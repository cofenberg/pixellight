/*********************************************************\
 *  File: SimpleMapKeyIterator.inl                       *
 *      Simple map iterator template implementation
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
#include "PLCore/Container/SimpleMap.h"


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
template <class KeyType, class ValueType, class Comparer>
SimpleMapKeyIterator<KeyType, ValueType, Comparer>::SimpleMapKeyIterator(const SimpleMap<KeyType, ValueType, Comparer> &mapOwner, uint32 nIndex) :
	m_pmapOwner(&mapOwner),
	m_pIterator(new Iterator< typename SimpleMap<KeyType, ValueType, Comparer>::Element >(m_pmapOwner->m_lstElements.GetIterator(nIndex)))
{
}

/**
*  @brief
*    Constructor
*/
template <class KeyType, class ValueType, class Comparer>
SimpleMapKeyIterator<KeyType, ValueType, Comparer>::SimpleMapKeyIterator(const SimpleMap<KeyType, ValueType, Comparer> &mapOwner) :
	m_pmapOwner(&mapOwner),
	m_pIterator(new Iterator< typename SimpleMap<KeyType, ValueType, Comparer>::Element >(m_pmapOwner->m_lstElements.GetEndIterator()))
{
}

/**
*  @brief
*    Copy constructor
*/
template <class KeyType, class ValueType, class Comparer>
SimpleMapKeyIterator<KeyType, ValueType, Comparer>::SimpleMapKeyIterator(const SimpleMapKeyIterator<KeyType, ValueType, Comparer> &cSource) :
	m_pmapOwner(cSource.m_pmapOwner),
	m_pIterator(new Iterator< typename SimpleMap<KeyType, ValueType, Comparer>::Element >(*cSource.m_pIterator))
{
}

/**
*  @brief
*    Destructor
*/
template <class KeyType, class ValueType, class Comparer>
SimpleMapKeyIterator<KeyType, ValueType, Comparer>::~SimpleMapKeyIterator()
{
	// Destroy the internal iterator
	delete m_pIterator;
}


//[-------------------------------------------------------]
//[ Private virtual IteratorImpl functions                ]
//[-------------------------------------------------------]
template <class KeyType, class ValueType, class Comparer>
IteratorImpl<KeyType> *SimpleMapKeyIterator<KeyType, ValueType, Comparer>::Clone() const
{
	return new SimpleMapKeyIterator<KeyType, ValueType, Comparer>(*this);
}

template <class KeyType, class ValueType, class Comparer>
bool SimpleMapKeyIterator<KeyType, ValueType, Comparer>::HasNext() const
{
	return m_pIterator->HasNext();
}

template <class KeyType, class ValueType, class Comparer>
KeyType &SimpleMapKeyIterator<KeyType, ValueType, Comparer>::Next()
{
	typename SimpleMap<KeyType, ValueType, Comparer>::Element &cNext = m_pIterator->Next();
	return (&cNext != &FastPool<typename SimpleMap<KeyType, ValueType, Comparer>::Element>::Null) ? cNext.Key : SimpleMap<KeyType, ValueType, Comparer>::NullKey;
}

template <class KeyType, class ValueType, class Comparer>
bool SimpleMapKeyIterator<KeyType, ValueType, Comparer>::HasPrevious() const
{
	return m_pIterator->HasPrevious();
}

template <class KeyType, class ValueType, class Comparer>
KeyType &SimpleMapKeyIterator<KeyType, ValueType, Comparer>::Previous()
{
	typename SimpleMap<KeyType, ValueType, Comparer>::Element &cPrevious = m_pIterator->Previous();
	return (&cPrevious != &FastPool<typename SimpleMap<KeyType, ValueType, Comparer>::Element>::Null) ? cPrevious.Key  : SimpleMap<KeyType, ValueType, Comparer>::NullKey;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
