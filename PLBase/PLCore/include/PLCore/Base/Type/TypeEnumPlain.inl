/*********************************************************\
 *  File: TypeEnumPlain.inl                              *
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
		typedef ENUM _Type;

		// Type ID
		static const int TypeID = Type<int>::TypeID;

		// Get type name
		static PLGeneral::String GetTypeName() {
			return Type<int>::GetTypeName();
		}

		// Convert var to type
		static ENUM ConvertFromVar(const DynVar *pValue)
		{
			return (ENUM)Type<int>::ConvertFromVar(pValue);
		}

		// Convert type to bool
		static bool ConvertToBool(ENUM Value)
		{
			return Type<int>::ConvertToBool((int)Value);
		}

		// Convert bool to type
		static ENUM ConvertFromBool(bool bValue)
		{
			return (ENUM)Type<int>::ConvertFromBool(bValue);
		}

		// Convert type to int
		static int ConvertToInt(ENUM Value)
		{
			return Type<int>::ConvertToInt((int)Value);
		}

		// Convert int to type
		static ENUM ConvertFromInt(int nValue)
		{
			return (ENUM)Type<int>::ConvertFromInt(nValue);
		}

		// Convert type to int8
		static PLGeneral::int8 ConvertToInt8(ENUM Value)
		{
			return Type<int>::ConvertToInt8((int)Value);
		}

		// Convert int8 to type
		static ENUM ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return (ENUM)Type<int>::ConvertFromInt8(nValue);
		}

		// Convert type to int16
		static PLGeneral::int16 ConvertToInt16(ENUM Value)
		{
			return Type<int>::ConvertToInt16((int)Value);
		}

		// Convert int16 to type
		static ENUM ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return (ENUM)Type<int>::ConvertFromInt16(nValue);
		}

		// Convert type to int32
		static PLGeneral::int32 ConvertToInt32(ENUM Value)
		{
			return Type<int>::ConvertToInt32((int)Value);
		}

		// Convert int32 to type
		static ENUM ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return (ENUM)Type<int>::ConvertFromInt32(nValue);
		}

		// Convert type to uint8
		static PLGeneral::uint8 ConvertToUInt8(ENUM Value)
		{
			return Type<int>::ConvertToUInt8((int)Value);
		}

		// Convert uint8 to type
		static ENUM ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return (ENUM)Type<int>::ConvertFromUInt8(nValue);
		}

		// Convert type to uint16
		static PLGeneral::uint16 ConvertToUInt16(ENUM Value)
		{
			return Type<int>::ConvertToUInt16((int)Value);
		}

		// Convert uint16 to type
		static ENUM ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return (ENUM)Type<int>::ConvertFromUInt16(nValue);
		}

		// Convert type to uint32
		static PLGeneral::uint32 ConvertToUInt32(ENUM Value)
		{
			return Type<int>::ConvertToUInt32((int)Value);
		}

		// Convert uint32 to type
		static ENUM ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return (ENUM)Type<int>::ConvertFromUInt32(nValue);
		}

		// Convert type to float
		static float ConvertToFloat(ENUM Value)
		{
			return Type<int>::ConvertToFloat((int)Value);
		}

		// Convert float to type
		static ENUM ConvertFromFloat(float fValue)
		{
			return (ENUM)Type<int>::ConvertFromFloat(fValue);
		}

		// Convert type to double
		static double ConvertToDouble(ENUM Value)
		{
			return Type<int>::ConvertToDouble((int)Value);
		}

		// Convert double to type
		static ENUM ConvertFromDouble(double dValue)
		{
			return (ENUM)Type<int>::ConvertFromDouble(dValue);
		}

		// Convert type to string
		static PLGeneral::String ConvertToString(ENUM Value)
		{
			return Type<int>::ConvertToString((int)Value);
		}

		// Convert string to type
		static ENUM ConvertFromString(const PLGeneral::String &sString)
		{
			return (ENUM)Type<int>::ConvertFromString(sString);
		}


};


#endif // __PLCORE_TYPE_ENUMPLAIN_INL__
