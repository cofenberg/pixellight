/*********************************************************\
 *  File: SPK_PLRenderer.cpp                             *
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
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
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
