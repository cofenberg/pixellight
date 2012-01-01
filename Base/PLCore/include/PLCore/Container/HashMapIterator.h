/*********************************************************\
 *  File: HashMapIterator.h                              *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLCORE_CONTAINER_HASHMAPITERATOR_H__
#define __PLCORE_CONTAINER_HASHMAPITERATOR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Container/IteratorImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class KeyType, class ValueType, class Hasher, class Comparer, class Grower> class HashMap;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Hash map iterator class
*/
template <class KeyType, class ValueType, class Hasher, class Comparer, class Grower>
class HashMapIterator : public IteratorImpl<ValueType> {


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
		HashMapIterator(const HashMap<KeyType, ValueType, Hasher, Comparer, Grower> &mapOwner, uint32 nIndex);

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
		HashMapIterator(const HashMap<KeyType, ValueType, Hasher, Comparer, Grower> &mapOwner);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		HashMapIterator(const HashMapIterator<KeyType, ValueType, Hasher, Comparer, Grower> &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~HashMapIterator();


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
		virtual IteratorImpl<ValueType> *Clone() const override;
		virtual bool HasNext() const override;
		virtual ValueType &Next() override;
		virtual bool HasPrevious() const override;
		virtual ValueType &Previous() override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Container/HashMapIterator.inl"


#endif // __PLCORE_CONTAINER_HASHMAPITERATOR_H__
