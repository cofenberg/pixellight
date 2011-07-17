/*********************************************************\
 *  File: PLCoreDefinitions.h                            *
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


#ifndef __PLCORE_DEFINITIONS_H__
#define __PLCORE_DEFINITIONS_H__
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
//[ Definitions                                           ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type IDs
*/
enum ETypeID {
	TypeInvalid = -1,
	TypeNull = 0,
	TypeVoid,
	TypeBool,
	TypeInt,
	TypeFloat,
	TypeDouble,
	TypeInt8,
	TypeInt16,
	TypeInt32,
	TypeInt64,
	TypeUInt8,
	TypeUInt16,
	TypeUInt32,
	TypeUInt64,
	TypeString,
	TypePtr,
	TypeRef,
	TypeObjectPtr
};

/**
*  @brief
*    Member types
*/
enum EMemberType {
	MemberAttribute = 0,
	MemberMethod,
	MemberConstructor,
	MemberEvent,
	MemberEventHandler
};

/**
*  @brief
*    Default value mode
*/
enum EDefaultValue {
	WithDefault = 0,		/**< Retrieve all variables, including those with a default value */
	NoDefault				/**< Retrieve only variables that are different than their default value */
};

/**
*  @brief
*    Recursive mode
*/
enum ERecursive {
	NonRecursive = 0,		/**< Do (whatever) not recursively */
	Recursive				/**< Do (whatever) recursively */
};

/**
*  @brief
*    Include base class in class searches
*/
enum EIncludeBase {
	IncludeBase = 0,		/**< Include that base class itself in the list of derived classes */
	NoBase					/**< Only include derived classes, not the base class itself */
};

/**
*  @brief
*    Include abstract classes in class searches
*/
enum EIncludeAbstract {
	IncludeAbstract = 0,	/**< Include abstract classes in list of classes */
	NoAbstract				/**< Do not include abstract classes */
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_DEFINITIONS_H__
