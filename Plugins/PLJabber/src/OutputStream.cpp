/*********************************************************\
 *  File: OutputStream.cpp                               *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
