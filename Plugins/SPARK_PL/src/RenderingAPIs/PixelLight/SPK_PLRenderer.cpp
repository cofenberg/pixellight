/*********************************************************\
 *  File: SPK_PLRenderer.cpp                             *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
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
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
SPK_PLRenderer::~SPK_PLRenderer()
{
}


//[-------------------------------------------------------]
//[ Public virtual SPK::Renderer functions                ]
//[-------------------------------------------------------]
void SPK_PLRenderer::setBlending(SPK::BlendingMode blendMode)
{
	switch (blendMode) {
		case SPK::BLENDING_NONE:
			m_nSrcBlending     = BlendFunc::One;
			m_nDestBlending    = BlendFunc::Zero;
			m_bBlendingEnabled = false;
			break;

		case SPK::BLENDING_ADD:
			m_nSrcBlending     = BlendFunc::SrcAlpha;
			m_nDestBlending    = BlendFunc::One;
			m_bBlendingEnabled = true;
			break;

		case SPK::BLENDING_ALPHA:
			m_nSrcBlending     = BlendFunc::SrcAlpha;
			m_nDestBlending    = BlendFunc::InvSrcAlpha;
			m_bBlendingEnabled = true;
			break;
	}
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
SPK_PLRenderer::SPK_PLRenderer(PLRenderer::Renderer &cRenderer) : Renderer(),
	m_pRenderer(&cRenderer),
	m_bBlendingEnabled(false),
	m_nSrcBlending(BlendFunc::SrcAlpha),
	m_nDestBlending(BlendFunc::InvSrcAlpha)
{
}

/**
*  @brief
*    Inits the blending of this SPK_PLRenderer
*/
void SPK_PLRenderer::InitBlending() const
{
	if (m_bBlendingEnabled) {
		m_pRenderer->SetRenderState(RenderState::SrcBlendFunc, m_nSrcBlending);
		m_pRenderer->SetRenderState(RenderState::DstBlendFunc, m_nDestBlending);
		m_pRenderer->SetRenderState(RenderState::BlendEnable, true);
	} else {
		m_pRenderer->SetRenderState(RenderState::BlendEnable, false);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL
