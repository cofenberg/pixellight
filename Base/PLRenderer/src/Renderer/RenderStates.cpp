/*********************************************************\
 *  File: RendersStates.cpp                              *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLRenderer/Renderer/RenderStates.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(RenderStates)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RenderStates::RenderStates() :
	FillMode(this),
	CullMode(this),
	ZEnable(this),
	ZWriteEnable(this),
	ZFunc(this),
	ZBias(this),
	SlopeScaleDepthBias(this),
	DepthBias(this),
	BlendEnable(this),
	SrcBlendFunc(this),
	DstBlendFunc(this),
	StencilEnable(this),
	StencilFunc(this),
	StencilRef(this),
	StencilMask(this),
	StencilFail(this),
	StencilZFail(this),
	StencilPass(this),
	TwoSidedStencilMode(this),
	CCWStencilFunc(this),
	CCWStencilFail(this),
	CCWStencilZFail(this),
	CCWStencilPass(this),
	PointSize(this),
	PointScaleEnable(this),
	PointSizeMin(this),
	PointSizeMax(this),
	PointScaleA(this),
	PointScaleB(this),
	PointScaleC(this),
	LineWidth(this),
	TessellationFactor(this),
// [TODO] Linux GCC: "error: changes meaning of ‘TessellationMode’ from ‘class PLRenderer::TessellationMode"
//	TessellationMode(this),
	PointSpriteEnable(this),
	DitherEnable(this),
	ScissorTestEnable(this),
	MultisampleEnable(this),
	InvCullMode(this),
	FixedFillMode(this)
{
	// Set default renderer states
	m_nRS[RenderState::FillMode] = Fill::Solid;
	m_nRS[RenderState::CullMode] = Cull::CCW;
	// Z buffer
	m_nRS[RenderState::ZEnable]             = true;
	m_nRS[RenderState::ZWriteEnable]        = true;
	m_nRS[RenderState::ZFunc]               = Compare::LessEqual;
	m_nRS[RenderState::ZBias]               = Tools::FloatToUInt32(0.0f);
	m_nRS[RenderState::SlopeScaleDepthBias] = Tools::FloatToUInt32(0.0f);
	m_nRS[RenderState::DepthBias]           = Tools::FloatToUInt32(0.0f);
	// Blend
	m_nRS[RenderState::BlendEnable]  = false;
	m_nRS[RenderState::SrcBlendFunc] = BlendFunc::SrcAlpha;
	m_nRS[RenderState::DstBlendFunc] = BlendFunc::InvSrcAlpha;
	// Stencil
	m_nRS[RenderState::StencilEnable]       = false;
	m_nRS[RenderState::StencilFunc]         = Compare::Always;
	m_nRS[RenderState::StencilRef]          = 0;
	m_nRS[RenderState::StencilMask]         = 0xFFFFFFFF;
	m_nRS[RenderState::StencilFail]         = StencilOp::Keep;
	m_nRS[RenderState::StencilZFail]        = StencilOp::Keep;
	m_nRS[RenderState::StencilPass]         = StencilOp::Keep;
	m_nRS[RenderState::TwoSidedStencilMode] = false;
	m_nRS[RenderState::CCWStencilFunc]      = Compare::Always;
	m_nRS[RenderState::CCWStencilFail]      = StencilOp::Keep;
	m_nRS[RenderState::CCWStencilZFail]     = StencilOp::Keep;
	m_nRS[RenderState::CCWStencilPass]      = StencilOp::Keep;
	// Point and line
	m_nRS[RenderState::PointSize]        = Tools::FloatToUInt32(1.0f);
	m_nRS[RenderState::PointScaleEnable] = false;
	m_nRS[RenderState::PointSizeMin]     = Tools::FloatToUInt32(1.0f);
	m_nRS[RenderState::PointSizeMax]     = Tools::FloatToUInt32(64.0f);
	m_nRS[RenderState::PointScaleA]      = Tools::FloatToUInt32(1.0f);
	m_nRS[RenderState::PointScaleB]      = Tools::FloatToUInt32(0.0f);
	m_nRS[RenderState::PointScaleC]      = Tools::FloatToUInt32(0.0f);
	m_nRS[RenderState::LineWidth]        = Tools::FloatToUInt32(1.0f);
	// Tessellation
	m_nRS[RenderState::TessellationFactor] = 1;
// [TODO] Linux GCC: "error: changes meaning of ‘TessellationMode’ from ‘class PLRenderer::TessellationMode"
//	m_nRS[RenderState::TessellationMode]   = TessellationMode::Discrete;
	// Misc
	m_nRS[RenderState::PointSpriteEnable] = false;
	m_nRS[RenderState::DitherEnable]      = false;
	m_nRS[RenderState::ScissorTestEnable] = false;
	m_nRS[RenderState::MultisampleEnable] = false;
	m_nRS[RenderState::InvCullMode]       = false;
	m_nRS[RenderState::FixedFillMode]     = Fill::Unknown;
}

/**
*  @brief
*    Copy constructor
*/
RenderStates::RenderStates(const RenderStates &cSource) :
	FillMode(this),
	CullMode(this),
	ZEnable(this),
	ZWriteEnable(this),
	ZFunc(this),
	ZBias(this),
	SlopeScaleDepthBias(this),
	DepthBias(this),
	BlendEnable(this),
	SrcBlendFunc(this),
	DstBlendFunc(this),
	StencilEnable(this),
	StencilFunc(this),
	StencilRef(this),
	StencilMask(this),
	StencilFail(this),
	StencilZFail(this),
	StencilPass(this),
	TwoSidedStencilMode(this),
	CCWStencilFunc(this),
	CCWStencilFail(this),
	CCWStencilZFail(this),
	CCWStencilPass(this),
	PointSize(this),
	PointScaleEnable(this),
	PointSizeMin(this),
	PointSizeMax(this),
	PointScaleA(this),
	PointScaleB(this),
	PointScaleC(this),
	LineWidth(this),
	TessellationFactor(this),
// [TODO] Linux GCC: "error: changes meaning of ‘TessellationMode’ from ‘class PLRenderer::TessellationMode"
//	TessellationMode(this),
	PointSpriteEnable(this),
	DitherEnable(this),
	ScissorTestEnable(this),
	MultisampleEnable(this),
	InvCullMode(this),
	FixedFillMode(this)
{
	// Copy states
	for (uint32 i=0; i<RenderState::Number; i++)
		m_nRS[i] = cSource.m_nRS[i];
}

/**
*  @brief
*    Destructor
*/
RenderStates::~RenderStates()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
