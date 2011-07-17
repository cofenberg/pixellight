/*********************************************************\
 *  File: ChatServerConnection.h                         *
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


#ifndef __PLSAMPLE_05_CHATSERVERCONNECTION_H__
#define __PLSAMPLE_05_CHATSERVERCONNECTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Network/Connection.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace NetworkChat {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Chat server connection network class
*/
class ChatServerConnection : public PLGeneral::Connection {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ChatServer;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cServer
		*    Server this server connection is connected to
		*/
		ChatServerConnection(PLGeneral::Host &cServer);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		ChatServerConnection(ChatServerConnection &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		ChatServerConnection &operator =(const ChatServerConnection &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ChatServerConnection();


	//[-------------------------------------------------------]
	//[ Private PLGeneral::Connection functions               ]
	//[-------------------------------------------------------]
	private:
		virtual void OnConnect();
		virtual void OnDisconnect();
		virtual void OnReceive(const char *pBuffer, PLGeneral::uint32 nSize);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // NetworkChat


#endif // __PLSAMPLE_05_CHATSERVERCONNECTION_H__
