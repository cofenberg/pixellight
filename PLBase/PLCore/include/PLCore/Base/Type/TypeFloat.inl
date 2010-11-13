/*********************************************************\
 *  File: TypeFloat.inl                                  *
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
		typedef float _Type;

		// Type ID
		static const int TypeID = TypeFloat;

		// Get type name
		static PLGeneral::String GetTypeName() {
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
			return (bool)(fValue != 0.0f);
		}

		// Convert bool to float
		static float ConvertFromBool(bool bValue)
		{
			return (float)(bValue);
		}

		// Convert float to int
		static int ConvertToInt(float fValue)
		{
			return (int)(fValue);
		}

		// Convert int to float
		static float ConvertFromInt(int nValue)
		{
			return (float)(nValue);
		}

		// Convert float to int8
		static PLGeneral::int8 ConvertToInt8(float fValue)
		{
			return (PLGeneral::int8)(fValue);
		}

		// Convert int8 to float
		static float ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return (float)(nValue);
		}

		// Convert float to int16
		static PLGeneral::int16 ConvertToInt16(float fValue)
		{
			return (PLGeneral::int16)(fValue);
		}

		// Convert int16 to float
		static float ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return (float)(nValue);
		}

		// Convert float to int32
		static PLGeneral::int32 ConvertToInt32(float fValue)
		{
			return (PLGeneral::int32)(fValue);
		}

		// Convert int32 to float
		static float ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return (float)(nValue);
		}

		// Convert float to int64
		static PLGeneral::int64 ConvertToInt64(float fValue)
		{
			return (PLGeneral::int64)(fValue);
		}

		// Convert int64 to float
		static float ConvertFromInt64(PLGeneral::int64 nValue)
		{
			return (float)(nValue);
		}

		// Convert float to uint8
		static PLGeneral::uint8 ConvertToUInt8(float fValue)
		{
			return (PLGeneral::uint8)(fValue);
		}

		// Convert uint8 to float
		static float ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return (float)(nValue);
		}

		// Convert float to uint16
		static PLGeneral::uint16 ConvertToUInt16(float fValue)
		{
			return (PLGeneral::uint16)(fValue);
		}

		// Convert uint16 to float
		static float ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return (float)(nValue);
		}

		// Convert float to uint32
		static PLGeneral::uint32 ConvertToUInt32(float fValue)
		{
			return (PLGeneral::uint32)(fValue);
		}

		// Convert uint32 to float
		static float ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return (float)(nValue);
		}

		// Convert float to uint64
		static PLGeneral::uint64 ConvertToUInt64(float fValue)
		{
			return (PLGeneral::uint64)(fValue);
		}

		// Convert uint64 to float
		static float ConvertFromUInt64(PLGeneral::uint64 nValue)
		{
			return (float)(nValue);
		}

		// Convert float to uint_ptr
		static PLGeneral::uint_ptr ConvertToUIntPtr(float fValue)
		{
			return (PLGeneral::uint_ptr)(fValue);
		}

		// Convert uint_ptr to float
		static float ConvertFromUIntPtr(PLGeneral::uint_ptr nValue)
		{
			return (float)(nValue);
		}

		// Convert float to float
		static float ConvertToFloat(float fValue)
		{
			return (float)(fValue);
		}

		// Convert float to float
		static float ConvertFromFloat(float fValue)
		{
			return (float)(fValue);
		}

		// Convert float to double
		static double ConvertToDouble(float fValue)
		{
			return (double)(fValue);
		}

		// Convert double to float
		static float ConvertFromDouble(double dValue)
		{
			return (float)(dValue);
		}

		// Convert float to string
		static PLGeneral::String ConvertToString(float fValue)
		{
			return PLGeneral::String() + fValue;
		}

		// Convert string to float
		static float ConvertFromString(const PLGeneral::String &sString)
		{
			return sString.GetFloat();
		}


};


#endif // __PLCORE_TYPE_FLOAT_INL__
