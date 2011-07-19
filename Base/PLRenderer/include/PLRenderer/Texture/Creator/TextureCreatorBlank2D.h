/*********************************************************\
 *  File: TextureCreatorBlank2D.h                        *
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


#ifndef __PLRENDERER_TEXTURECREATOR_BLANK2D_H__
#define __PLRENDERER_TEXTURECREATOR_BLANK2D_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color4.h>
#include "PLRenderer/Texture/Creator/TextureCreator.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Blank 2D texture (TextureBuffer::R8G8B8) creator class
*/
class TextureCreatorBlank2D : public TextureCreator {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDERER_RTTI_EXPORT, TextureCreatorBlank2D, "PLRenderer", PLRenderer::TextureCreator, "Blank 2D texture (TextureBuffer::R8G8B8) creator class")
		// Attributes
		pl_attribute(Width,			PLCore::uint32,		32,											ReadWrite,	DirectValue,	"Texture width (must be a power of 2)",		"Min='8'")
		pl_attribute(Height,		PLCore::uint32,		32,											ReadWrite,	DirectValue,	"Texture height (must be a power of 2)",	"Min='8'")
		pl_attribute(Components,	PLCore::uint8,		3,											ReadWrite,	DirectValue,	"Number of color components (1-4)",			"Min='1' Max='4'")
		pl_attribute(Color,			PLGraphics::Color4,	PLGraphics::Color4(0.0f, 0.0f, 0.0f, 1.0f),	ReadWrite,	DirectValue,	"Texture fill color",						"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLRENDERER_API TextureCreatorBlank2D();

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~TextureCreatorBlank2D();


	//[-------------------------------------------------------]
	//[ Private virtual TextureCreator functions              ]
	//[-------------------------------------------------------]
	private:
		virtual Texture *Create(TextureManager &cTextureManager, Texture *pTexture = nullptr) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_TEXTURECREATOR_BLANK2D_H__
