/*********************************************************\
 *  File: TypeInt.inl                                    *
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
		typedef int _Type;

		// Type ID
		static const int TypeID = TypeInt;

		// Get type name
		static PLGeneral::String GetTypeName() {
			return "int";
		}

		// Convert var to int
		static int ConvertFromVar(const DynVar *pValue)
		{
			return pValue->GetInt();
		}

		// Convert int to bool
		static bool ConvertToBool(int nValue)
		{
			return (bool)(nValue != 0);
		}

		// Convert bool to int
		static int ConvertFromBool(bool bValue)
		{
			return (int)(bValue);
		}

		// Convert int to int
		static int ConvertToInt(int nValue)
		{
			return (int)(nValue);
		}

		// Convert int to int
		static int ConvertFromInt(int nValue)
		{
			return (int)(nValue);
		}

		// Convert int to int8
		static PLGeneral::int8 ConvertToInt8(int nValue)
		{
			return (PLGeneral::int8)(nValue);
		}

		// Convert int8 to int
		static int ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return (int)(nValue);
		}

		// Convert int to int16
		static PLGeneral::int16 ConvertToInt16(int nValue)
		{
			return (PLGeneral::int16)(nValue);
		}

		// Convert int16 to int
		static int ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return (int)(nValue);
		}

		// Convert int to int32
		static PLGeneral::int32 ConvertToInt32(int nValue)
		{
			return (PLGeneral::int32)(nValue);
		}

		// Convert int32 to int
		static int ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return (int)(nValue);
		}

		// Convert int to uint8
		static PLGeneral::uint8 ConvertToUInt8(int nValue)
		{
			return (PLGeneral::uint8)(nValue);
		}

		// Convert uint8 to int
		static int ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return (int)(nValue);
		}

		// Convert int to uint16
		static PLGeneral::uint16 ConvertToUInt16(int nValue)
		{
			return (PLGeneral::uint16)(nValue);
		}

		// Convert uint16 to int
		static int ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return (int)(nValue);
		}

		// Convert int to uint32
		static PLGeneral::uint32 ConvertToUInt32(int nValue)
		{
			return (PLGeneral::uint32)(nValue);
		}

		// Convert uint32 to int
		static int ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return (int)(nValue);
		}

		// Convert int to float
		static float ConvertToFloat(int nValue)
		{
			return (float)(nValue);
		}

		// Convert float to int
		static int ConvertFromFloat(float fValue)
		{
			return (int)(fValue);
		}

		// Convert int to double
		static double ConvertToDouble(int nValue)
		{
			return (double)(nValue);
		}

		// Convert double to int
		static int ConvertFromDouble(double dValue)
		{
			return (int)(dValue);
		}

		// Convert int to string
		static PLGeneral::String ConvertToString(int nValue)
		{
			return PLGeneral::String() + nValue;
		}

		// Convert string to int
		static int ConvertFromString(const PLGeneral::String &sString)
		{
			return sString.GetInt();
		}


};


#endif // __PLCORE_TYPE_INT_INL__
