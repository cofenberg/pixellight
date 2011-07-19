/*********************************************************\
 *  File: TypeDouble.inl                                 *
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


#ifndef __PLCORE_TYPE_DOUBLE_INL__
#define __PLCORE_TYPE_DOUBLE_INL__
#pragma once


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for 'double'
*/
template <>
class Type<double> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef double _Type;			/**< Real type */
		typedef double _StorageType;	/**< Storage type, for this type identical to the real type */

		// Type ID
		static const int TypeID = TypeDouble;

		// Get type name
		static String GetTypeName()
		{
			return "double";
		}

		// Convert var to double
		static double ConvertFromVar(const DynVar *pValue)
		{
			return pValue->GetDouble();
		}

		// Convert double to bool
		static bool ConvertToBool(double dValue)
		{
			return static_cast<bool>(dValue != 0.0);
		}

		// Convert bool to double
		static double ConvertFromBool(bool bValue)
		{
			return static_cast<double>(bValue);
		}

		// Convert double to int
		static int ConvertToInt(double dValue)
		{
			return static_cast<int>(dValue);
		}

		// Convert int to double
		static double ConvertFromInt(int nValue)
		{
			return static_cast<double>(nValue);
		}

		// Convert double to int8
		static int8 ConvertToInt8(double dValue)
		{
			return static_cast<int8>(dValue);
		}

		// Convert int8 to double
		static double ConvertFromInt8(int8 nValue)
		{
			return static_cast<double>(nValue);
		}

		// Convert double to int16
		static int16 ConvertToInt16(double dValue)
		{
			return static_cast<int16>(dValue);
		}

		// Convert int16 to double
		static double ConvertFromInt16(int16 nValue)
		{
			return static_cast<double>(nValue);
		}

		// Convert double to int32
		static int32 ConvertToInt32(double dValue)
		{
			return static_cast<int32>(dValue);
		}

		// Convert int32 to double
		static double ConvertFromInt32(int32 nValue)
		{
			return static_cast<double>(nValue);
		}

		// Convert double to int64
		static int64 ConvertToInt64(double dValue)
		{
			return static_cast<int64>(dValue);
		}

		// Convert int64 to double
		static double ConvertFromInt64(int64 nValue)
		{
			return static_cast<double>(nValue);
		}

		// Convert double to uint8
		static uint8 ConvertToUInt8(double dValue)
		{
			return static_cast<uint8>(dValue);
		}

		// Convert uint8 to double
		static double ConvertFromUInt8(uint8 nValue)
		{
			return static_cast<double>(nValue);
		}

		// Convert double to uint16
		static uint16 ConvertToUInt16(double dValue)
		{
			return static_cast<uint16>(dValue);
		}

		// Convert uint16 to double
		static double ConvertFromUInt16(uint16 nValue)
		{
			return static_cast<double>(nValue);
		}

		// Convert double to uint32
		static uint32 ConvertToUInt32(double dValue)
		{
			return static_cast<uint32>(dValue);
		}

		// Convert uint32 to double
		static double ConvertFromUInt32(uint32 nValue)
		{
			return static_cast<double>(nValue);
		}

		// Convert double to uint64
		static uint64 ConvertToUInt64(double dValue)
		{
			return static_cast<uint64>(dValue);
		}

		// Convert uint64 to double
		static double ConvertFromUInt64(uint64 nValue)
		{
			return static_cast<double>(nValue);
		}

		// Convert double to uint_ptr
		static uint_ptr ConvertToUIntPtr(double dValue)
		{
			return static_cast<uint_ptr>(dValue);
		}

		// Convert uint_ptr to double
		static double ConvertFromUIntPtr(uint_ptr nValue)
		{
			return static_cast<double>(nValue);
		}

		// Convert double to float
		static float ConvertToFloat(double dValue)
		{
			return static_cast<float>(dValue);
		}

		// Convert float to double
		static double ConvertFromFloat(float fValue)
		{
			return static_cast<double>(fValue);
		}

		// Convert double to double
		static double ConvertToDouble(double dValue)
		{
			return static_cast<double>(dValue);
		}

		// Convert double to double
		static double ConvertFromDouble(double dValue)
		{
			return static_cast<double>(dValue);
		}

		// Convert double to string
		static String ConvertToString(double dValue)
		{
			return String() + dValue;
		}

		// Convert string to double
		static double ConvertFromString(const String &sString)
		{
			return sString.GetDouble();
		}

		// Convert real to storage type
		static double ConvertRealToStorage(double dValue)
		{
			return dValue;
		}

		// Convert storage to real type
		static double ConvertStorageToReal(double dValue)
		{
			return dValue;
		}

};


#endif // __PLCORE_TYPE_DOUBLE_INL__
