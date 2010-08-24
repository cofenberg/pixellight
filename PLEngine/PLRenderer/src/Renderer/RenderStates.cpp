/*********************************************************\
 *  File: RendersStates.cpp                              *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLRenderer/Renderer/RenderStates.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(RenderStates)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
// Modes
Fill::Enum RenderStates::GetFillMode() const
{
	return (Fill::Enum)m_nRS[RenderState::FillMode];
}

void RenderStates::SetFillMode(Fill::Enum nValue)
{
	m_nRS[RenderState::FillMode] = nValue;
}

Cull::Enum RenderStates::GetCullMode() const
{
	return (Cull::Enum)m_nRS[RenderState::CullMode];
}

void RenderStates::SetCullMode(Cull::Enum nValue)
{
	m_nRS[RenderState::CullMode] = nValue;
}

// Z buffer
bool RenderStates::GetZEnable() const
{
	return m_nRS[RenderState::ZEnable] != 0;
}

void RenderStates::SetZEnable(bool bValue)
{
	m_nRS[RenderState::ZEnable] = bValue;
}

bool RenderStates::GetZWriteEnable() const
{
	return m_nRS[RenderState::ZWriteEnable] != 0;
}

void RenderStates::SetZWriteEnable(bool bValue)
{
	m_nRS[RenderState::ZWriteEnable] = bValue;
}

Compare::Enum RenderStates::GetZFunc() const
{
	return (Compare::Enum)m_nRS[RenderState::ZFunc];
}

void RenderStates::SetZFunc(Compare::Enum nValue)
{
	m_nRS[RenderState::ZFunc] = nValue;
}

float RenderStates::GetZBias() const
{
	return Tools::UInt32ToFloat(m_nRS[RenderState::ZBias]);
}

void RenderStates::SetZBias(float fValue)
{
	m_nRS[RenderState::ZBias] = Tools::FloatToUInt32(fValue);
}

float RenderStates::GetSlopeScaleDepthBias() const
{
	return Tools::UInt32ToFloat(m_nRS[RenderState::SlopeScaleDepthBias]);
}

void RenderStates::SetSlopeScaleDepthBias(float fValue)
{
	m_nRS[RenderState::SlopeScaleDepthBias] = Tools::FloatToUInt32(fValue);
}

float RenderStates::GetDepthBias() const
{
	return Tools::UInt32ToFloat(m_nRS[RenderState::DepthBias]);
}

void RenderStates::SetDepthBias(float fValue)
{
	m_nRS[RenderState::DepthBias] = Tools::FloatToUInt32(fValue);
}

// Blend
bool RenderStates::GetBlendEnable() const
{
	return m_nRS[RenderState::BlendEnable] != 0;
}

void RenderStates::SetBlendEnable(bool bValue)
{
	m_nRS[RenderState::BlendEnable] = bValue;
}

BlendFunc::Enum RenderStates::GetSrcBlendFunc() const
{
	return (BlendFunc::Enum)m_nRS[RenderState::SrcBlendFunc];
}

void RenderStates::SetSrcBlendFunc(BlendFunc::Enum nValue)
{
	m_nRS[RenderState::SrcBlendFunc] = nValue;
}

BlendFunc::Enum RenderStates::GetDstBlendFunc() const
{
	return (BlendFunc::Enum)m_nRS[RenderState::DstBlendFunc];
}

void RenderStates::SetDstBlendFunc(BlendFunc::Enum nValue)
{
	m_nRS[RenderState::DstBlendFunc] = nValue;
}

// Stencil
bool RenderStates::GetStencilEnable() const
{
	return m_nRS[RenderState::StencilEnable] != 0;
}

void RenderStates::SetStencilEnable(bool bValue)
{
	m_nRS[RenderState::StencilEnable] = bValue;
}

Compare::Enum RenderStates::GetStencilFunc() const
{
	return (Compare::Enum)m_nRS[RenderState::StencilFunc];
}

void RenderStates::SetStencilFunc(Compare::Enum nValue)
{
	m_nRS[RenderState::StencilFunc] = nValue;
}

uint32 RenderStates::GetStencilRef() const
{
	return m_nRS[RenderState::StencilRef];
}

void RenderStates::SetStencilRef(uint32 nValue)
{
	m_nRS[RenderState::StencilRef] = nValue;
}

uint32 RenderStates::GetStencilMask() const
{
	return m_nRS[RenderState::StencilMask];
}

void RenderStates::SetStencilMask(uint32 nValue)
{
	m_nRS[RenderState::StencilMask] = nValue;
}

StencilOp::Enum RenderStates::GetStencilFail() const
{
	return (StencilOp::Enum)m_nRS[RenderState::StencilFail];
}

void RenderStates::SetStencilFail(StencilOp::Enum nValue)
{
	m_nRS[RenderState::StencilFail] = nValue;
}

StencilOp::Enum RenderStates::GetStencilZFail() const
{
	return (StencilOp::Enum)m_nRS[RenderState::StencilZFail];
}

void RenderStates::SetStencilZFail(StencilOp::Enum nValue)
{
	m_nRS[RenderState::StencilZFail] = nValue;
}

StencilOp::Enum RenderStates::GetStencilPass() const
{
	return (StencilOp::Enum)m_nRS[RenderState::StencilPass];
}

void RenderStates::SetStencilPass(StencilOp::Enum nValue)
{
	m_nRS[RenderState::StencilPass] = nValue;
}

bool RenderStates::GetTwoSidedStencilMode() const
{
	return m_nRS[RenderState::TwoSidedStencilMode] != 0;
}

void RenderStates::SetTwoSidedStencilMode(bool bValue)
{
	m_nRS[RenderState::TwoSidedStencilMode] = bValue;
}

Compare::Enum RenderStates::GetCCWStencilFunc() const
{
	return (Compare::Enum)m_nRS[RenderState::CCWStencilFunc];
}

void RenderStates::SetCCWStencilFunc(Compare::Enum nValue)
{
	m_nRS[RenderState::CCWStencilFunc] = nValue;
}

StencilOp::Enum RenderStates::GetCCWStencilFail() const
{
	return (StencilOp::Enum)m_nRS[RenderState::CCWStencilFail];
}

void RenderStates::SetCCWStencilFail(StencilOp::Enum nValue)
{
	m_nRS[RenderState::CCWStencilFail] = nValue;
}

StencilOp::Enum RenderStates::GetCCWStencilZFail() const
{
	return (StencilOp::Enum)m_nRS[RenderState::CCWStencilZFail];
}

void RenderStates::SetCCWStencilZFail(StencilOp::Enum nValue)
{
	m_nRS[RenderState::CCWStencilZFail] = nValue;
}

StencilOp::Enum RenderStates::GetCCWStencilPass() const
{
	return (StencilOp::Enum)m_nRS[RenderState::CCWStencilPass];
}

void RenderStates::SetCCWStencilPass(StencilOp::Enum nValue)
{
	m_nRS[RenderState::CCWStencilPass] = nValue;
}

// Point and line
float RenderStates::GetPointSize() const
{
	return Tools::UInt32ToFloat(m_nRS[RenderState::PointSize]);
}

void RenderStates::SetPointSize(float fValue)
{
	m_nRS[RenderState::PointSize] = Tools::FloatToUInt32(fValue);
}

bool RenderStates::GetPointScaleEnable() const
{
	return m_nRS[RenderState::PointScaleEnable] != 0;
}

void RenderStates::SetPointScaleEnable(bool bValue)
{
	m_nRS[RenderState::PointScaleEnable] = bValue;
}

float RenderStates::GetPointSizeMin() const
{
	return Tools::UInt32ToFloat(m_nRS[RenderState::PointSizeMin]);
}

void RenderStates::SetPointSizeMin(float fValue)
{
	m_nRS[RenderState::PointSizeMin] = Tools::FloatToUInt32(fValue);
}

float RenderStates::GetPointSizeMax() const
{
	return Tools::UInt32ToFloat(m_nRS[RenderState::PointSizeMax]);
}

void RenderStates::SetPointSizeMax(float fValue)
{
	m_nRS[RenderState::PointSizeMax] = Tools::FloatToUInt32(fValue);
}

float RenderStates::GetPointScaleA() const
{
	return Tools::UInt32ToFloat(m_nRS[RenderState::PointScaleA]);
}

void RenderStates::SetPointScaleA(float fValue)
{
	m_nRS[RenderState::PointScaleA] = Tools::FloatToUInt32(fValue);
}

float RenderStates::GetPointScaleB() const
{
	return Tools::UInt32ToFloat(m_nRS[RenderState::PointScaleB]);
}

void RenderStates::SetPointScaleB(float fValue)
{
	m_nRS[RenderState::PointScaleB] = Tools::FloatToUInt32(fValue);
}

float RenderStates::GetPointScaleC() const
{
	return Tools::UInt32ToFloat(m_nRS[RenderState::PointScaleC]);
}

void RenderStates::SetPointScaleC(float fValue)
{
	m_nRS[RenderState::PointScaleC] = Tools::FloatToUInt32(fValue);
}

float RenderStates::GetLineWidth() const
{
	return Tools::UInt32ToFloat(m_nRS[RenderState::LineWidth]);
}

void RenderStates::SetLineWidth(float fValue)
{
	m_nRS[RenderState::LineWidth] = Tools::FloatToUInt32(fValue);
}

// Tessellation
uint32 RenderStates::GetTessellationFactor() const
{
	return m_nRS[RenderState::TessellationFactor];
}

void RenderStates::SetTessellationFactor(uint32 nValue)
{
	m_nRS[RenderState::TessellationFactor] = nValue;
}
/*
// [TODO] Linux GCC: "error: changes meaning of ‘TessellationMode’ from ‘class PLRenderer::TessellationMode"
TessellationMode::Enum RenderStates::GetTessellationMode() const
{
	return (TessellationMode::Enum)m_nRS[RenderState::TessellationMode];
}

void RenderStates::SetTessellationMode(TessellationMode::Enum nValue)
{
	m_nRS[RenderState::TessellationMode] = nValue;
}
*/
// Misc
bool RenderStates::GetPointSpriteEnable() const
{
	return m_nRS[RenderState::PointSpriteEnable] != 0;
}

void RenderStates::SetPointSpriteEnable(bool bValue)
{
	m_nRS[RenderState::PointSpriteEnable] = bValue;
}

bool RenderStates::GetDitherEnable() const
{
	return m_nRS[RenderState::DitherEnable] != 0;
}

void RenderStates::SetDitherEnable(bool bValue)
{
	m_nRS[RenderState::DitherEnable] = bValue;
}

bool RenderStates::GetScissorTestEnable() const
{
	return m_nRS[RenderState::ScissorTestEnable] != 0;
}

void RenderStates::SetScissorTestEnable(bool bValue)
{
	m_nRS[RenderState::ScissorTestEnable] = bValue;
}

bool RenderStates::GetMultisampleEnable() const
{
	return m_nRS[RenderState::MultisampleEnable] != 0;
}

void RenderStates::SetMultisampleEnable(bool bValue)
{
	m_nRS[RenderState::MultisampleEnable] = bValue;
}

bool RenderStates::GetInvCullMode() const
{
	return m_nRS[RenderState::InvCullMode] != 0;
}

void RenderStates::SetInvCullMode(bool bValue)
{
	m_nRS[RenderState::InvCullMode] = bValue;
}

Fill::Enum RenderStates::GetFixedFillMode() const
{
	return (Fill::Enum)m_nRS[RenderState::FixedFillMode];
}

void RenderStates::SetFixedFillMode(Fill::Enum nValue)
{
	m_nRS[RenderState::FixedFillMode] = nValue;
}


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

/**
*  @brief
*    Retrieves a render-state value
*/
uint32 RenderStates::Get(RenderState::Enum nState) const
{
	// Check whether the state is a valid render state member
	return (nState < RenderState::Number) ? m_nRS[nState] : 0;
}

/**
*  @brief
*    Sets a single render-state parameter
*/
bool RenderStates::Set(RenderState::Enum nState, uint32 nValue)
{
	// Check whether the state is a valid render state member
	if (nState >= RenderState::Number)
		return false; // Error!

	// Set render state value
	m_nRS[nState] = nValue;

	// Done
	return true;
}

/**
*  @brief
*    Copy operator
*/
RenderStates &RenderStates::operator =(const RenderStates &cSource)
{
	// Copy states
	for (uint32 i=0; i<RenderState::Number; i++)
		m_nRS[i] = cSource.m_nRS[i];

	// Return this
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
