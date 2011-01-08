/*********************************************************\
 *  File: FontGlyphTexture.cpp                           *
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
#include <GLES2/gl2.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ftglyph.h>
#include <PLMath/Math.h>
#include "PLRendererOpenGLES/FontTexture.h"
#include "PLRendererOpenGLES/FontGlyphTexture.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLRendererOpenGLES {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FontGlyphTexture::FontGlyphTexture(FontTexture &cFontTexture, unsigned long nCharacterCode, const Vector2i &vPosition)
{
	// Get the FreeType library face object (aka "The Font")
	FT_Face *pFTFace = cFontTexture.GetFTFace();
	if (pFTFace) {
		// Load the Glyph for the character
		if (!FT_Load_Glyph(*pFTFace, FT_Get_Char_Index(*pFTFace, nCharacterCode), FT_LOAD_DEFAULT)) {
			// Move the glyph within the glyph slot of the face object into a glyph object
			FT_Glyph sFTGlyph;
			if (!FT_Get_Glyph((*pFTFace)->glyph, &sFTGlyph)) {
				// Convert the glyph to a bitmap
				FT_Glyph_To_Bitmap(&sFTGlyph, ft_render_mode_normal, 0, 1);
				FT_BitmapGlyph sFTBitmapGlyph = (FT_BitmapGlyph)sFTGlyph;

				// Get a reference to the glypth bitmap
				FT_Bitmap &sFTBitmap = sFTBitmapGlyph->bitmap;

				// Get the size (in pixel) of the glyph
				m_nSize.Set(sFTBitmap.width, sFTBitmap.rows);

				// Copy the glyph bitmap into the glyph texture atlas (this OpenGL texture must be currently bound!)
				if (m_nSize != Vector2i::Zero)
					glTexSubImage2D(GL_TEXTURE_2D, 0, vPosition.x, vPosition.y, m_nSize.x, m_nSize.y, GL_ALPHA, GL_UNSIGNED_BYTE, sFTBitmap.buffer);

				// Set the distance (in pixel) from the current pen position to the glyph bitmap
				m_vCorner.SetXY((float)sFTBitmapGlyph->left, (float)sFTBitmapGlyph->top - m_nSize.y);

				// Set the pen advance, the FreeType library measures font size in terms of 1/64ths of pixels, so we have to adjust with /64
				m_vPenAdvance.x = float((*pFTFace)->glyph->advance.x)/64.0f;
				m_vPenAdvance.y = float((*pFTFace)->glyph->advance.y)/64.0f;

				// Get the size of the glyph texture atlas
				const Vector2i &vGlyphTextureAtlasSize = cFontTexture.GetGlyphTextureAtlasSize();

				// Calculate the normalized minimum glyph texture coordinate inside the glyph texture atlas
				m_vTexCoordMin.x = float(vPosition.x)/float(vGlyphTextureAtlasSize.x);
				m_vTexCoordMin.y = float(vPosition.y)/float(vGlyphTextureAtlasSize.y);

				// Calculate the normalized maximum glyph texture coordinate inside the glyph texture atlas
				m_vTexCoordMax.x = float(vPosition.x + m_nSize.x)/float(vGlyphTextureAtlasSize.x);
				m_vTexCoordMax.y = float(vPosition.y + m_nSize.y)/float(vGlyphTextureAtlasSize.y);
			}
		}
	}
}

/**
*  @brief
*    Destructor
*/
FontGlyphTexture::~FontGlyphTexture()
{
}

/**
*  @brief
*    Returns the normalized minimum glyph texture coordinate inside the glyph texture atlas
*/
const Vector2 &FontGlyphTexture::GetTexCoordMin() const
{
	return m_vTexCoordMin;
}

/**
*  @brief
*    Returns the normalized maximum glyph texture coordinate inside the glyph texture atlas
*/
const Vector2 &FontGlyphTexture::GetTexCoordMax() const
{
	return m_vTexCoordMax;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES
