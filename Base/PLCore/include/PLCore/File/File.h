/*********************************************************\
 *  File: File.h                                         *
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


#ifndef __PLCORE_FILE_H__
#define __PLCORE_FILE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/File/FileObject.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class for accessing a file in the file system
*/
class File : public FileObject {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    File access flags
		*/
		enum EAccess {
			FileRead	=  1,	/**< File can be read */
			FileWrite	=  2,	/**< File can be written */
			FileAppend	=  4,	/**< File will be appended */
			FileCreate	=  8,	/**< File will be created */
			FileText	= 16,	/**< File will be opened in text mode */
			FileMemBuf	= 32	/**< File will be opened memory buffered (only usable for reading!) */
		};

		/**
		*  @brief
		*    Seek position enumerations
		*/
		enum ESeek {
			SeekSet = 0,	/**< Seek relative to the start of the file (default setting) */
			SeekCurrent,	/**< Seek relative to the current position */
			SeekEnd			/**< Seek relative to the end of the file */
		};


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		PLCORE_API static File StandardInput;	/**< Standard OS input stream (stdin) */
		PLCORE_API static File StandardOutput;	/**< Standard OS output stream (stdout) */
		PLCORE_API static File StandardError;	/**< Standard OS error stream (stderr) */


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Translates a given C file mode into access flags
		*
		*  @param[in] sMode
		*    C file mode ("r", "r+", "w", "w+", "a", "a+", "t", "r+t" etc. used for e.g. "fopen") to translate
		*
		*  @return
		*    The access flags (see EAccess)
		*/
		PLCORE_API static uint32 CFileModeToAccessFlags(const String &sMode);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API File();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sUrl
		*    URL of a file
		*  @param[in] pAccess
		*    Additional file access information (can be a null pointer)
		*/
		PLCORE_API File(const String &sUrl, const FileAccess *pAccess = nullptr);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cUrl
		*    URL of a file
		*  @param[in] pAccess
		*    Additional file access information (can be a null pointer)
		*/
		PLCORE_API File(const Url &cUrl, const FileAccess *pAccess = nullptr);

		/**
		*  @brief
		*    Constructor for a standard OS stream
		*
		*  @param[in] pFile
		*    Standard stream pointer
		*  @param[in] nAccess
		*    Access flags that were used to open the stream
		*/
		PLCORE_API File(FILE *pFile, uint32 nAccess);

		/**
		*  @brief
		*    Constructor
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
		PLCORE_API File(handle hFile);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pnData
		*    The file data, if a null pointer same as the standard constructor
		*  @param[in] nNumOfBytes
		*    Number of file data bytes, MUST be valid!
		*  @param[in] bCopy
		*    Copy the given data or use this one directly? Do ONLY set bCopy to 'false'
		*    if you are sure there can't go anything wrong. (data pointer MUST stay valid!)
		*  @param[in] sUrl
		*    URL of a file
		*/
		PLCORE_API File(uint8 *pnData, uint32 nNumOfBytes, bool bCopy = true, const String &sUrl = "");

		/**
		*  @brief
		*    Destructor
		*
		*  @note
		*    - The file is closed automatically
		*/
		PLCORE_API virtual ~File();

		/**
		*  @brief
		*    Create file
		*
		*  @param[in] bAlways
		*    If 'true', the file is created (and therefore overwritten) if it already exists
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		PLCORE_API bool Create(bool bAlways = false);

		/**
		*  @brief
		*    Delete file
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		PLCORE_API bool Delete();

		/**
		*  @brief
		*    Open the file for reading and/or writing
		*
		*  @param[in] nAccess
		*    Access mode, combination of 'EAccess' flags
		*
		*  @return
		*    'false' on error, else 'true'
		*
		*  @note
		*    - 'FileStandardInput', 'FileStandardOutput' and 'FileStandardError' are special access flags that can't
		*      be combined with other flags and the filename must be empty
		*/
		PLCORE_API bool Open(uint32 nAccess);

		/**
		*  @brief
		*    Close the file
		*/
		PLCORE_API void Close();

		/**
		*  @brief
		*    Returns whether the file is memory buffered (opened with flag 'FileMemBuf')
		*
		*  @return
		*    'true', if the file is memory buffered, else 'false'
		*
		*  @see
		*    - GetMemoryBuffer()
		*/
		PLCORE_API bool IsMemoryBuffered() const;

		/**
		*  @brief
		*    Returns whether the file is open
		*
		*  @return
		*    'true', if the file is open, else 'false'
		*/
		PLCORE_API bool IsOpen() const;

		/**
		*  @brief
		*    Returns whether the file is readable
		*
		*  @return
		*    'true', if the file can be read, else 'false'
		*/
		PLCORE_API bool IsReadable() const;

		/**
		*  @brief
		*    Returns whether the file is writable
		*
		*  @return
		*    'true', if the file can be written, else 'false'
		*/
		PLCORE_API bool IsWritable() const;

		/**
		*  @brief
		*    Returns whether end of file has been reached
		*
		*  @return
		*    'true', if the end of the file has been reached, else 'false'
		*/
		PLCORE_API bool IsEof() const;

		/**
		*  @brief
		*    Reads a character
		*
		*  @return
		*    A character from file, < 0 if there was an error
		*/
		PLCORE_API int GetC();

		/**
		*  @brief
		*    Writes a character
		*
		*  @param[in] nChar
		*    Character to write
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe file is read only)
		*/
		PLCORE_API bool PutC(int nChar);

