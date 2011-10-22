/*********************************************************\
 *  File: VarDesc.cpp                                    *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/PLCoreDefinitions.h"
#include "PLCore/Base/Class.h"
#include "PLCore/Base/Var/VarDesc.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
VarDesc::VarDesc(int nType, const String &sType, const String &sName, const String &sDescription, const String &sAnnotation) :
	MemberDesc(MemberAttribute, sName, sDescription, sAnnotation),
	m_nType(nType),
	m_sType(sType)
{
}

/**
*  @brief
*    Destructor
*/
VarDesc::~VarDesc()
{
}

/**
*  @brief
*    Initialize instance
*/
void VarDesc::Dummy()
{
	// This method is just here to ensure, that the compiler will actually create static instances
}

/**
*  @brief
*    Get type ID
*/
int VarDesc::GetTypeID() const
{
	// Return type ID
	return m_nType;
}

/**
*  @brief
*    Get type name
*/
String VarDesc::GetTypeName() const
{
	// Return type name
	return m_sType;
}


//[-------------------------------------------------------]
//[ Public virtual VarDesc functions                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get attribute
*/
DynVar *VarDesc::GetAttribute(const Object &cObject) const
{
	// To be implemented in derived classes
	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
