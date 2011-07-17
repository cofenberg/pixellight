/*********************************************************\
 *  File: FontGlyphTexture.h                             *
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


#ifndef __PLRENDEREROPENGLES_FONTGLYPHTEXTURE_H__
#define __PLRENDEREROPENGLES_FONTGLYPHTEXTURE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/FontGlyphTexture.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class FontTexture;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL ES renderer font glyph texture
*/
class FontGlyphTexture : public PLRenderer::FontGlyphTexture {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFontTexture
		*    Owner texture font
		*  @param[in] nCharacterCode
		*    Character code
		*  @param[in] vPosition
		*    Position offset of the glyph inside the font texture atlas in pixel
		*
		*  @note
		*    - The font texture atlas must be the current active and bound OpenGL texture
		*/
		FontGlyphTexture(FontTexture &cFontTexture, unsigned long nCharacterCode, const PLMath::Vector2i &vPosition);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~FontGlyphTexture();

		/**
		*  @brief
		*    Returns the normalized minimum glyph texture coordinate inside the glyph texture atlas
		*
		*  @return
		*    The normalized minimum glyph texture coordinate inside the glyph texture atlas
		*/
		const PLMath::Vector2 &GetTexCoordMin() const;

		/**
		*  @brief
		*    Returns the normalized maximum glyph texture coordinate inside the glyph texture atlas
		*
		*  @return
		*    The normalized maximum glyph texture coordinate inside the glyph texture atlas
		*/
		const PLMath::Vector2 &GetTexCoordMax() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		PLMath::Vector2 m_vTexCoordMin;	/**< Normalized minimum glyph texture coordinate inside the glyph texture atlas */
		PLMath::Vector2 m_vTexCoordMax;	/**< Normalized maximum glyph texture coordinate inside the glyph texture atlas */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES


#endif // __PLRENDEREROPENGLES_FONTGLYPHTEXTURE_H__
