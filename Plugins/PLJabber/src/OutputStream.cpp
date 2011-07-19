/*********************************************************\
 *  File: OutputStream.cpp                               *
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
#include <PLCore/Xml/XmlDeclaration.h>
#include <PLCore/Xml/XmlElement.h>
#include "PLJabber/JabberConnection.h"
#include "PLJabber/OutputStream.h"


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
OutputStream::OutputStream(JabberConnection &cJabberConnection) :
	m_pJabberConnection(&cJabberConnection),
	m_pStream(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
OutputStream::~OutputStream()
{
}

/**
*  @brief
*    Opens the XML stream
*/
void OutputStream::OpenStream(const String &sServer)
{
	// XML declaration ('<?xml version='1.0' ?>')
	XmlDeclaration *pDeclaration = new XmlDeclaration("1.0", "", "");
	m_cXml.LinkEndChild(*pDeclaration);
	String sStream = pDeclaration->ToString();
	m_pJabberConnection->Send(sStream.GetASCII(), sStream.GetLength());

	// [TODO] Destroy the old m_pStream?

	// Begin stream ('<stream:stream xmlns:stream="http://etherx.jabber.org/streams" to="$sServer" xmlns="jabber:client">')
	m_pStream = new XmlElement("stream:stream");
	m_pStream->SetAttribute("xmlns:stream", "http://etherx.jabber.org/streams");
	m_pStream->SetAttribute("to", sServer);
	m_pStream->SetAttribute("xmlns", "jabber:client");
	m_cXml.LinkEndChild(*m_pStream);
	sStream = String("<stream:stream xmlns:stream=\"http://etherx.jabber.org/streams\" to=\"") + sServer + "\" xmlns=\"jabber:client\">";
	m_pJabberConnection->Send(sStream.GetASCII(), sStream.GetLength());
}

/**
*  @brief
*    Sends an XML element
*/
void OutputStream::SendElement(const XmlElement &cElement) const
{
	// Add node to XML document
	if (m_pStream)
		m_pStream->InsertEndChild(cElement);

	// Send to stream
	String sStream = ((XmlElement&)cElement).ToString();
	m_pJabberConnection->Send(sStream.GetASCII(), sStream.GetLength());
}

/**
*  @brief
*    Closes the XML stream
*/
void OutputStream::CloseStream() const
{
	// End stream ('</stream:stream>')
	String sStream = "</stream:stream>";
	m_pJabberConnection->Send(sStream.GetASCII(), sStream.GetLength());
}

/**
*  @brief
*    Save the complete XML stream to a file
*/
void OutputStream::Save(const String &sFilename)
{
	// Save to file
	m_cXml.Save(sFilename);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
OutputStream::OutputStream(const OutputStream &cSource) :
	m_pJabberConnection(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
OutputStream &OutputStream::operator =(const OutputStream &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLJabber
