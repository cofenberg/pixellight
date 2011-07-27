/*********************************************************\
 *  File: BitsetIterator.h                               *
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


#ifndef __PLCORE_CONTAINER_BITSETITERATOR_H__
#define __PLCORE_CONTAINER_BITSETITERATOR_H__
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
class Bitset;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Bit set iterator class
*/
class BitsetIterator : public IteratorImpl<bool> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Bitset;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] lstBitset
		*    Bitset to operate on
		*  @param[in] nIndex
		*    Start index, if >= GetNumOfElements() the index is set to the last valid index
		*/
		BitsetIterator(const Bitset &lstBitset, uint32 nIndex);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] lstBitset
		*    Bitset to operate on
		*
		*  @note
		*    - The iterator will start at the last element
		*/
		BitsetIterator(const Bitset &lstBitset);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		BitsetIterator(const BitsetIterator &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~BitsetIterator();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		const Bitset *m_plstBitset;	/**< Bitset to operate on (always valid!) */
		uint32		  m_nNextID;	/**< ID of the next element */


	//[-------------------------------------------------------]
	//[ Privat virtual IteratorImpl functions                 ]
	//[-------------------------------------------------------]
	private:
		virtual IteratorImpl<bool> *Clone() const override;
		virtual bool HasNext() const override;
		virtual bool &Next() override;
		virtual bool HasPrevious() const override;
		virtual bool &Previous() override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CONTAINER_BITSETITERATOR_H__
