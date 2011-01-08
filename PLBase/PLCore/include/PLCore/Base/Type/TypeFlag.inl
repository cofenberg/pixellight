/*********************************************************\
 *  File: TypeFlag.inl                                   *
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


#ifndef __PLCORE_TYPE_FLAG_INL__
#define __PLCORE_TYPE_FLAG_INL__
#pragma once


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for flag types
*/
template <typename ENUM>
class Type< FlagType<ENUM> > {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef typename ENUM::_BaseType _BaseType;
		typedef typename ENUM::_BaseType _Type;
		typedef typename ENUM::_Type	 _EnumType;

		// Type ID
		static const int TypeID = Type<_BaseType>::TypeID;

		// Get type name
		static PLGeneral::String GetTypeName() {
			return Type<_BaseType>::GetTypeName();
		}

		// Convert var to type
		static _BaseType ConvertFromVar(const DynVar *pValue)
		{
			if (pValue->GetTypeID() == TypeString)
				return ConvertFromString(pValue->GetString());
			else
				return Type<_BaseType>::ConvertFromVar(pValue);
		}

		// Convert type to bool
		static bool ConvertToBool(_BaseType Value)
		{
			return Type<_BaseType>::ConvertToBool(Value);
		}

		// Convert bool to type
		static _BaseType ConvertFromBool(bool bValue)
		{
			return Type<_BaseType>::ConvertFromBool(bValue);
		}

		// Convert type to int
		static int ConvertToInt(_BaseType Value)
		{
			return Type<_BaseType>::ConvertToInt(Value);
		}

		// Convert int to type
		static _BaseType ConvertFromInt(int nValue)
		{
			return Type<_BaseType>::ConvertFromInt(nValue);
		}

		// Convert type to int8
		static PLGeneral::int8 ConvertToInt8(_BaseType Value)
		{
			return Type<_BaseType>::ConvertToInt8(Value);
		}

		// Convert int8 to type
		static _BaseType ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return Type<_BaseType>::ConvertFromInt8(nValue);
		}

		// Convert type to int16
		static PLGeneral::int16 ConvertToInt16(_BaseType Value)
		{
			return Type<_BaseType>::ConvertToInt16(Value);
		}

		// Convert int16 to type
		static _BaseType ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return Type<_BaseType>::ConvertFromInt16(nValue);
		}

		// Convert type to int32
		static PLGeneral::int32 ConvertToInt32(_BaseType Value)
		{
			return Type<_BaseType>::ConvertToInt32(Value);
		}

		// Convert int32 to type
		static _BaseType ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return Type<_BaseType>::ConvertFromInt32(nValue);
		}

		// Convert type to int64
		static PLGeneral::int64 ConvertToInt64(_BaseType Value)
		{
			return Type<_BaseType>::ConvertToInt64(Value);
		}

		// Convert int64 to type
		static _BaseType ConvertFromInt64(PLGeneral::int64 nValue)
		{
			return Type<_BaseType>::ConvertFromInt64(nValue);
		}

		// Convert type to uint8
		static PLGeneral::uint8 ConvertToUInt8(_BaseType Value)
		{
			return Type<_BaseType>::ConvertToUInt8(Value);
		}

		// Convert uint8 to type
		static _BaseType ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return Type<_BaseType>::ConvertFromUInt8(nValue);
		}

		// Convert type to uint16
		static PLGeneral::uint16 ConvertToUInt16(_BaseType Value)
		{
			return Type<_BaseType>::ConvertToUInt16(Value);
		}

		// Convert uint16 to type
		static _BaseType ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return Type<_BaseType>::ConvertFromUInt16(nValue);
		}

		// Convert type to uint32
		static PLGeneral::uint32 ConvertToUInt32(_BaseType Value)
		{
			return Type<_BaseType>::ConvertToUInt32(Value);
		}

		// Convert uint32 to type
		static _BaseType ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return Type<_BaseType>::ConvertFromUInt32(nValue);
		}

		// Convert type to uint64
		static PLGeneral::uint64 ConvertToUInt64(_BaseType Value)
		{
			return Type<_BaseType>::ConvertToUInt64(Value);
		}

		// Convert uint64 to type
		static _BaseType ConvertFromUInt64(PLGeneral::uint64 nValue)
		{
			return Type<_BaseType>::ConvertFromUInt64(nValue);
		}

		// Convert type to uint_ptr
		static PLGeneral::uint_ptr ConvertToUIntPtr(_BaseType Value)
		{
			return Type<_BaseType>::ConvertToUIntPtr(Value);
		}

		// Convert uint_ptr to type
		static _BaseType ConvertFromUIntPtr(PLGeneral::uint_ptr nValue)
		{
			return Type<_BaseType>::ConvertFromUIntPtr(nValue);
		}

		// Convert type to float
		static float ConvertToFloat(_BaseType Value)
		{
			return Type<_BaseType>::ConvertToFloat(Value);
		}

		// Convert float to type
		static _BaseType ConvertFromFloat(float fValue)
		{
			return Type<_BaseType>::ConvertFromFloat(fValue);
		}

		// Convert type to double
		static double ConvertToDouble(_BaseType Value)
		{
			return Type<_BaseType>::ConvertToDouble(Value);
		}

		// Convert double to type
		static _BaseType ConvertFromDouble(double dValue)
		{
			return Type<_BaseType>::ConvertFromDouble(dValue);
		}

		// Convert type to string
		static PLGeneral::String ConvertToString(_BaseType Value)
		{
			// Init return value
			PLGeneral::String sFlags;
			_BaseType nValue = Value;

			// Loop through enum values
			PLGeneral::String sName, sDesc;
			_EnumType nFlag;
			for (int i=0; ENUM::GetEnumValue(i, nFlag, sName, sDesc); i++) {
				// Check if flag is set
				if (nValue & nFlag) {
					if (sFlags.GetLength() > 0) sFlags += "|";
					sFlags += sName;
					nValue = (nValue & ~nFlag);
				}
			}

			// Add rest
			if (nValue != 0) {
				if (sFlags.GetLength() > 0) sFlags += "|";
				sFlags += nValue;
			}

			// Return flags
			if (sFlags.GetLength() == 0) sFlags = "0";
			return sFlags;
		}

		// Convert string to type
		static _BaseType ConvertFromString(const PLGeneral::String &sString)
		{
			// Init return value
			_BaseType nFlags = 0;

			// Tokenizer flags string
			if (sString.GetLength()) {
				PLGeneral::Tokenizer cTokenizer;
				cTokenizer.Start(sString);
				cTokenizer.SetDelimiters(" \t\r\n&,|");
				while (cTokenizer.GetNextToken().GetLength()) {
					// Get next token
					PLGeneral::String sToken = cTokenizer.GetToken();
					PLGeneral::String sDesc;

					// Try to convert token to number, else look up name in enum
					_EnumType nValue = (_EnumType)sToken.GetInt();
					if ((_BaseType)nValue == 0) ENUM::GetEnumValue(-1, nValue, sToken, sDesc);
					nFlags |= nValue;
				}
				cTokenizer.Stop();
			}

			// Return flags value
			return nFlags;
		}


};


#endif // __PLCORE_TYPE_FLAG_INL__
