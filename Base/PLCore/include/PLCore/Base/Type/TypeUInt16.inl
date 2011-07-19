/*********************************************************\
 *  File: TypeUInt16.inl                                 *
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


#ifndef __PLCORE_TYPE_UINT16_INL__
#define __PLCORE_TYPE_UINT16_INL__
#pragma once


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for 'uint16'
*/
template <>
class Type<uint16> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef uint16 _Type;			/**< Real type */
		typedef uint16 _StorageType;	/**< Storage type, for this type identical to the real type */

		// Type ID
		static const uint32 TypeID = TypeUInt16;

		// Get type name
		static String GetTypeName()
		{
			return "uint16";
		}

		// Convert var to uint16
		static uint16 ConvertFromVar(const DynVar *pValue)
		{
			return pValue->GetUInt16();
		}

		// Convert uint16 to bool
		static bool ConvertToBool(uint16 nValue)
		{
			return static_cast<bool>(nValue != 0);
		}

		// Convert bool to uint16
		static uint16 ConvertFromBool(bool bValue)
		{
			return static_cast<uint16>(bValue);
		}

		// Convert uint16 to int
		static int ConvertToInt(uint16 nValue)
		{
			return static_cast<int>(nValue);
		}

		// Convert int to uint16
		static uint16 ConvertFromInt(int nValue)
		{
			return static_cast<uint16>(nValue);
		}

		// Convert uint16 to int8
		static int8 ConvertToInt8(uint16 nValue)
		{
			return static_cast<int8>(nValue);
		}

		// Convert int8 to uint16
		static uint16 ConvertFromInt8(int8 nValue)
		{
			return static_cast<uint16>(nValue);
		}

		// Convert uint16 to int16
		static int16 ConvertToInt16(uint16 nValue)
		{
			return static_cast<int16>(nValue);
		}

		// Convert int16 to uint16
		static uint16 ConvertFromInt16(int16 nValue)
		{
			return static_cast<uint16>(nValue);
		}

		// Convert uint16 to int32
		static int32 ConvertToInt32(uint16 nValue)
		{
			return static_cast<int32>(nValue);
		}

		// Convert int32 to uint16
		static uint16 ConvertFromInt32(int32 nValue)
		{
			return static_cast<uint16>(nValue);
		}

		// Convert uint16 to int64
		static int64 ConvertToInt64(uint16 nValue)
		{
			return static_cast<int64>(nValue);
		}

		// Convert int64 to uint16
		static uint16 ConvertFromInt64(int64 nValue)
		{
			return static_cast<uint16>(nValue);
		}

		// Convert uint16 to uint8
		static uint8 ConvertToUInt8(uint16 nValue)
		{
			return static_cast<uint8>(nValue);
		}

		// Convert uint8 to uint16
		static uint16 ConvertFromUInt8(uint8 nValue)
		{
			return static_cast<uint16>(nValue);
		}

		// Convert uint16 to uint16
		static uint16 ConvertToUInt16(uint16 nValue)
		{
			return static_cast<uint16>(nValue);
		}

		// Convert uint16 to uint16
		static uint16 ConvertFromUInt16(uint16 nValue)
		{
			return static_cast<uint16>(nValue);
		}

		// Convert uint16 to uint32
		static uint32 ConvertToUInt32(uint16 nValue)
		{
			return static_cast<uint32>(nValue);
		}

		// Convert uint32 to uint16
		static uint16 ConvertFromUInt32(uint32 nValue)
		{
			return static_cast<uint16>(nValue);
		}

		// Convert uint16 to uint64
		static uint64 ConvertToUInt64(uint16 nValue)
		{
			return static_cast<uint64>(nValue);
		}

		// Convert uint64 to uint16
		static uint16 ConvertFromUInt64(uint64 nValue)
		{
			return static_cast<uint16>(nValue);
		}

		// Convert uint16 to uint_ptr
		static uint_ptr ConvertToUIntPtr(uint16 nValue)
		{
			return static_cast<uint_ptr>(nValue);
		}

		// Convert uint_ptr to uint16
		static uint16 ConvertFromUIntPtr(uint_ptr nValue)
		{
			return static_cast<uint16>(nValue);
		}

		// Convert uint16 to float
		static float ConvertToFloat(uint16 nValue)
		{
			return static_cast<float>(nValue);
		}

		// Convert float to uint16
		static uint16 ConvertFromFloat(float fValue)
		{
			return static_cast<uint16>(fValue);
		}

		// Convert uint16 to double
		static double ConvertToDouble(uint16 nValue)
		{
			return static_cast<double>(nValue);
		}

		// Convert double to uint16
		static uint16 ConvertFromDouble(double dValue)
		{
			return static_cast<uint16>(dValue);
		}

		// Convert uint16 to string
		static String ConvertToString(uint16 nValue)
		{
			return String() + static_cast<int>(nValue);
		}

		// Convert string to uint16
		static uint16 ConvertFromString(const String &sString)
		{
			return static_cast<uint16>(sString.GetInt());
		}

		// Convert real to storage type
		static uint16 ConvertRealToStorage(uint16 nValue)
		{
			return nValue;
		}

		// Convert storage to real type
		static uint16 ConvertStorageToReal(uint16 nValue)
		{
			return nValue;
		}

};


#endif // __PLCORE_TYPE_UINT16_INL__
