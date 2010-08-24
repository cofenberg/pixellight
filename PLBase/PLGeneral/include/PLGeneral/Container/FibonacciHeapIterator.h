/*********************************************************\
 *  File: FibonacciHeapIterator.h                        *
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


#ifndef __PLGENERAL_CONTAINER_FIBONACCIHEAPITERATOR_H__
#define __PLGENERAL_CONTAINER_FIBONACCIHEAPITERATOR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/Stack.h"
#include "PLGeneral/Container/IteratorImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class KeyType, class ValueType, class Comparer> class FibonacciHeap;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Fibonacci heap iterator class
*/
template <class KeyType, class ValueType, class Comparer>
class FibonacciHeapIterator : public IteratorImpl<ValueType> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class FibonacciHeap<KeyType, ValueType, Comparer>;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cHeapOwner
		*    Fibonacci heap to operate on
		*  @param[in] nIndex
		*    Start index, if >= GetNumOfElements() the index is set to the last valid index
		*/
		FibonacciHeapIterator(const FibonacciHeap<KeyType, ValueType, Comparer> &cHeapOwner, uint32 nIndex);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cHeapOwner
		*    Fibonacci heap to operate on
		*
		*  @note
		*    - The iterator will start at the last element
		*/
		FibonacciHeapIterator(const FibonacciHeap<KeyType, ValueType, Comparer> &cHeapOwner);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		FibonacciHeapIterator(const FibonacciHeapIterator<KeyType, ValueType, Comparer> &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~FibonacciHeapIterator();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		const FibonacciHeap<KeyType, ValueType, Comparer>				   *m_pHeapOwner;		/**< Fibonacci heap to operate on (always valid!) */
		Stack<typename FibonacciHeap<KeyType, ValueType, Comparer>::Tree*>  m_lstParent;		/**< Parent stack */
		typename FibonacciHeap<KeyType, ValueType, Comparer>::Tree		   *m_pNextTree;		/**< Next tree, can be NULL */
		typename FibonacciHeap<KeyType, ValueType, Comparer>::Tree		   *m_pPreviousTree;	/**< Previous tree, can be NULL */


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
#include "PLGeneral/Container/FibonacciHeapIterator.inl"


#endif // __PLGENERAL_CONTAINER_FIBONACCIHEAPITERATOR_H__
