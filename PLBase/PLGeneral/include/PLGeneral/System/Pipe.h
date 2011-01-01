/*********************************************************\
 *  File: Pipe.h                                         *
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


#ifndef __PLGENERAL_PIPE_H__
#define __PLGENERAL_PIPE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class to create and access system pipes (named or unnamed)
*/
class Pipe {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API Pipe();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy
		*/
		PLGENERAL_API Pipe(const Pipe &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API ~Pipe();

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] cSource
		*    Source to copy
		*
		*  @return
		*    Reference to this Pipe
		*/
		PLGENERAL_API Pipe &operator =(const Pipe &cSource);

		/**
		*  @brief
		*    Comparison operator
		*
		*  @param[in] cSource
		*    Pipe to compare with
		*
		*  @return
		*    'true', if both Pipe's are equal, else 'false'
		*/
		PLGENERAL_API bool operator ==(const Pipe &cSource) const;

		/**
		*  @brief
		*    Comparison operator
		*
		*  @param[in] cSource
		*    Pipe to compare with
		*
		*  @return
		*    'true', if the Pipe's are different, else 'false'
		*/
		PLGENERAL_API bool operator !=(const Pipe &cSource) const;

		/**
		*  @brief
		*    Creates a new unnamend pipe
		*
		*  @return
		*    'true', if the pipe could be created, else 'false'
		*/
		PLGENERAL_API bool Create();

		/**
		*  @brief
		*    Creates a new namend pipe
		*
		*  @param[in] sName
		*    Name of the pipe
		*
		*  @return
		*    'true', if the pipe could be created, else 'false'
		*/
		PLGENERAL_API bool Create(const String &sName);

		/**
		*  @brief
		*    Open a pipe by file handles
		*
		*  @param[in] hRead
		*    Handle to the read end of the pipe
		*  @param[in] hWrite
		*    Handle to the write end of the pipe
		*
		*  @return
		*    'true', if the pipe could be opened, else 'false'
		*/
		PLGENERAL_API bool Open(handle hRead, handle hWrite);

		/**
		*  @brief
		*    Close read side of the pipe
		*
		*  @return
		*    'true', if the read side could be closed, else 'false'
		*/
		PLGENERAL_API bool CloseRead();

		/**
		*  @brief
		*    Close write side of the pipe
		*
		*  @return
		*    'true', if the write side could be closed, else 'false'
		*/
		PLGENERAL_API bool CloseWrite();

		/**
		*  @brief
		*    Close both sides of the pipe
		*
		*  @return
		*    'true', if the pipe could be closed, else 'false'
		*/
		PLGENERAL_API bool Close();

		/**
		*  @brief
		*    Get name of pipe
		*
		*  @return
		*    Name of the pipe
		*/
		PLGENERAL_API String GetName() const;

		/**
		*  @brief
		*    Get read handle for the pipe
		*
		*  @return
		*    Handle for the read-end of the pipe
		*
		*  @note
		*    - On Linux, the handle is a file handle of type int
		*    - On Windows, the handle is a file handle of type HANDLE
		*/
		PLGENERAL_API handle GetReadHandle() const;

		/**
		*  @brief
		*    Get write handle for the pipe
		*
		*  @return
		*    Handle for the write-end of the pipe
		*
		*  @see
		*    - GetReadHandle()
		*/
		PLGENERAL_API handle GetWriteHandle() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Pipe data
		String	m_sName;		/**< Name of the pipe */
		handle	m_hPipe[2];		/**< Pipe handles (0 = read end, 1 = write end) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_PIPE_H__
