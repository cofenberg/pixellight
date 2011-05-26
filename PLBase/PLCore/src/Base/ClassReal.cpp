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
#include "PLCore/Base/Var/VarDesc.h"
#include "PLCore/Base/Func/FuncDesc.h"
#include "PLCore/Base/Func/ConstructorDesc.h"
#include "PLCore/Base/Event/EventDesc.h"
#include "PLCore/Base/Event/EventHandlerDesc.h"
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
//[ Protected virtual ClassImpl functions                 ]
//[-------------------------------------------------------]
bool ClassReal::IsDummy() const
{
	// This is the real thingy!
	return false;
}

const List<VarDesc*> &ClassReal::GetAttributes() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Return attributes
	return m_lstAttributes;
}

const VarDesc *ClassReal::GetAttribute(const String &sName) const
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

const List<FuncDesc*> &ClassReal::GetMethods() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Return methods
	return m_lstMethods;
}

const FuncDesc *ClassReal::GetMethod(const String &sName) const
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

const List<EventDesc*> &ClassReal::GetSignals() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Return signals
	return m_lstSignals;
}

const EventDesc *ClassReal::GetSignal(const String &sName) const
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

const List<EventHandlerDesc*> &ClassReal::GetSlots() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Return slots
	return m_lstSlots;
}

const EventHandlerDesc *ClassReal::GetSlot(const String &sName) const
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

bool ClassReal::HasConstructor() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Check if there is at least one constructor
	return (m_lstConstructors.GetNumOfElements() > 0);
}

bool ClassReal::HasDefaultConstructor() const
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

const List<ConstructorDesc*> &ClassReal::GetConstructors() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Return constructors
	return m_lstConstructors;
}

const ConstructorDesc *ClassReal::GetConstructor(const String &sName) const
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

Object *ClassReal::Create() const
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

Object *ClassReal::Create(const DynParams &cParams) const
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

Object *ClassReal::Create(const String &sName, const DynParams &cParams) const
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
