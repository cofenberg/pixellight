/*********************************************************\
 *  File: ClassReal.cpp                                  *
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
#include "PLCore/Base/ClassManager.h"
#include "PLCore/Base/ClassReal.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ClassReal::ClassReal(uint32 nModuleID, const String &sName, const String &sDescription, const String &sNamespace, const String &sBaseClass) : ClassImpl(nModuleID, sName, sDescription, sNamespace, sBaseClass)
{
	// Register at class manager
	ClassManager::GetInstance()->RegisterClass(nModuleID, this);
}

/**
*  @brief
*    Destructor
*/
ClassReal::~ClassReal()
{
	// Unregister at class manager
	ClassManager::GetInstance()->UnregisterClass(m_nModuleID, this);
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Add member
*/
void ClassReal::AddMember(MemberDesc *pMemberDesc)
{
	// De-initialize class
	if (m_bInitialized)
		DeInitClass();

	// Check if pointer is valid
	if (pMemberDesc) {
		// Add member to list
		m_lstOwnMembers.Add(pMemberDesc);
	}
}

/**
*  @brief
*    Add property
*/
void ClassReal::AddProperty(const String &sName, const String &sValue)
{
	// De-initialize class
	if (m_bInitialized)
		DeInitClass();

	// Check if name is valid
	if (sName != "") {
		// Add property
		m_mapOwnProperties.Add(sName, sValue);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
