/*********************************************************\
 *  File: HttpHeader.cpp                                 *
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
#include "PLGeneral/System/Console.h"
#include "PLGeneral/Network/Http/HttpHeader.h"


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
HttpHeader::HttpHeader() :
	m_nProtocol(Http11),
	m_nMessageType(HttpRequest),
	m_nRequest(HttpGet),
	m_nConnection(ConnectionClose),
	m_nStatusCode(Http_000_Unknown),
	m_nAuthType(NoAuth),
	m_nContentLength(0),
	m_bPartial(false),
	m_nRangeMin(0),
	m_nRangeMax(0),
	m_nRangeTotal(0)
{
}

/**
*  @brief
*    Copy constructor
*/
HttpHeader::HttpHeader(const HttpHeader &cSource) :
	m_lstEntries(cSource.m_lstEntries),
	m_nProtocol(cSource.m_nProtocol),
	m_nMessageType(cSource.m_nMessageType),
	m_nRequest(cSource.m_nRequest),
	m_sRequestUrl(cSource.m_sRequestUrl),
	m_nConnection(cSource.m_nConnection),
	m_nStatusCode(cSource.m_nStatusCode),
	m_sStatusString(cSource.m_sStatusString),
	m_sLocation(cSource.m_sLocation),
	m_sDate(cSource.m_sDate),
	m_sServer(cSource.m_sServer),
	m_sUserAgent(cSource.m_sUserAgent),
	m_nAuthType(cSource.m_nAuthType),
	m_sAuthRealm(cSource.m_sAuthRealm),
	m_sAuthorization(cSource.m_sAuthorization),
	m_sTransferEncoding(cSource.m_sTransferEncoding),
	m_nContentLength(cSource.m_nContentLength),
	m_sContentLanguage(cSource.m_sContentLanguage),
	m_sContentType(cSource.m_sContentType),
	m_sETag(cSource.m_sETag),
	m_bPartial(cSource.m_bPartial),
	m_nRangeMin(cSource.m_nRangeMin),
	m_nRangeMax(cSource.m_nRangeMax),
	m_nRangeTotal(cSource.m_nRangeTotal)
{
}

/**
*  @brief
*    Destructor
*/
HttpHeader::~HttpHeader()
{
}

/**
*  @brief
*    Assignment operator
*/
HttpHeader &HttpHeader::operator =(const HttpHeader &cSource)
{
	// Copy header
	m_lstEntries		= cSource.m_lstEntries;
	m_nProtocol			= cSource.m_nProtocol;
	m_nMessageType		= cSource.m_nMessageType;
	m_nRequest			= cSource.m_nRequest;
	m_sRequestUrl		= cSource.m_sRequestUrl;
	m_nConnection		= cSource.m_nConnection;
	m_nStatusCode		= cSource.m_nStatusCode;
	m_sStatusString		= cSource.m_sStatusString;
	m_sLocation			= cSource.m_sLocation;
	m_sDate				= cSource.m_sDate;
	m_sServer			= cSource.m_sServer;
	m_sUserAgent		= cSource.m_sUserAgent;
	m_nAuthType			= cSource.m_nAuthType;
	m_sAuthRealm		= cSource.m_sAuthRealm;
	m_sAuthorization	= cSource.m_sAuthorization;
	m_sTransferEncoding = cSource.m_sTransferEncoding;
	m_nContentLength	= cSource.m_nContentLength;
	m_sContentLanguage	= cSource.m_sContentLanguage;
	m_sContentType		= cSource.m_sContentType;
	m_sETag				= cSource.m_sETag;
	m_bPartial			= cSource.m_bPartial;
	m_nRangeMin			= cSource.m_nRangeMin;
	m_nRangeMax			= cSource.m_nRangeMax;
	m_nRangeTotal		= cSource.m_nRangeTotal;

	// Return reference to header
	return *this;
}

