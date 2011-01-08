/*********************************************************\
 *  File: RefCount.h                                     *
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


#ifndef __PLGENERAL_REFCOUNT_H__
#define __PLGENERAL_REFCOUNT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/PLGeneral.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Reference counter template
*
*  @note
*    - Initially the reference counter is 0
*/
template <class AType>
class RefCount {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		RefCount();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~RefCount();

		/**
		*  @brief
		*    Get a pointer to the object
		*
		*  @return
		*    Pointer to the reference counter's object, NEVER a null pointer!
		*/
		virtual AType *GetPointer() const;

		/**
		*  @brief
		*    Increases the reference count
		*
		*  @return
		*    Current reference count
		*/
		uint32 AddReference();

		/**
		*  @brief
		*    Decreases the reference count
		*
		*  @return
		*    Current reference count
		*/
		uint32 Release();

		/**
		*  @brief
		*    Gets the current reference count
		*
		*  @return
		*    Current reference count
		*/
		uint32 GetRefCount() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		uint32 m_nRefCount; /**< Reference count */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Base/RefCount.inl"


#endif // __PLGENERAL_REFCOUNT_H__
