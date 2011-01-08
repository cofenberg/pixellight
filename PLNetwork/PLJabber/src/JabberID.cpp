/*********************************************************\
 *  File: JabberID.cpp                                   *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/RegEx.h>
#include "PLJabber/JabberID.h"


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
*    Get ressource
*/
String JabberID::GetRessource() const
{
	// Return ressource
	return m_sRessource;
}

/**
*  @brief
*    Set ressource
*/
void JabberID::SetRessource(const String &sRessource)
{
	// Set ressource
	m_sRessource = sRessource;

	// Update Jabber ID
	ComposeJabberID();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Parses the jabber ID to determine it's components (user name, host name and ressource)
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
*    Composes the jabber ID from it's components (user name, host name and ressource)
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