/**
*  @brief
*    Clear header
*/
void HttpHeader::Clear()
{
	// Reset data
	m_lstEntries.Clear();
	m_nProtocol			= Http11;
	m_nMessageType		= HttpRequest;
	m_nRequest			= HttpGet;
	m_sRequestUrl		= "";
	m_nConnection		= ConnectionClose;
	m_nStatusCode		= Http_000_Unknown;
	m_sStatusString		= "";
	m_sLocation			= "";
	m_sDate				= "";
	m_sServer			= "";
	m_sUserAgent		= "";
	m_nAuthType			= NoAuth;
	m_sAuthRealm		= "";
	m_sAuthorization	= "";
	m_sTransferEncoding = "";
	m_nContentLength	= 0;
	m_sContentLanguage	= "";
	m_sContentType		= "";
	m_sETag				= "";
	m_bPartial			= false;
	m_nRangeMin			= 0;
	m_nRangeMax			= 0;
	m_nRangeTotal		= 0;
}

/**
*  @brief
*    Check if HTTP header is complete
*/
bool HttpHeader::IsComplete() const
{
	// Is there at least one header line?
	if (m_lstEntries.GetNumOfElements() > 0) {
		// Get last line
		const String sLine = m_lstEntries.Get(m_lstEntries.GetNumOfElements()-1);

		// Check if this line is the separator
		if (sLine == "") {
			// Header is complete
			return true;
		}
	}

	// Header is not complete yet
	return false;
}

/**
*  @brief
*    Get header entries
*/
const Container<String> &HttpHeader::GetEntries() const
{
	// Return entries
	return m_lstEntries;
}

/**
*  @brief
*    Add header entry
*/
void HttpHeader::AddEntry(const String &sEntry)
{
	// Add header entry to list
	String sLine = sEntry;
	sLine.RemoveLineEndings();
	m_lstEntries.Add(sLine);
}

/**
*  @brief
*    Parse header
*/
void HttpHeader::Parse()
{
	// Loop through header entries
	for (uint32 i=0; i<m_lstEntries.GetNumOfElements(); i++) {
		// Get line
		const String sLine = m_lstEntries.Get(i);

		// HTTP request
		if (sLine.IndexOf("HTTP/") > 0) {
			// HTTP request
			m_nMessageType = HttpRequest;

			// Get string parts
			const int nSpace1 = sLine.IndexOf(" ");
			const int nSpace2 = sLine.IndexOf(" ", nSpace1+1);
			if (nSpace1 > 0 || nSpace2 > nSpace2) {
				// Get request arguments
				const String sRequest  = sLine.GetSubstring(0, nSpace1);
				const String sUrl		 = sLine.GetSubstring(nSpace1+1, nSpace2-nSpace1-1);
				const String sProtocol = sLine.GetSubstring(nSpace2+1);

				// Request
					 if (sRequest == "GET")		m_nRequest = HttpGet;
				else if (sRequest == "POST")	m_nRequest = HttpPost;
				else if (sRequest == "HEAD")	m_nRequest = HttpHead;
				else if (sRequest == "PUT")		m_nRequest = HttpPut;
				else if (sRequest == "DELETE")	m_nRequest = HttpDelete;
				else if (sRequest == "TRACE")	m_nRequest = HttpTrace;
				else if (sRequest == "OPTIONS")	m_nRequest = HttpOptions;
				else if (sRequest == "CONNECT")	m_nRequest = HttpConnect;

				// URL
				m_sRequestUrl = sUrl;

				// Protocol version
				if (sProtocol == "HTTP/1.1")
					m_nProtocol = Http11;
				else
					m_nProtocol = Http10;
			}
		}

		// HTTP response
		if (sLine.GetSubstring(0, 4) == "HTTP") {
			// HTTP response
			m_nMessageType = HttpResponse;

			// Protocol version
			if (sLine.GetSubstring(0, 8) == "HTTP/1.1")
				m_nProtocol = Http11;
			else
				m_nProtocol = Http10;

			// Status code
			m_nStatusCode = (EHttpStatus)sLine.GetSubstring(9, 3).GetInt();

			// Status string
			m_sStatusString = sLine.GetSubstring(13);
		}

		// Connection type
		if (sLine.GetSubstring(0, 11) == "Connection:") {
			const String sConnection = sLine.GetSubstring(12);
			if (sConnection == "close")
				m_nConnection = ConnectionClose;
			else
				m_nConnection = ConnectionKeepAlive;
		}

		// Location
		if (sLine.GetSubstring(0, 9) == "Location:")
			m_sLocation = sLine.GetSubstring(10);

		// Date
		if (sLine.GetSubstring(0, 5) == "Date:")
			m_sDate = sLine.GetSubstring(6);

		// Server signature
		if (sLine.GetSubstring(0, 7) == "Server:")
			m_sServer = sLine.GetSubstring(8);

		// Client signature
		if (sLine.GetSubstring(0, 11) == "User-Agent:")
			m_sUserAgent = sLine.GetSubstring(12);

		// Authentication
		if (sLine.GetSubstring(0, 17) == "WWW-Authenticate:") {
			const String sAuth = sLine.GetSubstring(18);
			if (sAuth.GetSubstring(0, 5) == "Basic") {
				m_nAuthType = BasicAuth;
				const int nFirst = sAuth.IndexOf("\"");
				const int nLast  = sAuth.LastIndexOf("\"");
				if (nFirst > -1 && nLast > -1)
					m_sAuthRealm = sAuth.GetSubstring(nFirst+1, nLast-nFirst-1);
				else
					m_sAuthRealm = "";
			} else {
				m_nAuthType  = NoAuth;
				m_sAuthRealm = "";
			}
		}

		// Authorization
		if (sLine.GetSubstring(0, 14) == "Authorization:") {
			const String sAuth = sLine.GetSubstring(15);
			if (sAuth.GetSubstring(0, 5) == "Basic") {
				m_nAuthType		 = BasicAuth;
				m_sAuthorization = sAuth.GetSubstring(6);
			} else {
				m_nAuthType		 = NoAuth;
				m_sAuthorization = "";
			}
		}

		// Transfer-Encoding
		if (sLine.GetSubstring(0, 18) == "Transfer-Encoding:")
			m_sTransferEncoding = sLine.GetSubstring(19);

		// Content length
		if (sLine.GetSubstring(0, 15) == "Content-Length:")
			m_nContentLength = (uint32)sLine.GetSubstring(16).GetInt();

		// Content language
		if (sLine.GetSubstring(0, 17) == "Content-Language:")
			m_sContentLanguage = sLine.GetSubstring(18);

		// Content type
		if (sLine.GetSubstring(0, 13) == "Content-Type:")
			m_sContentType = sLine.GetSubstring(14);

		// Content range
		if (sLine.GetSubstring(0, 14) == "Content-Range:") {
			// Reset partial
			m_bPartial	= false;

			// Get range unit
			const String sByte = sLine.GetSubstring(15, 5);
			if (sByte == "bytes") {
				// Get range (e.g. "21010-47021/47022")
				const String sRange = sLine.GetSubstring(21);
				const int nPosMinus = sRange.IndexOf("-");
				const int nPosSlash = sRange.IndexOf("/");
				if (nPosMinus > -1 && nPosSlash > -1) {
					// Get parts
					const String sRangeMin   = sRange.GetSubstring(0, nPosMinus);
					const String sRangeMax   = sRange.GetSubstring(nPosMinus+1, nPosSlash-nPosMinus-1);
					const String sRangeTotal = sRange.GetSubstring(nPosSlash+1);

					// Set range
					m_bPartial	  = true;
					m_nRangeMin   = sRangeMin.  GetInt();
					m_nRangeMax   = sRangeMax.  GetInt();
					m_nRangeTotal = sRangeTotal.GetInt();
				}
			}
		}

		// ETag
		if (sLine.GetSubstring(0, 5) == "ETag:") {
			const String sETag = sLine.GetSubstring(6);
			m_sETag = sETag.GetSubstring(1, sETag.GetLength()-2);
		}
	}
}

/**
*  @brief
*    Print header entries to console
*/
void HttpHeader::Print(bool bRaw) const
{
	// Print mode?
	if (bRaw) {
		// Raw printout of all header lines
		System::GetInstance()->GetConsole().Print("HTTP message arrived:\n");
		for (uint32 i=0; i<GetEntries().GetNumOfElements()-1; i++)
			System::GetInstance()->GetConsole().Print("- " + GetEntries().Get(i) + "\n");
		System::GetInstance()->GetConsole().Print("\n");
	} else {
		// Print out all header information that we have parsed and understood
		System::GetInstance()->GetConsole().Print("HTTP message arrived:\n");
		System::GetInstance()->GetConsole().Print("- Protocol:          " + String() + (GetProtocol() == Http11 ? "HTTP 1.1\n" : "HTTP 1.0\n"));
		System::GetInstance()->GetConsole().Print("- Message:           " + String() + (GetMessageType() == HttpRequest ? "REQUEST\n" : "RESPONSE\n"));
		System::GetInstance()->GetConsole().Print("- Request-Type       " + GetRequestString() + "\n");
		System::GetInstance()->GetConsole().Print("- Request-URL        " + GetRequestUrl() + "\n");
		System::GetInstance()->GetConsole().Print("- Connection:        " + String() + (GetConnectionType() == ConnectionKeepAlive ? "Keep Alive\n" : "Close\n"));
		System::GetInstance()->GetConsole().Print("- Status-Code:       " + String() + (int)GetStatusCode() + "\n");
		System::GetInstance()->GetConsole().Print("- Status:            " + GetStatusString() + "\n");
		System::GetInstance()->GetConsole().Print("- Location:          " + GetLocation() + "\n");
		System::GetInstance()->GetConsole().Print("- Date:              " + GetDate() + "\n");
		System::GetInstance()->GetConsole().Print("- Server:            " + GetServer() + "\n");
		System::GetInstance()->GetConsole().Print("- Client:            " + GetUserAgent() + "\n");
		System::GetInstance()->GetConsole().Print("- Authentication:    " + String() + (GetAuthenticationType() == BasicAuth ? "Basic\n" : "No Authentication\n"));
		System::GetInstance()->GetConsole().Print("- Realm:             " + GetAuthenticationRealm() + "\n");
		System::GetInstance()->GetConsole().Print("- Authorization:     " + GetAuthorization() + "\n");
		System::GetInstance()->GetConsole().Print("- Transfer-Encoding: " + GetTransferEncoding() + "\n");
		System::GetInstance()->GetConsole().Print("- Chunked:           " + String() + (IsChunked() ? "Yes\n" : "No\n"));
		System::GetInstance()->GetConsole().Print("- Content-Length:    " + String() + (int)GetContentLength() + "\n");
		System::GetInstance()->GetConsole().Print("- Content-Language:  " + GetContentLanguage() + "\n");
		System::GetInstance()->GetConsole().Print("- Content-Type:      " + GetContentType() + "\n");
		System::GetInstance()->GetConsole().Print("- ETag:              " + GetETag() + "\n");
		System::GetInstance()->GetConsole().Print("- Partial:           " + String() + (IsPartial() ? "Yes\n" : "No\n"));
		System::GetInstance()->GetConsole().Print("- Range-Min:         " + String() + (int)GetRangeMin() + "\n");
		System::GetInstance()->GetConsole().Print("- Range-Max:         " + String() + (int)GetRangeMax() + "\n");
		System::GetInstance()->GetConsole().Print("- Range-Total:       " + String() + (int)GetRangeTotal() + "\n");
		System::GetInstance()->GetConsole().Print("\n");
	}

}

/**
*  @brief
*    Get protocol version
*/
EHttpProtocol HttpHeader::GetProtocol() const
{
	// Return protocol version
	return m_nProtocol;
}

/**
*  @brief
*    Get message type
*/
EHttpMessageType HttpHeader::GetMessageType() const
{
	// Return message type
	return m_nMessageType;
}

