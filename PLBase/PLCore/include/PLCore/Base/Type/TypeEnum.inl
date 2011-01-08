/*********************************************************\
 *  File: TypeEnum.inl                                   *
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


#ifndef __PLCORE_TYPE_ENUM_INL__
#define __PLCORE_TYPE_ENUM_INL__
#pragma once


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for enum types
*/
template <typename ENUM>
class Type< EnumType<ENUM> > {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef typename ENUM::_BaseType _BaseType;
		typedef typename ENUM::_Type	 _Type;

		// Type ID
		static const int TypeID = Type<_BaseType>::TypeID;

		// Get type name
		static PLGeneral::String GetTypeName() {
			return Type<_BaseType>::GetTypeName();
		}

		// Convert var to type
		static _Type ConvertFromVar(const DynVar *pValue)
		{
			if (pValue->GetTypeID() == TypeString)
				return ConvertFromString(pValue->GetString());
			else
				return (_Type)Type<_BaseType>::ConvertFromVar(pValue);
		}

		// Convert type to bool
		static bool ConvertToBool(_Type Value)
		{
			return Type<_BaseType>::ConvertToBool((_BaseType)Value);
		}

		// Convert bool to type
		static _Type ConvertFromBool(bool bValue)
		{
			return (_Type)Type<_BaseType>::ConvertFromBool(bValue);
		}

		// Convert type to int
		static int ConvertToInt(_Type Value)
		{
			return Type<_BaseType>::ConvertToInt((_BaseType)Value);
		}

		// Convert int to type
		static _Type ConvertFromInt(int nValue)
		{
			return (_Type)Type<_BaseType>::ConvertFromInt(nValue);
		}

		// Convert type to int8
		static PLGeneral::int8 ConvertToInt8(_Type Value)
		{
			return Type<_BaseType>::ConvertToInt8((_BaseType)Value);
		}

		// Convert int8 to type
		static _Type ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return (_Type)Type<_BaseType>::ConvertFromInt8(nValue);
		}

		// Convert type to int16
		static PLGeneral::int16 ConvertToInt16(_Type Value)
		{
			return Type<_BaseType>::ConvertToInt16((_BaseType)Value);
		}

		// Convert int16 to type
		static _Type ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return (_Type)Type<_BaseType>::ConvertFromInt16(nValue);
		}

		// Convert type to int32
		static PLGeneral::int32 ConvertToInt32(_Type Value)
		{
			return Type<_BaseType>::ConvertToInt32((_BaseType)Value);
		}

		// Convert int32 to type
		static _Type ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return (_Type)Type<_BaseType>::ConvertFromInt32(nValue);
		}

		// Convert type to int64
		static PLGeneral::int64 ConvertToInt64(_Type Value)
		{
			return Type<_BaseType>::ConvertToInt64((_BaseType)Value);
		}

		// Convert int64 to type
		static _Type ConvertFromInt64(PLGeneral::int64 nValue)
		{
			return (_Type)Type<_BaseType>::ConvertFromInt64(nValue);
		}

		// Convert type to uint8
		static PLGeneral::uint8 ConvertToUInt8(_Type Value)
		{
			return Type<_BaseType>::ConvertToUInt8((_BaseType)Value);
		}

		// Convert uint8 to type
		static _Type ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return (_Type)Type<_BaseType>::ConvertFromUInt8(nValue);
		}

		// Convert type to uint16
		static PLGeneral::uint16 ConvertToUInt16(_Type Value)
		{
			return Type<_BaseType>::ConvertToUInt16((_BaseType)Value);
		}

		// Convert uint16 to type
		static _Type ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return (_Type)Type<_BaseType>::ConvertFromUInt16(nValue);
		}

		// Convert type to uint32
		static PLGeneral::uint32 ConvertToUInt32(_Type Value)
		{
			return Type<_BaseType>::ConvertToUInt32((_BaseType)Value);
		}

		// Convert uint32 to type
		static _Type ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return (_Type)Type<_BaseType>::ConvertFromUInt32(nValue);
		}

		// Convert type to uint64
		static PLGeneral::uint64 ConvertToUInt64(_Type Value)
		{
			return Type<_BaseType>::ConvertToUInt64((_BaseType)Value);
		}

		// Convert uint64 to type
		static _Type ConvertFromUInt64(PLGeneral::uint64 nValue)
		{
			return (_Type)Type<_BaseType>::ConvertFromUInt64(nValue);
		}

		// Convert type to uint_ptr
		static PLGeneral::uint_ptr ConvertToUIntPtr(_Type Value)
		{
			return Type<_BaseType>::ConvertToUIntPtr((_BaseType)Value);
		}

		// Convert uint_ptr to type
		static _Type ConvertFromUIntPtr(PLGeneral::uint_ptr nValue)
		{
			return (_Type)Type<_BaseType>::ConvertFromUIntPtr(nValue);
		}

		// Convert type to float
		static float ConvertToFloat(_Type Value)
		{
			return Type<_BaseType>::ConvertToFloat((_BaseType)Value);
		}

		// Convert float to type
		static _Type ConvertFromFloat(float fValue)
		{
			return (_Type)Type<_BaseType>::ConvertFromFloat(fValue);
		}

		// Convert type to double
		static double ConvertToDouble(_Type Value)
		{
			return Type<_BaseType>::ConvertToDouble((_BaseType)Value);
		}

		// Convert double to type
		static _Type ConvertFromDouble(double dValue)
		{
			return (_Type)Type<_BaseType>::ConvertFromDouble(dValue);
		}

		// Convert type to string
		static PLGeneral::String ConvertToString(_Type Value)
		{
			PLGeneral::String sValue, sDesc;
			if (ENUM::GetEnumValue(-1, Value, sValue, sDesc))
				return sValue;
			else
				return Type<_BaseType>::ConvertToString((_BaseType)Value);
		}

		// Convert string to type
		static _Type ConvertFromString(const PLGeneral::String &sString)
		{
			PLGeneral::String sValue = sString;
			PLGeneral::String sDesc;
			_Type Value;
			if (ENUM::GetEnumValue(-1, Value, sValue, sDesc))
				return Value;
			else
				return (_Type)Type<_BaseType>::ConvertFromString(sString);
		}


};


#endif // __PLCORE_TYPE_ENUM_INL__
