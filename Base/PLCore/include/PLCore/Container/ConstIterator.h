/*********************************************************\
 *  File: ConstIterator.h                                *
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


#ifndef __PLCORE_CONTAINER_CONSTITERATOR_H__
#define __PLCORE_CONTAINER_CONSTITERATOR_H__
#pragma once


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class ValueType> class IteratorImpl;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constant iterator class
*
*  @remarks
*    If an iterator is used, the iterable (for instance 'Map', 'Container' or 'Heap') the iterator
*    is operating on should not be manipulated by adding/removing new elements because this may
*    produce undefined behaviour! Is highly recommended to keep the iterator in the smallest possible
*    local scope and to never keep an iterator as for instance pointer over a long time.
*
*  @note
*    - An iterator is similar to a "for each loop"
*/
template <class ValueType>
class ConstIterator {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cIteratorImpl
		*    Reference to the iterator specific implementation
		*/
		ConstIterator(IteratorImpl<ValueType> &cIteratorImpl);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cIterator
		*    Source to copy from
		*/
		ConstIterator(const ConstIterator<ValueType> &cIterator);

		/**
		*  @brief
		*    Destructor
		*/
		~ConstIterator<ValueType>();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cIterator
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		ConstIterator<ValueType> &operator =(const ConstIterator<ValueType> &cIterator);

		/**
		*  @brief
		*    Checks whether the iterator can return a next element
		*
		*  @return
		*    'true' if the iterator can return a next element, else 'false'
		*/
		bool HasNext() const;

		/**
		*  @brief
		*    Returns the next element
		*
		*  @return
		*    Reference to the next element, reference to the 'Null'-object on error
		*/
		const ValueType &Next();

		/**
		*  @brief
		*    Returns the next element
		*
		*  @return
		*    Reference to the next element, reference to the 'Null'-object on error
		*/
		const ValueType &operator ++();

		/**
		*  @brief
		*    Checks whether the iterator can return a previous element
		*
		*  @return
		*    'true' if the iterator can return a previous element, else 'false'
		*/
		bool HasPrevious() const;

		/**
		*  @brief
		*    Returns the previous element
		*
		*  @return
		*    Reference to the previous element, reference to the 'Null'-object on error
		*/
		const ValueType &Previous();

		/**
		*  @brief
		*    Returns the previous element
		*
		*  @return
		*    Reference to the previous element, reference to the 'Null'-object on error
		*/
		const ValueType &operator --();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Checks whether the current internal iterator implementation is 'shared' and splits it if so
		*/
		void UniqueImplementation();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		IteratorImpl<ValueType> *m_pIteratorImpl;	/**< Pointer to the iterator specific implementation, always valid */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Container/ConstIterator.inl"


#endif // __PLCORE_CONTAINER_CONSTITERATOR_H__
