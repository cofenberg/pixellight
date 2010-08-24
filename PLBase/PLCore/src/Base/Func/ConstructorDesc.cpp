/*********************************************************\
 *  File: ConstructorDesc.cpp                            *
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
#include "PLCore/Base/Func/ConstructorDesc.h"


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
ConstructorDesc::ConstructorDesc(const String &sSignature, const String &sName, const String &sDescription, const String &sAnnotation) :
	MemberDesc(MemberConstructor, sName, sDescription, sAnnotation),
	m_sSignature(sSignature)
{
}

/**
*  @brief
*    Destructor
*/
ConstructorDesc::~ConstructorDesc()
{
}

/**
*  @brief
*    Initialize instance
*/
void ConstructorDesc::Dummy()
{
}

/**
*  @brief
*    Get signature
*/
String ConstructorDesc::GetSignature() const
{
	// Return signature
	return m_sSignature;
}

/**
*  @brief
*    Check if this is a default constructor
*/
bool ConstructorDesc::IsDefaultConstructor() const
{
	// Check if signature is Object*()
	return (m_sSignature == "Object*()");
}


//[-------------------------------------------------------]
//[ Public virtual ConstructorDesc functions              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get constructor
*/
DynFunc *ConstructorDesc::GetConstructor() const
{
	// To be implemented in derived classes
	return NULL;
}

/**
*  @brief
*    Create object
*/
Object *ConstructorDesc::Create(const DynParams &cParams)
{
	// To be implemented in derived classes
	return NULL;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
