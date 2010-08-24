/*********************************************************\
 *  File: HDRBloom.h                                     *
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


#ifndef __PLCOMPOSITING_HDR_BLOOM_H__
#define __PLCOMPOSITING_HDR_BLOOM_H__
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
*    HDR bloom calculation component
*/
class HDRBloom {


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
		PLCOM_API HDRBloom(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API ~HDRBloom();

		/**
		*  @brief
		*    Calculates the bloom
		*
		*  @param[in] cOriginalTexture
		*    Original HDR texture buffer to calculate the bloom from
		*  @param[in] fBrightThreshold
		*    Bright threshold
		*  @param[in] bToneMapping
		*    Perform tone mapping
		*  @param[in] bAutomaticAverageLuminance
		*    Automatic average luminance
		*  @param[in] cLuminanceConvert
		*    Luminance convert
		*  @param[in] fKey
		*    Key
		*  @param[in] fWhiteLevel
		*    White level
		*  @param[in] fAverageLuminance
		*    Average luminance
		*  @param[in] pHDRAverageLuminanceTextureBuffer
		*    Average luminance texture buffer, can be NULL
		*  @param[in] nBloomBlurPasses
		*    Number of blur passes
		*  @param[in] fDownscale
		*    Downscale factor
		*
		*  @note
		*    - Use GetTextureBuffer() to receive the result of the calculation
		*/
		PLCOM_API void CalculateBloom(PLRenderer::TextureBufferRectangle &cOriginalTexture, float fBrightThreshold, bool bToneMapping, bool bAutomaticAverageLuminance, const PLGraphics::Color3 &cLuminanceConvert,
									   float fKey, float fWhiteLevel, float fAverageLuminance, PLRenderer::TextureBuffer *pHDRAverageLuminanceTextureBuffer, PLGeneral::uint32 nBloomBlurPasses, float fDownscale);

		/**
		*  @brief
		*    Returns the rectangle texture buffer storing the bloom
		*
		*  @return
		*    The rectangle texture buffer storing the bloom, NULL on error
		*
		*  @note
		*    - The texture buffer is only valid after CalculateBloom() was called
		*/
		PLCOM_API PLRenderer::TextureBuffer *GetTextureBuffer() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Returns the downsample fragment shader
		*
		*  @param[in] bToneMapping
		*    Perform tone mapping
		*  @param[in] bAutomaticAverageLuminance
		*    Automatic average luminance
		*
		*  @return
		*    The fragment shader, NULL on error
		*/
		PLRenderer::Shader *GetDownsampleFragmentShader(bool bToneMapping, bool bAutomaticAverageLuminance);

		/**
		*  @brief
		*    Returns the bloom fragment shader
		*
		*  @return
		*    The fragment shader, NULL on error
		*/
		PLRenderer::Shader *GetBloomFragmentShader();

		/**
		*  @brief
		*    Destroys all currently used shaders
		*/
		void DestroyShaders();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::Renderer						*m_pRenderer;						/**< Renderer to use, always valid! */
		PLScene::FullscreenQuad						*m_pFullscreenQuad;					/**< Fullscreen quad instance, can be NULL */
		bool										 m_bDownsampleFragmentShader[2][2];	/**< Downsample fragment shader build? [ToneMapping][bAutomaticAverageLuminance] */
		PLRenderer::ShaderHandler					 m_cDownsampleFragmentShader[2][2];	/**< Downsample fragment shader mode [ToneMapping][bAutomaticAverageLuminance] */
		PLGeneral::List<PLRenderer::ShaderHandler*>  m_lstShaders;						/**< List of all used shaders */
		PLRenderer::SurfaceTextureBuffer			*m_pRenderTarget[2];				/**< Render targets, can be NULL */
		bool										 m_bBloomFragmentShader;			/**< Bloom fragment shader build? */
		PLRenderer::ShaderHandler					 m_cBloomFragmentShader;			/**< Bloom fragment shader mode */
		bool										 m_bResultIndex;					/**< Index of the result texture buffer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_HDR_BLOOM_H__
