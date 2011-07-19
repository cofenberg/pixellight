/*********************************************************\
 *  File: SPEffectPreview.cpp                            *
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
#include "PLRenderer/RendererContext.h"
#include "PLRenderer/Renderer/DrawHelpers.h"
#include "PLRenderer/Renderer/SamplerStates.h"
#include "PLRenderer/Effect/EffectManager.h"
#include "PLRenderer/Effect/EffectTechnique.h"
#include "PLRenderer/Effect/EffectPass.h"
#include "PLRenderer/Effect/SPEffectPreview.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SPEffectPreview)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SPEffectPreview::SPEffectPreview(Renderer &cRenderer) : SPPreview(cRenderer)
{
}

/**
*  @brief
*    Destructor
*/
SPEffectPreview::~SPEffectPreview()
{
}

/**
*  @brief
*    Returns the name of the used effect
*/
String SPEffectPreview::GetEffect() const
{
	return m_sEffect;
}

/**
*  @brief
*    Sets the name of the used effect
*/
void SPEffectPreview::SetEffect(const String &sName)
{
	m_sEffect = sName;
}


//[-------------------------------------------------------]
//[ Private virtual SurfacePainter functions              ]
//[-------------------------------------------------------]
void SPEffectPreview::OnPaint(Surface &cSurface)
{
	// Get the used renderer
	Renderer &cRenderer = GetRenderer();

	// Get the used effect
	Effect *pEffect = cRenderer.GetRendererContext().GetEffectManager().GetByName(m_sEffect);
	if (pEffect) {
		// Set all render states to known default settings
		cRenderer.Reset();

		// Clear the frame buffer
		cRenderer.Clear();

		// Draw
		const EffectTechnique *pTechnique = pEffect->GetSelectedTechnique();
		if (pTechnique) {
			// Begin 2D mode
			DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
			cDrawHelpers.Begin2DMode();

				// Draw image (we have to flip the result upside-down...)
				SamplerStates cSamplerStates;
				for (uint32 i=0; i<pTechnique->GetNumOfPasses(); i++) {
					EffectPass *pEffectPass = pTechnique->GetPass(i);
					TextureBuffer *pTextureBuffer = cRenderer.GetTextureBuffer(0);
					if (pTextureBuffer) {
						cRenderer.SetRenderState(RenderState::CullMode, Cull::None);
						cDrawHelpers.DrawImage(*pTextureBuffer, cSamplerStates, Vector2(m_vCameraPosition.x-m_vCameraPosition.z, m_vCameraPosition.y-m_vCameraPosition.z), Vector2(m_vCameraPosition.z*2, m_vCameraPosition.z*2), pEffectPass->GetColor(),
											   1.0f, Vector2(1.0f, 1.0f), Vector2(-1.0f, -1.0f));
					}
				}

			// End 2D mode
			cDrawHelpers.End2DMode();
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
