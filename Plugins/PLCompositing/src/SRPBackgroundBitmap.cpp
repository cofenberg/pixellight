/*********************************************************\
 *  File: SRPBackgroundBitmap.cpp                        *
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
#include <PLGeneral/File/Url.h>
#include <PLMath/Matrix4x4.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Renderer/SamplerStates.h>
#include <PLRenderer/Material/MaterialManager.h>
#include "PLCompositing/SRPBackgroundBitmap.h"


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
pl_implement_class(SRPBackgroundBitmap)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String SRPBackgroundBitmap::GetMaterial() const
{
	return m_sMaterial;
}

void SRPBackgroundBitmap::SetMaterial(const String &sValue)
{
	// Material change?
	if (m_sMaterial != sValue) {
		m_sMaterial = sValue;
		m_bLoaded = false;
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPBackgroundBitmap::SRPBackgroundBitmap() :
	Material(this),
	Color(this),
	Position(this),
	Size(this),
	TexelStart(this),
	TexelEnd(this),
	Flags(this),
	m_bLoaded(false)
{
}

/**
*  @brief
*    Destructor
*/
SRPBackgroundBitmap::~SRPBackgroundBitmap()
{
}

/**
*  @brief
*    Returns the handler of the material
*/
const MaterialHandler &SRPBackgroundBitmap::GetMaterialHandler()
{
	// Load material?
	if (!m_bLoaded) {
		LoadMaterial();
		m_bLoaded = true;
	}
	return m_cMaterial;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loads the material
*/
void SRPBackgroundBitmap::LoadMaterial()
{
	// Get the renderer
	Renderer *pRenderer = GetRenderer();
	if (pRenderer) {
		// Load material
		PLRenderer::Material *pMaterial = m_sMaterial.GetLength() ? pRenderer->GetRendererContext().GetMaterialManager().LoadResource(m_sMaterial) : nullptr;
		m_cMaterial.SetResource(pMaterial);

		// Check whether this is a material or an effect, if not, we need to set a default effect
		if (pMaterial) {
			const String sExtension = Url(pMaterial->GetName()).GetExtension();
			if (sExtension != "mat" && sExtension != "plfx") {
				PLRenderer::Material *pDefaultMaterial = GetRenderer()->GetRendererContext().GetMaterialManager().LoadResource("Data/Effects/DefaultBitmap.plfx");
				if (pDefaultMaterial)
					pMaterial->SetEffect(pDefaultMaterial->GetEffect());
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPBackgroundBitmap::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Get the material
	PLRenderer::Material *pMaterial = GetMaterialHandler().GetResource();
	if (pMaterial) {
		// Begin 2D mode
		DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
		cDrawHelpers.Begin2DMode();

			// Loop through all material passes
			SamplerStates cSamplerStates;
			for (uint32 nPass=0; nPass<pMaterial->GetNumOfPasses(); nPass++) {
				// Setup render states
				pMaterial->SetupPass(nPass);
				TextureBuffer *pTextureBuffer = cRenderer.GetTextureBuffer(0);
				if (pTextureBuffer) {
					// Setup renderer
					cRenderer.SetRenderState(RenderState::CullMode,     Cull::None);
					cRenderer.SetRenderState(RenderState::ZEnable,      false);
					cRenderer.SetRenderState(RenderState::ZWriteEnable, false);

					// Set special bitmap color
					Color4 cColor = Color.Get();
					// [TODO] Figure out the color without using fixed functions to read back a previously set color!
		//			if (GetFlags() & IgnoreColor)
		//				cColor = pFixedFunctions->GetColor();

					// Draw the bitmap
					cDrawHelpers.DrawImage(*pTextureBuffer, cSamplerStates, Position.Get(), Size.Get(), cColor, 0.5f, TexelStart.Get(), TexelEnd.Get() - TexelStart.Get());
				}
			}

		// End 2D mode
		cDrawHelpers.End2DMode();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
