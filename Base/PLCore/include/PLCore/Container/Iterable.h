/*********************************************************\
 *  File: Iterable.h                                     *
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


#ifndef __PLCORE_CONTAINER_ITERABLE_H__
#define __PLCORE_CONTAINER_ITERABLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/PLCore.h"
#include "PLCore/Container/Iterator.h"
#include "PLCore/Container/ConstIterator.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class ValueType> class Iterator;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract iterable (aggregate) class
*
*  @see
*    - Iterator for further details and an usage example
*/
template <class ValueType>
class Iterable {


	//[-------------------------------------------------------]
	//[ Public virtual Iterable functions                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Iterable<ValueType>() {};

		/**
		*  @brief
		*    Returns an iterator operating on the derived data structure
		*
		*  @param[in] nIndex
		*    Start index, if >= 'total number of elements' the index is set to the last valid index
		*
		*  @return
		*    Iterator operating on the derived
		*/
		virtual Iterator<ValueType> GetIterator(uint32 nIndex = 0) const = 0;

		/**
		*  @brief
		*    Returns a constant iterator operating on the derived data structure
		*
		*  @param[in] nIndex
		*    Start index, if >= 'total number of elements' the index is set to the last valid index
		*
		*  @return
		*    Constant iterator operating on the derived
		*/
		virtual ConstIterator<ValueType> GetConstIterator(uint32 nIndex = 0) const = 0;

		/**
		*  @brief
		*    Returns an iterator operating on the derived data structure and starting at the end
		*
		*  @return
		*    Iterator operating on the derived,
		*
		*  @remarks
		*    Use this function to get an iterator if you want to iterate in reversed order starting
		*    at the end last element.
		*/
		virtual Iterator<ValueType> GetEndIterator() const = 0;

		/**
		*  @brief
		*    Returns a constant iterator operating on the derived data structure and starting at the end
		*
		*  @return
		*    Constant iterator operating on the derived,
		*
		*  @remarks
		*    Use this function to get a constant iterator if you want to iterate in reversed order
		*    starting at the end last element.
		*/
		virtual ConstIterator<ValueType> GetConstEndIterator() const = 0;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CONTAINER_ITERABLE_H__
