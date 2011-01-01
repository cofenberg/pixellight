/*********************************************************\
 *  File: SRPEnd.cpp                                     *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/Surface.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Renderer/SamplerStates.h>
#include <PLRenderer/Effect/EffectManager.h>
#include "PLCompositing/SRPBegin.h"
#include "PLCompositing/SRPEnd.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPEnd)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPEnd::SRPEnd()
{
}

/**
*  @brief
*    Destructor
*/
SRPEnd::~SRPEnd()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPEnd::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Get the "PLCompositing::SRPBegin" instance
	SRPBegin *pSRPBegin = (SRPBegin*)GetFirstInstanceOfSceneRendererPassClass("PLCompositing::SRPBegin");
	if (pSRPBegin) {
		// Get the original set render target
		Surface *pSurface = pSRPBegin->GetOriginalRenderTarget();
		if (pSurface) {
			// Is this already the current render target?
			if (pSurface != cRenderer.GetRenderTarget()) {
				// Get the back render target of SRPBegin, this holds the current content
				SurfaceTextureBuffer *pSurfaceTextureBuffer = pSRPBegin->GetBackRenderTarget();
				if (pSurfaceTextureBuffer) {
					// Set the current render target back to the orignal one
					cRenderer.SetRenderTarget(pSurface);

					// Setup renderer
					const uint32 nFixedFillModeBackup = cRenderer.GetRenderState(RenderState::FixedFillMode);
					cRenderer.GetRendererContext().GetEffectManager().Use();
					cRenderer.SetRenderState(RenderState::FixedFillMode, Fill::Solid);
					cRenderer.SetRenderState(RenderState::CullMode,     Cull::None);
					cRenderer.SetRenderState(RenderState::ZEnable,      false);
					cRenderer.SetRenderState(RenderState::ZWriteEnable, false);

					// Begin 2D mode
					DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
					cDrawHelpers.Begin2DMode();

						// Draw the result (we have to flip the result upside-down...)
						SamplerStates cSamplerStates;
						cSamplerStates.Set(Sampler::MipFilter, TextureFiltering::None);
						cSamplerStates.Set(Sampler::MipFilter, TextureFiltering::None);
						cSamplerStates.Set(Sampler::MipFilter, TextureFiltering::None);
						cDrawHelpers.DrawImage(*pSurfaceTextureBuffer->GetTextureBuffer(), cSamplerStates, Vector2::Zero, Vector2::One, Color4::White, 1.0f, Vector2(0.0f, 1.0f), Vector2(1.0f, -1.0f));

					// End 2D mode
					cDrawHelpers.End2DMode();

					// Restore fixed fill mode render state
					cRenderer.SetRenderState(RenderState::FixedFillMode, nFixedFillModeBackup);
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
