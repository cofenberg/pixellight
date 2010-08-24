/*********************************************************\
 *  File: SimpleMapIterator.inl                          *
 *      Simple map iterator template implementation
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLGeneral/Container/SimpleMap.h"


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
SimpleMapIterator<KeyType, ValueType, Comparer>::SimpleMapIterator(const SimpleMap<KeyType, ValueType, Comparer> &mapOwner, uint32 nIndex) :
	m_pmapOwner(&mapOwner),
	m_pIterator(new Iterator< typename SimpleMap<KeyType, ValueType, Comparer>::Element >(m_pmapOwner->m_lstElements.GetIterator(nIndex)))
{
}

/**
*  @brief
*    Constructor
*/
template <class KeyType, class ValueType, class Comparer>
SimpleMapIterator<KeyType, ValueType, Comparer>::SimpleMapIterator(const SimpleMap<KeyType, ValueType, Comparer> &mapOwner) :
	m_pmapOwner(&mapOwner),
	m_pIterator(new Iterator< typename SimpleMap<KeyType, ValueType, Comparer>::Element >(m_pmapOwner->m_lstElements.GetEndIterator()))
{
}

/**
*  @brief
*    Copy constructor
*/
template <class KeyType, class ValueType, class Comparer>
SimpleMapIterator<KeyType, ValueType, Comparer>::SimpleMapIterator(const SimpleMapIterator<KeyType, ValueType, Comparer> &cSource) :
	m_pmapOwner(cSource.m_pmapOwner),
	m_pIterator(new Iterator< typename SimpleMap<KeyType, ValueType, Comparer>::Element >(*cSource.m_pIterator))
{
}

/**
*  @brief
*    Destructor
*/
template <class KeyType, class ValueType, class Comparer>
SimpleMapIterator<KeyType, ValueType, Comparer>::~SimpleMapIterator()
{
	// Destroy the internal iterator
	delete m_pIterator;
}


//[-------------------------------------------------------]
//[ Private virtual IteratorImpl functions                ]
//[-------------------------------------------------------]
template <class KeyType, class ValueType, class Comparer>
IteratorImpl<ValueType> *SimpleMapIterator<KeyType, ValueType, Comparer>::Clone() const
{
	return new SimpleMapIterator<KeyType, ValueType, Comparer>(*this);
}

template <class KeyType, class ValueType, class Comparer>
bool SimpleMapIterator<KeyType, ValueType, Comparer>::HasNext() const
{
	return m_pIterator->HasNext();
}

template <class KeyType, class ValueType, class Comparer>
ValueType &SimpleMapIterator<KeyType, ValueType, Comparer>::Next()
{
	typename SimpleMap<KeyType, ValueType, Comparer>::Element &cNext = m_pIterator->Next();
	return (&cNext != &FastPool<typename SimpleMap<KeyType, ValueType, Comparer>::Element>::Null) ? cNext.Value : SimpleMap<KeyType, ValueType, Comparer>::Null;
}

template <class KeyType, class ValueType, class Comparer>
bool SimpleMapIterator<KeyType, ValueType, Comparer>::HasPrevious() const
{
	return m_pIterator->HasPrevious();
}

template <class KeyType, class ValueType, class Comparer>
ValueType &SimpleMapIterator<KeyType, ValueType, Comparer>::Previous()
{
	typename SimpleMap<KeyType, ValueType, Comparer>::Element &cPrevious = m_pIterator->Previous();
	return (&cPrevious != &FastPool<typename SimpleMap<KeyType, ValueType, Comparer>::Element>::Null) ? cPrevious.Value : SimpleMap<KeyType, ValueType, Comparer>::Null;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
