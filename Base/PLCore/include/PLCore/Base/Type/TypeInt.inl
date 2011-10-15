/*********************************************************\
 *  File: TypeInt.inl                                    *
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


#ifndef __PLCORE_TYPE_INT_INL__
#define __PLCORE_TYPE_INT_INL__
#pragma once


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for 'int'
*/
template <>
class Type<int> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef int _Type;			/**< Real type */
		typedef int _StorageType;	/**< Storage type, for this type identical to the real type */

		// Type ID
		static const int TypeID = TypeInt;

		// Get type name
		static String GetTypeName()
		{
			return "int";
		}

		// Convert var to int
		static int ConvertFromVar(const DynVar &cValue)
		{
			return cValue.GetInt();
		}

		// Convert int to bool
		static bool ConvertToBool(int nValue)
		{
			return static_cast<bool>(nValue != 0);
		}

		// Convert bool to int
		static int ConvertFromBool(bool bValue)
		{
			return static_cast<int>(bValue);
		}

		// Convert int to int
		static int ConvertToInt(int nValue)
		{
			return static_cast<int>(nValue);
		}

		// Convert int to int
		static int ConvertFromInt(int nValue)
		{
			return static_cast<int>(nValue);
		}

		// Convert int to int8
		static int8 ConvertToInt8(int nValue)
		{
			return static_cast<int8>(nValue);
		}

		// Convert int8 to int
		static int ConvertFromInt8(int8 nValue)
		{
			return static_cast<int>(nValue);
		}

		// Convert int to int16
		static int16 ConvertToInt16(int nValue)
		{
			return static_cast<int16>(nValue);
		}

		// Convert int16 to int
		static int ConvertFromInt16(int16 nValue)
		{
			return static_cast<int>(nValue);
		}

		// Convert int to int32
		static int32 ConvertToInt32(int nValue)
		{
			return static_cast<int32>(nValue);
		}

		// Convert int32 to int
		static int ConvertFromInt32(int32 nValue)
		{
			return static_cast<int>(nValue);
		}

		// Convert int to int64
		static int64 ConvertToInt64(int nValue)
		{
			return static_cast<int64>(nValue);
		}

		// Convert int64 to int
		static int ConvertFromInt64(int64 nValue)
		{
			return static_cast<int>(nValue);
		}

		// Convert int to uint8
		static uint8 ConvertToUInt8(int nValue)
		{
			return static_cast<uint8>(nValue);
		}

		// Convert uint8 to int
		static int ConvertFromUInt8(uint8 nValue)
		{
			return static_cast<int>(nValue);
		}

		// Convert int to uint16
		static uint16 ConvertToUInt16(int nValue)
		{
			return static_cast<uint16>(nValue);
		}

		// Convert uint16 to int
		static int ConvertFromUInt16(uint16 nValue)
		{
			return static_cast<int>(nValue);
		}

		// Convert int to uint32
		static uint32 ConvertToUInt32(int nValue)
		{
			return static_cast<uint32>(nValue);
		}

		// Convert uint32 to int
		static int ConvertFromUInt32(uint32 nValue)
		{
			return static_cast<int>(nValue);
		}

		// Convert int to uint64
		static uint64 ConvertToUInt64(int nValue)
		{
			return static_cast<uint64>(nValue);
		}

		// Convert uint64 to int
		static int ConvertFromUInt64(uint64 nValue)
		{
			return static_cast<int>(nValue);
		}

		// Convert int to uint_ptr
		static uint_ptr ConvertToUIntPtr(int nValue)
		{
			return static_cast<uint_ptr>(nValue);
		}

		// Convert uint_ptr to int
		static int ConvertFromUIntPtr(uint_ptr nValue)
		{
			return static_cast<int>(nValue);
		}

		// Convert int to float
		static float ConvertToFloat(int nValue)
		{
			return static_cast<float>(nValue);
		}

		// Convert float to int
		static int ConvertFromFloat(float fValue)
		{
			return static_cast<int>(fValue);
		}

		// Convert int to double
		static double ConvertToDouble(int nValue)
		{
			return static_cast<double>(nValue);
		}

		// Convert double to int
		static int ConvertFromDouble(double dValue)
		{
			return static_cast<int>(dValue);
		}

		// Convert int to string
		static String ConvertToString(int nValue)
		{
			return String() + nValue;
		}

		// Convert string to int
		static int ConvertFromString(const String &sString)
		{
			return sString.GetInt();
		}

		// Convert real to storage type
		static int ConvertRealToStorage(int nValue)
		{
			return nValue;
		}

		// Convert storage to real type
		static int ConvertStorageToReal(int nValue)
		{
			return nValue;
		}

};


#endif // __PLCORE_TYPE_INT_INL__
