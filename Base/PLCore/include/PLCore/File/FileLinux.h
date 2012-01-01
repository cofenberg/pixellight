/*********************************************************\
 *  File: FileLinux.h                                    *
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


#ifndef __PLCORE_FILE_LINUX_H__
#define __PLCORE_FILE_LINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <stdio.h>
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
*    Linux implementation of FileImpl
*
*  @note
*    - Implementation of the state design pattern, this class is a concrete state of the 'FileImpl'-state of the 'FileObject'-context
*/
class FileLinux : public FileImpl {


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
		*  @param[in] cUrl
		*    URL of the file or directory
		*  @param[in] pAccess
		*    Additional file access information (can be a null pointer)
		*/
		FileLinux(const Url &cUrl, const FileAccess *pAccess);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~FileLinux();


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
		virtual bool Open(uint32 nAccess, String::EFormat nStringFormat = String::ASCII) override;
		virtual bool IsOpen() const override;
		virtual bool IsReadable() const override;
		virtual bool IsWritable() const override;
		virtual String::EFormat GetStringFormat() const override;
		virtual bool IsEof() const override;
		virtual int GetC() override;
		virtual bool PutC(int nChar) override;
		virtual String GetS() override;
		virtual int PutS(const String &sString) override;
		virtual uint32 Read(void *pBuffer, uint32 nSize, uint32 nCount) override;
		virtual uint32 Write(const void *pBuffer, uint32 nSize, uint32 nCount) override;
		virtual bool Flush() override;
		virtual bool Seek(int32 nOffset, uint32 nLocation) override;
		virtual int32 Tell() const override;
		virtual uint32 GetSize() const override;
		virtual FileSearchImpl *CreateSearch() override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		String	 m_sFilename;	/**< File name (in Linux notation) */
		uint32	 m_nAccess;		/**< File access modes (see EAccess) */
		FILE	*m_pFile;		/**< Pointer to input stream, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_FILE_LINUX_H__
