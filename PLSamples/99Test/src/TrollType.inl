/*********************************************************\
 *  File: TrollType.inl                                  *
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


#ifndef __PLSAMPLE_TROLLTYPE_INL__
#define __PLSAMPLE_TROLLTYPE_INL__
#pragma once


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for 'TrollType'
*/
template <>
class Type<TrollType> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef TrollType _Type;

		// Type ID
		static const int TypeID = 100101;

		// Get type name
		static PLGeneral::String GetTypeName() {
			return "troll";
		}

		// Convert var to troll
		static TrollType ConvertFromVar(const PLCore::DynVar *pVar)
		{
			TrollType cTroll;
			cTroll.SetValue(pVar->GetInt());
			return cTroll;
		}

		// Convert troll to bool
		static bool ConvertToBool(const TrollType &cTroll)
		{
			return (bool)(cTroll.GetValue() != 0);
		}

		// Convert bool to troll
		static TrollType ConvertFromBool(bool bValue)
		{
			TrollType cTroll;
			cTroll.SetValue((int)bValue);
			return cTroll;
		}

		// Convert troll to int
		static int ConvertToInt(const TrollType &cTroll)
		{
			return cTroll.GetValue();
		}

		// Convert int to troll
		static TrollType ConvertFromInt(int nValue)
		{
			TrollType cTroll;
			cTroll.SetValue(nValue);
			return cTroll;
		}

		// Convert troll to int8
		static PLGeneral::int8 ConvertToInt8(const TrollType &cTroll)
		{
			return (PLGeneral::int8)ConvertToInt(cTroll);
		}

		// Convert int8 to troll
		static TrollType ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return ConvertFromInt((int)nValue);
		}

		// Convert troll to int16
		static PLGeneral::int16 ConvertToInt16(const TrollType &cTroll)
		{
			return (PLGeneral::int16)ConvertToInt(cTroll);
		}

		// Convert int16 to troll
		static TrollType ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return ConvertFromInt((int)nValue);
		}

		// Convert troll to int32
		static PLGeneral::int32 ConvertToInt32(const TrollType &cTroll)
		{
			return (PLGeneral::int32)ConvertToInt(cTroll);
		}

		// Convert int32 to troll
		static TrollType ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return ConvertFromInt((int)nValue);
		}

		// Convert troll to int64
		static PLGeneral::int64 ConvertToInt64(const TrollType &cTroll)
		{
			return (PLGeneral::int64)ConvertToInt(cTroll);
		}

		// Convert int64 to troll
		static TrollType ConvertFromInt64(PLGeneral::int64 nValue)
		{
			return ConvertFromInt((int)nValue);
		}

		// Convert troll to uint8
		static PLGeneral::uint8 ConvertToUInt8(const TrollType &cTroll)
		{
			return (PLGeneral::uint8)ConvertToInt(cTroll);
		}

		// Convert uint8 to troll
		static TrollType ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return ConvertFromInt((int)nValue);
		}

		// Convert troll to uint16
		static PLGeneral::uint16 ConvertToUInt16(const TrollType &cTroll)
		{
			return (PLGeneral::uint16)ConvertToInt(cTroll);
		}

		// Convert uint16 to troll
		static TrollType ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return ConvertFromInt((int)nValue);
		}

		// Convert troll to uint32
		static PLGeneral::uint32 ConvertToUInt32(const TrollType &cTroll)
		{
			return (PLGeneral::uint32)ConvertToInt(cTroll);
		}

		// Convert uint32 to troll
		static TrollType ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return ConvertFromInt((int)nValue);
		}

		// Convert troll to uint64
		static PLGeneral::uint64 ConvertToUInt64(const TrollType &cTroll)
		{
			return (PLGeneral::uint64)ConvertToInt(cTroll);
		}

		// Convert uint64 to troll
		static TrollType ConvertFromUInt64(PLGeneral::uint64 nValue)
		{
			return ConvertFromInt((int)nValue);
		}

		// Convert troll to uint_ptr
		static PLGeneral::uint_ptr ConvertToUIntPtr(const TrollType &cTroll)
		{
			return (PLGeneral::uint_ptr)ConvertToInt(cTroll);
		}

		// Convert uint_ptr to troll
		static TrollType ConvertFromUIntPtr(PLGeneral::uint_ptr nValue)
		{
			return ConvertFromInt((int)nValue);
		}

		// Convert troll to float
		static float ConvertToFloat(const TrollType &cTroll)
		{
			return (float)cTroll.GetValue();
		}

		// Convert float to troll
		static TrollType ConvertFromFloat(float fValue)
		{
			TrollType cTroll;
			cTroll.SetValue((int)fValue);
			return cTroll;
		}

		// Convert troll to double
		static double ConvertToDouble(const TrollType &cTroll)
		{
			return (double)cTroll.GetValue();
		}

		// Convert double to troll
		static TrollType ConvertFromDouble(double dValue)
		{
			TrollType cTroll;
			cTroll.SetValue((int)dValue);
			return cTroll;
		}

		// Convert troll to string
		static PLGeneral::String ConvertToString(const TrollType &cTroll)
		{
			return cTroll.GetComment();
		}

		// Convert string to troll
		static TrollType ConvertFromString(const PLGeneral::String &sString)
		{
			TrollType cTroll;
				 if (sString.CompareNoCase("nuthin'"))	cTroll.SetValue(0);
			else if (sString.CompareNoCase("one"))		cTroll.SetValue(1);
			else if (sString.CompareNoCase("two"))		cTroll.SetValue(2);
			else if (sString.CompareNoCase("many"))		cTroll.SetValue(3);
			else										cTroll.SetValue(-1);
			return cTroll;
		}


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLSAMPLE_TROLLTYPE_INL__
