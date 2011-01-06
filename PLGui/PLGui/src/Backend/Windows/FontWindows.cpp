/*********************************************************\
 *  File: FontWindows.cpp                                *
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
#include "PLGui/Backend/Windows/FontWindows.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FontWindows::FontWindows(Font &cFont) : FontImpl(cFont),
	m_hFont(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
FontWindows::~FontWindows()
{
	// Release font
	if (m_hFont) DeleteObject(m_hFont);
}

/**
*  @brief
*    Returns the font handle
*/
HFONT FontWindows::GetHandle() const
{
	// Return font handle
	return m_hFont;
}


//[-------------------------------------------------------]
//[ Public virtual FontImpl functions                     ]
//[-------------------------------------------------------]
bool FontWindows::LoadFont(const String &sFamily, uint32 nHeight, uint32 nWeight, EFontStyle nStyle)
{
	// Release old font
	if (m_hFont) DeleteObject(m_hFont);

	// Scale weight
	int nW = nWeight * 10;
	if (nW < 0)		nW = 0;
	if (nW > 1000)	nW = 1000;

	// Create font
	if (sFamily.GetFormat() == String::ASCII) {
		m_hFont = CreateFontA(
			nHeight > 0 ? nHeight : 12,	// nHeight
			0,							// nWidth
			0,							// nEscapement
			0,							// nOrientation
			nW,							// nWeight
			(nStyle == StyleItalics),	// bItalic
			false,						// bUnderline
			0,							// cStrikeOut
			ANSI_CHARSET,				// nCharSet
			OUT_DEFAULT_PRECIS,			// nOutPrecision
			CLIP_DEFAULT_PRECIS,		// nClipPrecision
			DEFAULT_QUALITY,			// nQuality
			DEFAULT_PITCH | FF_SWISS,	// nPitchAndFamily
			sFamily.GetASCII()			// lpszFacename
		);
	} else {
		m_hFont = CreateFontW(
			nHeight > 0 ? nHeight : 12,	// nHeight
			0,							// nWidth
			0,							// nEscapement
			0,							// nOrientation
			nW,							// nWeight
			(nStyle == StyleItalics),	// bItalic
			false,						// bUnderline
			0,							// cStrikeOut
			ANSI_CHARSET,				// nCharSet
			OUT_DEFAULT_PRECIS,			// nOutPrecision
			CLIP_DEFAULT_PRECIS,		// nClipPrecision
			DEFAULT_QUALITY,			// nQuality
			DEFAULT_PITCH | FF_SWISS,	// nPitchAndFamily
			sFamily.GetUnicode()		// lpszFacename
		);
	}

	// Return if a font has been successfully created
	return (m_hFont != nullptr);
}

bool FontWindows::LoadFont(const String &sFilename, uint32 nHeight)
{
	// Release old font
	if (m_hFont) DeleteObject(m_hFont);

	// [TODO] Implement
	m_hFont = nullptr;

	// Return if a font has been successfully created
	return (m_hFont != nullptr);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
