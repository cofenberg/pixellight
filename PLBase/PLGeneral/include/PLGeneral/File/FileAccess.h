/*********************************************************\
 *  File: FileAccess.h                                   *
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


#ifndef __PLGENERAL_FILEACCESS_H__
#define __PLGENERAL_FILEACCESS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/String.h"
#include "PLGeneral/Container/HashMap.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    This class contains information about how to access a file
*
*  @remarks
*    It can be used to supply authentication for files, e.g. username and password for a HTTP-connection
*    or a password for an encrypted ZIP-file, as well as other access options.
*    Please consider this information as hints that can be passed to the file-functions, it is not guaranteed
*    that everything you enter here will be used! (e.g. a ZIP-file won't be open with Write-Access, regardless
*    of what you pass in FlagsMask/FlagsValue)
*/
class FileAccess {


	//[-------------------------------------------------------]
	//[ File access entry                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Contains access information for a certain file/URL
		*/
		class Entry {


			//[-------------------------------------------------------]
			//[ Friends                                               ]
			//[-------------------------------------------------------]
			friend class FileAccess;


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				/**
				*  @brief
				*    Constructor
				*/
				PLGENERAL_API Entry();

				/**
				*  @brief
				*    Copy constructor
				*
				*  @param[in] cEntry
				*    Entry to copy
				*/
				PLGENERAL_API Entry(const Entry &cEntry);

				/**
				*  @brief
				*    Destructor
				*/
				PLGENERAL_API ~Entry();

				/**
				*  @brief
				*    Get ID
				*
				*  @return
				*    Entry ID
				*/
				PLGENERAL_API uint32 GetID() const;

				/**
				*  @brief
				*    Assignment operator
				*
				*  @param[in] cEntry
				*    Entry to copy
				*
				*  @return
				*    Reference to this instance
				*/
				PLGENERAL_API Entry &operator =(const Entry &cEntry);

				/**
				*  @brief
				*    Comparison operator
				*
				*  @param[in] cEntry
				*    Entry to compare to
				*
				*  @return
				*    'true' if both entries are equal, else 'false'
				*/
				PLGENERAL_API bool operator ==(const Entry &cEntry) const;

				/**
				*  @brief
				*    Get username
				*
				*  @return
				*    Username
				*/
				PLGENERAL_API String GetUsername() const;

				/**
				*  @brief
				*    Set username
				*
				*  @param[in] sUsername
				*    Username
				*/
				PLGENERAL_API void SetUsername(const String &sUsername);

				/**
				*  @brief
				*    Get password
				*
				*  @return
				*    Password
				*/
				PLGENERAL_API String GetPassword() const;

				/**
				*  @brief
				*    Set password
				*
				*  @param[in] sPassword
				*    Password
				*/
				PLGENERAL_API void SetPassword(const String &sPassword);

				/**
				*  @brief
				*    Set username and password
				*
				*  @param[in] sUsername
				*    Username
				*  @param[in] sPassword
				*    Password
				*/
				PLGENERAL_API void SetAuth(const String &sUsername, const String &sPassword);

				/**
				*  @brief
				*    Get case-sensitive
				*
				*  @return
				*    Case-sensitive-flag
				*/
				PLGENERAL_API bool GetCaseSensitive() const;

				/**
				*  @brief
				*    Set case-sensitive
				*
				*  @param[in] bCaseSensitive
				*    Case-sensitive-flag
				*/
				PLGENERAL_API void SetCaseSensitive(bool bCaseSensitive);

				/**
				*  @brief
				*    Get flags mask
				*
				*  @return
				*    Flags mask
				*/
				PLGENERAL_API uint32 GetFlagsMask() const;

				/**
				*  @brief
				*    Set flags mask
				*
				*  @param[in] nFlagsMask
				*    Flags mask
				*/
				PLGENERAL_API void SetFlagsMask(uint32 nFlagsMask);

				/**
				*  @brief
				*    Get flags value
				*
				*  @return
				*    Flags value
				*/
				PLGENERAL_API uint32 GetFlagsValue() const;

				/**
				*  @brief
				*    Set flags value
				*
				*  @param[in] nFlagsValue
				*    Flags value
				*/
				PLGENERAL_API void SetFlagsValue(uint32 nFlagsValue);

				/**
				*  @brief
				*    Get user flags
				*
				*  @return
				*    User flags
				*/
				PLGENERAL_API uint32 GetUserFlags() const;

				/**
				*  @brief
				*    Set user flags
				*
				*  @param[in] nUserFlags
				*    User flags
				*/
				PLGENERAL_API void SetUserFlags(uint32 nUserFlags);

				/**
				*  @brief
				*    Get user data
				*
				*  @return
				*    User data, can be NULL
				*/
				PLGENERAL_API void *GetUserData() const;

				/**
				*  @brief
				*    Set user data
				*
				*  @param[in] pUserData
				*    User data, can be NULL
				*/
				PLGENERAL_API void SetUserData(void *pUserData);

				/**
				*  @brief
				*    Get user info
				*
				*  @return
				*    User info
				*/
				PLGENERAL_API String GetUserInfo() const;

				/**
				*  @brief
				*    Set user info
				*
				*  @param[in] sUserInfo
				*    User info
				*/
				PLGENERAL_API void SetUserInfo(const String &sUserInfo);


			//[-------------------------------------------------------]
			//[ Private data                                          ]
			//[-------------------------------------------------------]
			private:
				uint32  m_nID;				/**< Unique entry ID */
				String  m_sUsername;		/**< Username for restricted access */
				String  m_sPassword;		/**< Password for restricted access */
				bool    m_bCaseSensitive;	/**< Case sensitivity */
				uint32  m_nFlagsMask;		/**< Mask of file-flags (see File::EAccess) */
				uint32  m_nFlagsValue;		/**< Values of file-flags (see File::EAccess) */
				uint32  m_nUserFlags;		/**< User defined flags */
				void   *m_pUserData;		/**< User defined data, can be NULL */
				String  m_sUserInfo;		/**< USer defined string */


		};


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		static const Entry NullEntry;	/**< Empty entry */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API FileAccess();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cFileAccess
		*    FileAccess object to copy
		*/
		PLGENERAL_API FileAccess(const FileAccess &cFileAccess);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API ~FileAccess();

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] cFileAccess
		*    'FileAccess' object to copy
		*
		*  @return
		*    Reference to this instance
		*/
		PLGENERAL_API FileAccess &operator =(const FileAccess &cFileAccess);

		/**
		*  @brief
		*    Check if an entry with a given name is available
		*
		*  @param[in] sName
		*    Name of the entry
		*
		*  @return
		*    'true' if the entry is set, else 'false'
		*/
		PLGENERAL_API bool HasEntry(const String &sName) const;

		/**
		*  @brief
		*    Returns an entry with a given name
		*
		*  @param[in] sName
		*    Name of the entry
		*
		*  @return
		*    Reference to that entry if it exists, else 'NullEntry'
		*/
		PLGENERAL_API const Entry &GetEntry(const String &sName) const;
		PLGENERAL_API const Entry &operator [](const String &sName) const;

		/**
		*  @brief
		*    Returns an entry with a given name
		*
		*  @param[in] sName
		*    Name of the entry
		*
		*  @return
		*    Reference to that entry, creates a new entry if it didn't exist before
		*/
		PLGENERAL_API Entry &GetEntry(const String &sName);
		PLGENERAL_API Entry &operator [](const String &sName);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		HashMap<String, Entry>	m_mapEntries;	/**< List of FileAccess entries */
		uint32					m_nNextID;		/**< ID counter for entries */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_FILEACCESS_H__
