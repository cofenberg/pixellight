/*********************************************************\
 *  File: ListIterator.h                                 *
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


#ifndef __PLGENERAL_CONTAINER_LISTITERATOR_H__
#define __PLGENERAL_CONTAINER_LISTITERATOR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/PLGeneral.h"
#include "PLGeneral/Container/IteratorImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class ValueType> class List;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linked list iterator class
*/
template <class ValueType>
class ListIterator : public IteratorImpl<ValueType> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class List<ValueType>;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] lstList
		*    List to operate on
		*  @param[in] nIndex
		*    Start index, if >= GetNumOfElements() the index is set to the last valid index
		*/
		ListIterator(const List<ValueType> &lstList, uint32 nIndex);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] lstList
		*    List to operate on
		*
		*  @note
		*    - The iterator will start at the last element
		*/
		ListIterator(const List<ValueType> &lstList);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		ListIterator(const ListIterator<ValueType> &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ListIterator();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		const List<ValueType>				  *m_plstList;			/**< List to operate on (always valid!) */
		typename List<ValueType>::ListElement *m_pNextElement;		/**< Next list element, can be a null pointer */
		typename List<ValueType>::ListElement *m_pPreviousElement;	/**< Previous list element, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Private virtual IteratorImpl functions                ]
	//[-------------------------------------------------------]
	private:
		virtual IteratorImpl<ValueType> *Clone() const;
		virtual bool HasNext() const;
		virtual ValueType &Next();
		virtual bool HasPrevious() const;
		virtual ValueType &Previous();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/ListIterator.inl"


#endif // __PLGENERAL_CONTAINER_LISTITERATOR_H__
