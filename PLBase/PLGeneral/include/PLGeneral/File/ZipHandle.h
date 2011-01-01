/*********************************************************\
 *  File: ZipHandle.h                                    *
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


#ifndef __PLGENERAL_ZIPHANDLE_H__
#define __PLGENERAL_ZIPHANDLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/File/File.h"
#include "PLGeneral/Tools/Time.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
struct z_stream_s;
typedef z_stream_s z_stream;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    This class represents a handle for working on a ZIP-file
*
*  @remarks
*    It can be used to navigate inside the ZIP-file and read data from it, but you don't need
*    to use it directly, as ZIP-files can be directly accessed through the File/Directory classes
*    (e.g.: File("C:\\test.zip\\readme.txt") to extract a file from a ZIP-file)
*/
class ZipHandle {


	//[-------------------------------------------------------]
	//[ ZIP file entry                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Represents an entry (file or directory) in a ZIP-file
		*/
		class ZipEntry {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				/**
				*  @brief
				*    Constructor
				*/
				PLGENERAL_API ZipEntry();

				/**
				*  @brief
				*    Copy constructor
				*
				*  @param[in] cZipEntry
				*    ZipEntry to copy
				*/
				PLGENERAL_API ZipEntry(const ZipEntry &cZipEntry);

				/**
				*  @brief
				*    Destructor
				*/
				PLGENERAL_API ~ZipEntry();

				/**
				*  @brief
				*    Assignment operator
				*
				*  @param[in] cZipEntry
				*    ZipEntry to copy
				*
				*  @return
				*    Reference to this instance
				*/
				PLGENERAL_API ZipEntry &operator =(const ZipEntry &cZipEntry);

				/**
				*  @brief
				*    Clear entry
				*/
				PLGENERAL_API void Clear();

				/**
				*  @brief
				*    Allocate memory for extra-field
				*
				*  @param[in] nSize
				*    Size of extra-field
				*/
				PLGENERAL_API void AllocateExtraField(uint16 nSize);


			//[-------------------------------------------------------]
			//[ Public fields                                         ]
			//[-------------------------------------------------------]
			public:
				bool	m_bValid;				/**< Is the current entry valid? */
				String  m_sFilename;			/**< Filename */
				String  m_sComment;				/**< File comment */
				uint16  m_nVersion;				/**< Version made by                 2 bytes */
				uint16  m_nVersionNeeded;		/**< Version needed to extract       2 bytes */
				uint16  m_nFlags;				/**< General purpose bit flag        2 bytes */
				uint16  m_nCompressionMethod;	/**< Compression method              2 bytes */
				uint32  m_nDOSDate;				/**< Last mod file date in DOS fmt   4 bytes */
				uint32  m_nCRC;					/**< Crc-32                          4 bytes */
				uint32  m_nCompressedSize;		/**< Compressed size                 4 bytes */
				uint32  m_nUncompressedSize;	/**< Uncompressed size               4 bytes */
				uint16  m_nSizeFilename;		/**< Filename length                 2 bytes */
				uint16  m_nSizeFileExtra;		/**< Extra field length              2 bytes */
				uint16  m_nSizeFileComment;		/**< File comment length             2 bytes */
				uint16  m_nDiskNumStart;		/**< Disk number start               2 bytes */
				uint16  m_nInternalAttr;		/**< Internal file attributes        2 bytes */
				uint32  m_nExternalAttr;		/**< External file attributes        4 bytes */
				uint32  m_nOffsetCurFile;		/**< Relative offset of local header 4 bytes */
				Time    m_cTime;				/**< Time of the current file */
				uint8  *m_pExtraField;			/**< Extra data, can be NULL */


		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ General                                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API ZipHandle();

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API ~ZipHandle();

		/**
		*  @brief
		*    Check if the ZIP-file is open
		*
		*  @return
		*    'true', if the file is valid, 'false' on error
		*/
		PLGENERAL_API bool IsOpen() const;

		/**
		*  @brief
		*    Open the ZIP-file
		*
		*  @param[in] sFilename
		*    Filename of the ZIP-file
		*  @param[in] sPassword
		*    Password if the file is encrypted, else empty string
		*  @param[in] bCaseSensitive
		*    Shall the filenames be treated case sensitive?
		*  @param[in] bMemBuf
		*    Shall the ZIP-file be read into a memory-buffer?
		*  @param[in] pAccess
		*    Access information to pass through (can be NULL)
		*
		*  @return
		*    'true', if the file could be opened, 'false' on error
		*/
		PLGENERAL_API bool Open(const String &sFilename, const String &sPassword, bool bCaseSensitive = true, bool bMemBuf = true, const FileAccess *pAccess = NULL);

