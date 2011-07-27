/*********************************************************\
 *  File: FontTextureFixedFunctions.h                    *
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


#ifndef __PLRENDEREROPENGL_FONTTEXTUREFIXEDFUNCTIONS_H__
#define __PLRENDEREROPENGL_FONTTEXTUREFIXEDFUNCTIONS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRendererOpenGL/FontTexture.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Fixed functions based OpenGL renderer font texture
*/
class FontTextureFixedFunctions : public FontTexture {


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
		virtual ~FontTextureFixedFunctions();


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Font functions             ]
	//[-------------------------------------------------------]
	public:
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
		FontTextureFixedFunctions(FontManager &cFontManager, PLCore::File &cFile);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_FONTTEXTUREFIXEDFUNCTIONS_H__
