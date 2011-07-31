/*********************************************************\
 *  File: HttpServerConnection.cpp                       *
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
#include "PLCore/File/File.h"
#include "PLCore/System/System.h"
#include "PLCore/Network/Http/HttpServer.h"
#include "PLCore/Network/Http/HttpServerConnection.h"
#include "PLCore/Network/Http/MimeTypeManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
HttpServerConnection::HttpServerConnection(HttpServer &cServer) : Connection(static_cast<Host&>(cServer)),
	m_pServer(&cServer)
{
}

/**
*  @brief
*    Destructor
*/
HttpServerConnection::~HttpServerConnection()
{
}

/**
*  @brief
*    Send a file to the client
*/
void HttpServerConnection::SendFile(EHttpStatus nStatus, const String &sFilename)
{
	// Open file
	File cFile(sFilename);
	if (cFile.Open(File::FileRead)) {
		// Send header
		SendHeader(nStatus, MimeTypeManager::GetMimeType(sFilename), cFile.GetSize());

		// Read in chunks of 256 bytes
		char szBuffer[256];
		while (!cFile.IsEof()) {
			// Read from file
			const uint32 nSize = cFile.Read(szBuffer, 1, 255);

			// Send
			if (nSize > 0)
				Send(szBuffer, nSize);
		}

		// Close file
		cFile.Close();

		// Close connection
		Disconnect();
	} else {
		// Error: File not found
		SendError(Http_404_NotFound);
	}
}

/**
*  @brief
*    Send data to the client
*/
void HttpServerConnection::SendData(EHttpStatus nStatus, const String &sMimeType, const String &sContent)
{
	// Send header
	SendHeader(nStatus, sMimeType, sContent.GetLength());

	// Send page
	Send(sContent);

	// Close connection
	Disconnect();
}

/**
*  @brief
*    Send a redirect
*/
void HttpServerConnection::SendRedirect(const String &sLocation)
{
	// HTTP protocol version and status
	Send("HTTP/1.1 " + Http::GetStatusString(Http_301_MovedPermanently) + "\r\n");

	// Date
	Send("Date: " + System::GetInstance()->GetTime().ToString() + "\r\n");

	// Redirect location
	Send("Location: " + sLocation + "\r\n");

	// Server identification
	Send("Server: PixelLight HTTP Server\r\n");

	// Connection type
	Send("Connection: close\r\n");

	// End header
	Send("\r\n");

	// Close
	Disconnect();
}

/**
*  @brief
*    Send an error
*/
void HttpServerConnection::SendError(EHttpStatus nStatus)
{
	// Status code must be 400 or higher
	if (nStatus > 400) {
		// Call virtual error function
		m_pServer->OnError(this, nStatus);
	} else {
		// Consider this as an internal server error
		SendError(Http_500_InternalServerError);
	}
}

/**
*  @brief
*    Send HTTP header
*/
void HttpServerConnection::SendHeader(EHttpStatus nStatus, const String &sMimeType, uint32 nLength)
{
	// HTTP protocol version and status
	Send("HTTP/1.1 " + Http::GetStatusString(nStatus) + "\r\n");

	// Date
	Send("Date: " + System::GetInstance()->GetTime().ToString() + "\r\n");

	// Content type
	if (sMimeType.GetLength())
		Send("Content-Type: " + sMimeType + "; charset=ISO-8859-1\r\n");

	// Content length
	if (nLength > 0)
		Send("Content-Length: " + String() + nLength + "\r\n");

	// Server identification
	Send("Server: PixelLight HTTP Server\r\n");

	// Connection type
	Send("Connection: close\r\n");

	// End header
	Send("\r\n");
}


//[-------------------------------------------------------]
//[ Protected virtual HttpConnection functions            ]
//[-------------------------------------------------------]
/**
*  @brief
*    A HTTP request has been received
*/
void HttpServerConnection::OnHttpRequest(const HttpHeader &cHttpHeader)
{
	// [DEBUG]
//	cHttpHeader.Print();

	// Perform HTTP request
	if (cHttpHeader.GetMessageType() == HttpRequest)
		m_pServer->OnRequest(this, &cHttpHeader);
}


//[-------------------------------------------------------]
//[ Protected virtual Connection functions                ]
//[-------------------------------------------------------]
void HttpServerConnection::OnConnect()
{
	// Initialize buffer
	m_cBuffer.SetRemoveLineDelimiters(false);
	m_cBuffer.Allocate(4096);

	// Initialize HTTP header
	m_cHttpHeader.Clear();
}

void HttpServerConnection::OnDisconnect()
{
	// Clear
	m_cBuffer.Clear();
	m_cHttpHeader.Clear();
}

void HttpServerConnection::OnReceive(const char *pBuffer, uint32 nSize)
{
	// Data recieved?
	if (pBuffer && !m_cHttpHeader.IsComplete()) {
		// Add data to buffer
		m_cBuffer.Add(pBuffer, nSize);

		// Read lines from buffer
		String sLine = m_cBuffer.GetLine();
		while (sLine.GetLength()) {
			// Add line to HTTP header
			m_cHttpHeader.AddEntry(sLine);
			if (m_cHttpHeader.IsComplete()) {
				// Parse header information
				m_cHttpHeader.Parse();

				// Process HTTP request
				OnHttpRequest(m_cHttpHeader);
			}

			// Next line
			sLine = m_cBuffer.GetLine();
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
