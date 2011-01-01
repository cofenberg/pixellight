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
		typedef PLGraphics::Color4 _Type;

		// Type ID
		static const int TypeID = 2002;

		// Get type name
		static PLGeneral::String GetTypeName() {
			return "color4";
		}

		// Convert var to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromVar(const DynVar *pVar)
		{
			const float fValue = pVar->GetFloat();
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
			return PLGraphics::Color4((float)nValue, (float)nValue, (float)nValue, (float)nValue);
		}

		// Convert PLGraphics::Color4 to int8
		static PLGeneral::int8 ConvertToInt8(const PLGraphics::Color4 &cColor)
		{
			return (PLGeneral::int8)ConvertToInt(cColor);
		}

		// Convert int8 to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return PLGraphics::Color4((float)nValue, (float)nValue, (float)nValue, (float)nValue);
		}

		// Convert PLGraphics::Color4 to int16
		static PLGeneral::int16 ConvertToInt16(const PLGraphics::Color4 &cColor)
		{
			return (PLGeneral::int16)ConvertToInt(cColor);
		}

		// Convert int16 to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return PLGraphics::Color4((float)nValue, (float)nValue, (float)nValue, (float)nValue);
		}

		// Convert PLGraphics::Color4 to int32
		static PLGeneral::int32 ConvertToInt32(const PLGraphics::Color4 &cColor)
		{
			return (PLGeneral::int32)ConvertToInt(cColor);
		}

		// Convert int32 to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return PLGraphics::Color4((float)nValue, (float)nValue, (float)nValue, (float)nValue);
		}

		// Convert PLGraphics::Color4 to int64
		static PLGeneral::int64 ConvertToInt64(const PLGraphics::Color4 &cColor)
		{
			return (PLGeneral::int64)ConvertToInt(cColor);
		}

		// Convert int64 to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromInt64(PLGeneral::int64 nValue)
		{
			return PLGraphics::Color4((float)nValue, (float)nValue, (float)nValue, (float)nValue);
		}

		// Convert PLGraphics::Color4 to uint8
		static PLGeneral::uint8 ConvertToUInt8(const PLGraphics::Color4 &cColor)
		{
			return (PLGeneral::uint8)ConvertToInt(cColor);
		}

		// Convert uint8 to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return PLGraphics::Color4((float)nValue, (float)nValue, (float)nValue, (float)nValue);
		}

		// Convert PLGraphics::Color4 to uint16
		static PLGeneral::uint16 ConvertToUInt16(const PLGraphics::Color4 &cColor)
		{
			return (PLGeneral::uint16)ConvertToInt(cColor);
		}

		// Convert uint16 to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return PLGraphics::Color4((float)nValue, (float)nValue, (float)nValue, (float)nValue);
		}

		// Convert PLGraphics::Color4 to uint32
		static PLGeneral::uint32 ConvertToUInt32(const PLGraphics::Color4 &cColor)
		{
			return (PLGeneral::uint32)ConvertToInt(cColor);
		}

		// Convert uint32 to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return PLGraphics::Color4((float)nValue, (float)nValue, (float)nValue, (float)nValue);
		}

		// Convert PLGraphics::Color4 to uint64
		static PLGeneral::uint64 ConvertToUInt64(const PLGraphics::Color4 &cColor)
		{
			return (PLGeneral::uint64)ConvertToInt(cColor);
		}

		// Convert uint64 to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromUInt64(PLGeneral::uint64 nValue)
		{
			return PLGraphics::Color4((float)nValue, (float)nValue, (float)nValue, (float)nValue);
		}

		// Convert PLGraphics::Color4 to uint_ptr
		static PLGeneral::uint_ptr ConvertToUIntPtr(const PLGraphics::Color4 &cColor)
		{
			return (PLGeneral::uint_ptr)ConvertToInt(cColor);
		}

		// Convert uint_ptr to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromUIntPtr(PLGeneral::uint_ptr nValue)
		{
			return PLGraphics::Color4((float)nValue, (float)nValue, (float)nValue, (float)nValue);
		}

		// Convert PLGraphics::Color4 to float
		static float ConvertToFloat(const PLGraphics::Color4 &cColor)
		{
			return (float)ConvertToInt(cColor);
		}

		// Convert float to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromFloat(float fValue)
		{
			return PLGraphics::Color4(fValue, fValue, fValue, fValue);
		}

		// Convert PLGraphics::Color4 to double
		static double ConvertToDouble(const PLGraphics::Color4 &cColor)
		{
			return (double)ConvertToInt(cColor);
		}

		// Convert double to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromDouble(double dValue)
		{
			return PLGraphics::Color4((float)dValue, (float)dValue, (float)dValue, (float)dValue);
		}

		// Convert PLGraphics::Color4 to string
		static PLGeneral::String ConvertToString(const PLGraphics::Color4 &cColor)
		{
			return cColor.ToString();
		}

		// Convert string to PLGraphics::Color4
		static PLGraphics::Color4 ConvertFromString(const PLGeneral::String &sString)
		{
			PLGraphics::Color4 cColor;
			cColor.FromString(sString);
			return cColor;
		}


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLGRAPHICS_TYPE_COLOR4_INL__
