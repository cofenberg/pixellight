/*********************************************************\
 *  File: SRPBackgroundColorGradient.cpp                 *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Math.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Effect/EffectManager.h>
#include "PLCompositing/SRPBackgroundColorGradient.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
using namespace PLRenderer;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPBackgroundColorGradient)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPBackgroundColorGradient::SRPBackgroundColorGradient() :
	Color1(this),
	Color2(this),
	Angle(this),
	Position(this),
	Size(this)
{
}

/**
*  @brief
*    Destructor
*/
SRPBackgroundColorGradient::~SRPBackgroundColorGradient()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPBackgroundColorGradient::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Setup renderer states
	cRenderer.GetRendererContext().GetEffectManager().Use();
	cRenderer.SetRenderState(RenderState::ZEnable,			 false);
	cRenderer.SetRenderState(RenderState::ZWriteEnable,		 false);

	// Begin 2D mode
	DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
	cDrawHelpers.Begin2DMode();

		// Draw the gradient quad, use degree instead of radian in here because humans tend to be able to imagine degree much better than radian
		cDrawHelpers.DrawGradientQuad(Color1.Get(), Color2.Get(), static_cast<float>(Angle.Get()*Math::DegToRad), Position.Get(), Size.Get());

	// End 2D mode
	cDrawHelpers.End2DMode();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
