/*********************************************************\
 *  File: BinaryHeap.h                                   *
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


#ifndef __PLCORE_CONTAINER_BINARYHEAP_H__
#define __PLCORE_CONTAINER_BINARYHEAP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Container/Heap.h"
#include "PLCore/Container/Functions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class KeyType, class ValueType, class Comparer> class BinaryHeapIterator;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Binary heap (arrayed)
*
*  @remarks
*    Node: Elements[i*2]  Left child: Elements[i*2+1]  Right child: Elements[i*2+2]
*/
template <class KeyType, class ValueType, class Comparer = CompareFunction >
class BinaryHeap : public Heap<KeyType, ValueType> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class BinaryHeapIterator<KeyType, ValueType, Comparer>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nResizeCount
		*    Resize count
		*/
		BinaryHeap(uint32 nResizeCount = 16);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~BinaryHeap();

		/**
		*  @brief
		*    Returns the number of elements automatically added if the binary heap
		*    size is to small
		*
		*  @return
		*    Number of elements automatically added if the binary heap size is to small
		*/
		uint32 GetResizeCount() const;

		/**
		*  @brief
		*    Sets the number of elements automatically added if the binary heap
		*    size is to small
		*
		*  @param[in] nCount
		*    Number of elements automatically added if the binary heap size is to small
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If nCount is 0, the binary heap size isn't changed automatically
		*/
		bool SetResizeCount(uint32 nCount = 16);

		/**
		*  @brief
		*    Resets the binary heap
		*
		*  @remarks
		*    While the Clear() function destroys also the data, this function will only
		*    reset the current number of elements within the array to 0.
		*/
		void Reset();


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
		BinaryHeap(const BinaryHeap<KeyType, ValueType, Comparer> &cSource);

		/**
		*  @brief
		*    Makes this heap to a copy of another heap
		*
		*  @param[in] cHeap
		*    'BinaryHeap' to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Heap<KeyType, ValueType> &operator =(const BinaryHeap<KeyType, ValueType, Comparer> &cHeap);

		/**
		*  @brief
		*    Returns the index of the parent
		*
		*  @param[in] nIndex
		*    Index of the current element
		*
		*  @return
		*    Index of the parent, < 0 if there's no parent
		*/
		int GetParent(uint32 nIndex) const;

		/**
		*  @brief
		*    Returns the index of the left child
		*
		*  @param[in] nIndex
		*    Index of the current element
		*
		*  @return
		*    Index of the left child
		*/
		uint32 GetLeft(uint32 nIndex) const;

		/**
		*  @brief
		*    Returns the index of the right child
		*
		*  @param[in] nIndex
		*    Index of the current element
		*
		*  @return
		*    Index of the right child
		*/
		uint32 GetRight(uint32 nIndex) const;

		/**
		*  @brief
		*    Shif up
		*
		*  @param[in] nIndex
		*    Current index
		*
		*  @return
		*    The new index of the element
		*/
		uint32 UpHeap(uint32 nIndex);

		/**
		*  @brief
		*    Shif down
		*
		*  @param[in] nIndex
		*    Current index
		*/
		void DownHeap(uint32 nIndex);


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal heap element
		*/
		class Element {
			public:
				KeyType   Key;
				ValueType Value;
				Element &operator =(const Element &cSource) {
					Key   = cSource.Key;
					Value = cSource.Value;
					return *this;
				}
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		uint32   m_nMaxNumOfElements;	/**< Maximum number of elements */
		uint32   m_nNumOfElements;		/**< Current number of elements */
		uint32   m_nResizeCount;		/**< Automatic resize count */
		Element *m_pData;				/**< Heap data, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Public virtual Iterable functions                     ]
	//[-------------------------------------------------------]
	public:
		virtual Iterator<ValueType> GetIterator(uint32 nIndex = 0) const override;
		virtual ConstIterator<ValueType> GetConstIterator(uint32 nIndex = 0) const override;
		virtual Iterator<ValueType> GetEndIterator() const override;
		virtual ConstIterator<ValueType> GetConstEndIterator() const override;


	//[-------------------------------------------------------]
	//[ Public virtual Heap functions                         ]
	//[-------------------------------------------------------]
	public:
		virtual void Clear() override;
		virtual bool IsEmpty() const override;
		virtual uint32 GetNumOfElements() const override;
		virtual bool Add(const KeyType &Key, const ValueType &Value) override;
		virtual bool GetTop(ValueType *pValue = nullptr, KeyType *pKey = nullptr) const override;
		virtual bool ExtractTop(ValueType *pValue = nullptr, KeyType *pKey = nullptr) override;


	//[-------------------------------------------------------]
	//[ Private virtual Heap functions                        ]
	//[-------------------------------------------------------]
	private:
		virtual Heap<KeyType, ValueType> &operator =(const Heap<KeyType, ValueType> &cHeap) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Container/BinaryHeap.inl"


#endif // __PLCORE_CONTAINER_BINARYHEAP_H__
