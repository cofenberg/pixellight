/*********************************************************\
 *  File: XmlTextSection.cpp                             *
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
#include <PLCore/Xml/XmlElement.h>
#include <PLCore/Xml/XmlAttribute.h>
#include <PLGui/Gui/Resources/Graphics.h>
#include "PLXmlText/XmlText/XmlTextRenderer.h"
#include "PLXmlText/XmlText/XmlTextSection.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLGraphics;
using namespace PLMath;
using namespace PLGui;
namespace PLXmlText {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XmlTextSection::XmlTextSection(XmlTextElement *pParent) : XmlTextElement(pParent),
	m_nPaddingLeft(0),
	m_nPaddingRight(0),
	m_nPaddingTop(0),
	m_nPaddingBottom(0),
	m_cBgColor(Color4::Transparent),
	m_fAlpha(1.0f),
	m_nBorder(0)
{
}

/**
*  @brief
*    Destructor
*/
XmlTextSection::~XmlTextSection()
{
}


//[-------------------------------------------------------]
//[ Protected virtual XmlTextElement functions            ]
//[-------------------------------------------------------]
void XmlTextSection::OnParse(XmlNode &cXmlNode)
{
	// Is this an XML element?
	if (cXmlNode.GetType() == XmlNode::Element) {
		// Get XML element
		XmlElement &cXmlElement = static_cast<XmlElement&>(cXmlNode);

		// Parse attributes
		XmlAttribute *pAttribute = cXmlElement.GetFirstAttribute();
		while (pAttribute) {
			// Get name and value
			String sName  = pAttribute->GetName();
			String sValue = pAttribute->GetValue();

			// Save attribute
			if (sName.CompareNoCase("X")) {
				// X
				m_vPos.x = sValue.GetInt();
			} else if (sName.CompareNoCase("Y")) {
				// Y
				m_vPos.y = sValue.GetInt();
			} else if (sName.CompareNoCase("Width")) {
				// Width
				m_vSize.x = sValue.GetInt();
			} else if (sName.CompareNoCase("Height")) {
				// Height
				m_vSize.y = sValue.GetInt();
			} else if (sName.CompareNoCase("Padding")) {
				// Padding on all sides
				m_nPaddingLeft	 = sValue.GetInt();
				m_nPaddingRight	 = m_nPaddingLeft;
				m_nPaddingTop	 = m_nPaddingLeft;
				m_nPaddingBottom = m_nPaddingLeft;
			} else if (sName.CompareNoCase("PaddingLeft")) {
				// Padding on left side
				m_nPaddingLeft = sValue.GetInt();
			} else if (sName.CompareNoCase("PaddingRight")) {
				// Padding on right side
				m_nPaddingRight	 = sValue.GetInt();
			} else if (sName.CompareNoCase("PaddingTop")) {
				// Padding on top side
				m_nPaddingTop	 = sValue.GetInt();
			} else if (sName.CompareNoCase("PaddingBottom")) {
				// Padding on bottom side
				m_nPaddingBottom	 = sValue.GetInt();
			} else if (sName.CompareNoCase("BgColor")) {
				// Background color
				m_cBgColor = GetColor(sValue);
			} else if (sName.CompareNoCase("Background")) {
				// Background image
				m_sBackground = sValue;
			} else if (sName.CompareNoCase("Border")) {
				// Border size
				m_nBorder = sValue.GetInt();
			} else if (sName.CompareNoCase("BorderColor")) {
				m_cBorderColor = GetColor(sValue);
			} else if (sName.CompareNoCase("Alpha")) {
				// Alpha transparency
				m_fAlpha = sValue.GetFloat();
			}

			// Next attribute
			pAttribute = pAttribute->GetNext();
		}
	}
}

void XmlTextSection::OnDraw(XmlTextRenderer &cRenderer)
{
	// Set section
	Vector2i vOldSectionPos  = cRenderer.GetSectionPos();
	Vector2i vOldSectionSize = cRenderer.GetSectionSize();
	cRenderer.SetSectionPos (m_vPos  + Vector2i(m_nPaddingLeft, m_nPaddingTop));
	cRenderer.SetSectionSize(m_vSize - Vector2i(m_nPaddingLeft + m_nPaddingRight, m_nPaddingTop + m_nPaddingBottom));

	// Draw background
	if (!m_cBgColor.IsTransparent()) {
		Color4 cColor(m_cBgColor.r, m_cBgColor.g, m_cBgColor.b, m_fAlpha);
		cRenderer.GetGraphics()->DrawBox(cColor, m_vPos, Vector2i(m_vPos.x + m_vSize.x - 1, m_vPos.y + m_vSize.y - 1));
	}

	// Draw background image
	if (m_sBackground.GetLength())
		cRenderer.GetGraphics()->DrawImage(LoadImage(cRenderer.GetGui(), m_sBackground), m_vPos, m_vSize);

	// Draw children
	DrawChildren(cRenderer);

	// Draw border
	if (m_nBorder > 0) {
		cRenderer.GetGraphics()->DrawRect(m_cBorderColor, m_vPos, Vector2i(m_vPos.x + m_vSize.x - 1, m_vPos.y + m_vSize.y - 1), m_nBorder);
	}

	// Restore section
	cRenderer.SetSectionPos (vOldSectionPos);
	cRenderer.SetSectionSize(vOldSectionSize);
}

Vector2i XmlTextSection::OnGetSize() const
{
	// Return size of section
	return m_vSize;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLXmlText
