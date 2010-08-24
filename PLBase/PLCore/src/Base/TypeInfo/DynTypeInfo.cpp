/*********************************************************\
 *  File: DynTypeInfo.cpp                                *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/TypeInfo/DynTypeInfo.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DynTypeInfo::DynTypeInfo()
{
}

/**
*  @brief
*    Destructor
*/
DynTypeInfo::~DynTypeInfo()
{
}


//[-------------------------------------------------------]
//[ Public virtual DynTypeInfo functions                  ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get type ID
*/
int DynTypeInfo::GetTypeID() const
{
	// Unknown
	return -1;
}

/**
*  @brief
*    Get type name
*/
String DynTypeInfo::GetTypeName() const
{
	// Unknown
	return "";
}

/**
*  @brief
*    Check if this is an enum type
*/
bool DynTypeInfo::IsEnumType() const
{
	// No enum type
	return false;
}

/**
*  @brief
*    Check if this is a flag type
*/
bool DynTypeInfo::IsFlagType() const
{
	// No flag type
	return false;
}

/**
*  @brief
*    Get enum value names
*/
const List<String> &DynTypeInfo::GetEnumValues() const
{
	// Return list
	return m_lstEnumValues;
}

/**
*  @brief
*    Get enum value
*/
String DynTypeInfo::GetEnumValue(const String &sEnum) const
{
	// No enum type
	return "";
}

/**
*  @brief
*    Get enum description
*/
String DynTypeInfo::GetEnumDescription(const String &sEnum) const
{
	// No enum type
	return "";
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
