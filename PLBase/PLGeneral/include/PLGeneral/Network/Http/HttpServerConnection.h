/*********************************************************\
 *  File: HttpServerConnection.h                         *
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


#ifndef __PLGENERAL_HTTPSERVERCONNECTION_H__
#define __PLGENERAL_HTTPSERVERCONNECTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Network/Connection.h"
#include "PLGeneral/Network/Buffer.h"
#include "PLGeneral/Network/Http/HttpHeader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class HttpServer;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Http server connection
*/
class HttpServerConnection : public Connection {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API HttpServerConnection(HttpServer &cServer);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API virtual ~HttpServerConnection();

		/**
		*  @brief
		*    Send a file to the client
		*
		*  @param[in] pConnection
		*    Connection
		*  @param[in] nStatus
		*    HTTP status code
		*  @param[in] sFilename
		*    Filename
		*/
		PLGENERAL_API void SendFile(EHttpStatus nStatus, const String &sFilename);

		/**
		*  @brief
		*    Send data to the client
		*
		*  @param[in] pConnection
		*    Connection
		*  @param[in] nStatus
		*    HTTP status code
		*  @param[in] sMimeType
		*    MIME type
		*  @param[in] sContent
		*    Data to send
		*/
		PLGENERAL_API void SendData(EHttpStatus nStatus, const String &sMimeType, const String &sContent);

		/**
		*  @brief
		*    Send a redirect
		*
		*  @param[in] pConnection
		*    Connection
		*  @param[in] sLocation
		*    New location
		*/
		PLGENERAL_API void SendRedirect(const String &sLocation);

		/**
		*  @brief
		*    Send an error
		*
		*  @param[in] pConnection
		*    Connection
		*  @param[in] nStatus
		*    HTTP status code
		*/
		PLGENERAL_API void SendError(EHttpStatus nStatus);

		/**
		*  @brief
		*    Send HTTP header
		*
		*  @param[in] pConnection
		*    Connection
		*  @param[in] nStatus
		*    HTTP status code
		*  @param[in] sMimeType
		*    MIME type
		*  @param[in] nLength
		*    Content length (0 for not sending the content-length at all)
		*/
		PLGENERAL_API void SendHeader(EHttpStatus nStatus, const String &sMimeType, uint32 nLength);


	//[-------------------------------------------------------]
	//[ Protected virtual HttpServerConnection functions      ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    A HTTP request has been received
		*
		*  @param[in] cHttpHeader
		*    HTTP header
		*/
		PLGENERAL_API virtual void OnHttpRequest(const HttpHeader &cHttpHeader);


	//[-------------------------------------------------------]
	//[ Protected virtual Connection functions                ]
	//[-------------------------------------------------------]
	protected:
		PLGENERAL_API virtual void OnConnect();
		PLGENERAL_API virtual void OnDisconnect();
		PLGENERAL_API virtual void OnReceive(const char *pBuffer, uint32 nSize);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		HttpServer	*m_pServer;		/**< HTTP server */
		Buffer		 m_cBuffer;		/**< Receive buffer */
		HttpHeader	 m_cHttpHeader;	/**< Received HTTP header */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_HTTPSERVERCONNECTION_H__
