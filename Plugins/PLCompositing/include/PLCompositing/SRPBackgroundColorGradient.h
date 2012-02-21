/*********************************************************\
 *  File: SRPBackgroundColorGradient.h                   *
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


#ifndef __PLCOMPOSITING_BACKGROUNDCOLORGRADIENT_H__
#define __PLCOMPOSITING_BACKGROUNDCOLORGRADIENT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
#include <PLGraphics/Color/Color4.h>
#include "PLCompositing/SRPBackground.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Color gradient background scene renderer pass
*/
class SRPBackgroundColorGradient : public SRPBackground {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPBackgroundColorGradient, "PLCompositing", PLCompositing::SRPBackground, "Color gradient background scene renderer pass")
		// Attributes
		pl_attribute(Color1,	PLGraphics::Color4,	PLGraphics::Color4::White,	ReadWrite,	DirectValue,	"First color to use",																"")
		pl_attribute(Color2,	PLGraphics::Color4,	PLGraphics::Color4::Black,	ReadWrite,	DirectValue,	"Second color to use",																"")
		pl_attribute(Angle,		float,				135.0f,						ReadWrite,	DirectValue,	"Clockwise angle (in degree) of the gradient color. 0° means from left to right.",	"")
		pl_attribute(Position,	PLMath::Vector2,	PLMath::Vector2::Zero,		ReadWrite,	DirectValue,	"Gradient quad position (0..1), (0, 0)=left top",									"")
		pl_attribute(Size,		PLMath::Vector2,	PLMath::Vector2::One,		ReadWrite,	DirectValue,	"Gradient quad size (0..1)",														"")
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
		PLCOM_API SRPBackgroundColorGradient();

		/**
		*  @brief
		*    Destructor
		*/
		PLCOM_API virtual ~SRPBackgroundColorGradient();


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneRendererPass functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void Draw(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_BACKGROUNDCOLORGRADIENT_H__
