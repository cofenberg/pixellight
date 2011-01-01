/*********************************************************\
 *  File: FibonacciHeap.h                                *
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


#ifndef __PLGENERAL_CONTAINER_FIBONACCIHEAP_H__
#define __PLGENERAL_CONTAINER_FIBONACCIHEAP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/Heap.h"
#include "PLGeneral/Container/Functions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class KeyType, class ValueType, class Comparer> class FibonacciHeapIterator;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Fibonacci heap
*/
template <class KeyType, class ValueType, class Comparer = CompareFunction >
class FibonacciHeap : public Heap<KeyType, ValueType> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class FibonacciHeapIterator<KeyType, ValueType, Comparer>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		FibonacciHeap();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~FibonacciHeap();

		/**
		*  @brief
		*    Returns whether the Fibonacci heap is normalized or not
		*
		*  @return
		*    'true' if the Fibonacci heap is normalized, else 'false'
		*
		*  @remarks
		*    A Fibonacci heap is normalized if there are no tree's within the tree list
		*    with the same degree. After 'ExtractTop()' the heap is always normalized.
		*/
		bool IsNormalized();

		/**
		*  @brief
		*    Consolidate
		*
		*  @remarks
		*    'Cleanup' function. This function is called during the extraction of
		*    the top element automatically. After the execution of this function the
		*    heap is 'normalized'.
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe consolidate is not required)
		*/
		bool Consolidate();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		FibonacciHeap(const FibonacciHeap<KeyType, ValueType, Comparer> &cSource);

		/**
		*  @brief
		*    Makes this heap to a copy of another heap
		*
		*  @param[in] cHeap
		*    'FibonacciHeap' to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Heap<KeyType, ValueType> &operator =(const FibonacciHeap<KeyType, ValueType, Comparer> &cHeap);


	//[-------------------------------------------------------]
	//[ Private classes                                       ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal Fibonacci tree
		*/
		class Tree {


			//[-------------------------------------------------------]
			//[ Friends                                               ]
			//[-------------------------------------------------------]
			friend class FibonacciHeap<KeyType, ValueType, Comparer>;
			friend class FibonacciHeapIterator<KeyType, ValueType, Comparer>;


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				/**
				*  @brief
				*    Constructor
				*
				*  @param[in] Key
				*    Key
				*  @param[in] Value
				*    Value
				*/
				Tree(KeyType Key, ValueType Value);

				/**
				*  @brief
				*    Destructor
				*/
				~Tree();

				/**
				*  @brief
				*    Union
				*
				*  @param[in] cTree
				*    Tree to union with this tree
				*/
				void Union(Tree &cTree);


			//[-------------------------------------------------------]
			//[ Private data                                          ]
			//[-------------------------------------------------------]
			private:
				uint32	   m_nDegree;			/**< Degree of this tree node */
				Tree	  *m_pPreviousSibling;	/**< Previous sibling tree, can be NULL */
				Tree	  *m_pNextSibling;		/**< Next sibling tree, can be NULL */
				Tree	  *m_pChild;			/**< Child tree, can be NULL */
				KeyType	   m_Key;				/**< Key of this tree node */
				ValueType  m_Value;				/**< Value of this tree node */


		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// General data
		uint32   m_nNumOfElements;	/**< Current number of elements */
		Tree    *m_pFirst;			/**< First Fibonacci tree, can be NULL */
		Tree    *m_pTop;			/**< The current top Fibonacci tree, can be NULL (smallest/greatest key) */
		// Data for cleanup
		uint32   m_nNumOfTrees;		/**< Current number of trees ('m_pFirst' and all it's siblings) */
		uint32   m_nMaxNumOfMarks;	/**< Maximum number of marks */
		Tree   **m_ppMark;			/**< Mark array, can be NULL (has 'm_nMaxNumOfMarks' elements) */


	//[-------------------------------------------------------]
	//[ Public virtual Iterable functions                     ]
	//[-------------------------------------------------------]
	public:
		virtual Iterator<ValueType> GetIterator(uint32 nIndex = 0) const;
		virtual ConstIterator<ValueType> GetConstIterator(uint32 nIndex = 0) const;
		virtual Iterator<ValueType> GetEndIterator() const;
		virtual ConstIterator<ValueType> GetConstEndIterator() const;


	//[-------------------------------------------------------]
	//[ Public virtual Heap functions                         ]
	//[-------------------------------------------------------]
	public:
		virtual void Clear();
		virtual bool IsEmpty() const;
		virtual uint32 GetNumOfElements() const;
		virtual bool Add(const KeyType &Key, const ValueType &Value);
		virtual bool GetTop(ValueType *pValue = NULL, KeyType *pKey = NULL) const;
		virtual bool ExtractTop(ValueType *pValue = NULL, KeyType *pKey = NULL);


	//[-------------------------------------------------------]
	//[ Private virtual Heap functions                        ]
	//[-------------------------------------------------------]
	private:
		virtual Heap<KeyType, ValueType> &operator =(const Heap<KeyType, ValueType> &cHeap);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/FibonacciHeap.inl"


#endif // __PLGENERAL_CONTAINER_FIBONACCIHEAP_H__
