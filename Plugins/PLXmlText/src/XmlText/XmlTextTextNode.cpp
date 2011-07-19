/*********************************************************\
 *  File: XmlTextTextNode.cpp                            *
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
#include <PLCore/String/RegEx.h>
#include <PLCore/Xml/XmlText.h>
#include "PLXmlText/XmlText/XmlTextRenderer.h"
#include "PLXmlText/XmlText/XmlTextTextNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLXmlText {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XmlTextTextNode::XmlTextTextNode(XmlTextElement *pParent) : XmlTextElement(pParent)
{
}

/**
*  @brief
*    Destructor
*/
XmlTextTextNode::~XmlTextTextNode()
{
}


//[-------------------------------------------------------]
//[ Protected virtual XmlTextElement functions            ]
//[-------------------------------------------------------]
void XmlTextTextNode::OnParse(XmlNode &cXmlNode)
{
	// Get XML text
	XmlText &cXmlText = static_cast<XmlText&>(cXmlNode);
	m_sText = cXmlText.GetValue();
}

void XmlTextTextNode::OnDraw(XmlTextRenderer &cRenderer)
{
	// Get text word for word
	RegEx cRegEx("\\s*([^\\s]+)");
	uint32 nParsePos = 0;
	while (cRegEx.Match(m_sText, nParsePos)) {
		// Get next word
		nParsePos = cRegEx.GetPosition();
		String sWord = cRegEx.GetResult(0);

		// Draw word
		cRenderer.DrawText(sWord);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLXmlText
