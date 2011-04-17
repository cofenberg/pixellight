/*********************************************************\
 *  File: SPK_PLQuadRendererFixedFunctions.cpp           *
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
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Texture/TextureHandler.h>
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLBuffer.h"
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLQuadRendererFixedFunctions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
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
	if (prepareBuffers(group)) {
		// Is there a valid m_pSPK_PLBuffer instance?
		if (m_pSPK_PLBuffer && m_pSPK_PLBuffer->GetVertexBuffer()) {
			// Setup render states
			InitBlending();
			InitRenderingHints();
			void (SPK_PLQuadRendererFixedFunctions::*pRenderParticle)(const SPK::Particle&);	// Pointer to the right render method
			switch (texturingMode) {
				case SPK::TEXTURE_2D:
					m_pTextureHandler->Bind();
					if (group.getModel()->isEnabled(SPK::PARAM_TEXTURE_INDEX))
						pRenderParticle = group.getModel()->isEnabled(SPK::PARAM_ANGLE) ? &SPK_PLQuadRendererFixedFunctions::Render2DAtlasRot : &SPK_PLQuadRendererFixedFunctions::Render2DAtlas;
					else
						pRenderParticle = group.getModel()->isEnabled(SPK::PARAM_ANGLE) ? &SPK_PLQuadRendererFixedFunctions::Render2DRot : &SPK_PLQuadRendererFixedFunctions::Render2D;

					{ // Get the fixed functions interface
						FixedFunctions *pFixedFunctions = GetPLRenderer().GetFixedFunctions();
						if (pFixedFunctions)
							pFixedFunctions->SetTextureStageState(0, FixedFunctions::TextureStage::ColorTexEnv, m_nTextureBlending);
					}
					break;

				case SPK::TEXTURE_3D:
					m_pTextureHandler->Bind();
					pRenderParticle = group.getModel()->isEnabled(SPK::PARAM_ANGLE) ? &SPK_PLQuadRendererFixedFunctions::Render3DRot : &SPK_PLQuadRendererFixedFunctions::Render3D;

					{ // Get the fixed functions interface
						FixedFunctions *pFixedFunctions = GetPLRenderer().GetFixedFunctions();
						if (pFixedFunctions)
							pFixedFunctions->SetTextureStageState(0, FixedFunctions::TextureStage::ColorTexEnv, m_nTextureBlending);
					}
					break;

				case SPK::TEXTURE_NONE:
					GetPLRenderer().SetTextureBuffer();
					pRenderParticle = group.getModel()->isEnabled(SPK::PARAM_ANGLE) ? &SPK_PLQuadRendererFixedFunctions::Render2DRot : &SPK_PLQuadRendererFixedFunctions::Render2D;
					break;

				default:
					pRenderParticle = nullptr;
					break;
			}

			// Get the vertex buffer instance from m_pSPK_PLBuffer and lock it
			VertexBuffer *pVertexBuffer = m_pSPK_PLBuffer->GetVertexBuffer();
			if (pVertexBuffer->Lock(Lock::WriteOnly)) {
				// Get the inverse of the current view matrix
				FixedFunctions *pFixedFunctions = GetPLRenderer().GetFixedFunctions();
				const Matrix4x4 &mView   = pFixedFunctions ? pFixedFunctions->GetTransformState(FixedFunctions::Transform::View)  : Matrix4x4::Identity;
				const Matrix4x4 &mWorld  = pFixedFunctions ? pFixedFunctions->GetTransformState(FixedFunctions::Transform::World) : Matrix4x4::Identity;
				const Matrix4x4 mViewInv = (mView*mWorld).GetInverted();

				// Get current vertex buffer data
				m_nCurrentVertexSize	= pVertexBuffer->GetVertexSize();
				m_pfCurrentPosition		= static_cast<float*>(pVertexBuffer->GetData(0, VertexBuffer::Position));
				m_pfCurrentTexCoord		= static_cast<float*>(pVertexBuffer->GetData(0, VertexBuffer::TexCoord));
				m_pCurrentVertexBuffer	= pVertexBuffer;
				m_nCurrentVertex		= 0;

				// Calculate the current orientation
				const bool bGlobalOrientation = precomputeOrientation3D(
					group,
					SPK::Vector3D(-mViewInv.fM[8],  -mViewInv.fM[9],  -mViewInv.fM[10]),
					SPK::Vector3D( mViewInv.fM[4],   mViewInv.fM[5],   mViewInv.fM[6]),
					SPK::Vector3D( mViewInv.fM[12],  mViewInv.fM[13],  mViewInv.fM[14]));
				if (pRenderParticle) {
					if (bGlobalOrientation) {
						computeGlobalOrientation3D();
						for (size_t i=0; i<group.getNbParticles(); i++)
							(this->*pRenderParticle)(group.getParticle(i));
					} else {
						for (size_t i=0; i<group.getNbParticles(); i++) {
							const SPK::Particle &cParticle = group.getParticle(i);
							computeSingleOrientation3D(cParticle);
							(this->*pRenderParticle)(cParticle);
						}
					}
				}

				// Unlock the vertex buffer
				pVertexBuffer->Unlock();
			}

			// Get the fixed functions interface
			FixedFunctions *pFixedFunctions = GetPLRenderer().GetFixedFunctions();
			if (pFixedFunctions) {
				// Make the index buffer to the current renderer index buffer
				IndexBuffer *pIndexBuffer = m_pSPK_PLBuffer->GetIndexBuffer();
				if (pIndexBuffer)
					GetPLRenderer().SetIndexBuffer(pIndexBuffer);

				// Make the vertex buffer to the current renderer vertex buffer
				pFixedFunctions->SetVertexBuffer(pVertexBuffer);

				// Draw
				GetPLRenderer().DrawIndexedPrimitives(Primitive::TriangleList, 0, group.getNbParticles()*NumOfVerticesPerParticle-1, 0, group.getNbParticles()*NumOfIndicesPerParticle);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL
