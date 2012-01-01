/*********************************************************\
 *  File: Class.inl                                      *
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
#include "PLCore/Base/ClassImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get module the class belongs to
*/
inline const Module *Class::GetModule() const
{
	// Return module from class manager
	return m_pClassImpl->GetModule();
}

/**
*  @brief
*    Get full class name (with namespace)
*/
inline String Class::GetClassName() const
{
	// Return name of class and namespace
	return m_pClassImpl->GetClassName();
}

/**
*  @brief
*    Get full name of base class (with namespace)
*/
inline String Class::GetBaseClassName() const
{
	// Return base class
	return m_pClassImpl->GetBaseClassName();
}

/**
*  @brief
*    Get class name
*/
inline String Class::GetName() const
{
	// Return name of class
	return m_pClassImpl->GetName();
}

/**
*  @brief
*    Get class description
*/
inline String Class::GetDescription() const
{
	// Return description
	return m_pClassImpl->GetDescription();
}

/**
*  @brief
*    Get namespace
*/
inline String Class::GetNamespace() const
{
	// Return namespace
	return m_pClassImpl->GetNamespace();
}

/**
*  @brief
*    Get base class
*/
inline const Class *Class::GetBaseClass() const
{
	// Return base class
	return m_pClassImpl->GetBaseClass();
}

/**
*  @brief
*    Check if class is derived from another class
*/
inline bool Class::IsDerivedFrom(const Class &cBaseClass) const
{
	// Call implementation
	return m_pClassImpl->IsDerivedFrom(cBaseClass);
}

/**
*  @brief
*    Check if class is derived from another class
*/
inline bool Class::IsDerivedFrom(const String &sBaseClass) const
{
	// Call implementation
	return m_pClassImpl->IsDerivedFrom(sBaseClass);
}

/**
*  @brief
*    Get properties
*/
inline const HashMap<String, String> &Class::GetProperties() const
{
	// Return property map
	return m_pClassImpl->GetProperties();
}

/**
*  @brief
*    Get attributes
*/
inline const List<VarDesc*> &Class::GetAttributes() const
{
	// Return attributes
	return m_pClassImpl->GetAttributes();
}

/**
*  @brief
*    Get attribute
*/
inline const VarDesc *Class::GetAttribute(const String &sName) const
{
	// Get attribute
	return m_pClassImpl->GetAttribute(sName);
}

/**
*  @brief
*    Get methods
*/
inline const List<FuncDesc*> &Class::GetMethods() const
{
	// Return methods
	return m_pClassImpl->GetMethods();
}

/**
*  @brief
*    Get method
*/
inline const FuncDesc *Class::GetMethod(const String &sName) const
{
	// Get method
	return m_pClassImpl->GetMethod(sName);
}

/**
*  @brief
*    Get signals
*/
inline const List<EventDesc*> &Class::GetSignals() const
{
	// Return signals
	return m_pClassImpl->GetSignals();
}

/**
*  @brief
*    Get signal
*/
inline const EventDesc *Class::GetSignal(const String &sName) const
{
	// Get signal
	return m_pClassImpl->GetSignal(sName);
}

/**
*  @brief
*    Get slots
*/
inline const List<EventHandlerDesc*> &Class::GetSlots() const
{
	// Return slots
	return m_pClassImpl->GetSlots();
}

/**
*  @brief
*    Get slot
*/
inline const EventHandlerDesc *Class::GetSlot(const String &sName) const
{
	// Get slot
	return m_pClassImpl->GetSlot(sName);
}

/**
*  @brief
*    Check if class has any constructors
*/
inline bool Class::HasConstructor() const
{
	// Check if there is at least one constructor
	return m_pClassImpl->HasConstructor();
}

/**
*  @brief
*    Check if class has a default constructor
*/
inline bool Class::HasDefaultConstructor() const
{
	// Check if class has a default constructor
	return m_pClassImpl->HasDefaultConstructor();
}

/**
*  @brief
*    Get constructors
*/
inline const List<ConstructorDesc*> &Class::GetConstructors() const
{
	// Return constructors
	return m_pClassImpl->GetConstructors();
}

/**
*  @brief
*    Get constructor
*/
inline const ConstructorDesc *Class::GetConstructor(const String &sName) const
{
	// Get constructor
	return m_pClassImpl->GetConstructor(sName);
}

/**
*  @brief
*    Create object by using the default constructor
*/
inline Object *Class::Create() const
{
	// Create object
	return m_pClassImpl->Create();
}

/**
*  @brief
*    Create object by using typed constructor parameters in order to identity the constructor automatically
*/
inline Object *Class::Create(const DynParams &cParams) const
{
	// Create object
	return m_pClassImpl->Create(cParams);
}

/**
*  @brief
*    Create object by using a given constructor name and typed constructor parameters
*/
inline Object *Class::Create(const String &sName, const DynParams &cParams) const
{
	// Create object
	return m_pClassImpl->Create(sName, cParams);
}

/**
*  @brief
*    Create object by using a given constructor name and typeless constructor parameters
*/
inline Object *Class::Create(const String &sName, const String &sParams) const
{
	// Create object
	return m_pClassImpl->Create(sName, sParams);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