		/**
		*  @brief
		*    Close the ZIP file
		*
		*  @return
		*    'true', if the file could be closed, 'false' on error
		*/
		PLGENERAL_API bool Close();

		/**
		*  @brief
		*    Returns whether names treated case sensitive
		*
		*  @return
		*    'true' if names treated case sensitive, else 'false'
		*/
		PLGENERAL_API bool IsCaseSensitive() const;

		//[-------------------------------------------------------]
		//[ Enumerate entries in the ZIP-file                     ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Sets the pointer to the first entry in the ZIP-file
		*
		*  @return
		*    'true', if the file is valid, 'false' on error
		*/
		PLGENERAL_API bool LocateFirstFile();

		/**
		*  @brief
		*    Sets the pointer to the next entry in the ZIP-file
		*
		*  @return
		*    'true', if the file is valid, 'false' on error
		*/
		PLGENERAL_API bool LocateNextFile();

		/**
		*  @brief
		*    Sets the pointer to a specific entry in the ZIP-file
		*
		*  @param[in] sFilename
		*    Name of the file
		*
		*  @return
		*    'true', if the file is valid, 'false' on error
		*/
		PLGENERAL_API bool LocateFile(const String &sFilename);

		/**
		*  @brief
		*    Get information about the current entry in the ZIP-file
		*
		*  @return
		*    Current ZipEntry, could be invalid (see ZipEntry::IsValid)
		*/
		PLGENERAL_API const ZipEntry &GetCurrentFile() const;

		//[-------------------------------------------------------]
		//[ Read file from ZIP-file                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Check if a file is currently open
		*
		*  @return
		*    'true' if a file is currently open, else 'false'
		*/
		PLGENERAL_API bool IsFileOpen() const;

		/**
		*  @brief
		*    Open the currently selected file
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLGENERAL_API bool OpenFile();

		/**
		*  @brief
		*    Close file
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLGENERAL_API bool CloseFile();

		/**
		*  @brief
		*    Reads data from the file
		*
		*  @param[out] pBuffer
		*    Buffer to store the data (MUST be valid and large enough!)
		*  @param[in]  nSize
		*    Item size in bytes
		*  @param[in]  nCount
		*    Number of items to read
		*
		*  @return
		*    Number of full read items, if != 'nCount' an error occured
		*/
		PLGENERAL_API uint32 Read(void *pBuffer, uint32 nSize, uint32 nCount);

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
		PLGENERAL_API bool Seek(int32 nOffset, File::ESeek nLocation);

		/**
		*  @brief
		*    Returns the file position
		*
		*  @return
		*    Current position within the file, or < 0 on error
		*/
		PLGENERAL_API int32 Tell() const;

		/**
		*  @brief
		*    Returns whether end of file has been reached
		*
		*  @return
		*    'true', if the end of the file has been reached, else 'false'
		*/
		PLGENERAL_API bool IsEof() const;

		/**
		*  @brief
		*    Gets the size of the current file's extra data field
		*
		*  @return
		*    Size of the local data field
		*/
		PLGENERAL_API uint32 GetLocalExtrafieldSize() const;

		/**
		*  @brief
		*    Reads the extra data of the current file
		*
		*  @param[out] pBuffer
		*    Buffer to store the data (MUST valid and large enough!)
		*  @param[in]  nSize
		*    Size of the buffer (MUST be valid!)
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		PLGENERAL_API bool GetLocalExtrafield(void *pBuffer, uint32 nSize);


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
		ZipHandle(const ZipHandle &cSource);

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
		ZipHandle &operator =(const ZipHandle &cSource);

		/**
		*  @brief
		*    Opens the ZIP-file
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		bool OpenZipFile();

		/**
		*  @brief
		*    Search for the central directory entry within the ZIP-file
		*
		*  @return
		*    Position of the central directory, 0 on error
		*/
		uint32 SearchCentralDir();

		/**
		*  @brief
		*    Reads the information about the current file
		*
		*  @return
		*    'true', if the file is valid, 'false' on error
		*/
		bool ReadCurrentFileInfo();

