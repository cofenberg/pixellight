/*********************************************************\
 *  File: HttpClient.h                                   *
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


#ifndef __PLCORE_HTTPCLIENT_H__
#define __PLCORE_HTTPCLIENT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Network/Client.h"
#include "PLCore/Network/Http/Http.h"
#include "PLCore/Network/Http/HttpHeader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class HttpClientConnection;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Http server
*/
class HttpClient : protected Client {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ General                                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API HttpClient();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~HttpClient();

		//[-------------------------------------------------------]
		//[ Options                                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Get client signature
		*
		*  @return
		*    Client signature
		*/
		PLCORE_API EClientSignature GetClientSignature() const;

		/**
		*  @brief
		*    Set client signature
		*
		*  @param[in] nClientSignature
		*    Client signature
		*
		*  @remarks
		*    Usually, this HTTP client will send "PixelLight HTTP Client" as it's client
		*    identification, so the server will know, who we are ;-) If you want to mimic
		*    other clients, you can set this to another value, e.g. to mimic a Mozilla client.
		*/
		PLCORE_API void SetClientSignature(EClientSignature nClientSignature);

		/**
		*  @brief
		*    Get protocol version
		*
		*  @return
		*    HTTP protocol version
		*/
		PLCORE_API EHttpProtocol GetProtocol() const;

		/**
		*  @brief
		*    Set protocol version
		*
		*  @param[in] nProtocol
		*    HTTP protocol version
		*/
		PLCORE_API void SetProtocol(EHttpProtocol nProtocol);

		/**
		*  @brief
		*    Get connection type
		*
		*  @return
		*    HTTP connection type
		*/
		PLCORE_API EHttpConnection GetConnectionType() const;

		/**
		*  @brief
		*    Set connection type
		*
		*  @param[in] nConnection
		*    HTTP connection type
		*/
		PLCORE_API void SetConnectionType(EHttpConnection nConnection);

		/**
		*  @brief
		*    Get authentication
		*
		*  @return
		*    HTTP authentication type
		*/
		PLCORE_API EHttpAuth GetAuthentication() const;

		/**
		*  @brief
		*    Set authentication
		*
		*  @param[in] nAuth
		*    HTTP authentication type
		*  @param[in] sUsername
		*    User name
		*  @param[in] sPassword
		*    Password
		*/
		PLCORE_API void SetAuthentication(EHttpAuth nAuth, const String &sUsername, const String &sPassword);

		//[-------------------------------------------------------]
		//[ Functions                                             ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Check if a connection is open
		*
		*  @return
		*    'true' if connection is open, else 'false'
		*/
		PLCORE_API bool IsConnected() const;

		/**
		*  @brief
		*    Open connection to server
		*
		*  @param[in] sAddress
		*    Server address
		*  @param[in] nPort
		*    Port number (Default: 80)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool Open(const String &sAddress, uint32 nPort = 80);

		/**
		*  @brief
		*    Close HTTP session
		*/
		PLCORE_API void Disconnect();

		/**
		*  @brief
		*    Open a HTTP resource (GET command)
		*
		*  @param[in] sURL
		*    URL
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool Get(const String &sURL);

		/**
		*  @brief
		*    Open a HTTP resource and get partial data (GET command)
		*
		*  @param[in] sURL
		*    URL
		*  @param[in] nPos
		*    Start offset
		*  @param[in] nSize
		*    Size of data to read (-1 for all)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool GetPartial(const String &sURL, uint32 nPos, int32 nSize = -1);

		/**
		*  @brief
		*    Open a HTTP resource (POST command)
		*
		*  @param[in] sURL
		*    URL
		*  @param[in] sPostData
		*    Additional data for POST command
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool Post(const String &sURL, const String &sPostData);

		/**
		*  @brief
		*    Delete a HTTP resource (DELETE command)
		*
		*  @param[in] sURL
		*    URL
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool Delete(const String &sURL);

		/**
		*  @brief
		*    Get HTTP header sent from server
		*
		*  @return
		*    Header of HTTP answer from server
		*/
		PLCORE_API const HttpHeader &GetHeader() const;

		/**
		*  @brief
		*    Read data from HTTP connection
		*
		*  @param[in] pBuffer
		*    Data buffer
		*  @param[in] nSize
		*    Size in bytes
		*
		*  @return
		*    Total number of bytes read. Can be less than the requested size
		*    to be sent, negative value on error
		*/
		PLCORE_API int Read(char *pBuffer, uint32 nSize);


	//[-------------------------------------------------------]
	//[ Protected virtual Client functions                    ]
	//[-------------------------------------------------------]
	protected:
		PLCORE_API virtual Connection *CreateOutgoingConnection();
		PLCORE_API virtual void OnDisconnect(Connection &cConnection);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cClient
		*    HTTP client
		*/
		HttpClient(const HttpClient &cClient);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cHttpClient
		*    HTTP client
		*
		*  @return
		*    Reference to this client
		*/
		HttpClient &operator =(const HttpClient &cClient);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		EClientSignature		 m_nClientSignature;	/**< Used client signature (Default: ClientPixelLight) */
		EHttpProtocol			 m_nHttpProtocol;		/**< Used protocol version (Default: Http11) */
		EHttpConnection			 m_nConnection;			/**< Used connection type  (Default: Close) */
		EHttpAuth				 m_nHttpAuth;			/**< Used authentication   (Default: NoAuth) */
		String					 m_sAddress;			/**< Host address */
		uint32					 m_nPort;				/**< Port number */
		String					 m_sUsername;			/**< User name (for authentication) */
		String					 m_sPassword;			/**< Password  (for authentication) */
		HttpClientConnection	*m_pConnection;			/**< Current connection */
		HttpHeader				 m_cHttpHeader;			/**< Received HTTP header */
		int						 m_nChunkSize;			/**< Size of current chunk (only for chunked transfer-coding) */
		int						 m_nChunkLeft;			/**< Size of chunk remaining (only for chunked transfer-coding) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_HTTPCLIENT_H__
