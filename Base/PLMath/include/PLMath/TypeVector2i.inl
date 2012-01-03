/*********************************************************\
 *  File: TypeVector2i.inl                               *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
		typedef PLMath::Vector2i _Type;			/**< Real type */
		typedef PLMath::Vector2i _StorageType;	/**< Storage type, for this type identical to the real type */

		// Type ID
		static const int TypeID = 1003;

		// Get type name
		static String GetTypeName()
		{
			return "vector2i";
		}

		// Convert var to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromVar(const DynVar &cVar)
		{
			const int nValue = cVar.GetInt();
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
		static int8 ConvertToInt8(const PLMath::Vector2i &vVector)
		{
			return static_cast<int8>(ConvertToInt(vVector));
		}

		// Convert int8 to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromInt8(int8 nValue)
		{
			return PLMath::Vector2i(nValue, nValue);
		}

		// Convert PLMath::Vector2i to int16
		static int16 ConvertToInt16(const PLMath::Vector2i &vVector)
		{
			return static_cast<int16>(ConvertToInt(vVector));
		}

		// Convert int16 to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromInt16(int16 nValue)
		{
			return PLMath::Vector2i(nValue, nValue);
		}

		// Convert PLMath::Vector2i to int32
		static int32 ConvertToInt32(const PLMath::Vector2i &vVector)
		{
			return static_cast<int32>(ConvertToInt(vVector));
		}

		// Convert int32 to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromInt32(int32 nValue)
		{
			return PLMath::Vector2i(nValue, nValue);
		}

		// Convert PLMath::Vector2i to int64
		static int64 ConvertToInt64(const PLMath::Vector2i &vVector)
		{
			return static_cast<int64>(ConvertToInt(vVector));
		}

		// Convert int64 to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromInt64(int64 nValue)
		{
			return PLMath::Vector2i(static_cast<int>(nValue), static_cast<int>(nValue));
		}

		// Convert PLMath::Vector2i to uint8
		static uint8 ConvertToUInt8(const PLMath::Vector2i &vVector)
		{
			return static_cast<uint8>(ConvertToInt(vVector));
		}

		// Convert uint8 to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromUInt8(uint8 nValue)
		{
			return PLMath::Vector2i(nValue, nValue);
		}

		// Convert PLMath::Vector2i to uint16
		static uint16 ConvertToUInt16(const PLMath::Vector2i &vVector)
		{
			return static_cast<uint16>(ConvertToInt(vVector));
		}

		// Convert uint16 to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromUInt16(uint16 nValue)
		{
			return PLMath::Vector2i(nValue, nValue);
		}

		// Convert PLMath::Vector2i to uint32
		static uint32 ConvertToUInt32(const PLMath::Vector2i &vVector)
		{
			return static_cast<uint32>(ConvertToInt(vVector));
		}

		// Convert uint32 to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromUInt32(uint32 nValue)
		{
			return PLMath::Vector2i(nValue, nValue);
		}

		// Convert PLMath::Vector2i to uint64
		static uint64 ConvertToUInt64(const PLMath::Vector2i &vVector)
		{
			return static_cast<uint64>(ConvertToInt(vVector));
		}

		// Convert uint64 to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromUInt64(uint64 nValue)
		{
			return PLMath::Vector2i(static_cast<int>(nValue), static_cast<int>(nValue));
		}

		// Convert PLMath::Vector2i to uint_ptr
		static uint_ptr ConvertToUIntPtr(const PLMath::Vector2i &vVector)
		{
			return static_cast<uint_ptr>(ConvertToInt(vVector));
		}

		// Convert uint_ptr to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromUIntPtr(uint_ptr nValue)
		{
			return PLMath::Vector2i(static_cast<int>(nValue), static_cast<int>(nValue));
		}

		// Convert PLMath::Vector2i to float
		static float ConvertToFloat(const PLMath::Vector2i &vVector)
		{
			return static_cast<float>(ConvertToInt(vVector));
		}

		// Convert float to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromFloat(float fValue)
		{
			return PLMath::Vector2i(static_cast<int>(fValue), static_cast<int>(fValue));
		}

		// Convert PLMath::Vector2i to double
		static double ConvertToDouble(const PLMath::Vector2i &vVector)
		{
			return static_cast<double>(ConvertToInt(vVector));
		}

		// Convert double to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromDouble(double dValue)
		{
			return PLMath::Vector2i(static_cast<int>(dValue), static_cast<int>(dValue));
		}

		// Convert PLMath::Vector2i to string
		static String ConvertToString(const PLMath::Vector2i &vVector)
		{
			return vVector.ToString();
		}

		// Convert string to PLMath::Vector2i
		static PLMath::Vector2i ConvertFromString(const String &sString)
		{
			PLMath::Vector2i vVector;
			vVector.FromString(sString);
			return vVector;
		}

		// Convert real to storage type (reference is enough in here)
		static PLMath::Vector2i &ConvertRealToStorage(PLMath::Vector2i &vValue)
		{
			return vValue;
		}

		// Convert storage to real type (reference is enough in here)
		static PLMath::Vector2i &ConvertStorageToReal(PLMath::Vector2i &vValue)
		{
			return vValue;
		}


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLMATH_TYPE_VECTOR2I_INL__
