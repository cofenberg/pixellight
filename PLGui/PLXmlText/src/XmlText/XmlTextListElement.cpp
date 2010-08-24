/*********************************************************\
 *  File: XmlTextListElement.cpp                         *
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
#include "PLXmlText/XmlText/XmlTextRenderer.h"
#include "PLXmlText/XmlText/XmlTextListElement.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLXmlText {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XmlTextListElement::XmlTextListElement(XmlTextElement *pParent) : XmlTextElement(pParent)
{
}

/**
*  @brief
*    Destructor
*/
XmlTextListElement::~XmlTextListElement()
{
}


//[-------------------------------------------------------]
//[ Protected virtual XmlTextElement functions            ]
//[-------------------------------------------------------]
void XmlTextListElement::OnParse(XmlNode &cXmlNode)
{
}

void XmlTextListElement::OnDraw(XmlTextRenderer &cRenderer)
{
	// Draw bullet
	cRenderer.DrawBullet();

	// Draw children
	DrawChildren(cRenderer);

	// End line
	cRenderer.AddLineBreak();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLXmlText
