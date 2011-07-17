/*********************************************************\
 *  File: TypeVector3i.inl                               *
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


#ifndef __PLMATH_TYPE_VECTOR3I_INL__
#define __PLMATH_TYPE_VECTOR3I_INL__
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
*    Type wrapper for 'PLMath::Vector3i'
*/
template <>
class Type<PLMath::Vector3i> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef PLMath::Vector3i _Type;			/**< Real type */
		typedef PLMath::Vector3i _StorageType;	/**< Storage type, for this type identical to the real type */

		// Type ID
		static const int TypeID = 1004;

		// Get type name
		static PLGeneral::String GetTypeName()
		{
			return "vector3i";
		}

		// Convert var to PLMath::Vector3i
		static PLMath::Vector3i ConvertFromVar(const DynVar *pVar)
		{
			const int nValue = pVar->GetInt();
			return PLMath::Vector3i(nValue, nValue, nValue);
		}

		// Convert PLMath::Vector3i to bool
		static bool ConvertToBool(const PLMath::Vector3i &vVector)
		{
			return (vVector == PLMath::Vector3i::Zero);
		}

		// Convert bool to PLMath::Vector3i
		static PLMath::Vector3i ConvertFromBool(bool bValue)
		{
			const int nValue = bValue ? 1 : 0;
			return PLMath::Vector3i(nValue, nValue, nValue);
		}

		// Convert PLMath::Vector3i to int
		static int ConvertToInt(const PLMath::Vector3i &vVector)
		{
			return (vVector == PLMath::Vector3i::Zero);
		}

		// Convert int to PLMath::Vector3i
		static PLMath::Vector3i ConvertFromInt(int nValue)
		{
			return PLMath::Vector3i(nValue, nValue, nValue);
		}

		// Convert PLMath::Vector3i to int8
		static PLGeneral::int8 ConvertToInt8(const PLMath::Vector3i &vVector)
		{
			return static_cast<PLGeneral::int8>(ConvertToInt(vVector));
		}

		// Convert int8 to PLMath::Vector3i
		static PLMath::Vector3i ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return PLMath::Vector3i(nValue, nValue, nValue);
		}

		// Convert PLMath::Vector3i to int16
		static PLGeneral::int16 ConvertToInt16(const PLMath::Vector3i &vVector)
		{
			return static_cast<PLGeneral::int16>(ConvertToInt(vVector));
		}

		// Convert int16 to PLMath::Vector3i
		static PLMath::Vector3i ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return PLMath::Vector3i(nValue, nValue, nValue);
		}

		// Convert PLMath::Vector3i to int32
		static PLGeneral::int32 ConvertToInt32(const PLMath::Vector3i &vVector)
		{
			return static_cast<PLGeneral::int32>(ConvertToInt(vVector));
		}

		// Convert int32 to PLMath::Vector3i
		static PLMath::Vector3i ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return PLMath::Vector3i(nValue, nValue, nValue);
		}

		// Convert PLMath::Vector3i to int64
		static PLGeneral::int64 ConvertToInt64(const PLMath::Vector3i &vVector)
		{
			return static_cast<PLGeneral::int64>(ConvertToInt(vVector));
		}

		// Convert int64 to PLMath::Vector3i
		static PLMath::Vector3i ConvertFromInt64(PLGeneral::int32 nValue)
		{
			return PLMath::Vector3i(static_cast<int>(nValue), static_cast<int>(nValue), static_cast<int>(nValue));
		}

		// Convert PLMath::Vector3i to uint8
		static PLGeneral::uint8 ConvertToUInt8(const PLMath::Vector3i &vVector)
		{
			return static_cast<PLGeneral::uint8>(ConvertToInt(vVector));
		}

		// Convert uint8 to PLMath::Vector3i
		static PLMath::Vector3i ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return PLMath::Vector3i(nValue, nValue, nValue);
		}

		// Convert PLMath::Vector3i to uint16
		static PLGeneral::uint16 ConvertToUInt16(const PLMath::Vector3i &vVector)
		{
			return static_cast<PLGeneral::uint16>(ConvertToInt(vVector));
		}

		// Convert uint16 to PLMath::Vector3i
		static PLMath::Vector3i ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return PLMath::Vector3i(nValue, nValue, nValue);
		}

		// Convert PLMath::Vector3i to uint32
		static PLGeneral::uint32 ConvertToUInt32(const PLMath::Vector3i &vVector)
		{
			return static_cast<PLGeneral::uint32>(ConvertToInt(vVector));
		}

		// Convert uint32 to PLMath::Vector3i
		static PLMath::Vector3i ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return PLMath::Vector3i(nValue, nValue, nValue);
		}

		// Convert PLMath::Vector3i to uint64
		static PLGeneral::uint64 ConvertToUInt64(const PLMath::Vector3i &vVector)
		{
			return static_cast<PLGeneral::uint64>(ConvertToInt(vVector));
		}

		// Convert uint64 to PLMath::Vector3i
		static PLMath::Vector3i ConvertFromUInt64(PLGeneral::uint64 nValue)
		{
			return PLMath::Vector3i(static_cast<int>(nValue), static_cast<int>(nValue), static_cast<int>(nValue));
		}

		// Convert PLMath::Vector3i to uint_ptr
		static PLGeneral::uint_ptr ConvertToUIntPtr(const PLMath::Vector3i &vVector)
		{
			return static_cast<PLGeneral::uint_ptr>(ConvertToInt(vVector));
		}

		// Convert uint_ptr to PLMath::Vector3i
		static PLMath::Vector3i ConvertFromUIntPtr(PLGeneral::uint_ptr nValue)
		{
			return PLMath::Vector3i(static_cast<int>(nValue), static_cast<int>(nValue), static_cast<int>(nValue));
		}

		// Convert PLMath::Vector3i to float
		static float ConvertToFloat(const PLMath::Vector3i &vVector)
		{
			return static_cast<float>(ConvertToInt(vVector));
		}

		// Convert float to PLMath::Vector3i
		static PLMath::Vector3i ConvertFromFloat(float fValue)
		{
			return PLMath::Vector3i(static_cast<int>(fValue), static_cast<int>(fValue), static_cast<int>(fValue));
		}

		// Convert PLMath::Vector3i to double
		static double ConvertToDouble(const PLMath::Vector3i &vVector)
		{
			return static_cast<double>(ConvertToInt(vVector));
		}

		// Convert double to PLMath::Vector3i
		static PLMath::Vector3i ConvertFromDouble(double dValue)
		{
			return PLMath::Vector3i(static_cast<int>(dValue), static_cast<int>(dValue), static_cast<int>(dValue));
		}

		// Convert PLMath::Vector3i to string
		static PLGeneral::String ConvertToString(const PLMath::Vector3i &vVector)
		{
			return vVector.ToString();
		}

		// Convert string to PLMath::Vector3i
		static PLMath::Vector3i ConvertFromString(const PLGeneral::String &sString)
		{
			PLMath::Vector3i vVector;
			vVector.FromString(sString);
			return vVector;
		}

		// Convert real to storage type (reference is enough in here)
		static PLMath::Vector3i &ConvertRealToStorage(PLMath::Vector3i &vValue)
		{
			return vValue;
		}

		// Convert storage to real type (reference is enough in here)
		static PLMath::Vector3i &ConvertStorageToReal(PLMath::Vector3i &vValue)
		{
			return vValue;
		}


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLMATH_TYPE_VECTOR3I_INL__
