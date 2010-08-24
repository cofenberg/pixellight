/*********************************************************\
 *  File: MemberDesc.cpp                                 *
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
#include <PLGeneral/PLGeneral.h>
#include "PLCore/Base/Class.h"
#include "PLCore/Base/MemberDesc.h"


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
MemberDesc::MemberDesc(EMemberType nMemberType, const String &sName, const String &sDescription, const String &sAnnotation) :
	m_nMemberType(nMemberType),
	m_sName(sName),
	m_sDescription(sDescription),
	m_sAnnotation(sAnnotation)
{
}

/**
*  @brief
*    Destructor
*/
MemberDesc::~MemberDesc()
{
}

/**
*  @brief
*    Get type
*/
EMemberType MemberDesc::GetMemberType() const
{
	// Return type
	return m_nMemberType;
}

/**
*  @brief
*    Get name
*/
String MemberDesc::GetName() const
{
	// Return name of var
	return m_sName;
}

/**
*  @brief
*    Get description
*/
String MemberDesc::GetDescription() const
{
	// Return description of var
	return m_sDescription;
}

/**
*  @brief
*    Get annotation
*/
String MemberDesc::GetAnnotation() const
{
	// Return annotation of var
	return m_sAnnotation;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Register member at class
*/
void MemberDesc::Register(Class *pClass)
{
	// Check parameters
	if (pClass) {
		// Add attribute
		pClass->AddMember(this);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
