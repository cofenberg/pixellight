/*********************************************************\
 *  File: TextureCreatorHorizonMap3D.h                   *
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


#ifndef __PLRENDERER_TEXTURECREATOR_HORIZONMAP3D_H__
#define __PLRENDERER_TEXTURECREATOR_HORIZONMAP3D_H__
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
*    3D horizon map texture (TextureBuffer::L8) creator class
*
*  @note
*    - This 3D horizon map texture can be used within shader programs for self shadowing.
*      For more information about this have a look at "Interactive Horizon Mapping".
*      (http://research.microsoft.com/~cohen/bs.pdf)
*    - The creation of horizons map shouldn't done at runtime because it's not
*      performant!
*/
class TextureCreatorHorizonMap3D : public TextureCreator {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDERER_RTTI_EXPORT, TextureCreatorHorizonMap3D, "PLRenderer", PLRenderer::TextureCreator, "3D horizon map texture (TextureBuffer::L8) creator class")
		// Attributes
		pl_attribute(Filename2D,	PLCore::String,	"",		ReadWrite,	DirectValue,	"2D height map filename to create the horizon map for",	"")
		pl_attribute(XSize,			PLCore::uint32,	64,		ReadWrite,	DirectValue,	"Texture x size (must be a power of 2)",				"Min='8'")
		pl_attribute(YSize,			PLCore::uint32,	64,		ReadWrite,	DirectValue,	"Texture y size (must be a power of 2)",				"Min='8'")
		pl_attribute(ZSize,			PLCore::uint32,	64,		ReadWrite,	DirectValue,	"Texture z size (must be a power of 2)",				"Min='8'")
		pl_attribute(Height,		float,			0.16f,	ReadWrite,	DirectValue,	"Height",												"")
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
		PLRENDERER_API TextureCreatorHorizonMap3D();

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~TextureCreatorHorizonMap3D();


	//[-------------------------------------------------------]
	//[ Private virtual TextureCreator functions              ]
	//[-------------------------------------------------------]
	private:
		virtual Texture *Create(TextureManager &cTextureManager, Texture *pTexture = nullptr) const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_TEXTURECREATOR_HORIZONMAP3D_H__
