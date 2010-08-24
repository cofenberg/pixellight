/*********************************************************\
 *  File: JabberConnection.cpp                           *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLGeneral/System/System.h>
#include <PLGeneral/System/Console.h>
#include <PLGeneral/Xml/XmlElement.h>
#include <PLGeneral/Xml/XmlText.h>
#include "PLJabber/JabberConnection.h"


//[-------------------------------------------------------]
//[ Disable warnings                                      ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLJabber {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Create a new Jabber account
*/
void JabberConnection::CreateAccount(const String &sServer, const String &sUsername, const String &sPassword)
{
	// [TODO] Implement
}

/**
*  @brief
*    Log in with an existing Jabber account
*/
void JabberConnection::Login(const String &sServer, const String &sUsername, const String &sPassword)
{
	// Save user data
	m_sUsername = sUsername;
	m_sPassword = sPassword;
	m_sUserID = sUsername + '@' + sServer + "/PLJabber";

	// Set login query
	SendQueryLogin(sUsername, sPassword);
}

/**
*  @brief
*    Log out
*/
void JabberConnection::Logout()
{
	// [TODO] Implement
}

void JabberConnection::GetRoster() const
{
	SendQueryRoster();
}

void JabberConnection::SetPresence(EPresence nPresence, EPresenceShow nShow, const String &sStatus, int nPriority) const
{
	// Type
	String sType = (nPresence == Available) ? "available" : "unavailable";

	// Show
	String sShow;
	switch (nShow) {
		case Away:		sShow = "away"; break;
		case Chat:		sShow = "chat"; break;
		case DND:		sShow = "dnd"; break;
		case Normal:	sShow = "normal"; break;
		case XA:		sShow = "xa"; break;
	}

	// Send presence element
	SendPresence("", "", sType, sShow, sStatus, nPriority);
}

void JabberConnection::Subscribe(const String &sTo) const
{
	// Send presence element
	SendPresence(m_sUserID, sTo, "subscribe", "", "", 0);
}

void JabberConnection::Unsubscribe(const String &sTo) const
{
	// Send presence element
	SendPresence(m_sUserID, sTo, "ubsubscribe", "", "", 0);
}

void JabberConnection::AllowSubscription(const String &sTo) const
{
	// Send presence element
	SendPresence(m_sUserID, sTo, "subscribed", "", "", 0);
}

void JabberConnection::RevokeSubscription(const String &sTo) const
{
	// Send presence element
	SendPresence(m_sUserID, sTo, "ubsubscribed", "", "", 0);
}

