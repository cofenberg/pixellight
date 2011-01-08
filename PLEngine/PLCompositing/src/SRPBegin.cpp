/*********************************************************\
 *  File: SRPBegin.cpp                                   *
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
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLScene/Scene/SNCamera.h>
#include "PLCompositing/SRPBegin.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPBegin)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPBegin::SRPBegin() :
	TextureFormat(this),
	ClearFlags(this),
	ColorClear(this),
	FillMode(this),
	Flags(this),
	m_pOriginalRenderTarget(nullptr),
	m_bCurrentFrontRenderTarget(0)
{
	// Initialize the pointers to the render targets
	m_pRenderTarget[0] = m_pRenderTarget[1] = nullptr;
}

/**
*  @brief
*    Destructor
*/
SRPBegin::~SRPBegin()
{
	// Destroy the render targets
	if (m_pRenderTarget[0])
		delete m_pRenderTarget[0];
	if (m_pRenderTarget[1])
		delete m_pRenderTarget[1];
}

/**
*  @brief
*    Returns the render target that was set before the current render target was changed to the front/back render target
*/
Surface *SRPBegin::GetOriginalRenderTarget() const
{
	return m_pOriginalRenderTarget;
}

/**
*  @brief
*    Returns the current front render target
*/
SurfaceTextureBuffer *SRPBegin::GetFrontRenderTarget() const
{
	return m_pRenderTarget[m_bCurrentFrontRenderTarget];
}

/**
*  @brief
*    Returns the current back render target
*/
SurfaceTextureBuffer *SRPBegin::GetBackRenderTarget() const
{
	return m_pRenderTarget[!m_bCurrentFrontRenderTarget];
}

/**
*  @brief
*    Swaps the render targets
*/
void SRPBegin::SwapRenderTargets()
{
	// Both render targets must exist
	if (m_pRenderTarget[0] && m_pRenderTarget[1]) {
		// Swap the current front render target
		m_bCurrentFrontRenderTarget = !m_bCurrentFrontRenderTarget;

		// Pass on the depth buffer of the surface texture buffer
		m_pRenderTarget[!m_bCurrentFrontRenderTarget]->TakeDepthBufferFromSurfaceTextureBuffer(*m_pRenderTarget[m_bCurrentFrontRenderTarget]);

		// Set the new render target, we'll render into the back render target
		m_pRenderTarget[m_bCurrentFrontRenderTarget]->GetRenderer().SetRenderTarget(m_pRenderTarget[!m_bCurrentFrontRenderTarget]);
	}
}


