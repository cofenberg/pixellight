/*********************************************************\
 *  File: DynTypeInfo.h                                  *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLCORE_DYNTYPEINFO_H__
#define __PLCORE_DYNTYPEINFO_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLGeneral/Container/List.h>
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
*    Virtual base class for types
*
*  @remarks
*    This is the virtual base class to access dynamic type information.
*    Usually it is better to use the static type template classes
*    such as Type<int> etc. However, sometimes it is necessary go get the
*    type e.g. of a variable in a dynamic (polymorphic) way.
*/
class DynTypeInfo {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API DynTypeInfo();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~DynTypeInfo();


	//[-------------------------------------------------------]
	//[ Public virtual DynTypeInfo functions                  ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get type ID
		*
		*  @return
		*    Type ID
		*/
		PLCORE_API virtual int GetTypeID() const;

		/**
		*  @brief
		*    Get type name
		*
		*  @return
		*    Type name
		*/
		PLCORE_API virtual PLGeneral::String GetTypeName() const;

		/**
		*  @brief
		*    Check if this is an enum type
		*
		*  @return
		*    'true' if type is enum type, else 'false'
		*/
		PLCORE_API virtual bool IsEnumType() const;

		/**
		*  @brief
		*    Check if this is an flag type
		*
		*  @return
		*    'true' if type is flag type, else 'false'
		*/
		PLCORE_API virtual bool IsFlagType() const;

		/**
		*  @brief
		*    Get enum value names
		*
		*  @return
		*    List of enum value names
		*/
		PLCORE_API virtual const PLGeneral::List<PLGeneral::String> &GetEnumValues() const;

		/**
		*  @brief
		*    Get enum value
		*
		*  @param[in] sEnum
		*    Enum name
		*
		*  @return
		*    Enum value as string
		*/
		PLCORE_API virtual PLGeneral::String GetEnumValue(const PLGeneral::String &sEnum) const;

		/**
		*  @brief
		*    Get enum description
		*
		*  @param[in] sEnum
		*    Enum name
		*
		*  @return
		*    Description for that enum value
		*/
		PLCORE_API virtual PLGeneral::String GetEnumDescription(const PLGeneral::String &sEnum) const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::List<PLGeneral::String> m_lstEnumValues;	/**< List of enum values (empty but for enum-types) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_DYNTYPEINFO_H__
