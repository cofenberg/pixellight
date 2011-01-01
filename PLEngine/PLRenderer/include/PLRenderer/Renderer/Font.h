/*********************************************************\
 *  File: Font.h                                         *
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


#ifndef __PLRENDERER_FONT_H__
#define __PLRENDERER_FONT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/Array.h>
#include <PLMath/Vector2.h>
#include <PLMath/Vector2i.h>
#include "PLRenderer/Renderer/Resource.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class Matrix4x4;
}
namespace PLGraphics {
	class Color4;
}
namespace PLRenderer {
	class FontGlyph;
	class FontManager;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract renderer font resource base class
*
*  @remarks
*
*    Height       Ascender    Internal leading
*      |            |         |
*      |   |    |   |             |
*      |   |    |   |             |
*      |   |----|   |             |
*      |   |    |   |             |
*    0 |___|____|___|_____________|___ Baseline 
*      |0               |         |
*      |                |         |
*                   Descender    Size
*
*    Term definitions:
*    - Height = Ascender + Descender
*    - Size   = Height - Internal leading
*
*  @note
*    - For italic/bold fonts, you have to specify the corresponding font variation file of the font file
*/
class Font : public Resource {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  brief
		*    Draw flags
		*/
		enum EDrawFlags {
			CenterText    = 1<<0,	/**< Center the text */
			UnderlineText = 1<<1,	/**< Underline the text */
			CrossoutText  = 1<<2,	/**< Cross out the text */
			Mipmapping    = 1<<3	/**< Use mipmapping (may blur the font in an ugly way) */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~Font();

		/**
		*  @brief
		*    Returns the creating font manager
		*
		*  @return
		*    The creating font manager
		*/
		PLRENDERER_API FontManager &GetFontManager() const;

		/**
		*  @brief
		*    Returns the filename of the font file the data came from
		*
		*  @return
		*    The filename of the font file the data came from
		*/
		PLRENDERER_API PLGeneral::String GetFilename() const;

		/**
		*  @brief
		*    Returns the nominal font size in points (72 points per inch)
		*
		*  @return
		*    The nominal font size in points, for example 12
		*/
		PLRENDERER_API PLGeneral::uint32 GetSize() const;

		/**
		*  @brief
		*    Returns the horizontal and vertical resolution in DPI
		*
		*  @return
		*    The horizontal and vertical resolution in DPI, for example 96
		*/
		PLRENDERER_API PLGeneral::uint32 GetResolution() const;

		/**
		*  @brief
		*    Returns the font size in pixels
		*
		*  @return
		*    The font size in pixels
		*
		*  @remarks
		*    Example: Arial 12pt at 96 dpi:
		*
		*                          Font size in points             12
		*    Font size in pixels = ------------------- × 96 dpi = ---- × 96 = 16 pixels
		*                          72 points per inch              72
		*/
		PLRENDERER_API PLGeneral::uint32 GetSizeInPixels() const;

		/**
		*  @brief
		*    Returns the font (line) height in pixels
		*
		*  @return
		*    The font height in pixels
		*
		*  @see
		*    - GetSizeInPixels()
		*/
		PLRENDERER_API PLGeneral::uint32 GetHeightInPixels() const;


	//[-------------------------------------------------------]
	//[ Public virtual Font functions                         ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Sets the font size
		*
		*  @param[in] nSize
		*    Nominal font size in points, for example 12 (72 points per inch)
		*  @param[in] nResolution
		*    The horizontal and vertical resolution in DPI, for example 96
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - When overwriting this method, it's highly recommended to call this base implementation, too
		*/
		PLRENDERER_API virtual bool SetSize(PLGeneral::uint32 nSize = 12, PLGeneral::uint32 nResolution = 96);

		/**
		*  @brief
		*    Returns whether or not this font is valid
		*
		*  @return
		*    'true' if the font is valid, else 'false'
		*/
		virtual bool IsValid() const = 0;

		/**
		*  @brief
		*    Returns the ascender in font units
		*
		*  @return
		*    The ascender in font units
		*/
		virtual float GetAscender() const = 0;

		/**
		*  @brief
		*    Returns the descender in font units
		*
		*  @return
		*    The descender in font units (negative value)
		*/
		virtual float GetDescender() const = 0;

		/**
		*  @brief
		*    Returns the height in font units
		*
		*  @return
		*    The height in font units
		*/
		virtual float GetHeight() const = 0;

		/**
		*  @brief
		*    Returns the width of a text (in font units) drawn with this font
		*
		*  @param[in] sText
		*    Text to 'draw'
		*
		*  @return
		*    The width of a text (in font units) drawn with this font
		*
		*  @note
		*    - When overwriting this method, it's highly recommended to call this base implementation, too
		*/
		PLRENDERER_API virtual float GetTextWidth(const PLGeneral::String &sText);

		/**
		*  @brief
		*    Draws a text
		*
		*  @param[in] sText
		*    Text to draw
		*  @param[in] cColor
		*    Text color
		*  @param[in] mObjectSpaceToClipSpace
		*    Object space to clip space matrix
		*  @param[in] vScale
		*    Font scale, there are situations were it's more comfortable to have a special scale variable as just mObjectSpaceToClipSpace with all build in
		*  @param[in] vBias
		*    Font bias (position offset), there are situations were it's more comfortable to have a special bias variable as just mObjectSpaceToClipSpace with all build in
		*  @param[in] nFlags
		*    Draw flags, see EDrawFlags
		*/
		virtual void Draw(const PLGeneral::String &sText, const PLGraphics::Color4 &cColor, const PLMath::Matrix4x4 &mObjectSpaceToClipSpace, const PLMath::Vector2 &vScale = PLMath::Vector2::One, const PLMath::Vector2 &vBias = PLMath::Vector2::Zero, PLGeneral::uint32 nFlags = 0) = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default
		*
		*  @param[in] cFontManager
		*    Creating font manager
		*  @param[in] sFilename
		*    Filename of the font file the data came from, used to reference the new font by filename
		*/
		PLRENDERER_API Font(FontManager &cFontManager, const PLGeneral::String &sFilename);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Font(const Font &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Font &operator =(const Font &cSource);

		/**
		*  @brief
		*    Destroys the currently active glyphs
		*/
		PLRENDERER_API void DestroyGlyphs();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		FontManager					 *m_pFontManager;	/**< Creating font manager, always valid! */
		PLGeneral::String			  m_sFilename;		/**< The filename of the font file the data came from */
		PLGeneral::uint32			  m_nSize;			/**< Font size in points, for example 12 (72 points per inch) */
		PLGeneral::uint32			  m_nResolution;	/**< The horizontal and vertical resolution in DPI, for example 96 */
		PLGeneral::Array<FontGlyph*>  m_lstGlyphs;		/**< List of currently active glyphs ("character code -> glyph instance") */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_FONT_H__
