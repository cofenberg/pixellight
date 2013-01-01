/*********************************************************\
 *  File: TrollType.inl                                  *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
		typedef TrollType _Type;		/**< Real type */
		typedef TrollType _StorageType;	/**< Storage type, for this type identical to the real type */

		// Type ID
		static const int TypeID = 100101;

		// Get type name
		static String GetTypeName()
		{
			return "troll";
		}

		// Convert var to troll
		static TrollType ConvertFromVar(const PLCore::DynVar &cVar)
		{
			TrollType cTroll;
			cTroll.SetValue(cVar.GetInt());
			return cTroll;
		}

		// Convert troll to bool
		static bool ConvertToBool(const TrollType &cTroll)
		{
			return static_cast<bool>(cTroll.GetValue() != 0);
		}

		// Convert bool to troll
		static TrollType ConvertFromBool(bool bValue)
		{
			TrollType cTroll;
			cTroll.SetValue(static_cast<int>(bValue));
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
		static int8 ConvertToInt8(const TrollType &cTroll)
		{
			return static_cast<int8>(ConvertToInt(cTroll));
		}

		// Convert int8 to troll
		static TrollType ConvertFromInt8(int8 nValue)
		{
			return ConvertFromInt(static_cast<int>(nValue));
		}

		// Convert troll to int16
		static int16 ConvertToInt16(const TrollType &cTroll)
		{
			return static_cast<int16>(ConvertToInt(cTroll));
		}

		// Convert int16 to troll
		static TrollType ConvertFromInt16(int16 nValue)
		{
			return ConvertFromInt(static_cast<int>(nValue));
		}

		// Convert troll to int32
		static int32 ConvertToInt32(const TrollType &cTroll)
		{
			return static_cast<int32>(ConvertToInt(cTroll));
		}

		// Convert int32 to troll
		static TrollType ConvertFromInt32(int32 nValue)
		{
			return ConvertFromInt(static_cast<int>(nValue));
		}

		// Convert troll to int64
		static int64 ConvertToInt64(const TrollType &cTroll)
		{
			return static_cast<int64>(ConvertToInt(cTroll));
		}

		// Convert int64 to troll
		static TrollType ConvertFromInt64(int64 nValue)
		{
			return ConvertFromInt(static_cast<int>(nValue));
		}

		// Convert troll to uint8
		static uint8 ConvertToUInt8(const TrollType &cTroll)
		{
			return static_cast<uint8>(ConvertToInt(cTroll));
		}

		// Convert uint8 to troll
		static TrollType ConvertFromUInt8(uint8 nValue)
		{
			return ConvertFromInt(static_cast<int>(nValue));
		}

		// Convert troll to uint16
		static uint16 ConvertToUInt16(const TrollType &cTroll)
		{
			return static_cast<uint16>(ConvertToInt(cTroll));
		}

		// Convert uint16 to troll
		static TrollType ConvertFromUInt16(uint16 nValue)
		{
			return ConvertFromInt(static_cast<int>(nValue));
		}

		// Convert troll to uint32
		static uint32 ConvertToUInt32(const TrollType &cTroll)
		{
			return static_cast<uint32>(ConvertToInt(cTroll));
		}

		// Convert uint32 to troll
		static TrollType ConvertFromUInt32(uint32 nValue)
		{
			return ConvertFromInt(static_cast<int>(nValue));
		}

		// Convert troll to uint64
		static uint64 ConvertToUInt64(const TrollType &cTroll)
		{
			return static_cast<uint64>(ConvertToInt(cTroll));
		}

		// Convert uint64 to troll
		static TrollType ConvertFromUInt64(uint64 nValue)
		{
			return ConvertFromInt(static_cast<int>(nValue));
		}

		// Convert troll to uint_ptr
		static uint_ptr ConvertToUIntPtr(const TrollType &cTroll)
		{
			return static_cast<uint_ptr>(ConvertToInt(cTroll));
		}

		// Convert uint_ptr to troll
		static TrollType ConvertFromUIntPtr(uint_ptr nValue)
		{
			return ConvertFromInt(static_cast<int>(nValue));
		}

		// Convert troll to float
		static float ConvertToFloat(const TrollType &cTroll)
		{
			return static_cast<float>(cTroll.GetValue());
		}

		// Convert float to troll
		static TrollType ConvertFromFloat(float fValue)
		{
			TrollType cTroll;
			cTroll.SetValue(static_cast<int>(fValue));
			return cTroll;
		}

		// Convert troll to double
		static double ConvertToDouble(const TrollType &cTroll)
		{
			return static_cast<double>(cTroll.GetValue());
		}

		// Convert double to troll
		static TrollType ConvertFromDouble(double dValue)
		{
			TrollType cTroll;
			cTroll.SetValue(static_cast<int>(dValue));
			return cTroll;
		}

		// Convert troll to string
		static String ConvertToString(const TrollType &cTroll)
		{
			return cTroll.GetComment();
		}

		// Convert string to troll
		static TrollType ConvertFromString(const String &sString)
		{
			TrollType cTroll;
				 if (sString.CompareNoCase("nuthin'"))	cTroll.SetValue(0);
			else if (sString.CompareNoCase("one"))		cTroll.SetValue(1);
			else if (sString.CompareNoCase("two"))		cTroll.SetValue(2);
			else if (sString.CompareNoCase("many"))		cTroll.SetValue(3);
			else										cTroll.SetValue(-1);
			return cTroll;
		}

		// Convert real to storage type (reference is enough in here)
		static TrollType &ConvertRealToStorage(TrollType &cValue)
		{
			return cValue;
		}

		// Convert storage to real type (reference is enough in here)
		static TrollType &ConvertStorageToReal(TrollType &cValue)
		{
			return cValue;
		}


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLSAMPLE_TROLLTYPE_INL__
