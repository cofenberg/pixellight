/*********************************************************\
 *  File: ClassImpl.cpp                                  *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLCore/Base/Class.h"
#include "PLCore/Base/ClassManager.h"
#include "PLCore/Base/Var/VarDesc.h"
#include "PLCore/Base/Func/FuncDesc.h"
#include "PLCore/Base/Func/ConstructorDesc.h"
#include "PLCore/Base/Event/EventDesc.h"
#include "PLCore/Base/Event/EventHandlerDesc.h"
#include "PLCore/Base/ClassImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ClassImpl::ClassImpl(uint32 nModuleID, const String &sName, const String &sDescription, const String &sNamespace, const String &sBaseClass) :
	m_pClass(nullptr),
	m_sName(sName),
	m_sNamespace(sNamespace),
	m_sClassName(m_sNamespace.GetLength() ? m_sNamespace + "::" + m_sName : m_sName),
	m_sDescription(sDescription),
	m_sBaseClass(sBaseClass),
	m_nModuleID(nModuleID),
	m_bInitialized(false),
	m_pBaseClass(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
ClassImpl::~ClassImpl()
{
}

/**
*  @brief
*    Get module the class belongs to
*/
const Module *ClassImpl::GetModule() const
{
	// Return module from class manager
	return ClassManager::GetInstance()->GetModule(m_nModuleID);
}

/**
*  @brief
*    Get base class
*/
const Class *ClassImpl::GetBaseClass() const
{
	// Get base class?
	if (!m_pBaseClass && m_sBaseClass.GetLength())
		m_pBaseClass = ClassManager::GetInstance()->GetClass(m_sBaseClass);

	// Return base class
	return m_pBaseClass;
}

/**
*  @brief
*    Check if class is derived from another class
*/
bool ClassImpl::IsDerivedFrom(const Class &cBaseClass) const
{
	// Get base class by name
	return IsDerivedFrom(cBaseClass.GetClassName());
}

/**
*  @brief
*    Check if class is derived from another class
*/
bool ClassImpl::IsDerivedFrom(const String &sBaseClass) const
{
	// Start with own class name
	String sName = GetBaseClassName();
	while (sName.GetLength()) {
		// Base class found?
		if (sName == sBaseClass)
			return true;

		// Next base class
		const Class *pClass = ClassManager::GetInstance()->GetClass(sName);
		sName = pClass ? pClass->GetBaseClassName() : "";
	}

	// Not a base class
	return false;
}

/**
*  @brief
*    Add property
*/
void ClassImpl::AddProperty(const String &sName, const String &sValue)
{
	// De-initialize class
	if (m_bInitialized)
		DeInitClass();

	// Check if name is valid
	if (sName.GetLength()) {
		// Add property
		m_mapOwnProperties.Add(sName, sValue);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
ClassImpl::ClassImpl(const ClassImpl &cSource) :
	m_pClass(nullptr),
	m_nModuleID(0),
	m_bInitialized(false),
	m_pBaseClass(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
ClassImpl &ClassImpl::operator =(const ClassImpl &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
