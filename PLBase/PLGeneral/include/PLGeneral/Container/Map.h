/*********************************************************\
 *  File: Map.h                                          *
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


#ifndef __PLGENERAL_CONTAINER_MAP_H__
#define __PLGENERAL_CONTAINER_MAP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/Iterable.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract map (associative array) base template class
*
*  @verbatim
*    Usage example:
*    HashMap<String, MyClass*> mapHashMap;  // Hash table which manages MyClass pointers
*    MyClass *pT1=new MyClass(), *pT2=new MyClass(), *pT3=new MyClass(), *pT;  // Test instances
*    mapHashMap.Add("Lenny", pT1);  // Give pointer to T1 the name 'Lenny'
*    mapHashMap.Add("Barny", pT2);  // Give pointer to T2 the name 'Barny'
*    mapHashMap.Set("Homer", pT3);  // Give pointer to T3 the name 'Homer' by using the set function
*    pT = mapHashMap.Get("Barny");   // Give us the pointer to 'Barny'
*    pT = mapHashMap.Get("Homer");   // Give us the pointer to 'Homer'
*    pT = mapHashMap.Get("Lenny");   // Give us the pointer to 'Lenny'
*  @endverbatim
*
*  @note
*    - The standard container iterator iterates over all values (NOT the keys!) within the map, use
*      the special key iterator for iterating over all keys
*    - Within a map, you can't expect that the iterator returns the elements always in exact the same order
*    - Usually map iterators are not that performance by concept, so, try to avoid to use map iterators
*/
template <class KeyType, class ValueType>
class Map : public Iterable<ValueType> {


	//[-------------------------------------------------------]
	//[ Public static variables                               ]
	//[-------------------------------------------------------]
	public:
		static KeyType NullKey;	/**< 'Null' key object, do NEVER EVER manipulate this object! */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Clears the map
		*/
		virtual void Clear() = 0;

		/**
		*  @brief
		*    Checks whether the map is complete empty
		*
		*  @return
		*    'true' if the map is empty, else 'false'
		*/
		virtual bool IsEmpty() const = 0;

		/**
		*  @brief
		*    Returns the number of elements/entries
		*
		*  @return
		*    Number of container elements/entries
		*/
		virtual uint32 GetNumOfElements() const = 0;

		/**
		*  @brief
		*    Adds/puts a new element to the map
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
		*    - You have to check by yourself whether there's already such a key within the map
		*
		*  @see
		*    - Set()
		*/
		virtual bool Add(const KeyType &Key, const ValueType &Value) = 0;

		/**
		*  @brief
		*    Replaces the value of a map element
		*
		*  @param[in] Key
		*    The key of the element
		*  @param[in] NewValue
		*    The new value of the element
		*
		*  @return
		*    'true' if all went fine, else 'false' (key not found?)
		*
		*  @see
		*    - Set()
		*/
		virtual bool Replace(const KeyType &Key, const ValueType &NewValue) = 0;

		/**
		*  @brief
		*    Sets (adds or replaces) the value of a map element
		*
		*  @param[in] Key
		*    The key of the element
		*  @param[in] Value
		*    The set value of the element
		*
		*  @return
		*    'false' if a new element was added, 'true' if the value was replaced
		*
		*  @remarks
		*    This function is a combination of the add and replace function and 'just' assigns
		*    a value to a given key without taking care of whether or not there's already an
		*    element with the given key inside the map.
		*
		*  @see
		*    - Add()
		*    - Replace()
		*/
		virtual bool Set(const KeyType &Key, const ValueType &Value) = 0;

		/**
		*  @brief
		*    Removes an element from the map
		*
		*  @param[in] Key
		*    Key of the element which should be removed
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Remove(const KeyType &Key) = 0;

		/**
		*  @brief
		*    Removes all elements with a certain value from the map
		*
		*  @param[in] Value
		*    Value to look for
		*
		*  @return
		*    Number of removed elements
		*
		*  @note
		*    - For performance reasons, try to use the Remove(<Key>) function
		*      whenever possible!
		*/
		virtual uint32 RemoveValue(const ValueType &Value) = 0;

		/**
		*  @brief
		*    Returns the value of a given key
		*
		*  @param[in] Key
		*    Key to use
		*
		*  @return
		*    Reference of the value of the given key, reference to the 'Null'-object on error
		*/
		virtual const ValueType &Get(const KeyType &Key) const = 0;

		/**
		*  @brief
		*    Returns the value of a given key
		*
		*  @param[in] Key
		*    Key to use
		*
		*  @return
		*    Reference of the value of the given key, reference to the 'Null'-object on error
		*/
		virtual ValueType &Get(const KeyType &Key) = 0;

		/**
		*  @brief
		*    Returns a key iterator operating on the derived data structure
		*
		*  @param[in] nIndex
		*    Start index, if >= 'total number of elements' the index is set to the last valid index
		*
		*  @return
		*    Key iterator operating on the derived
		*/
		virtual Iterator<KeyType> GetKeyIterator(uint32 nIndex = 0) const = 0;

		/**
		*  @brief
		*    Returns a constant key iterator operating on the derived data structure
		*
		*  @param[in] nIndex
		*    Start index, if >= 'total number of elements' the index is set to the last valid index
		*
		*  @return
		*    Constant key iterator operating on the derived
		*/
		virtual ConstIterator<KeyType> GetConstKeyIterator(uint32 nIndex = 0) const = 0;

		/**
		*  @brief
		*    Returns a key iterator operating on the derived data structure and starting at the end
		*
		*  @return
		*    Key iterator operating on the derived,
		*
		*  @remarks
		*    Use this function to get a key iterator if you want to iterate in reversed order starting
		*    at the end last element.
		*/
		virtual Iterator<KeyType> GetEndKeyIterator() const = 0;

		/**
		*  @brief
		*    Returns a constant key iterator operating on the derived data structure and starting at the end
		*
		*  @return
		*    Constant key iterator operating on the derived,
		*
		*  @remarks
		*    Use this function to get a constant key iterator if you want to iterate in reversed order
		*    starting at the end last element.
		*/
		virtual ConstIterator<KeyType> GetConstEndKeyIterator() const = 0;


	//[-------------------------------------------------------]
	//[ Private virtual Map functions                         ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Makes this map to a copy of another map
		*
		*  @param[in] cMap
		*    Map to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		virtual Map<KeyType, ValueType> &operator =(const Map<KeyType, ValueType> &cMap) = 0;


};


//[-------------------------------------------------------]
//[ Public static variables                               ]
//[-------------------------------------------------------]
template <class KeyType, class ValueType> KeyType Map<KeyType, ValueType>::NullKey;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_CONTAINER_MAP_H__