		/**
		*  @brief
		*    Reads a string
		*
		*  @return
		*    Read string
		*/
		PLCORE_API String GetS();

		/**
		*  @brief
		*    Writes a string
		*
		*  @param[in] sString
		*    String which should be written into the file
		*
		*  @return
		*    Number of bytes written, 0 if nothing was written, < 0 if there was an error
		*/
		PLCORE_API int PutS(const String &sString);

		/**
		*  @brief
		*    Reads the given number of bytes
		*
		*  @param[out] pBuffer
		*    Buffer were the data should be copied in (MUST valid and large enough!)
		*  @param[in]  nSize
		*    Item size in bytes
		*  @param[in]  nCount
		*    Maximum number of items to be read
		*
		*  @return
		*    Number of fully read items, if != 'nCount' an error occurred
		*/
		PLCORE_API uint32 Read(void *pBuffer, uint32 nSize, uint32 nCount);

		/**
		*  @brief
		*    Writes the given number of bytes
		*
		*  @param[in] pBuffer
		*    Buffer with the data which should be written into the file (MUST valid and large enough!)
		*  @param[in] nSize
		*    Item size in bytes
		*  @param[in] nCount
		*    Maximum number of items to be written
		*
		*  @return
		*    Number of fully written items, if != 'nCount' an error occurred
		*/
		PLCORE_API uint32 Write(const void *pBuffer, uint32 nSize, uint32 nCount);

		/**
		*  @brief
		*    Flushs the file buffer
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*    Writes down all temporarily buffered data.
		*/
		PLCORE_API bool Flush();

		/**
		*  @brief
		*    Sets the starting position
		*
		*  @param[in] nOffset
		*    File offset in bytes relative to the given location
		*  @param[in] nLocation
		*    Location
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool Seek(int32 nOffset = 0, ESeek nLocation = SeekSet);

		/**
		*  @brief
		*    Gets the current position of the file pointer
		*
		*  @return
		*    The current byte position of the file pointer, < 0 if there was an error
		*/
		PLCORE_API int32 Tell() const;

		/**
		*  @brief
		*    Returns the file size
		*
		*  @return
		*    File size in bytes
		*/
		PLCORE_API uint32 GetSize() const;

		/**
		*  @brief
		*    Writes a string into the file
		*
		*  @param[in] sString
		*    String which should be written into the file
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool Print(const String &sString);

		/**
		*  @brief
		*    Writes a string and a newline into the file
		*
		*  @param[in] sString
		*    String which should be written into the file
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool PrintLn(const String &sString);

		/**
		*  @brief
		*    Returns a pointer to the buffer for memory buffered file
		*
		*  @return
		*    Pointer to the buffer for memory buffered file, a null pointer if there's no such buffer
		*
		*  @see
		*    - IsMemoryBuffered()
		*/
		PLCORE_API const uint8 *GetMemoryBuffer() const;

		/**
		*  @brief
		*    Returns the complete content of the file as string
		*
		*  @param[in] nFormat
		*    String format, "String::ASCII" or "String::Unicode" (not recommended!)
		*
		*  @return
		*    The complete file content as string, empty string on error or if the file is just empty
		*
		*  @note
		*    - It's not recommended to read in Unicode by using this method because internally
		*      wchar_t is used and this data type has not the same size on every platform
		*/
		PLCORE_API String GetContentAsString(String::EFormat nFormat = String::ASCII);


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
		File(const File &cSource);

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
		File &operator =(const File &cSource);

		/**
		*  @brief
		*    Open the file (for memory buffered files)
		*
		*  @param[in] nAccess
		*    Access mode (see EAccess)
		*
		*  @return
		*    'false' on error, else 'true'
		*/
		bool MemBufOpen(uint32 nAccess);

		/**
		*  @brief
		*    Close the file (for memory buffered files)
		*/
		void MemBufClose();

		/**
		*  @brief
		*    Reads a character (for memory buffered files)
		*
		*  @return
		*    A character from file, < 0 if there was an error
		*/
		int MemBufGetC();

		/**
		*  @brief
		*    Reads a string (for memory buffered files)
		*
		*  @return
		*    Read string
		*/
		String MemBufGetS();

		/**
		*  @brief
		*    Reads the given number of bytes (for memory buffered files)
		*
		*  @param[out] pBuffer
		*    Buffer were the data should be copied in (MUST valid and large enough!)
		*  @param[in]  nSize
		*    Item size in bytes
		*  @param[in]  nCount
		*    Maximum number of items to be read
		*
		*  @return
		*    Number of fully read items, if != 'nCount' an error occurred
		*/
		uint32 MemBufRead(void *pBuffer, uint32 nSize, uint32 nCount);

		/**
		*  @brief
		*    Sets the starting position (for memory buffered files)
		*
		*  @param[in] nOffset
		*    File offset in bytes relative to the given location
		*  @param[in] nLocation
		*    Location
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool MemBufSeek(int32 nOffset, ESeek nLocation);


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    File internal access flags
		*/
		enum EInternalAccess {
			FileMemBufShared = 64	/**< Opened memory buffered is shared and is NOT allowed to be destroyed by this file object! */
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		uint8  *m_pMemBuf;			/**< Buffer for memory buffered file, can be a null pointer */
		uint32  m_nMemBufSize;		/**< Size of memory buffered file */
		uint32  m_nMemBufPos;		/**< Seek position for memory buffered file */
		uint32  m_nMemBufAccess;	/**< Access flags for memory buffered file */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_FILE_H__
