/*********************************************************\
 *  File: TypeInt64.inl                                  *
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


#ifndef __PLCORE_TYPE_INT64_INL__
#define __PLCORE_TYPE_INT64_INL__
#pragma once


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for 'int64'
*/
template <>
class Type<PLGeneral::int64> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef PLGeneral::int64 _Type;

		// Type ID
		static const PLGeneral::uint32 TypeID = TypeInt64;

		// Get type name
		static PLGeneral::String GetTypeName() {
			return "int64";
		}

		// Convert var to int64
		static PLGeneral::int64 ConvertFromVar(const DynVar *pValue)
		{
			return pValue->GetInt64();
		}

		// Convert int64 to bool
		static bool ConvertToBool(PLGeneral::int64 nValue)
		{
			return (bool)(nValue != 0);
		}

		// Convert bool to int64
		static PLGeneral::int64 ConvertFromBool(bool bValue)
		{
			return (PLGeneral::int64)(bValue);
		}

		// Convert int64 to int
		static int ConvertToInt(PLGeneral::int64 nValue)
		{
			return (int)(nValue);
		}

		// Convert int to int64
		static PLGeneral::int64 ConvertFromInt(int nValue)
		{
			return (PLGeneral::int64)(nValue);
		}

		// Convert int64 to int8
		static PLGeneral::int8 ConvertToInt8(PLGeneral::int64 nValue)
		{
			return (PLGeneral::int8)(nValue);
		}

		// Convert int8 to int64
		static PLGeneral::int64 ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return (PLGeneral::int64)(nValue);
		}

		// Convert int64 to int16
		static PLGeneral::int16 ConvertToInt16(PLGeneral::int64 nValue)
		{
			return (PLGeneral::int16)(nValue);
		}

		// Convert int16 to int64
		static PLGeneral::int64 ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return (PLGeneral::int64)(nValue);
		}

		// Convert int64 to int32
		static PLGeneral::int32 ConvertToInt32(PLGeneral::int64 nValue)
		{
			return (PLGeneral::int32)(nValue);
		}

		// Convert int32 to int64
		static PLGeneral::int64 ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return (PLGeneral::int64)(nValue);
		}

		// Convert int64 to int64
		static PLGeneral::int64 ConvertToInt64(PLGeneral::int64 nValue)
		{
			return (PLGeneral::int64)(nValue);
		}

		// Convert int64 to int64
		static PLGeneral::int64 ConvertFromInt64(PLGeneral::int64 nValue)
		{
			return (PLGeneral::int64)(nValue);
		}

		// Convert int64 to uint8
		static PLGeneral::uint8 ConvertToUInt8(PLGeneral::int64 nValue)
		{
			return (PLGeneral::uint8)(nValue);
		}

		// Convert uint8 to int64
		static PLGeneral::int64 ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return (PLGeneral::int64)(nValue);
		}

		// Convert int64 to uint16
		static PLGeneral::uint16 ConvertToUInt16(PLGeneral::int64 nValue)
		{
			return (PLGeneral::uint16)(nValue);
		}

		// Convert uint16 to int64
		static PLGeneral::int64 ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return (PLGeneral::int64)(nValue);
		}

		// Convert int64 to uint32
		static PLGeneral::uint32 ConvertToUInt32(PLGeneral::int64 nValue)
		{
			return (PLGeneral::uint32)(nValue);
		}

		// Convert uint32 to int64
		static PLGeneral::int64 ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return (PLGeneral::int64)(nValue);
		}

		// Convert int64 to uint64
		static PLGeneral::uint64 ConvertToUInt64(PLGeneral::int64 nValue)
		{
			return (PLGeneral::uint64)(nValue);
		}

		// Convert uint64 to int64
		static PLGeneral::int64 ConvertFromUInt64(PLGeneral::uint64 nValue)
		{
			return (PLGeneral::int64)(nValue);
		}

		// Convert int64 to uint_ptr
		static PLGeneral::uint_ptr ConvertToUIntPtr(PLGeneral::int64 nValue)
		{
			return (PLGeneral::uint_ptr)(nValue);
		}

		// Convert uint_ptr to int64
		static PLGeneral::int64 ConvertFromUIntPtr(PLGeneral::uint_ptr nValue)
		{
			return (PLGeneral::int64)(nValue);
		}

		// Convert int64 to float
		static float ConvertToFloat(PLGeneral::int64 nValue)
		{
			return (float)(nValue);
		}

		// Convert float to int64
		static PLGeneral::int64 ConvertFromFloat(float fValue)
		{
			return (PLGeneral::int64)(fValue);
		}

		// Convert int64 to double
		static double ConvertToDouble(PLGeneral::int64 nValue)
		{
			return (double)(nValue);
		}

		// Convert double to int64
		static PLGeneral::int64 ConvertFromDouble(double dValue)
		{
			return (PLGeneral::int64)(dValue);
		}

		// Convert int64 to string
		static PLGeneral::String ConvertToString(PLGeneral::int64 nValue)
		{
			return PLGeneral::String() + (int)nValue;
		}

		// Convert string to PLGeneral::int64
		static PLGeneral::int64 ConvertFromString(const PLGeneral::String &sString)
		{
			return sString.GetInt();
		}


};


#endif // __PLCORE_TYPE_INT64_INL__
