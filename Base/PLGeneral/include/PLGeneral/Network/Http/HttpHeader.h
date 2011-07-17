/*********************************************************\
 *  File: HttpHeader.h                                   *
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


#ifndef __PLGENERAL_HTTPHEADER_H__
#define __PLGENERAL_HTTPHEADER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/String.h"
#include "PLGeneral/Container/Array.h"
#include "PLGeneral/Network/Http/Http.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    HTTP header
*/
class HttpHeader {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API HttpHeader();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    HTTP header
		*/
		PLGENERAL_API HttpHeader(const HttpHeader &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API ~HttpHeader();

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] cSource
		*    HTTP header
		*
		*  @return
		*    Reference to this header
		*/
		PLGENERAL_API HttpHeader &operator =(const HttpHeader &cSource);

		/**
		*  @brief
		*    Clear header
		*/
		PLGENERAL_API void Clear();

		/**
		*  @brief
		*    Check if HTTP header is complete
		*
		*  @return
		*    'true' if header is complete, else 'false'
		*/
		PLGENERAL_API bool IsComplete() const;

		/**
		*  @brief
		*    Get header entries
		*
		*  @return
		*    List of header entries
		*/
		PLGENERAL_API const Container<String> &GetEntries() const;

		/**
		*  @brief
		*    Add entry
		*
		*  @param[in] sEntry
		*    Header entry
		*/
		PLGENERAL_API void AddEntry(const String &sEntry);

		/**
		*  @brief
		*    Parse header
		*
		*  @remarks
		*    This function will parse and interpret all header entries. Call this function
		*    after you have received the header, then you can access the parsed information
		*    via their get-methods (GetSize(), GetContentType(), etc.)
		*/
		PLGENERAL_API void Parse();

		/**
		*  @brief
		*    Print header entries to console
		*
		*  @param[in] bRaw
		*    If 'true', all header entries will be printed out, otherwise only those which are known by this implementation
		*/
		PLGENERAL_API void Print(bool bRaw = false) const;

		/**
		*  @brief
		*    Get protocol version
		*
		*  @return
		*    HTTP Protocol version
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API EHttpProtocol GetProtocol() const;

		/**
		*  @brief
		*    Get message type
		*
		*  @return
		*    HTTP message type (request or response)
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API EHttpMessageType GetMessageType() const;

		/**
		*  @brief
		*    Get request
		*
		*  @return
		*    HTTP request type
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API EHttpRequest GetRequest() const;

		/**
		*  @brief
		*    Get request as string
		*
		*  @return
		*    HTTP request type
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API String GetRequestString() const;

		/**
		*  @brief
		*    Get request URL
		*
		*  @return
		*    HTTP request URL
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API String GetRequestUrl() const;

		/**
		*  @brief
		*    Get connection type
		*
		*  @return
		*    HTTP connection type
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API EHttpConnection GetConnectionType() const;

		/**
		*  @brief
		*    Get status code
		*
		*  @return
		*    Status code
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API uint32 GetStatusCode() const;

		/**
		*  @brief
		*    Get status string
		*
		*  @return
		*    Status string
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API String GetStatusString() const;

		/**
		*  @brief
		*    Get location
		*
		*  @return
		*    Location
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API String GetLocation() const;

		/**
		*  @brief
		*    Get date
		*
		*  @return
		*    Date
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API String GetDate() const;

		/**
		*  @brief
		*    Get server signature
		*
		*  @return
		*    Server signature
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API String GetServer() const;

		/**
		*  @brief
		*    Get client signature
		*
		*  @return
		*    Client signature
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API String GetUserAgent() const;

		/**
		*  @brief
		*    Get authentication type
		*
		*  @return
		*    Authentication type
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API EHttpAuth GetAuthenticationType() const;

		/**
		*  @brief
		*    Get authentication realm
		*
		*  @return
		*    Authentication realm
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API String GetAuthenticationRealm() const;

		/**
		*  @brief
		*    Get authorization string
		*
		*  @return
		*    Authorization string
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API String GetAuthorization() const;

		/**
		*  @brief
		*    Get transfer encoding
		*
		*  @return
		*    Transfer encoding
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API String GetTransferEncoding() const;

		/**
		*  @brief
		*    Check if data is transfered "chunked"
		*
		*  @return
		*    'true' if rransfer encoding is "chunked", else 'false'
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API bool IsChunked() const;

		/**
		*  @brief
		*    Get content length
		*
		*  @return
		*    Content length
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API uint32 GetContentLength() const;

		/**
		*  @brief
		*    Get content language
		*
		*  @return
		*    Content language
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API String GetContentLanguage() const;

		/**
		*  @brief
		*    Get content type
		*
		*  @return
		*    Content type
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API String GetContentType() const;

		/**
		*  @brief
		*    Get ETag
		*
		*  @return
		*    ETag for content
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API String GetETag() const;

		/**
		*  @brief
		*    Check if partial data is returned
		*
		*  @return
		*    'true' if partial data is returned, else 'false'
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API bool IsPartial() const;

		/**
		*  @brief
		*    Get start of range
		*
		*  @return
		*    Byte position
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API uint32 GetRangeMin() const;

		/**
		*  @brief
		*    Get end of range
		*
		*  @return
		*    Byte position
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API uint32 GetRangeMax() const;

		/**
		*  @brief
		*    Get total size
		*
		*  @return
		*    Size
		*
		*  @remarks
		*    To access this information, Parse() has to be called first
		*/
		PLGENERAL_API uint32 GetRangeTotal() const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:	
		Array<String>			m_lstEntries;			/**< Header entries */
		EHttpProtocol			m_nProtocol;			/**< HTTP protocol version */
		EHttpMessageType		m_nMessageType;			/**< Message type (request or response) */
		EHttpRequest			m_nRequest;				/**< Request type */
		String					m_sRequestUrl;			/**< Request URL */
		EHttpConnection			m_nConnection;			/**< Connection type (Close or KeepAlive) */
		EHttpStatus				m_nStatusCode;			/**< Status code */
		String					m_sStatusString;		/**< Status string */
		String					m_sLocation;			/**< Location */
		String					m_sDate;				/**< Date */
		String					m_sServer;				/**< Server signature */
		String					m_sUserAgent;			/**< Client signature */
		EHttpAuth				m_nAuthType;			/**< Authentication type */
		String					m_sAuthRealm;			/**< Authentication realm */
		String					m_sAuthorization;		/**< Authorization string */
		String					m_sTransferEncoding;	/**< Transfer encoding */
		uint32					m_nContentLength;		/**< Content size */
		String					m_sContentLanguage;		/**< Content language */
		String					m_sContentType;			/**< Content type (MIME type) */
		String					m_sETag;				/**< ETag (identifier for content) */
		bool					m_bPartial;				/**< Partial download? */
		uint32					m_nRangeMin;			/**< Start of range (for partical content) */
		uint32					m_nRangeMax;			/**< End of range   (for partical content) */
		uint32					m_nRangeTotal;			/**< Total size     (for partical content) */
	

};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_HTTPHEADER_H__
