/*********************************************************\
 *  File: RegistryWindows.cpp                            *
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
#include "PLGeneral/Registry/RegistryWindows.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RegistryWindows::RegistryWindows() :
	m_nKey(Registry::KeyNone),
	m_nAccess(0),
	m_hKey(NULL)
{
}

/**
*  @brief
*    Destructor
*/
RegistryWindows::~RegistryWindows()
{
	// Close registry key
	Close();
}


//[-------------------------------------------------------]
//[ Private virtual RegistryImpl functions                ]
//[-------------------------------------------------------]
Registry::ERegistry RegistryWindows::GetRegistryType() const
{
	// We have a Windows registry
	return Registry::Windows;
}

bool RegistryWindows::Open(Registry::EKey nKey, const String &sSubKey, uint32 nAccess)
{
	// Close first
	Close();

	// Save options
	m_nKey	  = nKey;
	m_sSubKey = sSubKey;
	m_nAccess = nAccess;

	// Get root key
	HKEY hRootKey = NULL;
	switch (nKey) {
		case Registry::KeyClassesRoot:	hRootKey = HKEY_CLASSES_ROOT;	break;
		case Registry::KeyCurrentUser:	hRootKey = HKEY_CURRENT_USER;	break;
		case Registry::KeyLocalMachine:	hRootKey = HKEY_LOCAL_MACHINE;	break;
		case Registry::KeyUsers:		hRootKey = HKEY_USERS;			break;
		default:						return false; // Error!
	}

	// Get access modes
	REGSAM nMode = 0;
	if (nAccess & Registry::RegRead)	nMode |= KEY_READ;
	if (nAccess & Registry::RegWrite)	nMode |= KEY_WRITE;
	if (nAccess & Registry::RegNotify)	nMode |= KEY_NOTIFY;

	// Open key
	return (RegOpenKeyExW(hRootKey, sSubKey.GetUnicode(), 0, nMode, &m_hKey) == ERROR_SUCCESS);
}

bool RegistryWindows::Create(Registry::EKey nKey, const String &sSubKey, uint32 nAccess)
{
	// Close first
	Close();

	// Save options
	m_nKey	  = nKey;
	m_sSubKey = sSubKey;
	m_nAccess = nAccess;

	// Get root key
	HKEY hRootKey = NULL;
	switch (nKey) {
		case Registry::KeyClassesRoot:	hRootKey = HKEY_CLASSES_ROOT;	break;
		case Registry::KeyCurrentUser:	hRootKey = HKEY_CURRENT_USER;	break;
		case Registry::KeyLocalMachine:	hRootKey = HKEY_LOCAL_MACHINE;	break;
		case Registry::KeyUsers:		hRootKey = HKEY_USERS;			break;
		default:						return false; // Error!
	}

	// Get access modes
	REGSAM nMode = 0;
	if (nAccess & Registry::RegRead)	nMode |= KEY_READ;
	if (nAccess & Registry::RegWrite)	nMode |= KEY_WRITE;
	if (nAccess & Registry::RegNotify)	nMode |= KEY_NOTIFY;

	// Create key
	return (RegCreateKeyExW(hRootKey, sSubKey.GetUnicode(), 0, NULL, REG_OPTION_NON_VOLATILE, nMode, NULL, &m_hKey, NULL) == ERROR_SUCCESS);
}

bool RegistryWindows::Delete()
{
	// Close first
	Close();

	// Get root key
	HKEY hRootKey = NULL;
	switch (m_nKey) {
		case Registry::KeyClassesRoot:	hRootKey = HKEY_CLASSES_ROOT;	break;
		case Registry::KeyCurrentUser:	hRootKey = HKEY_CURRENT_USER;	break;
		case Registry::KeyLocalMachine:	hRootKey = HKEY_LOCAL_MACHINE;	break;
		case Registry::KeyUsers:		hRootKey = HKEY_USERS;			break;
		default:						return false; // Error!
	}

	// Delete key
	return (RegDeleteKeyW(hRootKey, m_sSubKey.GetUnicode()) == ERROR_SUCCESS);
}

void RegistryWindows::Close()
{
	// Close registry key
	if (m_hKey != NULL) {
		RegCloseKey(m_hKey);
		m_hKey = NULL;
	}
}

Registry::EKey RegistryWindows::GetOpenKey() const
{
	// Return key ID
	return m_nKey;
}

String RegistryWindows::GetOpenSubKey() const
{
	// Return sub-key name
	return m_sSubKey;
}

uint32 RegistryWindows::GetOpenAccessMode() const
{
	// Return access modes
	return m_nAccess;
}

