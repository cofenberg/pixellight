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
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ Protected virtual ClassImpl functions                 ]
//[-------------------------------------------------------]
bool ClassDummy::IsDummy() const
{
	// Bah! It's just a dummy!
	return true;
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
