/*********************************************************\
 *  File: GraphicsLinux.cpp                              *
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
#include <PLGraphics/Color/Color3.h>
#include <PLGraphics/Color/Color4.h>
#include "PLGui/Gui/Gui.h"
#include "PLGui/Gui/Resources/Graphics.h"
#include "PLGui/Gui/Resources/Image.h"
#include "PLGui/Gui/Resources/Font.h"
#include "PLGui/Backend/Linux/GuiLinux.h"
#include "PLGui/Backend/Linux/GraphicsLinux.h"
#include "PLGui/Backend/Linux/ImageLinux.h"
#include "PLGui/Backend/Linux/FontLinux.h"
#include "PLGui/Backend/Linux/ToolsLinux.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGraphics;
using namespace PLMath;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
GraphicsLinux::GraphicsLinux(::Display *pDisplay, int nScreen, ::Window nWindow) : GraphicsImpl(),
	m_pDisplay(pDisplay),
	m_nScreen(nScreen),
	m_nColorDepth(16),
	m_nWindow(nWindow)
{
	// Get color depth
	m_nColorDepth  = DefaultDepth(pDisplay, nScreen);

	// Create graphics context
	::XGCValues	sGCValues;
	sGCValues.function   = GXcopy;
	sGCValues.foreground = ToolsLinux::GetXColor(Color3::Black, m_nColorDepth);
	m_sGC = XCreateGC(m_pDisplay, m_nWindow, GCFunction | GCForeground, &sGCValues);
}

/**
*  @brief
*    Constructor
*/
GraphicsLinux::GraphicsLinux(Graphics &cGraphics) : GraphicsImpl(cGraphics)
{
	// Get linux GUI
	GuiLinux *pGuiLinux = (GuiLinux*)cGraphics.GetGui()->GetImpl();
	m_pDisplay = pGuiLinux->m_pDisplay;
	m_nScreen = DefaultScreen(m_pDisplay);
	m_nWindow = RootWindow(m_pDisplay, m_nScreen);
	Pixmap offscreen = XCreatePixmap(m_pDisplay, m_nWindow, 512, 512, 1);

	// Get color depth
	m_nColorDepth = DefaultDepth(m_pDisplay, m_nScreen);

	// Create graphics context
	::XGCValues	sGCValues;
	sGCValues.function   = GXcopy;
	sGCValues.foreground = ToolsLinux::GetXColor(Color3::Black, m_nColorDepth);
	m_sGC = XCreateGC(m_pDisplay, m_nWindow, GCFunction | GCForeground, &sGCValues);
}

/**
*  @brief
*    Destructor
*/
GraphicsLinux::~GraphicsLinux()
{
	// Free graphics context
	XFree(m_sGC);
}


//[-------------------------------------------------------]
//[ Public virtual GraphicsImpl functions                 ]
//[-------------------------------------------------------]
void GraphicsLinux::DrawLine(const Color4 &cColor, const Vector2i &vPos1, const Vector2i &vPos2, uint32 nWidth)
{
	// Check if window handle is valid
	if (m_nWindow) {
		// Set graphics options
		::XGCValues	sGCValues;
		sGCValues.function   = GXcopy;
		sGCValues.foreground = ToolsLinux::GetXColor(Color3(cColor), m_nColorDepth);
		sGCValues.line_width = nWidth;
		XChangeGC(m_pDisplay, m_sGC, GCFunction | GCForeground | GCLineWidth, &sGCValues);

		// Draw line
		XDrawLine(m_pDisplay, m_nWindow, m_sGC, vPos1.x, vPos1.y, vPos2.x, vPos2.y);
	}
}

void GraphicsLinux::DrawRect(const Color4 &cColor, const Vector2i &vPos1, const Vector2i &vPos2, uint32 nRoundX, uint32 nRoundY, uint32 nWidth)
{
	// Check if window handle is valid
	if (m_nWindow) {
		// Set graphics options
		::XGCValues	sGCValues;
		sGCValues.function   = GXcopy;
		sGCValues.foreground = ToolsLinux::GetXColor(Color3(cColor), m_nColorDepth);
		sGCValues.line_width = nWidth;
		XChangeGC(m_pDisplay, m_sGC, GCFunction | GCForeground | GCLineWidth, &sGCValues);

		// Draw rectangle
		XDrawRectangle(m_pDisplay, m_nWindow, m_sGC, vPos1.x, vPos1.y, vPos2.x-vPos1.x, vPos2.y-vPos1.y);
	}
}

void GraphicsLinux::DrawBox(const Color4 &cColor, const Vector2i &vPos1, const Vector2i &vPos2, uint32 nRoundX, uint32 nRoundY)
{
	// Check if window handle is valid
	if (m_nWindow) {
		// Set graphics options
		::XGCValues	sGCValues;
		sGCValues.function   = GXcopy;
		sGCValues.foreground = ToolsLinux::GetXColor(Color3(cColor), m_nColorDepth);
		sGCValues.background = ToolsLinux::GetXColor(Color3(cColor), m_nColorDepth);
		XChangeGC(m_pDisplay, m_sGC, GCFunction | GCForeground | GCBackground, &sGCValues);

		// Draw box
		XFillRectangle(m_pDisplay, m_nWindow, m_sGC, vPos1.x, vPos1.y, vPos2.x-vPos1.x+1, vPos2.y-vPos1.y+1);
	}
}

