/*********************************************************\
 *  File: SRPDeferredDOF.h                               *
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


#ifndef __PLCOMPOSITING_DEFERRED_DOF_H__
#define __PLCOMPOSITING_DEFERRED_DOF_H__
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
*    Scene renderer pass for deferred rendering DOF effect
*
*  @note
*    - The technique described within \url{http://ati.amd.com/developer/gdc/Scheuermann_DepthOfField.pdf} is used
*/
class SRPDeferredDOF : public SRPDeferred {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene renderer pass flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			IgnoreCameraSettings = 1<<1,	/**< Don't use SNMPostProcessDepthOfField settings of the camera scene node */
			ShowDepthBlur        = 1<<2,	/**< Show depth blur (for debugging) */
			ShowBlur             = 1<<3		/**< Show blur (for debugging) */
		};
		pl_enum(EFlags)
			pl_enum_base(SRPDeferred::EFlags)
			pl_enum_value(IgnoreCameraSettings,	"Don't use SNMPostProcessDepthOfField settings of the camera scene node")
			pl_enum_value(ShowDepthBlur,		"Show depth blur (for debugging)")
			pl_enum_value(ShowBlur,				"Show blur (for debugging)")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDeferredDOF, "PLCompositing", PLCompositing::SRPDeferred, "Scene renderer pass for deferred rendering DOF effect")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(EffectWeight,		float,					1.0f,	ReadWrite,	DirectValue,	"Effect weight, 0 means that this effect has no influence, 1 for the intended influence",					"Min=0 Max=1")
		pl_attribute(NearPlaneDepth,	float,					0.5f,	ReadWrite,	DirectValue,	"Everything closer than this is fully blurred (only used if IgnoreCameraSettings is set)",					"")
		pl_attribute(FocalPlaneDepth,	float,					5.0f,	ReadWrite,	DirectValue,	"Points on this plane are in focus (only used if IgnoreCameraSettings is set)",								"")
		pl_attribute(FarPlaneDepth,		float,					10.0f,	ReadWrite,	DirectValue,	"Everything beyond the far plane is fully blurred (only used if IgnoreCameraSettings is set)",				"")
		pl_attribute(BlurrinessCutoff,	float,					0.8f,	ReadWrite,	DirectValue,	"Blurriness cutoff constant for objects behind the focal plane (only used if IgnoreCameraSettings is set)",	"")
		pl_attribute(BlurPasses,		PLGeneral::uint32,		2,		ReadWrite,	DirectValue,	"Number of blur passes, should be a multiple of 2",															"")
		pl_attribute(BlurDownscale,		float,					4.0f,	ReadWrite,	DirectValue,	"Blur downscale factor, should be a multiple of 2",															"Min='1.0'")
		// Overwritten SceneRendererPass variables
		pl_attribute(Flags,				pl_flag_type(EFlags),	0,		ReadWrite,	GetSet,			"Flags",																									"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPDeferredDOF();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDeferredDOF();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Calculates the depth blur
		*
		*  @param[in] cFullscreenQuad
		*    Fullscreen quad instance instance to use
		*  @param[in] cRGBTexture
		*    Texture buffer containing RGB
		*  @param[in] cNormalDepthTexture
		*    Normal depth texture buffer
		*  @param[in] fNearPlaneDepth
		*    Near plane depth
		*  @param[in] fFocalPlaneDepth
		*    Focal plane depth
		*  @param[in] fFarPlaneDepth
		*    Far plane depth
		*  @param[in] fBlurrinessCutoff
		*    Blurriness cutoff
		*/
		void CalculateDepthBlur(PLScene::FullscreenQuad &cFullscreenQuad, PLRenderer::TextureBufferRectangle &cRGBTexture, PLRenderer::TextureBufferRectangle &cNormalDepthTexture,
								float fNearPlaneDepth, float fFocalPlaneDepth, float fFarPlaneDepth, float fBlurrinessCutoff);

		/**
		*  @brief
		*    Calculates the blur
		*
		*  @param[in] cFullscreenQuad
		*    Fullscreen quad instance instance to use
		*  @param[in] cOriginalTexture
		*    Original HDR texture buffer to calculate the blur from
		*  @param[in] fBrightThreshold
		*    Bright threshold
		*  @param[in] nBlurPasses
		*    Number of blur passes
		*  @param[in] fDownscale
		*    Downscale factor
		*
		*  @note
		*    - Use GetBlurTextureBuffer() to receive the result of the calculation
		*/
		void CalculateBlur(PLScene::FullscreenQuad &cFullscreenQuad, PLRenderer::TextureBufferRectangle &cOriginalTexture, float fBrightThreshold, PLGeneral::uint32 nBlurPasses, float fDownscale);

		/**
		*  @brief
		*    Shows data
		*
		*  @param[in] cFullscreenQuad
		*    Fullscreen quad instance instance to use
		*  @param[in] cTexture
		*    Texture buffer containing the data
		*  @param[in] nType
		*    0 for depth blur, 1 for blur
		*/
		void Show(PLScene::FullscreenQuad &cFullscreenQuad, PLRenderer::TextureBufferRectangle &cTexture, PLGeneral::uint32 nType);

		/**
		*  @brief
		*    Returns the rectangle texture buffer storing the blur
		*
		*  @return
		*    The rectangle texture buffer storing the blur, NULL on error
		*
		*  @note
		*    - The texture buffer is only valid after CalculateBlur() was called
		*/
		PLRenderer::TextureBuffer *GetBlurTextureBuffer() const;

		/**
		*  @brief
		*    Returns the depth blur fragment shader
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*
		*  @return
		*    The fragment shader, NULL on error
		*/
		PLRenderer::Shader *GetDepthBlurFragmentShader(PLRenderer::Renderer &cRenderer);

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
		*    Returns the blur fragment shader
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*
		*  @return
		*    The fragment shader, NULL on error
		*/
		PLRenderer::Shader *GetBlurFragmentShader(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Returns the result fragment shader
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*
		*  @return
		*    The fragment shader, NULL on error
		*/
		PLRenderer::Shader *GetResultFragmentShader(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Returns the show fragment shader
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] nType
		*    0 for depth blur, 1 for blur
		*
		*  @return
		*    The fragment shader, NULL on error
		*/
		PLRenderer::Shader *GetShowFragmentShader(PLRenderer::Renderer &cRenderer, PLGeneral::uint32 nType);

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
		bool							  m_bDepthBlurFragmentShader;	/**< Depth blur fragment shader build? */
		PLRenderer::ShaderHandler		  m_cDepthBlurFragmentShader;	/**< Depth blur fragment shader mode */
		bool							  m_bDownsampleFragmentShader;	/**< Downsample fragment shader build? */
		PLRenderer::ShaderHandler		  m_cDownsampleFragmentShader;	/**< Downsample fragment shader mode */
		bool							  m_bBlurFragmentShader;		/**< Blur fragment shader build? */
		PLRenderer::ShaderHandler		  m_cBlurFragmentShader;		/**< Blur fragment shader mode */
		bool							  m_bResultIndex;				/**< Index of the result texture buffer */
		bool							  m_bResultFragmentShader;		/**< Result fragment shader build? */
		PLRenderer::ShaderHandler		  m_cResultFragmentShader;		/**< Result fragment shader mode */
		bool							  m_bShowFragmentShader[2];		/**< Show fragment shader build? [Type] */
		PLRenderer::ShaderHandler		  m_cShowFragmentShader[2];		/**< Show fragment shader mode [Type] */


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


#endif // __PLCOMPOSITING_DEFERRED_DOF_H__
