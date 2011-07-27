/*********************************************************\
 *  File: Heap.h                                         *
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


#ifndef __PLCORE_CONTAINER_HEAP_H__
#define __PLCORE_CONTAINER_HEAP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Container/Iterable.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract heap class template (priority queue)
*
*  @remarks
*  @verbatim
*    Usage example:
*    // Create binary heap object with integer as key and pointer to characters
*    // as value
*    Heap<int, char*> cHeap;
*    // Fill heap
*    cHeap.Insert(1, "Second");  // Insert "Second"
*    cHeap.Insert(0, "First");   // Insert "First"
*    cHeap.Insert(2, "Third");   // Insert "Third"
*    // Read out heap
*    char *pT;
*    cHeap.Remove(pT, 0);  // Returns "First"
*    cHeap.Remove(pT, 0);  // Returns "Second"
*    cHeap.Remove(pT, 0);  // Returns "Third"
*  @endverbatim
*/
template <class KeyType, class ValueType>
class Heap : public Iterable<ValueType> {


	//[-------------------------------------------------------]
	//[ Public virtual Heap functions                         ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Clears the heap
		*/
		virtual void Clear() = 0;

		/**
		*  @brief
		*    Checks whether the heap is complete empty
		*
		*  @return
		*    'true' if the heap is empty, else 'false'
		*/
		virtual bool IsEmpty() const = 0;

		/**
		*  @brief
		*    Returns the number of elements
		*
		*  @return
		*    Number of container elements
		*/
		virtual uint32 GetNumOfElements() const = 0;

		/**
		*  @brief
		*    Adds a new element to the heap
		*
		*  @param[in] Key
		*    The key of the new element
		*  @param[in] Value
		*    The value of the new element
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - You have to check by yourself whether there's already such a key within the heap
		*/
		virtual bool Add(const KeyType &Key, const ValueType &Value) = 0;

		/**
		*  @brief
		*    Returns the value of the top element
		*
		*  @param[out] pValue
		*    If not a null pointer, this will receive the value of the top element
		*  @param[out] pKey
		*    If not a null pointer, this will receive the key of the top element
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool GetTop(ValueType *pValue = nullptr, KeyType *pKey = nullptr) const = 0;

		/**
		*  @brief
		*    Returns the value of the top element and removes it from the heap
		*
		*  @param[out] pValue
		*    If not a null pointer, this will receive the value of the top element
		*  @param[out] pKey
		*    If not a null pointer, this will receive the key of the top element
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool ExtractTop(ValueType *pValue = nullptr, KeyType *pKey = nullptr) = 0;


	//[-------------------------------------------------------]
	//[ Private virtual Heap functions                        ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Makes this heap to a copy of another heap
		*
		*  @param[in] cHeap
		*    Heap to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		virtual Heap<KeyType, ValueType> &operator =(const Heap<KeyType, ValueType> &cHeap) = 0;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CONTAINER_HEAP_H__
