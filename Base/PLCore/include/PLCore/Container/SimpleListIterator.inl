/*********************************************************\
 *  File: SimpleListIterator.inl                         *
 *      Simple list iterator template implementation
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
#include "PLCore/Container/SimpleList.h"


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
SimpleListIterator<ValueType>::SimpleListIterator(const SimpleList<ValueType> &lstSimpleList, uint32 nIndex) :
	m_plstSimpleList(&lstSimpleList)
{
	// Start at first element?
	if (!nIndex) {
		m_pNextElement     = m_plstSimpleList->pFirstElement;
		m_pPreviousElement = nullptr;

	// Ok, we start somewhere between the start/end element
	} else {
		// Start with the first element
		m_pPreviousElement = m_plstSimpleList->pFirstElement;
		m_pNextElement     = m_pPreviousElement->pNextElement;
		uint32 nCurrent = 1;
		while (m_pNextElement && nCurrent != nIndex) {
			m_pPreviousElement = m_pNextElement;
			m_pNextElement     = m_pNextElement->pNextElement;
			nCurrent++;
		}
	}
}

/**
*  @brief
*    Constructor
*/
template <class ValueType>
SimpleListIterator<ValueType>::SimpleListIterator(const SimpleList<ValueType> &lstSimpleList) :
	m_plstSimpleList(&lstSimpleList),
	m_pNextElement(nullptr),
	m_pPreviousElement(nullptr)
{
	// Start with the first element
	typename SimpleList<ValueType>::ListElement *pElement = lstSimpleList.pFirstElement;
	while (pElement) {
		// Next, please
		m_pPreviousElement = pElement;
		pElement		   = pElement->pNextElement;
	}
}

/**
*  @brief
*    Copy constructor
*/
template <class ValueType>
SimpleListIterator<ValueType>::SimpleListIterator(const SimpleListIterator<ValueType> &cSource) :
	m_plstSimpleList(cSource.m_plstSimpleList),
	m_pNextElement(cSource.m_pNextElement),
	m_pPreviousElement(cSource.m_pPreviousElement)
{
}

/**
*  @brief
*    Destructor
*/
template <class ValueType>
SimpleListIterator<ValueType>::~SimpleListIterator()
{
}


//[-------------------------------------------------------]
//[ Private virtual IteratorImpl functions                ]
//[-------------------------------------------------------]
template <class ValueType>
IteratorImpl<ValueType> *SimpleListIterator<ValueType>::Clone() const
{
	return new SimpleListIterator<ValueType>(*this);
}

template <class ValueType>
bool SimpleListIterator<ValueType>::HasNext() const
{
	return (m_pNextElement != nullptr);
}

template <class ValueType>
ValueType &SimpleListIterator<ValueType>::Next()
{
	if (!m_pNextElement)
		return SimpleList<ValueType>::Null; // There's no next element
	m_pPreviousElement = m_pNextElement;
	m_pNextElement     = m_pNextElement->pNextElement;
	return m_pPreviousElement->Data;
}

template <class ValueType>
bool SimpleListIterator<ValueType>::HasPrevious() const
{
	return (m_pPreviousElement != nullptr);
}

template <class ValueType>
ValueType &SimpleListIterator<ValueType>::Previous()
{
	if (!m_pPreviousElement)
		return SimpleList<ValueType>::Null; // There's no previous element

	// Set next element
	m_pNextElement = m_pPreviousElement;

	// Start with the first element
	typename SimpleList<ValueType>::ListElement *pElement = m_plstSimpleList->pFirstElement;
	m_pPreviousElement = nullptr;
	while (pElement && m_pNextElement != pElement) {
		// Next, please
		m_pPreviousElement = pElement;
		pElement		   = pElement->pNextElement;
	}

	// Return data
	return m_pNextElement->Data;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
