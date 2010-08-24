/*********************************************************\
 *  File: XmlTextText.cpp                                *
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
#include <PLGeneral/Xml/XmlElement.h>
#include <PLGeneral/Xml/XmlAttribute.h>
#include <PLGui/Gui/Resources/Font.h>
#include "PLXmlText/XmlText/XmlTextRenderer.h"
#include "PLXmlText/XmlText/XmlTextText.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGraphics;
using namespace PLGui;
namespace PLXmlText {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XmlTextText::XmlTextText(bool bParagraph, XmlTextElement *pParent) : XmlTextElement(pParent),
	m_bParagraph(bParagraph),
	m_cTextColor(Color4::Transparent),
	m_cBgColor(Color4::Transparent),
	m_nFontSize(-1),
	m_nHAlign(XmlTextRenderer::HAlignUnknown),
	m_nVAlign(XmlTextRenderer::VAlignUnknown)
{
}

/**
*  @brief
*    Destructor
*/
XmlTextText::~XmlTextText()
{
}


//[-------------------------------------------------------]
//[ Protected virtual XmlTextElement functions            ]
//[-------------------------------------------------------]
void XmlTextText::OnParse(XmlNode &cXmlNode)
{
	// Is this an XML element?
	if (cXmlNode.GetType() == XmlNode::Element) {
		// Get XML element
		XmlElement &cXmlElement = (XmlElement&)cXmlNode;

		// Parse attributes
		XmlAttribute *pAttribute = cXmlElement.GetFirstAttribute();
		while (pAttribute) {
			// Get name and value
			String sName  = pAttribute->GetName();
			String sValue = pAttribute->GetValue();

			// Save attribute
			if (sName.CompareNoCase("Color")) {
				// Text color
				m_cTextColor = GetColor(sValue);
			} else if (sName.CompareNoCase("BgColor")) {
				// Background color
				m_cBgColor = GetColor(sValue);
			} else if (sName.CompareNoCase("Font")) {
				// Font name
				m_sFont = sValue;
			} else if (sName.CompareNoCase("FontSize")) {
				// Font size
				m_nFontSize = sValue.GetInt();
			} else if (sName.CompareNoCase("HAlign")) {
					 if (sValue.CompareNoCase("Left"))		m_nHAlign = XmlTextRenderer::HAlignLeft;
				else if (sValue.CompareNoCase("Right"))		m_nHAlign = XmlTextRenderer::HAlignRight;
				else if (sValue.CompareNoCase("Center"))	m_nHAlign = XmlTextRenderer::HAlignCenter;
				else if (sValue.CompareNoCase("Justify"))	m_nHAlign = XmlTextRenderer::HAlignJustify;
				else										m_nHAlign = XmlTextRenderer::HAlignUnknown;
			} else if (sName.CompareNoCase("VAlign")) {
					 if (sValue.CompareNoCase("Top"))		m_nVAlign = XmlTextRenderer::VAlignTop;
				else if (sValue.CompareNoCase("Bottom"))	m_nVAlign = XmlTextRenderer::VAlignBottom;
				else if (sValue.CompareNoCase("Middle"))	m_nVAlign = XmlTextRenderer::VAlignMiddle;
				else										m_nVAlign = XmlTextRenderer::VAlignUnknown;
			}

			// Next attribute
			pAttribute = pAttribute->GetNext();
		}
	}
}

void XmlTextText::OnDraw(XmlTextRenderer &cRenderer)
{
	// Start paragraph
	if (m_bParagraph) {
		cRenderer.AddLineBreak();
	}

	// Set renderer state
	Color4 cOldTextColor = cRenderer.GetTextColor();
	if (!m_cTextColor.IsTransparent()) cRenderer.SetTextColor(m_cTextColor);
	Color4 cOldBgColor = cRenderer.GetBgColor();
	if (!m_cBgColor.IsTransparent()) cRenderer.SetBgColor(m_cBgColor);
	Font *pOldFont = cRenderer.GetFont() ? new Font(*cRenderer.GetFont()) : NULL;
	if (m_sFont.GetLength() || m_nFontSize > -1) cRenderer.SetFont(m_sFont, m_nFontSize);
	XmlTextRenderer::HAlign nOldHAlign = cRenderer.GetHAlign();
	if (m_nHAlign != XmlTextRenderer::HAlignUnknown) cRenderer.SetHAlign(m_nHAlign);
	XmlTextRenderer::VAlign nOldVAlign = cRenderer.GetVAlign();
	if (m_nVAlign != XmlTextRenderer::VAlignUnknown) cRenderer.SetVAlign(m_nVAlign);

	// Draw children
	DrawChildren(cRenderer);

	// End paragraph
	if (m_bParagraph) {
		cRenderer.AddLineBreak();
		cRenderer.AddVerticalSpace(10);
	}

	// Restore renderer state
	cRenderer.SetTextColor(cOldTextColor);
	cRenderer.SetBgColor(cOldBgColor);
	cRenderer.SetFont(pOldFont);
	cRenderer.SetHAlign(nOldHAlign);
	cRenderer.SetVAlign(nOldVAlign);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLXmlText
