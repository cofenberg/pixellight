/*********************************************************\
 *  File: XmlTextView.cpp                                *
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
#include <PLGeneral/File/Url.h>
#include "PLXmlText/XmlText/XmlTextView.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGui;
namespace PLXmlText {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(XmlTextView)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String XmlTextView::GetFilename() const
{
	return m_sFilename;
}

void XmlTextView::SetFilename(const String &sValue)
{
	if (m_sFilename != sValue) {
		m_sFilename = sValue;
		Load(m_sFilename);
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XmlTextView::XmlTextView(Widget *pParent) : Widget(pParent),
	Filename(this),
	m_cRenderer(*GetGui())
{
}

/**
*  @brief
*    Load XML file
*/
void XmlTextView::Load(const String &sFilename)
{
	// Save file name and document root
	m_sFilename = sFilename;
	m_sDocumentRoot = Url(m_sFilename).CutFilename();

	// Load XML file
	m_cXmlText.m_pXmlText = this;
	m_cXmlText.Load(sFilename);

	// Redraw
	Redraw();
}

/**
*  @brief
*    Get document root
*/
String XmlTextView::GetDocumentRoot() const
{
	// Return path
	return m_sDocumentRoot;
}

/**
*  @brief
*    Get size of content
*/
Vector2i XmlTextView::GetContentSize() const
{
	// Return size of loaded XmlText
	return m_cXmlText.GetSize();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
XmlTextView::~XmlTextView()
{
}


//[-------------------------------------------------------]
//[ Public virtual Window functions                       ]
//[-------------------------------------------------------]
void XmlTextView::OnDraw(Graphics &cGraphics)
{
	// Call base implementation
	Widget::OnDraw(cGraphics);

	// Draw XmlText
	m_cRenderer.Init(cGraphics, GetSize());
	m_cXmlText.Draw(m_cRenderer);
	m_cRenderer.Finish();
}

void XmlTextView::OnSize(const Vector2i &vSize)
{
	// Call base implementation
	Widget::OnSize(vSize);

	// Redraw HTML
	Redraw();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLXmlText
