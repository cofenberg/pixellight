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
class Type<PLGeneral::uint64> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef PLGeneral::uint64 _Type;		/**< Real type */
		typedef PLGeneral::uint64 _StorageType;	/**< Storage type, for this type identical to the real type */

		// Type ID
		static const PLGeneral::uint32 TypeID = TypeUInt64;

		// Get type name
		static PLGeneral::String GetTypeName()
		{
			return "uint64";
		}

		// Convert var to uint64
		static PLGeneral::uint64 ConvertFromVar(const DynVar *pValue)
		{
			return pValue->GetUInt64();
		}

		// Convert uint64 to bool
		static bool ConvertToBool(PLGeneral::uint64 nValue)
		{
			return static_cast<bool>(nValue != 0);
		}

		// Convert bool to uint64
		static PLGeneral::uint64 ConvertFromBool(bool bValue)
		{
			return static_cast<PLGeneral::uint64>(bValue);
		}

		// Convert uint64 to int
		static int ConvertToInt(PLGeneral::uint64 nValue)
		{
			return static_cast<int>(nValue);
		}

		// Convert int to uint64
		static PLGeneral::uint64 ConvertFromInt(int nValue)
		{
			return static_cast<PLGeneral::uint64>(nValue);
		}

		// Convert uint64 to int8
		static PLGeneral::int8 ConvertToInt8(PLGeneral::uint64 nValue)
		{
			return static_cast<PLGeneral::int8>(nValue);
		}

		// Convert int8 to uint64
		static PLGeneral::uint64 ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return static_cast<PLGeneral::uint64>(nValue);
		}

		// Convert uint64 to int16
		static PLGeneral::int16 ConvertToInt16(PLGeneral::uint64 nValue)
		{
			return static_cast<PLGeneral::int16>(nValue);
		}

		// Convert int16 to uint64
		static PLGeneral::uint64 ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return static_cast<PLGeneral::uint64>(nValue);
		}

		// Convert uint64 to int32
		static PLGeneral::int32 ConvertToInt32(PLGeneral::uint64 nValue)
		{
			return static_cast<PLGeneral::int32>(nValue);
		}

		// Convert int32 to uint64
		static PLGeneral::uint64 ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return static_cast<PLGeneral::uint64>(nValue);
		}

		// Convert uint64 to int64
		static PLGeneral::int64 ConvertToInt64(PLGeneral::uint64 nValue)
		{
			return static_cast<PLGeneral::int64>(nValue);
		}

		// Convert int64 to uint64
		static PLGeneral::uint64 ConvertFromInt64(PLGeneral::int64 nValue)
		{
			return static_cast<PLGeneral::uint64>(nValue);
		}

		// Convert uint64 to uint8
		static PLGeneral::uint8 ConvertToUInt8(PLGeneral::uint64 nValue)
		{
			return static_cast<PLGeneral::uint8>(nValue);
		}

		// Convert uint8 to uint64
		static PLGeneral::uint64 ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return static_cast<PLGeneral::uint64>(nValue);
		}

		// Convert uint64 to uint16
		static PLGeneral::uint16 ConvertToUInt16(PLGeneral::uint64 nValue)
		{
			return static_cast<PLGeneral::uint16>(nValue);
		}

		// Convert uint16 to uint64
		static PLGeneral::uint64 ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return static_cast<PLGeneral::uint64>(nValue);
		}

		// Convert uint64 to uint32
		static PLGeneral::uint32 ConvertToUInt32(PLGeneral::uint64 nValue)
		{
			return static_cast<PLGeneral::uint32>(nValue);
		}

		// Convert uint32 to uint64
		static PLGeneral::uint64 ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return static_cast<PLGeneral::uint64>(nValue);
		}

		// Convert uint64 to uint64
		static PLGeneral::uint64 ConvertToUInt64(PLGeneral::uint64 nValue)
		{
			return static_cast<PLGeneral::uint64>(nValue);
		}

		// Convert uint64 to uint64
		static PLGeneral::uint64 ConvertFromUInt64(PLGeneral::uint64 nValue)
		{
			return static_cast<PLGeneral::uint64>(nValue);
		}

		// Convert uint64 to uint_ptr
		static PLGeneral::uint_ptr ConvertToUIntPtr(PLGeneral::uint64 nValue)
		{
			return static_cast<PLGeneral::uint_ptr>(nValue);
		}

		// Convert uint_ptr to uint64
		static PLGeneral::uint64 ConvertFromUIntPtr(PLGeneral::uint_ptr nValue)
		{
			return static_cast<PLGeneral::uint64>(nValue);
		}

		// Convert uint64 to float
		static float ConvertToFloat(PLGeneral::uint64 nValue)
		{
			return static_cast<float>(nValue);
		}

		// Convert float to uint64
		static PLGeneral::uint64 ConvertFromFloat(float fValue)
		{
			return static_cast<PLGeneral::uint64>(fValue);
		}

		// Convert uint64 to double
		static double ConvertToDouble(PLGeneral::uint64 nValue)
		{
			return static_cast<double>(nValue);
		}

		// Convert double to uint64
		static PLGeneral::uint64 ConvertFromDouble(double dValue)
		{
			return static_cast<PLGeneral::uint64>(dValue);
		}

		// Convert uint64 to string
		static PLGeneral::String ConvertToString(PLGeneral::uint64 nValue)
		{
			return PLGeneral::String() + static_cast<int>(nValue);
		}

		// Convert string to PLGeneral::uint64
		static PLGeneral::uint64 ConvertFromString(const PLGeneral::String &sString)
		{
			return sString.GetInt();
		}

		// Convert real to storage type
		static PLGeneral::uint64 ConvertRealToStorage(PLGeneral::uint64 nValue)
		{
			return nValue;
		}

		// Convert storage to real type
		static PLGeneral::uint64 ConvertStorageToReal(PLGeneral::uint64 nValue)
		{
			return nValue;
		}

};


#endif // __PLCORE_TYPE_UINTPTR_INL__
