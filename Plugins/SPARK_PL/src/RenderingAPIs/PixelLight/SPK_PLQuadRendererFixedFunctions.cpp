/*********************************************************\
 *  File: SPK_PLQuadRendererFixedFunctions.cpp           *
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
#include <PLCore/Tools/Tools.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Texture/TextureHandler.h>
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLBuffer.h"
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLQuadRendererFixedFunctions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
SPK_PLQuadRendererFixedFunctions *SPK_PLQuadRendererFixedFunctions::Create(PLRenderer::Renderer &cRenderer, float fScaleX, float fScaleY)
{
	SPK_PLQuadRendererFixedFunctions *pSPK_PLQuadRendererFixedFunctions = new SPK_PLQuadRendererFixedFunctions(cRenderer, fScaleX, fScaleY);
	registerObject(pSPK_PLQuadRendererFixedFunctions);
	return pSPK_PLQuadRendererFixedFunctions;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor of SPK_PLQuadRendererFixedFunctions
*/
SPK_PLQuadRendererFixedFunctions::SPK_PLQuadRendererFixedFunctions(PLRenderer::Renderer &cRenderer, float fScaleX, float fScaleY) : SPK_PLQuadRenderer(cRenderer, fScaleX, fScaleY),
	m_nTextureBlending(FixedFunctions::TextureEnvironment::Modulate)
{
}

/**
*  @brief
*    Destructor of SPK_PLQuadRendererFixedFunctions
*/
SPK_PLQuadRendererFixedFunctions::~SPK_PLQuadRendererFixedFunctions()
{
}

/**
*  @brief
*    Gets the texture blending function of this SPK_PLQuadRendererFixedFunctions
*/
FixedFunctions::TextureEnvironment::Enum SPK_PLQuadRendererFixedFunctions::GetTextureBlending() const
{
	return m_nTextureBlending;
}

/**
*  @brief
*    Sets the texture blending function of this SPK_PLQuadRendererFixedFunctions
*/
void SPK_PLQuadRendererFixedFunctions::SetTextureBlending(FixedFunctions::TextureEnvironment::Enum nTextureBlending)
{
	m_nTextureBlending = nTextureBlending;
}


//[-------------------------------------------------------]
//[ Public virtual SPK::Renderer functions                ]
//[-------------------------------------------------------]
void SPK_PLQuadRendererFixedFunctions::render(const SPK::Group &group)
{
	// Is there a valid m_pSPK_PLBuffer instance?
	if (prepareBuffers(group) && m_pSPK_PLBuffer && m_pSPK_PLBuffer->GetVertexBuffer()) {
		// Update the vertex buffer
		UpdateVertexBuffer(group);

		// Setup render states
		InitBlending();
		GetPLRenderer().SetRenderState(RenderState::ZEnable,      isRenderingHintEnabled(SPK::DEPTH_TEST));
		GetPLRenderer().SetRenderState(RenderState::ZWriteEnable, isRenderingHintEnabled(SPK::DEPTH_WRITE));

		// Get the fixed functions interface
		FixedFunctions *pFixedFunctions = GetPLRenderer().GetFixedFunctions();
		if (pFixedFunctions) {
			// Setup texture
			switch (texturingMode) {
				case SPK::TEXTURE_2D:
					m_pTextureHandler->Bind();
					pFixedFunctions->SetTextureStageState(0, FixedFunctions::TextureStage::ColorTexEnv, m_nTextureBlending);
					break;

				case SPK::TEXTURE_3D:
					m_pTextureHandler->Bind();
					pFixedFunctions->SetTextureStageState(0, FixedFunctions::TextureStage::ColorTexEnv, m_nTextureBlending);
					break;

				case SPK::TEXTURE_NONE:
					GetPLRenderer().SetTextureBuffer();
					break;
			}

			// Alpha test
			if (isRenderingHintEnabled(SPK::ALPHA_TEST)) {
				pFixedFunctions->SetRenderState(FixedFunctions::RenderState::AlphaTestEnable,    true);
				pFixedFunctions->SetRenderState(FixedFunctions::RenderState::AlphaTestFunction,  Compare::GreaterEqual);
				pFixedFunctions->SetRenderState(FixedFunctions::RenderState::AlphaTestReference, Tools::FloatToUInt32(getAlphaTestThreshold()));
			} else {
				pFixedFunctions->SetRenderState(FixedFunctions::RenderState::AlphaTestEnable, false);
			}

			// Make the index buffer to the current renderer index buffer
			IndexBuffer *pIndexBuffer = m_pSPK_PLBuffer->GetIndexBuffer();
			if (pIndexBuffer)
				GetPLRenderer().SetIndexBuffer(pIndexBuffer);

			// Make the vertex buffer to the current renderer vertex buffer
			pFixedFunctions->SetVertexBuffer(m_pSPK_PLBuffer->GetVertexBuffer());

			// Draw
			GetPLRenderer().DrawIndexedPrimitives(Primitive::TriangleList, 0, static_cast<uint32>(group.getNbParticles()*NumOfVerticesPerParticle-1), 0, static_cast<uint32>(group.getNbParticles()*NumOfIndicesPerParticle));
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL
