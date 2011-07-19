/*********************************************************\
 *  File: TypeFloat.inl                                  *
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


#ifndef __PLCORE_TYPE_FLOAT_INL__
#define __PLCORE_TYPE_FLOAT_INL__
#pragma once


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for 'float'
*/
template <>
class Type<float> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef float _Type;		/**< Real type */
		typedef float _StorageType;	/**< Storage type, for this type identical to the real type */

		// Type ID
		static const int TypeID = TypeFloat;

		// Get type name
		static String GetTypeName()
		{
			return "float";
		}

		// Convert var to float
		static float ConvertFromVar(const DynVar *pValue)
		{
			return pValue->GetFloat();
		}

		// Convert float to bool
		static bool ConvertToBool(float fValue)
		{
			return static_cast<bool>(fValue != 0.0f);
		}

		// Convert bool to float
		static float ConvertFromBool(bool bValue)
		{
			return static_cast<float>(bValue);
		}

		// Convert float to int
		static int ConvertToInt(float fValue)
		{
			return static_cast<int>(fValue);
		}

		// Convert int to float
		static float ConvertFromInt(int nValue)
		{
			return static_cast<float>(nValue);
		}

		// Convert float to int8
		static int8 ConvertToInt8(float fValue)
		{
			return static_cast<int8>(fValue);
		}

		// Convert int8 to float
		static float ConvertFromInt8(int8 nValue)
		{
			return static_cast<float>(nValue);
		}

		// Convert float to int16
		static int16 ConvertToInt16(float fValue)
		{
			return static_cast<int16>(fValue);
		}

		// Convert int16 to float
		static float ConvertFromInt16(int16 nValue)
		{
			return static_cast<float>(nValue);
		}

		// Convert float to int32
		static int32 ConvertToInt32(float fValue)
		{
			return static_cast<int32>(fValue);
		}

		// Convert int32 to float
		static float ConvertFromInt32(int32 nValue)
		{
			return static_cast<float>(nValue);
		}

		// Convert float to int64
		static int64 ConvertToInt64(float fValue)
		{
			return static_cast<int64>(fValue);
		}

		// Convert int64 to float
		static float ConvertFromInt64(int64 nValue)
		{
			return static_cast<float>(nValue);
		}

		// Convert float to uint8
		static uint8 ConvertToUInt8(float fValue)
		{
			return static_cast<uint8>(fValue);
		}

		// Convert uint8 to float
		static float ConvertFromUInt8(uint8 nValue)
		{
			return static_cast<float>(nValue);
		}

		// Convert float to uint16
		static uint16 ConvertToUInt16(float fValue)
		{
			return static_cast<uint16>(fValue);
		}

		// Convert uint16 to float
		static float ConvertFromUInt16(uint16 nValue)
		{
			return static_cast<float>(nValue);
		}

		// Convert float to uint32
		static uint32 ConvertToUInt32(float fValue)
		{
			return static_cast<uint32>(fValue);
		}

		// Convert uint32 to float
		static float ConvertFromUInt32(uint32 nValue)
		{
			return static_cast<float>(nValue);
		}

		// Convert float to uint64
		static uint64 ConvertToUInt64(float fValue)
		{
			return static_cast<uint64>(fValue);
		}

		// Convert uint64 to float
		static float ConvertFromUInt64(uint64 nValue)
		{
			return static_cast<float>(nValue);
		}

		// Convert float to uint_ptr
		static uint_ptr ConvertToUIntPtr(float fValue)
		{
			return static_cast<uint_ptr>(fValue);
		}

		// Convert uint_ptr to float
		static float ConvertFromUIntPtr(uint_ptr nValue)
		{
			return static_cast<float>(nValue);
		}

		// Convert float to float
		static float ConvertToFloat(float fValue)
		{
			return static_cast<float>(fValue);
		}

		// Convert float to float
		static float ConvertFromFloat(float fValue)
		{
			return static_cast<float>(fValue);
		}

		// Convert float to double
		static double ConvertToDouble(float fValue)
		{
			return static_cast<double>(fValue);
		}

		// Convert double to float
		static float ConvertFromDouble(double dValue)
		{
			return static_cast<float>(dValue);
		}

		// Convert float to string
		static String ConvertToString(float fValue)
		{
			return String() + fValue;
		}

		// Convert string to float
		static float ConvertFromString(const String &sString)
		{
			return sString.GetFloat();
		}

		// Convert real to storage type
		static float ConvertRealToStorage(float fValue)
		{
			return fValue;
		}

		// Convert storage to real type
		static float ConvertStorageToReal(float fValue)
		{
			return fValue;
		}

};


#endif // __PLCORE_TYPE_FLOAT_INL__
