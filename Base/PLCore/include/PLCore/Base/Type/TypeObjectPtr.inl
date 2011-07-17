/*********************************************************\
 *  File: TypeObjectPtr.inl                              *
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


#ifndef __PLCORE_TYPE_OBJECTPTR_INL__
#define __PLCORE_TYPE_OBJECTPTR_INL__
#pragma once


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Object;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for 'Object*'
*/
template <>
class Type<Object*> {


	//[-------------------------------------------------------]
	//[ Public static type information                        ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef Object *_Type;			/**< Real type */
		typedef Object *_StorageType;	/**< Storage type, for this type identical to the real type */

		// Type ID
		static const int TypeID = TypeObjectPtr;

		// Get type name
		static PLGeneral::String GetTypeName()
		{
			return "Object*";
		}

		// Convert var to pointer
		static Object *ConvertFromVar(const DynVar *pValue)
		{
			return reinterpret_cast<Object*>(pValue->GetUIntPtr());
		}

		// Convert pointer to bool
		static bool ConvertToBool(Object *pValue)
		{
			return static_cast<bool>(pValue != nullptr);
		}

		// Convert bool to pointer
		static Object *ConvertFromBool(bool bValue)
		{
			return nullptr;
		}

		// Convert pointer to int
		static int ConvertToInt(Object *pValue)
		{
			return static_cast<int>(reinterpret_cast<PLGeneral::uint_ptr>(pValue));
		}

		// Convert int to pointer
		static Object *ConvertFromInt(int nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to int8
		static PLGeneral::int8 ConvertToInt8(Object *pValue)
		{
			return static_cast<PLGeneral::int8>(reinterpret_cast<PLGeneral::uint_ptr>(pValue));
		}

		// Convert int8 to pointer
		static Object *ConvertFromInt8(PLGeneral::int8 nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to int16
		static PLGeneral::int16 ConvertToInt16(Object *pValue)
		{
			return static_cast<PLGeneral::int16>(reinterpret_cast<PLGeneral::uint_ptr>(pValue));
		}

		// Convert int16 to pointer
		static Object *ConvertFromInt16(PLGeneral::int16 nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to int32
		static PLGeneral::int32 ConvertToInt32(Object *pValue)
		{
			return static_cast<PLGeneral::int32>(reinterpret_cast<PLGeneral::uint_ptr>(pValue));
		}

		// Convert int32 to pointer
		static Object *ConvertFromInt32(PLGeneral::int32 nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to int64
		static PLGeneral::int64 ConvertToInt64(Object *pValue)
		{
			return static_cast<PLGeneral::int64>(reinterpret_cast<PLGeneral::uint_ptr>(pValue));
		}

		// Convert int64 to pointer
		static Object *ConvertFromInt64(PLGeneral::int64 nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to uint8
		static PLGeneral::uint8 ConvertToUInt8(Object *pValue)
		{
			return static_cast<PLGeneral::uint8>(reinterpret_cast<PLGeneral::uint_ptr>(pValue));
		}

		// Convert uint8 to pointer
		static Object *ConvertFromUInt8(PLGeneral::uint8 nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to uint16
		static PLGeneral::uint16 ConvertToUInt16(Object *pValue)
		{
			return static_cast<PLGeneral::uint16>(reinterpret_cast<PLGeneral::uint_ptr>(pValue));
		}

		// Convert uint16 to pointer
		static Object *ConvertFromUInt16(PLGeneral::uint16 nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to uint32
		static PLGeneral::uint32 ConvertToUInt32(Object *pValue)
		{
			return static_cast<PLGeneral::uint32>(reinterpret_cast<PLGeneral::uint_ptr>(pValue));
		}

		// Convert uint32 to pointer
		static Object *ConvertFromUInt32(PLGeneral::uint32 nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to uint64
		static PLGeneral::uint64 ConvertToUInt64(Object *pValue)
		{
			return static_cast<PLGeneral::uint64>(reinterpret_cast<PLGeneral::uint_ptr>(pValue));
		}

		// Convert uint64 to pointer
		static Object *ConvertFromUInt64(PLGeneral::uint64 nValue)
		{

			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to uint_ptr
		static PLGeneral::uint_ptr ConvertToUIntPtr(Object *pValue)
		{
			return reinterpret_cast<PLGeneral::uint_ptr>(pValue);
		}

		// Convert uint_ptr to pointer
		static Object *ConvertFromUIntPtr(PLGeneral::uint_ptr nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to float
		static float ConvertToFloat(Object *pValue)
		{
			// No conversion from pointer types in non-integral types!
			return 0.0f;
		}

		// Convert float to pointer
		static Object *ConvertFromFloat(float fValue)
		{
			// No conversion from pointer types in non-integral types!
			return nullptr;
		}

		// Convert pointer to double
		static double ConvertToDouble(Object *pValue)
		{
			// No conversion from pointer types in non-integral types!
			return 0.0;
		}

		// Convert double to pointer
		static Object *ConvertFromDouble(double dValue)
		{
			// No conversion from pointer types in non-integral types!
			return nullptr;
		}

		// Convert pointer to string
		static PLGeneral::String ConvertToString(Object *pValue)
		{
			return PLGeneral::String() + reinterpret_cast<PLGeneral::uint_ptr>(pValue);
		}

		// Convert string to pointer
		static Object *ConvertFromString(const PLGeneral::String &sString)
		{
			return reinterpret_cast<Object*>(sString.GetUIntPtr());
		}

		// Convert real to storage type
		static Object *ConvertRealToStorage(Object *pValue)
		{
			return pValue;
		}

		// Convert storage to real type
		static Object *ConvertStorageToReal(Object *pValue)
		{
			return pValue;
		}

};


#endif // __PLCORE_TYPE_OBJECTPTR_INL__
