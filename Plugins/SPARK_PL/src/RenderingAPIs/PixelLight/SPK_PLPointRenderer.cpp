/*********************************************************\
 *  File: SPK_PLPointRenderer.cpp                        *
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
#include <PLMath/Rectangle.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Texture/TextureHandler.h>
#include <PLScene/Scene/SNCamera.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4530) // "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	// [HACK] There are missing forward declarations within the SPARK headers...
	namespace SPK {
		class Group;
	}
	#include <Core/SPK_Group.h>
PL_WARNING_POP
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLBuffer.h"
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLPointRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLScene;
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Protected definitions                                 ]
//[-------------------------------------------------------]
const float		  SPK_PLPointRenderer::PointSizeCurrent	= 32.0f;
const float		  SPK_PLPointRenderer::PointSizeMin		= 1.0f;
const float		  SPK_PLPointRenderer::PointSizeMax		= 1024.0f;
const std::string SPK_PLPointRenderer::PLBufferName("SPK_PLPointRenderer_Buffer");


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor of SPK_PLPointRenderer
*/
SPK_PLPointRenderer::~SPK_PLPointRenderer()
{
	delete m_pTextureHandler;
}

/**
*  @brief
*    Tells whether world size is enabled or not in this SPK_PLPointRenderer
*/
bool SPK_PLPointRenderer::IsWorldSizeEnabled() const
{
	return m_bWorldSize;
}

/**
*  @brief
*   Sets the way size of points is computed in this SPK_PLPointRenderer
*/
bool SPK_PLPointRenderer::EnableWorldSize(bool bWorldSizeEnabled)
{
	// We can only use world size if point parameters are
	m_bWorldSize = (bWorldSizeEnabled && GetPLRenderer().GetCapabilities().bPointParameters);
	return m_bWorldSize;
}

/**
*  @brief
*    Computes a conversion ratio between pixels and universe units
*/
void SPK_PLPointRenderer::SetPixelPerUnit(float fFovY, int nScreenHeight)
{
	if (fFovY < 0.0f || nScreenHeight < 0) {
		m_fPixelPerUnit = -1.0f;
	} else {
		// The pixel per unit is computed for a distance from the camera of nScreenHeight
		m_fPixelPerUnit = nScreenHeight/(2.0f*Math::Tan(fFovY*0.5f));
	}
}

/**
*  @brief
*    Sets the texture of this SPK_PLPointRenderer
*/
Texture *SPK_PLPointRenderer::GetTexture() const
{
	return m_pTextureHandler->GetResource();
}

/**
*  @brief
*    Gets the texture of this SPK_PLPointRenderer
*/
void SPK_PLPointRenderer::SetTexture(Texture *pTexture)
{
	m_pTextureHandler->SetResource(pTexture);
}


//[-------------------------------------------------------]
//[ Public virtual SPK::PointRendererInterface functions  ]
//[-------------------------------------------------------]
bool SPK_PLPointRenderer::setType(SPK::PointType type)
{
	// We can only use point sprites if it is available
	if ((type != SPK::POINT_SPRITE) || GetPLRenderer().GetCapabilities().bPointSprite) {
		// *thumbs up* - all is fine
		this->type = type;

		// Done
		return true;
	} else {
		// *thumbs down* - the renderer is not capable of everything we need
		return false;
	}
}


//[-------------------------------------------------------]
//[ Public virtual SPK::BufferHandler functions           ]
//[-------------------------------------------------------]
void SPK_PLPointRenderer::createBuffers(const SPK::Group &group)
{
	// Create the SPK_PLBuffer instance
	m_pSPK_PLBuffer = static_cast<SPK_PLBuffer*>(group.createBuffer(PLBufferName, PLBufferCreator(GetPLRenderer(), 1, 0, SPK::TEXTURE_NONE), 0U, false));
}

