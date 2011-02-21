/*********************************************************\
 *  File: SPK_PLLineTrailRenderer.cpp                    *
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
	#include <Core/SPK_Particle.h>
	#include <Core/SPK_ArrayBuffer.h>
PL_WARNING_POP
#include "SPARK_PL/RenderingAPI/SPK_PLBuffer.h"
#include "SPARK_PL/RenderingAPI/SPK_PLLineTrailRenderer.h"


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
const std::string SPK_PLLineTrailRenderer::VertexBufferName("SPK_GLLineTrailRenderer_Vertex");
const std::string SPK_PLLineTrailRenderer::ColorBufferName("SPK_GLLineTrailRenderer_Color");
const std::string SPK_PLLineTrailRenderer::ValueBufferName("SPK_GLLineTrailRenderer_Value");
const std::string SPK_PLLineTrailRenderer::PLBufferName("SPK_PLLineTrailRenderer_Buffer");


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Creates and registers a new SPK_PLLineTrailRenderer
*/
SPK_PLLineTrailRenderer *SPK_PLLineTrailRenderer::Create(PLRenderer::Renderer &cRenderer)
{
	SPK_PLLineTrailRenderer *pSPK_PLLineTrailRenderer = new SPK_PLLineTrailRenderer(cRenderer);
	registerObject(pSPK_PLLineTrailRenderer);
	return pSPK_PLLineTrailRenderer;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
SPK_PLLineTrailRenderer::SPK_PLLineTrailRenderer(PLRenderer::Renderer &cRenderer) : SPK_PLRenderer(cRenderer),
	m_pSPK_PLBuffer(nullptr),
	m_nNumOfSamples(8),
	m_fWidth(1.0f),
	m_fDuration(1.0f),
	m_cColor(0.0f, 0.0f, 0.0f, 0.0f),
	m_pfVertexBuffer(nullptr),
	m_pfVertexIterator(nullptr),
	m_pfColorBuffer(nullptr),
	m_pfColorIterator(nullptr),
	m_pfValueBuffer(nullptr),
	m_pfValueIterator(nullptr)
{
	EnableBlending(true);
}

/**
*  @brief
*    Destructor of SPK_PLLineTrailRenderer
*/
SPK_PLLineTrailRenderer::~SPK_PLLineTrailRenderer()
{
}

/**
*  @brief
*    Gets the number of samples per trail
*/
uint32 SPK_PLLineTrailRenderer::GetNumOfSamples() const
{
	return m_nNumOfSamples;
}

/**
*  @brief
*    Sets the number of samples in a trail
*/
void SPK_PLLineTrailRenderer::SetNumOfSamples(uint32 nNumOfSamples)
{
	m_nNumOfSamples = nNumOfSamples;
}

/**
*  @brief
*    Gets the width of a trail
*/
float SPK_PLLineTrailRenderer::GetWidth() const
{
	return m_fWidth;
}

/**
*  @brief
*    Sets the width of a trail
*/
void SPK_PLLineTrailRenderer::SetWidth(float fWidth)
{
	m_fWidth = fWidth;
}

/**
*  @brief
*    Gets the duration of a sample
*/
float SPK_PLLineTrailRenderer::GetDuration() const
{
	return m_fDuration;
}

/**
*  @brief
*    Sets the duration of a sample
*/
void SPK_PLLineTrailRenderer::SetDuration(float fDuration)
{
	m_fDuration = fDuration;
}

/**
*  @brief
*    Gets the color components of degenerated lines
*/
const Color4 &SPK_PLLineTrailRenderer::GetDegeneratedLines() const
{
	return m_cColor;
}

/**
*  @brief
*    Sets the color components of degenerated lines
*/
void SPK_PLLineTrailRenderer::SetDegeneratedLines(const Color4 &cColor)
{
	m_cColor = cColor;
}

/**
*  @brief
*    Inits all the trails of the particle of the group
*/
void SPK_PLLineTrailRenderer::Init(const SPK::Group &cGroup)
{
	if (prepareBuffers(cGroup)) {
		for (size_t i=0; i<cGroup.getNbParticles(); i++) {
			const SPK::Particle &cParticle = cGroup.getParticle(i);
			Init(cParticle, cParticle.getAge());
		}
	}
}


//[-------------------------------------------------------]
//[ Public virtual SPK::Renderer functions                ]
//[-------------------------------------------------------]
void SPK_PLLineTrailRenderer::render(const SPK::Group &group)
{	
	if (prepareBuffers(group)) {
		// Is there a valid m_pSPK_PLBuffer instance?
		if (m_pSPK_PLBuffer && m_pSPK_PLBuffer->GetVertexBuffer()) {
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
			InitRenderingHints();
			GetPLRenderer().SetRenderState(RenderState::LineWidth, Tools::FloatToUInt32(m_fWidth));

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
}


//[-------------------------------------------------------]
//[ Public virtual SPK::BufferHandler functions           ]
//[-------------------------------------------------------]
void SPK_PLLineTrailRenderer::createBuffers(const SPK::Group &group)
{	
	SPK::FloatBuffer *fVertexBuffer = static_cast<SPK::FloatBuffer*>(group.createBuffer(VertexBufferName, SPK::FloatBufferCreator((m_nNumOfSamples + 2)*3), m_nNumOfSamples, true));
	SPK::FloatBuffer *fColorBuffer = static_cast<SPK::FloatBuffer*>(group.createBuffer(ColorBufferName, SPK::FloatBufferCreator((m_nNumOfSamples + 2) << 2), m_nNumOfSamples, true));
	SPK::FloatBuffer *fValueBuffer = static_cast<SPK::FloatBuffer*>(group.createBuffer(ValueBufferName, SPK::FloatBufferCreator(m_nNumOfSamples), m_nNumOfSamples, true));

	m_pfVertexIterator = m_pfVertexBuffer = fVertexBuffer->getData();
	m_pfColorIterator = m_pfColorBuffer = fColorBuffer->getData();
	m_pfValueIterator = m_pfValueBuffer = fValueBuffer->getData();

	// Fills the buffers with correct values
	for (size_t i=0; i<group.getNbParticles(); i++) {
		const SPK::Particle &cParticle = group.getParticle(i);
		Init(cParticle, cParticle.getAge());
	}

	// Resets the iterators at the beginning after the init
	m_pfVertexIterator = m_pfVertexBuffer;
	m_pfColorIterator = m_pfColorBuffer;
	m_pfValueIterator = m_pfValueBuffer;

	// Create the SPK_PLBuffer instance
	m_pSPK_PLBuffer = static_cast<SPK_PLBuffer*>(group.createBuffer(PLBufferName, PLBufferCreator(GetPLRenderer(), m_nNumOfSamples + 2, 0, SPK::TEXTURE_NONE), 0U, false));
}

void SPK_PLLineTrailRenderer::destroyBuffers(const SPK::Group &group)
{
	group.destroyBuffer(VertexBufferName);
	group.destroyBuffer(ColorBufferName);
	group.destroyBuffer(ValueBufferName);
	group.destroyBuffer(PLBufferName);
}


//[-------------------------------------------------------]
//[ Protected virtual SPK::BufferHandler functions        ]
//[-------------------------------------------------------]
bool SPK_PLLineTrailRenderer::checkBuffers(const SPK::Group &group)
{
	SPK::FloatBuffer *pVertexBuffer = static_cast<SPK::FloatBuffer*>(group.getBuffer(VertexBufferName, m_nNumOfSamples));
	if (!pVertexBuffer)
		return false;
	SPK::FloatBuffer *pColorBuffer = static_cast<SPK::FloatBuffer*>(group.getBuffer(ColorBufferName, m_nNumOfSamples));
	if (!pColorBuffer)
		return false;
	SPK::FloatBuffer *pValueBuffer = static_cast<SPK::FloatBuffer*>(group.getBuffer(ValueBufferName, m_nNumOfSamples));
	if (!pValueBuffer)
		return false;

	m_pfVertexIterator = m_pfVertexBuffer = pVertexBuffer->getData();
	m_pfColorIterator = m_pfColorBuffer = pColorBuffer->getData();
	m_pfValueIterator = m_pfValueBuffer = pValueBuffer->getData();

	return true;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Inits a given particle
*/
void SPK_PLLineTrailRenderer::Init(const SPK::Particle &cParticle, float fAge)
{
	// Gets the particle's values
	const SPK::Vector3D &vPos = cParticle.position();
	const float r = cParticle.getR();
	const float g = cParticle.getG();
	const float b = cParticle.getB();
	const float a = cParticle.getParamCurrentValue(SPK::PARAM_ALPHA);

	// Inits position
	for (uint32 i=0; i<m_nNumOfSamples+2; i++) {
		*(m_pfVertexIterator++) = vPos.x;
		*(m_pfVertexIterator++) = vPos.y;
		*(m_pfVertexIterator++) = vPos.z;
	}

	// Inits color
	// Degenerate pre vertex
	*(m_pfColorIterator++) = m_cColor.r;
	*(m_pfColorIterator++) = m_cColor.g;
	*(m_pfColorIterator++) = m_cColor.b;
	*(m_pfColorIterator++) = m_cColor.a;

	for (uint32 i=0; i<m_nNumOfSamples; i++) {
		*(m_pfColorIterator++) = r;
		*(m_pfColorIterator++) = g;
		*(m_pfColorIterator++) = b;
		*(m_pfColorIterator++) = a;
	}

	// Degenerate post vertex
	*(m_pfColorIterator++) = m_cColor.r;
	*(m_pfColorIterator++) = m_cColor.g;
	*(m_pfColorIterator++) = m_cColor.b;
	*(m_pfColorIterator++) = m_cColor.a;

	// Inits age
	for (uint32 i=0; i<m_nNumOfSamples; i++)
		*(m_pfValueIterator++) = fAge;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL
