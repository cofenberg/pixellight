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
		virtual DynTypeInfo &GetType() const override
		{
			return TypeInfo<T>::Instance;
		}

		virtual String GetTypeName() const override
		{
			return Type<T>::GetTypeName();
		}

		virtual int GetTypeID() const override
		{
			return Type<T>::TypeID;
		}

		virtual bool IsDefault() const override
		{
			return (m_Value.Get() == m_Value.GetDefault());
		}

		virtual void SetDefault() override
		{
			m_Value.Set(m_Value.GetDefault());
		}

		virtual String GetDefault() const override
		{
			return Type<T>::ConvertToString(m_Value.GetDefault());
		}

		virtual void SetVar(const DynVar &cValue) override
		{
			m_Value.Set(Type<T>::ConvertFromVar(cValue));
		}

		virtual bool GetBool() const override
		{
			return Type<T>::ConvertToBool(m_Value.Get());
		}

		virtual void SetBool(bool bValue) override
		{
			m_Value.Set(Type<T>::ConvertFromBool(bValue));
		}

		virtual int GetInt() const override
		{
			return Type<T>::ConvertToInt(m_Value.Get());
		}

		virtual void SetInt(int nValue) override
		{
			m_Value.Set(Type<T>::ConvertFromInt(nValue));
		}

		virtual int8 GetInt8() const override
		{
			return Type<T>::ConvertToInt8(m_Value.Get());
		}

		virtual void SetInt8(int8 nValue) override
		{
			m_Value.Set(Type<T>::ConvertFromInt8(nValue));
		}

		virtual int16 GetInt16() const override
		{
			return Type<T>::ConvertToInt16(m_Value.Get());
		}

		virtual void SetInt16(int16 nValue) override
		{
			m_Value.Set(Type<T>::ConvertFromInt16(nValue));
		}

		virtual int32 GetInt32() const override
		{
			return Type<T>::ConvertToInt32(m_Value.Get());
		}

		virtual void SetInt32(int32 nValue) override
		{
			m_Value.Set(Type<T>::ConvertFromInt32(nValue));
		}

		virtual int64 GetInt64() const override
		{
			return Type<T>::ConvertToInt64(m_Value.Get());
		}

		virtual void SetInt64(int64 nValue) override
		{
			m_Value.Set(Type<T>::ConvertFromInt64(nValue));
		}

		virtual uint8 GetUInt8() const override
		{
			return Type<T>::ConvertToUInt8(m_Value.Get());
		}

		virtual void SetUInt8(uint8 nValue) override
		{
			m_Value.Set(Type<T>::ConvertFromUInt8(nValue));
		}

		virtual uint16 GetUInt16() const override
		{
			return Type<T>::ConvertToUInt16(m_Value.Get());
		}

		virtual void SetUInt16(uint16 nValue) override
		{
			m_Value.Set(Type<T>::ConvertFromUInt16(nValue));
		}

		virtual uint32 GetUInt32() const override
		{
			return Type<T>::ConvertToUInt32(m_Value.Get());
		}

		virtual void SetUInt32(uint32 nValue) override
		{
			m_Value.Set(Type<T>::ConvertFromUInt32(nValue));
		}

		virtual uint64 GetUInt64() const override
		{
			return Type<T>::ConvertToUInt64(m_Value.Get());
		}

		virtual void SetUInt64(uint64 nValue) override
		{
			m_Value.Set(Type<T>::ConvertFromUInt64(nValue));
		}

		virtual uint_ptr GetUIntPtr() const override
		{
			return Type<T>::ConvertToUIntPtr(m_Value.Get());
		}

		virtual void SetUIntPtr(uint_ptr nValue) override
		{
			m_Value.Set(Type<T>::ConvertFromUIntPtr(nValue));
		}

		virtual float GetFloat() const override
		{
			return Type<T>::ConvertToFloat(m_Value.Get());
		}

		virtual void SetFloat(float fValue) override
		{
			m_Value.Set(Type<T>::ConvertFromFloat(fValue));
		}

		virtual double GetDouble() const override
		{
			return Type<T>::ConvertToDouble(m_Value.Get());
		}

		virtual void SetDouble(double dValue) override
		{
			m_Value.Set(Type<T>::ConvertFromDouble(dValue));
		}

		virtual String GetString() const override
		{
			return Type<T>::ConvertToString(m_Value.Get());
		}

		virtual void SetString(const String &sValue) override
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
