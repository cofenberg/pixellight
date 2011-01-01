/*********************************************************\
 *  File: DynVar.h                                       *
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


#ifndef __PLCORE_DYNVAR_H__
#define __PLCORE_DYNVAR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include "PLCore/PLCore.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class DynTypeInfo;
class VarDesc;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Virtual base class for variables
*
*  @remarks
*    This is the virtual base class to access variables and attributes dynamically.
*    It is a virtual interface that allows you to access a variable regardless
*    of it's actual type and storage.
*/
class DynVar {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API DynVar();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~DynVar();


	//[-------------------------------------------------------]
	//[ Public virtual DynVar functions                       ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get variable descriptor
		*
		*  @return
		*    Descriptor (can be NULL)
		*/
		PLCORE_API virtual const VarDesc *GetDesc() const;

		/**
		*  @brief
		*    Get type
		*
		*  @return
		*    Type info
		*/
		PLCORE_API virtual DynTypeInfo &GetType() const;

		/**
		*  @brief
		*    Get type ID
		*
		*  @return
		*    Type ID
		*/
		PLCORE_API virtual int GetTypeID() const;

		/**
		*  @brief
		*    Get type name
		*
		*  @return
		*    Type name (e.g. "int")
		*/
		PLCORE_API virtual PLGeneral::String GetTypeName() const;

		/**
		*  @brief
		*    Check if variable is set to default value
		*
		*  @return
		*    'true' if default value is set, else 'false'
		*/
		PLCORE_API virtual bool IsDefault() const;

		/**
		*  @brief
		*    Set variable to default value
		*/
		PLCORE_API virtual void SetDefault();

		/**
		*  @brief
		*    Get default value as string
		*
		*  @return
		*    Default value as string
		*/
		PLCORE_API virtual PLGeneral::String GetDefault() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] pValue
		*    Value as dynamic var
		*/
		PLCORE_API virtual void SetVar(const DynVar *pValue);

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value as bool
		*/
		PLCORE_API virtual bool GetBool() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] bValue
		*    Value as bool
		*/
		PLCORE_API virtual void SetBool(bool bValue);

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value as int
		*/
		PLCORE_API virtual int GetInt() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] nValue
		*    Value as int
		*/
		PLCORE_API virtual void SetInt(int nValue);

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value as int8
		*/
		PLCORE_API virtual PLGeneral::int8 GetInt8() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] nValue
		*    Value as int8
		*/
		PLCORE_API virtual void SetInt8(PLGeneral::int8 nValue);

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value as int16
		*/
		PLCORE_API virtual PLGeneral::int16 GetInt16() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] nValue
		*    Value as int16
		*/
		PLCORE_API virtual void SetInt16(PLGeneral::int16 nValue);

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value as int32
		*/
		PLCORE_API virtual PLGeneral::int32 GetInt32() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] nValue
		*    Value as int32
		*/
		PLCORE_API virtual void SetInt32(PLGeneral::int32 nValue);

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value as int64
		*/
		PLCORE_API virtual PLGeneral::int64 GetInt64() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] nValue
		*    Value as int64
		*/
		PLCORE_API virtual void SetInt64(PLGeneral::int64 nValue);

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value as uint8
		*/
		PLCORE_API virtual PLGeneral::uint8 GetUInt8() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] nValue
		*    Value as uint8
		*/
		PLCORE_API virtual void SetUInt8(PLGeneral::uint8 nValue);

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value as uint16
		*/
		PLCORE_API virtual PLGeneral::uint16 GetUInt16() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] nValue
		*    Value as uint16
		*/
		PLCORE_API virtual void SetUInt16(PLGeneral::uint16 nValue);

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value as uint32
		*/
		PLCORE_API virtual PLGeneral::uint32 GetUInt32() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] nValue
		*    Value as uint32
		*/
		PLCORE_API virtual void SetUInt32(PLGeneral::uint32 nValue);

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value as uint64
		*/
		PLCORE_API virtual PLGeneral::uint64 GetUInt64() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] nValue
		*    Value as uint64
		*/
		PLCORE_API virtual void SetUInt64(PLGeneral::uint64 nValue);

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value as uint_ptr
		*/
		PLCORE_API virtual PLGeneral::uint_ptr GetUIntPtr() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] nValue
		*    Value as uint_ptr
		*/
		PLCORE_API virtual void SetUIntPtr(PLGeneral::uint_ptr nValue);

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value as float
		*/
		PLCORE_API virtual float GetFloat() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] fValue
		*    Value as float
		*/
		PLCORE_API virtual void SetFloat(float fValue);

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value as double
		*/
		PLCORE_API virtual double GetDouble() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] dValue
		*    Value as double
		*/
		PLCORE_API virtual void SetDouble(double dValue);

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value as string
		*/
		PLCORE_API virtual PLGeneral::String GetString() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] sValue
		*    Value as string
		*/
		PLCORE_API virtual void SetString(const PLGeneral::String &sValue);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_DYNVAR_H__
