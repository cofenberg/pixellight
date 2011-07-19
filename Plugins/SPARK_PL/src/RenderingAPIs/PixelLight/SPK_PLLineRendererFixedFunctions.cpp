/*********************************************************\
 *  File: SPK_PLLineRendererFixedFunctions.cpp           *
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
#include <PLCore/Tools/Tools.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4530) // "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	// [HACK] There are missing forward declarations within the SPARK headers...
	namespace SPK {
		class Group;
	}
	#include <Core/SPK_Group.h>
PL_WARNING_POP
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLBuffer.h"
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLLineRendererFixedFunctions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLGraphics;
using namespace PLRenderer;
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
SPK_PLLineRendererFixedFunctions *SPK_PLLineRendererFixedFunctions::Create(PLRenderer::Renderer &cRenderer, float fLength, float fWidth)
{
	SPK_PLLineRendererFixedFunctions *pSPK_PLLineRendererFixedFunctions = new SPK_PLLineRendererFixedFunctions(cRenderer, fLength, fWidth);
	registerObject(pSPK_PLLineRendererFixedFunctions);
	return pSPK_PLLineRendererFixedFunctions;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
SPK_PLLineRendererFixedFunctions::SPK_PLLineRendererFixedFunctions(PLRenderer::Renderer &cRenderer, float fLength, float fWidth) : SPK_PLLineRenderer(cRenderer, fLength, fWidth)
{
}

/**
*  @brief
*    Destructor of SPK_PLLineRendererFixedFunctions
*/
SPK_PLLineRendererFixedFunctions::~SPK_PLLineRendererFixedFunctions()
{
}


//[-------------------------------------------------------]
//[ Public virtual SPK::Renderer functions                ]
//[-------------------------------------------------------]
void SPK_PLLineRendererFixedFunctions::render(const SPK::Group &group)
{
	// Is there a valid m_pSPK_PLBuffer instance?
	if (prepareBuffers(group) && m_pSPK_PLBuffer && m_pSPK_PLBuffer->GetVertexBuffer()) {
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
		GetPLRenderer().SetRenderState(RenderState::ZEnable,      isRenderingHintEnabled(SPK::DEPTH_TEST));
		GetPLRenderer().SetRenderState(RenderState::ZWriteEnable, isRenderingHintEnabled(SPK::DEPTH_WRITE));
		GetPLRenderer().SetRenderState(RenderState::LineWidth,    Tools::FloatToUInt32(width));

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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL
