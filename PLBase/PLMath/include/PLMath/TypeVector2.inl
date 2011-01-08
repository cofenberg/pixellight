/*********************************************************\
 *  File: TypeVector2.inl                                *
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


#ifndef __PLMATH_TYPE_VECTOR2_INL__
#define __PLMATH_TYPE_VECTOR2_INL__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Type/Type.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for 'PLMath::Vector2'
*/
template <>
class Type<PLMath::Vector2> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef PLMath::Vector2 _Type;

		// Type ID
		static const int TypeID = 1000;

		// Get type name
		static PLGeneral::String GetTypeName() {
			return "vector2";
		}

		// Convert var to PLMath::Vector2
		static PLMath::Vector2 ConvertFromVar(const DynVar *pVar)
		{
			const float fValue = pVar->GetFloat();
			return PLMath::Vector2(fValue, fValue);
		}

		// Convert PLMath::Vector2 to bool
		static bool ConvertToBool(const PLMath::Vector2 &vVector)
		{
			return vVector.IsNull();
		}

		// Convert bool to PLMath::Vector2
		static PLMath::Vector2 ConvertFromBool(bool bValue)
		{
			const float fValue = bValue ? 1.0f : 0.0f;
			return PLMath::Vector2(fValue, fValue);
		}

		// Convert PLMath::Vector2 to int
		static int ConvertToInt(const PLMath::Vector2 &vVector)
		{
			return vVector.IsNull();
		}

		// Convert int to PLMath::Vector2
		static PLMath::Vector2 ConvertFromInt(int nValue)
		{
			return PLMath::Vector2((float)nValue, (float)nValue);
		}

		// Convert PLMath::Vector2 to int8
		static PLGeneral::int8 ConvertToInt8(const PLMath::Vector2 &vVector)
		{
			return (PLGeneral::int8)ConvertToInt(vVector);
		}

		// Convert int8 to PLMath::Vector2
		static PLMath::Vector2 ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return PLMath::Vector2((float)nValue, (float)nValue);
		}

		// Convert PLMath::Vector2 to int16
		static PLGeneral::int16 ConvertToInt16(const PLMath::Vector2 &vVector)
		{
			return (PLGeneral::int16)ConvertToInt(vVector);
		}

		// Convert int16 to PLMath::Vector2
		static PLMath::Vector2 ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return PLMath::Vector2((float)nValue, (float)nValue);
		}

		// Convert PLMath::Vector2 to int32
		static PLGeneral::int32 ConvertToInt32(const PLMath::Vector2 &vVector)
		{
			return (PLGeneral::int32)ConvertToInt(vVector);
		}

		// Convert int32 to PLMath::Vector2
		static PLMath::Vector2 ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return PLMath::Vector2((float)nValue, (float)nValue);
		}

		// Convert PLMath::Vector2 to int64
		static PLGeneral::int64 ConvertToInt64(const PLMath::Vector2 &vVector)
		{
			return (PLGeneral::int64)ConvertToInt(vVector);
		}

		// Convert int64 to PLMath::Vector2
		static PLMath::Vector2 ConvertFromInt64(PLGeneral::int64 nValue)
		{
			return PLMath::Vector2((float)nValue, (float)nValue);
		}

		// Convert PLMath::Vector2 to uint8
		static PLGeneral::uint8 ConvertToUInt8(const PLMath::Vector2 &vVector)
		{
			return (PLGeneral::uint8)ConvertToInt(vVector);
		}

		// Convert uint8 to PLMath::Vector2
		static PLMath::Vector2 ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return PLMath::Vector2((float)nValue, (float)nValue);
		}

		// Convert PLMath::Vector2 to uint16
		static PLGeneral::uint16 ConvertToUInt16(const PLMath::Vector2 &vVector)
		{
			return (PLGeneral::uint16)ConvertToInt(vVector);
		}

		// Convert uint16 to PLMath::Vector2
		static PLMath::Vector2 ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return PLMath::Vector2((float)nValue, (float)nValue);
		}

		// Convert PLMath::Vector2 to uint32
		static PLGeneral::uint32 ConvertToUInt32(const PLMath::Vector2 &vVector)
		{
			return (PLGeneral::uint32)ConvertToInt(vVector);
		}

		// Convert uint32 to PLMath::Vector2
		static PLMath::Vector2 ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return PLMath::Vector2((float)nValue, (float)nValue);
		}

		// Convert PLMath::Vector2 to uint64
		static PLGeneral::uint64 ConvertToUInt64(const PLMath::Vector2 &vVector)
		{
			return (PLGeneral::uint64)ConvertToInt(vVector);
		}

		// Convert uint64 to PLMath::Vector2
		static PLMath::Vector2 ConvertFromUInt64(PLGeneral::uint64 nValue)
		{
			return PLMath::Vector2((float)nValue, (float)nValue);
		}

		// Convert PLMath::Vector2 to uint_ptr
		static PLGeneral::uint_ptr ConvertToUIntPtr(const PLMath::Vector2 &vVector)
		{
			return (PLGeneral::uint_ptr)ConvertToInt(vVector);
		}

		// Convert uint_ptr to PLMath::Vector2
		static PLMath::Vector2 ConvertFromUIntPtr(PLGeneral::uint_ptr nValue)
		{
			return PLMath::Vector2((float)nValue, (float)nValue);
		}

		// Convert PLMath::Vector2 to float
		static float ConvertToFloat(const PLMath::Vector2 &vVector)
		{
			return (float)ConvertToInt(vVector);
		}

		// Convert float to PLMath::Vector2
		static PLMath::Vector2 ConvertFromFloat(float fValue)
		{
			return PLMath::Vector2(fValue, fValue);
		}

		// Convert PLMath::Vector2 to double
		static double ConvertToDouble(const PLMath::Vector2 &vVector)
		{
			return (double)ConvertToInt(vVector);
		}

		// Convert double to PLMath::Vector2
		static PLMath::Vector2 ConvertFromDouble(double dValue)
		{
			return PLMath::Vector2((float)dValue, (float)dValue);
		}

		// Convert PLMath::Vector2 to string
		static PLGeneral::String ConvertToString(const PLMath::Vector2 &vVector)
		{
			return vVector.ToString();
		}

		// Convert string to PLMath::Vector2
		static PLMath::Vector2 ConvertFromString(const PLGeneral::String &sString)
		{
			PLMath::Vector2 vVector;
			vVector.FromString(sString);
			return vVector;
		}


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLMATH_TYPE_VECTOR2_INL__
