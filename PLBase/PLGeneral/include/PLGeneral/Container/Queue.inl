/*********************************************************\
 *  File: Queue.inl                                      *
 *      Queue template implementation
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
//[ Private static data                                   ]
//[-------------------------------------------------------]
template <class ValueType> ValueType Queue<ValueType>::temp;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
template <class ValueType>
Queue<ValueType>::Queue() :
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
Queue<ValueType>::Queue(const Queue<ValueType> &cSource) :
	m_nNumOfElements(0),
	m_pTop(nullptr),
	m_pBottom(nullptr)
{
	// Copy queue
	*this = cSource;
}

/**
*  @brief
*    Destructor
*/
template <class ValueType>
Queue<ValueType>::~Queue()
{
	// Cleanup
	Clear();
}

/**
*  @brief
*    Push an element onto the queue
*/
template <class ValueType>
bool Queue<ValueType>::Push(const ValueType &Element)
{
	// Create new element
	QueueElement *pElement = new QueueElement;
	pElement->Data = Element;

	// Is this the first element?
	if (m_pTop) {
		// Push onto queue
		m_pTop->pNext = pElement;
		m_pTop		  = pElement;
		m_pTop->pNext = nullptr;
	} else {
		// This is the first element
		m_pBottom	  = pElement;
		m_pTop		  = pElement;
		m_pTop->pNext = nullptr;
	}
	m_nNumOfElements++;

	// Done
	return true;
}

/**
*  @brief
*    Pops the bottom element from the queue
*/
template <class ValueType>
bool Queue<ValueType>::Pop(ValueType *pElement)
{
	// Is there a bottom element?
	if (!m_pBottom)
		return false; // Error!

	// Get top element
	if (pElement)
		*pElement = m_pBottom->Data;

	// Pop element
	QueueElement *pBottomElement = m_pBottom;
	m_pBottom = m_pBottom->pNext;
	if (!m_pBottom)
		m_pTop = nullptr;
	delete pBottomElement;
	m_nNumOfElements--;

	// Done
	return true;
}

/**
*  @brief
*    Get the bottom element without removing it
*/
template <class ValueType>
ValueType Queue<ValueType>::Bottom() const
{
	// On error return temp object...
	return m_pBottom ? m_pBottom->Data : temp;
}

/**
*  @brief
*    Returns the number of element on the queue
*/
template <class ValueType>
uint32 Queue<ValueType>::GetNumOfElements() const
{
	return m_nNumOfElements;
}

/**
*  @brief
*    Copies the data from another queue
*/
template <class ValueType>
Queue<ValueType> &Queue<ValueType>::operator =(const Queue<ValueType> &cSource)
{
	// Clear queue
	Clear();

	// Push all elements from the other queue
	QueueElement *pElement = cSource.m_pBottom;
	while (pElement) {
		Push(pElement->Data);
		pElement = pElement->pNext;
	}

	// Return this instance
	return *this;
}

/**
*  @brief
*    Clears the whole queue
*/
template <class ValueType>
void Queue<ValueType>::Clear()
{
	// Remove all elements
	while (m_pBottom)
		Pop();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
