/*********************************************************\
 *  File: Var.h                                          *
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


#ifndef __PLCORE_VAR_H__
#define __PLCORE_VAR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Tools/TypeTraits.h"
#include "PLCore/Base/Type/Type.h"
#include "PLCore/Base/Var/DynVar.h"
#include "PLCore/Base/Var/VarAccess.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Object;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Typed variable
*
*  @remarks
*    This class represents an actual variable of a certain type.
*    The two other template parameters control, where the actual value
*    is stored (STORAGE) and how the variable is allowed to be accessed (ACCESS).
*/
template <typename T, typename ACCESS = PLCore::AccessReadWrite, typename STORAGE = PLCore::StorageDirectValue >
class Var : public DynVar {


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
		*/
		Var() :
			m_Value(DefaultValue<T>::Default())
		{
		}

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] DefaultValue
		*    Default value for the var
		*/
		Var(_Type DefaultValue) :
			m_Value(DefaultValue)
		{
		}

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] DefaultValue
		*    Default value for the var
		*  @param[in] pObject
		*    Pointer to object to which the attribute belongs
		*/
		Var(_Type DefaultValue, Object *pObject) :
			m_Value(DefaultValue, pObject)
		{
		}

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Var()
		{
		}

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value
		*/
		operator _Type() const
		{
			// Get value
			return m_Value.Get();
		}

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] Value
		*    New value
		*
		*  @return
		*    Reference to this instance
		*/
		Var &operator =(const _Type &Value)
		{
			// Set value
			m_Value.Set(Value);
			return *this;
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
			// Return value
			return m_Value.Get();
		}

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] Value
		*    New value
		*/
		inline void Set(const _Type &Value)
		{
			m_Value.Set(Value);
		}

		/**
		*  @brief
		*    Get default value
		*
		*  @return
		*    Default value
		*/
		inline _Type Default() const
		{
			// Return default value
			return m_Value.GetDefault();
		}


	//[-------------------------------------------------------]
	//[ Public virtual DynVar functions                       ]
	//[-------------------------------------------------------]
	public:
		virtual DynTypeInfo &GetType() const
		{
			return TypeInfo<T>::Instance;
		}

		virtual PLGeneral::String GetTypeName() const
		{
			return Type<T>::GetTypeName();
		}

		virtual int GetTypeID() const
		{
			return Type<T>::TypeID;
		}

		virtual bool IsDefault() const
		{
			return (m_Value.Get() == m_Value.GetDefault());
		}

		virtual void SetDefault()
		{
			m_Value.Set(m_Value.GetDefault());
		}

		virtual PLGeneral::String GetDefault() const
		{
			return Type<T>::ConvertToString(m_Value.GetDefault());
		}

		virtual void SetVar(const DynVar *pValue)
		{
			m_Value.Set(Type<T>::ConvertFromVar(pValue));
		}

		virtual bool GetBool() const
		{
			return Type<T>::ConvertToBool(m_Value.Get());
		}

		virtual void SetBool(bool bValue)
		{
			m_Value.Set(Type<T>::ConvertFromBool(bValue));
		}

		virtual int GetInt() const
		{
			return Type<T>::ConvertToInt(m_Value.Get());
		}

		virtual void SetInt(int nValue)
		{
			m_Value.Set(Type<T>::ConvertFromInt(nValue));
		}

		virtual PLGeneral::int8 GetInt8() const
		{
			return Type<T>::ConvertToInt8(m_Value.Get());
		}

		virtual void SetInt8(PLGeneral::int8 nValue)
		{
			m_Value.Set(Type<T>::ConvertFromInt8(nValue));
		}

		virtual PLGeneral::int16 GetInt16() const
		{
			return Type<T>::ConvertToInt16(m_Value.Get());
		}

		virtual void SetInt16(PLGeneral::int16 nValue)
		{
			m_Value.Set(Type<T>::ConvertFromInt16(nValue));
		}

		virtual PLGeneral::int32 GetInt32() const
		{
			return Type<T>::ConvertToInt32(m_Value.Get());
		}

		virtual void SetInt32(PLGeneral::int32 nValue)
		{
			m_Value.Set(Type<T>::ConvertFromInt32(nValue));
		}

		virtual PLGeneral::int64 GetInt64() const
		{
			return Type<T>::ConvertToInt64(m_Value.Get());
		}

		virtual void SetInt64(PLGeneral::int64 nValue)
		{
			m_Value.Set(Type<T>::ConvertFromInt64(nValue));
		}

		virtual PLGeneral::uint8 GetUInt8() const
		{
			return Type<T>::ConvertToUInt8(m_Value.Get());
		}

		virtual void SetUInt8(PLGeneral::uint8 nValue)
		{
			m_Value.Set(Type<T>::ConvertFromUInt8(nValue));
		}

		virtual PLGeneral::uint16 GetUInt16() const
		{
			return Type<T>::ConvertToUInt16(m_Value.Get());
		}

		virtual void SetUInt16(PLGeneral::uint16 nValue)
		{
			m_Value.Set(Type<T>::ConvertFromUInt16(nValue));
		}

		virtual PLGeneral::uint32 GetUInt32() const
		{
			return Type<T>::ConvertToUInt32(m_Value.Get());
		}

		virtual void SetUInt32(PLGeneral::uint32 nValue)
		{
			m_Value.Set(Type<T>::ConvertFromUInt32(nValue));
		}

		virtual PLGeneral::uint64 GetUInt64() const
		{
			return Type<T>::ConvertToUInt64(m_Value.Get());
		}

		virtual void SetUInt64(PLGeneral::uint64 nValue)
		{
			m_Value.Set(Type<T>::ConvertFromUInt64(nValue));
		}

		virtual PLGeneral::uint_ptr GetUIntPtr() const
		{
			return Type<T>::ConvertToUIntPtr(m_Value.Get());
		}

		virtual void SetUIntPtr(PLGeneral::uint_ptr nValue)
		{
			m_Value.Set(Type<T>::ConvertFromUIntPtr(nValue));
		}

		virtual float GetFloat() const
		{
			return Type<T>::ConvertToFloat(m_Value.Get());
		}

		virtual void SetFloat(float fValue)
		{
			m_Value.Set(Type<T>::ConvertFromFloat(fValue));
		}

		virtual double GetDouble() const
		{
			return Type<T>::ConvertToDouble(m_Value.Get());
		}

		virtual void SetDouble(double dValue)
		{
			m_Value.Set(Type<T>::ConvertFromDouble(dValue));
		}

		virtual PLGeneral::String GetString() const
		{
			return Type<T>::ConvertToString(m_Value.Get());
		}

		virtual void SetString(const PLGeneral::String &sValue)
		{
			m_Value.Set(Type<T>::ConvertFromString(sValue));
		}


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Variable value
		VarAccess<_Type, ACCESS, STORAGE> m_Value;	/**< Value storage and access */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_VAR_H__
