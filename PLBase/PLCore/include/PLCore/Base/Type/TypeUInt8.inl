/*********************************************************\
 *  File: TypeUInt8.inl                                  *
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


#ifndef __PLCORE_TYPE_UINT8_INL__
#define __PLCORE_TYPE_UINT8_INL__
#pragma once


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for 'uint8'
*/
template <>
class Type<PLGeneral::uint8> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef PLGeneral::uint8 _Type;

		// Type ID
		static const PLGeneral::uint32 TypeID = TypeUInt8;

		// Get type name
		static PLGeneral::String GetTypeName() {
			return "uint8";
		}

		// Convert var to uint8
		static PLGeneral::uint8 ConvertFromVar(const DynVar *pValue)
		{
			return pValue->GetUInt8();
		}

		// Convert uint8 to bool
		static bool ConvertToBool(PLGeneral::uint8 nValue)
		{
			return (bool)(nValue != 0);
		}

		// Convert bool to uint8
		static PLGeneral::uint8 ConvertFromBool(bool bValue)
		{
			return (PLGeneral::uint8)(bValue);
		}

		// Convert uint8 to int
		static int ConvertToInt(PLGeneral::uint8 nValue)
		{
			return (int)(nValue);
		}

		// Convert int to uint8
		static PLGeneral::uint8 ConvertFromInt(int nValue)
		{
			return (PLGeneral::uint8)(nValue);
		}

		// Convert uint8 to int8
		static PLGeneral::int8 ConvertToInt8(PLGeneral::uint8 nValue)
		{
			return (PLGeneral::int8)(nValue);
		}

		// Convert int8 to uint8
		static PLGeneral::uint8 ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return (PLGeneral::uint8)(nValue);
		}

		// Convert uint8 to int16
		static PLGeneral::int16 ConvertToInt16(PLGeneral::uint8 nValue)
		{
			return (PLGeneral::int16)(nValue);
		}

		// Convert int16 to uint8
		static PLGeneral::uint8 ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return (PLGeneral::uint8)(nValue);
		}

		// Convert uint8 to int32
		static PLGeneral::int32 ConvertToInt32(PLGeneral::uint8 nValue)
		{
			return (PLGeneral::int32)(nValue);
		}

		// Convert int32 to uint8
		static PLGeneral::uint8 ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return (PLGeneral::uint8)(nValue);
		}

		// Convert uint8 to int64
		static PLGeneral::int64 ConvertToInt64(PLGeneral::uint8 nValue)
		{
			return (PLGeneral::int64)(nValue);
		}

		// Convert int64 to uint8
		static PLGeneral::uint8 ConvertFromInt64(PLGeneral::int64 nValue)
		{
			return (PLGeneral::uint8)(nValue);
		}

		// Convert uint8 to uint8
		static PLGeneral::uint8 ConvertToUInt8(PLGeneral::uint8 nValue)
		{
			return (PLGeneral::uint8)(nValue);
		}

		// Convert uint8 to uint8
		static PLGeneral::uint8 ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return (PLGeneral::uint8)(nValue);
		}

		// Convert uint8 to uint16
		static PLGeneral::uint16 ConvertToUInt16(PLGeneral::uint8 nValue)
		{
			return (PLGeneral::uint16)(nValue);
		}

		// Convert uint16 to uint8
		static PLGeneral::uint8 ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return (PLGeneral::uint8)(nValue);
		}

		// Convert uint8 to uint32
		static PLGeneral::uint32 ConvertToUInt32(PLGeneral::uint8 nValue)
		{
			return (PLGeneral::uint32)(nValue);
		}

		// Convert uint32 to uint8
		static PLGeneral::uint8 ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return (PLGeneral::uint8)(nValue);
		}

		// Convert uint8 to uint64
		static PLGeneral::uint64 ConvertToUInt64(PLGeneral::uint8 nValue)
		{
			return (PLGeneral::uint64)(nValue);
		}

		// Convert uint64 to uint8
		static PLGeneral::uint8 ConvertFromUInt64(PLGeneral::uint64 nValue)
		{
			return (PLGeneral::uint8)(nValue);
		}

		// Convert uint8 to uint_ptr
		static PLGeneral::uint_ptr ConvertToUIntPtr(PLGeneral::uint8 nValue)
		{
			return (PLGeneral::uint_ptr)(nValue);
		}

		// Convert uint_ptr to uint8
		static PLGeneral::uint8 ConvertFromUIntPtr(PLGeneral::uint_ptr nValue)
		{
			return (PLGeneral::uint8)(nValue);
		}

		// Convert uint8 to float
		static float ConvertToFloat(PLGeneral::uint8 nValue)
		{
			return (float)(nValue);
		}

		// Convert float to uint8
		static PLGeneral::uint8 ConvertFromFloat(float fValue)
		{
			return (PLGeneral::uint8)(fValue);
		}

		// Convert uint8 to double
		static double ConvertToDouble(PLGeneral::uint8 nValue)
		{
			return (double)(nValue);
		}

		// Convert double to uint8
		static PLGeneral::uint8 ConvertFromDouble(double dValue)
		{
			return (PLGeneral::uint8)(dValue);
		}

		// Convert uint8 to string
		static PLGeneral::String ConvertToString(PLGeneral::uint8 nValue)
		{
			return PLGeneral::String() + (int)nValue;
		}

		// Convert string to PLGeneral::uint8
		static PLGeneral::uint8 ConvertFromString(const PLGeneral::String &sString)
		{
			return (PLGeneral::uint8)sString.GetInt();
		}


};


#endif // __PLCORE_TYPE_UINT8_INL__
