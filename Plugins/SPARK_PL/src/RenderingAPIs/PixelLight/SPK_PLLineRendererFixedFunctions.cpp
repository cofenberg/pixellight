/*********************************************************\
 *  File: SPK_PLLineRendererFixedFunctions.cpp           *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
				pVertexBuffer->SetColor(static_cast<uint32>(nCurrentVertex), Color4(cParticle.getR(), cParticle.getG(), cParticle.getB(), cParticle.getParamCurrentValue(SPK::PARAM_ALPHA)));
				nCurrentVertex++;	// Next, please!

				// Copy over the particle position into the vertex data
				pfPosition[0] = cParticle.position().x + cParticle.velocity().x*length;
				pfPosition[1] = cParticle.position().y + cParticle.velocity().y*length;
				pfPosition[2] = cParticle.position().z + cParticle.velocity().z*length;
				pfPosition = reinterpret_cast<float*>(reinterpret_cast<char*>(pfPosition) + nVertexSize);	// Next, please!
				// Copy over the particle color into the vertex data
				pVertexBuffer->SetColor(static_cast<uint32>(nCurrentVertex), Color4(cParticle.getR(), cParticle.getG(), cParticle.getB(), cParticle.getParamCurrentValue(SPK::PARAM_ALPHA)));
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
			GetPLRenderer().DrawPrimitives(Primitive::LineList, 0, static_cast<uint32>(group.getNbParticles() << 1));
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL
