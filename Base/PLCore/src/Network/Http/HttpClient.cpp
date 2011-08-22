/*********************************************************\
 *  File: HttpClient.cpp                                 *
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
#include "PLCore/Tools/Tools.h"
#include "PLCore/String/ParseTools.h"
#include "PLCore/Network/Http/HttpClient.h"
#include "PLCore/Network/Http/HttpClientConnection.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ General                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
HttpClient::HttpClient() :
	m_nClientSignature(ClientPixelLight),
	m_nHttpProtocol(Http11),
	m_nConnection(ConnectionClose),
	m_nHttpAuth(NoAuth),
	m_nPort(80),
	m_pConnection(nullptr),
	m_nChunkSize(-1),
	m_nChunkLeft(0)
{
}

/**
*  @brief
*    Destructor
*/
HttpClient::~HttpClient()
{
	// Close connection
	Close();
}

//[-------------------------------------------------------]
//[ Options                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get client signature
*/
EClientSignature HttpClient::GetClientSignature() const
{
	// Return client signature
	return m_nClientSignature;
}

/**
*  @brief
*    Set client signature
*/
void HttpClient::SetClientSignature(EClientSignature nClientSignature)
{
	// Set client signature
	m_nClientSignature = nClientSignature;
}

/**
*  @brief
*    Get protocol version
*/
EHttpProtocol HttpClient::GetProtocol() const
{
	// Return protocol
	return m_nHttpProtocol;
}

/**
*  @brief
*    Set protocol version
*/
void HttpClient::SetProtocol(EHttpProtocol nProtocol)
{
	// Set protocol
	m_nHttpProtocol = nProtocol;
}

/**
*  @brief
*    Get connection type
*/
EHttpConnection HttpClient::GetConnectionType() const
{
	// Return connection type
	return m_nConnection;
}

/**
*  @brief
*    Set connection type
*/
void HttpClient::SetConnectionType(EHttpConnection nConnection)
{
	// Set connection type
	m_nConnection = nConnection;
}

/**
*  @brief
*    Get authentication
*/
EHttpAuth HttpClient::GetAuthentication() const
{
	// Return authentication
	return m_nHttpAuth;
}

/**
*  @brief
*    Set authentication
*/
void HttpClient::SetAuthentication(EHttpAuth nAuth, const String &sUsername, const String &sPassword)
{
	// Set authentication
	m_nHttpAuth = nAuth;

	// Set username and password
	m_sUsername = sUsername;
	m_sPassword = sPassword;
}

//[-------------------------------------------------------]
//[ Functions                                             ]
//[-------------------------------------------------------]
/**
*  @brief
*    Check if a connection is open
*/
bool HttpClient::IsConnected() const
{
	// Return if a connection is active
	return (m_pConnection != nullptr);
}

