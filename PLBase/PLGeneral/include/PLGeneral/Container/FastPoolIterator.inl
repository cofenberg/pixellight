/*********************************************************\
 *  File: FastPoolIterator.inl                           *
 *      Fast pool iterator template implementation
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
#include "PLGeneral/Container/FastPool.h"


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
template <class ValueType>
FastPoolIterator<ValueType>::FastPoolIterator(const FastPool<ValueType> &lstPool, uint32 nIndex) :
	m_plstPool(&lstPool)
{
	// Start at first element?
	if (!nIndex) {
		m_pNextElement     = m_plstPool->m_pFirstElement;
		m_pPreviousElement = NULL;

	// Start at last element?
	} else if (nIndex >= m_plstPool->m_nNumOfElements-1) {
		m_pNextElement     = NULL;
		m_pPreviousElement = m_plstPool->m_pLastElement;

	// Ok, we start somewhere between the start/end element... which search direction?
	} else {
		if (nIndex < m_plstPool->m_nNumOfElements/2) {
			// Start with the first element
			m_pPreviousElement = m_plstPool->m_pFirstElement;
			m_pNextElement     = m_pPreviousElement->m_pNextElement;
			uint32 nCurrent = 1;
			while (m_pNextElement && nCurrent != nIndex) {
				m_pPreviousElement = m_pNextElement;
				m_pNextElement     = m_pNextElement->m_pNextElement;
				nCurrent++;
			}
		} else {
			// Start with the last element
			m_pNextElement     = m_plstPool->m_pLastElement;
			m_pPreviousElement = m_pNextElement->m_pPreviousElement;
			uint32 nCurrent = m_plstPool->m_nNumOfElements-2;
			while (m_pPreviousElement && nCurrent != nIndex) {
				m_pNextElement     = m_pPreviousElement;
				m_pPreviousElement = m_pPreviousElement->m_pPreviousElement;
				nCurrent--;
			}
		}
	}
}

/**
*  @brief
*    Constructor
*/
template <class ValueType>
FastPoolIterator<ValueType>::FastPoolIterator(const FastPool<ValueType> &lstPool) :
	m_plstPool(&lstPool),
	m_pNextElement(NULL),
	m_pPreviousElement(lstPool.m_pLastElement)
{
}

/**
*  @brief
*    Copy constructor
*/
template <class ValueType>
FastPoolIterator<ValueType>::FastPoolIterator(const FastPoolIterator<ValueType> &lstSource) :
	m_plstPool(lstSource.m_plstPool),
	m_pNextElement(lstSource.m_pNextElement),
	m_pPreviousElement(lstSource.m_pPreviousElement)
{
}

/**
*  @brief
*    Destructor
*/
template <class ValueType>
FastPoolIterator<ValueType>::~FastPoolIterator()
{
}


//[-------------------------------------------------------]
//[ Private virtual IteratorImpl functions                ]
//[-------------------------------------------------------]
template <class ValueType>
IteratorImpl<ValueType> *FastPoolIterator<ValueType>::Clone() const
{
	return new FastPoolIterator<ValueType>(*this);
}

template <class ValueType>
bool FastPoolIterator<ValueType>::HasNext() const
{
	return (m_pNextElement != NULL);
}

template <class ValueType>
ValueType &FastPoolIterator<ValueType>::Next()
{
	if (!m_pNextElement)
		return FastPool<ValueType>::Null; // There's no next element
	m_pPreviousElement = m_pNextElement;
	m_pNextElement     = m_pNextElement->m_pNextElement;
	return *m_pPreviousElement;
}

template <class ValueType>
bool FastPoolIterator<ValueType>::HasPrevious() const
{
	return (m_pPreviousElement != NULL);
}

template <class ValueType>
ValueType &FastPoolIterator<ValueType>::Previous()
{
	if (!m_pPreviousElement)
		return FastPool<ValueType>::Null; // There's no previous element
	m_pNextElement     = m_pPreviousElement;
	m_pPreviousElement = m_pPreviousElement->m_pPreviousElement;
	return *m_pNextElement;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
