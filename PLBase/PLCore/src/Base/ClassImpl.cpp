/*********************************************************\
 *  File: ClassImpl.cpp                                  *
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
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Return the pointer to the owner class instance wrapping this class implementation
*/
Class *ClassImpl::GetClass() const
{
	return m_pClass;
}


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
	m_sClassName((m_sNamespace != "") ? m_sNamespace + "::" + m_sName : m_sName),
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
	// De-initialize class
	if (m_bInitialized)
		DeInitClass();
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
*    Get full class name (with namespace)
*/
String ClassImpl::GetClassName() const
{
	// Return name of class and namespace
	return m_sClassName;
}

/**
*  @brief
*    Get full name of base class (with namespace)
*/
String ClassImpl::GetBaseClassName() const
{
	// Return base class
	return m_sBaseClass;
}

/**
*  @brief
*    Get class name (without namespace)
*/
String ClassImpl::GetName() const
{
	// Return name of class
	return m_sName;
}

/**
*  @brief
*    Get class description
*/
String ClassImpl::GetDescription() const
{
	// Return description
	return m_sDescription;
}

/**
*  @brief
*    Get namespace
*/
String ClassImpl::GetNamespace() const
{
	// Return namespace
	return m_sNamespace;
}

/**
*  @brief
*    Get base class
*/
const Class *ClassImpl::GetBaseClass() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

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
*    Get properties
*/
const HashMap<String, String> &ClassImpl::GetProperties() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Return property map
	return m_mapProperties;
}

/**
*  @brief
*    Initialize class and class members
*/
void ClassImpl::InitClass() const
{
	// Check if class has already been initialized
	if (!m_bInitialized) {
		// Get base class
		m_pBaseClass = ClassManager::GetInstance()->GetClass(m_sBaseClass);

		// Check if a valid base class has been found
		if (m_pBaseClass || m_sBaseClass == "") {
			// Do we have a base class? (only Object doesn't, but that must count, too)
			if (m_pBaseClass) {
				// Get the real base class implementation
				ClassImpl *pBaseClassReal = static_cast<ClassImpl*>(m_pBaseClass->m_pClassImpl);

				// Initialize base class
				pBaseClassReal->InitClass();

				// Add properties from base class
				Iterator<String> cIterator = pBaseClassReal->m_mapOwnProperties.GetKeyIterator();
				while (cIterator.HasNext()) {
					const String sName  = cIterator.Next();
					const String sValue = pBaseClassReal->m_mapOwnProperties.Get(sName);
					m_mapProperties.Set(sName, sValue);
				}

				// Add attributes from base class
				m_lstAttributes = pBaseClassReal->m_lstAttributes;
				for (uint32 i=0; i<m_lstAttributes.GetNumOfElements(); i++) {
					VarDesc *pAttr = m_lstAttributes[i];
					m_mapMembers.Add(pAttr->GetName(), pAttr);
				}

				// Add methods from base class
				m_lstMethods = pBaseClassReal->m_lstMethods;
				for (uint32 i=0; i<m_lstMethods.GetNumOfElements(); i++) {
					FuncDesc *pMethod = m_lstMethods[i];
					m_mapMembers.Add(pMethod->GetName(), pMethod);
				}

				// Add signals from base class
				m_lstSignals = pBaseClassReal->m_lstSignals;
				for (uint32 i=0; i<m_lstSignals.GetNumOfElements(); i++) {
					EventDesc *pSignal = m_lstSignals[i];
					m_mapMembers.Add(pSignal->GetName(), pSignal);
				}

				// Add slots from base class
				m_lstSlots = pBaseClassReal->m_lstSlots;
				for (uint32 i=0; i<m_lstSlots.GetNumOfElements(); i++) {
					EventHandlerDesc *pSlot = m_lstSlots[i];
					m_mapMembers.Add(pSlot->GetName(), pSlot);
				}

				// Constructors are not copied from base classes, only the own constructors can be used!
			}

			// Add own properties
			Iterator<String> cIterator = m_mapOwnProperties.GetKeyIterator();
			while (cIterator.HasNext()) {
				const String sName  = cIterator.Next();
				const String sValue = m_mapOwnProperties.Get(sName);
				m_mapProperties.Set(sName, sValue);
			}

			// Add own members
			for (uint32 i=0; i<m_lstOwnMembers.GetNumOfElements(); i++) {
				// Get member
				MemberDesc *pMember = m_lstOwnMembers[i];

				// Add to hash map and overwrite variables from base classes that are already there (having the same name!)
				MemberDesc *pOverwriteMember = m_mapMembers.Get(pMember->GetName());
				if (pOverwriteMember) {
					// Overwrite base class member
					m_mapMembers.Set(pMember->GetName(), pMember);
				} else {
					// Add new member
					m_mapMembers.Add(pMember->GetName(), pMember);
				}

				// Check type and add to respective list
				if (pMember->GetMemberType() == MemberAttribute) {
					// Attribute
					if (pOverwriteMember)
						m_lstAttributes.Remove(static_cast<VarDesc*>(pOverwriteMember));
					m_lstAttributes.Add(static_cast<VarDesc*>(pMember));
				} else if (pMember->GetMemberType() == MemberMethod) {
					// Method
					if (pOverwriteMember)
						m_lstMethods.Remove(static_cast<FuncDesc*>(pOverwriteMember));
					m_lstMethods.Add(static_cast<FuncDesc*>(pMember));
				} else if (pMember->GetMemberType() == MemberEvent) {
					// Event
					if (pOverwriteMember)
						m_lstSignals.Remove(static_cast<EventDesc*>(pOverwriteMember));
					m_lstSignals.Add(static_cast<EventDesc*>(pMember));
				} else if (pMember->GetMemberType() == MemberEventHandler) {
					// Event handler
					if (pOverwriteMember)
						m_lstSlots.Remove(static_cast<EventHandlerDesc*>(pOverwriteMember));
					m_lstSlots.Add(static_cast<EventHandlerDesc*>(pMember));
				} else if (pMember->GetMemberType() == MemberConstructor) {
					// Constructor
					m_lstConstructors.Add(static_cast<ConstructorDesc*>(pMember));
				}
			}

			// Done
			m_bInitialized = true;
		} else {
			// Error! Could not find base class
		}
	}
}

/**
*  @brief
*    De-Initialize class and class members
*/
void ClassImpl::DeInitClass() const
{
	// Clear lists
	m_mapProperties.Clear();
	m_mapMembers.Clear();
	m_lstAttributes.Clear();
	m_lstMethods.Clear();
	m_lstSignals.Clear();
	m_lstSlots.Clear();
	m_lstConstructors.Clear();

	// Remove base class
	m_pBaseClass = nullptr;

	// Class de-initialized
	m_bInitialized = false;

	// De-initialize derived classes
	List<const Class*> lstClasses;
	ClassManager::GetInstance()->GetClasses(lstClasses, m_sClassName, NonRecursive, NoBase, IncludeAbstract);
	for (uint32 i=0; i<lstClasses.GetNumOfElements(); i++)
		lstClasses[i]->m_pClassImpl->DeInitClass();
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
	if (sName != "") {
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
