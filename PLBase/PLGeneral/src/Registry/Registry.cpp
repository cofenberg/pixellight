/*********************************************************\
 *  File: Registry.cpp                                   *
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
	m_pRegistryImpl(NULL)
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
	m_pRegistryImpl(NULL)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pRegistryImpl = new RegistryWindows();
	#endif

	// Open registry key
	if (m_pRegistryImpl) {
		m_pRegistryImpl->Open(nKey, sSubKey, nAccess);
	}
}

/**
*  @brief
*    Copy constructor
*/
Registry::Registry(const Registry &cRegistry) :
	m_pRegistryImpl(NULL)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pRegistryImpl = new RegistryWindows();
	#endif

	// Open the same key again
	if (m_pRegistryImpl) {
		Open(cRegistry.GetOpenKey(), cRegistry.GetOpenSubKey(), cRegistry.GetOpenAccessMode());
	}
}

/**
*  @brief
*    Destructor
*/
Registry::~Registry()
{
	// Delete system implementation
	if (m_pRegistryImpl) delete m_pRegistryImpl;
}

/**
*  @brief
*    Get type of registry
*/
Registry::ERegistry Registry::GetRegistryType() const
{
	if (m_pRegistryImpl) return m_pRegistryImpl->GetRegistryType();
	else				 return None;
}

/**
*  @brief
*    Open registry key
*/
bool Registry::Open(EKey nKey, const String &sSubKey, uint32 nAccess)
{
	if (m_pRegistryImpl) return m_pRegistryImpl->Open(nKey, sSubKey, nAccess);
	else				 return false;
}

/**
*  @brief
*    Create a new registry key
*/
bool Registry::Create(EKey nKey, const String &sSubKey, uint32 nAccess)
{
	if (m_pRegistryImpl) return m_pRegistryImpl->Create(nKey, sSubKey, nAccess);
	else				 return false;
}

/**
*  @brief
*    Delete the registry key
*/
bool Registry::Delete()
{
	if (m_pRegistryImpl) return m_pRegistryImpl->Delete();
	else				 return false;
}

/**
*  @brief
*    Close registry key
*/
void Registry::Close()
{
	if (m_pRegistryImpl) return m_pRegistryImpl->Close();
}

/**
*  @brief
*    Get ID of opened registry key
*/
Registry::EKey Registry::GetOpenKey() const
{
	if (m_pRegistryImpl) return m_pRegistryImpl->GetOpenKey();
	else				 return KeyNone;
}

/**
*  @brief
*    Get name of opened sub-key
*/
String Registry::GetOpenSubKey() const
{
	if (m_pRegistryImpl) return m_pRegistryImpl->GetOpenSubKey();
	else				 return "";
}

/**
*  @brief
*    Get access modes
*/
uint32 Registry::GetOpenAccessMode() const
{
	if (m_pRegistryImpl) return m_pRegistryImpl->GetOpenAccessMode();
	else				 return 0;
}

/**
*  @brief
*    Returns the number of sub-keys
*/
uint32 Registry::GetNumOfSubKeys() const
{
	if (m_pRegistryImpl) return m_pRegistryImpl->GetNumOfSubKeys();
	else				 return 0;
}

/**
*  @brief
*    Get a sub-key of the opened registry key
*/
String Registry::GetSubKey(uint32 nIndex) const
{
	if (m_pRegistryImpl) return m_pRegistryImpl->GetSubKey(nIndex);
	else				 return "";
}

/**
*  @brief
*    Returns the number of values
*/
uint32 Registry::GetNumOfValues() const
{
	if (m_pRegistryImpl) return m_pRegistryImpl->GetNumOfValues();
	else				 return 0;
}

/**
*  @brief
*    Get a value of the opened registry key
*/
String Registry::GetValue(uint32 nIndex) const
{
	if (m_pRegistryImpl) return m_pRegistryImpl->GetValue(nIndex);
	else				 return "";
}

/**
*  @brief
*    Get the type of a given value
*/
Registry::EType Registry::GetValueType(const String &sName) const
{
	if (m_pRegistryImpl) return m_pRegistryImpl->GetValueType(sName);
	else				 return TypeNone;
}

/**
*  @brief
*    Get a value of type string
*/
String Registry::GetValueString(const String &sName) const
{
	if (m_pRegistryImpl) return m_pRegistryImpl->GetValueString(sName);
	else				 return "";
}

/**
*  @brief
*    Get a value of type dword
*/
uint32 Registry::GetValueDWord(const String &sName) const
{
	if (m_pRegistryImpl) return m_pRegistryImpl->GetValueDWord(sName);
	else				 return 0;
}

/**
*  @brief
*    Get a value of type binary
*/
uint32 Registry::GetValueBinary(const String &sName, uint8 *pBuffer, uint32 nSize) const
{
	if (m_pRegistryImpl) return m_pRegistryImpl->GetValueBinary(sName, pBuffer, nSize);
	else				 return 0;
}

/**
*  @brief
*    Set a value of type string
*/
bool Registry::SetValueString(const String &sName, const String &sValue)
{
	if (m_pRegistryImpl) return m_pRegistryImpl->SetValueString(sName, sValue);
	else				 return false;
}

/**
*  @brief
*    Set a value of type dword
*/
bool Registry::SetValueDWord(const String &sName, uint32 nValue)
{
	if (m_pRegistryImpl) return m_pRegistryImpl->SetValueDWord(sName, nValue);
	else				 return false;
}

/**
*  @brief
*    Set a value of type binary
*/
bool Registry::SetValueBinary(const String &sName, const uint8 *pBuffer, uint32 nSize)
{
	if (m_pRegistryImpl) return m_pRegistryImpl->SetValueBinary(sName, pBuffer, nSize);
	else				 return false;
}

/**
*  @brief
*    Write all values to the registry
*/
void Registry::Flush()
{
	if (m_pRegistryImpl) return m_pRegistryImpl->Flush();
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
