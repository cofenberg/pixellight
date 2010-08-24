/*********************************************************\
 *  File: XmlTextList.cpp                                *
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
#include "PLXmlText/XmlText/XmlTextList.h"


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
XmlTextList::XmlTextList(XmlTextElement *pParent) : XmlTextElement(pParent)
{
}

/**
*  @brief
*    Destructor
*/
XmlTextList::~XmlTextList()
{
}


//[-------------------------------------------------------]
//[ Protected virtual XmlTextElement functions            ]
//[-------------------------------------------------------]
void XmlTextList::OnParse(XmlNode &cXmlNode)
{
}

void XmlTextList::OnDraw(XmlTextRenderer &cRenderer)
{
	// End paragraph
	cRenderer.AddLineBreak();
	cRenderer.AddVerticalSpace(8);

	// Set indent
	int nOldIndent = cRenderer.GetIndent();
	cRenderer.SetIndent(nOldIndent + 10);

	// Draw children
	DrawChildren(cRenderer);

	// Restore indent
	cRenderer.SetIndent(nOldIndent);

	// End paragraph
	cRenderer.AddLineBreak();
	cRenderer.AddVerticalSpace(8);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLXmlText
