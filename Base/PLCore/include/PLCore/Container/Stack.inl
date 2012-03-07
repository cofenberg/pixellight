/*********************************************************\
 *  File: Stack.inl                                      *
 *      Stack template implementation
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLCore/Container/StackIterator.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public static variables                               ]
//[-------------------------------------------------------]
template <class ValueType> ValueType Stack<ValueType>::Null;


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
template <class ValueType> ValueType Stack<ValueType>::temp;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
template <class ValueType>
Stack<ValueType>::Stack() :
	m_nNumOfElements(0),
	m_pTop(nullptr),
	m_pBottom(nullptr)
{
}

/**
*  @brief
*    Copy constructor
*/
template <class ValueType>
Stack<ValueType>::Stack(const Stack<ValueType> &cSource) :
	m_nNumOfElements(0),
	m_pTop(nullptr),
	m_pBottom(nullptr)
{
	// Copy stack
	*this = cSource;
}

/**
*  @brief
*    Destructor
*/
template <class ValueType>
Stack<ValueType>::~Stack()
{
	// Clean up
	Clear();
}

/**
*  @brief
*    Push an element onto the stack
*/
template <class ValueType>
bool Stack<ValueType>::Push(const ValueType &Element)
{
	// Create new element
	StackElement *pElement = new StackElement;
	pElement->Data = Element;

	// Is this the first element?
	if (!m_pTop)
		m_pBottom = pElement;

	// Push onto stack
	pElement->pNextElement = m_pTop;
	m_pTop = pElement;
	m_nNumOfElements++;

	// Done
	return true;
}

/**
*  @brief
*    Pops the top element from the stack
*/
template <class ValueType>
bool Stack<ValueType>::Pop(ValueType *pElement)
{
	// Is there a top element?
	if (!m_pTop)
		return false; // Error!

	// Get top element
	if (pElement)
		*pElement = m_pTop->Data;

	// Pop element
	StackElement *pTopElement = m_pTop;
	m_pTop = m_pTop->pNextElement;
	if (!m_pTop)
		m_pBottom = nullptr;
	delete pTopElement;
	m_nNumOfElements--;

	// Done
	return true;
}

/**
*  @brief
*    Get the top element without removing it
*/
template <class ValueType>
ValueType Stack<ValueType>::Top() const
{
	// On error return temp object...
	return m_pTop ? m_pTop->Data : temp;
}

/**
*  @brief
*    Get the bottom element without removing it
*/
template <class ValueType>
ValueType Stack<ValueType>::Bottom() const
{
	// On error return temp object...
	return m_pBottom ? m_pBottom->Data : temp;
}

/**
*  @brief
*    Returns the number of element on the stack
*/
template <class ValueType>
uint32 Stack<ValueType>::GetNumOfElements() const
{
	return m_nNumOfElements;
}

/**
*  @brief
*    Copies the data from another stack
*/
template <class ValueType>
Stack<ValueType> &Stack<ValueType>::operator =(const Stack<ValueType> &cSource)
{
	// Clear stack
	Clear();

	// Push all elements from the other stack
	StackElement *pElement = cSource.m_pTop;
	while (pElement) {
		PushBack(pElement->Data);
		pElement = pElement->pNextElement;
	}

	// Return this instance
	return *this;
}

/**
*  @brief
*    Clears the whole stack
*/
template <class ValueType>
void Stack<ValueType>::Clear()
{
	// Remove all elements
	while (m_pTop)
		Pop();
}

/**
*  @brief
*    Push an element to the back of the stack
*/
template <class ValueType>
bool Stack<ValueType>::PushBack(const ValueType &Element)
{
	// Empty stack?
	if (m_pBottom) {
		// No, stack isn't empty
		StackElement *pElement = new StackElement;
		pElement->Data = Element;
		pElement->pNextElement = nullptr;
		m_pBottom->pNextElement = pElement;
		m_pBottom = pElement;
		m_nNumOfElements++;

		// Done
		return true;
	} else {
		// Yes stack was empty, so push-back == push
		return Push(Element);
	}
}


//[-------------------------------------------------------]
//[ Public Iterable functions                             ]
//[-------------------------------------------------------]
template <class ValueType>
Iterator<ValueType> Stack<ValueType>::GetIterator(uint32 nIndex) const
{
	Iterator<ValueType> cIterator(*(new StackIterator<ValueType>(*this, nIndex)));
	return cIterator;
}

template <class ValueType>
ConstIterator<ValueType> Stack<ValueType>::GetConstIterator(uint32 nIndex) const
{
	ConstIterator<ValueType> cIterator(*(new StackIterator<ValueType>(*this, nIndex)));
	return cIterator;
}

template <class ValueType>
Iterator<ValueType> Stack<ValueType>::GetEndIterator() const
{
	Iterator<ValueType> cIterator(*(new StackIterator<ValueType>(*this)));
	return cIterator;
}

template <class ValueType>
ConstIterator<ValueType> Stack<ValueType>::GetConstEndIterator() const
{
	ConstIterator<ValueType> cIterator(*(new StackIterator<ValueType>(*this)));
	return cIterator;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
