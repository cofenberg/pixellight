/*********************************************************\
 *  File: RefCountPtr.h                                  *
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


#ifndef __PLGENERAL_REFCOUNT_PTR_H__
#define __PLGENERAL_REFCOUNT_PTR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Base/RefCount.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Reference counted pointer template
*
*  @remarks
*    RefCountPtr contains a pointer to the reference counted object,
*    while RefCount is used in derived classes and therefore is the
*    reference counted object itself.
*/
template <class AType>
class RefCountPtr : public RefCount<AType> {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pPointer
		*    Pointer to the referenced object, can be a null pointer
		*/
		RefCountPtr(AType *pPointer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~RefCountPtr();

		/**
		*  @brief
		*    Get a pointer to the object
		*
		*  @return
		*    Pointer to the reference counter's object, can be a null pointer
		*/
		virtual AType *GetPointer() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		AType *m_pPointer; /**< Pointer to the referenced object, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Base/RefCountPtr.inl"


#endif // __PLGENERAL_REFCOUNT_PTR_H__