void SPK_PLPointRenderer::destroyBuffers(const SPK::Group &group)
{
	group.destroyBuffer(PLBufferName);
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/** 
*  @brief
*    Constructor of SPK_PLPointRenderer
*/
SPK_PLPointRenderer::SPK_PLPointRenderer(PLRenderer::Renderer &cRenderer, float fSize) : SPK_PLRenderer(cRenderer), SPK::PointRendererInterface(SPK::POINT_SQUARE, fSize),
	m_pSPK_PLBuffer(nullptr),
	m_pTextureHandler(new TextureHandler()),
	m_bWorldSize(false),
	m_fPixelPerUnit(-1.0f)
{
}

/**
*  @brief
*    Enables the use of point parameters
*/
void SPK_PLPointRenderer::EnablePointParameter(float fSize, bool bDistance) const
{
	float fPixelPerUnit = m_fPixelPerUnit;
	if (fPixelPerUnit < 0.0f) {
		// The pixel per unit is computed for a distance from the camera of nScreenHeight
		const float fScreenHeight = GetPLRenderer().GetViewport().GetHeight();
		const float fFovY = SNCamera::GetCamera() ? static_cast<float>(SNCamera::GetCamera()->GetFOV()*Math::DegToRad) : 45.0f;
		fPixelPerUnit = fScreenHeight/(2.0f*Math::Tan(fFovY*0.5f));
	}

	// Derived size = size*sqrt(1/(A + B*distance + C*distance�))
	if (bDistance) {
		const float fSqrtC = PointSizeCurrent/(fSize*fPixelPerUnit);
		GetPLRenderer().SetRenderState(RenderState::PointScaleA, Tools::FloatToUInt32(0.0f));			// A = 0
		GetPLRenderer().SetRenderState(RenderState::PointScaleB, Tools::FloatToUInt32(0.0f));			// B = 0
		GetPLRenderer().SetRenderState(RenderState::PointScaleC, Tools::FloatToUInt32(fSqrtC*fSqrtC));	// C = (PointSizeCurrent/(size*fPixelPerUnit))^2
	} else {
		const float fSqrtA = PointSizeCurrent/fSize;
		GetPLRenderer().SetRenderState(RenderState::PointScaleA, Tools::FloatToUInt32(fSqrtA*fSqrtA));	// A = (PointSizeCurrent/size)^2
		GetPLRenderer().SetRenderState(RenderState::PointScaleB, Tools::FloatToUInt32(0.0f));			// B = 0
		GetPLRenderer().SetRenderState(RenderState::PointScaleC, Tools::FloatToUInt32(0.0f));			// C = 0
	}

	// Set point size and the minimum/maximum point size
	GetPLRenderer().SetRenderState(RenderState::PointSize,		  Tools::FloatToUInt32(PointSizeCurrent));
	GetPLRenderer().SetRenderState(RenderState::PointSizeMin,	  Tools::FloatToUInt32(PointSizeMin));
	GetPLRenderer().SetRenderState(RenderState::PointSizeMax,	  Tools::FloatToUInt32(PointSizeMax));
	GetPLRenderer().SetRenderState(RenderState::PointScaleEnable, true);
}

/**
*  @brief
*    Setup common render states
*/
void SPK_PLPointRenderer::SetupCommonRenderStates(const SPK::Group &group)
{
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
			pVertexBuffer->SetColor(static_cast<uint32>(i), Color4(cParticle.getR(), cParticle.getG(), cParticle.getB(), group.getModel()->isEnabled(SPK::PARAM_ALPHA) ? cParticle.getParamCurrentValue(SPK::PARAM_ALPHA) : 1.0f));
		}

		// Unlock the vertex buffer
		pVertexBuffer->Unlock();
	}

	// Setup render states
	InitBlending();
	GetPLRenderer().SetRenderState(RenderState::ZEnable,      isRenderingHintEnabled(SPK::DEPTH_TEST));
	GetPLRenderer().SetRenderState(RenderState::ZWriteEnable, isRenderingHintEnabled(SPK::DEPTH_WRITE));
	switch(type) {
		case SPK::POINT_SQUARE:
			GetPLRenderer().SetRenderState(RenderState::PointSpriteEnable, false);
			// [TODO] Currently, GL_POINT_SMOOTH is not supported by PLRenderer
			// glDisable(GL_POINT_SMOOTH);
			break;

		case SPK::POINT_SPRITE:
			GetPLRenderer().SetRenderState(RenderState::PointSpriteEnable, true);
			break;

		case SPK::POINT_CIRCLE:
			GetPLRenderer().SetRenderState(RenderState::PointSpriteEnable, false);
			// [TODO] Currently, GL_POINT_SMOOTH is not supported by PLRenderer
			// glEnable(GL_POINT_SMOOTH);
			break;
	}
	if (m_bWorldSize) {
		EnablePointParameter(size, true);
	} else {
		GetPLRenderer().SetRenderState(RenderState::PointScaleEnable, false);
		GetPLRenderer().SetRenderState(RenderState::PointSize,		  Tools::FloatToUInt32(size));
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL
