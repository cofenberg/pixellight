/*********************************************************\
 *  File: IRCConnection.cpp                              *
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


// [TODO]
// - Topic: datentyp von date (millies) überprüfen
// - Channel prefixes: #$+!
// - Log Ausgaben
// - Zu jedem OnMode auch ein SetMode ?
// - IDENT-Server ?
// - Komplett auf String-Klasse umstellen


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
// [TODO] Remove this
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef WIN32
	#include <PLGeneral/PLGeneralWindowsIncludes.h>
#endif
#ifdef LINUX
	#include <PLGeneral/PLGeneralLinuxWrapper.h>
#endif
#include <PLGeneral/System/System.h>

#include "PLIRC/User.h"
#include "PLIRC/Channel.h"
#include "PLIRC/IRCClient.h"
#include "PLIRC/IRCConnection.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLIRC {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
void IRCConnection::Login(const String &sNick, const String &sLogin, const String &sName, const String &sPass)
{
	// Check parameters
	if (sNick.GetLength()) {
		String sComposed;

		// Send password
		if (sPass.GetLength()) sComposed += "PASS " + sPass + "\r\n";

		// Send nickname
		sComposed += "NICK " + sNick + "\r\n";

		// Send user information
		sComposed += "USER " + (sLogin.GetLength() ? sLogin : sNick) + " 8 * :" + (sName.GetLength() ? sName : "nobody") + "\r\n";

		// Finally, send the composed command
		SendCommand(sComposed);

/* [TODO] Check this: During my tests the following did not work, it only works if I compose the command as used above...
		// Send password
		if (sPass.GetLength()) SendCommand("PASS " + sPass);

		// Send nickname
		SendCommand("NICK " + sNick);

		// Send user information
		SendCommand("USER " + (sLogin.GetLength() ? sLogin : sNick) + " 8 * :" + (sName.GetLength() ? sName : "nobody"));
*/

		// Save nick
		m_sNick = sNick;
	}
}

void IRCConnection::Logout(const String &sReason)
{
	// Send QUIT message
	SendCommand("QUIT :" + sReason);
}

void IRCConnection::JoinChannel(const String &sChannel, const String &sPass)
{
	// Send JOIN message
	if (sPass.GetLength()) SendCommand("JOIN " + sChannel + ' ' + sPass);
	else				   SendCommand("JOIN " + sChannel);
}

void IRCConnection::PartChannel(const String &sChannel, const String &sReason)
{
	// Send PART message
	if (sReason.GetLength()) SendCommand("PART " + sChannel + " :" + sReason);
	else					 SendCommand("PART " + sChannel);
}

void IRCConnection::SendMessage(const String &sTarget, const String &sMessage)
{
	// Send PRIVMSG message
	SendCommand("PRIVMSG " + sTarget + " :" + sMessage);
}

void IRCConnection::SendAction(const String &sChannel, const String &sAction)
{
	// Send PRIVMSG message
	SendCTCP(sChannel, "ACTION " + sAction);
}

void IRCConnection::SendNotice(const String &sTarget, const String &sNotice)
{
	// Send NOTICE message
	SendCommand("NOTICE " + sTarget + " :" + sNotice);
}

void IRCConnection::SendCTCP(const String &sTarget, const String &sMessage)
{
	// Send PRIVMSG message
	SendCommand("PRIVMSG " + sTarget + " :\1" + sMessage + "\1");
}

void IRCConnection::SetNick(const String &sNick)
{
	// Send NICK message
	SendCommand("NICK " + sNick);
}

void IRCConnection::SetMode(const String &sChannel, const String &sMode)
{
	// Send MODE message
	// [TODO] Test this
	SendCommand("MODE " + sChannel + ' ' + sMode);
}

void IRCConnection::Invite(const String &sChannel, const String &sTarget)
{
	// Send INVITE message
	SendCommand("INVITE " + sTarget + " :" + sChannel);
}

void IRCConnection::GetTopic(const String &sChannel)
{
	// Send TOPIC request
	SendCommand("TOPIC " + sChannel);
}

void IRCConnection::SetTopic(const String &sChannel, const String &sTopic)
{
	// Send TOPIC message
	SendCommand("TOPIC " + sChannel + " :" + sTopic);
}

void IRCConnection::Kick(const String &sChannel, const String &sTarget, const String &sReason)
{
	// Send KICK message
	SendCommand("KICK " + sChannel + ' ' + sTarget + " :" + sReason);
}

void IRCConnection::SetBan(const String &sChannel, const String &sHostmask, bool bBan)
{
	// Set ban mode
	SendCommand("MODE " + sChannel + (bBan ? "+b" : "-b") + sHostmask);
}

void IRCConnection::SetOp(const String &sChannel, const String &sTarget, bool bOp)
{
	// Set op mode
	SendCommand("MODE " + sChannel + (bOp ? "+o" : "-o") + sTarget);
}

void IRCConnection::SetVoice(const String &sChannel, const String &sTarget, bool bVoice)
{
	// Set voice mode
	SendCommand("MODE " + sChannel + (bVoice ? "+v" : "-v") + sTarget);
}

uint32 IRCConnection::GetNumOfChannels() const
{
	return m_lstChannels.GetNumOfElements();
}

const Channel *IRCConnection::GetChannel(uint32 nChannel) const
{
	return m_lstChannels[nChannel];
}

const Channel *IRCConnection::GetChannel(const String &sChannel) const
{
	// Search for channel
	Iterator<Channel*> cIterator = m_lstChannels.GetIterator();
	while (cIterator.HasNext()) {
		Channel *pChannel = cIterator.Next();
		if (pChannel->GetName() == sChannel) {
			// Return channel
			return pChannel;
		}
	}

	// Channel not found
	return nullptr;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
IRCConnection::IRCConnection(IRCClient &cClient) : Connection(cClient)
{
}

/**
*  @brief
*    Destructor
*/
IRCConnection::~IRCConnection()
{
	// Delete all channels
	RemoveAllChannels();
}

// Processes an IRC message
void IRCConnection::ProcessIRCMessage(const String &sMessage)
{
	// Save message in temporary buffer
	char *pszMsg = new char[sMessage.GetLength()+1];
	strcpy(pszMsg, sMessage.GetASCII());
	pszMsg[sMessage.GetLength()] = '\0';

	// Call notify function
	OnIRCMessage(sMessage);

	// NOTICE AUTH
	if (!strncmp(pszMsg, "NOTICE AUTH", 11)) {
		const char *pszString = strchr(pszMsg, ':');
		if (pszString) {
			// Call notify function
			OnNoticeAuth(pszString+1);
		}

	// PING
	} else if (!strncmp(pszMsg, "PING", 4)) {
		const char *pszString = strchr(pszMsg, ':');
		if (pszString) {
			// Call notify function
			OnServerPing(pszString+1);
		}

	// A general message
	} else if (pszMsg[0] == ':') {
		// Init parameters
		char *pszParams[32];
		for (int i=0; i<32; i++) pszParams[i] = nullptr;

		// Parse string
		int nParam = 0;
		char *pszPos = pszMsg+1;
		char *pszEnd = pszPos;
		do {
			// Find end of parameter
			if (pszPos[0] != ':') pszEnd = strchr(pszPos, ' ');
			else {
				pszPos++;
				pszEnd = nullptr;
			}
			if (pszEnd) pszEnd[0] = '\0';

			// Save parameter
			pszParams[nParam] = new char[strlen(pszPos)+1];
			strcpy(pszParams[nParam], pszPos);
			nParam++;

			// Next parameter
			pszPos = pszEnd+1;
		} while (pszEnd);

		// Get nick, login and host name
		char szNick[256] = "";
		char szUser[256] = "";
		char *pszEx = strchr(pszParams[0], '!');
		if (pszEx) {
			strcpy(szNick, pszParams[0]); szNick[pszEx-pszParams[0]] = '\0';
			strcpy(szUser, pszEx+1);
		}

		// Server message
		int nServerMsg = atoi(pszParams[1]);
		if (nServerMsg > 0) {
			// Process server message
			ProcessServerMessage(pszParams[0], nServerMsg, pszParams);

		// JOIN
		} else if (!strcmp(pszParams[1], "JOIN")) {
			// Did we join a channel?
			if (!stricmp(m_sNick.GetASCII(), szNick)) {
				// Add channel
				AddChannel(pszParams[2]);
			} else {
				// Add new user to channel
				Channel *pChannel = GetChannel(pszParams[2]);
				if (pChannel) pChannel->AddUser(szNick);
			}

			// Call event function
			OnJoin(pszParams[2], szNick, szUser);

		// PART
		} else if (!strcmp(pszParams[1], "PART")) {
			// Did we leave a channel?
			if (!stricmp(m_sNick.GetASCII(), szNick)) {
				// Remove channel
				RemoveChannel(pszParams[2]);
			} else {
				// Remove user from channel
				Channel *pChannel = GetChannel(pszParams[2]);
				if (pChannel) pChannel->RemoveUser(szNick);
			}

			// Call event function
			OnPart(pszParams[2], szNick);

		// QUIT
		} else if (!strcmp(pszParams[1], "QUIT")) {
			// Did we quit?
			if (!stricmp(m_sNick.GetASCII(), szNick)) {
				// Leave all channels
				RemoveAllChannels();
			} else {
				// Remove user from all channels
				for (uint32 i=0; i<GetNumOfChannels(); i++)
					GetChannel(i)->RemoveUser(szNick);
			}

			// Call event function
			OnQuit(szNick, pszParams[2]);

		// NICK
		} else if (!strcmp(pszParams[1], "NICK")) {
			// Change own nick
			if (!stricmp(m_sNick.GetASCII(), szNick))
				m_sNick = pszParams[2];

			// Change nick in all channels
			for (uint32 i=0; i<GetNumOfChannels(); i++) {
				User *pUser = GetChannel(i)->GetUser(szNick);
				if (pUser) pUser->SetNick(pszParams[2]);
			}

			// Call event function
			OnNick(szNick, pszParams[2]);

		// KICK
		} else if (!strcmp(pszParams[1], "KICK")) {
			// Did we got kicked?
			if (!stricmp(m_sNick.GetASCII(), pszParams[3])) {
				// Remove channel
				RemoveChannel(pszParams[2]);
			} else {
				// Remove user from channel
				Channel *pChannel = GetChannel(pszParams[2]);
				if (pChannel) pChannel->RemoveUser(pszParams[3]);
			}

			// Call event function
			OnKick(pszParams[2], szNick, pszParams[3], pszParams[4]);

		// MODE
		} else if (!strcmp(pszParams[1], "MODE")) {
			// Call event function
			ProcessMode(strlen(szNick) ? szNick : pszParams[0], pszParams[2], pszParams);

		// INVITE
		} else if (!strcmp(pszParams[1], "INVITE")) {
			// Call event function
			OnInvite(pszParams[3], szNick, pszParams[2]);

		// TOPIC
		} else if (!strcmp(pszParams[1], "TOPIC")) {
			// Call event function
			Channel *pChannel = GetChannel(pszParams[2]);
			if (pChannel) {
				Topic &cTopic = pChannel->GetTopic();
				cTopic.SetNick(szNick);
				cTopic.SetTopic(pszParams[3]);
				Time cTime = System::GetInstance()->GetTime();
				cTopic.SetDate(cTime);
				OnTopic(pszParams[2], szNick, pszParams[3], cTime, true);
			}

		// NOTICE
		} else if (!strcmp(pszParams[1], "NOTICE")) {
			// Call event function
			OnNotice(szNick, pszParams[2], pszParams[3]);

		// PRIVMSG
		} else if (!strcmp(pszParams[1], "PRIVMSG")) {
			// CTCP message
			if (pszParams[3][0] == '\1') {
				// Get CTCP command
				int nLen = static_cast<int>(strlen(pszParams[3]))-2;
				for (int i=0; i<nLen; i++) pszParams[3][i] = pszParams[3][i+1];
				pszParams[3][nLen] = '\0';

				// Process CTCP message
				ProcessCTCPMessage(szNick, pszParams[2], pszParams[3]);

			// Channel or private message
			} else {
				// Call event function
				if (pszParams[2][0] == '#')	OnMessage(pszParams[2], szNick, pszParams[3]);
				else						OnPrivateMessage(szNick, pszParams[3]);
			}

		// Unknown message
		} else {
			// Call event function
			OnUnknownMessage(sMessage);
		}

		// Delete parameters
		for (int i=0; i<32; i++) {
			if (pszParams[i]) delete [] pszParams[i];
		}

	// Unknown message
	} else {
		// Call event function
		OnUnknownMessage(sMessage);
	}

	// Release buffer
	delete [] pszMsg;
}

// Process a server message
void IRCConnection::ProcessServerMessage(const String &sSource, int nCmd, char *pszParams[])
{
	// Call notify function
	OnServerMessage(sSource, nCmd, pszParams);

	// 331: No topic set
	if (nCmd == 331) {
		const char *pszChannel = pszParams[3];
		Channel *pChannel = GetChannel(pszChannel);
		if (pChannel) {
			Topic &cTopic = pChannel->GetTopic();
			cTopic.SetNick("");
			cTopic.SetTopic("");
			cTopic.SetDate(Time::Null);
			OnTopic(pszChannel, "", "", Time::Null, false);
		}

	// 332: Topic information part 1
	} else if (nCmd == 332) {
		const char *pszChannel = pszParams[3];
		Channel *pChannel = GetChannel(pszChannel);
		if (pChannel) {
			const char *pszTopic = pszParams[4];
			Topic &cTopic = pChannel->GetTopic();
			cTopic.SetNick("");
			cTopic.SetTopic(pszTopic);
			cTopic.SetDate(Time::Null);
		}

	// 333: Topic information part 2
	} else if (nCmd == 333) {
		char   *pszChannel = pszParams[3];
		char   *pszNick    = pszParams[4];
		char   *pszDate    = pszParams[5];
		uint32  nDate      = atol(pszDate) * 1000; // Get POSIX timestamp (number of seconds since the epoch) at which the topic was last set
		char *pszEx = strchr(pszNick, '!');
		if (pszEx) pszEx[0] = '\0';
		Channel *pChannel = GetChannel(pszChannel);
		if (pChannel) {
			Topic &cTopic = pChannel->GetTopic();
			cTopic.SetNick(pszNick);
			Time cTime;
			cTime.SetUnixDate(nDate);
			cTopic.SetDate(cTime);
			OnTopic(pszChannel, cTopic.GetNick(), cTopic.GetTopic(), cTime, false);
		}

	// 353: User list
	} else if (nCmd == 353) {
		// Parse user list
		const char *pszStart = pszParams[5];
		while (pszStart[0] != '\0') {
			// Get end of first nick name
			const char *pszEnd = strchr(pszStart, ' ');
			if (!pszEnd) pszEnd = pszStart + strlen(pszStart);
			unsigned int nLength = static_cast<unsigned int>(pszEnd - pszStart);

			// Copy first nick name
			char szNick[256];
			strncpy(szNick, pszStart, nLength);
			szNick[nLength] = '\0';

			// Get name and status flags
			const char *pszNick = szNick;
			bool bOp	= false;
			bool bVoice	= false;
			while (pszNick[0] == '@' || pszNick[0] == '+' || pszNick[0] == '.') {
				if (pszNick[0] == '@') bOp	  = true;
				if (pszNick[0] == '+') bVoice = true;
				pszNick++;
			}

			// Add user
			Channel *pChannel = GetChannel(pszParams[4]);
			if (pChannel) pChannel->AddUser(pszNick, bOp, bVoice);

			// Go to next nick name
			if (pszEnd[0] != '\0')	pszStart = pszEnd+1;
			else					pszStart = pszEnd;
		}

	// 366: End of user list
	} else if (nCmd == 366) {
		OnUserList(pszParams[3]);
	}
}

// Process a CTCP message
void IRCConnection::ProcessCTCPMessage(const String &sSource, const String &sTarget, const String &sCTCPMessage)
{
	// Call notify function
	OnCTCPMessage(sSource, sCTCPMessage);

	// VERSION request
	if (sCTCPMessage == "VERSION") {
		OnVersion(sSource);

	// USERINFO request
	} else if (sCTCPMessage == "USERINFO") {
		OnUserInfo(sSource);

	// CLIENTINFO request
	} else if (sCTCPMessage == "CLIENTINFO") {
		OnClientInfo(sSource);

	// ACTION request
	} else if (sCTCPMessage.Compare("ACTION ", 0, 7)) {
		OnAction(sTarget, sSource, sCTCPMessage.GetSubstring(7));

	// PING request
	} else if (sCTCPMessage.Compare("PING ", 0, 5)) {
		OnPing(sSource, sCTCPMessage.GetSubstring(5));

	// TIME request
	} else if (sCTCPMessage == "TIME") {
		OnTime(sSource);

	// FINGER request
	} else if (sCTCPMessage == "FINGER") {
		OnFinger(sSource);

	// DCC request
	} else if (sCTCPMessage.Compare("DCC ", 0, 4)) {
		OnDCC(sSource, sCTCPMessage.GetSubstring(5));
	}
}

// Process a MODE message
void IRCConnection::ProcessMode(const String &sSource, const String &sTarget, char *pszParams[])
{
	// Concatenate mode string
	char szMode[1024] = "";
	for (int i=2; i<32; i++) {
		if (!pszParams[i]) break;
		if (i>2) strcat(szMode, " ");
		strcat(szMode, pszParams[i]);
	}

	// Fire mode event
	OnMode(sSource, sTarget, szMode);

	// Has the mode of a channel been set?
	if (sTarget[static_cast<uint32>(0)] == '#') {
		// Get mode string
		const String &sChannel = sTarget;
		const char *pszMode = pszParams[3];
		if (!pszMode) return;
		if (pszMode[0] != '+' && pszMode[0] != '-') return;

		// Loop over mode string
		int  nParam = 4;
		bool bSet = true;
		for (int i=0; i<static_cast<int>(strlen(pszMode)); i++) {
			// Set mode
			if (pszMode[i] == '+') {
				bSet = true;

			// Remove mode
			} else if (pszMode[i] == '-') {
				bSet = false;

			// Operator
			} else if (pszMode[i] == 'o') {
				if (!pszParams[nParam]) return;
				// [TODO] Test this!!!
				Channel *pChannel = GetChannel(sChannel);
				if (pChannel) {
					User *pUser = pChannel->GetUser(pszParams[nParam]);
					if (pUser) pUser->SetOp(bSet);
				}
				OnOp(sTarget, sSource, pszParams[nParam], bSet);
				nParam++;

			// Voice
			} else if (pszMode[i] == 'v') {
				if (!pszParams[nParam]) return;
				// [TODO] Test this!!!
				Channel *pChannel = GetChannel(sChannel);
				if (pChannel) {
					User *pUser = pChannel->GetUser(pszParams[nParam]);
					if (pUser) pUser->SetVoice(bSet);
				}
				OnVoice(sTarget, sSource, pszParams[nParam], bSet);
				nParam++;

			// Channel key
			} else if (pszMode[i] == 'k') {
				if (!pszParams[nParam]) return;
				OnSetChannelKey(sTarget, sSource, pszParams[nParam], bSet);
				nParam++;

			// Channel limit
			} else if (pszMode[i] == 'l') {
				int nLimit = -1;
				if (bSet) {
					if (!pszParams[nParam]) return;
					nLimit = atoi(pszParams[nParam]);
					nParam++;
				}
				OnSetChannelLimit(sTarget, sSource, nLimit);

			// Ban
			} else if (pszMode[i] == 'b') {
				if (!pszParams[nParam]) return;
				OnBan(sTarget, sSource, pszParams[nParam], bSet);
				nParam++;

			// Topic protection
			} else if (pszMode[i] == 't') {
				OnSetTopicProtection(sTarget, sSource, bSet);

			// No External Messages
			} else if (pszMode[i] == 'n') {
				OnSetNoExternalMessages(sTarget, sSource, bSet);

			// Invite
			} else if (pszMode[i] == 'i') {
				OnSetInviteOnly(sTarget, sSource, bSet);

			// Moderated
			} else if (pszMode[i] == 'm') {
				OnSetModerated(sTarget, sSource, bSet);

			// Private
			} else if (pszMode[i] == 'p') {
				OnSetPrivate(sTarget, sSource, bSet);

			// Secret
			} else if (pszMode[i] == 's') {
				OnSetSecret(sTarget, sSource, bSet);
			}
		}
	}
}

Channel *IRCConnection::GetChannel(uint32 nChannel)
{
	return m_lstChannels[nChannel];
}

Channel *IRCConnection::GetChannel(const String &sChannel)
{
	// Search for channel
	Iterator<Channel*> cIterator = m_lstChannels.GetIterator();
	while (cIterator.HasNext()) {
		Channel *pChannel = cIterator.Next();
		if (pChannel->GetName() == sChannel) {
			// Return channel
			return pChannel;
		}
	}

	// Channel not found
	return nullptr;
}

// Add a channel
bool IRCConnection::AddChannel(const String &sChannel)
{
	// Check if channel is already there
	if (GetChannel(sChannel)) return false; // Error!
	else {
		// Create new channel
		m_lstChannels.Add(new Channel(sChannel));

		// Done
		return true;
	}
}

// Remove a channel
void IRCConnection::RemoveChannel(const String &sChannel)
{
	// Search for channel
	Iterator<Channel*> cIterator = m_lstChannels.GetIterator();
	while (cIterator.HasNext()) {
		Channel *pChannel = cIterator.Next();
		if (pChannel->GetName() == sChannel) {
			// Delete channel
			m_lstChannels.Remove(pChannel);
			return;
		}
	}
}

void IRCConnection::RemoveAllChannels()
{
	// Delete all channels
	{
		Iterator<Channel*> cIterator = m_lstChannels.GetIterator();
		while (cIterator.HasNext())
			delete cIterator.Next();
	}
	m_lstChannels.Clear();
}


//[-------------------------------------------------------]
//[ Protected virtual functions                           ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sends a command string to the IRC server
*/
int IRCConnection::SendCommand(const String &sCommand)
{
	// Just send the command as default implementation
	return Send(sCommand);
}

// A raw message from the IRC server
void IRCConnection::OnIRCMessage(const String &sMessage)
{
}

// An unknown message
void IRCConnection::OnUnknownMessage(const String &sMessage)
{
}

// A server message
void IRCConnection::OnServerMessage(const String &sSource, int nCmd, char *pszParams[])
{
	// [TEST]
	printf("--");
	for (int i=3; i<32; i++) {
		if (pszParams[i]) printf(" %s", pszParams[i]);
	}
	printf("\n");
}

// A CTCP message
void IRCConnection::OnCTCPMessage(const String &sSource, const String &sMessage)
{
	// [TEST]
	printf("CTCP: Received '%s' from %s\n", sMessage.GetASCII(), sSource.GetASCII());
}

// A NOTICE AUTH message
void IRCConnection::OnNoticeAuth(const String &sMessage)
{
	// [TEST]
	printf("!! %s\n", sMessage.GetASCII());
}

// A PING request from the server
void IRCConnection::OnServerPing(const String &sMessage)
{
	// Send PONG
	SendCommand("PONG :" + sMessage);

	// [TEST]
	printf("PING ... PONG\n");
}

// A user has joined a channel
void IRCConnection::OnJoin(const String &sChannel, const String &sSource, const String &sUser)
{
	// [TEST]
	printf("%s [%s] joined %s\n", sSource.GetASCII(), sUser.GetASCII(), sChannel.GetASCII());
}

// A user has part a channel
void IRCConnection::OnPart(const String &sChannel, const String &sSource)
{
	// [TEST]
	printf("%s parted %s\n", sSource.GetASCII(), sChannel.GetASCII());
}

// A user has quit the server
void IRCConnection::OnQuit(const String &sSource, const String &sReason)
{
	// [TEST]
	printf("%s has quit IRC (%s)\n", sSource.GetASCII(), sReason.GetASCII());
}

// A user has changed it's nick
void IRCConnection::OnNick(const String &sSource, const String &sNick)
{
	// [TEST]
	printf("%s has changed it's nick to %s\n", sSource.GetASCII(), sNick.GetASCII());
}

// A user has been kicked
void IRCConnection::OnKick(const String &sChannel, const String &sSource, const String &sTarget, const String &sReason)
{
	// [TEST]
	printf("%s has kicked %s from %s (%s)\n", sSource.GetASCII(), sTarget.GetASCII(), sChannel.GetASCII(), sReason.GetASCII());
}

// A user has changed the mode
void IRCConnection::OnMode(const String &sSource, const String &sTarget, const String &sMode)
{
	// [TEST]
	printf("%s sets mode to %s: %s\n", sSource.GetASCII(), sTarget.GetASCII(), sMode.GetASCII());
}

// Mode change: operator
void IRCConnection::OnOp(const String &sChannel, const String &sSource, const String &sTarget, bool bOp)
{
	// [TEST]
	if (bOp) printf("%s gives channel operator status to %s on %s\n",   sSource.GetASCII(), sTarget.GetASCII(), sChannel.GetASCII());
	else	 printf("%s takes channel operator status from %s on %s\n", sSource.GetASCII(), sTarget.GetASCII(), sChannel.GetASCII());
}

// Mode change: voice
void IRCConnection::OnVoice(const String &sChannel, const String &sSource, const String &sTarget, bool bVoice)
{
	// [TEST]
	if (bVoice) printf("%s gives voice to %s on %s\n",   sSource.GetASCII(), sTarget.GetASCII(), sChannel.GetASCII());
	else		printf("%s takes voice from %s on %s\n", sSource.GetASCII(), sTarget.GetASCII(), sChannel.GetASCII());
}

// Mode change: ban
void IRCConnection::OnBan(const String &sChannel, const String &sSource, const String &sHostmask, bool bBan)
{
	// [TODO] Test this
}

// Mode change: channel key
void IRCConnection::OnSetChannelKey(const String &sChannel, const String &sSource, const String &sKey, bool bKey)
{
	// [TEST]
	if (bKey) printf("%s sets channel key on %s to %s\n",     sSource.GetASCII(), sChannel.GetASCII(), sKey.GetASCII());
	else	  printf("%s removes channel key from %s (%s)\n", sSource.GetASCII(), sChannel.GetASCII(), sKey.GetASCII());
}

// Mode change: channel limit
void IRCConnection::OnSetChannelLimit(const String &sChannel, const String &sSource, int nLimit)
{
	// [TEST]
	if (nLimit == -1) printf("%s removes channel limit from %s\n", sSource.GetASCII(), sChannel.GetASCII());
	else			  printf("%s set channel limit on %s to %d\n", sSource.GetASCII(), sChannel.GetASCII(), nLimit);
}

// Mode change: channel topic protection
void IRCConnection::OnSetTopicProtection(const String &sChannel, const String &sSource, bool bTopicProtection)
{
	// [TEST]
	printf("%s sets topic protection on %s %s\n", sSource.GetASCII(), sChannel.GetASCII(), bTopicProtection ? "on" : "off");
}

// Mode change: channel no external messages
void IRCConnection::OnSetNoExternalMessages(const String &sChannel, const String &sSource, bool bNoExternalMessages)
{
	// [TEST]
	printf("%s sets no external messages on %s %s\n", sSource.GetASCII(), sChannel.GetASCII(), bNoExternalMessages ? "on" : "off");
}

// Mode change: channel invite only
void IRCConnection::OnSetInviteOnly(const String &sChannel, const String &sSource, bool bInviteOnly)
{
	// [TEST]
	printf("%s sets invite only on %s %s\n", sSource.GetASCII(), sChannel.GetASCII(), bInviteOnly ? "on" : "off");
}

// Mode change: channel moderated
void IRCConnection::OnSetModerated(const String &sChannel, const String &sSource, bool bModerated)
{
	// [TEST]
	printf("%s sets moderated on %s %s\n", sSource.GetASCII(), sChannel.GetASCII(), bModerated ? "on" : "off");
}

// Mode change: channel private
void IRCConnection::OnSetPrivate(const String &sChannel, const String &sSource, bool bPrivate)
{
	// [TEST]
	printf("%s sets private on %s %s\n", sSource.GetASCII(), sChannel.GetASCII(), bPrivate ? "on" : "off");
}

// Mode change: channel secret
void IRCConnection::OnSetSecret(const String &sChannel, const String &sSource, bool bSecret)
{
	// [TEST]
	printf("%s sets secret on %s %s\n", sSource.GetASCII(), sChannel.GetASCII(), bSecret ? "on" : "off");
}

// A user has invited another user to join a channel
void IRCConnection::OnInvite(const String &sChannel, const String &sSource, const String &sTarget)
{
	// [TEST]
	printf("%s has invited %s to join %s\n", sSource.GetASCII(), sTarget.GetASCII(), sChannel.GetASCII());
}

// A user has changed the topic
void IRCConnection::OnTopic(const String &sChannel, const String &sSource, const String &sTopic, const Time &cTime, bool bChanged)
{
	// [TEST]
	if (!sTopic.GetLength()) {
		printf("%s has no topic\n", sChannel.GetASCII());
	} else if (bChanged) {
		printf("%s sets the topic of %s to '%s' at '%s'\n", sSource.GetASCII(), sChannel.GetASCII(), sTopic.GetASCII(), cTime.ToString().GetASCII());
	} else {
		printf("topic of %s is '%s', set by %s at '%s'\n", sChannel.GetASCII(), sTopic.GetASCII(), sSource.GetASCII(), cTime.ToString().GetASCII());
	}
}

// A channel has sent it's user list (use GetChannel(), GetUser())
void IRCConnection::OnUserList(const String &sChannel)
{
	// [TEST]
//	PrintUsers(sChannel);
}

// A notice has been sent
void IRCConnection::OnNotice(const String &sSource, const String &sTarget, const String &sMessage)
{
	// [TEST]
	printf("-%s- %s\n", sSource.GetASCII(), sMessage.GetASCII());
}

// A channel message has been sent
void IRCConnection::OnMessage(const String &sChannel, const String &sSource, const String &sMessage)
{
	// [TEST]
	printf("%s <%s> %s\n", sChannel.GetASCII(), sSource.GetASCII(), sMessage.GetASCII());
}

// A private message has been sent
void IRCConnection::OnPrivateMessage(const String &sSource, const String &sMessage)
{
	// [TEST]
	printf("PRIV <%s> %s\n", sSource.GetASCII(), sMessage.GetASCII());
}

// CTCP VERSION Request
void IRCConnection::OnVersion(const String &sSource)
{
	// Replay to VERSION
	SendCommand("NOTICE " + sSource + " :\1VERSION " + "IRC-Test 0.2" + "\1");

	// [TEST]
	printf("received a VERSION request from %s\n", sSource.GetASCII());
}

// CTCP USERINFO Request
void IRCConnection::OnUserInfo(const String &sSource)
{
	// [TEST]
	printf("received a USERINFO request from %s\n", sSource.GetASCII());
}

// CTCP CLIENTINFO Request
void IRCConnection::OnClientInfo(const String &sSource)
{
	// [TEST]
	printf("received a CLIENTINFO request from %s\n", sSource.GetASCII());
}

// CTCP ACTION Request
void IRCConnection::OnAction(const String &sChannel, const String &sSource, const String &sAction)
{
	// [TEST]
	printf("%s * %s %s\n", sChannel.GetASCII(), sSource.GetASCII(), sAction.GetASCII());
}

// CTCP PING Request
void IRCConnection::OnPing(const String &sSource, const String &sMessage)
{
	// Reply to PING
	SendCommand("NOTICE " + sSource + " :\1PING " + sMessage + "\1");

	// [TEST]
	printf("received a PING request from %s: '%s'\n", sSource.GetASCII(), sMessage.GetASCII());
}

// CTCP TIME Request
void IRCConnection::OnTime(const String &sSource)
{
	// Replay to TIME
	SendCommand("NOTICE " + sSource + " :\1TIME " + "Too late for tea :-)" + "\1");

	// [TEST]
	printf("received a TIME request from %s\n", sSource.GetASCII());
}

// CTCP FINGER Request
void IRCConnection::OnFinger(const String &sSource)
{
	// [TEST]
	printf("received a FINGER request from %s\n", sSource.GetASCII());
}

// CTCP DCC Request
void IRCConnection::OnDCC(const String &sSource, const String &sMessage)
{
	// [TEST]
	printf("received a DCC request from %s: '%s'\n", sSource.GetASCII(), sMessage.GetASCII());
}


//[-------------------------------------------------------]
//[ Protected virtual PLGeneral::Connection functions     ]
//[-------------------------------------------------------]
void IRCConnection::OnConnect()
{
	// Initialize buffer
	m_cBuffer.Allocate(4096);

	// [TEST]
	printf("IRC Client Started\n");
}

void IRCConnection::OnDisconnect()
{
	// Clear buffer
	m_cBuffer.Clear();

	// [TEST]
	printf("IRC Client Shutdown\n");
}

void IRCConnection::OnReceive(const char *pBuffer, uint32 nSize)
{
	if (pBuffer) {
		// Add data to buffer
		m_cBuffer.Add(pBuffer, nSize);

		// Read lines from buffer
		String sLine = m_cBuffer.GetLine();
		while (sLine.GetLength()) {
			// Process IRC message
			ProcessIRCMessage(sLine);

			// Next line
			sLine = m_cBuffer.GetLine();
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLIRC
