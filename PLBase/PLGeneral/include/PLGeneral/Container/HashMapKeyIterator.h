/*********************************************************\
 *  File: HashMapKeyIterator.h                           *
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


#ifndef __PLGENERAL_CONTAINER_HASHMAPKEYITERATOR_H__
#define __PLGENERAL_CONTAINER_HASHMAPKEYITERATOR_H__
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
template <class KeyType, class ValueType, class Hasher, class Comparer, class Grower> class HashMap;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Hash map key iterator class
*/
template <class KeyType, class ValueType, class Hasher, class Comparer, class Grower>
class HashMapKeyIterator : public IteratorImpl<KeyType> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class HashMap<KeyType, ValueType, Hasher, Comparer, Grower>;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] mapOwner
		*    Hash map to operate on
		*  @param[in] nIndex
		*    Start index, if >= GetNumOfElements() the index is set to the last valid index
		*/
		HashMapKeyIterator(const HashMap<KeyType, ValueType, Hasher, Comparer, Grower> &mapOwner, uint32 nIndex);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] mapOwner
		*    Hash map to operate on
		*
		*  @note
		*    - The iterator will start at the last element
		*/
		HashMapKeyIterator(const HashMap<KeyType, ValueType, Hasher, Comparer, Grower> &mapOwner);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		HashMapKeyIterator(const HashMapKeyIterator<KeyType, ValueType, Hasher, Comparer, Grower> &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~HashMapKeyIterator();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		const HashMap<KeyType, ValueType, Hasher, Comparer, Grower>			 *m_pmapOwner;		/**< Hash map to operate on (always valid!) */
		uint32																  m_nNextSlots;		/**< Next slots list */
		typename HashMap<KeyType, ValueType, Hasher, Comparer, Grower>::Slot *m_pNextSlot;		/**< Next slot, can be a null pointer */
		uint32																  m_nPreviousSlots;	/**< Next slots list */
		typename HashMap<KeyType, ValueType, Hasher, Comparer, Grower>::Slot *m_pPreviousSlot;	/**< Previous slot, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Private virtual IteratorImpl functions                ]
	//[-------------------------------------------------------]
	private:
		virtual IteratorImpl<KeyType> *Clone() const;
		virtual bool HasNext() const;
		virtual KeyType &Next();
		virtual bool HasPrevious() const;
		virtual KeyType &Previous();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/HashMapKeyIterator.inl"


#endif // __PLGENERAL_CONTAINER_HASHMAPKEYITERATOR_H__
