/*********************************************************\
 *  File: TypeVector2i.inl                               *
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


#ifndef __PLMATH_TYPE_VECTOR2I_INL__
#define __PLMATH_TYPE_VECTOR2I_INL__
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
*    Type wrapper for 'PLMath::Vector2i'
*/
template <>
class Type<PLMath::Vector2i> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef PLMath::Vector2i _Type;

		// Type ID
		static const int TypeID = 1003;

		// Get type name
		static PLGeneral::String GetTypeName() {
			return "vector2i";
		}

		// Convert var to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromVar(const DynVar *pVar)
		{
			const int nValue = pVar->GetInt();
			return PLMath::Vector2i(nValue, nValue);
		}

		// Convert PLMath::Vector2i to bool
		static bool ConvertToBool(const PLMath::Vector2i &vVector)
		{
			return (vVector == PLMath::Vector2i::Zero);
		}

		// Convert bool to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromBool(bool bValue)
		{
			const int nValue = bValue ? 1 : 0;
			return PLMath::Vector2i(nValue, nValue);
		}

		// Convert PLMath::Vector2i to int
		static int ConvertToInt(const PLMath::Vector2i &vVector)
		{
			return (vVector == PLMath::Vector2i::Zero);
		}

		// Convert int to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromInt(int nValue)
		{
			return PLMath::Vector2i(nValue, nValue);
		}

		// Convert PLMath::Vector2i to int8
		static PLGeneral::int8 ConvertToInt8(const PLMath::Vector2i &vVector)
		{
			return (PLGeneral::int8)ConvertToInt(vVector);
		}

		// Convert int8 to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return PLMath::Vector2i(nValue, nValue);
		}

		// Convert PLMath::Vector2i to int16
		static PLGeneral::int16 ConvertToInt16(const PLMath::Vector2i &vVector)
		{
			return (PLGeneral::int16)ConvertToInt(vVector);
		}

		// Convert int16 to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return PLMath::Vector2i(nValue, nValue);
		}

		// Convert PLMath::Vector2i to int32
		static PLGeneral::int32 ConvertToInt32(const PLMath::Vector2i &vVector)
		{
			return (PLGeneral::int32)ConvertToInt(vVector);
		}

		// Convert int32 to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return PLMath::Vector2i(nValue, nValue);
		}

		// Convert PLMath::Vector2i to int8
		static PLGeneral::uint8 ConvertToUInt8(const PLMath::Vector2i &vVector)
		{
			return (PLGeneral::uint8)ConvertToInt(vVector);
		}

		// Convert uint8 to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return PLMath::Vector2i(nValue, nValue);
		}

		// Convert PLMath::Vector2i to uint16
		static PLGeneral::uint16 ConvertToUInt16(const PLMath::Vector2i &vVector)
		{
			return (PLGeneral::uint16)ConvertToInt(vVector);
		}

		// Convert uint16 to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return PLMath::Vector2i(nValue, nValue);
		}

		// Convert PLMath::Vector2i to uint32
		static PLGeneral::uint32 ConvertToUInt32(const PLMath::Vector2i &vVector)
		{
			return (PLGeneral::uint32)ConvertToInt(vVector);
		}

		// Convert uint32 to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return PLMath::Vector2i(nValue, nValue);
		}

		// Convert PLMath::Vector2i to float
		static float ConvertToFloat(const PLMath::Vector2i &vVector)
		{
			return (float)ConvertToInt(vVector);
		}

		// Convert float to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromFloat(float fValue)
		{
			return PLMath::Vector2i((int)fValue, (int)fValue);
		}

		// Convert PLMath::Vector2i to double
		static double ConvertToDouble(const PLMath::Vector2i &vVector)
		{
			return (double)ConvertToInt(vVector);
		}

		// Convert double to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromDouble(double dValue)
		{
			return PLMath::Vector2i((int)dValue, (int)dValue);
		}

		// Convert PLMath::Vector2i to string
		static PLGeneral::String ConvertToString(const PLMath::Vector2i &vVector)
		{
			return vVector.ToString();
		}

		// Convert string to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromString(const PLGeneral::String &sString)
		{
			PLMath::Vector2i vVector;
			vVector.FromString(sString);
			return vVector;
		}


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLMATH_TYPE_VECTOR2I_INL__
