/*********************************************************\
 *  File: JabberConnection.h                             *
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


#ifndef __PLJABBER_JABBERCONNECTION_H__
#define __PLJABBER_JABBERCONNECTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Network/Connection.h>
#include "PLJabber/InputStream.h"
#include "PLJabber/OutputStream.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLJabber {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class JabberClient;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Jabber connection
*/
class JabberConnection : public PLCore::Connection {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class JabberClient;
	friend class InputStream;


	//[-------------------------------------------------------]
	//[ Public data types                                     ]
	//[-------------------------------------------------------]
	public:
		enum EPresence {
			Unavailable,
			Available
		};

		enum EPresenceShow {
			Away,
			Chat,
			DND,
			Normal,
			XA
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Create a new Jabber account
		*
		*  @param[in] sServer
		*    Name of the server
		*  @param[in] sUsername
		*    Desired user name
		*  @param[in] sPassword
		*    Desired password
		*/
		PLJABBER_API void CreateAccount(const PLCore::String &sServer, const PLCore::String &sUsername, const PLCore::String &sPassword);

		/**
		*  @brief
		*    Log in with an existing Jabber account
		*
		*  @param[in] sServer
		*    Name of the server
		*  @param[in] sUsername
		*    User name
		*  @param[in] sPassword
		*    Password
		*/
		PLJABBER_API void Login(const PLCore::String &sServer, const PLCore::String &sUsername, const PLCore::String &sPassword);

		/**
		*  @brief
		*    Log out
		*/
		PLJABBER_API void Logout();

		// [TODO] Comments for the following methods
		PLJABBER_API void GetRoster() const;

		PLJABBER_API void SetPresence(EPresence nPresence, EPresenceShow nShow, const PLCore::String &sStatus, int nPriority) const;

		PLJABBER_API void Subscribe(const PLCore::String &sTo) const;

		PLJABBER_API void Unsubscribe(const PLCore::String &sTo) const;

		PLJABBER_API void AllowSubscription(const PLCore::String &sTo) const;

		PLJABBER_API void RevokeSubscription(const PLCore::String &sTo) const;

		PLJABBER_API void Message(const PLCore::String &sTo, const PLCore::String &sSubject, const PLCore::String &sMessage) const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cClient
		*    Client this client connection is connected to
		*/
		PLJABBER_API JabberConnection(JabberClient &cClient);

		/**
		*  @brief
		*    Destructor
		*/
		PLJABBER_API virtual ~JabberConnection();

		/**
		*  @brief
		*    Send an element to the Jabber server
		*
		*  @param[in] cElement
		*    XML Element
		*/
		PLJABBER_API void SendElement(const PLCore::XmlElement &cElement) const;

		PLJABBER_API void SendQueryLogin(const PLCore::String &sUsername, const PLCore::String &sPassword) const;
		PLJABBER_API void SendLogin(const PLCore::String &sUsername, const PLCore::String &sPassword) const;
		PLJABBER_API void SendQueryRoster() const;
		PLJABBER_API void SendMsg(const PLCore::String &sTo, const PLCore::String &sSubject, const PLCore::String &sMessage) const;

		/**
		*  @brief
		*    Send a presence element
		*
		*  @param[in] sFrom
		*    Name of sending entity
		*  @param[in] sTo
		*    Name of receiving entity
		*  @param[in] sType
		*    Type of the presence element
		*  @param[in] sShow
		*    Online status of the user
		*  @param[in] sStatus
		*    Additional status text
		*  @param[in] nPriority
		*    Priority for this connection
		*
		*  @remarks
		*    sFrom only needs to be set for type 'probe'
		*    sTo only needs to be set for type 'subscribe', 'unsubscribe' or 'probe'
		*    sType can have one of the following values:
		*      - 'available':   Set presence to available
		*      - 'unavailable': Set presence to unavailable
		*      - 'probe':       Probe for the presence of another entity (do NOT use, the server is responsible for this!)
		*      - 'subscribe':	Subscribe for the presence of another entity
		*      - 'unsubscribe': Unsubscribe from the presence of another entity
		*    sShow can have one of the following values:
		*      - 'away':   User is away
		*      - 'chat':   User is available and open to conversation
		*      - 'dnd':    User doesn't want to be disturbed
		*      - 'normal': User is available (standard online status)
		*      - 'xa':     User is away. Really.
		*/
		PLJABBER_API void SendPresence(const PLCore::String &sFrom, const PLCore::String &sTo, const PLCore::String &sType, const PLCore::String &sShow, const PLCore::String &sStatus, int nPriority) const;


	//[-------------------------------------------------------]
	//[ Protected virtual PLCore::Connection functions        ]
	//[-------------------------------------------------------]
	protected:
		PLJABBER_API virtual void OnConnect() override;
		PLJABBER_API virtual void OnDisconnect() override;
		PLJABBER_API virtual void OnReceive(const char *pBuffer, PLCore::uint32 nSize) override;


	//[-------------------------------------------------------]
	//[ Protected virtual JabberConnection functions          ]
	//[-------------------------------------------------------]
	protected:
		PLJABBER_API virtual void OnStreamStarted(const PLCore::XmlElement &cStream);
		PLJABBER_API virtual void OnElement(const PLCore::XmlElement &cElement);
		PLJABBER_API virtual void OnInformQuery(const PLCore::XmlElement &cElement);
		PLJABBER_API virtual void OnMessage(const PLCore::XmlElement &cElement);
		PLJABBER_API virtual void OnPresence(const PLCore::XmlElement &cElement);
		PLJABBER_API virtual void OnError(const PLCore::XmlElement &cElement);
		PLJABBER_API virtual void OnAuthInfo(const PLCore::XmlElement &cElement);
		PLJABBER_API virtual void OnAuth(const PLCore::XmlElement &cElement);
		PLJABBER_API virtual void OnRoster(const PLCore::XmlElement &cElement);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// XML streams
		InputStream		m_cInput;		/**< XML input stream */
		OutputStream	m_cOutput;		/**< XML output stream */

		// User data
		PLCore::String	m_sUsername;
		PLCore::String	m_sPassword;
		PLCore::String	m_sUserID;

		// Connection data
		PLCore::String	m_sServer;		/**< Name of the server */
		PLCore::String	m_sID;			/**< ID generated by the server */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLJabber


#endif // __PLJABBER_JABBERCONNECTION_H__
