/*********************************************************\
 *  File: SPK_PLLineTrailRendererFixedFunctions.cpp      *
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
	// [HACK] There are missing forward declarations within the SPARK headers...
	namespace SPK {
		class Group;
	}
	#include <Core/SPK_Group.h>
PL_WARNING_POP
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLBuffer.h"
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLLineTrailRendererFixedFunctions.h"


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
/**
*  @brief
*    Creates and registers a new SPK_PLLineTrailRendererFixedFunctions
*/
SPK_PLLineTrailRendererFixedFunctions *SPK_PLLineTrailRendererFixedFunctions::Create(PLRenderer::Renderer &cRenderer)
{
	SPK_PLLineTrailRendererFixedFunctions *pSPK_PLLineTrailRendererFixedFunctions = new SPK_PLLineTrailRendererFixedFunctions(cRenderer);
	registerObject(pSPK_PLLineTrailRendererFixedFunctions);
	return pSPK_PLLineTrailRendererFixedFunctions;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
SPK_PLLineTrailRendererFixedFunctions::SPK_PLLineTrailRendererFixedFunctions(PLRenderer::Renderer &cRenderer) : SPK_PLLineTrailRenderer(cRenderer)
{
}

/**
*  @brief
*    Destructor of SPK_PLLineTrailRendererFixedFunctions
*/
SPK_PLLineTrailRendererFixedFunctions::~SPK_PLLineTrailRendererFixedFunctions()
{
}


//[-------------------------------------------------------]
//[ Public virtual SPK::Renderer functions                ]
//[-------------------------------------------------------]
void SPK_PLLineTrailRendererFixedFunctions::render(const SPK::Group &group)
{	
	// Is there a valid m_pSPK_PLBuffer instance?
	if (prepareBuffers(group) && m_pSPK_PLBuffer && m_pSPK_PLBuffer->GetVertexBuffer()) {
		// Update buffers
		for (size_t i=0; i<group.getNbParticles(); i++) {
			const SPK::Particle &cParticle = group.getParticle(i);
			float fAge = cParticle.getAge();
			float fOldAge = *m_pfValueIterator;

			if ((fAge == 0.0f) || (fAge < *m_pfValueIterator)) {
				// If the particle is new, buffers for it are reinitialized
				Init(cParticle, 0.0f);
			} else {
				if (fAge - *(m_pfValueIterator + 1) >= m_fDuration/(m_nNumOfSamples - 1)) {
					// Shifts the data by one
					memmove(m_pfVertexIterator + 6, m_pfVertexIterator + 3, (m_nNumOfSamples - 1)*3*sizeof(float));
					memmove(m_pfColorIterator + 8,  m_pfColorIterator + 4,  ((m_nNumOfSamples - 1) << 2)*sizeof(float));
					memmove(m_pfValueIterator + 1,  m_pfValueIterator,      (m_nNumOfSamples - 1)*sizeof(float));

					// Post degenerated vertex copy
					memcpy(m_pfVertexIterator + (m_nNumOfSamples + 1)*3, m_pfVertexIterator + m_nNumOfSamples*3, 3*sizeof(float));
				}

				// Updates the current sample
				const SPK::Vector3D &pos = cParticle.position();
				*(m_pfVertexIterator++) = pos.x;
				*(m_pfVertexIterator++) = pos.y;
				*(m_pfVertexIterator++) = pos.z;

				memcpy(m_pfVertexIterator, m_pfVertexIterator - 3, 3*sizeof(float));
				m_pfVertexIterator += (m_nNumOfSamples + 1)*3;

				m_pfColorIterator += 4; // Skips post degenerated vertex color
				*(m_pfColorIterator++) = cParticle.getR();
				*(m_pfColorIterator++) = cParticle.getG();
				*(m_pfColorIterator++) = cParticle.getB();
				*(m_pfColorIterator++) = cParticle.getParamCurrentValue(SPK::PARAM_ALPHA);
				m_pfColorIterator += 3;

				*(m_pfValueIterator++) = fAge;

				// Updates alpha
				for (uint32 i=0; i<m_nNumOfSamples-1; i++) {
					const float fRatio = (fAge - fOldAge)/(m_fDuration - fAge + *m_pfValueIterator);
					if (fRatio > 0.0f)
						*m_pfColorIterator *= (fRatio < 1.0f) ? 1.0f - fRatio : 0.0f;
					m_pfColorIterator += 4;
					++m_pfValueIterator;
				}
				++m_pfColorIterator;
			}
		}

		// Get the vertex buffer instance from m_pSPK_PLBuffer and lock it
		VertexBuffer *pVertexBuffer = m_pSPK_PLBuffer->GetVertexBuffer();
		if (pVertexBuffer->Lock(Lock::WriteOnly)) {
			// Vertex buffer data
			const uint32 nVertexSize = pVertexBuffer->GetVertexSize();
			float *pfPosition = static_cast<float*>(pVertexBuffer->GetData(0, VertexBuffer::Position));

			// Fill the vertex buffer with the current data
			m_pfVertexIterator = m_pfVertexBuffer;
			m_pfColorIterator = m_pfColorBuffer;
			for (size_t i=0; i<group.getNbParticles()*(m_nNumOfSamples + 2); i++) {
				// Copy over the particle position into the vertex data
				pfPosition[0] = m_pfVertexIterator[0];
				pfPosition[1] = m_pfVertexIterator[1];
				pfPosition[2] = m_pfVertexIterator[2];
				pfPosition = reinterpret_cast<float*>(reinterpret_cast<char*>(pfPosition) + nVertexSize);	// Next, please!
				m_pfVertexIterator += 3;	// Next, please!

				// Copy over the particle color into the vertex data
				pVertexBuffer->SetColor(i, Color4(m_pfColorIterator[0], m_pfColorIterator[1], m_pfColorIterator[2], m_pfColorIterator[3]));
				m_pfColorIterator += 4;	// Next, please!
			}

			// Unlock the vertex buffer
			pVertexBuffer->Unlock();
		}

		// Setup render states
		InitBlending();
		GetPLRenderer().SetRenderState(RenderState::ZEnable,      isRenderingHintEnabled(SPK::DEPTH_TEST));
		GetPLRenderer().SetRenderState(RenderState::ZWriteEnable, isRenderingHintEnabled(SPK::DEPTH_WRITE));
		GetPLRenderer().SetRenderState(RenderState::LineWidth,    Tools::FloatToUInt32(m_fWidth));

		// Get the fixed functions interface
		FixedFunctions *pFixedFunctions = GetPLRenderer().GetFixedFunctions();
		if (pFixedFunctions) {
			pFixedFunctions->SetRenderState(FixedFunctions::RenderState::ShadeMode, FixedFunctions::Shade::Smooth);

			// Make the vertex buffer to the current renderer vertex buffer
			pFixedFunctions->SetVertexBuffer(pVertexBuffer);

			// Draw
			GetPLRenderer().DrawPrimitives(Primitive::LineStrip, 0, group.getNbParticles()*(m_nNumOfSamples + 2));
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL
