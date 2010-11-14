/*********************************************************\
 *  File: TypeBool.inl                                   *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLCORE_TYPE_BOOL_INL__
#define __PLCORE_TYPE_BOOL_INL__
#pragma once


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for 'bool'
*/
template <>
class Type<bool> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef bool _Type;

		// Type ID
		static const int TypeID = TypeBool;

		// Get type name
		static PLGeneral::String GetTypeName() {
			return "bool";
		}

		// Convert var to bool
		static bool ConvertFromVar(const DynVar *pValue)
		{
			return pValue->GetBool();
		}

		// Convert bool to bool
		static bool ConvertToBool(bool bValue)
		{
			return (bool)(bValue);
		}

		// Convert bool to bool
		static bool ConvertFromBool(bool bValue)
		{
			return (bool)(bValue);
		}

		// Convert bool to int
		static int ConvertToInt(bool bValue)
		{
			return (int)(bValue);
		}

		// Convert int to bool
		static bool ConvertFromInt(int nValue)
		{
			return (bool)(nValue != 0);
		}

		// Convert bool to int8
		static PLGeneral::int8 ConvertToInt8(bool bValue)
		{
			return (PLGeneral::int8)(bValue);
		}

		// Convert int8 to bool
		static bool ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return (bool)(nValue != 0);
		}

		// Convert bool to int16
		static PLGeneral::int16 ConvertToInt16(bool bValue)
		{
			return (PLGeneral::int16)(bValue);
		}

		// Convert int16 to bool
		static bool ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return (bool)(nValue != 0);
		}

		// Convert bool to int32
		static PLGeneral::int32 ConvertToInt32(bool bValue)
		{
			return (PLGeneral::int32)(bValue);
		}

		// Convert int32 to bool
		static bool ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return (bool)(nValue != 0);
		}

		// Convert bool to int64
		static PLGeneral::int64 ConvertToInt64(bool bValue)
		{
			return (PLGeneral::int64)(bValue);
		}

		// Convert int64 to bool
		static bool ConvertFromInt64(PLGeneral::int64 nValue)
		{
			return (bool)(nValue != 0);
		}

		// Convert bool to uint8
		static PLGeneral::uint8 ConvertToUInt8(bool bValue)
		{
			return (PLGeneral::uint8)(bValue);
		}

		// Convert uint8 to bool
		static bool ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return (bool)(nValue != 0);
		}

		// Convert bool to uint16
		static PLGeneral::uint16 ConvertToUInt16(bool bValue)
		{
			return (PLGeneral::uint16)(bValue);
		}

		// Convert uint16 to bool
		static bool ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return (bool)(nValue != 0);
		}

		// Convert bool to uint32
		static PLGeneral::uint32 ConvertToUInt32(bool bValue)
		{
			return (PLGeneral::uint32)(bValue);
		}

		// Convert uint32 to bool
		static bool ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return (bool)(nValue != 0);
		}

		// Convert bool to uint64
		static PLGeneral::uint64 ConvertToUInt64(bool bValue)
		{
			return (PLGeneral::uint64)(bValue);
		}

		// Convert uint64 to bool
		static bool ConvertFromUInt64(PLGeneral::uint64 nValue)
		{
			return (bool)(nValue != 0);
		}

		// Convert bool to uint_ptr
		static PLGeneral::uint_ptr ConvertToUIntPtr(bool bValue)
		{
			return (PLGeneral::uint_ptr)(bValue);
		}

		// Convert uint_ptr to bool
		static bool ConvertFromUIntPtr(PLGeneral::uint_ptr nValue)
		{
			return (bool)(nValue != 0);
		}

		// Convert bool to float
		static float ConvertToFloat(bool bValue)
		{
			return (float)(bValue);
		}

		// Convert float to bool
		static bool ConvertFromFloat(float fValue)
		{
			return (bool)(fValue != 0.0f);
		}

		// Convert bool to double
		static double ConvertToDouble(bool bValue)
		{
			return (double)(bValue);
		}

		// Convert double to bool
		static bool ConvertFromDouble(double dValue)
		{
			return (bool)(dValue != 0.0);
		}

		// Convert bool to string
		static PLGeneral::String ConvertToString(bool bValue)
		{
			return (bValue ? "true" : "false");
		}

		// Convert string to bool
		static bool ConvertFromString(const PLGeneral::String &sString)
		{
			return sString.GetBool();
		}


};


#endif // __PLCORE_TYPE_BOOL_INL__
