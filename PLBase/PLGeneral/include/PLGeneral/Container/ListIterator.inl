/*********************************************************\
 *  File: ListIterator.inl                               *
 *      List iterator template implementation
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
#include "PLGeneral/Container/List.h"


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
ListIterator<ValueType>::ListIterator(const List<ValueType> &lstList, uint32 nIndex) :
	m_plstList(&lstList)
{
	// Start at first element?
	if (!nIndex) {
		m_pNextElement     = m_plstList->m_pFirstElement;
		m_pPreviousElement = nullptr;

	// Start at last element?
	} else if (nIndex >= m_plstList->m_nNumOfElements-1) {
		m_pNextElement     = nullptr;
		m_pPreviousElement = m_plstList->m_pLastElement;

	// Ok, we start somewhere between the start/end element... which search direction?
	} else {
		if (nIndex < m_plstList->m_nNumOfElements/2) {
			// Start with the first element
			m_pPreviousElement = m_plstList->m_pFirstElement;
			m_pNextElement     = m_pPreviousElement->pNextElement;
			uint32 nCurrent = 1;
			while (m_pNextElement && nCurrent != nIndex) {
				m_pPreviousElement = m_pNextElement;
				m_pNextElement     = m_pNextElement->pNextElement;
				nCurrent++;
			}
		} else {
			// Start with the last element
			m_pNextElement     = m_plstList->m_pLastElement;
			m_pPreviousElement = m_pNextElement->pPreviousElement;
			uint32 nCurrent = m_plstList->m_nNumOfElements-2;
			while (m_pPreviousElement && nCurrent != nIndex) {
				m_pNextElement     = m_pPreviousElement;
				m_pPreviousElement = m_pPreviousElement->pPreviousElement;
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
ListIterator<ValueType>::ListIterator(const List<ValueType> &lstList) :
	m_plstList(&lstList),
	m_pNextElement(nullptr),
	m_pPreviousElement(lstList.m_pLastElement)
{
}

/**
*  @brief
*    Copy constructor
*/
template <class ValueType>
ListIterator<ValueType>::ListIterator(const ListIterator<ValueType> &cSource) :
	m_plstList(cSource.m_plstList),
	m_pNextElement(cSource.m_pNextElement),
	m_pPreviousElement(cSource.m_pPreviousElement)
{
}

/**
*  @brief
*    Destructor
*/
template <class ValueType>
ListIterator<ValueType>::~ListIterator()
{
}


//[-------------------------------------------------------]
//[ Private virtual IteratorImpl functions                ]
//[-------------------------------------------------------]
template <class ValueType>
IteratorImpl<ValueType> *ListIterator<ValueType>::Clone() const
{
	return new ListIterator<ValueType>(*this);
}

template <class ValueType>
bool ListIterator<ValueType>::HasNext() const
{
	return (m_pNextElement != nullptr);
}

template <class ValueType>
ValueType &ListIterator<ValueType>::Next()
{
	if (!m_pNextElement)
		return List<ValueType>::Null; // There's no next element
	m_pPreviousElement = m_pNextElement;
	m_pNextElement     = m_pNextElement->pNextElement;
	return m_pPreviousElement->Data;
}

template <class ValueType>
bool ListIterator<ValueType>::HasPrevious() const
{
	return (m_pPreviousElement != nullptr);
}

template <class ValueType>
ValueType &ListIterator<ValueType>::Previous()
{
	if (!m_pPreviousElement)
		return List<ValueType>::Null; // There's no previous element
	m_pNextElement     = m_pPreviousElement;
	m_pPreviousElement = m_pPreviousElement->pPreviousElement;
	return m_pNextElement->Data;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
