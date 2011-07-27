/*********************************************************\
 *  File: TypeInfo.h                                     *
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


#ifndef __PLCORE_TYPEINFO_H__
#define __PLCORE_TYPEINFO_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/TypeInfo/DynTypeInfo.h"
#include "PLCore/Base/Type/EnumType.h"
#include "PLCore/Base/Type/DefaultValue.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <typename T>
class Type;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Dynamic type wrapper
*/
template <typename T>
class TypeInfo : public DynTypeInfo {


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		static TypeInfo Instance;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		TypeInfo()
		{
		}

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~TypeInfo()
		{
		}


	//[-------------------------------------------------------]
	//[ Public virtual DynTypeInfo functions                  ]
	//[-------------------------------------------------------]
	public:
		virtual int GetTypeID() const override
		{
			return Type<T>::TypeID;
		}

		virtual String GetTypeName() const override
		{
			return Type<T>::GetTypeName();
		}

		virtual bool IsEnumType() const override
		{
			return false;
		}

		virtual bool IsFlagType() const override
		{
			return false;
		}

		virtual String GetEnumValue(const String &sEnum) const override
		{
			return "";
		}


};


//[-------------------------------------------------------]
//[ Static variables                                      ]
//[-------------------------------------------------------]
template <typename T> TypeInfo<T> TypeInfo<T>::Instance;


//[-------------------------------------------------------]
//[ Include type info implementations                     ]
//[-------------------------------------------------------]
#include "TypeInfoEnum.inl"
#include "TypeInfoFlag.inl"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_TYPEINFO_H__
