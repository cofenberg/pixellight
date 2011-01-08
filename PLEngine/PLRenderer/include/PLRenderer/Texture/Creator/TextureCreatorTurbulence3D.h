/*********************************************************\
 *  File: TextureCreatorTurbulence3D.h                   *
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


#ifndef __PLRENDERER_TEXTURECREATOR_TURBULENCE3D_H__
#define __PLRENDERER_TEXTURECREATOR_TURBULENCE3D_H__
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
*    3D turbulence texture (TextureBuffer::L8) creator class
*/
class TextureCreatorTurbulence3D : public TextureCreator {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDERER_RTTI_EXPORT, TextureCreatorTurbulence3D, "PLRenderer", PLRenderer::TextureCreator, "3D turbulence texture (TextureBuffer::L8) creator class")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(XSize,	PLGeneral::uint32,	128,									ReadWrite,	DirectValue,	"Texture x size (must be a power of 2)",	"Min='8'")
		pl_attribute(YSize,	PLGeneral::uint32,	32,										ReadWrite,	DirectValue,	"Texture y size (must be a power of 2)",	"Min='8'")
		pl_attribute(ZSize,	PLGeneral::uint32,	32,										ReadWrite,	DirectValue,	"Texture z size (must be a power of 2)",	"Min='8'")
		pl_attribute(Scale,	PLMath::Vector3,	PLMath::Vector3(0.08f, 0.16f, 0.16f),	ReadWrite,	DirectValue,	"Texture scale",							"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLRENDERER_API TextureCreatorTurbulence3D();

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~TextureCreatorTurbulence3D();


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


#endif // __PLRENDERER_TEXTURECREATOR_TURBULENCE3D_H__
