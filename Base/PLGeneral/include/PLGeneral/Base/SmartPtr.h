/*********************************************************\
 *  File: SmartPtr.h                                     *
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


#ifndef __PLGENERAL_SMARTPTR_H__
#define __PLGENERAL_SMARTPTR_H__
#pragma once


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class AType> class RefCount;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Smart pointer template
*/
template <class AType>
class SmartPtr {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		SmartPtr();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pPtr
		*    Direct pointer to initialize with, can be a null pointer
		*/
		SmartPtr(AType *pPtr);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pPtr
		*    Smart pointer to initialize with
		*/
		SmartPtr(const SmartPtr<AType> &pPtr);

		/**
		*  @brief
		*    Destructor
		*/
		~SmartPtr();

		/**
		*  @brief
		*    Assign a pointer
		*
		*  @param[in] pPtr
		*    Direct pointer to assign, can be a null pointer
		*
		*  @return
		*    Reference to the smart pointer
		*/
		SmartPtr<AType> &operator =(AType *pPtr);

		/**
		*  @brief
		*    Assign a smart pointer
		*
		*  @param[in] cPtr
		*    Smart pointer to assign
		*
		*  @return
		*    Reference to the smart pointer
		*/
		SmartPtr<AType> &operator =(const SmartPtr<AType> &cPtr);

		/**
		*  @brief
		*    Get a direct pointer to the object
		*
		*  @return
		*    Pointer to the object, can be a null pointer
		*/
		AType *GetPointer() const;

		/**
		*  @brief
		*    Get a pointer to access the object
		*
		*  @return
		*    Pointer to the object, can be a null pointer
		*/
		AType *operator ->() const;

		/**
		*  @brief
		*    Cast to a pointer to the object
		*
		*  @return
		*    Pointer to the object, can be a null pointer
		*/
		operator AType*() const;

		/**
		*  @brief
		*    Check if the pointer is not a null pointer
		*
		*  @return
		*    'true' if the pointer is not a null pointer
		*/
		bool operator !() const;

		/**
		*  @brief
		*    Check for equality
		*
		*  @param[in] pPtr
		*    Direct pointer to compare with, can be a null pointer
		*
		*  @return
		*    'true' if the two pointers are equal
		*/
		bool operator ==(AType *pPtr) const;

		/**
		*  @brief
		*    Check for equality
		*
		*  @param[in] cPtr
		*    Smart pointer to compare with
		*
		*  @return
		*    'true' if the two pointers are equal
		*/
		bool operator ==(const SmartPtr<AType> &cPtr) const;

		/**
		*  @brief
		*    Check for equality
		*
		*  @param[in] pPtr
		*    Direct pointer to compare with, can be a null pointer
		*
		*  @return
		*    'true' if the two pointers are not equal
		*/
		bool operator !=(AType *pPtr) const;

		/**
		*  @brief
		*    Check for equality
		*
		*  @param[in] cPtr
		*    Smart pointer to compare with
		*
		*  @return
		*    'true' if the two pointers are not equal
		*/
		bool operator !=(const SmartPtr<AType> &cPtr) const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Assign a pointer to an object that does not implement RefCount
		*
		*  @param[in] pPtr
		*    Pointer to assign, can be a null pointer
		*/
		void SetPtr(void *pPtr);

		/**
		*  @brief
		*    Assign a pointer to an object that implements RefCount
		*
		*  @param[in] pPtr
		*    Pointer to assign, can be a null pointer
		*/
		void SetPtr(RefCount<AType> *pPtr);

		/**
		*  @brief
		*    Get pointer to the reference counted object
		*
		*  @return
		*    Pointer to the RefCount object, can be a null pointer
		*/
		RefCount<AType> *GetPtr() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		RefCount<AType> *m_pPtr; /**< Pointer to reference counter, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Base/SmartPtr.inl"


#endif // __PLGENERAL_SMARTPTR_H__
