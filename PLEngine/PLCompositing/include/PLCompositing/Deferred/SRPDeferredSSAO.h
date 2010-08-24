/*********************************************************\
 *  File: SRPDeferredSSAO.h                              *
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


#ifndef __PLCOMPOSITING_DEFERRED_SSAO_H__
#define __PLCOMPOSITING_DEFERRED_SSAO_H__
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
*    Abstract scene renderer pass for deferred rendering "Screen-Space Ambient Occlusion" (SSAO)
*
*  @note
*    - Overwrites the static ambient occlusion value from GBuffer RT0
*    - Using "Cross Bilateral Filter" as described within NVIDIA Direct3D SDK 10 Code Samples
*      (http://developer.download.nvidia.com/SDK/10.5/direct3d/Source/ScreenSpaceAO/doc/ScreenSpaceAO.pdf)
*/
class SRPDeferredSSAO : public SRPDeferred {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene renderer pass flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			NoBlur = 1<<1	/**< Do not blur the calculated ambient occlusion */
		};
		pl_enum(EFlags)
			pl_enum_base(SRPDeferred::EFlags)
			pl_enum_value(NoBlur, "Do not blur the calculated ambient occlusion")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDeferredSSAO, "PLCompositing", PLCompositing::SRPDeferred, "Abstract scene renderer pass for deferred rendering \"Screen-Space Ambient Occlusion\" (SSAO)")
		pl_attribute(Contrast,			float,					1.25f,	ReadWrite,	DirectValue,	"This value allows to scales up the ambient occlusion values",																																																				"Min='0.0'")
		pl_attribute(BlurRadius,		float,					2.0f,	ReadWrite,	DirectValue,	"Blur kernel radius in pixel",																																																												"Min='0.0'")
		pl_attribute(BlurSharpness,		float,					16.0f,	ReadWrite,	DirectValue,	"Controls the depth-dependent weight of the bilateral filter, to avoid bleeding across edges. A zero sharpness is a pure Gaussian blur. Increasing the blur sharpness removes bleeding by using lower weights for samples with large depth delta from the current pixel.",	"Min='0.0'")
		pl_attribute(ResolutionScale,	float,					0.5f,	ReadWrite,	DirectValue,	"If less 1, the ambient occlusion is computed with a lower resolution and then stretched up to the full resolution. This can be used to trade visual quality for better performance.",																						"Min='0.0' Max='1.0'")
		pl_attribute(SceneScale,		float,					1.0f,	ReadWrite,	DirectValue,	"Scene scale ",																																																																"Min='0.0'")
		// Overwritten SceneRendererPass variables
		pl_attribute(Flags,				pl_flag_type(EFlags),	0,		ReadWrite,	GetSet,			"Flags",																																																																	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPDeferredSSAO();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDeferredSSAO();


	//[-------------------------------------------------------]
	//[ Protected virtual SRPDeferredSSAO functions           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Draws the AO
		*
		*  @param[in] cFullscreenQuad
		*    Fullscreen quad to use
		*  @param[in] cNormalDepthTextureBuffer
		*    RG components of RT1 store the normal vector, B component of RT1 stores the linear view space depth
		*/
		virtual void DrawAO(PLScene::FullscreenQuad &cFullscreenQuad, PLRenderer::TextureBufferRectangle &cNormalDepthTextureBuffer) = 0;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Returns the blur vertex shader
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*
		*  @return
		*    The blur vertex shader with the requested features, NULL on error
		*/
		PLRenderer::Shader *GetBlurVertexShader(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Returns the blur fragment shader
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] bXBlur
		*    X blur, else it's y blur
		*
		*  @return
		*    The blur fragment shader with the requested features, NULL on error
		*/
		PLRenderer::Shader *GetBlurFragmentShader(PLRenderer::Renderer &cRenderer, bool bXBlur);

		/**
		*  @brief
		*    Destroys all currently used shaders
		*/
		void DestroyShaders();

		/**
		*  @brief
		*    Draws the blur
		*
		*  @param[in] cInputTextureBuffer
		*    Input texture buffer to apply to blur to
		*  @param[in] cNormalDepthTextureBuffer
		*    RG components of RT1 store the normal vector, B component of RT1 stores the linear view space depth
		*  @param[in] bXBlur
		*    X blur, else it's y blur
		*/
		void DrawBlur(PLRenderer::TextureBufferRectangle &cInputTextureBuffer, PLRenderer::TextureBufferRectangle &cNormalDepthTextureBuffer, bool bXBlur);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::SurfaceTextureBuffer			*m_pRenderTargetAO;			/**< Render target catching the result of AO, can be NULL */
		PLRenderer::SurfaceTextureBuffer			*m_pRenderTargetXBlur;		/**< Render target catching the result of x blur, can be NULL */
		bool										 m_bBlurVertexShader;		/**< Generic blur vertex shader already build? */
		PLRenderer::ShaderHandler					 m_cBlurVertexShader;		/**< Generic blur vertex shader */
		bool										 m_bBlurFragmentShader[2];	/**< Fragment blur shader build? [XBlur] */
		PLRenderer::ShaderHandler					 m_cBlurFragmentShader[2];	/**< Fragment blur shader mode [XBlur] */
		PLGeneral::List<PLRenderer::ShaderHandler*>  m_lstShaders;				/**< List of all used shaders */


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


#endif // __PLCOMPOSITING_DEFERRED_SSAO_H__
