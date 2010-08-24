/*********************************************************\
 *  File: HttpServer.cpp                                 *
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
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Send a file to the client
*/
void HttpServer::SendFile(HttpServerConnection *pConnection, EHttpStatus nStatus, const String &sFilename)
{
	// Open file
	File cFile(sFilename);
	if (cFile.Open(File::FileRead)) {
		// Send header
		SendHeader(pConnection, nStatus, MimeTypeManager::GetMimeType(sFilename), cFile.GetSize());

		// Read in chunks of 256 bytes
		char szBuffer[256];
		while (!cFile.IsEof()) {
			// Read from file
			uint32 nSize = cFile.Read(szBuffer, 1, 255);

			// Send
			if (nSize > 0) pConnection->Send(szBuffer, nSize);
		}

		// Close file
		cFile.Close();

		// Close connection
		pConnection->Disconnect();
	} else {
		// Error: File not found
		SendError(pConnection, Http_404_NotFound);
	}
}

/**
*  @brief
*    Send data to the client
*/
void HttpServer::Send(HttpServerConnection *pConnection, EHttpStatus nStatus, const String &sMimeType, const String &sContent)
{
	// Send header
	SendHeader(pConnection, nStatus, sMimeType, sContent.GetLength());

	// Send page
	pConnection->Send(sContent);

	// Close connection
	pConnection->Disconnect();
}

/**
*  @brief
*    Send a redirect
*/
void HttpServer::SendRedirect(HttpServerConnection *pConnection, const String &sLocation)
{
	// HTTP protocol version and status
	pConnection->Send("HTTP/1.1 " + Http::GetStatusString(Http_301_MovedPermanently) + "\r\n");

	// Date
	pConnection->Send("Date: " + System::GetInstance()->GetTime().ToString() + "\r\n");

	// Redirect location
	pConnection->Send("Location: " + sLocation + "\r\n");

	// Server identification
	pConnection->Send("Server: PixelLight HTTP Server\r\n");

	// Connection type
	pConnection->Send("Connection: close\r\n");

	// End header
	pConnection->Send("\r\n");

	// Close
	pConnection->Disconnect();
}

/**
*  @brief
*    Send an error
*/
void HttpServer::SendError(HttpServerConnection *pConnection, EHttpStatus nStatus)
{
	// Status code must be 400 or higher
	if (nStatus > 400) {
		// Call virtual error function
		OnError(pConnection, nStatus);
	} else {
		// Consider this as an internal server error
		SendError(pConnection, Http_500_InternalServerError);
	}
}

/**
*  @brief
*    Send HTTP header
*/
void HttpServer::SendHeader(HttpServerConnection *pConnection, EHttpStatus nStatus, const String &sMimeType, uint32 nLength)
{
	// HTTP protocol version and status
	pConnection->Send("HTTP/1.1 " + Http::GetStatusString(nStatus) + "\r\n");

	// Date
	pConnection->Send("Date: " + System::GetInstance()->GetTime().ToString() + "\r\n");

	// Content type
	if (sMimeType != "") {
		pConnection->Send("Content-Type: " + sMimeType + "; charset=ISO-8859-1\r\n");
	}

	// Content length
	if (nLength > 0) {
		pConnection->Send("Content-Length: " + String() + (int)nLength + "\r\n");
	}

	// Server identification
	pConnection->Send("Server: PixelLight HTTP Server\r\n");

	// Connection type
	pConnection->Send("Connection: close\r\n");

	// End header
	pConnection->Send("\r\n");
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
			SendError(pConnection, Http_501_NotImplemented);
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
	String sUrl = pHeader->GetRequestUrl();

	// Send page
	if (sUrl == "/") {
		// Create a default page
		String sPage = "<html><head><title>PixelLight Webserver</title></head><body><h1>Welcome</h1>Welcome to PixelLight webserver</body></html>";

		// Send default page
		Send(pConnection, Http_200_OK, "text/html", sPage);
	} else {
		// Send file not found
		SendError(pConnection, Http_404_NotFound);
	}
}

/**
*  @brief
*    An error occured
*/
void HttpServer::OnError(HttpServerConnection *pConnection, EHttpStatus nStatus)
{
	// Get error code
	String sError = Http::GetStatusString(nStatus);

	// Create a dynamic page containing the error code
	String sPage = "<html><head><title>" + sError + "</title></head><body><h1>" + sError + "</h1></body></html>";

	// Send error page
	Send(pConnection, nStatus, "text/html", sPage);
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
