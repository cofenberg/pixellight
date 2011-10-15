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
		static String GetTypeName()
		{
			return "Object*";
		}

		// Convert var to pointer
		static Object *ConvertFromVar(const DynVar &cValue)
		{
			return reinterpret_cast<Object*>(cValue.GetUIntPtr());
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
			return static_cast<int>(reinterpret_cast<uint_ptr>(pValue));
		}

		// Convert int to pointer
		static Object *ConvertFromInt(int nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to int8
		static int8 ConvertToInt8(Object *pValue)
		{
			return static_cast<int8>(reinterpret_cast<uint_ptr>(pValue));
		}

		// Convert int8 to pointer
		static Object *ConvertFromInt8(int8 nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to int16
		static int16 ConvertToInt16(Object *pValue)
		{
			return static_cast<int16>(reinterpret_cast<uint_ptr>(pValue));
		}

		// Convert int16 to pointer
		static Object *ConvertFromInt16(int16 nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to int32
		static int32 ConvertToInt32(Object *pValue)
		{
			return static_cast<int32>(reinterpret_cast<uint_ptr>(pValue));
		}

		// Convert int32 to pointer
		static Object *ConvertFromInt32(int32 nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to int64
		static int64 ConvertToInt64(Object *pValue)
		{
			return static_cast<int64>(reinterpret_cast<uint_ptr>(pValue));
		}

		// Convert int64 to pointer
		static Object *ConvertFromInt64(int64 nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to uint8
		static uint8 ConvertToUInt8(Object *pValue)
		{
			return static_cast<uint8>(reinterpret_cast<uint_ptr>(pValue));
		}

		// Convert uint8 to pointer
		static Object *ConvertFromUInt8(uint8 nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to uint16
		static uint16 ConvertToUInt16(Object *pValue)
		{
			return static_cast<uint16>(reinterpret_cast<uint_ptr>(pValue));
		}

		// Convert uint16 to pointer
		static Object *ConvertFromUInt16(uint16 nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to uint32
		static uint32 ConvertToUInt32(Object *pValue)
		{
			return static_cast<uint32>(reinterpret_cast<uint_ptr>(pValue));
		}

		// Convert uint32 to pointer
		static Object *ConvertFromUInt32(uint32 nValue)
		{
			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to uint64
		static uint64 ConvertToUInt64(Object *pValue)
		{
			return static_cast<uint64>(reinterpret_cast<uint_ptr>(pValue));
		}

		// Convert uint64 to pointer
		static Object *ConvertFromUInt64(uint64 nValue)
		{

			return reinterpret_cast<Object*>(nValue);
		}

		// Convert pointer to uint_ptr
		static uint_ptr ConvertToUIntPtr(Object *pValue)
		{
			return reinterpret_cast<uint_ptr>(pValue);
		}

		// Convert uint_ptr to pointer
		static Object *ConvertFromUIntPtr(uint_ptr nValue)
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
		static String ConvertToString(Object *pValue)
		{
			return String() + reinterpret_cast<uint_ptr>(pValue);
		}

		// Convert string to pointer
		static Object *ConvertFromString(const String &sString)
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