		/**
		*  @brief
		*    Checks the local header of the selected file
		*
		*  @param[out] nSizeVar
		*    Will receive the total local header size
		*  @param[out] nPosLocalExtra
		*    Will receive the position of the local extra
		*  @param[out] nSizeLocalExtra
		*    Will receive the size of the local extra
		*  @param[out] nFlags
		*    Will receive the flags
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool CheckFileHeader(uint32 &nSizeVar, uint32 &nPosLocalExtra, uint32 &nSizeLocalExtra, uint16 &nFlags);

		/**
		*  @brief
		*    Reads a byte from the ZIP-file
		*
		*  @param[out] nByte
		*    Will receive the read byte value
		*
		*  @return
		*    'true' if everything went fine, else 'false' ('nByte' is set to 0)
		*/
		bool ReadByte(uint8 &nByte);

		/**
		*  @brief
		*    Reads a unsigned short from the ZIP-file
		*
		*  @param[out] nShort
		*    Will receive the read unsigned short value
		*
		*  @return
		*    'true' if everything went fine, else 'false' ('nShort' is set to 0)
		*/
		bool ReadShort(uint16 &nShort);

		/**
		*  @brief
		*    Reads a unsigned long from the ZIP-file
		*
		*  @param[out] nLong
		*    Will receive the read unsigned long value
		*
		*  @return
		*    'true' if everything went fine, else 'false' ('nLong' is set to 0)
		*/
		bool ReadLong(uint32 &nLong);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// General
		File		m_cZipFile;				/**< ZIP-file to work on */
		bool		m_bCaseSensitive;		/**< Are names treated case sensitive? */
		bool		m_bMemBuf;				/**< Read ZIP-file memory-buffered? */

		// Information about the ZIP-file
		bool		m_bZipFileValid;		/**< Error flag */
		uint16		m_nNumEntries;			/**< Number of directory entries in the ZIP-file */
		uint16		m_nCommentSize;			/**< Size of the ZIP-file comment */
		uint32		m_nBytesBeforeZip;		/**< Byte before the ZIP-file, (> 0 for sfx) */
		uint32		m_nCentralDirPos;		/**< Position of the beginning of the central directory */
		uint32		m_nCentralDirSize;		/**< Size of the central directory */
		uint32		m_nCentralDirOffset;	/**< Offset of start of central directory with respect to the starting disk number */
		uint16		m_nDiskNum;				/**< Disk number (for splitted ZIP-files) */
		uint16		m_nMainDisk;			/**< Disk number that contains the central directory */
		uint16		m_nMainEntries;			/**< Number of entries in the central directory on this disk */

		// Currently selected file
		ZipEntry	m_cCurFile;				/**< Current file entry */
		uint32		m_nCurFile;				/**< Number of the current file in the ZIP-file */
		uint32		m_nCurCentralDirPos;	/**< Position of the current file in the central directory */

		// Stream data
		uint8      *m_pReadBuffer;			/**< Internal buffer for compressed data (always valid!) */
		z_stream   *m_pStream;				/**< ZLib stream structure for inflate, can be NULL */
		uint32		m_nPosInZip;			/**< Position in byte on the ZIP-file, for fseek */
		uint32		m_nPosLocalExtra;		/**< Offset of the local extra field */
		uint32		m_nSizeLocalExtra;		/**< Size of the local extra field */
		uint32		m_nPosInLocalExtra;		/**< Position in the local extra field in read */
		uint32		m_nCRC32;				/**< CRC32 of all data uncompressed */
		uint32		m_nCRC32Wait;			/**< CRC32 we must obtain after decompress all */
		uint32		m_nReadCompressed;		/**< Number of byte to be decompressed */
		uint32		m_nReadUncompressed;	/**< Number of byte to be obtained after decompression */
		uint16		m_nCompressionMethod;	/**< Currently used compression method (copied from cCurrentFile) */

		// Encryption data
		bool		m_bEncrypted;			/**< Is the file encrypted? */
		uint32		m_nKeys[3];				/**< Decryption keys, initialized by constructor */
		int			m_nEncheadLeft;			/**< The first call(s) to Read() will read this many encryption-header bytes first */
		char		m_nCRCEncTest;			/**< If encrypted, we'll check the encryption buffer against this */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_ZIPHANDLE_H__
