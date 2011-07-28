/*********************************************************\
 *  File: SRP2DGame.h                                    *
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


#ifndef __PLSAMPLE_67_SRP2DGAME_H__
#define __PLSAMPLE_67_SRP2DGAME_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
#include <PLScene/Compositing/SceneRendererPass.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene renderer pass 2D game
*/
class SRP2DGame : public PLScene::SceneRendererPass {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SRP2DGame, "", PLScene::SceneRendererPass, "Scene renderer pass 2D game")
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
		SRP2DGame();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SRP2DGame();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Draws an image
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] sName
		*    Name of the texture to use
		*  @param[in] vPos
		*    Image position
		*  @param[in] vSize
		*    Image size
		*  @param[in] vTextureCoordinate
		*    Normalized texture coordinate (0..1)
		*  @param[in] vTextureCoordinateSize
		*    Normalized texture coordinate size (0..1)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool DrawImage(PLRenderer::Renderer &cRenderer, const PLCore::String &sName, const PLMath::Vector2 &vPos, const PLMath::Vector2 &vSize = PLMath::Vector2::Zero,
					   const PLMath::Vector2 &vTextureCoordinate = PLMath::Vector2::Zero, const PLMath::Vector2 &vTextureCoordinateSize = PLMath::Vector2::One) const;


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneRendererPass functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void Draw(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery) override;


};


#endif // __PLSAMPLE_67_SRP2DGAME_H__
