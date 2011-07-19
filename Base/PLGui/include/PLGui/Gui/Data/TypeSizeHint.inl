/*********************************************************\
 *  File: TypeColor3.inl                                *
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


#ifndef __PLGUI_TYPE_SIZEHINT_INL__
#define __PLGUI_TYPE_SIZEHINT_INL__
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
*    Type wrapper for 'PLGui::SizeHint'
*/
template <>
class Type<PLGui::SizeHint> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef PLGui::SizeHint _Type;			/**< Real type */
		typedef PLGui::SizeHint _StorageType;

		// Type ID
		static const int TypeID = 2201;

		// Get type name
		static String GetTypeName()
		{
			return "sizehint";
		}

		// Convert var to PLGui::SizeHint
		static PLGui::SizeHint ConvertFromVar(const DynVar *pVar)
		{
			PLGui::SizeHint cSize;
			cSize.FromString(pVar->GetString());
			return cSize;
		}

		// Convert PLGui::SizeHint to bool
		static bool ConvertToBool(const PLGui::SizeHint &cSize)
		{
			return (cSize.GetPolicy() != PLGui::SizeHint::Floating);
		}

		// Convert bool to PLGui::SizeHint
		static PLGui::SizeHint ConvertFromBool(bool bValue)
		{
			return PLGui::SizeHint();
		}

		// Convert PLGui::SizeHint to int
		static int ConvertToInt(const PLGui::SizeHint &cSize)
		{
			return static_cast<int>(cSize.GetSize());
		}

		// Convert int to PLGui::SizeHint
		static PLGui::SizeHint ConvertFromInt(int nValue)
		{
			return PLGui::SizeHint(PLGui::SizeHint::Pixel, nValue);
		}

		// Convert PLGui::SizeHint to int8
		static int8 ConvertToInt8(const PLGui::SizeHint &cSize)
		{
			return static_cast<int8>(cSize.GetSize());
		}

		// Convert int8 to PLGui::SizeHint
		static PLGui::SizeHint ConvertFromInt8(int8 nValue)
		{
			return PLGui::SizeHint(PLGui::SizeHint::Pixel, nValue);
		}

		// Convert PLGui::SizeHint to int16
		static int16 ConvertToInt16(const PLGui::SizeHint &cSize)
		{
			return static_cast<int16>(cSize.GetSize());
		}

		// Convert int16 to PLGui::SizeHint
		static PLGui::SizeHint ConvertFromInt16(int16 nValue)
		{
			return PLGui::SizeHint(PLGui::SizeHint::Pixel, nValue);
		}

		// Convert PLGui::SizeHint to int32
		static int32 ConvertToInt32(const PLGui::SizeHint &cSize)
		{
			return static_cast<int32>(cSize.GetSize());
		}

		// Convert int32 to PLGui::SizeHint
		static PLGui::SizeHint ConvertFromInt32(int32 nValue)
		{
			return PLGui::SizeHint(PLGui::SizeHint::Pixel, nValue);
		}

		// Convert PLGui::SizeHint to int64
		static int64 ConvertToInt64(const PLGui::SizeHint &cSize)
		{
			return static_cast<int64>(cSize.GetSize());
		}

		// Convert int64 to PLGui::SizeHint
		static PLGui::SizeHint ConvertFromInt64(int64 nValue)
		{
			return PLGui::SizeHint(PLGui::SizeHint::Pixel, static_cast<uint32>(nValue));
		}

		// Convert PLGui::SizeHint to int8
		static uint8 ConvertToUInt8(const PLGui::SizeHint &cSize)
		{
			return static_cast<uint8>(cSize.GetSize());
		}

		// Convert uint8 to PLGui::SizeHint
		static PLGui::SizeHint ConvertFromUInt8(uint8 nValue)
		{
			return PLGui::SizeHint(PLGui::SizeHint::Pixel, nValue);
		}

		// Convert PLGui::SizeHint to uint16
		static uint16 ConvertToUInt16(const PLGui::SizeHint &cSize)
		{
			return static_cast<uint16>(cSize.GetSize());
		}

		// Convert uint16 to PLGui::SizeHint
		static PLGui::SizeHint ConvertFromUInt16(uint16 nValue)
		{
			return PLGui::SizeHint(PLGui::SizeHint::Pixel, nValue);
		}

		// Convert PLGui::SizeHint to uint32
		static uint32 ConvertToUInt32(const PLGui::SizeHint &cSize)
		{
			return static_cast<uint32>(cSize.GetSize());
		}

		// Convert uint32 to PLGui::SizeHint
		static PLGui::SizeHint ConvertFromUInt32(uint32 nValue)
		{
			return PLGui::SizeHint(PLGui::SizeHint::Pixel, nValue);
		}

		// Convert PLGui::SizeHint to uint64
		static uint64 ConvertToUInt64(const PLGui::SizeHint &cSize)
		{
			return static_cast<uint64>(cSize.GetSize());
		}

		// Convert uint64 to PLGui::SizeHint
		static PLGui::SizeHint ConvertFromUInt64(uint64 nValue)
		{
			return PLGui::SizeHint(PLGui::SizeHint::Pixel, static_cast<uint32>(nValue));
		}

		// Convert PLGui::SizeHint to uint_ptr
		static uint_ptr ConvertToUIntPtr(const PLGui::SizeHint &cSize)
		{
			return static_cast<uint_ptr>(cSize.GetSize());
		}

		// Convert uint_ptr to PLGui::SizeHint
		static PLGui::SizeHint ConvertFromUIntPtr(uint_ptr nValue)
		{
			return PLGui::SizeHint(PLGui::SizeHint::Pixel, static_cast<uint32>(nValue));
		}

		// Convert PLGui::SizeHint to float
		static float ConvertToFloat(const PLGui::SizeHint &cSize)
		{
			return cSize.GetSizeFloat();
		}

		// Convert float to PLGui::SizeHint
		static PLGui::SizeHint ConvertFromFloat(float fValue)
		{
			PLGui::SizeHint cSize(PLGui::SizeHint::Pixel);
			cSize.SetSizeFloat(fValue);
			return cSize;
		}

		// Convert PLGui::SizeHint to double
		static double ConvertToDouble(const PLGui::SizeHint &cSize)
		{
			return static_cast<double>(cSize.GetSizeFloat());
		}

		// Convert double to PLGui::SizeHint
		static PLGui::SizeHint ConvertFromDouble(double dValue)
		{
			PLGui::SizeHint cSize(PLGui::SizeHint::Pixel);
			cSize.SetSizeFloat(static_cast<float>(dValue));
			return cSize;
		}

		// Convert PLGui::SizeHint to string
		static String ConvertToString(const PLGui::SizeHint &cSize)
		{
			return cSize.ToString();
		}

		// Convert string to PLGui::SizeHint
		static PLGui::SizeHint ConvertFromString(const String &sString)
		{
			PLGui::SizeHint cSize;
			cSize.FromString(sString);
			return cSize;
		}

		// Convert real to storage type (reference is enough in here)
		static PLGui::SizeHint &ConvertRealToStorage(PLGui::SizeHint &nValue)
		{
			return nValue;
		}

		// Convert storage to real type (reference is enough in here)
		static PLGui::SizeHint &ConvertStorageToReal(PLGui::SizeHint &nValue)
		{
			return nValue;
		}


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLGUI_TYPE_SIZEHINT_INL__
