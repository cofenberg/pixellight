/*********************************************************\
 *  File: Class.cpp                                      *
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
#include "PLCore/Base/Var/VarDesc.h"
#include "PLCore/Base/Func/DynFunc.h"
#include "PLCore/Base/Func/ConstructorDesc.h"
#include "PLCore/Base/Func/Params.h"
#include "PLCore/Base/Func/FuncDesc.h"
#include "PLCore/Base/Event/EventDesc.h"
#include "PLCore/Base/Event/EventHandlerDesc.h"
#include "PLCore/Base/MemberDesc.h"
#include "PLCore/Base/ClassManager.h"
#include "PLCore/Base/Class.h"
#include "PLCore/Base/Rtti.h"


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
Class::Class(uint32 nModuleID, const String &sName, const String &sDescription, const String &sNamespace, const String &sBaseClass) :
	m_nModuleID(nModuleID),
	m_bInitialized(false),
	m_pBaseClass(nullptr),
	m_sName(sName),
	m_sNamespace(sNamespace),
	m_sDescription(sDescription),
	m_sBaseClass(sBaseClass)
{
	// Compose namespace and name
	if (m_sNamespace != "")
		m_sClassName = m_sNamespace + "::" + m_sName;
	else
		m_sClassName = m_sName;

	// Register at class manager
	ClassManager::GetInstance()->RegisterClass(m_nModuleID, this);
}

/**
*  @brief
*    Destructor
*/
Class::~Class()
{
	// Unregister at class manager
	ClassManager::GetInstance()->UnregisterClass(m_nModuleID, this);
}

/**
*  @brief
*    Get module the class belongs to
*/
const Module *Class::GetModule() const
{
	// Return module from class manager
	return ClassManager::GetInstance()->GetModule(m_nModuleID);
}

/**
*  @brief
*    Get full class name (with namespace)
*/
String Class::GetClassName() const
{
	// Return name of class and namespace
	return m_sClassName;
}

/**
*  @brief
*    Get full name of base class (with namespace)
*/
String Class::GetBaseClassName() const
{
	// Return base class
	return m_sBaseClass;
}

/**
*  @brief
*    Get class name
*/
String Class::GetName() const
{
	// Return name of class
	return m_sName;
}

/**
*  @brief
*    Get class description
*/
String Class::GetDescription() const
{
	// Return description
	return m_sDescription;
}

/**
*  @brief
*    Get namespace
*/
String Class::GetNamespace() const
{
	// Return namespace
	return m_sNamespace;
}

/**
*  @brief
*    Get base class
*/
const Class *Class::GetBaseClass() const
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
bool Class::IsDerivedFrom(const Class &cBaseClass) const
{
	// Get base class by name
	return IsDerivedFrom(cBaseClass.GetClassName());
}

/**
*  @brief
*    Check if class is derived from another class
*/
bool Class::IsDerivedFrom(const String &sBaseClass) const
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
*    Get derived classes
*/
const List<const Class*> Class::GetDerivedClasses() const
{
	// Get list of derived classes
	List<const Class*> lstClasses;
	ClassManager::GetInstance()->GetClasses(lstClasses, GetClassName(), NonRecursive, NoBase, IncludeAbstract);
	return lstClasses;
}

/**
*  @brief
*    Get properties
*/
const HashMap<String, String> &Class::GetProperties() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Return property map
	return m_mapProperties;
}

/**
*  @brief
*    Get attributes
*/
const List<VarDesc*> &Class::GetAttributes() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Return attributes
	return m_lstAttributes;
}

/**
*  @brief
*    Get attribute
*/
const VarDesc *Class::GetAttribute(const String &sName) const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Get attribute
	MemberDesc *pMember = m_mapMembers.Get(sName);
	if (pMember && pMember->GetMemberType() == MemberAttribute)
		return static_cast<VarDesc*>(pMember);

	// Attribute could not be found
	return nullptr;
}

/**
*  @brief
*    Get methods
*/
const List<FuncDesc*> &Class::GetMethods() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Return methods
	return m_lstMethods;
}

/**
*  @brief
*    Get method
*/
const FuncDesc *Class::GetMethod(const String &sName) const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Get method
	MemberDesc *pMember = m_mapMembers.Get(sName);
	if (pMember && pMember->GetMemberType() == MemberMethod)
		return static_cast<FuncDesc*>(pMember);

	// Method could not be found
	return nullptr;
}

/**
*  @brief
*    Get signals
*/
const List<EventDesc*> &Class::GetSignals() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Return signals
	return m_lstSignals;
}

/**
*  @brief
*    Get signal
*/
const EventDesc *Class::GetSignal(const String &sName) const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Get signal
	MemberDesc *pMember = m_mapMembers.Get(sName);
	if (pMember && pMember->GetMemberType() == MemberEvent)
		return static_cast<EventDesc*>(pMember);

	// Signal could not be found
	return nullptr;
}

/**
*  @brief
*    Get slots
*/
const List<EventHandlerDesc*> &Class::GetSlots() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Return slots
	return m_lstSlots;
}

/**
*  @brief
*    Get slot
*/
const EventHandlerDesc *Class::GetSlot(const String &sName) const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Get slot
	MemberDesc *pMember = m_mapMembers.Get(sName);
	if (pMember && pMember->GetMemberType() == MemberEventHandler)
		return static_cast<EventHandlerDesc*>(pMember);

	// Slot could not be found
	return nullptr;
}

/**
*  @brief
*    Check if class has any constructors
*/
bool Class::HasConstructor() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Check if there is at least one constructor
	return (m_lstConstructors.GetNumOfElements() > 0);
}

