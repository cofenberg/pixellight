/*********************************************************\
 *  File: TypeColor4.inl                                 *
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


#ifndef __PLGRAPHICS_TYPE_COLOR4_INL__
#define __PLGRAPHICS_TYPE_COLOR4_INL__
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
*    Type wrapper for 'PLGraphics::Color4'
*/
template <>
class Type<PLGraphics::Color4> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef PLGraphics::Color4 _Type;			/**< Real type */
		typedef PLGraphics::Color4 _StorageType;	/**< Storage type, for this type identical to the real type */

		// Type ID
		static const int TypeID = 2002;

		// Get type name
		static String GetTypeName()
		{
			return "color4";
		}

		// Convert var to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromVar(const DynVar &cVar)
		{
			const float fValue = cVar.GetFloat();
			return PLGraphics::Color4(fValue, fValue, fValue, fValue);
		}

		// Convert PLGraphics::Color4 to bool
		static bool ConvertToBool(const PLGraphics::Color4 &cColor)
		{
			return cColor.IsValid();
		}

		// Convert bool to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromBool(bool bValue)
		{
			const float fValue = bValue ? 1.0f : 0.0f;
			return PLGraphics::Color4(fValue, fValue, fValue, fValue);
		}

		// Convert PLGraphics::Color4 to int
		static int ConvertToInt(const PLGraphics::Color4 &cColor)
		{
			return cColor.IsValid();
		}

		// Convert int to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromInt(int nValue)
		{
			return PLGraphics::Color4(static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue));
		}

		// Convert PLGraphics::Color4 to int8
		static int8 ConvertToInt8(const PLGraphics::Color4 &cColor)
		{
			return static_cast<int8>(ConvertToInt(cColor));
		}

		// Convert int8 to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromInt8(int8 nValue)
		{
			return PLGraphics::Color4(static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue));
		}

		// Convert PLGraphics::Color4 to int16
		static int16 ConvertToInt16(const PLGraphics::Color4 &cColor)
		{
			return static_cast<int16>(ConvertToInt(cColor));
		}

		// Convert int16 to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromInt16(int16 nValue)
		{
			return PLGraphics::Color4(static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue));
		}

		// Convert PLGraphics::Color4 to int32
		static int32 ConvertToInt32(const PLGraphics::Color4 &cColor)
		{
			return static_cast<int32>(ConvertToInt(cColor));
		}

		// Convert int32 to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromInt32(int32 nValue)
		{
			return PLGraphics::Color4(static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue));
		}

		// Convert PLGraphics::Color4 to int64
		static int64 ConvertToInt64(const PLGraphics::Color4 &cColor)
		{
			return static_cast<int64>(ConvertToInt(cColor));
		}

		// Convert int64 to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromInt64(int64 nValue)
		{
			return PLGraphics::Color4(static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue));
		}

		// Convert PLGraphics::Color4 to uint8
		static uint8 ConvertToUInt8(const PLGraphics::Color4 &cColor)
		{
			return static_cast<uint8>(ConvertToInt(cColor));
		}

		// Convert uint8 to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromUInt8(uint8 nValue)
		{
			return PLGraphics::Color4(static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue));
		}

		// Convert PLGraphics::Color4 to uint16
		static uint16 ConvertToUInt16(const PLGraphics::Color4 &cColor)
		{
			return static_cast<uint16>(ConvertToInt(cColor));
		}

		// Convert uint16 to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromUInt16(uint16 nValue)
		{
			return PLGraphics::Color4(static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue));
		}

		// Convert PLGraphics::Color4 to uint32
		static uint32 ConvertToUInt32(const PLGraphics::Color4 &cColor)
		{
			return static_cast<uint32>(ConvertToInt(cColor));
		}

		// Convert uint32 to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromUInt32(uint32 nValue)
		{
			return PLGraphics::Color4(static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue));
		}

		// Convert PLGraphics::Color4 to uint64
		static uint64 ConvertToUInt64(const PLGraphics::Color4 &cColor)
		{
			return static_cast<uint64>(ConvertToInt(cColor));
		}

		// Convert uint64 to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromUInt64(uint64 nValue)
		{
			return PLGraphics::Color4(static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue));
		}

		// Convert PLGraphics::Color4 to uint_ptr
		static uint_ptr ConvertToUIntPtr(const PLGraphics::Color4 &cColor)
		{
			return static_cast<uint_ptr>(ConvertToInt(cColor));
		}

		// Convert uint_ptr to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromUIntPtr(uint_ptr nValue)
		{
			return PLGraphics::Color4(static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue), static_cast<float>(nValue));
		}

		// Convert PLGraphics::Color4 to float
		static float ConvertToFloat(const PLGraphics::Color4 &cColor)
		{
			return static_cast<float>(ConvertToInt(cColor));
		}

		// Convert float to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromFloat(float fValue)
		{
			return PLGraphics::Color4(fValue, fValue, fValue, fValue);
		}

		// Convert PLGraphics::Color4 to double
		static double ConvertToDouble(const PLGraphics::Color4 &cColor)
		{
			return static_cast<double>(ConvertToInt(cColor));
		}

		// Convert double to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromDouble(double dValue)
		{
			return PLGraphics::Color4(static_cast<float>(dValue), static_cast<float>(dValue), static_cast<float>(dValue), static_cast<float>(dValue));
		}

		// Convert PLGraphics::Color4 to string
		static String ConvertToString(const PLGraphics::Color4 &cColor)
		{
			return cColor.ToString();
		}

		// Convert string to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromString(const String &sString)
		{
			PLGraphics::Color4 cColor;
			cColor.FromString(sString);
			return cColor;
		}

		// Convert real to storage type (reference is enough in here)
		static PLGraphics::Color4 &ConvertRealToStorage(PLGraphics::Color4 &cValue)
		{
			return cValue;
		}

		// Convert storage to real type (reference is enough in here)
		static PLGraphics::Color4 &ConvertStorageToReal(PLGraphics::Color4 &cValue)
		{
			return cValue;
		}


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLGRAPHICS_TYPE_COLOR4_INL__
