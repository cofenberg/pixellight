/*********************************************************\
 *  File: JabberID.cpp                                   *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/RegEx.h>
#include "PLJabber/JabberID.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLJabber {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
JabberID::JabberID(const String &sJabberID)
{
	// Set Jabber ID
	SetValue(sJabberID);
}

/**
*  @brief
*    Destructor
*/
JabberID::~JabberID()
{
}

/**
*  @brief
*    Get Jabber ID
*/
String JabberID::GetValue() const
{
	// Return Jabber ID
	return m_sJabberID;
}

/**
*  @brief
*    Set Jabber ID
*/
void JabberID::SetValue(const String &sJabberID)
{
	// Set Jabber ID
	m_sJabberID = sJabberID;

	// Parse Jabber ID
	ParseJabberID();
}

/**
*  @brief
*    Get user name
*/
String JabberID::GetUserName() const
{
	// Return user name
	return m_sUserName;
}

/**
*  @brief
*    Set user name
*/
void JabberID::SetUserName(const String &sUserName)
{
	// Set user name
	m_sUserName = sUserName;

	// Update Jabber ID
	ComposeJabberID();
}

/**
*  @brief
*    Get host name
*/
String JabberID::GetHostName() const
{
	// Return host name
	return m_sHostName;
}

/**
*  @brief
*    Set host name
*/
void JabberID::SetHostName(const String &sHostName)
{
	// Set host name
	m_sHostName = sHostName;

	// Update Jabber ID
	ComposeJabberID();
}

/**
*  @brief
*    Get resource
*/
String JabberID::GetRessource() const
{
	// Return resource
	return m_sRessource;
}

/**
*  @brief
*    Set resource
*/
void JabberID::SetRessource(const String &sRessource)
{
	// Set resource
	m_sRessource = sRessource;

	// Update Jabber ID
	ComposeJabberID();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Parses the jabber ID to determine it's components (user name, host name and resource)
*/
void JabberID::ParseJabberID()
{
	// Parse Jabber ID
	static RegEx cRegEx("^((\\w*)@)?(\\w*)(/(\\w*))?$");
	if (cRegEx.Match(m_sJabberID)) {
		// Jabber ID is valid
		m_sUserName  = cRegEx.GetResult(1);
		m_sHostName  = cRegEx.GetResult(2);
		m_sRessource = cRegEx.GetResult(4);
	} else {
		// Jabber ID is NOT valid
		m_sJabberID  = "";
		m_sUserName  = "";
		m_sHostName  = "";
		m_sRessource = "";
	}
}

/**
*  @brief
*    Composes the jabber ID from it's components (user name, host name and resource)
*/
void JabberID::ComposeJabberID()
{
	// Compose jabber ID from components
	m_sJabberID = (m_sUserName.GetLength() ? (m_sUserName + '@') : "") +
				   m_sHostName +
				  (m_sRessource.GetLength() ? ('/' + m_sRessource) : "");
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLJabber
