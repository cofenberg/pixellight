/*********************************************************\
 *  File: ClassDummy.cpp                                 *
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
#include "PLCore/Base/Module.h"
#include "PLCore/Base/ClassManager.h"
#include "PLCore/Base/ClassDummy.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
HashMap<String, MemberDesc*> ClassDummy::m_mapMembers;
List<VarDesc*>				 ClassDummy::m_lstAttributes;
List<FuncDesc*>				 ClassDummy::m_lstMethods;
List<EventDesc*>			 ClassDummy::m_lstSignals;
List<EventHandlerDesc*>		 ClassDummy::m_lstSlots;
List<ConstructorDesc*>		 ClassDummy::m_lstConstructors;


//[-------------------------------------------------------]
//[ Protected virtual ClassImpl functions                 ]
//[-------------------------------------------------------]
bool ClassDummy::IsDummy() const
{
	// Bah! It's just a dummy!
	return true;
}

/**
*  @brief
*    Initialize class and class members
*/
void ClassDummy::InitClass() const
{
	// Check if class has already been initialized
	if (!m_bInitialized) {
		// Get base class
		if (m_sBaseClass.GetLength())
			m_pBaseClass = ClassManager::GetInstance()->GetClass(m_sBaseClass);

		// Check if a valid base class has been found
		if (m_pBaseClass || !m_sBaseClass.GetLength()) {
			// Do we have a base class? (only Object doesn't, but that must count, too)
			if (m_pBaseClass) {
				// Initialize base class
				static_cast<ClassImpl*>(m_pBaseClass->m_pClassImpl)->InitClass();

				// Add properties from base class
				ClassImpl *pBaseClassReal = static_cast<ClassImpl*>(m_pBaseClass->m_pClassImpl);
				Iterator<String> cIterator = pBaseClassReal->m_mapOwnProperties.GetKeyIterator();
				while (cIterator.HasNext()) {
					const String sName  = cIterator.Next();
					const String sValue = pBaseClassReal->m_mapOwnProperties.Get(sName);
					m_mapProperties.Set(sName, sValue);
				}

				// The dummy doesn't support attributes
				// The dummy doesn't support methods
				// The dummy doesn't support signals
				// The dummy doesn't support slots

				// Constructors are not copied from base classes, only the own constructors can be used!
			}

			// Add own properties
			Iterator<String> cIterator = m_mapOwnProperties.GetKeyIterator();
			while (cIterator.HasNext()) {
				const String sName  = cIterator.Next();
				const String sValue = m_mapOwnProperties.Get(sName);
				m_mapProperties.Set(sName, sValue);
			}

			// The dummy doesn't support attributes
			// The dummy doesn't support methods
			// The dummy doesn't support signals
			// The dummy doesn't support slots

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
void ClassDummy::DeInitClass() const
{
	// Clear lists
	m_mapProperties.Clear();
	// The dummy doesn't support members
	// The dummy doesn't support attributes
	// The dummy doesn't support methods
	// The dummy doesn't support signals
	// The dummy doesn't support slots
	// The dummy doesn't support constructors

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

const List<VarDesc*> &ClassDummy::GetAttributes() const
{
	// For this action, we really need the real class: Requests the real class implementation
	ClassImpl *pRealClassImpl = GetRealClassImpl();
	return pRealClassImpl ? pRealClassImpl->GetAttributes() : m_lstAttributes;
}

const VarDesc *ClassDummy::GetAttribute(const String &sName) const
{
	// For this action, we really need the real class: Requests the real class implementation
	ClassImpl *pRealClassImpl = GetRealClassImpl();
	return pRealClassImpl ? pRealClassImpl->GetAttribute(sName) : nullptr;
}

const List<FuncDesc*> &ClassDummy::GetMethods() const
{
	// For this action, we really need the real class: Requests the real class implementation
	ClassImpl *pRealClassImpl = GetRealClassImpl();
	return pRealClassImpl ? pRealClassImpl->GetMethods() : m_lstMethods;
}

const FuncDesc *ClassDummy::GetMethod(const String &sName) const
{
	// For this action, we really need the real class: Requests the real class implementation
	ClassImpl *pRealClassImpl = GetRealClassImpl();
	return pRealClassImpl ? pRealClassImpl->GetMethod(sName) : nullptr;
}

const List<EventDesc*> &ClassDummy::GetSignals() const
{
	// For this action, we really need the real class: Requests the real class implementation
	ClassImpl *pRealClassImpl = GetRealClassImpl();
	return pRealClassImpl ? pRealClassImpl->GetSignals() : m_lstSignals;
}

const EventDesc *ClassDummy::GetSignal(const String &sName) const
{
	// For this action, we really need the real class: Requests the real class implementation
	ClassImpl *pRealClassImpl = GetRealClassImpl();
	return pRealClassImpl ? pRealClassImpl->GetSignal(sName) : nullptr;
}

const List<EventHandlerDesc*> &ClassDummy::GetSlots() const
{
	// For this action, we really need the real class: Requests the real class implementation
	ClassImpl *pRealClassImpl = GetRealClassImpl();
	return pRealClassImpl ? pRealClassImpl->GetSlots() : m_lstSlots;
}

const EventHandlerDesc *ClassDummy::GetSlot(const String &sName) const
{
	// For this action, we really need the real class: Requests the real class implementation
	ClassImpl *pRealClassImpl = GetRealClassImpl();
	return pRealClassImpl ? pRealClassImpl->GetSlot(sName) : nullptr;
}

bool ClassDummy::HasConstructor() const
{
	return m_bHasConstructor;
}

bool ClassDummy::HasDefaultConstructor() const
{
	return m_bHasDefaultConstructor;
}

const List<ConstructorDesc*> &ClassDummy::GetConstructors() const
{
	// For this action, we really need the real class: Requests the real class implementation
	ClassImpl *pRealClassImpl = GetRealClassImpl();
	return pRealClassImpl ? pRealClassImpl->GetConstructors() : m_lstConstructors;
}

const ConstructorDesc *ClassDummy::GetConstructor(const String &sName) const
{
	// For this action, we really need the real class: Requests the real class implementation
	ClassImpl *pRealClassImpl = GetRealClassImpl();
	return pRealClassImpl ? pRealClassImpl->GetConstructor(sName) : nullptr;
}

Object *ClassDummy::Create() const
{
	// For this action, we really need the real class: Requests the real class implementation
	ClassImpl *pRealClassImpl = GetRealClassImpl();
	return pRealClassImpl ? pRealClassImpl->Create() : nullptr;
}

Object *ClassDummy::Create(const DynParams &cParams) const
{
	// For this action, we really need the real class: Requests the real class implementation
	ClassImpl *pRealClassImpl = GetRealClassImpl();
	return pRealClassImpl ? pRealClassImpl->Create(cParams) : nullptr;
}

Object *ClassDummy::Create(const String &sName, const DynParams &cParams) const
{
	// For this action, we really need the real class: Requests the real class implementation
	ClassImpl *pRealClassImpl = GetRealClassImpl();
	return pRealClassImpl ? pRealClassImpl->Create(sName, cParams) : nullptr;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ClassDummy::ClassDummy(uint32 nModuleID, const String &sName, const String &sDescription, const String &sNamespace, const String &sBaseClass, bool bHasConstructor, bool bHasDefaultConstructor) : ClassImpl(nModuleID, sName, sDescription, sNamespace, sBaseClass),
	m_bHasConstructor(bHasConstructor),
	m_bHasDefaultConstructor(bHasDefaultConstructor)
{
}

/**
*  @brief
*    Destructor
*/
ClassDummy::~ClassDummy()
{
	// De-initialize class
	if (m_bInitialized)
		DeInitClass();
}

/*
*  @brief
*    Requests the real class implementation
*/
ClassImpl *ClassDummy::GetRealClassImpl() const
{
	// Get the module instance this dummy implementation is in
	const Module *pModule = GetModule();
	if (pModule) {
		// Backup some pointers on the runtime stack - this class implementation dummy will propably die in the next step...
		const ClassImpl *pThisClassImpl = this;
		Class *pClass = m_pClass;

		// Get the class manager instance
		ClassManager *pClassManager = ClassManager::GetInstance();

		// Load the real module, this also creates the real class implementations
		pClassManager->LoadModule(pModule->GetFilename());

		// Class implementation changed?
		if (pClass->m_pClassImpl != pThisClassImpl) {
			// The dummy class implementation is no more, this means the dummy module has now to go as well

			// Module has been unloaded (emit event)
			pClassManager->EventModuleUnloaded(pModule);

			// Remove module
			pClassManager->m_lstModules.Remove(pModule);
			pClassManager->m_mapModules.Remove(pModule->GetModuleID());
			delete pModule;

			// Return the real class implementation
			return pClass->m_pClassImpl;
		}
	}

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
