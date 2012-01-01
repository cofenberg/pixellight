/*********************************************************\
 *  File: Iterator.inl                                   *
 *      Iterator template implementation
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
template <class ValueType>
Iterator<ValueType>::Iterator(IteratorImpl<ValueType> &cIteratorImpl) :
	m_pIteratorImpl(&cIteratorImpl)
{
	// Add a reference to the used iterator implementation
	m_pIteratorImpl->AddReference();
}

/**
*  @brief
*    Copy constructor
*/
template <class ValueType>
Iterator<ValueType>::Iterator(const Iterator<ValueType> &cIterator) :
	m_pIteratorImpl(cIterator.m_pIteratorImpl)
{
	// Add a reference to the used iterator implementation
	m_pIteratorImpl->AddReference();
}

/**
*  @brief
*    Destructor
*/
template <class ValueType>
Iterator<ValueType>::~Iterator()
{
	// Release the used iterator implementation
	m_pIteratorImpl->Release();
}

/**
*  @brief
*    Copy operator
*/
template <class ValueType>
Iterator<ValueType> &Iterator<ValueType>::operator =(const Iterator<ValueType> &cIterator)
{
	// Do only go on if the source is NOT this object!
	if (&cIterator != this) {
		// Release the current used iterator implementation
		m_pIteratorImpl->Release();

		// Set the new iterator implementation
		m_pIteratorImpl = cIterator.m_pIteratorImpl;

		// Add a reference to the new used iterator implementation
		m_pIteratorImpl->AddReference();
	}

	// Return this instance
	return *this;
}

/**
*  @brief
*    Checks whether the iterator can return a next element
*/
template <class ValueType>
bool Iterator<ValueType>::HasNext() const
{
	return m_pIteratorImpl->HasNext();
}

/**
*  @brief
*    Returns the next element
*/
template <class ValueType>
ValueType &Iterator<ValueType>::Next()
{
	// Make the implementation unique
	UniqueImplementation();

	// Return the next element
	return m_pIteratorImpl->Next();
}

/**
*  @brief
*    Returns the next element
*/
template <class ValueType>
ValueType &Iterator<ValueType>::operator ++()
{
	// Make the implementation unique
	UniqueImplementation();

	// Return the next element
	return m_pIteratorImpl->Next();
}

/**
*  @brief
*    Checks whether the iterator can return a previous element
*/
template <class ValueType>
bool Iterator<ValueType>::HasPrevious() const
{
	return m_pIteratorImpl->HasPrevious();
}

/**
*  @brief
*    Returns the previous element
*/
template <class ValueType>
ValueType &Iterator<ValueType>::Previous()
{
	// Make the implementation unique
	UniqueImplementation();

	// Return the previous element
	return m_pIteratorImpl->Previous();
}

/**
*  @brief
*    Returns the previous element
*/
template <class ValueType>
ValueType &Iterator<ValueType>::operator --()
{
	// Make the implementation unique
	UniqueImplementation();

	// Return the previous element
	return m_pIteratorImpl->Previous();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Checks whether the current internal iterator implementation is 'shared' and splits it if so
*/
template <class ValueType>
void Iterator<ValueType>::UniqueImplementation()
{
	// Is the iterator implementation used more than once?
	if (m_pIteratorImpl->GetRefCount() > 1) {
		// Release the current used iterator implementation
		m_pIteratorImpl->Release();

		// Set the new iterator implementation
		m_pIteratorImpl = m_pIteratorImpl->Clone();

		// Add a reference to the new used iterator implementation
		m_pIteratorImpl->AddReference();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
