/*********************************************************\
 *  File: FileStdStream.h                                *
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


#ifndef __PLGENERAL_FILE_STDSTREAM_H__
#define __PLGENERAL_FILE_STDSTREAM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/File/StdIo.h"
#include "PLGeneral/File/FileImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Standard OS file stream implementation of 'FileImpl'
*
*  @remarks
*    This implementation works either on a FILE* or on an OS file handle
*    (HANDLE on Windows, int on Linux). This can be used to access files
*    that have been returned by other functions/libraries.
*/
class FileStdStream : public FileImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class FileObject;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pFile
		*    Standard stream pointer
		*  @param[in] nAccess
		*    Access flags that were used to open the stream
		*/
		FileStdStream(FILE *pFile, uint32 nAccess);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] hFile
		*    System file handle
		*
		*  @note
		*    - On Linux, the handle is a file handle of type int.
		*    - On Windows, the handle is a file handle of type HANDLE.
		*      Do not expect an int (fileno) here! If you need it to work with
		*      low level io functions, you need to convert the HANDLE to a
		*      file handle by yourself (see _open_osfhandle).
		*/
		FileStdStream(handle hFile);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~FileStdStream();


	//[-------------------------------------------------------]
	//[ Private virtual FileImpl functions                    ]
	//[-------------------------------------------------------]
	private:
		virtual bool Exists() const;
		virtual bool IsFile() const;
		virtual bool IsDirectory() const;
		virtual bool CopyTo(const String &sDest, bool bOverwrite) const;
		virtual bool MoveTo(const String &sDest);
		virtual bool Rename(const String &sName);
		virtual bool CreateNewFile(bool bAlways);
		virtual bool CreateNewDirectory();
		virtual bool Delete();
		virtual bool DeleteDirectory();
		virtual void Close();
		virtual bool Open(uint32 nAccess);
		virtual bool IsOpen() const;
		virtual bool IsReadable() const;
		virtual bool IsWritable() const;
		virtual bool IsEof() const;
		virtual int GetC();
		virtual bool PutC(int nChar);
		virtual String GetS();
		virtual int PutS(const String &sString);
		virtual uint32 Read(void *pBuffer, uint32 nSize, uint32 nCount);
		virtual uint32 Write(const void *pBuffer, uint32 nSize, uint32 nCount);
		virtual bool Flush();
		virtual bool Seek(int32 nOffset, File::ESeek nLocation);
		virtual int32 Tell() const;
		virtual uint32 GetSize() const;
		virtual FileSearchImpl *CreateSearch();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool	m_bStream;	/**< If 'true', m_pFile is used, otherwise m_hFile */
		FILE   *m_pFile;	/**< Pointer to file stream, can be NULL */
		handle	m_hFile;	/**< System file handle */
		uint32  m_nAccess;	/**< File access modes (see EAccess) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_FILE_STDSTREAM_H__
