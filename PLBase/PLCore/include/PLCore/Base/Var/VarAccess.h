/*********************************************************\
 *  File: VarAccess.h                                    *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLCORE_VAR_ACCESS_H__
#define __PLCORE_VAR_ACCESS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Var/VarStorage.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Object;


//[-------------------------------------------------------]
//[ Helper classes                                        ]
//[-------------------------------------------------------]
// Access types
class AccessReadWrite{};	// Allow read and write access to var
class AccessReadOnly {};	// Allow only read access to var


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Access mode for a variable
*
*  @remarks
*    This class template is used to control the access mode of a variable.
*    If AccessReadWrite is specified, a variable can be read and written to.
*    If AccessReadOnly is specified, a variable can only be read.
*/
template <typename T, typename ACCESS, typename STORAGE>
class VarAccess : public VarStorage<T, STORAGE, typename STORAGE::StorageType> {
};


/**
*  @brief
*    Access mode for a variable
*
*  @remarks
*    Implementation for read/write access
*/
template <typename T, typename STORAGE>
class VarAccess<T, AccessReadWrite, STORAGE> : public VarStorage<T, STORAGE, typename STORAGE::StorageType> {


	//[-------------------------------------------------------]
	//[ Public data types                                     ]
	//[-------------------------------------------------------]
	public:
		// Storage type
		typedef typename Type<T>::_Type _Type;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] DefaultValue
		*    Default value of var
		*/
		VarAccess(const _Type &DefaultValue) : VarStorage<T, STORAGE, typename STORAGE::StorageType>(DefaultValue)
		{
		}

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] DefaultValue
		*    Default value of var
		*  @param[in] pObject
		*    Pointer to object holding the attribute
		*/
		VarAccess(const _Type &DefaultValue, Object *pObject) : VarStorage<T, STORAGE, typename STORAGE::StorageType>(DefaultValue, pObject)
		{
		}

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value
		*/
		inline _Type Get() const
		{
			return VarStorage<T, STORAGE, typename STORAGE::StorageType>::StorageGet();
		}

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] Value
		*    Value
		*/
		inline void Set(const _Type &Value)
		{
			VarStorage<T, STORAGE, typename STORAGE::StorageType>::StorageSet(Value);
		}


};


/**
*  @brief
*    Access mode for a variable
*
*  @remarks
*    Implementation for read-only access
*/
template <typename T, typename STORAGE>
class VarAccess<T, AccessReadOnly, STORAGE> : public VarStorage<T, STORAGE, typename STORAGE::StorageType> {


	//[-------------------------------------------------------]
	//[ Public data types                                     ]
	//[-------------------------------------------------------]
	public:
		// Storage type
		typedef typename Type<T>::_Type _Type;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] DefaultValue
		*    Default value of var
		*/
		VarAccess(const _Type &DefaultValue) : VarStorage<T, STORAGE, typename STORAGE::StorageType>(DefaultValue)
		{
		}

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] DefaultValue
		*    Default value of var
		*  @param[in] pObject
		*    Pointer to object holding the attribute
		*/
		VarAccess(const _Type &DefaultValue, Object *pObject) : VarStorage<T, STORAGE, typename STORAGE::StorageType>(DefaultValue, pObject)
		{
		}

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value
		*/
		inline _Type Get() const
		{
			return VarStorage<T, STORAGE, typename STORAGE::StorageType>::StorageGet();
		}

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] Value
		*    Value
		*/
		inline void Set(const _Type &Value)
		{
		}


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_VAR_ACCESS_H__
