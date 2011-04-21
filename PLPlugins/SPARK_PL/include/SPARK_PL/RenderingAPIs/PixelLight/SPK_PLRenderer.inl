/*********************************************************\
 *  File: SPK_PLRenderer.inl                             *
  *      SPK_PLRenderer implementation
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


#ifndef __SPARK_PL_RENDERER_INL__
#define __SPARK_PL_RENDERER_INL__
#pragma once


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the used PixelLight renderer
*/
inline PLRenderer::Renderer &SPK_PLRenderer::GetPLRenderer() const
{
	return *m_pRenderer;
}

/**
*  @brief
*    Tells whether blending is enabled for this SPK_PLRenderer
*/
inline bool SPK_PLRenderer::IsBlendingEnabled() const
{
	return m_bBlendingEnabled;
}

/**
*  @brief
*    Enables or disables the blending of this SPK_PLRenderer
*/
inline void SPK_PLRenderer::EnableBlending(bool bBlendingEnabled)
{
	m_bBlendingEnabled = bBlendingEnabled;
}

/**
*  @brief
*    Gets the source blending function of this SPK_PLRenderer
*/
inline PLRenderer::BlendFunc::Enum SPK_PLRenderer::GetSrcBlendingFunction() const
{
	return m_nSrcBlending;
}

/**
*  @brief
*    Gets the destination blending function of this SPK_PLRenderer
*/
inline PLRenderer::BlendFunc::Enum SPK_PLRenderer::GetDestBlendingFunction() const
{
	return m_nDestBlending;
}

/**
*  @brief
*    Sets the blending functions of this SPK_PLRenderer
*/
inline void SPK_PLRenderer::SetBlendingFunctions(PLRenderer::BlendFunc::Enum nSrcBlending, PLRenderer::BlendFunc::Enum nDestBlending)
{
	m_nSrcBlending  = nSrcBlending;
	m_nDestBlending = nDestBlending;
}

/**
*  @brief
*    Sets the world view projection matrix used for rendering
*/
inline void SPK_PLRenderer::SetWorldViewProjectionMatrix(const PLMath::Matrix4x4 &mWorldViewProjection)
{
	m_mWorldViewProjection = mWorldViewProjection;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


#endif	// __SPARK_PL_RENDERER_INL__
