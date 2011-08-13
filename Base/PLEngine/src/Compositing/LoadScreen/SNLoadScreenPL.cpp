/*********************************************************\
 *  File: SNLoadScreenPL.cpp                             *
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
#include <PLCore/Tools/Localization.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/Font.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Renderer/FontManager.h>
#include <PLRenderer/Renderer/SamplerStates.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLScene/Scene/SceneContext.h>
#include "PLEngine/Compositing/LoadScreen/SNLoadScreenPL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLScene;
namespace PLEngine {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNLoadScreenPL)


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNLoadScreenPL::SNLoadScreenPL() :
	ClearFlags(this),
	ClearColor(this),
	Flags(this)
{
	// Set draw function flags
	SetDrawFunctionFlags(static_cast<uint8>(GetDrawFunctionFlags() | UseDrawPost));
}

/**
*  @brief
*    Destructor
*/
SNLoadScreenPL::~SNLoadScreenPL()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Free's the used materials
*/
void SNLoadScreenPL::FreeMaterials()
{
	m_cLogoMaterial.SetResource();
}


//[-------------------------------------------------------]
//[ Public virtual PLScene::SceneNode functions           ]
//[-------------------------------------------------------]
void SNLoadScreenPL::DrawPost(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Call base implementation
	SNLoadScreenBase::DrawPost(cRenderer, pVisNode);

	// Hide the load screen?
	const float fProgress = GetLoadProgress();
	if (fProgress > 1.0f || fProgress < 0.0f) {
		// We do not longer need the used materials :)
		FreeMaterials();
	} else {
		// Clear the screen
		if (ClearFlags) {
			uint32 nFlags = 0;
			if (ClearFlags & Color)
				nFlags |= Clear::Color;
			if (ClearFlags & Depth)
				nFlags |= Clear::ZBuffer;
			if (ClearFlags & Stencil)
				nFlags |= Clear::Stencil;
			cRenderer.Clear(nFlags, ClearColor.Get());
		}

		// Setup render states
		cRenderer.GetRendererContext().GetEffectManager().Use();
		cRenderer.SetRenderState(RenderState::ZEnable,      false);
		cRenderer.SetRenderState(RenderState::ZWriteEnable, false);

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
					cDrawHelpers.DrawImage(*pDiffuseMap, cSamplerStates, Vector2(0.4f, 0.4f), Vector2(0.2f, 0.2f), Color4::White);
				}
			}

			// Draw text
			Font *pFont = cRenderer.GetFontManager().GetDefaultFontTexture();
			if (pFont)
				cDrawHelpers.DrawText(*pFont, PLT("Loading") + String::Format(" - %.0f %%", fProgress*100.0f), Color4::White, Vector2(0.5f, 0.9f), Font::CenterText);

		// End 2D mode
		cDrawHelpers.End2DMode();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
