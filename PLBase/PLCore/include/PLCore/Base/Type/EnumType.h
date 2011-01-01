/*********************************************************\
 *  File: EnumType.h                                     *
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


#ifndef __PLCORE_ENUMTYPE_H__
#define __PLCORE_ENUMTYPE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/PLCore.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Enum type wrapper (for plain enum types without RTTI interface)
*/
template <typename ENUM>
class EnumTypePlain {
};


/**
*  @brief
*    Enum type wrapper
*/
template <typename ENUM>
class EnumType {


	//[-------------------------------------------------------]
	//[ Public data types                                     ]
	//[-------------------------------------------------------]
	public:
		typedef typename ENUM::_BaseType _BaseType;
		typedef typename ENUM::_Type	 _Type;


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		static int GetNumOfEnumValues() {
			PLGeneral::String sEnum, sDesc;
			_Type nValue;
			int nIndex = 0;
			for (nIndex=0; ENUM::GetEnumValue(nIndex, nValue, sEnum, sDesc); nIndex++);
			return nIndex;
		}

		static PLGeneral::String GetEnumName(int nIndex) {
			PLGeneral::String sEnum, sDesc;
			_Type nValue;
			ENUM::GetEnumValue(nIndex, nValue, sEnum, sDesc);
			return sEnum;
		}

		static _Type GetEnumValue(const PLGeneral::String &sName) {
			PLGeneral::String sEnum = sName;
			PLGeneral::String sDesc;
			_Type nValue;
			ENUM::GetEnumValue(-1, nValue, sEnum, sDesc);
			return nValue;
		}

		static PLGeneral::String GetEnumDescription(const PLGeneral::String &sName) {
			PLGeneral::String sEnum = sName;
			PLGeneral::String sDesc;
			_Type nValue;
			ENUM::GetEnumValue(-1, nValue, sEnum, sDesc);
			return sDesc;
		}


};


/**
*  @brief
*    Flag type wrapper
*/
template <typename ENUM>
class FlagType {


	//[-------------------------------------------------------]
	//[ Public data types                                     ]
	//[-------------------------------------------------------]
	public:
		typedef typename PLGeneral::uint32 _BaseType;
		typedef typename ENUM::_Type       _Type;


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		static int GetNumOfEnumValues() {
			PLGeneral::String sEnum, sDesc;
			_Type nValue;
			int nIndex = 0;
			for (nIndex=0; ENUM::GetEnumValue(nIndex, nValue, sEnum, sDesc); nIndex++);
			return nIndex;
		}

		static PLGeneral::String GetEnumName(int nIndex) {
			PLGeneral::String sEnum, sDesc;
			_Type nValue;
			ENUM::GetEnumValue(nIndex, nValue, sEnum, sDesc);
			return sEnum;
		}

		static _Type GetEnumValue(const PLGeneral::String &sName) {
			PLGeneral::String sEnum = sName;
			PLGeneral::String sDesc;
			_Type nValue;
			ENUM::GetEnumValue(-1, nValue, sEnum, sDesc);
			return nValue;
		}

		static PLGeneral::String GetEnumDescription(const PLGeneral::String &sName) {
			PLGeneral::String sEnum = sName;
			PLGeneral::String sDesc;
			_Type nValue;
			ENUM::GetEnumValue(-1, nValue, sEnum, sDesc);
			return sDesc;
		}


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_ENUMTYPE_H__