/**
*  @brief
*    Get request
*/
EHttpRequest HttpHeader::GetRequest() const
{
	// Return HTTP request
	return m_nRequest;
}

/**
*  @brief
*    Get request as string
*/
String HttpHeader::GetRequestString() const
{
	// Return HTTP request
	switch (m_nRequest) {
		case HttpGet:		return "GET";
		case HttpPost:		return "POST";
		case HttpHead:		return "HEAD";
		case HttpPut:		return "PUT";
		case HttpDelete:	return "DELETE";
		case HttpTrace:		return "TRACE";
		case HttpOptions:	return "OPTIONS";
		case HttpConnect:	return "CONNECT";
		default:			return "";
	}
}

/**
*  @brief
*    Get request URL
*/
String HttpHeader::GetRequestUrl() const
{
	// Return request URL
	return m_sRequestUrl;
}

/**
*  @brief
*    Get connection type
*/
EHttpConnection HttpHeader::GetConnectionType() const
{
	// Return connection type
	return m_nConnection;
}

/**
*  @brief
*    Get status code
*/
uint32 HttpHeader::GetStatusCode() const
{
	// Return status code
	return m_nStatusCode;
}

/**
*  @brief
*    Get status string
*/
String HttpHeader::GetStatusString() const
{
	// Return status string
	return m_sStatusString;
}

/**
*  @brief
*    Get location
*/
String HttpHeader::GetLocation() const
{
	// Return location
	return m_sLocation;
}

/**
*  @brief
*    Get date
*/
String HttpHeader::GetDate() const
{
	// Return date
	return m_sDate;
}

/**
*  @brief
*    Get server signature
*/
String HttpHeader::GetServer() const
{
	// Return server signature
	return m_sServer;
}

/**
*  @brief
*    Get client signature
*/
String HttpHeader::GetUserAgent() const
{
	// Return client signature
	return m_sUserAgent;
}

/**
*  @brief
*    Get authentication type
*/
EHttpAuth HttpHeader::GetAuthenticationType() const
{
	// Return authentication type
	return m_nAuthType;
}

/**
*  @brief
*    Get authentication realm
*/
String HttpHeader::GetAuthenticationRealm() const
{
	// Return authentication realm
	return m_sAuthRealm;
}

/**
*  @brief
*    Get authorization string
*/
String HttpHeader::GetAuthorization() const
{
	// Return authorization string
	return m_sAuthorization;
}

/**
*  @brief
*    Get transfer encoding
*/
String HttpHeader::GetTransferEncoding() const
{
	// Return transfer encoding
	return m_sTransferEncoding;
}

/**
*  @brief
*    Check if data is transfered "chunked"
*/
bool HttpHeader::IsChunked() const
{
	// Return if transfer encoding is set to "chunked"
	return m_sTransferEncoding.IsSubstring("chunked");
}

/**
*  @brief
*    Get content length
*/
uint32 HttpHeader::GetContentLength() const
{
	// Return content length
	return m_nContentLength;
}

/**
*  @brief
*    Get content language
*/
String HttpHeader::GetContentLanguage() const
{
	// Return content language
	return m_sContentLanguage;
}

/**
*  @brief
*    Get content type
*/
String HttpHeader::GetContentType() const
{
	// Return content type
	return m_sContentType;
}

/**
*  @brief
*    Get ETag
*/
String HttpHeader::GetETag() const
{
	// Return ETag
	return m_sETag;
}

/**
*  @brief
*    Check if partial data is returned
*/
bool HttpHeader::IsPartial() const
{
	// Return if partial data is received
	return m_bPartial;
}

/**
*  @brief
*    Get start of range
*/
uint32 HttpHeader::GetRangeMin() const
{
	// Return start of range
	return m_nRangeMin;
}

/**
*  @brief
*    Get end of range
*/
uint32 HttpHeader::GetRangeMax() const
{
	// Return end of range
	return m_nRangeMax;
}

/**
*  @brief
*    Get total size
*/
uint32 HttpHeader::GetRangeTotal() const
{
	// Return total size
	return m_nRangeTotal;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
