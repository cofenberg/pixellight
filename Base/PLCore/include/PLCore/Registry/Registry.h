/*********************************************************\
 *  File: Registry.h                                     *
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


#ifndef __PLCORE_REGISTRY_H__
#define __PLCORE_REGISTRY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class RegistryImpl;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Registry key handle
*
*  @remarks
*    For Windows OS: Please note, if you access the registry on a 64 bit OS by using
*    a 32 bit application 'Wow6432Node' may be added automatically by the OS. Usually this
*    is no problem as long as you always use a 32 bit application to access this data - but
*    if you have a 64 bit application and want to access the same registry data the 32 bit
*    application is using you have to keep this topic in mind.
*/
class Registry {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Registry types
		*/
		enum ERegistry {
			None = 0,	/**< None */
			Windows		/**< Windows */
		};

		/**
		*  @brief
		*    Registry keys
		*/
		enum EKey {
			KeyNone = 0,		/**< None */
			KeyClassesRoot,		/**< Classes root */
			KeyCurrentUser,		/**< Current user */
			KeyLocalMachine,	/**< Local machine */
			KeyUsers			/**< Users */
		};

		/**
		*  @brief
		*    Registry access
		*/
		enum EAccess {
			RegRead   = 1,	/**< Read */
			RegWrite  = 2,	/**< Write */
			RegNotify = 4	/**< Notify */
		};

		/**
		*  @brief
		*    Registry value types
		*/
		enum EType {
			TypeNone = 0,		/**< None */
			TypeBinary,			/**< Binary */
			TypeDWord,			/**< Double word */
			TypeString,			/**< String */
			TypeExpandString,	/**< Expand string */
			TypeMultiString		/**< Multi string */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API Registry();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nKey
		*    Registry key
		*  @param[in] sSubKey
		*    Name of subkey
		*  @param[in] nAccess
		*    Access modes (combination of 'EAccess' values)
		*/
		PLCORE_API Registry(EKey nKey, const String &sSubKey, uint32 nAccess);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cRegistry
		*    Registry handle to copy
		*/
		PLCORE_API Registry(const Registry &cRegistry);

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API ~Registry();

		/**
		*  @brief
		*    Get type of registry
		*
		*  @return
		*    Type of registry ('None' if no registry is available on your system!)
		*/
		PLCORE_API ERegistry GetRegistryType() const;

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
		PLCORE_API bool Open(EKey nKey, const String &sSubKey, uint32 nAccess);

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
		PLCORE_API bool Create(EKey nKey, const String &sSubKey, uint32 nAccess);

		/**
		*  @brief
		*    Delete the registry key
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool Delete();

		/**
		*  @brief
		*    Close registry key
		*/
		PLCORE_API void Close();

		/**
		*  @brief
		*    Get ID of opened registry key
		*
		*  @return
		*    Key ID
		*/
		PLCORE_API EKey GetOpenKey() const;

		/**
		*  @brief
		*    Get name of opened sub-key
		*
		*  @return
		*    Name of sub-key
		*/
		PLCORE_API String GetOpenSubKey() const;

		/**
		*  @brief
		*    Get access modes
		*
		*  @return
		*    Access modes
		*/
		PLCORE_API uint32 GetOpenAccessMode() const;

		/**
		*  @brief
		*    Returns the number of sub-keys
		*
		*  @return
		*    Number of sub-keys
		*/
		PLCORE_API uint32 GetNumOfSubKeys() const;

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
		PLCORE_API String GetSubKey(uint32 nIndex) const;

		/**
		*  @brief
		*    Returns the number of values
		*
		*  @return
		*    Number of values
		*/
		PLCORE_API uint32 GetNumOfValues() const;

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
		PLCORE_API String GetValue(uint32 nIndex) const;

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
		PLCORE_API EType GetValueType(const String &sName) const;

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
		PLCORE_API String GetValueString(const String &sName) const;

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
		PLCORE_API uint32 GetValueDWord(const String &sName) const;

		/**
		*  @brief
		*    Get a value of type binary
		*
		*  @param[in]  sName
		*    Name of the value
		*  @param[out] pBuffer
		*    Buffer to receive the value, if a null pointer, returns the number of  bytes required
		*  @param[in]  nSize
		*    Size of the given buffer in bytes, ignored if 'pBuffer' is a null pointer
		*
		*  @return
		*    Number of bytes written to the buffer
		*/
		PLCORE_API uint32 GetValueBinary(const String &sName, uint8 *pBuffer, uint32 nSize) const;

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
		PLCORE_API bool SetValueString(const String &sName, const String &sValue);

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
		PLCORE_API bool SetValueDWord(const String &sName, uint32 nValue);

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
		PLCORE_API bool SetValueBinary(const String &sName, const uint8 *pBuffer, uint32 nSize);

		/**
		*  @brief
		*    Write all values to the registry
		*/
		PLCORE_API void Flush();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cRegistry
		*    Source registry to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		PLCORE_API Registry &operator =(const Registry &cRegistry);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		RegistryImpl *m_pRegistryImpl;	/**< Pointer to the system specific implementation (can be a null pointer!) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_REGISTRY_H__
