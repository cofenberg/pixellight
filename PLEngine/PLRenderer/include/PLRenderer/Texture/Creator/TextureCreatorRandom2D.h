/*********************************************************\
 *  File: TextureCreatorRandom2D.h                       *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLRENDERER_TEXTURECREATOR_RANDOM2D_H__
#define __PLRENDERER_TEXTURECREATOR_RANDOM2D_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
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
*    Random 2D texture (TextureBuffer::R8G8B8) creator class
*/
class TextureCreatorRandom2D : public TextureCreator {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDERER_RTTI_EXPORT, TextureCreatorRandom2D, "PLRenderer", PLRenderer::TextureCreator, "Random 2D texture (TextureBuffer::R8G8B8) creator class")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(Width,			PLGeneral::uint32,	32,	ReadWrite,	DirectValue,	"Texture width (must be a power of 2)",		"Min='8'")
		pl_attribute(Height,		PLGeneral::uint32,	32,	ReadWrite,	DirectValue,	"Texture height (must be a power of 2)",	"Min='8'")
		pl_attribute(Components,	PLGeneral::uint8,	3,	ReadWrite,	DirectValue,	"Number of color components (1-4)",			"Min='1' Max='4'")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLRENDERER_API TextureCreatorRandom2D();

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~TextureCreatorRandom2D();


	//[-------------------------------------------------------]
	//[ Private virtual TextureCreator functions              ]
	//[-------------------------------------------------------]
	private:
		virtual Texture *Create(TextureManager &cTextureManager, Texture *pTexture = NULL) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_TEXTURECREATOR_RANDOM2D_H__
