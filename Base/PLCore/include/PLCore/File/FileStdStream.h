/*********************************************************\
 *  File: FileStdStream.h                                *
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


#ifndef __PLCORE_FILE_STDSTREAM_H__
#define __PLCORE_FILE_STDSTREAM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/File/StdIo.h"
#include "PLCore/File/FileImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


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
		virtual bool Exists() const override;
		virtual bool IsFile() const override;
		virtual bool IsDirectory() const override;
		virtual bool CopyTo(const String &sDest, bool bOverwrite) const override;
		virtual bool MoveTo(const String &sDest) override;
		virtual bool Rename(const String &sName) override;
		virtual bool CreateNewFile(bool bAlways) override;
		virtual bool CreateNewDirectory() override;
		virtual bool Delete() override;
		virtual bool DeleteDirectory() override;
		virtual void Close() override;
		virtual bool Open(uint32 nAccess) override;
		virtual bool IsOpen() const override;
		virtual bool IsReadable() const override;
		virtual bool IsWritable() const override;
		virtual bool IsEof() const override;
		virtual int GetC() override;
		virtual bool PutC(int nChar) override;
		virtual String GetS() override;
		virtual int PutS(const String &sString) override;
		virtual uint32 Read(void *pBuffer, uint32 nSize, uint32 nCount) override;
		virtual uint32 Write(const void *pBuffer, uint32 nSize, uint32 nCount) override;
		virtual bool Flush() override;
		virtual bool Seek(int32 nOffset, File::ESeek nLocation) override;
		virtual int32 Tell() const override;
		virtual uint32 GetSize() const override;
		virtual FileSearchImpl *CreateSearch() override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool	m_bStream;	/**< If 'true', m_pFile is used, otherwise m_hFile */
		FILE   *m_pFile;	/**< Pointer to file stream, can be a null pointer */
		handle	m_hFile;	/**< System file handle */
		uint32  m_nAccess;	/**< File access modes (see EAccess) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_FILE_STDSTREAM_H__