/**
*  @brief
*    Open connection to server
*/
bool HttpClient::Open(const String &sAddress, uint32 nPort)
{
	// Close former connection
	Disconnect();

	// Open connection
	m_pConnection = static_cast<HttpClientConnection*>(Connect(sAddress, nPort));
	if (m_pConnection) {
		// Save address
		m_sAddress = sAddress;
		m_nPort    = nPort;

		// Reset data
		m_cHttpHeader.Clear();

		// Connection established
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Close HTTP session
*/
void HttpClient::Disconnect()
{
	// Close connection
	if (m_pConnection) {
		m_pConnection->Disconnect();
		m_pConnection = nullptr;
		m_cHttpHeader.Clear();
	}
}

/**
*  @brief
*    Open a HTTP resource (GET command)
*/
bool HttpClient::Get(const String &sURL)
{
	// Is a connection open?
	if (IsConnected()) {
		// Reset
		m_cHttpHeader.Clear();

		// Send HTTP request
		if (m_nHttpProtocol == Http11)							m_pConnection->Send("GET " + sURL + " HTTP/1.1\r\n");
		else													m_pConnection->Send("GET " + sURL + " HTTP/1.0\r\n");

		// Host
		if (m_nPort != 80)										m_pConnection->Send("Host: " + m_sAddress + ':' + m_nPort + "\r\n");
		else													m_pConnection->Send("Host: " + m_sAddress + "\r\n");

		// User agent
		if (m_nClientSignature == ClientPixelLight)				m_pConnection->Send("User-Agent: PixelLight HTTP Client\r\n");
		else if (m_nClientSignature == ClientMozilla)			m_pConnection->Send("User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; de; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3\r\n");

		// Connection
		if (m_nConnection == ConnectionKeepAlive)				m_pConnection->Send("Connection: keep-alive\r\n");
		else													m_pConnection->Send("Connection: close\r\n");

		// Authentication
		if (m_nHttpAuth == BasicAuth)							m_pConnection->Send("Authorization: Basic " + Tools::GetBase64(m_sUsername + ':' + m_sPassword) + "\r\n");

		// Send Header
		m_pConnection->Send("\r\n");

		// Read answer
		m_cHttpHeader = m_pConnection->ReadHttpHeader();

		// Return if header is read successfully
		return m_cHttpHeader.IsComplete();
	}

	// Error!
	return false;
}

/**
*  @brief
*    Open a HTTP resource and get partial data (GET command)
*/
bool HttpClient::GetPartial(const String &sURL, uint32 nPos, int32 nSize)
{
	// Is a connection open and do we use HTTP 1.1? (Partial data is not supported by HTTP 1.0)
	if (IsConnected() && m_nHttpProtocol == Http11) {
		// Reset
		m_cHttpHeader.Clear();

		// Send HTTP request
		if (m_nHttpProtocol == Http11)							m_pConnection->Send("GET " + sURL + " HTTP/1.1\r\n");
		else													m_pConnection->Send("GET " + sURL + " HTTP/1.0\r\n");

		// Host
		if (m_nPort != 80)										m_pConnection->Send("Host: " + m_sAddress + ':' + m_nPort + "\r\n");
		else													m_pConnection->Send("Host: " + m_sAddress + "\r\n");

		// User agent
		if (m_nClientSignature == ClientPixelLight)				m_pConnection->Send("User-Agent: PixelLight HTTP Client\r\n");
		else if (m_nClientSignature == ClientMozilla)			m_pConnection->Send("User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; de; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3\r\n");

		// Connection
		if (m_nConnection == ConnectionKeepAlive)				m_pConnection->Send("Connection: keep-alive\r\n");
		else													m_pConnection->Send("Connection: close\r\n");

		// Authentication
		if (m_nHttpAuth == BasicAuth)							m_pConnection->Send("Authorization: Basic " + Tools::GetBase64(m_sUsername + ':' + m_sPassword) + "\r\n");

		// Get partial data
		String sPartial = String("Range: bytes=") + nPos + '-';
		if (nSize > 0)
			sPartial += nPos+nSize-1;
		sPartial += "\r\n";
		m_pConnection->Send(sPartial);

		// Send Header
		m_pConnection->Send("\r\n");

		// Read answer
		m_cHttpHeader = m_pConnection->ReadHttpHeader();

		// Return if header is read successfully
		return m_cHttpHeader.IsComplete();
	}

	// Error!
	return false;
}

/**
*  @brief
*    Open a HTTP resource (POST command)
*/
bool HttpClient::Post(const String &sURL, const String &sPostData)
{
	// Is a connection open?
	if (IsConnected()) {
		// Reset
		m_cHttpHeader.Clear();

		// Send HTTP request
		if (m_nHttpProtocol == Http11)							m_pConnection->Send("POST " + sURL + " HTTP/1.1\r\n");
		else													m_pConnection->Send("POST " + sURL + " HTTP/1.0\r\n");

		// Host
		if (m_nPort != 80)										m_pConnection->Send("Host: " + m_sAddress + ':' + m_nPort + "\r\n");
		else													m_pConnection->Send("Host: " + m_sAddress + "\r\n");

		// User agent
		if (m_nClientSignature == ClientPixelLight)				m_pConnection->Send("User-Agent: PixelLight HTTP Client\r\n");
		else if (m_nClientSignature == ClientMozilla)			m_pConnection->Send("User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; de; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3\r\n");

		// Connection
		if (m_nConnection == ConnectionKeepAlive)				m_pConnection->Send("Connection: keep-alive\r\n");
		else													m_pConnection->Send("Connection: close\r\n");

		// Authentication
		if (m_nHttpAuth == BasicAuth)							m_pConnection->Send("Authorization: Basic " + Tools::GetBase64(m_sUsername + ':' + m_sPassword) + "\r\n");

		// Send Header
		m_pConnection->Send("\r\n");

		// Send post data
		m_pConnection->Send(sPostData);

		// Read answer
		m_cHttpHeader = m_pConnection->ReadHttpHeader();

		// Return if header is read successfully
		return m_cHttpHeader.IsComplete();
	}

	// Error!
	return false;
}

/**
*  @brief
*    Delete a HTTP resource (DELETE command)
*/
bool HttpClient::Delete(const String &sURL)
{
	// Is a connection open?
	if (IsConnected()) {
		// Reset
		m_cHttpHeader.Clear();

		// Send HTTP request
		if (m_nHttpProtocol == Http11)							m_pConnection->Send("DELETE " + sURL + " HTTP/1.1\r\n");
		else													m_pConnection->Send("DELETE " + sURL + " HTTP/1.0\r\n");

		// Host
		if (m_nPort != 80)										m_pConnection->Send("Host: " + m_sAddress + ':' + m_nPort + "\r\n");
		else													m_pConnection->Send("Host: " + m_sAddress + "\r\n");

		// User agent
		if (m_nClientSignature == ClientPixelLight)				m_pConnection->Send("User-Agent: PixelLight HTTP Client\r\n");
		else if (m_nClientSignature == ClientMozilla)			m_pConnection->Send("User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; de; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3\r\n");

		// Connection
		if (m_nConnection == ConnectionKeepAlive)				m_pConnection->Send("Connection: keep-alive\r\n");
		else													m_pConnection->Send("Connection: close\r\n");

		// Authentication
		if (m_nHttpAuth == BasicAuth)							m_pConnection->Send("Authorization: Basic " + Tools::GetBase64(m_sUsername + ':' + m_sPassword) + "\r\n");

		// Send Header
		m_pConnection->Send("\r\n");

		// Read answer
		m_cHttpHeader = m_pConnection->ReadHttpHeader();

		// Return if header is read successfully
		return m_cHttpHeader.IsComplete();
	}

	// Error!
	return false;
}

/**
*  @brief
*    Get HTTP header sent from server
*/
const HttpHeader &HttpClient::GetHeader() const
{
	// Return header
	return m_cHttpHeader;
}

/**
*  @brief
*    Read data from HTTP connection
*/
int HttpClient::Read(char *pBuffer, uint32 nSize)
{
	// Check for chunked transfer
	if (m_cHttpHeader.IsChunked()) {
		// Transfer is chunked. Read header if not already done
		if (m_nChunkSize == -1) {
			// Read chunk header
			String sHeader = m_pConnection->ReadLine().RemoveLineEndings();
			const int nSpace = sHeader.IndexOf(' ');
			if (nSpace > -1)
				sHeader = sHeader.GetSubstring(0, nSpace);

			// Set chunk data
			m_nChunkSize = ParseTools::ParseHexValue(sHeader);
			m_nChunkLeft = m_nChunkSize;
		}

		// Check maximum size that can be read
		int nRead = nSize;
		if (nRead > m_nChunkLeft)
			nRead = m_nChunkLeft;

		// Read data
		const int nResult = m_pConnection->Receive(pBuffer, nRead);
		if (nResult > -1)
			m_nChunkLeft -= nResult;

		// Read end of chunk
		if (m_nChunkLeft <= 0) {
			// Read CRLF
			m_pConnection->ReadLine();

			// Reset chunk data
			m_nChunkSize = -1;
			m_nChunkLeft =  0;
		}

		// Return number of bytes read
		return nResult;
	} else {
		// Not chunked. Read directly from HTTP connection
		return m_pConnection->Receive(pBuffer, nSize);
	}
}


//[-------------------------------------------------------]
//[ Protected virtual Client functions                    ]
//[-------------------------------------------------------]
Connection *HttpClient::CreateOutgoingConnection()
{
	// Create web server connection
	HttpClientConnection *pConnection = new HttpClientConnection(*this);

	// We want to read manually, please (content could be huge, so read step by step)
	pConnection->SetReceiveMode(Connection::ReceiveManual);

	// Return connection
	return pConnection;
}

void HttpClient::OnDisconnect(Connection &cConnection)
{
	// Reset connection
	m_pConnection = nullptr;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
HttpClient::HttpClient(const HttpClient &cClient)
{
	// No implementation because the copy operator is never used
}

/**
*  @brief
*    Copy operator
*/
HttpClient &HttpClient::operator =(const HttpClient &cClient)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
