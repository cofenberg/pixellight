/*********************************************************\
 *  File: HttpServer.cpp                                 *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/System/System.h"
#include "PLGeneral/File/File.h"
#include "PLGeneral/Network/Http/MimeTypeManager.h"
#include "PLGeneral/Network/Http/HttpServerConnection.h"
#include "PLGeneral/Network/Http/HttpServer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
HttpServer::HttpServer()
{
}

/**
*  @brief
*    Destructor
*/
HttpServer::~HttpServer()
{
}


//[-------------------------------------------------------]
//[ Protected virtual HttpServer functions                ]
//[-------------------------------------------------------]
/**
*  @brief
*    A webserver request has come in
*/
void HttpServer::OnRequest(HttpServerConnection *pConnection, const HttpHeader *pHeader)
{
	// Get request type
	switch (pHeader->GetRequest()) {
		// GET
		case HttpGet:
			OnGet(pConnection, pHeader);
			break;

		// Not implemented functions
		case HttpPost:
		case HttpHead:
		case HttpPut:
		case HttpDelete:
		case HttpTrace:
		case HttpOptions:
		case HttpConnect:
			pConnection->SendError(Http_501_NotImplemented);
			break;
	}
}

/**
*  @brief
*    A GET request has come in
*/
void HttpServer::OnGet(HttpServerConnection *pConnection, const HttpHeader *pHeader)
{
	// Get what?
	const String sUrl = pHeader->GetRequestUrl();

	// Send page
	if (sUrl == "/") {
		// Create a default page
		const String sPage = "<html><head><title>PixelLight Webserver</title></head><body><h1>Welcome</h1>Welcome to PixelLight webserver</body></html>";

		// Send default page
		pConnection->SendData(Http_200_OK, "text/html", sPage);
	} else {
		// Send file not found
		pConnection->SendError(Http_404_NotFound);
	}
}

/**
*  @brief
*    An error occured
*/
void HttpServer::OnError(HttpServerConnection *pConnection, EHttpStatus nStatus)
{
	// Get error code
	const String sError = Http::GetStatusString(nStatus);

	// Create a dynamic page containing the error code
	const String sPage = "<html><head><title>" + sError + "</title></head><body><h1>" + sError + "</h1></body></html>";

	// Send error page
	pConnection->SendData(nStatus, "text/html", sPage);
}


//[-------------------------------------------------------]
//[ Protected virtual Server functions                    ]
//[-------------------------------------------------------]
Connection *HttpServer::CreateIncomingConnection()
{
	// Create webserver connection
	return new HttpServerConnection(*this);
}

void HttpServer::OnConnect(Connection &cConnection)
{
}

void HttpServer::OnDisconnect(Connection &cConnection)
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
HttpServer::HttpServer(const HttpServer &cMessage)
{
	// No implementation because the copy operator is never used
}

/**
*  @brief
*    Copy operator
*/
HttpServer &HttpServer::operator =(const HttpServer &cServer)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