void JabberConnection::Message(const String &sTo, const String &sSubject, const String &sMessage) const
{
	// Set message
	SendMsg(sTo, sSubject, sMessage);
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
JabberConnection::JabberConnection(JabberClient &cClient) : Connection((PLGeneral::Host&)cClient),
	m_cInput(*this),
	m_cOutput(*this)
{
}

/**
*  @brief
*    Destructor
*/
JabberConnection::~JabberConnection()
{
}

/**
*  @brief
*    Send an element to the Jabber server
*/
void JabberConnection::SendElement(const XmlElement &cElement) const
{
	// [DEBUG] Output to console
	System::GetInstance()->GetConsole().Print("SEND: " + ((XmlElement&)cElement).ToString() + '\n');

	// Send to XML output stream
	m_cOutput.SendElement(cElement);
}

void JabberConnection::SendQueryLogin(const String &sUsername, const String &sPassword) const
{
	// Info/Query: "get"
	XmlElement cIQ("iq");
	cIQ.SetAttribute("type", "get");
	cIQ.SetAttribute("to", m_sServer);
	cIQ.SetAttribute("id", "auth-info");
		// Query: "jabber:iq:auth"
		XmlElement cQuery("query");
		cQuery.SetAttribute("xmlns", "jabber:iq:auth");
			// Username
			XmlElement cUsername("username");
				XmlText cText(sUsername);
				cUsername.InsertEndChild(cText);
			cQuery.InsertEndChild(cUsername);
		cIQ.InsertEndChild(cQuery);

	// Send element
	SendElement(cIQ);
}

void JabberConnection::SendLogin(const String &sUsername, const String &sPassword) const
{
	String sResource = "PLJabber";

	// Info/Query: "set"
	XmlElement cIQ("iq");
	cIQ.SetAttribute("type", "set");
	cIQ.SetAttribute("to", m_sServer);
	cIQ.SetAttribute("id", "auth-set");
		// Query: "jabber:iq:auth"
		XmlElement cQuery("query");
		cQuery.SetAttribute("xmlns", "jabber:iq:auth");
			// Username
			XmlElement cUsername("username");
				XmlText cText(sUsername);
				cUsername.InsertEndChild(cText);
			cQuery.InsertEndChild(cUsername);
			// Password
			XmlElement cPassword("password");
				XmlText cText2(sPassword);
				cPassword.InsertEndChild(cText2);
			cQuery.InsertEndChild(cPassword);
			// Resource
			XmlElement cResource("resource");
				XmlText cText3(sResource);
				cResource.InsertEndChild(cText3);
			cQuery.InsertEndChild(cResource);
		cIQ.InsertEndChild(cQuery);

	// Send element
	SendElement(cIQ);
}

void JabberConnection::SendQueryRoster() const
{
	// Info/Query: "get"
	XmlElement cIQ("iq");
	cIQ.SetAttribute("type", "get");
	cIQ.SetAttribute("id", "roster");
		// Query: "jabber:iq:roster"
		XmlElement cQuery("query");
		cQuery.SetAttribute("xmlns", "jabber:iq:roster");
		cIQ.InsertEndChild(cQuery);

	// Send element
	SendElement(cIQ);
}

void JabberConnection::SendMsg(const String &sTo, const String &sSubject, const String &sMessage) const
{
	// Message
	XmlElement cMessage("message");
	cMessage.SetAttribute("type", "normal");
	cMessage.SetAttribute("to", sTo);
		// Subject
		XmlElement cSubject("subject");
			XmlText cSubjectText(sSubject);
			cSubject.InsertEndChild(cSubjectText);
		cMessage.InsertEndChild(cSubject);
		// Body
		XmlElement cBody("body");
			XmlText cBodyText(sMessage);
			cBody.InsertEndChild(cBodyText);
		cMessage.InsertEndChild(cBody);
		// Thread
		// [TODO]

	// Send element
	SendElement(cMessage);
}

/**
*  @brief
*    Send a presence element
*/
void JabberConnection::SendPresence(const String &sFrom, const String &sTo, const String &sType, const String &sShow, const String &sStatus, int nPriority) const
{
	// Message
	XmlElement cPresence("presence");
	cPresence.SetAttribute("type", sType);
	if (sTo.GetLength())	cPresence.SetAttribute("to", sTo);
	if (sFrom.GetLength())	cPresence.SetAttribute("from", sFrom);
		if (sType == "available" || sType == "unavailable") {
			// Show
			XmlElement cShow("show");
				XmlText cShowText(sShow);
				cShow.InsertEndChild(cShowText);
			cPresence.InsertEndChild(cShow);
			// Status
			XmlElement cStatus("status");
				XmlText cStatusText(sStatus);
				cStatus.InsertEndChild(cStatusText);
			cPresence.InsertEndChild(cStatus);
			// Priority
			XmlElement cPriority("priority");
				XmlText cPriorityText(String() + nPriority);
				cPriority.InsertEndChild(cPriorityText);
			cPresence.InsertEndChild(cPriority);
		}

	// Send element
	SendElement(cPresence);
}


//[-------------------------------------------------------]
//[ Protected virtual PLGeneral::Connection functions     ]
//[-------------------------------------------------------]
void JabberConnection::OnConnect()
{
	// [DEBUG]
	System::GetInstance()->GetConsole().Print("Jabber Client Started\n");

	// Open XML output stream
	m_sServer = GetHostname();
	m_cOutput.OpenStream(m_sServer);
}

void JabberConnection::OnDisconnect()
{
	// Close XML output stream
	m_cOutput.CloseStream();

	// [DEBUG] Save XML streams
	System::GetInstance()->GetConsole().Print("Jabber Client Shutdown\n");
	m_cOutput.Save("Output.xml");
	m_cInput .Save("Input.xml");
}

void JabberConnection::OnReceive(const char *pBuffer, uint32 nSize)
{
	// Check input
	if (pBuffer && nSize) {
		// Parse XML input stream
		m_cInput.ParseStream(String(pBuffer, true, nSize));
	}
}


//[-------------------------------------------------------]
//[ Protected virtual JabberConnection functions          ]
//[-------------------------------------------------------]
void JabberConnection::OnStreamStarted(const XmlElement &cStream)
{
	// [DEBUG] Output to console
	System::GetInstance()->GetConsole().Print("RECV: " + ((XmlElement&)cStream).ToString() + '\n');

	// Use value of attribute 'from' as the new server name (could be an alias)
	m_sServer = cStream.GetAttribute("from");

	// Save server generated ID
	m_sID = cStream.GetAttribute("id");
}

void JabberConnection::OnElement(const XmlElement &cElement)
{
	// [DEBUG] Output to console
	System::GetInstance()->GetConsole().Print("RECV: " + ((XmlElement&)cElement).ToString() + '\n');

	// Check type of element
	if (cElement.GetValue() == "iq") {
		// Inform/query
		OnInformQuery(cElement);
	} else if (cElement.GetValue() == "message") {
		// Message
		OnMessage(cElement);
	} else if (cElement.GetValue() == "presence") {
		// Presence
		OnPresence(cElement);
	}
}

void JabberConnection::OnInformQuery(const XmlElement &cElement)
{
	// Get attributes
	String sType = cElement.GetAttribute("type");
	String sFrom = cElement.GetAttribute("from");
	String sID   = cElement.GetAttribute("id");

	// Check query
	if (sType == "result" && sID == "auth-info") {
		// Reply for 'auth-info'
		OnAuthInfo(cElement);
	} else if (sType == "result" && sID == "auth") {
		// Reply for 'auth'
		OnAuth(cElement);
	} else if (sType == "result" && sID == "roster") {
		// Reply for 'roster'
		OnRoster(cElement);
	} else if (sType == "error") {
		// Error!
		OnError(cElement);
	}
}

void JabberConnection::OnMessage(const XmlElement &cElement)
{
}

void JabberConnection::OnPresence(const XmlElement &cElement)
{
}

void JabberConnection::OnError(const XmlElement &cElement)
{
}

void JabberConnection::OnAuthInfo(const XmlElement &cElement)
{
	// Now do authentication
	SendLogin(m_sUsername, m_sPassword);
}

void JabberConnection::OnAuth(const XmlElement &cElement)
{
	// Authentication successful
}

void JabberConnection::OnRoster(const XmlElement &cElement)
{
	const XmlNode *pQuery = cElement.GetFirstChildElement();
	for (const XmlNode *pNode=pQuery->GetFirstChild(); pNode; pNode=pNode->GetNextSibling()) {
		if (pNode->GetType() == XmlNode::Element) {
			XmlElement *pElement = (XmlElement*)pNode;
			if (pElement->GetValue() == "item") {
				String sJID  = pElement->GetAttribute("jid");
				String sName = pElement->GetAttribute("name");
				System::GetInstance()->GetConsole().Print("JID  = " + sJID  + '\n');
				System::GetInstance()->GetConsole().Print("Name = " + sName + '\n');
			}
		}
	}

	/*
RECV: <iq id='roster_0' type='result' from='dj@yak/Work'>
        <query xmlns='jabber:iq:roster'>
          <item jid='sabine@yak' name='sabine' subscription='both'>
            <group>Family</group>
          </item>
        </query>
      </iq>
	 */
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLJabber


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
