/*********************************************************\
 *  File: IRCConnection.h                                *
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


#ifndef __PLIRC_IRCCONNECTION_H__
#define __PLIRC_IRCCONNECTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/List.h>
#include <PLGeneral/Network/Buffer.h>
#include <PLGeneral/Network/Connection.h>
#include "PLIRC/PLIRC.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class Time;
}
namespace PLIRC {
	class Channel;
	class IRCClient;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLIRC {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    IRC connection
*/
class IRCConnection : public PLGeneral::Connection {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class IRCClient;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		// Login to IRC server
		PLIRC_API void Login(const PLGeneral::String &sNick, const PLGeneral::String &sLogin = "",
									const PLGeneral::String &sName = "", const PLGeneral::String &sPass = "");

		// Logout from IRC server
		PLIRC_API void Logout(const PLGeneral::String &sReason = "");

		// Joins a channel
		PLIRC_API void JoinChannel(const PLGeneral::String &sChannel, const PLGeneral::String &sPass = "");

		// Leaves (parts) a channel
		PLIRC_API void PartChannel(const PLGeneral::String &sChannel, const PLGeneral::String &sReason = "");

		// Sends a message to a channel or a user
		PLIRC_API void SendMessage(const PLGeneral::String &sTarget, const PLGeneral::String &sMessage);

		// Sends an action to a channel
		PLIRC_API void SendAction(const PLGeneral::String &sChannel, const PLGeneral::String &sAction);

		// Sends a notice to a channel or a user
		PLIRC_API void SendNotice(const PLGeneral::String &sTarget, const PLGeneral::String &sNotice);

		// Sends a CTCP request to a channel or a user
		PLIRC_API void SendCTCP(const PLGeneral::String &sTarget, const PLGeneral::String &sMessage);

		// Sets a new nick name
		PLIRC_API void SetNick(const PLGeneral::String &sNick);

		// Set the channel mode
		PLIRC_API void SetMode(const PLGeneral::String &sChannel, const PLGeneral::String &sMode);

		// Invites a user to a channel
		PLIRC_API void Invite(const PLGeneral::String &sChannel, const PLGeneral::String &sTarget);

		// Get the channel topic (will trigger an OnTopic message)
		PLIRC_API void GetTopic(const PLGeneral::String &sChannel);

		// Sets the channel topic
		PLIRC_API void SetTopic(const PLGeneral::String &sChannel, const PLGeneral::String &sTopic);

		// Kicks a user from a channel
		PLIRC_API void Kick(const PLGeneral::String &sChannel, const PLGeneral::String &sTarget, const PLGeneral::String &sReason);

		// Bans users from a channel
		PLIRC_API void SetBan(const PLGeneral::String &sChannel, const PLGeneral::String &sHostmask, bool bBan = true);

		// Sets the operator status of a user
		PLIRC_API void SetOp(const PLGeneral::String &sChannel, const PLGeneral::String &sTarget, bool bOp = true);

		// Sets the voice status of a user
		PLIRC_API void SetVoice(const PLGeneral::String &sChannel, const PLGeneral::String &sTarget, bool bVoice = true);

		// Channel list
		PLIRC_API PLGeneral::uint32 GetNumOfChannels() const;
		PLIRC_API const Channel *GetChannel(PLGeneral::uint32 nChannel) const;
		PLIRC_API const Channel *GetChannel(const PLGeneral::String &sChannel) const;


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
		PLIRC_API IRCConnection(IRCClient &cClient);

		/**
		*  @brief
		*    Destructor
		*/
		PLIRC_API virtual ~IRCConnection();

		// IRC message processing
		PLIRC_API void ProcessIRCMessage(const PLGeneral::String &sMessage);
		PLIRC_API void ProcessServerMessage(const PLGeneral::String &sSource, int nCmd, char *pszParams[]);
		PLIRC_API void ProcessCTCPMessage(const PLGeneral::String &sSource, const PLGeneral::String &sTarget, const PLGeneral::String &sCTCPMessage);
		PLIRC_API void ProcessMode(const PLGeneral::String &sSource, const PLGeneral::String &sTarget, char *pszParams[]);

		// Channel list
		PLIRC_API Channel *GetChannel(PLGeneral::uint32 nChannel);
		PLIRC_API Channel *GetChannel(const PLGeneral::String &sChannel);
		PLIRC_API bool AddChannel(const PLGeneral::String &sChannel);
		PLIRC_API void RemoveChannel(const PLGeneral::String &sChannel);
		PLIRC_API void RemoveAllChannels();


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Sends a command string to the IRC server
		*
		*  @param[in] sCommand
		*    Command to send
		*
		*  @return
		*    Total number of bytes sent, negative value on error
		*
		*  @remarks
		*    The default implementation only calls Send(sMessage). Overwrite this function
		*    to for instance print send messages on the screen.
		*/
		PLIRC_API virtual int SendCommand(const PLGeneral::String &sCommand);

			// The raw message from the IRC server
		PLIRC_API virtual void OnIRCMessage(const PLGeneral::String &sMessage);
			// A unknown message
		PLIRC_API virtual void OnUnknownMessage(const PLGeneral::String &sMessage);
			// A server message
		PLIRC_API virtual void OnServerMessage(const PLGeneral::String &sSource, int nCmd, char *pszParams[]);
			// A CTCP message
		PLIRC_API virtual void OnCTCPMessage(const PLGeneral::String &sSource, const PLGeneral::String &sMessage);
			// A NOTICE AUTH message
		PLIRC_API virtual void OnNoticeAuth(const PLGeneral::String &sMessage);
			// A PING request from the server
		PLIRC_API virtual void OnServerPing(const PLGeneral::String &sMessage);
			// A user has joined a channel
		PLIRC_API virtual void OnJoin(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, const PLGeneral::String &sUser);
			// A user has part a channel
		PLIRC_API virtual void OnPart(const PLGeneral::String &sChannel, const PLGeneral::String &sSource);
			// A user has quit the server
		PLIRC_API virtual void OnQuit(const PLGeneral::String &sSource, const PLGeneral::String &sReason);
			// A user has changed it's nick
		PLIRC_API virtual void OnNick(const PLGeneral::String &sSource, const PLGeneral::String &sNick);
			// A user has been kicked
		PLIRC_API virtual void OnKick(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, const PLGeneral::String &sTarget, const PLGeneral::String &sReason);
			// A user has changed the mode
		PLIRC_API virtual void OnMode(const PLGeneral::String &sSource, const PLGeneral::String &sTarget, const PLGeneral::String &sMode);
			// Mode change: operator
		PLIRC_API virtual void OnOp(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, const PLGeneral::String &sTarget, bool bOp);
			// Mode change: voice
		PLIRC_API virtual void OnVoice(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, const PLGeneral::String &sTarget, bool bVoice);
			// Mode change: ban
		PLIRC_API virtual void OnBan(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, const PLGeneral::String &sHostmask, bool bBan);
			// Mode change: channel key
		PLIRC_API virtual void OnSetChannelKey(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, const PLGeneral::String &sKey, bool bKey);
			// Mode change: channel limit
		PLIRC_API virtual void OnSetChannelLimit(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, int nLimit);
			// Mode change: channel topic protection
		PLIRC_API virtual void OnSetTopicProtection(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, bool bTopicProtection);
			// Mode change: channel no external messages
		PLIRC_API virtual void OnSetNoExternalMessages(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, bool bNoExternalMessages);
			// Mode change: channel invite only
		PLIRC_API virtual void OnSetInviteOnly(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, bool bInviteOnly);
			// Mode change: channel moderated
		PLIRC_API virtual void OnSetModerated(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, bool bModerated);
			// Mode change: channel private
		PLIRC_API virtual void OnSetPrivate(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, bool bPrivate);
			// Mode change: channel secret
		PLIRC_API virtual void OnSetSecret(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, bool bSecret);
			// A user has invited another user to join a channel
		PLIRC_API virtual void OnInvite(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, const PLGeneral::String &sTarget);
			// A user has changed the topic
		PLIRC_API virtual void OnTopic(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, const PLGeneral::String &sTopic, const PLGeneral::Time &cTime, bool bChanged);
			// A channel has sent it's user list (use GetChannel(), GetUser())
		PLIRC_API virtual void OnUserList(const PLGeneral::String &sChannel);
			// A notice has been sent
		PLIRC_API virtual void OnNotice(const PLGeneral::String &sSource, const PLGeneral::String &sTarget, const PLGeneral::String &sMessage);
			// A channel message has been sent
		PLIRC_API virtual void OnMessage(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, const PLGeneral::String &sMessage);
			// A private message has been sent
		PLIRC_API virtual void OnPrivateMessage(const PLGeneral::String &sSource, const PLGeneral::String &sMessage);
			// CTCP VERSION Request
		PLIRC_API virtual void OnVersion(const PLGeneral::String &sSource);
			// CTCP USERINFO Request
		PLIRC_API virtual void OnUserInfo(const PLGeneral::String &sSource);
			// CTCP CLIENTINFO Request
		PLIRC_API virtual void OnClientInfo(const PLGeneral::String &sSource);
			// CTCP ACTION Request
		PLIRC_API virtual void OnAction(const PLGeneral::String &sChannel, const PLGeneral::String &sSource, const PLGeneral::String &sAction);
			// CTCP PING Request
		PLIRC_API virtual void OnPing(const PLGeneral::String &sSource, const PLGeneral::String &sMessage);
			// CTCP TIME Request
		PLIRC_API virtual void OnTime(const PLGeneral::String &sSource);
			// CTCP FINGER Request
		PLIRC_API virtual void OnFinger(const PLGeneral::String &sSource);
			// CTCP DCC Request
		PLIRC_API virtual void OnDCC(const PLGeneral::String &sSource, const PLGeneral::String &sMessage);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::String		  m_sNick;			/**< User nick name */
		PLGeneral::Buffer		  m_cBuffer;		/**< Receive buffer */
		PLGeneral::List<Channel*> m_lstChannels;	/**< List of channels the user has joined */


	//[-------------------------------------------------------]
	//[ Protected virtual PLGeneral::Connection functions     ]
	//[-------------------------------------------------------]
	protected:
		PLIRC_API virtual void OnConnect();
		PLIRC_API virtual void OnDisconnect();
		PLIRC_API virtual void OnReceive(const char *pBuffer, PLGeneral::uint32 nSize);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLIRC


#endif // __PLIRC_IRCCONNECTION_H__
