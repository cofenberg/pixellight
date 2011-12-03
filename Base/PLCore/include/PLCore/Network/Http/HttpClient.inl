/*********************************************************\
 *  File: HttpClient.inl                                 *
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Options                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get client signature
*/
inline EClientSignature HttpClient::GetClientSignature() const
{
	// Return client signature
	return m_nClientSignature;
}

/**
*  @brief
*    Set client signature
*/
inline void HttpClient::SetClientSignature(EClientSignature nClientSignature)
{
	// Set client signature
	m_nClientSignature = nClientSignature;
}

/**
*  @brief
*    Get protocol version
*/
inline EHttpProtocol HttpClient::GetProtocol() const
{
	// Return protocol
	return m_nHttpProtocol;
}

/**
*  @brief
*    Set protocol version
*/
inline void HttpClient::SetProtocol(EHttpProtocol nProtocol)
{
	// Set protocol
	m_nHttpProtocol = nProtocol;
}

/**
*  @brief
*    Get connection type
*/
inline EHttpConnection HttpClient::GetConnectionType() const
{
	// Return connection type
	return m_nConnection;
}

/**
*  @brief
*    Set connection type
*/
inline void HttpClient::SetConnectionType(EHttpConnection nConnection)
{
	// Set connection type
	m_nConnection = nConnection;
}

/**
*  @brief
*    Get authentication
*/
inline EHttpAuth HttpClient::GetAuthentication() const
{
	// Return authentication
	return m_nHttpAuth;
}

/**
*  @brief
*    Set authentication
*/
inline void HttpClient::SetAuthentication(EHttpAuth nAuth, const String &sUsername, const String &sPassword)
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
inline bool HttpClient::IsConnected() const
{
	// Return if a connection is active
	return (m_pConnection != nullptr);
}

/**
*  @brief
*    Get HTTP header sent from server
*/
inline const HttpHeader &HttpClient::GetHeader() const
{
	// Return header
	return m_cHttpHeader;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
