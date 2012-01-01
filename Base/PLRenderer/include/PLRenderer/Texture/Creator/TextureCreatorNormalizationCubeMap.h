/*********************************************************\
 *  File: TextureCreatorNormalizationCubeMap.h           *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLRENDERER_TEXTURECREATOR_NORMALIZATIONCUBEMAP_H__
#define __PLRENDERER_TEXTURECREATOR_NORMALIZATIONCUBEMAP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
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
*    Normalization cube map (TextureBuffer::R8G8B8) texture creator class
*
*  @remarks
*    This cube map texture can be used within shader programs to normalize vectors
*    through a fast texture access instead of a slower normalization using
*    math functions.
*/
class TextureCreatorNormalizationCubeMap : public TextureCreator {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDERER_RTTI_EXPORT, TextureCreatorNormalizationCubeMap, "PLRenderer", PLRenderer::TextureCreator, "Normalization cube map (TextureBuffer::R8G8B8) texture creator class")
		// Attributes
		pl_attribute(Size,	PLCore::uint32,	64,	ReadWrite,	DirectValue,	"Texture size (must be a power of 2)",	"Min='8'")
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
		PLRENDERER_API TextureCreatorNormalizationCubeMap();

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~TextureCreatorNormalizationCubeMap();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/*
		*  @brief
		*    Returns a cube vector
		*
		*  @param[in] i
		*    Cube map side
		*  @param[in] x
		*    Cube map x position
		*  @param[in] y
		*    Cube map y position
		*
		*  @return
		*    The cube requested vector
		*/
		PLMath::Vector3 GetCubeVector(PLCore::uint8 i, PLCore::uint32 x, PLCore::uint32 y) const;


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


#endif // __PLRENDERER_TEXTURECREATOR_NORMALIZATIONCUBEMAP_H__
