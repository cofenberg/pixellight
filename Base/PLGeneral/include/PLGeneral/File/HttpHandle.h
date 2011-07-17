/*********************************************************\
 *  File: HttpHandle.h                                   *
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


#ifndef __PLGENERAL_FILE_HTTPHANDLE_H__
#define __PLGENERAL_FILE_HTTPHANDLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/File/File.h"
#include "PLGeneral/Network/Socket.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    This class represents a tiny HTTP (Hypertext Transfer Protocol) client to download files via HTTP
*
*  @remarks
*    You don't need to use it directly, as you can also use the HTTP protocol through the
*    File/Directory classes, e.g.: File("http://www.pixellight.org/welcome.html")
*
*  @note
*    - Port: 80/TCP
*/
class HttpHandle {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API HttpHandle();

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API ~HttpHandle();

		/**
		*  @brief
		*    Check if the connection is currently open
		*
		*  @return
		*    'true' if the connection is currently open, else 'false'
		*/
		PLGENERAL_API bool IsOpen() const;

		/**
		*  @brief
		*    Open the connection
		*
		*  @param[in] sUrl
		*    URL
		*  @param[in] sUsername
		*    Username
		*  @param[in] sPassword
		*    Password
		*
		*  @return
		*    'true', if the file could be opened, 'false' on error
		*/
		PLGENERAL_API bool Open(const String &sUrl, const String &sUsername, const String &sPassword);

		/**
		*  @brief
		*    Close the connection
		*
		*  @return
		*    'true', if the file could be closed, 'false' on error
		*/
		PLGENERAL_API bool Close();

		/**
		*  @brief
		*    Get HTTP response string
		*
		*  @return
		*    HTTP response
		*/
		PLGENERAL_API String GetResponse() const;

		/**
		*  @brief
		*    Get HTTP authenticate string
		*
		*  @return
		*    HTTP authenticate-field
		*/
		PLGENERAL_API String GetAuthenticate() const;

		/**
		*  @brief
		*    Get HTTP server string
		*
		*  @return
		*    HTTP server-field
		*/
		PLGENERAL_API String GetServer() const;

		/**
		*  @brief
		*    Get HTTP date string
		*
		*  @return
		*    HTTP date-field
		*/
		PLGENERAL_API String GetDate() const;

		/**
		*  @brief
		*    Get HTTP ContentType string
		*
		*  @return
		*    HTTP ContentType-field
		*/
		PLGENERAL_API String GetContentType() const;

		/**
		*  @brief
		*    Get HTTP content-length
		*
		*  @return
		*    HTTP ContentLength-field
		*/
		PLGENERAL_API int GetContentLength() const;

		/**
		*  @brief
		*    Reads data from the connection
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


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Connects to the webserver
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		bool Connect();

		/**
		*  @brief
		*    Reads a single line from the HTTP header
		*
		*  @return
		*    Next line from the header, "" at the end
		*/
		String ReadLine();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Socket	m_cSocket;			/**< Socket */
		Url		m_cUrl;				/**< Current URL */
		String	m_sDomain;			/**< Domain part of the URL */
		String	m_sUsername;		/**< Username */
		String	m_sPassword;		/**< Password */
		String	m_sResponse;		/**< HTTP Response */
		String	m_sAuthenticate;	/**< HTTP WWW-Authenticate-field */
		String	m_sServer;			/**< HTTP Server-field */
		String	m_sDate;			/**< HTTP Date-field */
		String	m_sContentType;		/**< HTTP ContentType-field */
		int		m_nContentLength;	/**< HTTP ContentLength-field */
		int		m_nPosition;		/**< Current stream position */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_FILE_HTTPHANDLE_H__
