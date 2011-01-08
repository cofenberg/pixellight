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
class Type<PLGeneral::uint16> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef PLGeneral::uint16 _Type;

		// Type ID
		static const PLGeneral::uint32 TypeID = TypeUInt16;

		// Get type name
		static PLGeneral::String GetTypeName() {
			return "uint16";
		}

		// Convert var to uint16
		static PLGeneral::uint16 ConvertFromVar(const DynVar *pValue)
		{
			return pValue->GetUInt16();
		}

		// Convert uint16 to bool
		static bool ConvertToBool(PLGeneral::uint16 nValue)
		{
			return (bool)(nValue != 0);
		}

		// Convert bool to uint16
		static PLGeneral::uint16 ConvertFromBool(bool bValue)
		{
			return (PLGeneral::uint16)(bValue);
		}

		// Convert uint16 to int
		static int ConvertToInt(PLGeneral::uint16 nValue)
		{
			return (int)(nValue);
		}

		// Convert int to uint16
		static PLGeneral::uint16 ConvertFromInt(int nValue)
		{
			return (PLGeneral::uint16)(nValue);
		}

		// Convert uint16 to int8
		static PLGeneral::int8 ConvertToInt8(PLGeneral::uint16 nValue)
		{
			return (PLGeneral::int8)(nValue);
		}

		// Convert int8 to uint16
		static PLGeneral::uint16 ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return (PLGeneral::uint16)(nValue);
		}

		// Convert uint16 to int16
		static PLGeneral::int16 ConvertToInt16(PLGeneral::uint16 nValue)
		{
			return (PLGeneral::int16)(nValue);
		}

		// Convert int16 to uint16
		static PLGeneral::uint16 ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return (PLGeneral::uint16)(nValue);
		}

		// Convert uint16 to int32
		static PLGeneral::int32 ConvertToInt32(PLGeneral::uint16 nValue)
		{
			return (PLGeneral::int32)(nValue);
		}

		// Convert int32 to uint16
		static PLGeneral::uint16 ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return (PLGeneral::uint16)(nValue);
		}

		// Convert uint16 to int64
		static PLGeneral::int64 ConvertToInt64(PLGeneral::uint16 nValue)
		{
			return (PLGeneral::int64)(nValue);
		}

		// Convert int64 to uint16
		static PLGeneral::uint16 ConvertFromInt64(PLGeneral::int64 nValue)
		{
			return (PLGeneral::uint16)(nValue);
		}

		// Convert uint16 to uint8
		static PLGeneral::uint8 ConvertToUInt8(PLGeneral::uint16 nValue)
		{
			return (PLGeneral::uint8)(nValue);
		}

		// Convert uint8 to uint16
		static PLGeneral::uint16 ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return (PLGeneral::uint16)(nValue);
		}

		// Convert uint16 to uint16
		static PLGeneral::uint16 ConvertToUInt16(PLGeneral::uint16 nValue)
		{
			return (PLGeneral::uint16)(nValue);
		}

		// Convert uint16 to uint16
		static PLGeneral::uint16 ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return (PLGeneral::uint16)(nValue);
		}

		// Convert uint16 to uint32
		static PLGeneral::uint32 ConvertToUInt32(PLGeneral::uint16 nValue)
		{
			return (PLGeneral::uint32)(nValue);
		}

		// Convert uint32 to uint16
		static PLGeneral::uint16 ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return (PLGeneral::uint16)(nValue);
		}

		// Convert uint16 to uint64
		static PLGeneral::uint64 ConvertToUInt64(PLGeneral::uint16 nValue)
		{
			return (PLGeneral::uint64)(nValue);
		}

		// Convert uint64 to uint16
		static PLGeneral::uint16 ConvertFromUInt64(PLGeneral::uint64 nValue)
		{
			return (PLGeneral::uint16)(nValue);
		}

		// Convert uint16 to uint_ptr
		static PLGeneral::uint_ptr ConvertToUIntPtr(PLGeneral::uint16 nValue)
		{
			return (PLGeneral::uint_ptr)(nValue);
		}

		// Convert uint_ptr to uint16
		static PLGeneral::uint16 ConvertFromUIntPtr(PLGeneral::uint_ptr nValue)
		{
			return (PLGeneral::uint16)(nValue);
		}

		// Convert uint16 to float
		static float ConvertToFloat(PLGeneral::uint16 nValue)
		{
			return (float)(nValue);
		}

		// Convert float to uint16
		static PLGeneral::uint16 ConvertFromFloat(float fValue)
		{
			return (PLGeneral::uint16)(fValue);
		}

		// Convert uint16 to double
		static double ConvertToDouble(PLGeneral::uint16 nValue)
		{
			return (double)(nValue);
		}

		// Convert double to uint16
		static PLGeneral::uint16 ConvertFromDouble(double dValue)
		{
			return (PLGeneral::uint16)(dValue);
		}

		// Convert uint16 to string
		static PLGeneral::String ConvertToString(PLGeneral::uint16 nValue)
		{
			return PLGeneral::String() + (int)nValue;
		}

		// Convert string to PLGeneral::uint16
		static PLGeneral::uint16 ConvertFromString(const PLGeneral::String &sString)
		{
			return (PLGeneral::uint16)sString.GetInt();
		}


};


#endif // __PLCORE_TYPE_UINT16_INL__
