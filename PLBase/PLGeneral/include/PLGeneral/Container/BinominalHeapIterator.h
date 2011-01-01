/*********************************************************\
 *  File: BinominalHeapIterator.h                        *
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


#ifndef __PLGENERAL_CONTAINER_BINOMINALHEAPITERATOR_H__
#define __PLGENERAL_CONTAINER_BINOMINALHEAPITERATOR_H__
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
template <class KeyType, class ValueType, class Comparer> class BinominalHeap;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Binominal heap iterator class
*/
template <class KeyType, class ValueType, class Comparer>
class BinominalHeapIterator : public IteratorImpl<ValueType> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class BinominalHeap<KeyType, ValueType, Comparer>;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cHeapOwner
		*    Binominal heap to operate on
		*  @param[in] nIndex
		*    Start index, if >= GetNumOfElements() the index is set to the last valid index
		*/
		BinominalHeapIterator(const BinominalHeap<KeyType, ValueType, Comparer> &cHeapOwner, uint32 nIndex);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cHeapOwner
		*    Binominal heap to operate on
		*
		*  @note
		*    - The iterator will start at the last element
		*/
		BinominalHeapIterator(const BinominalHeap<KeyType, ValueType, Comparer> &cHeapOwner);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		BinominalHeapIterator(const BinominalHeapIterator<KeyType, ValueType, Comparer> &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~BinominalHeapIterator();

		/**
		*  @brief
		*    Returns the previous sibling of the given tree
		*
		*  @param[in] pTree
		*    Tree to return the previous sibling from, can be NULL
		*
		*  @return
		*    Previous sibling tree of the given one, NULL of there's no previous sibling tree
		*
		*  @note
		*    - Because the binominal heap provides no information about the previous sibling tree, we
		*      have to find out the previous sibling tree by yourself (not that performant :)
		*/
		typename BinominalHeap<KeyType, ValueType, Comparer>::Tree *GetPreviousSibling(typename BinominalHeap<KeyType, ValueType, Comparer>::Tree *pTree) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		const BinominalHeap<KeyType, ValueType, Comparer>					*m_pHeapOwner;		/**< Binominal heap to operate on (always valid!) */
		Stack<typename BinominalHeap<KeyType, ValueType, Comparer>::Tree*>   m_lstParent;		/**< Parent stack */
		typename BinominalHeap<KeyType, ValueType, Comparer>::Tree			*m_pNextTree;		/**< Next tree, can be NULL */
		typename BinominalHeap<KeyType, ValueType, Comparer>::Tree			*m_pPreviousTree;	/**< Previous tree, can be NULL */


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
#include "PLGeneral/Container/BinominalHeapIterator.inl"


#endif // __PLGENERAL_CONTAINER_BINOMINALHEAPITERATOR_H__