/**
*  @brief
*    Check if class has a default constructors
*/
bool Class::HasDefaultConstructor() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Loop through list
	Iterator<ConstructorDesc*> cIterator = m_lstConstructors.GetIterator();
	while (cIterator.HasNext()) {
		// Get constructor
		ConstructorDesc *pConstructor = cIterator.Next();

		// Default constructor?
		if (pConstructor->IsDefaultConstructor()) {
			// We found a default constructor
			return true;
		}
	}

	// No default constructor found
	return false;
}

/**
*  @brief
*    Get constructors
*/
const List<ConstructorDesc*> &Class::GetConstructors() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Return constructors
	return m_lstConstructors;
}

/**
*  @brief
*    Get constructor
*/
const ConstructorDesc *Class::GetConstructor(const String &sName) const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Get constructor
	MemberDesc *pMember = m_mapMembers.Get(sName);
	if (pMember && pMember->GetMemberType() == MemberConstructor)
		return static_cast<ConstructorDesc*>(pMember);

	// Constructor could not be found
	return nullptr;
}

/**
*  @brief
*    Create object
*/
Object *Class::Create() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Loop through constructors
	for (uint32 i=0; i<m_lstConstructors.GetNumOfElements(); i++) {
		// Get constructor
		ConstructorDesc *pConstructor = m_lstConstructors[i];

		// Check if this constructor is a default constructor
		if (pConstructor->GetSignature() == "Object*()") {
			// Call constructor
			Params<Object*> cParams;
			return pConstructor->Create(cParams);
		}
	}

	// Error, no value constructor found
	return nullptr;
}

/**
*  @brief
*    Create object
*/
Object *Class::Create(const DynParams &cParams) const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Loop through constructors
	for (uint32 i=0; i<m_lstConstructors.GetNumOfElements(); i++) {
		// Get constructor
		ConstructorDesc *pConstructor = m_lstConstructors[i];

		// Check if this constructor is a default constructor
		if (pConstructor->GetSignature() == cParams.GetSignature()) {
			// Call constructor
			return pConstructor->Create(cParams);
		}
	}

	// Error, no value constructor found
	return nullptr;
}

/**
*  @brief
*    Create object
*/
Object *Class::Create(const String &sName, const DynParams &cParams) const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Loop through constructors
	for (uint32 i=0; i<m_lstConstructors.GetNumOfElements(); i++) {
		// Get constructor
		ConstructorDesc *pConstructor = m_lstConstructors[i];

		// Check if this constructor is a default constructor
		if (pConstructor->GetName() == sName && pConstructor->GetSignature() == cParams.GetSignature()) {
			// Call constructor
			return pConstructor->Create(cParams);
		}
	}

	// Error, no value constructor found
	return nullptr;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Add member
*/
void Class::AddMember(MemberDesc *pMemberDesc)
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
void Class::AddProperty(const String &sName, const String &sValue)
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

/**
*  @brief
*    Initialize class and class members
*/
void Class::InitClass() const
{
	// Check if class has already been initialized
	if (!m_bInitialized) {
		// Get base class
		m_pBaseClass = ClassManager::GetInstance()->GetClass(m_sBaseClass);

		// Check if a valid base class has been found
		if (m_pBaseClass || m_sBaseClass == "") {
			// Do we have a base class? (only Object doesn't, but that must count, too)
			if (m_pBaseClass) {
				// Initialize base class
				m_pBaseClass->InitClass();

				// Add properties from base class
				Iterator<PLGeneral::String> cIterator = m_pBaseClass->m_mapOwnProperties.GetKeyIterator();
				while (cIterator.HasNext()) {
					const String sName  = cIterator.Next();
					const String sValue = m_pBaseClass->m_mapOwnProperties.Get(sName);
					m_mapProperties.Set(sName, sValue);
				}

				// Add attributes from base class
				m_lstAttributes = m_pBaseClass->m_lstAttributes;
				for (uint32 i=0; i<m_lstAttributes.GetNumOfElements(); i++) {
					VarDesc *pAttr = m_lstAttributes[i];
					m_mapMembers.Add(pAttr->GetName(), pAttr);
				}

				// Add methods from base class
				m_lstMethods = m_pBaseClass->m_lstMethods;
				for (uint32 i=0; i<m_lstMethods.GetNumOfElements(); i++) {
					FuncDesc *pMethod = m_lstMethods[i];
					m_mapMembers.Add(pMethod->GetName(), pMethod);
				}

				// Add signals from base class
				m_lstSignals = m_pBaseClass->m_lstSignals;
				for (uint32 i=0; i<m_lstSignals.GetNumOfElements(); i++) {
					EventDesc *pSignal = m_lstSignals[i];
					m_mapMembers.Add(pSignal->GetName(), pSignal);
				}

				// Add slots from base class
				m_lstSlots = m_pBaseClass->m_lstSlots;
				for (uint32 i=0; i<m_lstSlots.GetNumOfElements(); i++) {
					EventHandlerDesc *pSlot = m_lstSlots[i];
					m_mapMembers.Add(pSlot->GetName(), pSlot);
				}

				// Constructors are not copied from base classes, only the own constructors can be used!
			}

			// Add own properties
			Iterator<PLGeneral::String> cIterator = m_mapOwnProperties.GetKeyIterator();
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
void Class::DeInitClass() const
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
	List<const Class*> lstClasses = GetDerivedClasses();
	for (uint32 i=0; i<lstClasses.GetNumOfElements(); i++)
		lstClasses[i]->DeInitClass();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
