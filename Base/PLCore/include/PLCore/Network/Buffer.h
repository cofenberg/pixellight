/*********************************************************\
 *  File: Buffer.h                                       *
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


#ifndef __PLCORE_BUFFER_H__
#define __PLCORE_BUFFER_H__
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
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Network buffer
*
*  @remarks
*    This buffer can be used within concrete network implementations to manage send/received
*    network data.
*/
class Buffer {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nSize
		*    Size of the buffer in bytes, if 0, no buffer is allocated
		*/
		PLCORE_API Buffer(uint32 nSize = 0);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLCORE_API Buffer(const Buffer &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API ~Buffer();

		/**
		*  @brief
		*    Get option for removing line delimiters
		*
		*  @return
		*    'true' if line delimiters shall be removed, else 'false'
		*/
		PLCORE_API bool GetRemoveLineDelimiters() const;

		/**
		*  @brief
		*    Set option for removing line delimiters
		*
		*  @param[in] bRemoveDelimiters
		*    'true' if line delimiters shall be removed, else 'false'
		*/
		PLCORE_API void SetRemoveLineDelimiters(bool bRemoveDelimiters);

		/**
		*  @brief
		*    Clear buffer
		*/
		PLCORE_API void Clear();

		/**
		*  @brief
		*    Allocates a new buffer (all previous data will be lost)
		*
		*  @param[in] nSize
		*    Size of the buffer in bytes, if 0, no buffer is allocated (same as just Clear())
		*/
		PLCORE_API void Allocate(uint32 nSize);

		/**
		*  @brief
		*    Get current buffer size
		*
		*  @return
		*    The current buffer size in bytes
		*/
		PLCORE_API uint32 GetSize() const;

		/**
		*  @brief
		*    Add data to the buffer
		*
		*  @param[in] pData
		*    Data to add, if a null pointer nothing happens
		*  @param[in] nSize
		*    Size of the data to add in bytes (MUST be correct!)
		*/
		PLCORE_API void Add(const char *pData, uint32 nSize);

		/**
		*  @brief
		*    Get a line from the buffer
		*
		*  @return
		*    The read line, empty string on error
		*
		*  @note
		*    - The read line is removed from buffer
		*    - \r\n will be replaced by \0.
		*/
		PLCORE_API String GetLine();

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
		PLCORE_API Buffer &operator =(const Buffer &cSource);

		/**
		*  @brief
		*    Get data
		*
		*  @return
		*    Pointer to buffer
		*/
		PLCORE_API const char *GetData() const;

		/**
		*  @brief
		*    Get data
		*
		*  @return
		*    Pointer to buffer
		*/
		PLCORE_API char *GetData();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		char	*m_pBuffer;				/**< Data buffer, can be a null pointer */
		uint32   m_nSize;				/**< Size of buffer */
		uint32   m_nUsed;				/**< Currenty used size */
		bool	m_bRemoveDelimiters;	/**< Remove line delimiters (CR/LF)? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_BUFFER_H__
