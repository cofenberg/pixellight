/*********************************************************\
 *  File: HttpClientConnection.cpp                       *
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
#include "PLGeneral/Network/Http/HttpClientConnection.h"


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
HttpClientConnection::HttpClientConnection(Host &cHost) : Connection(cHost)
{
}

/**
*  @brief
*    Destructor
*/
HttpClientConnection::~HttpClientConnection()
{
}

/**
*  @brief
*    Read HTTP header
*/
const HttpHeader &HttpClientConnection::ReadHttpHeader()
{
	// Reset header
	m_cHttpHeader.Clear();

	// Read until header is complete
	while (IsConnected() && !m_cHttpHeader.IsComplete()) {
		// Disconnect on read error
		if (ReadLine() == "") Disconnect();
	}

	// Return header
	return m_cHttpHeader;
}


//[-------------------------------------------------------]
//[ Protected virtual Connection functions                ]
//[-------------------------------------------------------]
void HttpClientConnection::OnConnect()
{
	// Initialize buffer
	m_cBuffer.SetRemoveLineDelimiters(false);
	m_cBuffer.Allocate(4096);

	// Initialize HTTP message
	m_cHttpHeader.Clear();
}

void HttpClientConnection::OnDisconnect()
{
	// Clear
	m_cBuffer.Clear();
	m_cHttpHeader.Clear();
}

void HttpClientConnection::OnReceive(const char *pBuffer, uint32 nSize)
{
	// Data recieved?
	if (pBuffer && !m_cHttpHeader.IsComplete()) {
		// Add data to buffer
		m_cBuffer.Add(pBuffer, nSize);

		// Read lines from buffer
		String sLine = m_cBuffer.GetLine();
		while (sLine.GetLength()) {
			// Add line to HTTP message
			m_cHttpHeader.AddEntry(sLine);
			if (m_cHttpHeader.IsComplete()) {
				// Parse header information
				m_cHttpHeader.Parse();
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
