/*********************************************************\
 *  File: HDRAverageLuminance.h                          *
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


#ifndef __PLCOMPOSITING_HDR_AVERAGELUMINANCE_H__
#define __PLCOMPOSITING_HDR_AVERAGELUMINANCE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Shader/ShaderManager.h>
#include "PLCompositing/PLCompositing.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGraphics {
	class Color3;
}
namespace PLRenderer {
	class TextureBuffer;
	class TextureBuffer2D;
	class SurfaceTextureBuffer;
	class TextureBufferRectangle;
}
namespace PLScene {
	class FullscreenQuad;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    HDR logarithmic average luminance calculation component
*
*  @note
*    - The technique described in http://developer.download.nvidia.com/SDK/9.5/Samples/DEMOS/Direct3D9/HDR_FP16x2.zip is used
*/
class HDRAverageLuminance {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*/
		PLCOM_API HDRAverageLuminance(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API ~HDRAverageLuminance();

		/**
		*  @brief
		*    Calculates the logarithmic average luminance
		*
		*  @param[in] cOriginalTexture
		*    Original HDR texture buffer to calculate the logarithmic average luminance from
		*  @param[in] cLuminanceConvert
		*    Luminance convert
		*
		*  @note
		*    - Use GetTextureBuffer() to receive the result of the calculation
		*/
		PLCOM_API void CalculateAverageLuminance(PLRenderer::TextureBufferRectangle &cOriginalTexture, const PLGraphics::Color3 &cLuminanceConvert);

		/**
		*  @brief
		*    Returns the 1x1 2D texture buffer storing the logarithmic average luminance
		*
		*  @return
		*    The 1x1 2D texture buffer storing the logarithmic average luminance, NULL on error
		*
		*  @note
		*    - The texture buffer is only valid after CalculateAverageLuminance() was called
		*/
		PLCOM_API PLRenderer::TextureBuffer *GetTextureBuffer() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Returns the downsample 2x2 log fragment shader
		*
		*  @return
		*    The fragment shader, NULL on error
		*/
		PLRenderer::Shader *GetDownsampleLogFragmentShader();

		/**
		*  @brief
		*    Returns the downsample 4x4 fragment shader
		*
		*  @return
		*    The fragment shader, NULL on error
		*/
		PLRenderer::Shader *GetDownsampleFragmentShader();

		/**
		*  @brief
		*    Returns the downsample 4x4 exp fragment shader
		*
		*  @return
		*    The fragment shader, NULL on error
		*/
		PLRenderer::Shader *GetDownsampleExpFragmentShader();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::Renderer			 *m_pRenderer;							/**< Renderer to use, always valid! */
		PLScene::FullscreenQuad			 *m_pFullscreenQuad;					/**< Fullscreen quad instance, can be NULL */
		// Downsample 2x2, calculate pixel luminance and log
		bool							  m_bDownsampleLogFragmentShader;		/**< Downsample 2x2 log fragment shader build? */
		PLRenderer::ShaderHandler		  m_cDownsampleLogFragmentShader;		/**< Downsample 2x2 log fragment shader mode */
		PLRenderer::SurfaceTextureBuffer *m_pDownsampleLogRenderTarget;			/**< Downsample 2x2 log render target, can be NULL */
		// Downsample 4x4
		bool							  m_bDownsampleFragmentShader;			/**< Downsample 4x4 fragment shader build? */
		PLRenderer::ShaderHandler		  m_cDownsampleFragmentShader;			/**< Downsample 4x4 fragment shader mode */
		PLRenderer::SurfaceTextureBuffer *m_pDownsampleRenderTarget;			/**< Downsample 4x4 render target, can be NULL */
		// Reduce <4>x<4> to <1>x<1> and calculate the exponent
		bool							  m_bDownsampleExpFragmentShader;		/**< Downsample 4x4 exp fragment shader build? */
		PLRenderer::ShaderHandler		  m_cDownsampleExpFragmentShader;		/**< Downsample 4x4 exp fragment shader mode */
		PLRenderer::SurfaceTextureBuffer *m_pAverageLuminanceTextureBuffer2D;	/**< 1x1 2D texture buffer storing the logarithmic average luminance */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_HDR_AVERAGELUMINANCE_H__
