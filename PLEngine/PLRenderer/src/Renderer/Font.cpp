/*********************************************************\
 *  File: Font.cpp                                       *
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
#include "PLRenderer/Renderer/FontGlyph.h"
#include "PLRenderer/Renderer/FontManager.h"
#include "PLRenderer/Renderer/Font.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
Font::~Font()
{
	// Destroy the currently active glyphs
	DestroyGlyphs();
}

/**
*  @brief
*    Returns the creating font manager
*/
FontManager &Font::GetFontManager() const
{
	return *m_pFontManager;
}

/**
*  @brief
*    Returns the filename of the font file the data came from
*/
String Font::GetFilename() const
{
	return m_sFilename;
}

/**
*  @brief
*    Returns the font size in points (72 points per inch)
*/
uint32 Font::GetSize() const
{
	return m_nSize;
}

/**
*  @brief
*    Returns the horizontal and vertical resolution in DPI
*/
uint32 Font::GetResolution() const
{
	return m_nResolution;
}

/**
*  @brief
*    Returns the font size in pixels
*/
uint32 Font::GetSizeInPixels() const
{
	return uint32(m_nSize/72.0f*m_nResolution);
}

/**
*  @brief
*    Returns the font height in pixels
*/
uint32 Font::GetHeightInPixels() const
{
	return uint32(GetHeight()/72.0f*m_nResolution);
}


//[-------------------------------------------------------]
//[ Public virtual Font functions                         ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets the font size
*/
bool Font::SetSize(uint32 nSize, uint32 nResolution)
{
	// Destroy the currently active glyphs
	DestroyGlyphs();

	// Done
	return true;
}

/**
*  @brief
*    Returns the width of a text (in font units) drawn with this font
*/
float Font::GetTextWidth(const String &sText)
{
	float fWidth = 0.0f;

	// Are there any glyphs at all?
	if (m_lstGlyphs.GetNumOfElements()) {
		// Get the text to 'draw' - we only support ASCII
		const char *pszText = sText.GetASCII();

		// Iterate through all characters of the text to 'draw'
		for (uint32 i=0; i<sText.GetLength(); i++, pszText++) {
			// Get the character code
			const unsigned char nCharacterCode = (unsigned char)*pszText;

			// Get the glyph instance of the character to 'draw'
			FontGlyph *pFontGlyph = m_lstGlyphs[nCharacterCode];
			if (pFontGlyph) {
				// 'Draw' the glyph and let the pen advance to the object space position of the next character
				fWidth += pFontGlyph->GetPenAdvance().x;
			}
		}
	}

	// Return the width
	return fWidth;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Font::Font(FontManager &cFontManager, const String &sFilename) : Resource(cFontManager.GetRenderer(), TypeFont),
	m_pFontManager(&cFontManager),
	m_sFilename(sFilename),
	m_nSize(0),
	m_nResolution(0)
{
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Font::Font(const Font &cSource) : Resource(cSource.GetRenderer(), TypeFont)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Font &Font::operator =(const Font &cSource)
{
	// No implementation because the copy constructor is never used
	return *this;
}

/**
*  @brief
*    Destroys the currently active glyphs
*/
void Font::DestroyGlyphs()
{
	for (uint32 i=0; i<m_lstGlyphs.GetNumOfElements(); i++)
		delete m_lstGlyphs[i];
	m_lstGlyphs.Clear();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
