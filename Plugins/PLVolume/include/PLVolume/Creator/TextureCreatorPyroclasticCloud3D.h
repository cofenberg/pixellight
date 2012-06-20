/*********************************************************\
 *  File: TextureCreatorPyroclasticCloud3D.h             *
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


#ifndef __PLVOLUME_TEXTURECREATOR_PYROCLASTICCLOUD3D_H__
#define __PLVOLUME_TEXTURECREATOR_PYROCLASTICCLOUD3D_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include <PLRenderer/Texture/Creator/TextureCreator.h>
#include "PLVolume/PLVolume.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolume {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    3D pyroclastic cloud texture (TextureBuffer::L8) creator class
*
*  @note
*    - Basing on http://prideout.net/blog/?p=64 and http://magnuswrenninge.com/volumetricmethods (SIGGRAPH 2010 Course Notes "Volumetric Methods in Visual Effects")
*/
class TextureCreatorPyroclasticCloud3D : public PLRenderer::TextureCreator {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUME_RTTI_EXPORT, TextureCreatorPyroclasticCloud3D, "PLVolume", PLRenderer::TextureCreator, "3D pyroclastic cloud texture (TextureBuffer::L8) creator class")
		// PLVOLUME_RTTI_EXPORT
		pl_attribute(TextureSize,	PLCore::uint32,	128,	ReadWrite,	DirectValue,	"Texture size",	"Min='8'")
		pl_attribute(Radius,		float,			0.025f,	ReadWrite,	DirectValue,	"Radius",		"")
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
		TextureCreatorPyroclasticCloud3D();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~TextureCreatorPyroclasticCloud3D();


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::TextureCreator functions  ]
	//[-------------------------------------------------------]
	private:
		virtual PLRenderer::Texture *Create(PLRenderer::TextureManager &cTextureManager, PLRenderer::Texture *pTexture = nullptr) const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume


#endif // __PLVOLUME_TEXTURECREATOR_PYROCLASTICCLOUD3D_H__
