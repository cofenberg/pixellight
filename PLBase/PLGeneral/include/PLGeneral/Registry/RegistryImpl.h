/*********************************************************\
 *  File: RegistryImpl.h                                 *
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


#ifndef __PLGENERAL_REGISTRY_IMPL_H__
#define __PLGENERAL_REGISTRY_IMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Registry/Registry.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract base class for platform specific 'Registry' implementations
*/
class RegistryImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Registry;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		RegistryImpl();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~RegistryImpl();


	//[-------------------------------------------------------]
	//[ Protected virtual RegistryImpl functions              ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Get type of registry
		*
		*  @return
		*    Type of registry ('RegistryNone' if no registry is available on your system!)
		*/
		virtual Registry::ERegistry GetRegistryType() const = 0;

		/**
		*  @brief
		*    Open registry key
		*
		*  @param[in] nKey
		*    Registry key
		*  @param[in] sSubKey
		*    Name of subkey
		*  @param[in] nAccess
		*    Access modes (combination of 'EAccess' values)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Open(Registry::EKey nKey, const String &sSubKey, uint32 nAccess) = 0;

		/**
		*  @brief
		*    Create a new registry key
		*
		*  @param[in] nKey
		*    Registry key
		*  @param[in] sSubKey
		*    Name of subkey
		*  @param[in] nAccess
		*    Access modes (combination of 'EAccess' values)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Create(Registry::EKey nKey, const String &sSubKey, uint32 nAccess) = 0;

		/**
		*  @brief
		*    Delete the registry key
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Delete() = 0;

		/**
		*  @brief
		*    Close registry key
		*/
		virtual void Close() = 0;

		/**
		*  @brief
		*    Get ID of opened registry key
		*
		*  @return
		*    Key ID
		*/
		virtual Registry::EKey GetOpenKey() const = 0;

		/**
		*  @brief
		*    Get name of opened sub-key
		*
		*  @return
		*    Name of sub-key
		*/
		virtual String GetOpenSubKey() const = 0;

		/**
		*  @brief
		*    Get access mode
		*
		*  @return
		*    Access mode
		*/
		virtual uint32 GetOpenAccessMode() const = 0;

		/**
		*  @brief
		*    Returns the number of sub-keys
		*
		*  @return
		*    Number of sub-keys
		*/
		virtual uint32 GetNumOfSubKeys() const = 0;

		/**
		*  @brief
		*    Get a sub-key of the opened registry key
		*
		*  @param[in] nIndex
		*    Index of the sub-key
		*
		*  @return
		*    Name of the sub-key, or "" if no more sub-keys are present
		*/
		virtual String GetSubKey(uint32 nIndex) const = 0;

		/**
		*  @brief
		*    Returns the number of values
		*
		*  @return
		*    Number of values
		*/
		virtual uint32 GetNumOfValues() const = 0;

		/**
		*  @brief
		*    Get a value of the opened registry key
		*
		*  @param[in] nIndex
		*    Index of the value
		*
		*  @return
		*    Name of the value, or "" if no more values are present
		*/
		virtual String GetValue(uint32 nIndex) const = 0;

		/**
		*  @brief
		*    Get the type of a given value
		*
		*  @param[in] sName
		*    Name of the value
		*
		*  @return
		*    Type of the value
		*/
		virtual Registry::EType GetValueType(const String &sName) const = 0;

		/**
		*  @brief
		*    Get a value of type string
		*
		*  @param[in] sName
		*    Name of the value
		*
		*  @return
		*    String value
		*/
		virtual String GetValueString(const String &sName) const = 0;

		/**
		*  @brief
		*    Get a value of type 'dword'
		*
		*  @param[in] sName
		*    Name of the value
		*
		*  @return
		*    Value
		*/
		virtual uint32 GetValueDWord(const String &sName) const = 0;

		/**
		*  @brief
		*    Get a value of type binary
		*
		*  @param[in] sName
		*    Name of the value
		*  @param[out] pBuffer
		*    Buffer to receive the value, if a null pointer, returns the number of  bytes required
		*  @param[in]  nSize
		*    Size of the given buffer in bytes, ignored if 'pBuffer' is a null pointer
		*
		*  @return
		*    Number of bytes written to the buffer
		*/
		virtual uint32 GetValueBinary(const String &sName, uint8 *pBuffer, uint32 nSize) const = 0;

		/**
		*  @brief
		*    Set a value of type string
		*
		*  @param[in] sName
		*    Name of the value
		*  @param[in] sValue
		*    String value to set
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool SetValueString(const String &sName, const String &sValue) = 0;

		/**
		*  @brief
		*    Set a value of type 'dword'
		*
		*  @param[in] sName
		*    Name of the value
		*  @param[in] nValue
		*    Value to set
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool SetValueDWord(const String &sName, uint32 nValue) = 0;

		/**
		*  @brief
		*    Set a value of type binary
		*
		*  @param[in] sName
		*    Name of the value
		*  @param[in] pBuffer
		*    Buffer containing the value to set (if a null pointer, the function fails)
		*  @param[in] nSize
		*    Size of the given buffer in bytes
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool SetValueBinary(const String &sName, const uint8 *pBuffer, uint32 nSize) = 0;

		/**
		*  @brief
		*    Write all values to the registry
		*/
		virtual void Flush() = 0;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_REGISTRY_IMPL_H__
