/*********************************************************\
 *  File: SRPDeferredGlow.h                              *
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


#ifndef __PLCOMPOSITING_DEFERRED_GLOW_H__
#define __PLCOMPOSITING_DEFERRED_GLOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Shader/ShaderManager.h>
#include "PLCompositing/Deferred/SRPDeferred.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class TextureBuffer;
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
*    Scene renderer pass for deferred rendering glow effect
*
*  @note
*    - The technique used is loosely basing on the technique described within \url{http://http.developer.nvidia.com/GPUGems/gpugems_ch21.html}
*    - The content of the emissive/light map render target of the GBuffer is used
*/
class SRPDeferredGlow : public SRPDeferred {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene renderer flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			NoDiscard  = 1<<1,	/**< Disable discard (may result in better or worse performance) */
			NoBlending = 1<<2	/**< Disable blending (for debugging) */
		};
		pl_enum(EFlags)
			pl_enum_base(SRPDeferred::EFlags)
			pl_enum_value(NoDiscard,	"Disable discard (may result in better or worse performance)")
			pl_enum_value(NoBlending,	"Disable blending (for debugging)")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDeferredGlow, "PLCompositing", PLCompositing::SRPDeferred, "Scene renderer pass for deferred rendering glow effect")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(GlowFactor,		float,					1.0f,	ReadWrite,	DirectValue,	"Glow factor",												"")
		pl_attribute(GlowBlurPasses,	PLGeneral::uint32,		4,		ReadWrite,	DirectValue,	"Number of glow blur passes, should be a multiple of 2",	"")
		pl_attribute(GlowDownscale,		float,					8.0f,	ReadWrite,	DirectValue,	"Glow downscale factor, should be a multiple of 2",			"Min='1.0'")
		// Overwritten SceneRendererPass variables
		pl_attribute(Flags,				pl_flag_type(EFlags),	0,		ReadWrite,	GetSet,			"Flags",													"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPDeferredGlow();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDeferredGlow();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Calculates the glow
		*
		*  @param[in] cFullscreenQuad
		*    Fullscreen quad instance instance to use
		*  @param[in] cOriginalTexture
		*    Original HDR texture buffer to calculate the glow from
		*  @param[in] fBrightThreshold
		*    Bright threshold
		*  @param[in] nBlurPasses
		*    Number of blur passes
		*  @param[in] fDownscale
		*    Downscale factor
		*
		*  @note
		*    - Use GetTextureBuffer() to receive the result of the calculation
		*/
		void CalculateGlow(PLScene::FullscreenQuad &cFullscreenQuad, PLRenderer::TextureBufferRectangle &cOriginalTexture, float fBrightThreshold, PLGeneral::uint32 nBlurPasses, float fDownscale);

		/**
		*  @brief
		*    Returns the rectangle texture buffer storing the glow
		*
		*  @return
		*    The rectangle texture buffer storing the glow, NULL on error
		*
		*  @note
		*    - The texture buffer is only valid after CalculateGlow() was called
		*/
		PLRenderer::TextureBuffer *GetTextureBuffer() const;

		/**
		*  @brief
		*    Returns the downsample fragment shader
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*
		*  @return
		*    The fragment shader, NULL on error
		*/
		PLRenderer::Shader *GetDownsampleFragmentShader(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Returns the glow fragment shader
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*
		*  @return
		*    The fragment shader, NULL on error
		*/
		PLRenderer::Shader *GetGlowFragmentShader(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Returns the result fragment shader
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] bDiscard
		*    Use discard
		*
		*  @return
		*    The fragment shader, NULL on error
		*/
		PLRenderer::Shader *GetResultFragmentShader(PLRenderer::Renderer &cRenderer, bool bDiscard);

		/**
		*  @brief
		*    Destroys all currently used shaders
		*/
		void DestroyShaders();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::SurfaceTextureBuffer *m_pRenderTarget[2];			/**< Render targets, can be NULL */
		bool							  m_bDownsampleFragmentShader;	/**< Downsample fragment shader build? */
		PLRenderer::ShaderHandler		  m_cDownsampleFragmentShader;	/**< Downsample fragment shader mode */
		bool							  m_bGlowFragmentShader;		/**< Glow fragment shader build? */
		PLRenderer::ShaderHandler		  m_cGlowFragmentShader;		/**< Glow fragment shader mode */
		bool							  m_bResultIndex;				/**< Index of the result texture buffer */
		bool							  m_bResultFragmentShader[2];	/**< Result fragment shader build? [Discard] */
		PLRenderer::ShaderHandler		  m_cResultFragmentShader[2];	/**< Result fragment shader mode [Discard] */


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneRendererPass functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void Draw(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_DEFERRED_GLOW_H__
