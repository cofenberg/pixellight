/*********************************************************\
 *  File: SNBitmap2D.cpp                                 *
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
#include <PLMath/Rectangle.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Renderer/SamplerStates.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include "PLScene/Visibility/VisNode.h"
#include "PLScene/Scene/SceneNodes/SNBitmap2D.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNBitmap2D)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNBitmap2D::SNBitmap2D() :
	Width(this),
	Height(this),
	Flags(this)
{
	// Overwrite the default setting of the flags
	SetFlags(GetFlags()|NoCulling);

	// Set draw function flags
	SetDrawFunctionFlags(static_cast<uint8>(GetDrawFunctionFlags() | UseDrawPre | UseDrawPost));
}

/**
*  @brief
*    Destructor
*/
SNBitmap2D::~SNBitmap2D()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Draws the bitmap
*/
void SNBitmap2D::DrawBitmap(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Get the material
	PLRenderer::Material *pMaterial = GetMaterialHandler().GetResource();
	if (pMaterial) {
		// Fixed functions suppord required
		FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
		if (pFixedFunctions) {
			// Get the position
			Vector3 vPos2D;
			if (GetFlags() & Pos3D) {
				// Get the 2D screen position
				const Vector3 vPos3D = pVisNode ? pVisNode->GetWorldMatrix().GetTranslation() : GetTransform().GetPosition();
				Matrix4x4 mTransform = pFixedFunctions->GetTransformState(FixedFunctions::Transform::Projection);
				mTransform *= pFixedFunctions->GetTransformState(FixedFunctions::Transform::View);
				vPos2D = vPos3D.To2DCoordinate(mTransform, cRenderer.GetViewport());

				// Normalize this position (0...1)
				const Rectangle &cViewport = cRenderer.GetViewport();
				if (cViewport.GetWidth())
					vPos2D.x /= cViewport.GetWidth();
				if (cViewport.GetHeight())
					vPos2D.y /= cViewport.GetHeight();
			} else vPos2D = GetTransform().GetPosition();

			// Begin 2D mode
			const Vector3 &vScale = GetTransform().GetScale();
			SamplerStates cSamplerStates;
			DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
			cDrawHelpers.Begin2DMode();

				// Loop through all material passes
				for (uint32 nPass=0; nPass<pMaterial->GetNumOfPasses(); nPass++) {
					// Setup render states
					pMaterial->SetupPass(nPass);
					TextureBuffer *pTextureBuffer = cRenderer.GetTextureBuffer(0);
					if (pTextureBuffer) {
						// Set special bitmap color
						Color4 cColor = Color.Get();
						if (GetFlags() & IgnoreColor)
							cColor = pFixedFunctions->GetColor();

						// No culling, please
						cRenderer.SetRenderState(RenderState::CullMode, Cull::None);

						// Draw
						if (GetFlags() & Center) {
							cDrawHelpers.DrawImage(*pTextureBuffer, cSamplerStates, Vector2(vPos2D.x - Width*0.5f, vPos2D.y - Height*0.5f), Vector2(Width*vScale.x, Height*vScale.y),
												   Color4::White, 1.0f, GetTexelStart(), GetTexelEnd());
						} else {
							cDrawHelpers.DrawImage(*pTextureBuffer, cSamplerStates, vPos2D, Vector2(Width*vScale.x, Height*vScale.y),
												   Color4::White, 1.0f, GetTexelStart(), GetTexelEnd());
						}
					}
				}

			// End 2D mode
			cDrawHelpers.End2DMode();
		}
	}
}


//[-------------------------------------------------------]
//[ Public virtual SceneNode functions                    ]
//[-------------------------------------------------------]
void SNBitmap2D::DrawPre(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Call base implementation
	SNBitmap::DrawPre(cRenderer, pVisNode);

	// Background or foreground bitmap?
	if (GetFlags() & Background)
		DrawBitmap(cRenderer, pVisNode);
}

void SNBitmap2D::DrawPost(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Call base implementation
	SNBitmap::DrawPost(cRenderer, pVisNode);

	// Background or foreground bitmap?
	if (!(GetFlags() & Background))
		DrawBitmap(cRenderer, pVisNode);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
