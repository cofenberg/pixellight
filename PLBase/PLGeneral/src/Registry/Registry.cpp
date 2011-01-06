/*********************************************************\
 *  File: Registry.cpp                                   *
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
#include "PLGeneral/Registry/RegistryImpl.h"
#if defined(WIN32)
	#include "PLGeneral/Registry/RegistryWindows.h"
#endif
#include "PLGeneral/Registry/Registry.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Registry::Registry() :
	m_pRegistryImpl(nullptr)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pRegistryImpl = new RegistryWindows();
	#endif
}

/**
*  @brief
*    Constructor
*/
Registry::Registry(EKey nKey, const String &sSubKey, uint32 nAccess) :
	m_pRegistryImpl(nullptr)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pRegistryImpl = new RegistryWindows();
	#endif

	// Open registry key
	if (m_pRegistryImpl)
		m_pRegistryImpl->Open(nKey, sSubKey, nAccess);
}

/**
*  @brief
*    Copy constructor
*/
Registry::Registry(const Registry &cRegistry) :
	m_pRegistryImpl(nullptr)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pRegistryImpl = new RegistryWindows();
	#endif

	// Open the same key again
	if (m_pRegistryImpl)
		Open(cRegistry.GetOpenKey(), cRegistry.GetOpenSubKey(), cRegistry.GetOpenAccessMode());
}

/**
*  @brief
*    Destructor
*/
Registry::~Registry()
{
	// Delete system implementation
	if (m_pRegistryImpl)
		delete m_pRegistryImpl;
}

/**
*  @brief
*    Get type of registry
*/
Registry::ERegistry Registry::GetRegistryType() const
{
	return m_pRegistryImpl ? m_pRegistryImpl->GetRegistryType() : None;
}

/**
*  @brief
*    Open registry key
*/
bool Registry::Open(EKey nKey, const String &sSubKey, uint32 nAccess)
{
	return m_pRegistryImpl ? m_pRegistryImpl->Open(nKey, sSubKey, nAccess) : false;
}

/**
*  @brief
*    Create a new registry key
*/
bool Registry::Create(EKey nKey, const String &sSubKey, uint32 nAccess)
{
	return m_pRegistryImpl ? m_pRegistryImpl->Create(nKey, sSubKey, nAccess) : false;
}

/**
*  @brief
*    Delete the registry key
*/
bool Registry::Delete()
{
	return m_pRegistryImpl ? m_pRegistryImpl->Delete() : false;
}

/**
*  @brief
*    Close registry key
*/
void Registry::Close()
{
	if (m_pRegistryImpl)
		return m_pRegistryImpl->Close();
}

/**
*  @brief
*    Get ID of opened registry key
*/
Registry::EKey Registry::GetOpenKey() const
{
	return m_pRegistryImpl ? m_pRegistryImpl->GetOpenKey() : KeyNone;
}

/**
*  @brief
*    Get name of opened sub-key
*/
String Registry::GetOpenSubKey() const
{
	return m_pRegistryImpl ? m_pRegistryImpl->GetOpenSubKey() : "";
}

/**
*  @brief
*    Get access modes
*/
uint32 Registry::GetOpenAccessMode() const
{
	return m_pRegistryImpl ? m_pRegistryImpl->GetOpenAccessMode() : 0;
}

/**
*  @brief
*    Returns the number of sub-keys
*/
uint32 Registry::GetNumOfSubKeys() const
{
	return m_pRegistryImpl ? m_pRegistryImpl->GetNumOfSubKeys() : 0;
}

/**
*  @brief
*    Get a sub-key of the opened registry key
*/
String Registry::GetSubKey(uint32 nIndex) const
{
	return m_pRegistryImpl ? m_pRegistryImpl->GetSubKey(nIndex) : "";
}

/**
*  @brief
*    Returns the number of values
*/
uint32 Registry::GetNumOfValues() const
{
	return m_pRegistryImpl ? m_pRegistryImpl->GetNumOfValues() : 0;
}

/**
*  @brief
*    Get a value of the opened registry key
*/
String Registry::GetValue(uint32 nIndex) const
{
	return m_pRegistryImpl ? m_pRegistryImpl->GetValue(nIndex) : "";
}

/**
*  @brief
*    Get the type of a given value
*/
Registry::EType Registry::GetValueType(const String &sName) const
{
	return m_pRegistryImpl ? m_pRegistryImpl->GetValueType(sName) : TypeNone;
}

/**
*  @brief
*    Get a value of type string
*/
String Registry::GetValueString(const String &sName) const
{
	return m_pRegistryImpl ? m_pRegistryImpl->GetValueString(sName) : "";
}

/**
*  @brief
*    Get a value of type dword
*/
uint32 Registry::GetValueDWord(const String &sName) const
{
	return m_pRegistryImpl ? m_pRegistryImpl->GetValueDWord(sName) : 0;
}

/**
*  @brief
*    Get a value of type binary
*/
uint32 Registry::GetValueBinary(const String &sName, uint8 *pBuffer, uint32 nSize) const
{
	return m_pRegistryImpl ? m_pRegistryImpl->GetValueBinary(sName, pBuffer, nSize) : 0;
}

/**
*  @brief
*    Set a value of type string
*/
bool Registry::SetValueString(const String &sName, const String &sValue)
{
	return m_pRegistryImpl ? m_pRegistryImpl->SetValueString(sName, sValue) : false;
}

/**
*  @brief
*    Set a value of type dword
*/
bool Registry::SetValueDWord(const String &sName, uint32 nValue)
{
	return m_pRegistryImpl ? m_pRegistryImpl->SetValueDWord(sName, nValue) : false;
}

/**
*  @brief
*    Set a value of type binary
*/
bool Registry::SetValueBinary(const String &sName, const uint8 *pBuffer, uint32 nSize)
{
	return m_pRegistryImpl ? m_pRegistryImpl->SetValueBinary(sName, pBuffer, nSize) : false;
}

/**
*  @brief
*    Write all values to the registry
*/
void Registry::Flush()
{
	if (m_pRegistryImpl)
		return m_pRegistryImpl->Flush();
}

/**
*  @brief
*    Copy operator
*/
Registry &Registry::operator =(const Registry &cRegistry)
{
	// Open the same key again
	Open(cRegistry.GetOpenKey(), cRegistry.GetOpenSubKey(), cRegistry.GetOpenAccessMode());

	// Return this object
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
