/*********************************************************\
 *  File: SimpleListIterator.h                           *
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


#ifndef __PLGENERAL_CONTAINER_SIMPLELISTITERATOR_H__
#define __PLGENERAL_CONTAINER_SIMPLELISTITERATOR_H__
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
template <class ValueType> class SimpleList;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linked simple list iterator class
*/
template <class ValueType>
class SimpleListIterator : public IteratorImpl<ValueType> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SimpleList<ValueType>;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] lstSimpleList
		*    Simple list to operate on
		*  @param[in] nIndex
		*    Start index, if >= GetNumOfElements() the index is set to the last valid index
		*/
		SimpleListIterator(const SimpleList<ValueType> &lstSimpleList, uint32 nIndex);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] lstSimpleList
		*    Simple list to operate on
		*
		*  @note
		*    - The iterator will start at the last element
		*/
		SimpleListIterator(const SimpleList<ValueType> &lstSimpleList);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		SimpleListIterator(const SimpleListIterator<ValueType> &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SimpleListIterator();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		const SimpleList<ValueType>					*m_plstSimpleList;		/**< Simple list to operate on (always valid!) */
		typename SimpleList<ValueType>::ListElement *m_pNextElement;		/**< Next list element, can be a null pointer */
		typename SimpleList<ValueType>::ListElement *m_pPreviousElement;	/**< Previous list element, can be a null pointer */


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
#include "PLGeneral/Container/SimpleListIterator.inl"


#endif // __PLGENERAL_CONTAINER_SIMPLELISTITERATOR_H__