void GraphicsLinux::DrawGradientBox(const Color4 &cColor1, const Color4 &cColor2, float fAngle, const Vector2i &vPos1, const Vector2i &vPos2)
{
	// [TODO]
}

void GraphicsLinux::DrawImage(const Image &cImage, const Vector2i &vPos, const Vector2i &vSize)
{
	// [TODO] Currently, the image is always drawn with the source size (no scaling implemented)

	// Check if window handle is valid
	if (m_nWindow) {
		// Get image and mask pixmaps
		Pixmap pixmap = ((ImageLinux*)cImage.GetImpl())->GetPixmap();
		Pixmap mask   = ((ImageLinux*)cImage.GetImpl())->GetMaskPixmap();

		// Set mask
		::XGCValues	sGCValues;
		sGCValues.clip_mask		= mask;
		sGCValues.clip_x_origin = vPos.x;
		sGCValues.clip_y_origin = vPos.y;
		XChangeGC(m_pDisplay, m_sGC, GCClipMask | GCClipXOrigin | GCClipYOrigin, &sGCValues);

		// Draw image
		unsigned int nWidth  = vSize.x ? vSize.x : cImage.GetSize().x;
		unsigned int nHeight = vSize.y ? vSize.y : cImage.GetSize().y;
		XCopyArea(m_pDisplay, pixmap, m_nWindow, m_sGC, 0, 0, nWidth, nHeight, vPos.x, vPos.y);

		// Reset mask
		sGCValues.clip_mask		= XLib::None;
		sGCValues.clip_x_origin	= 0;
		sGCValues.clip_y_origin	= 0;
		XChangeGC(m_pDisplay, m_sGC, GCClipMask | GCClipXOrigin | GCClipYOrigin, &sGCValues);
	}
}

void GraphicsLinux::DrawText(const Font &cFont, const Color4 &cTextColor, const Color4 &cBkColor, const Vector2i &vPos, const String &sText)
{
	// Set graphics options
	::XGCValues	sGCValues;
	sGCValues.function   = GXcopy;
	sGCValues.foreground = ToolsLinux::GetXColor(Color3(cTextColor), m_nColorDepth);
	sGCValues.background = ToolsLinux::GetXColor(Color3(cBkColor),   m_nColorDepth);
	sGCValues.font = ((FontLinux*)cFont.GetImpl())->GetXFont()->fid;
	XChangeGC(m_pDisplay, m_sGC, GCFunction | GCForeground | GCBackground | GCFont, &sGCValues);

	// Get font height
	uint32 nHeight = ((FontLinux*)cFont.GetImpl())->GetHeight();

	// Draw text
	if (sText.GetFormat() == String::ASCII)
		XDrawString(m_pDisplay, m_nWindow, m_sGC, vPos.x, vPos.y + nHeight, sText.GetASCII(), sText.GetLength());
	else if (sText.GetFormat() == String::Unicode)
		// [TODO] For UTC-2 strings, look at FontSet instead of FontStruct and
		//        XmbDrawString or Xutf8DrawString instead of XDrawString
		XDrawString(m_pDisplay, m_nWindow, m_sGC, vPos.x, vPos.y + nHeight, sText.GetASCII(), sText.GetLength());
	else if (sText.GetFormat() == String::UTF8)
		// [TODO] For UTF-8 strings, look at FontSet instead of FontStruct and
		//        XmbDrawString or Xutf8DrawString instead of XDrawString
		XDrawString(m_pDisplay, m_nWindow, m_sGC, vPos.x, vPos.y + nHeight, sText.GetASCII(), sText.GetLength());
}

uint32 GraphicsLinux::GetTextWidth(const Font &cFont, const String &sText)
{
	// Get text width
	uint32 nWidth = 0;
	if (sText.GetFormat() == String::ASCII)
		nWidth = XTextWidth(((FontLinux*)cFont.GetImpl())->GetXFont(), sText.GetASCII(), sText.GetLength());
	else if (sText.GetFormat() == String::Unicode)
		// [TODO] Look at XTextWidth16 etc.
		nWidth = XTextWidth(((FontLinux*)cFont.GetImpl())->GetXFont(), sText.GetASCII(), sText.GetLength());
	else if (sText.GetFormat() == String::UTF8)
		// [TODO] Look at XTextWidth16 etc.
		nWidth = XTextWidth(((FontLinux*)cFont.GetImpl())->GetXFont(), sText.GetASCII(), sText.GetLength());

	// Return width
	return nWidth;
}

uint32 GraphicsLinux::GetTextHeight(const Font &cFont, const String &sText)
{
	// Return text height from font
	return ((FontLinux*)cFont.GetImpl())->GetHeight();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
