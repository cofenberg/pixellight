/*********************************************************\
 *  File: SPK_PLLineRenderer.cpp                         *
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
#include <PLGeneral/Tools/Tools.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4530) // "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	#include <Core/SPK_Group.h>
PL_WARNING_POP
#include "SPARK_PL/RenderingAPI/SPK_PLBuffer.h"
#include "SPARK_PL/RenderingAPI/SPK_PLLineRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGraphics;
using namespace PLRenderer;
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Private definitions                                   ]
//[-------------------------------------------------------]
const std::string SPK_PLLineRenderer::PLBufferName("SPK_PLLineRenderer_Buffer");


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
SPK_PLLineRenderer *SPK_PLLineRenderer::Create(PLRenderer::Renderer &cRenderer, float fLength, float fWidth)
{
	SPK_PLLineRenderer *pSPK_PLLineRenderer = new SPK_PLLineRenderer(cRenderer, fLength, fWidth);
	registerObject(pSPK_PLLineRenderer);
	return pSPK_PLLineRenderer;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
SPK_PLLineRenderer::SPK_PLLineRenderer(PLRenderer::Renderer &cRenderer, float fLength, float fWidth) : SPK_PLRenderer(cRenderer), SPK::LineRendererInterface(fLength, fWidth),
	m_pSPK_PLBuffer(nullptr)
{
}

/**
*  @brief
*    Destructor of SPK_PLLineRenderer
*/
SPK_PLLineRenderer::~SPK_PLLineRenderer()
{
}


//[-------------------------------------------------------]
//[ Public virtual SPK::Renderer functions                ]
//[-------------------------------------------------------]
void SPK_PLLineRenderer::render(const SPK::Group &group)
{
	if (prepareBuffers(group)) {
		// Is there a valid m_pSPK_PLBuffer instance?
		if (m_pSPK_PLBuffer && m_pSPK_PLBuffer->GetVertexBuffer()) {
			// Get the vertex buffer instance from m_pSPK_PLBuffer and lock it
			VertexBuffer *pVertexBuffer = m_pSPK_PLBuffer->GetVertexBuffer();
			if (pVertexBuffer->Lock(Lock::WriteOnly)) {
				// Vertex buffer data
				const uint32 nVertexSize = pVertexBuffer->GetVertexSize();
				float *pfPosition = static_cast<float*>(pVertexBuffer->GetData(0, VertexBuffer::Position));

				// Fill the vertex buffer with the current data
				for (size_t i=0, nCurrentVertex=0; i<group.getNbParticles(); i++) {
					// Get the particle
					const SPK::Particle &cParticle = group.getParticle(i);

					// Copy over the particle position into the vertex data
					pfPosition[0] = cParticle.position().x;
					pfPosition[1] = cParticle.position().y;
					pfPosition[2] = cParticle.position().z;
					pfPosition = reinterpret_cast<float*>(reinterpret_cast<char*>(pfPosition) + nVertexSize);	// Next, please!
					// Copy over the particle color into the vertex data
					pVertexBuffer->SetColor(nCurrentVertex, Color4(cParticle.getR(), cParticle.getG(), cParticle.getB(), cParticle.getParamCurrentValue(SPK::PARAM_ALPHA)));
					nCurrentVertex++;	// Next, please!

					// Copy over the particle position into the vertex data
					pfPosition[0] = cParticle.position().x + cParticle.velocity().x*length;
					pfPosition[1] = cParticle.position().y + cParticle.velocity().y*length;
					pfPosition[2] = cParticle.position().z + cParticle.velocity().z*length;
					pfPosition = reinterpret_cast<float*>(reinterpret_cast<char*>(pfPosition) + nVertexSize);	// Next, please!
					// Copy over the particle color into the vertex data
					pVertexBuffer->SetColor(nCurrentVertex, Color4(cParticle.getR(), cParticle.getG(), cParticle.getB(), cParticle.getParamCurrentValue(SPK::PARAM_ALPHA)));
					nCurrentVertex++;	// Next, please!
				}

				// Unlock the vertex buffer
				pVertexBuffer->Unlock();
			}

			// Setup render states
			InitBlending();
			InitRenderingHints();
			GetPLRenderer().SetRenderState(RenderState::LineWidth, Tools::FloatToUInt32(width));

			// Get the fixed functions interface
			FixedFunctions *pFixedFunctions = GetPLRenderer().GetFixedFunctions();
			if (pFixedFunctions) {
				// Make the vertex buffer to the current renderer vertex buffer
				pFixedFunctions->SetVertexBuffer(pVertexBuffer);

				// Draw
				GetPLRenderer().DrawPrimitives(Primitive::LineList, 0, group.getNbParticles() << 1);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Public virtual SPK::BufferHandler functions           ]
//[-------------------------------------------------------]
void SPK_PLLineRenderer::createBuffers(const SPK::Group &group)
{
	// Create the SPK_PLBuffer instance
	m_pSPK_PLBuffer = static_cast<SPK_PLBuffer*>(group.createBuffer(PLBufferName, PLBufferCreator(GetPLRenderer(), 14, 0, SPK::TEXTURE_NONE), 0U, false));
}

void SPK_PLLineRenderer::destroyBuffers(const SPK::Group &group)
{
	group.destroyBuffer(PLBufferName);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL
