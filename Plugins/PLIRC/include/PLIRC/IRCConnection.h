/*********************************************************\
 *  File: IRCConnection.h                                *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLIRC_IRCCONNECTION_H__
#define __PLIRC_IRCCONNECTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/List.h>
#include <PLCore/Network/Buffer.h>
#include <PLCore/Network/Connection.h>
#include "PLIRC/PLIRC.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
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
class IRCConnection : public PLCore::Connection {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class IRCClient;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		// Login to IRC server
		PLIRC_API void Login(const PLCore::String &sNick, const PLCore::String &sLogin = "",
							 const PLCore::String &sName = "", const PLCore::String &sPass = "");

		// Logout from IRC server
		PLIRC_API void Logout(const PLCore::String &sReason = "");

		// Joins a channel
		PLIRC_API void JoinChannel(const PLCore::String &sChannel, const PLCore::String &sPass = "");

		// Leaves (parts) a channel
		PLIRC_API void PartChannel(const PLCore::String &sChannel, const PLCore::String &sReason = "");

		// Sends a message to a channel or a user
		PLIRC_API void SendMessage(const PLCore::String &sTarget, const PLCore::String &sMessage);

		// Sends an action to a channel
		PLIRC_API void SendAction(const PLCore::String &sChannel, const PLCore::String &sAction);

		// Sends a notice to a channel or a user
		PLIRC_API void SendNotice(const PLCore::String &sTarget, const PLCore::String &sNotice);

		// Sends a CTCP request to a channel or a user
		PLIRC_API void SendCTCP(const PLCore::String &sTarget, const PLCore::String &sMessage);

		// Sets a new nick name
		PLIRC_API void SetNick(const PLCore::String &sNick);

		// Set the channel mode
		PLIRC_API void SetMode(const PLCore::String &sChannel, const PLCore::String &sMode);

		// Invites a user to a channel
		PLIRC_API void Invite(const PLCore::String &sChannel, const PLCore::String &sTarget);

		// Get the channel topic (will trigger an OnTopic message)
		PLIRC_API void GetTopic(const PLCore::String &sChannel);

		// Sets the channel topic
		PLIRC_API void SetTopic(const PLCore::String &sChannel, const PLCore::String &sTopic);

		// Kicks a user from a channel
		PLIRC_API void Kick(const PLCore::String &sChannel, const PLCore::String &sTarget, const PLCore::String &sReason);

		// Bans users from a channel
		PLIRC_API void SetBan(const PLCore::String &sChannel, const PLCore::String &sHostmask, bool bBan = true);

		// Sets the operator status of a user
		PLIRC_API void SetOp(const PLCore::String &sChannel, const PLCore::String &sTarget, bool bOp = true);

		// Sets the voice status of a user
		PLIRC_API void SetVoice(const PLCore::String &sChannel, const PLCore::String &sTarget, bool bVoice = true);

		// Channel list
		PLIRC_API PLCore::uint32 GetNumOfChannels() const;
		PLIRC_API const Channel *GetChannel(PLCore::uint32 nChannel) const;
		PLIRC_API const Channel *GetChannel(const PLCore::String &sChannel) const;


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
		PLIRC_API void ProcessIRCMessage(const PLCore::String &sMessage);
		PLIRC_API void ProcessServerMessage(const PLCore::String &sSource, int nCmd, char *pszParams[]);
		PLIRC_API void ProcessCTCPMessage(const PLCore::String &sSource, const PLCore::String &sTarget, const PLCore::String &sCTCPMessage);
		PLIRC_API void ProcessMode(const PLCore::String &sSource, const PLCore::String &sTarget, char *pszParams[]);

		// Channel list
		PLIRC_API Channel *GetChannel(PLCore::uint32 nChannel);
		PLIRC_API Channel *GetChannel(const PLCore::String &sChannel);
		PLIRC_API bool AddChannel(const PLCore::String &sChannel);
		PLIRC_API void RemoveChannel(const PLCore::String &sChannel);
		PLIRC_API void RemoveAllChannels();


	//[-------------------------------------------------------]
	//[ Protected IRCConnection virtual functions             ]
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
		PLIRC_API virtual int SendCommand(const PLCore::String &sCommand);

			// The raw message from the IRC server
		PLIRC_API virtual void OnIRCMessage(const PLCore::String &sMessage);
			// A unknown message
		PLIRC_API virtual void OnUnknownMessage(const PLCore::String &sMessage);
			// A server message
		PLIRC_API virtual void OnServerMessage(const PLCore::String &sSource, int nCmd, char *pszParams[]);
			// A CTCP message
		PLIRC_API virtual void OnCTCPMessage(const PLCore::String &sSource, const PLCore::String &sMessage);
			// A NOTICE AUTH message
		PLIRC_API virtual void OnNoticeAuth(const PLCore::String &sMessage);
			// A PING request from the server
		PLIRC_API virtual void OnServerPing(const PLCore::String &sMessage);
			// A user has joined a channel
		PLIRC_API virtual void OnJoin(const PLCore::String &sChannel, const PLCore::String &sSource, const PLCore::String &sUser);
			// A user has part a channel
		PLIRC_API virtual void OnPart(const PLCore::String &sChannel, const PLCore::String &sSource);
			// A user has quit the server
		PLIRC_API virtual void OnQuit(const PLCore::String &sSource, const PLCore::String &sReason);
			// A user has changed it's nick
		PLIRC_API virtual void OnNick(const PLCore::String &sSource, const PLCore::String &sNick);
			// A user has been kicked
		PLIRC_API virtual void OnKick(const PLCore::String &sChannel, const PLCore::String &sSource, const PLCore::String &sTarget, const PLCore::String &sReason);
			// A user has changed the mode
		PLIRC_API virtual void OnMode(const PLCore::String &sSource, const PLCore::String &sTarget, const PLCore::String &sMode);
			// Mode change: operator
		PLIRC_API virtual void OnOp(const PLCore::String &sChannel, const PLCore::String &sSource, const PLCore::String &sTarget, bool bOp);
			// Mode change: voice
		PLIRC_API virtual void OnVoice(const PLCore::String &sChannel, const PLCore::String &sSource, const PLCore::String &sTarget, bool bVoice);
			// Mode change: ban
		PLIRC_API virtual void OnBan(const PLCore::String &sChannel, const PLCore::String &sSource, const PLCore::String &sHostmask, bool bBan);
			// Mode change: channel key
		PLIRC_API virtual void OnSetChannelKey(const PLCore::String &sChannel, const PLCore::String &sSource, const PLCore::String &sKey, bool bKey);
			// Mode change: channel limit
		PLIRC_API virtual void OnSetChannelLimit(const PLCore::String &sChannel, const PLCore::String &sSource, int nLimit);
			// Mode change: channel topic protection
		PLIRC_API virtual void OnSetTopicProtection(const PLCore::String &sChannel, const PLCore::String &sSource, bool bTopicProtection);
			// Mode change: channel no external messages
		PLIRC_API virtual void OnSetNoExternalMessages(const PLCore::String &sChannel, const PLCore::String &sSource, bool bNoExternalMessages);
			// Mode change: channel invite only
		PLIRC_API virtual void OnSetInviteOnly(const PLCore::String &sChannel, const PLCore::String &sSource, bool bInviteOnly);
			// Mode change: channel moderated
		PLIRC_API virtual void OnSetModerated(const PLCore::String &sChannel, const PLCore::String &sSource, bool bModerated);
			// Mode change: channel private
		PLIRC_API virtual void OnSetPrivate(const PLCore::String &sChannel, const PLCore::String &sSource, bool bPrivate);
			// Mode change: channel secret
		PLIRC_API virtual void OnSetSecret(const PLCore::String &sChannel, const PLCore::String &sSource, bool bSecret);
			// A user has invited another user to join a channel
		PLIRC_API virtual void OnInvite(const PLCore::String &sChannel, const PLCore::String &sSource, const PLCore::String &sTarget);
			// A user has changed the topic
		PLIRC_API virtual void OnTopic(const PLCore::String &sChannel, const PLCore::String &sSource, const PLCore::String &sTopic, const PLCore::Time &cTime, bool bChanged);
			// A channel has sent it's user list (use GetChannel(), GetUser())
		PLIRC_API virtual void OnUserList(const PLCore::String &sChannel);
			// A notice has been sent
		PLIRC_API virtual void OnNotice(const PLCore::String &sSource, const PLCore::String &sTarget, const PLCore::String &sMessage);
			// A channel message has been sent
		PLIRC_API virtual void OnMessage(const PLCore::String &sChannel, const PLCore::String &sSource, const PLCore::String &sMessage);
			// A private message has been sent
		PLIRC_API virtual void OnPrivateMessage(const PLCore::String &sSource, const PLCore::String &sMessage);
			// CTCP VERSION Request
		PLIRC_API virtual void OnVersion(const PLCore::String &sSource);
			// CTCP USERINFO Request
		PLIRC_API virtual void OnUserInfo(const PLCore::String &sSource);
			// CTCP CLIENTINFO Request
		PLIRC_API virtual void OnClientInfo(const PLCore::String &sSource);
			// CTCP ACTION Request
		PLIRC_API virtual void OnAction(const PLCore::String &sChannel, const PLCore::String &sSource, const PLCore::String &sAction);
			// CTCP PING Request
		PLIRC_API virtual void OnPing(const PLCore::String &sSource, const PLCore::String &sMessage);
			// CTCP TIME Request
		PLIRC_API virtual void OnTime(const PLCore::String &sSource);
			// CTCP FINGER Request
		PLIRC_API virtual void OnFinger(const PLCore::String &sSource);
			// CTCP DCC Request
		PLIRC_API virtual void OnDCC(const PLCore::String &sSource, const PLCore::String &sMessage);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::String		   m_sNick;			/**< User nick name */
		PLCore::Buffer		   m_cBuffer;		/**< Receive buffer */
		PLCore::List<Channel*> m_lstChannels;	/**< List of channels the user has joined */


	//[-------------------------------------------------------]
	//[ Protected virtual PLCore::Connection functions        ]
	//[-------------------------------------------------------]
	protected:
		PLIRC_API virtual void OnConnect() override;
		PLIRC_API virtual void OnDisconnect() override;
		PLIRC_API virtual void OnReceive(const char *pBuffer, PLCore::uint32 nSize) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLIRC


#endif // __PLIRC_IRCCONNECTION_H__
