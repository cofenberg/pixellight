/*********************************************************\
 *  File: InputStream.cpp                                *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLCore/Xml/XmlElement.h>
#include "PLJabber/JabberConnection.h"
#include "PLJabber/InputStream.h"


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
InputStream::InputStream(JabberConnection &cJabberConnection) :
	m_pJabberConnection(&cJabberConnection),
	m_pStream(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
InputStream::~InputStream()
{
}

/**
*  @brief
*    Parse incoming stream data
*/
void InputStream::ParseStream(const String &sStream)
{
	// Has the document been initialized yet?
	if (!m_pStream) {
		// Parse beginning of document
		m_cXml.Parse(sStream.GetASCII());

		// Get root element
		XmlElement *pRoot = m_cXml.GetRootElement();
		if (pRoot && pRoot->GetValue() == "stream:stream") {
			// Save stream element
			m_pStream = pRoot;

			// Callback function for stream element
			m_pJabberConnection->OnStreamStarted(*m_pStream);
		}
	} else {
		// Parse XML part
		XmlDocument cXml;
		cXml.Parse(sStream.GetASCII());
		XmlElement *pRoot = cXml.GetRootElement();
		if (pRoot) {
			// Add element
			XmlElement *pElement = static_cast<XmlElement*>(pRoot->Clone());
			m_pStream->LinkEndChild(*pElement);

			// Callback function for element
			m_pJabberConnection->OnElement(*pElement);
		}
	}
}

/**
*  @brief
*    Save the complete XML stream to a file
*/
void InputStream::Save(const String &sFilename)
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
InputStream::InputStream(const InputStream &cSource) :
	m_pJabberConnection(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
InputStream &InputStream::operator =(const InputStream &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLJabber
