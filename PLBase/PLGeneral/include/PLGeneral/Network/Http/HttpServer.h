/*********************************************************\
 *  File: HttpServer.h                                   *
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


#ifndef __PLGENERAL_HTTPSERVER_H__
#define __PLGENERAL_HTTPSERVER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Network/Server.h"
#include "PLGeneral/Network/Http/Http.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class HttpHeader;
class HttpServerConnection;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Http server
*/
class HttpServer : public Server {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class HttpServerConnection;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API HttpServer();

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API virtual ~HttpServer();


	//[-------------------------------------------------------]
	//[ Protected virtual HttpServer functions                ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    A webserver request has come in
		*
		*  @param[in] pConnection
		*    Connection
		*  @param[in] pHeader
		*    HTTP header
		*/
		PLGENERAL_API virtual void OnRequest(HttpServerConnection *pConnection, const HttpHeader *pHeader);

		/**
		*  @brief
		*    A GET request has come in
		*
		*  @param[in] pConnection
		*    Connection
		*  @param[in] pHeader
		*    HTTP header
		*/
		PLGENERAL_API virtual void OnGet(HttpServerConnection *pConnection, const HttpHeader *pHeader);

		/**
		*  @brief
		*    An error occured
		*
		*  @param[in] pConnection
		*    Connection
		*  @param[in] nStatus
		*    HTTP status code
		*/
		PLGENERAL_API virtual void OnError(HttpServerConnection *pConnection, EHttpStatus nStatus);


	//[-------------------------------------------------------]
	//[ Protected virtual Server functions                    ]
	//[-------------------------------------------------------]
	protected:
		PLGENERAL_API virtual Connection *CreateIncomingConnection();
		PLGENERAL_API virtual void OnConnect(Connection &cConnection);
		PLGENERAL_API virtual void OnDisconnect(Connection &cConnection);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cServer
		*    HTTP server
		*/
		HttpServer(const HttpServer &cServer);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cHttpServer
		*    HTTP server
		*
		*  @return
		*    Reference to this server
		*/
		HttpServer &operator =(const HttpServer &cServer);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_HTTPSERVER_H__
