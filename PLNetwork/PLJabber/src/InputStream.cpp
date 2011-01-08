/*********************************************************\
 *  File: InputStream.cpp                                *
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
#include <PLGeneral/Xml/XmlElement.h>
#include "PLJabber/JabberConnection.h"
#include "PLJabber/InputStream.h"


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
			XmlElement *pElement = (XmlElement*)pRoot->Clone();
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
