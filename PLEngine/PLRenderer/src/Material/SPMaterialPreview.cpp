/*********************************************************\
 *  File: SPMaterialPreview.cpp                          *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLRenderer/Material/MaterialManager.h"
#include "PLRenderer/Material/SPMaterialPreview.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SPMaterialPreview)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SPMaterialPreview::SPMaterialPreview(Renderer &cRenderer) : SPPreview(cRenderer)
{
}

/**
*  @brief
*    Destructor
*/
SPMaterialPreview::~SPMaterialPreview()
{
}

/**
*  @brief
*    Returns the name of the used material
*/
String SPMaterialPreview::GetMaterial() const
{
	return m_sMaterial;
}

/**
*  @brief
*    Sets the name of the used material
*/
void SPMaterialPreview::SetMaterial(const String &sName)
{
	m_sMaterial = sName;
}


//[-------------------------------------------------------]
//[ Private virtual SurfacePainter functions              ]
//[-------------------------------------------------------]
void SPMaterialPreview::OnPaint(Surface &cSurface)
{
	// Get the used renderer
	Renderer &cRenderer = GetRenderer();

	// Set all render states to known default settings
	cRenderer.Reset();

	// Clear the frame buffer
	cRenderer.Clear();

	// Get the used material
	Material *pMaterial = cRenderer.GetRendererContext().GetMaterialManager().Get(m_sMaterial);
	if (pMaterial) {
		// Begin 2D mode
		DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
		cDrawHelpers.Begin2DMode();

			// Draw image (we have to flip the result upside-down...)
			SamplerStates cSamplerStates;
			for (uint32 i=0; i<pMaterial->GetNumOfPasses(); i++) {
				pMaterial->SetupPass(i);
				TextureBuffer *pTextureBuffer = cRenderer.GetTextureBuffer(0);
				if (pTextureBuffer) {
					cRenderer.SetRenderState(RenderState::CullMode, Cull::None);
					cDrawHelpers.DrawImage(*pTextureBuffer, cSamplerStates, Vector2(m_vCameraPosition.x-m_vCameraPosition.z, m_vCameraPosition.y-m_vCameraPosition.z), Vector2(m_vCameraPosition.z*2, m_vCameraPosition.z*2),
										   Color4::White, 1.0f, Vector2(1.0f, 1.0f), Vector2(-1.0f, -1.0f));
				}
			}

		// End 2D mode
		cDrawHelpers.End2DMode();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
