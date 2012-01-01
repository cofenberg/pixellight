/*********************************************************\
 *  File: HttpHeader.inl                                 *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
/**
*  @brief
*    Destructor
*/
inline HttpHeader::~HttpHeader()
{
}

/**
*  @brief
*    Get header entries
*/
inline const Container<String> &HttpHeader::GetEntries() const
{
	// Return entries
	return m_lstEntries;
}

/**
*  @brief
*    Add header entry
*/
inline void HttpHeader::AddEntry(const String &sEntry)
{
	// Add header entry to list
	String sLine = sEntry;
	sLine.RemoveLineEndings();
	m_lstEntries.Add(sLine);
}

/**
*  @brief
*    Get protocol version
*/
inline EHttpProtocol HttpHeader::GetProtocol() const
{
	// Return protocol version
	return m_nProtocol;
}

/**
*  @brief
*    Get message type
*/
inline EHttpMessageType HttpHeader::GetMessageType() const
{
	// Return message type
	return m_nMessageType;
}

/**
*  @brief
*    Get request
*/
inline EHttpRequest HttpHeader::GetRequest() const
{
	// Return HTTP request
	return m_nRequest;
}

/**
*  @brief
*    Get request URL
*/
inline String HttpHeader::GetRequestUrl() const
{
	// Return request URL
	return m_sRequestUrl;
}

/**
*  @brief
*    Get connection type
*/
inline EHttpConnection HttpHeader::GetConnectionType() const
{
	// Return connection type
	return m_nConnection;
}

/**
*  @brief
*    Get status code
*/
inline uint32 HttpHeader::GetStatusCode() const
{
	// Return status code
	return m_nStatusCode;
}

/**
*  @brief
*    Get status string
*/
inline String HttpHeader::GetStatusString() const
{
	// Return status string
	return m_sStatusString;
}

/**
*  @brief
*    Get location
*/
inline String HttpHeader::GetLocation() const
{
	// Return location
	return m_sLocation;
}

/**
*  @brief
*    Get date
*/
inline String HttpHeader::GetDate() const
{
	// Return date
	return m_sDate;
}

/**
*  @brief
*    Get server signature
*/
inline String HttpHeader::GetServer() const
{
	// Return server signature
	return m_sServer;
}

/**
*  @brief
*    Get client signature
*/
inline String HttpHeader::GetUserAgent() const
{
	// Return client signature
	return m_sUserAgent;
}

/**
*  @brief
*    Get authentication type
*/
inline EHttpAuth HttpHeader::GetAuthenticationType() const
{
	// Return authentication type
	return m_nAuthType;
}

/**
*  @brief
*    Get authentication realm
*/
inline String HttpHeader::GetAuthenticationRealm() const
{
	// Return authentication realm
	return m_sAuthRealm;
}

/**
*  @brief
*    Get authorization string
*/
inline String HttpHeader::GetAuthorization() const
{
	// Return authorization string
	return m_sAuthorization;
}

/**
*  @brief
*    Get transfer encoding
*/
inline String HttpHeader::GetTransferEncoding() const
{
	// Return transfer encoding
	return m_sTransferEncoding;
}

/**
*  @brief
*    Check if data is transfered "chunked"
*/
inline bool HttpHeader::IsChunked() const
{
	// Return if transfer encoding is set to "chunked"
	return m_sTransferEncoding.IsSubstring("chunked");
}

/**
*  @brief
*    Get content length
*/
inline uint32 HttpHeader::GetContentLength() const
{
	// Return content length
	return m_nContentLength;
}

/**
*  @brief
*    Get content language
*/
inline String HttpHeader::GetContentLanguage() const
{
	// Return content language
	return m_sContentLanguage;
}

/**
*  @brief
*    Get content type
*/
inline String HttpHeader::GetContentType() const
{
	// Return content type
	return m_sContentType;
}

/**
*  @brief
*    Get ETag
*/
inline String HttpHeader::GetETag() const
{
	// Return ETag
	return m_sETag;
}

/**
*  @brief
*    Check if partial data is returned
*/
inline bool HttpHeader::IsPartial() const
{
	// Return if partial data is received
	return m_bPartial;
}

/**
*  @brief
*    Get start of range
*/
inline uint32 HttpHeader::GetRangeMin() const
{
	// Return start of range
	return m_nRangeMin;
}

/**
*  @brief
*    Get end of range
*/
inline uint32 HttpHeader::GetRangeMax() const
{
	// Return end of range
	return m_nRangeMax;
}

/**
*  @brief
*    Get total size
*/
inline uint32 HttpHeader::GetRangeTotal() const
{
	// Return total size
	return m_nRangeTotal;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
