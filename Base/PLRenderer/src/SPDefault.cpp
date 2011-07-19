/*********************************************************\
 *  File: SPDefault.cpp                                  *
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
#include <PLCore/Tools/Timing.h>
#include <PLCore/Tools/Localization.h>
#include "PLRenderer/RendererContext.h"
#include "PLRenderer/Renderer/Font.h"
#include "PLRenderer/Renderer/Renderer.h"
#include "PLRenderer/Renderer/DrawHelpers.h"
#include "PLRenderer/Renderer/FontManager.h"
#include "PLRenderer/Renderer/SamplerStates.h"
#include "PLRenderer/Effect/EffectManager.h"
#include "PLRenderer/Material/MaterialManager.h"
#include "PLRenderer/SPDefault.h"


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
pl_implement_class(SPDefault)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SPDefault::SPDefault(Renderer &cRenderer) : SurfacePainter(cRenderer),
	m_fRotation(0.0f)
{
}

/**
*  @brief
*    Destructor
*/
SPDefault::~SPDefault()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::SurfacePainter functions  ]
//[-------------------------------------------------------]
void SPDefault::OnPaint(Surface &cSurface)
{
	// Get the used renderer
	Renderer &cRenderer = GetRenderer();

	// Clear the content of the current used render target (color to black and depth to 1.0 by default)
	cRenderer.Clear();

	// Begin 2D mode
	SamplerStates cSamplerStates;
	DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
	cDrawHelpers.Begin2DMode();

		// PixelLight logo
		Material *pMaterial = m_cLogoMaterial.GetResource();
		if (!pMaterial) {
			pMaterial = cRenderer.GetRendererContext().GetMaterialManager().LoadResource("Data/Textures/PLLogo.dds");
			if (pMaterial)
				m_cLogoMaterial.SetResource(pMaterial);
		}
		if (pMaterial) {
			TextureBuffer *pDiffuseMap = pMaterial->GetParameterTextureBuffer(Material::DiffuseMap);
			if (pDiffuseMap) {
				cRenderer.SetRenderState(RenderState::CullMode, Cull::None);
				cDrawHelpers.DrawImage(*pDiffuseMap, cSamplerStates, Vector2(0.4f + Math::Sin(m_fRotation)*0.4f, 0.4f + Math::Cos(m_fRotation*0.3f)*0.4f), Vector2(0.2f, 0.2f), Color4::White);
			}
		}

		// Draw text
		Font *pFont = reinterpret_cast<Font*>(cRenderer.GetFontManager().GetDefaultFontTexture());
		if (pFont)
			cDrawHelpers.DrawText(*pFont, PLT("Using surface painter PLRenderer::SPDefault, see PLEngine::RenderApplication on how to use your own painter"), Color4::White, Vector2(0.5f, 0.9f), Font::CenterText);

	// End 2D mode
	cDrawHelpers.End2DMode();

	// Increase the rotation by the current time difference (time past since the last frame)
	// -> Normally, such work should NOT be performed within the rendering step, but we want
	//    to keep the implementation simple in here...
	m_fRotation += Timing::GetInstance()->GetTimeDifference()*0.5f;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