uint32 RegistryWindows::GetNumOfSubKeys() const
{
	// Key opened?
	if (m_hKey) {
		// Get number of sub-keys
		DWORD nSubKeys = 0;
		if (RegQueryInfoKeyW(m_hKey, NULL, NULL, NULL, &nSubKeys, NULL, NULL, NULL, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
			return nSubKeys; // Done
		}
	}

	// Error!
	return 0;
}

String RegistryWindows::GetSubKey(uint32 nIndex) const
{
	// Key opened?
	if (m_hKey) {
		// Get maximum size of name
		DWORD nSize = 0;
		if (RegQueryInfoKeyW(m_hKey, NULL, NULL, NULL, NULL, &nSize, NULL, NULL, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
			// Allocate buffer
			nSize++;
			wchar_t *pszName = new wchar_t[nSize];

			// Get name of sub-key
			if (RegEnumKeyW(m_hKey, nIndex, pszName, nSize) == ERROR_SUCCESS) {
				return String(pszName, false); // Do not copy, please
			} else delete [] pszName;
		}
	}

	// Error!
	return "";
}

uint32 RegistryWindows::GetNumOfValues() const
{
	// Key opened?
	if (m_hKey) {
		// Get number of sub-keys
		DWORD nValues = 0;
		if (RegQueryInfoKeyW(m_hKey, NULL, NULL, NULL, NULL, NULL, NULL, &nValues, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
			return nValues; // Done
		}
	}

	// Error!
	return 0;
}

String RegistryWindows::GetValue(uint32 nIndex) const
{
	// Key opened?
	if (m_hKey) {
		// Query maximum size of name
		DWORD nSize = 0;
		if (RegQueryInfoKeyW(m_hKey, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &nSize, NULL, NULL, NULL) == ERROR_SUCCESS) {
			// Allocate buffer
			nSize++;
			wchar_t *pszName = new wchar_t[nSize];

			// Get name of value
			if (RegEnumValueW(m_hKey, nIndex, pszName, &nSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
				return String(pszName, false); // Do not copy, please
			} else delete [] pszName;
		}
	}

	// Error!
	return "";
}

Registry::EType RegistryWindows::GetValueType(const String &sName) const
{
	// Key opened?
	if (m_hKey) {
		// Get value type
		DWORD nType;
		if (RegQueryValueExW(m_hKey, sName.GetUnicode(), 0, &nType, NULL, NULL) == ERROR_SUCCESS) {
			// Return type of value
			switch (nType) {
				case REG_BINARY:	return Registry::TypeBinary;
				case REG_DWORD:		return Registry::TypeDWord;
				case REG_SZ:		return Registry::TypeString;
				case REG_EXPAND_SZ:	return Registry::TypeExpandString;
				case REG_MULTI_SZ:	return Registry::TypeMultiString;
			}
		}
	}

	// Error!
	return Registry::TypeNone;
}

String RegistryWindows::GetValueString(const String &sName) const
{
	// Key opened?
	if (m_hKey) {
		// Query size of value
		DWORD nSize = 0;
		if (RegQueryValueExW(m_hKey, sName.GetUnicode(), 0, NULL, NULL, &nSize) == ERROR_SUCCESS) {
			// Allocate buffer
			nSize++;
			wchar_t *pszValue = new wchar_t[nSize];

			// Get value
			if (RegQueryValueExW(m_hKey, sName.GetUnicode(), 0, NULL, (BYTE*)pszValue, &nSize) == ERROR_SUCCESS) {
				return String(pszValue, false); // Do not copy, please
			} else delete [] pszValue;
		}
	}

	// Error!
	return "";
}

uint32 RegistryWindows::GetValueDWord(const String &sName) const
{
	// Key opened?
	if (m_hKey) {
		// Get value
		DWORD nSize = sizeof(DWORD);
		DWORD nValue;
		if (RegQueryValueExW(m_hKey, sName.GetUnicode(), 0, NULL, (BYTE*)&nValue, &nSize) == ERROR_SUCCESS) {
			return nValue; // Done
		}
	}

	// Error!
	return 0;
}

uint32 RegistryWindows::GetValueBinary(const String &sName, uint8 *pBuffer, uint32 nSize) const
{
	// Key opened?
	if (m_hKey) {
		// Get value
		DWORD dwSize = nSize;
		if (RegQueryValueExW(m_hKey, sName.GetUnicode(), 0, NULL, (BYTE*)pBuffer, &dwSize) == ERROR_SUCCESS) {
			return dwSize; // Done
		}
	}

	// Error!
	return 0;
}

bool RegistryWindows::SetValueString(const String &sName, const String &sValue)
{
	// Key opened?
	if (m_hKey) {
		// Set value
		String sValueW = sValue.GetUnicode();
		if (RegSetValueExW(m_hKey, sName.GetUnicode(), 0, REG_SZ, (BYTE*)sValueW.GetUnicode(), sValueW.GetNumOfBytes()) == ERROR_SUCCESS) {
			return true; // Done
		}
	}

	// Error!
	return false;
}

bool RegistryWindows::SetValueDWord(const String &sName, uint32 nValue)
{
	// Key opened?
	if (m_hKey) {
		// Set value
		if (RegSetValueExW(m_hKey, sName.GetUnicode(), 0, REG_DWORD, (BYTE*)&nValue, sizeof(nValue)) == ERROR_SUCCESS) {
			return true; // Done
		}
	}

	// Error!
	return false;
}

bool RegistryWindows::SetValueBinary(const String &sName, const uint8 *pBuffer, uint32 nSize)
{
	// Key opened?
	if (m_hKey && pBuffer && nSize) {
		// Set value
		if (RegSetValueExW(m_hKey, sName.GetUnicode(), 0, REG_BINARY, (BYTE*)pBuffer, nSize) == ERROR_SUCCESS) {
			return true; // Done
		}
	}

	// Error!
	return false;
}

void RegistryWindows::Flush()
{
	// Key opened?
	if (m_hKey) {
		// Flush
		RegFlushKey(m_hKey);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
