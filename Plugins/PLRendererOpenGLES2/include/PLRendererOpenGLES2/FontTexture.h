/*********************************************************\
 *  File: FontTexture.h                                  *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLRENDEREROPENGLES2_FONTTEXTURE_H__
#define __PLRENDEREROPENGLES2_FONTTEXTURE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/FontTexture.h>
#include "PLRendererOpenGLES2/Context.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
typedef struct FT_FaceRec_ *FT_Face;
namespace PLCore {
	class File;
}
namespace PLRendererOpenGLES2 {
	class FontManager;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL ES renderer font texture
*/
class FontTexture : public PLRenderer::FontTexture {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class FontManager;


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
		virtual bool SetSize(PLCore::uint32 nSize = 12, PLCore::uint32 nResolution = 96) override;
		virtual bool IsValid() const override;
		virtual float GetAscender() const override;
		virtual float GetDescender() const override;
		virtual float GetHeight() const override;
		virtual float GetTextWidth(const PLCore::String &sText) override;
		virtual void Draw(const PLCore::String &sText, const PLGraphics::Color4 &cColor, const PLMath::Matrix4x4 &mObjectSpaceToClipSpace, const PLMath::Vector2 &vScale = PLMath::Vector2::One, const PLMath::Vector2 &vBias = PLMath::Vector2::Zero, PLCore::uint32 nFlags = 0) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFontManager
		*    Creating font manager
		*  @param[in] cFile
		*    File to load from, must be opened and readable
		*/
		FontTexture(FontManager &cFontManager, PLCore::File &cFile);

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
		PLCore::uint32 GetGlyphTextureAtlasNumOfBytes(bool bIncludeMipmaps) const;

		/**
		*  @brief
		*    Destroys the glyph texture atlas
		*/
		void DestroyGlyphTextureAtlas();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::uint32     m_nFontFileSize;					/**< Font file size in bytes */
		PLCore::uint8  	  *m_pFontFileData;					/**< Font file data, can be a null pointer */
		FT_Face			  *m_pFTFace;						/**< FreeType library face (aka "The Font"), a null pointer on error */
		PLCore::uint32     m_nGlyphTextureAtlasPadding;		/**< Glyph texture atlas gab between glyphs in pixel */
		GLuint			   m_nOpenGLESGlyphTextureAtlas;	/**< OpenGL ES glyph texture atlas, can be null */
		PLMath::Vector2i   m_vGlyphTextureAtlasSize;		/**< Glyph texture atlas size */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2


#endif // __PLRENDEREROPENGLES2_FONTTEXTURE_H__
