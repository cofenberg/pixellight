/*********************************************************\
 *  File: SPK_PLPointRendererShaders.cpp                 *
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
PL_WARNING_PUSH
PL_WARNING_DISABLE(4530) // "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	// [HACK] There are missing forward declarations within the SPARK headers...
	namespace SPK {
		class Group;
	}
	#include <Core/SPK_Group.h>
PL_WARNING_POP
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLBuffer.h"
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLPointRendererShaders.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGraphics;
using namespace PLRenderer;
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
SPK_PLPointRendererShaders *SPK_PLPointRendererShaders::Create(PLRenderer::Renderer &cRenderer, float fSize)
{
	SPK_PLPointRendererShaders *pSPK_PLPointRendererShaders = new SPK_PLPointRendererShaders(cRenderer, fSize);
	registerObject(pSPK_PLPointRendererShaders);
	return pSPK_PLPointRendererShaders;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
SPK_PLPointRendererShaders::SPK_PLPointRendererShaders(PLRenderer::Renderer &cRenderer, float fSize) : SPK_PLPointRenderer(cRenderer, fSize)
{
}

/**
*  @brief
*    Destructor of SPK_PLPointRendererShaders
*/
SPK_PLPointRendererShaders::~SPK_PLPointRendererShaders()
{
}


//[-------------------------------------------------------]
//[ Public virtual SPK::Renderer functions                ]
//[-------------------------------------------------------]
void SPK_PLPointRendererShaders::render(const SPK::Group &group)
{
	// Is there a valid m_pSPK_PLBuffer instance?
	if (m_pSPK_PLBuffer && m_pSPK_PLBuffer->GetVertexBuffer()) {
		// Get the vertex buffer instance from m_pSPK_PLBuffer and lock it
		VertexBuffer *pVertexBuffer = m_pSPK_PLBuffer->GetVertexBuffer();
		if (pVertexBuffer->Lock(Lock::WriteOnly)) {
			// Vertex buffer data
			const uint32 nVertexSize = pVertexBuffer->GetVertexSize();
			float *pfPosition = static_cast<float*>(pVertexBuffer->GetData(0, VertexBuffer::Position));

			// Fill the vertex buffer with the current data
			for (size_t i=0; i<group.getNbParticles(); i++) {
				// Get the particle
				const SPK::Particle &cParticle = group.getParticle(i);

				// Copy over the particle position into the vertex data
				pfPosition[0] = cParticle.position().x;
				pfPosition[1] = cParticle.position().y;
				pfPosition[2] = cParticle.position().z;
				pfPosition = reinterpret_cast<float*>(reinterpret_cast<char*>(pfPosition) + nVertexSize);	// Next, please!

				// Copy over the particle color into the vertex data
				pVertexBuffer->SetColor(i, Color4(cParticle.getR(), cParticle.getG(), cParticle.getB(), group.getModel()->isEnabled(SPK::PARAM_ALPHA) ? cParticle.getParamCurrentValue(SPK::PARAM_ALPHA) : 1.0f));
			}

			// Unlock the vertex buffer
			pVertexBuffer->Unlock();
		}

		// [TODO] Implement me
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL
