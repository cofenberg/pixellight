/*********************************************************\
 *  File: TypeString.inl                                 *
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


#ifndef __PLCORE_TYPE_STRING_INL__
#define __PLCORE_TYPE_STRING_INL__
#pragma once


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for 'String'
*/
template <>
class Type<PLGeneral::String> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef PLGeneral::String _Type;

		// Type ID
		static const int TypeID = TypeString;

		// Get type name
		static PLGeneral::String GetTypeName() {
			return "string";
		}

		// Convert var to string
		static PLGeneral::String ConvertFromVar(const DynVar *pValue)
		{
			return pValue->GetString();
		}

		// Convert string to bool
		static bool ConvertToBool(const PLGeneral::String &sString)
		{
			return sString.GetBool();
		}

		// Convert bool to string
		static PLGeneral::String ConvertFromBool(bool bValue)
		{
			return (PLGeneral::String() + bValue);
		}

		// Convert string to int
		static int ConvertToInt(const PLGeneral::String &sString)
		{
			return sString.GetInt();
		}

		// Convert int to string
		static PLGeneral::String ConvertFromInt(int nValue)
		{
			return (PLGeneral::String() + nValue);
		}

		// Convert string to int8
		static PLGeneral::int8 ConvertToInt8(const PLGeneral::String &sString)
		{
			return (PLGeneral::int8)sString.GetInt();
		}

		// Convert int8 to string
		static PLGeneral::String ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return (PLGeneral::String() + (int)nValue);
		}

		// Convert string to int16
		static PLGeneral::int16 ConvertToInt16(const PLGeneral::String &sString)
		{
			return (PLGeneral::int16)sString.GetInt();
		}

		// Convert int16 to string
		static PLGeneral::String ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return (PLGeneral::String() + (int)nValue);
		}

		// Convert string to int32
		static PLGeneral::int32 ConvertToInt32(const PLGeneral::String &sString)
		{
			return (PLGeneral::int32)sString.GetInt();
		}

		// Convert int32 to string
		static PLGeneral::String ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return (PLGeneral::String() + (int)nValue);
		}

		// Convert string to int64
		static PLGeneral::int64 ConvertToInt64(const PLGeneral::String &sString)
		{
			return (PLGeneral::int64)sString.GetInt();
		}

		// Convert int64 to string
		static PLGeneral::String ConvertFromInt64(PLGeneral::int64 nValue)
		{
			return (PLGeneral::String() + (int)nValue);
		}

		// Convert string to uint8
		static PLGeneral::uint8 ConvertToUInt8(const PLGeneral::String &sString)
		{
			return (PLGeneral::uint8)sString.GetInt();
		}

		// Convert uint8 to string
		static PLGeneral::String ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return (PLGeneral::String() + (int)nValue);
		}

		// Convert string to uint16
		static PLGeneral::uint16 ConvertToUInt16(const PLGeneral::String &sString)
		{
			return (PLGeneral::uint16)sString.GetInt();
		}

		// Convert uint16 to string
		static PLGeneral::String ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return (PLGeneral::String() + (int)nValue);
		}

		// Convert string to uint32
		static PLGeneral::uint32 ConvertToUInt32(const PLGeneral::String &sString)
		{
			return (PLGeneral::uint32)sString.GetInt();
		}

		// Convert uint32 to string
		static PLGeneral::String ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return (PLGeneral::String() + (int)nValue);
		}

		// Convert string to uint64
		static PLGeneral::uint64 ConvertToUInt64(const PLGeneral::String &sString)
		{
			return (PLGeneral::uint64)sString.GetInt();
		}

		// Convert uint64 to string
		static PLGeneral::String ConvertFromUInt64(PLGeneral::uint64 nValue)
		{
			return (PLGeneral::String() + (int)nValue);
		}

		// Convert string to uint_ptr
		static PLGeneral::uint_ptr ConvertToUIntPtr(const PLGeneral::String &sString)
		{
			return (PLGeneral::uint_ptr)sString.GetInt();
		}

		// Convert uint_ptr to string
		static PLGeneral::String ConvertFromUIntPtr(PLGeneral::uint_ptr nValue)
		{
			return (PLGeneral::String() + (int)nValue);
		}

		// Convert string to float
		static float ConvertToFloat(const PLGeneral::String &sString)
		{
			return sString.GetFloat();
		}

		// Convert float to string
		static PLGeneral::String ConvertFromFloat(float fValue)
		{
			return (PLGeneral::String() + fValue);
		}

		// Convert string to double
		static double ConvertToDouble(const PLGeneral::String &sString)
		{
			return sString.GetDouble();
		}

		// Convert double to string
		static PLGeneral::String ConvertFromDouble(double dValue)
		{
			return (PLGeneral::String() + dValue);
		}

		// Convert string to string
		static PLGeneral::String ConvertToString(const PLGeneral::String &sString)
		{
			return sString;
		}

		// Convert string to string
		static PLGeneral::String ConvertFromString(const PLGeneral::String &sString)
		{
			return sString;
		}


};


#endif // __PLCORE_TYPE_STRING_INL__
