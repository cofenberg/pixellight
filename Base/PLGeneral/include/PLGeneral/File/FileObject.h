/*********************************************************\
 *  File: FileObject.h                                   *
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


#ifndef __PLGENERAL_FILEOBJECT_H__
#define __PLGENERAL_FILEOBJECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/File/StdIo.h"
#include "PLGeneral/File/Url.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class FileImpl;
class FileAccess;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Base class for files and directories
*
*  @remarks
*    When working with archive file objects, you have to differ whether you want to use the
*    archive files as 'file' or whether you want do use it as 'directory'. Here some examples:
*      FileObject("test.zip") .IsFile()      -> true
*      FileObject("test.zip") .IsDirectory() -> false
*      FileObject("test.zip/").IsFile()      -> false
*      FileObject("test.zip/").IsDirectory() -> true
*
*  @note
*    - Implementation of the state design pattern, this class is the context
*/
class FileObject {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API FileObject();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sUrl
		*    URL of the file or directory
		*  @param[in] pAccess
		*    Additional file access information (can be a null pointer)
		*/
		PLGENERAL_API FileObject(const String &sUrl, const FileAccess *pAccess = nullptr);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cUrl
		*    URL of the file or directory
		*  @param[in] pAccess
		*    Additional file access information (can be a null pointer)
		*/
		PLGENERAL_API FileObject(const Url &cUrl, const FileAccess *pAccess = nullptr);

		/**
		*  @brief
		*    Destructor
		*
		*  @note
		*    - The file object is closed automatically
		*/
		PLGENERAL_API virtual ~FileObject();

		/**
		*  @brief
		*    Assign a new URL
		*
		*  @param[in] sUrl
		*    URL of the file or directory
		*  @param[in] pAccess
		*    Additional file access information (can be a null pointer)
		*/
		PLGENERAL_API void Assign(const String &sUrl, const FileAccess *pAccess = nullptr);

		/**
		*  @brief
		*    Assign a new URL
		*
		*  @param[in] cUrl
		*    URL of the file or directory
		*  @param[in] pAccess
		*    Additional file access information (can be a null pointer)
		*/
		PLGENERAL_API void Assign(const Url &cUrl, const FileAccess *pAccess = nullptr);

		/**
		*  @brief
		*    Assign a new file
		*
		*  @param[in] pFile
		*    Standard stream pointer
		*  @param[in] nAccess
		*    Access flags that were used to open the stream
		*/
		PLGENERAL_API void Assign(FILE *pFile, uint32 nAccess);

		/**
		*  @brief
		*    Assign a new file
		*
		*  @param[in] hFile
		*    OS file handle
		*
		*  @note
		*    - On Linux, the handle is a file handle of type int.
		*    - On Windows, the handle is a file handle of type HANDLE.
		*      Do not expect an int (fileno) here! If you need it to work with
		*      low level io functions, you need to convert the HANDLE to a
		*      file handle by yourself (see _open_osfhandle).
		*/
		PLGENERAL_API void Assign(handle hFile);

		/**
		*  @brief
		*    Get URL
		*
		*  @return
		*    URL of the file
		*
		*  @note
		*    - The URL of a 'FileObject' always contains a filename that never ends with "/"! (so, you can safely
		*      use 'Url::GetFilename()' to get the name of any file or directory)
		*    - e.g.: 'Directory("C:\\test")' and 'Directory("C:\\test\\")' are equal, but
		*      'GetUrl()' will always return "C:/test".
		*/
		PLGENERAL_API const Url &GetUrl() const;

		/**
		*  @brief
		*    Check if the file or directory exists
		*
		*  @return
		*    'true', if the object is existing, else 'false'
		*/
		PLGENERAL_API bool Exists() const;

		/**
		*  @brief
		*    Returns if the object is a regular file
		*
		*  @return
		*    'true', if the object is a file, else 'false'
		*/
		PLGENERAL_API bool IsFile() const;

		/**
		*  @brief
		*    Returns if the object is a directory
		*
		*  @return
		*    'true', if the object is a directory, else 'false'
		*/
		PLGENERAL_API bool IsDirectory() const;

		/**
		*  @brief
		*    Copy the file or directory to a new location
		*
		*  @param[in] sDest
		*    URL of the destination
		*  @param[in] bOverwrite
		*    Shall the file be overwritten if it already exists?
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		PLGENERAL_API bool Copy(const String &sDest, bool bOverwrite = false) const;

		/**
		*  @brief
		*    Move the file or directory to a new location
		*
		*  @param[in] sDest
		*    URL of the destination
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		PLGENERAL_API bool Move(const String &sDest);

		/**
		*  @brief
		*    Rename the file or directory
		*
		*  @param[in] sName
		*    New filename (filename only, no path)
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		PLGENERAL_API bool Rename(const String &sName);

		/**
		*  @brief
		*    Close the file or directory
		*/
		PLGENERAL_API void Close();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor for a standard OS stream
		*
		*  @param[in] pFile
		*    Standard stream pointer
		*  @param[in] nAccess
		*    Access flags that were used to open the stream
		*/
		PLGENERAL_API FileObject(FILE *pFile, uint32 nAccess);

		/**
		*  @brief
		*    Constructor for a OS file handle
		*
		*  @param[in] hFile
		*    OS file handle
		*/
		PLGENERAL_API FileObject(handle hFile);

		/**
		*  @brief
		*    Generic implementation of 'Copy()' (if system-implementation does not work)
		*
		*  @param[in] sDest
		*    URL of the destination
		*  @param[in] bOverwrite
		*    Shall the file be overwritten if it already exists?
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		PLGENERAL_API bool GenericCopy(const String &sDest, bool bOverwrite = false) const;

		/**
		*  @brief
		*    Generic implementation of 'Move()' (if system-implementation does not work)
		*
		*  @param[in] sDest
		*    URL of the destination
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		PLGENERAL_API bool GenericMove(const String &sDest);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		FileObject(const FileObject &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		FileObject &operator =(const FileObject &cSource);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		FileImpl *m_pFileImpl;	/**< Platform implementation for file object (can be a null pointer) */
		Url		  m_cNullUrl;	/**< Empty URL */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_FILEOBJECT_H__
