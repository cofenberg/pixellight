/*********************************************************\
 *  File: TypeEnumPlain.inl                              *
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


#ifndef __PLCORE_TYPE_ENUMPLAIN_INL__
#define __PLCORE_TYPE_ENUMPLAIN_INL__
#pragma once


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for enum types
*/
template <typename ENUM>
class Type< EnumTypePlain<ENUM> > {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef ENUM _Type;			/**< Real type */
		typedef ENUM _StorageType;	/**< Storage type, for this type identical to the real type */

		// Type ID
		static const int TypeID = Type<int>::TypeID;

		// Get type name
		static String GetTypeName()
		{
			return Type<int>::GetTypeName();
		}

		// Convert var to type
		static ENUM ConvertFromVar(const DynVar &cValue)
		{
			return static_cast<ENUM>(Type<int>::ConvertFromVar(cValue));
		}

		// Convert type to bool
		static bool ConvertToBool(ENUM Value)
		{
			return Type<int>::ConvertToBool(static_cast<int>(Value));
		}

		// Convert bool to type
		static ENUM ConvertFromBool(bool bValue)
		{
			return static_cast<ENUM>(Type<int>::ConvertFromBool(bValue));
		}

		// Convert type to int
		static int ConvertToInt(ENUM Value)
		{
			return Type<int>::ConvertToInt(static_cast<int>(Value));
		}

		// Convert int to type
		static ENUM ConvertFromInt(int nValue)
		{
			return static_cast<ENUM>(Type<int>::ConvertFromInt(nValue));
		}

		// Convert type to int8
		static int8 ConvertToInt8(ENUM Value)
		{
			return Type<int>::ConvertToInt8(static_cast<int>(Value));
		}

		// Convert int8 to type
		static ENUM ConvertFromInt8(int8 nValue)
		{
			return static_cast<ENUM>(Type<int>::ConvertFromInt8(nValue));
		}

		// Convert type to int16
		static int16 ConvertToInt16(ENUM Value)
		{
			return Type<int>::ConvertToInt16(static_cast<int>(Value));
		}

		// Convert int16 to type
		static ENUM ConvertFromInt16(int16 nValue)
		{
			return static_cast<ENUM>(Type<int>::ConvertFromInt16(nValue));
		}

		// Convert type to int32
		static int32 ConvertToInt32(ENUM Value)
		{
			return Type<int>::ConvertToInt32(static_cast<int>(Value));
		}

		// Convert int32 to type
		static ENUM ConvertFromInt32(int32 nValue)
		{
			return static_cast<ENUM>(Type<int>::ConvertFromInt32(nValue));
		}

		// Convert type to int64
		static int64 ConvertToInt64(ENUM Value)
		{
			return Type<int>::ConvertToInt64(static_cast<int>(Value));
		}

		// Convert int64 to type
		static ENUM ConvertFromInt64(int64 nValue)
		{
			return static_cast<ENUM>(Type<int>::ConvertFromInt64(nValue));
		}

		// Convert type to uint8
		static uint8 ConvertToUInt8(ENUM Value)
		{
			return Type<int>::ConvertToUInt8(static_cast<int>(Value));
		}

		// Convert uint8 to type
		static ENUM ConvertFromUInt8(uint8 nValue)
		{
			return static_cast<ENUM>(Type<int>::ConvertFromUInt8(nValue));
		}

		// Convert type to uint16
		static uint16 ConvertToUInt16(ENUM Value)
		{
			return Type<int>::ConvertToUInt16(static_cast<int>(Value));
		}

		// Convert uint16 to type
		static ENUM ConvertFromUInt16(uint16 nValue)
		{
			return static_cast<ENUM>(Type<int>::ConvertFromUInt16(nValue));
		}

		// Convert type to uint32
		static uint32 ConvertToUInt32(ENUM Value)
		{
			return Type<int>::ConvertToUInt32(static_cast<int>(Value));
		}

		// Convert uint32 to type
		static ENUM ConvertFromUInt32(uint32 nValue)
		{
			return static_cast<ENUM>(Type<int>::ConvertFromUInt32(nValue));
		}

		// Convert type to uint64
		static uint64 ConvertToUInt64(ENUM Value)
		{
			return Type<int>::ConvertToUInt64(static_cast<int>(Value));
		}

		// Convert uint64 to type
		static ENUM ConvertFromUInt64(uint64 nValue)
		{
			return static_cast<ENUM>(Type<int>::ConvertFromUInt64(nValue));
		}

		// Convert type to uint_ptr
		static uint_ptr ConvertToUIntPtr(ENUM Value)
		{
			return Type<int>::ConvertToUIntPtr(static_cast<int>(Value));
		}

		// Convert uint_ptr to type
		static ENUM ConvertFromUIntPtr(uint_ptr nValue)
		{
			return static_cast<ENUM>(Type<int>::ConvertFromUIntPtr(nValue));
		}

		// Convert type to float
		static float ConvertToFloat(ENUM Value)
		{
			return Type<int>::ConvertToFloat(static_cast<int>(Value));
		}

		// Convert float to type
		static ENUM ConvertFromFloat(float fValue)
		{
			return static_cast<ENUM>(Type<int>::ConvertFromFloat(fValue));
		}

		// Convert type to double
		static double ConvertToDouble(ENUM Value)
		{
			return Type<int>::ConvertToDouble(static_cast<int>(Value));
		}

		// Convert double to type
		static ENUM ConvertFromDouble(double dValue)
		{
			return static_cast<ENUM>(Type<int>::ConvertFromDouble(dValue));
		}

		// Convert type to string
		static String ConvertToString(ENUM Value)
		{
			return Type<int>::ConvertToString(static_cast<int>(Value));
		}

		// Convert string to type
		static ENUM ConvertFromString(const String &sString)
		{
			return static_cast<ENUM>(Type<int>::ConvertFromString(sString));
		}

		// Convert real to storage type
		static _StorageType ConvertRealToStorage(_Type nValue)
		{
			return nValue;
		}

		// Convert storage to real type
		static _Type ConvertStorageToReal(_StorageType nValue)
		{
			return nValue;
		}

};


#endif // __PLCORE_TYPE_ENUMPLAIN_INL__
