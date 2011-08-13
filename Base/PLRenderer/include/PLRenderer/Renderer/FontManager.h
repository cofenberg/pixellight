/*********************************************************\
 *  File: FontManager.h                                  *
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


#ifndef __PLRENDERER_FONTMANAGER_H__
#define __PLRENDERER_FONTMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/Array.h>
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class File;
	class String;
}
namespace PLRenderer {
	class Font;
	class Renderer;
	class FontTexture;
	class ResourceHandler;
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
*    Abstract renderer font manager
*/
class FontManager {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class FontTexture;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the owner renderer
		*
		*  @return
		*    The owner renderer
		*/
		PLRENDERER_API Renderer &GetRenderer() const;

		//[-------------------------------------------------------]
		//[ Texture font                                          ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the default texture font
		*
		*  @return
		*    The default texture font, a null pointer on error
		*
		*  @remarks
		*    The default texture font setting is build in and is set to
		*    - Filename   = "Data/Fonts/LinLibertine_Re-2.7.9.9.otf"
		*    - Size       = 15
		*      Resolution = 96
		*   In order to remove the default texture font or to set another default texture font,
		*   just set it during the application initialization. The font is internally not initialized
		*   until it's first real usage, so, this approach doesn't introduce overhead if you never use
		*   the build in default font.
		*/
		PLRENDERER_API Font *GetDefaultFontTexture();

		/**
		*  @brief
		*    Sets the default texture font
		*
		*  @param[in] pFont
		*    The texture font or a null pointer
		*/
		PLRENDERER_API void SetDefaultFontTexture(FontTexture *pFont);

		/**
		*  @brief
		*    Returns a texture font
		*
		*  @param[in] sFilename
		*    The font filename
		*  @param[in] nSize
		*    Nominal font size in points, for example 12 (72 points per inch)
		*  @param[in] nResolution
		*    The horizontal and vertical resolution in DPI, for example 96
		*
		*  @return
		*    The texture font, a null pointer on error
		*/
		PLRENDERER_API FontTexture *GetFontTexture(const PLCore::String &sFilename, PLCore::uint32 nSize = 12, PLCore::uint32 nResolution = 96);

		/**
		*  @brief
		*    Clears all texture fonts
		*/
		PLRENDERER_API void ClearFontTexture();


	//[-------------------------------------------------------]
	//[ Public virtual FontManager functions                  ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Creates a texture font
		*
		*  @param[in] sFilename
		*    The font filename
		*  @param[in] nSize
		*    Nominal font size in points, for example 12 (72 points per inch)
		*  @param[in] nResolution
		*    The horizontal and vertical resolution in DPI, for example 96
		*
		*  @return
		*    The created texture font, destroy the instance if you no longer need it
		*
		*  @note
		*    - The default implementations opens and reads in the file
		*/
		PLRENDERER_API virtual Font *CreateFontTexture(const PLCore::String &sFilename, PLCore::uint32 nSize = 12, PLCore::uint32 nResolution = 96);

		/**
		*  @brief
		*    Creates a texture font
		*
		*  @param[in] cFile
		*    File to load from, must be opened and readable
		*  @param[in] nSize
		*    Nominal font size in points, for example 12 (72 points per inch)
		*  @param[in] nResolution
		*    The horizontal and vertical resolution in DPI, for example 96
		*
		*  @return
		*    The created texture font, destroy the instance if you no longer need it
		*/
		virtual Font *CreateFontTexture(PLCore::File &cFile, PLCore::uint32 nSize = 12, PLCore::uint32 nResolution = 96) = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*/
		PLRENDERER_API FontManager(Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~FontManager();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Renderer					*m_pRenderer;					/**< Owner renderer, always valid! */
		ResourceHandler				*m_pDefaultFontTextureHandler;	/**< Default texture font, always valid! */
		bool						 m_bDefaultFontTextureSet;		/**< Default font texture already set? */
		PLCore::Array<FontTexture*>  m_lstFontTexture;				/**< Texture fonts */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		FontManager(const FontManager &cSource);

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
		FontManager &operator =(const FontManager &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_FONTMANAGER_H__
