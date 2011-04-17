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
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4530) // "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	// [HACK] There are missing forward declarations within the SPARK headers...
	namespace SPK {
		class Group;
	}
	#include <Core/SPK_Group.h>
	#include <Core/SPK_ArrayBuffer.h>
PL_WARNING_POP
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLBuffer.h"
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLLineTrailRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGraphics;
using namespace PLRenderer;
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Protected definitions                                 ]
//[-------------------------------------------------------]
const std::string SPK_PLLineTrailRenderer::VertexBufferName("SPK_GLLineTrailRenderer_Vertex");
const std::string SPK_PLLineTrailRenderer::ColorBufferName("SPK_GLLineTrailRenderer_Color");
const std::string SPK_PLLineTrailRenderer::ValueBufferName("SPK_GLLineTrailRenderer_Value");
const std::string SPK_PLLineTrailRenderer::PLBufferName("SPK_PLLineTrailRenderer_Buffer");


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
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
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor of SPK_PLLineTrailRenderer
*/
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
