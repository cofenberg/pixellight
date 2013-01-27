/*********************************************************\
 *  File: SPK_PLRenderer.inl                             *
  *      SPK_PLRenderer implementation
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

/**
*  @brief
*    Sets the inverse world view matrix used for rendering
*/
inline void SPK_PLRenderer::SetWorldViewInverse(const PLMath::Matrix4x4 &mWorldViewInverse)
{
	m_mWorldViewInverse = mWorldViewInverse;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


#endif	// __SPARK_PL_RENDERER_INL__
