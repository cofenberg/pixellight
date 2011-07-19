/*********************************************************\
 *  File: HttpClientConnection.h                         *
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


#ifndef __PLCORE_HTTPCLIENTCONNECTION_H__
#define __PLCORE_HTTPCLIENTCONNECTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Network/Connection.h"
#include "PLCore/Network/Buffer.h"
#include "PLCore/Network/Http/HttpHeader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Http client connection
*/
class HttpClientConnection : public Connection {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API HttpClientConnection(Host &cHost);

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~HttpClientConnection();

		/**
		*  @brief
		*    Read HTTP header
		*/
		PLCORE_API const HttpHeader &ReadHttpHeader();


	//[-------------------------------------------------------]
	//[ Protected virtual Connection functions                ]
	//[-------------------------------------------------------]
	protected:
		PLCORE_API virtual void OnConnect();
		PLCORE_API virtual void OnDisconnect();
		PLCORE_API virtual void OnReceive(const char *pBuffer, uint32 nSize);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Buffer		m_cBuffer;		/**< Receive buffer */
		HttpHeader	m_cHttpHeader;	/**< Received HTTP header */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_HTTPCLIENTCONNECTION_H__
