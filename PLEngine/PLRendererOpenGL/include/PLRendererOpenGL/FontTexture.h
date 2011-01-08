/*********************************************************\
 *  File: FontTexture.h                                  *
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


#ifndef __PLRENDEREROPENGL_FONTTEXTURE_H__
#define __PLRENDEREROPENGL_FONTTEXTURE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/FontTexture.h>
#include "PLRendererOpenGL/PLRendererOpenGL.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
typedef struct FT_FaceRec_ *FT_Face;
namespace PLGeneral {
	class File;
}
namespace PLRendererOpenGL {
	class FontManager;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract OpenGL renderer font texture
*/
class FontTexture : public PLRenderer::FontTexture {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~FontTexture();

		/**
		*  @brief
		*    Returns the FreeType library face object (aka "The Font")
		*
		*  @return
		*    The FreeType library face object, a null pointer on error
		*/
		FT_Face *GetFTFace() const;

		/**
		*  @brief
		*    Returns the size of the glyph texture atlas (in pixel)
		*
		*  @return
		*    The size of the glyph texture atlas
		*/
		const PLMath::Vector2i &GetGlyphTextureAtlasSize() const;


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Font functions             ]
	//[-------------------------------------------------------]
	public:
		virtual bool SetSize(PLGeneral::uint32 nSize = 12, PLGeneral::uint32 nResolution = 96);
		virtual bool IsValid() const;
		virtual float GetAscender() const;
		virtual float GetDescender() const;
		virtual float GetHeight() const;
		virtual float GetTextWidth(const PLGeneral::String &sText);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFontManager
		*    Creating font manager
		*  @param[in] cFile
		*    File to load from, must be opened and readable
		*/
		FontTexture(FontManager &cFontManager, PLGeneral::File &cFile);

		/**
		*  @brief
		*    Calculates the glyph texture atlas size using the current glyph settings and hardware capabilities
		*
		*  @param[out] vSize
		*    Receives the glyph texture atlas size
		*/
		void CalculateGlyphTextureAtlasSize(PLMath::Vector2i &vSize);

		/**
		*  @brief
		*    Creates the glyph texture atlas
		*/
		void CreateGlyphTextureAtlas();

		/**
		*  @brief
		*    Returns the number of bytes the glyph texture atlas allocates
		*
		*  @param[in] bIncludeMipmaps
		*    Include the memory required for the mipmaps?
		*
		*  @return
		*    The number of bytes the glyph texture atlas allocates
		*/
		PLGeneral::uint32 GetGlyphTextureAtlasNumOfBytes(bool bIncludeMipmaps) const;

		/**
		*  @brief
		*    Destroys the glyph texture atlas
		*/
		void DestroyGlyphTextureAtlas();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::uint32  m_nFontFileSize;				/**< Font file size in bytes */
		PLGeneral::uint8  *m_pFontFileData;				/**< Font file data, can be a null pointer */
		FT_Face			  *m_pFTFace;					/**< FreeType library face (aka "The Font"), a null pointer on error */
		PLGeneral::uint32  m_nGlyphTextureAtlasPadding;	/**< Glyph texture atlas gab between glyphs in pixel */
		GLuint			   m_nOpenGLGlyphTextureAtlas;	/**< OpenGL glyph texture atlas, can be null */
		PLMath::Vector2i   m_vGlyphTextureAtlasSize;	/**< Glyph texture atlas size */


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::Resource functions        ]
	//[-------------------------------------------------------]
	private:
		virtual void BackupDeviceData(PLGeneral::uint8 **ppBackup);
		virtual void RestoreDeviceData(PLGeneral::uint8 **ppBackup);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_FONTTEXTURE_H__
