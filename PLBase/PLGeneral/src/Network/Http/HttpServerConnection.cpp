/*********************************************************\
 *  File: HttpServerConnection.cpp                       *
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
#include "PLGeneral/Network/Http/HttpServer.h"
#include "PLGeneral/Network/Http/HttpServerConnection.h"


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
HttpServerConnection::HttpServerConnection(HttpServer &cServer) : Connection((Host&)cServer),
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
	if (cHttpHeader.GetMessageType() == HttpRequest) {
		m_pServer->OnRequest(this, &cHttpHeader);
	}
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
} // PLGeneral