//[-------------------------------------------------------]
//[ Protected virtual PLScene::SceneRendererPass functions ]
//[-------------------------------------------------------]
void SRPBegin::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	{ // Set all render states to known default settings
		cRenderer.ResetRenderStates();
	//	cRenderer.ResetTransformStates(); // Would also reset camera settings, not ok
		cRenderer.ResetSamplerStates();
		cRenderer.SetTextureBuffer();
		cRenderer.SetIndexBuffer();
		cRenderer.SetViewport();
		cRenderer.SetScissorRect();
		cRenderer.SetColorMask();

		// Fixed functions
		FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
		if (pFixedFunctions) {
			pFixedFunctions->SetColor();
			pFixedFunctions->ResetRenderStates();
			pFixedFunctions->ResetTextureStageStates();
			pFixedFunctions->ResetMaterialStates();
			pFixedFunctions->ResetLights();
			pFixedFunctions->SetClipPlaneEnabled();
			pFixedFunctions->SetClipPlane();
			pFixedFunctions->SetVertexBuffer();
		}

		// Draw helpers
		cRenderer.GetDrawHelpers().End2DMode();
		cRenderer.GetDrawHelpers().Set2DZValue();
	}

	// Get the currently set render target
	m_pOriginalRenderTarget = cRenderer.GetRenderTarget();
	if (m_pOriginalRenderTarget) {
		// Get the width and height of the viewport
		const Vector2i vRenderTargetSize = m_pOriginalRenderTarget->GetSize();

		// Create render targets or recreate them if required
		for (uint32 i=0; i<2; i++) {
			// Get the render target
			SurfaceTextureBuffer *pRenderTarget = m_pRenderTarget[i];
			if (pRenderTarget) {
				// Do we need to recreate this render target?
				const bool bRequestedStencilSetting = !(GetFlags() & NoStencil);
				const bool bCurrentStencilSetting   = (pRenderTarget->GetFlags() & SurfaceTextureBuffer::Stencil) != 0;
				const bool bRequestedMultisampleAntialiasingSetting = !(GetFlags() & NoMultisampleAntialiasing);
				const bool bCurrentMultisampleAntialiasingSetting   = !(pRenderTarget->GetFlags() & SurfaceTextureBuffer::NoMultisampleAntialiasing);
				if (pRenderTarget->GetFormat() != TextureFormat || pRenderTarget->GetSize() != vRenderTargetSize ||
					(i == 0 && (bRequestedStencilSetting != bCurrentStencilSetting || bRequestedMultisampleAntialiasingSetting != bCurrentMultisampleAntialiasingSetting))) {
					// Dam'n we have to recreate this render target :(
					delete pRenderTarget;
					pRenderTarget = nullptr;
					m_pRenderTarget[i] = nullptr;
				}
			}

			// Create render target if necessary
			if (!pRenderTarget && TextureFormat != TextureBuffer::Unknown) {
				// Flags
				uint32 nFlags = (GetFlags() & NoMultisampleAntialiasing) ? SurfaceTextureBuffer::NoMultisampleAntialiasing : 0;

				// Only one render target requires a depth&stencil buffer
				if (i == 0) {
					nFlags |= SurfaceTextureBuffer::Depth;
					if (!(GetFlags() & NoStencil))
						nFlags |= SurfaceTextureBuffer::Stencil;
				}

				// Create the render target
				m_pRenderTarget[i] = cRenderer.CreateSurfaceTextureBufferRectangle(vRenderTargetSize, (TextureBuffer::EPixelFormat)TextureFormat.GetInt(), nFlags);
				m_bCurrentFrontRenderTarget = 1;
			}
		}
	}

	// Set the current render target
	if (m_pRenderTarget[0] && m_pRenderTarget[1]) {
		// Set the new render target, we'll render into the back render target
		cRenderer.SetRenderTarget(m_pRenderTarget[!m_bCurrentFrontRenderTarget]);
	}

	// Set fill mode
	switch (FillMode) {
		case SolidMode:
			cRenderer.SetRenderState(RenderState::FixedFillMode, Fill::Solid);
			break;

		case LineMode:
			cRenderer.SetRenderState(RenderState::FixedFillMode, Fill::Line);
			break;

		case PointMode:
			cRenderer.SetRenderState(RenderState::FixedFillMode, Fill::Point);
			break;

		default:
			cRenderer.SetRenderState(RenderState::FixedFillMode, Fill::Solid);
			break;
	}

	// [TODO] Remove this
	// Setup cull mode
	cRenderer.SetRenderState(RenderState::InvCullMode, false);
	SNCamera *pCamera = SNCamera::GetCamera();
	if (pCamera)
		cRenderer.SetRenderState(RenderState::InvCullMode, pCamera->GetFlags() & SNCamera::InvCullMode);

	{ // Clear the color, depth and stencil buffer
		uint32 nFlags = 0;
		if (ClearFlags & ClearColor)
			nFlags |= Clear::Color;
		if (ClearFlags & ClearDepth)
			nFlags |= Clear::ZBuffer;
		if (!(GetFlags() & NoStencil) && (ClearFlags & ClearStencil))
			nFlags |= Clear::Stencil;
		cRenderer.Clear(nFlags, ColorClear.Get());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
