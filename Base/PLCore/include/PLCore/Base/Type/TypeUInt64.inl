/*********************************************************\
 *  File: TypeUInt64.inl                                 *
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


#ifndef __PLCORE_TYPE_UINT64_INL__
#define __PLCORE_TYPE_UINT64_INL__
#pragma once


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for 'uint64'
*/
template <>
class Type<uint64> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef uint64 _Type;			/**< Real type */
		typedef uint64 _StorageType;	/**< Storage type, for this type identical to the real type */

		// Type ID
		static const uint32 TypeID = TypeUInt64;

		// Get type name
		static String GetTypeName()
		{
			return "uint64";
		}

		// Convert var to uint64
		static uint64 ConvertFromVar(const DynVar *pValue)
		{
			return pValue->GetUInt64();
		}

		// Convert uint64 to bool
		static bool ConvertToBool(uint64 nValue)
		{
			return static_cast<bool>(nValue != 0);
		}

		// Convert bool to uint64
		static uint64 ConvertFromBool(bool bValue)
		{
			return static_cast<uint64>(bValue);
		}

		// Convert uint64 to int
		static int ConvertToInt(uint64 nValue)
		{
			return static_cast<int>(nValue);
		}

		// Convert int to uint64
		static uint64 ConvertFromInt(int nValue)
		{
			return static_cast<uint64>(nValue);
		}

		// Convert uint64 to int8
		static int8 ConvertToInt8(uint64 nValue)
		{
			return static_cast<int8>(nValue);
		}

		// Convert int8 to uint64
		static uint64 ConvertFromInt8(int8 nValue)
		{
			return static_cast<uint64>(nValue);
		}

		// Convert uint64 to int16
		static int16 ConvertToInt16(uint64 nValue)
		{
			return static_cast<int16>(nValue);
		}

		// Convert int16 to uint64
		static uint64 ConvertFromInt16(int16 nValue)
		{
			return static_cast<uint64>(nValue);
		}

		// Convert uint64 to int32
		static int32 ConvertToInt32(uint64 nValue)
		{
			return static_cast<int32>(nValue);
		}

		// Convert int32 to uint64
		static uint64 ConvertFromInt32(int32 nValue)
		{
			return static_cast<uint64>(nValue);
		}

		// Convert uint64 to int64
		static int64 ConvertToInt64(uint64 nValue)
		{
			return static_cast<int64>(nValue);
		}

		// Convert int64 to uint64
		static uint64 ConvertFromInt64(int64 nValue)
		{
			return static_cast<uint64>(nValue);
		}

		// Convert uint64 to uint8
		static uint8 ConvertToUInt8(uint64 nValue)
		{
			return static_cast<uint8>(nValue);
		}

		// Convert uint8 to uint64
		static uint64 ConvertFromUInt8(uint8 nValue)
		{
			return static_cast<uint64>(nValue);
		}

		// Convert uint64 to uint16
		static uint16 ConvertToUInt16(uint64 nValue)
		{
			return static_cast<uint16>(nValue);
		}

		// Convert uint16 to uint64
		static uint64 ConvertFromUInt16(uint16 nValue)
		{
			return static_cast<uint64>(nValue);
		}

		// Convert uint64 to uint32
		static uint32 ConvertToUInt32(uint64 nValue)
		{
			return static_cast<uint32>(nValue);
		}

		// Convert uint32 to uint64
		static uint64 ConvertFromUInt32(uint32 nValue)
		{
			return static_cast<uint64>(nValue);
		}

		// Convert uint64 to uint64
		static uint64 ConvertToUInt64(uint64 nValue)
		{
			return static_cast<uint64>(nValue);
		}

		// Convert uint64 to uint64
		static uint64 ConvertFromUInt64(uint64 nValue)
		{
			return static_cast<uint64>(nValue);
		}

		// Convert uint64 to uint_ptr
		static uint_ptr ConvertToUIntPtr(uint64 nValue)
		{
			return static_cast<uint_ptr>(nValue);
		}

		// Convert uint_ptr to uint64
		static uint64 ConvertFromUIntPtr(uint_ptr nValue)
		{
			return static_cast<uint64>(nValue);
		}

		// Convert uint64 to float
		static float ConvertToFloat(uint64 nValue)
		{
			return static_cast<float>(nValue);
		}

		// Convert float to uint64
		static uint64 ConvertFromFloat(float fValue)
		{
			return static_cast<uint64>(fValue);
		}

		// Convert uint64 to double
		static double ConvertToDouble(uint64 nValue)
		{
			return static_cast<double>(nValue);
		}

		// Convert double to uint64
		static uint64 ConvertFromDouble(double dValue)
		{
			return static_cast<uint64>(dValue);
		}

		// Convert uint64 to string
		static String ConvertToString(uint64 nValue)
		{
			return String() + static_cast<int>(nValue);
		}

		// Convert string to uint64
		static uint64 ConvertFromString(const String &sString)
		{
			return sString.GetInt();
		}

		// Convert real to storage type
		static uint64 ConvertRealToStorage(uint64 nValue)
		{
			return nValue;
		}

		// Convert storage to real type
		static uint64 ConvertStorageToReal(uint64 nValue)
		{
			return nValue;
		}

};


#endif // __PLCORE_TYPE_UINTPTR_INL__
