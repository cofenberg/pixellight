/*********************************************************\
 *  File: SRPMotionBlurShaders.h                         *
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


#ifndef __PLCOMPOSITING_GENERAL_MOTIONBLUR_H__
#define __PLCOMPOSITING_GENERAL_MOTIONBLUR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Matrix4x4.h>
#include <PLRenderer/Renderer/ProgramGenerator.h>
#include <PLScene/Compositing/SceneRendererPass.h>
#include "PLCompositing/PLCompositing.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class ProgramUniform;
	class ProgramAttribute;
}
namespace PLCompositing {
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
*    Shaders based scene renderer pass for image based motion blur
*
*  @note
*    - Implementation from "GPU Gems 3 - Chapter 27. Motion Blur as a Post-Processing Effect" (http://http.developer.nvidia.com/GPUGems3/gpugems3_ch27.html)
*      with additional improvements from http://www.john-chapman.net/content.php?id=11
*/
class SRPMotionBlurShaders : public PLScene::SceneRendererPass {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene renderer pass flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			NoTargetFPS      = 1<<1,	/**< Do not use the target FPS for adaptive motion blur factor */
			ShowVelocity     = 1<<2,	/**< Show velocity (for debugging) */
			ShowOnlyVelocity = 1<<3		/**< Show only velocity, everything else black (for debugging) */
		};
		pl_enum(EFlags)
			pl_enum_base(PLScene::SceneRendererPass::EFlags)
			pl_enum_value(NoTargetFPS,		"Do not use the target FPS for adaptive motion blur factor")
			pl_enum_value(ShowVelocity	,	"Show velocity (for debugging)")
			pl_enum_value(ShowOnlyVelocity,	"Show only velocity, everything else black (for debugging)")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPMotionBlurShaders, "PLCompositing", PLScene::SceneRendererPass, "Shaders based scene renderer pass for image based motion blur")
		// Attributes
		pl_attribute(ShaderLanguage,	PLCore::String,			"",		ReadWrite,	DirectValue,	"Shader language to use (for example \"GLSL\" or \"Cg\"), if empty string, the default shader language of the renderer will be used",	"")
		pl_attribute(NumberOfSamples,	PLCore::uint32,			20,		ReadWrite,	DirectValue,	"Number of samples, higher is better but costs more performance",																		"")
		pl_attribute(MotionBlurFactor,	float,					1.0f,	ReadWrite,	DirectValue,	"Motion blur factor (normally between 0..1)",																							"")
		pl_attribute(TargetFPS,			float,					60.0f,	ReadWrite,	DirectValue,	"Target FPS for adaptive motion blur factor (not physically realistic, just a compensation for a variable FPS)",						"")
			// Overwritten PLScene::SceneRendererPass attributes
		pl_attribute(Flags,				pl_flag_type(EFlags),	0,		ReadWrite,	GetSet,			"Flags",																																"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPMotionBlurShaders();

		/**
		*  @brief
		*    Destructor
		*/
		PLCOM_API virtual ~SRPMotionBlurShaders();


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Fragment shader flags, flag names become to source code definitions
		*/
		enum EFragmentShaderFlags {
			FS_SHOW_VELOCITY      = 1<<0,	/**< Show velocity (for debugging) */
			FS_SHOW_ONLY_VELOCITY = 1<<1	/**< Show only velocity, everything else black (for debugging) */
		};

		/**
		*  @brief
		*    Direct pointers to uniforms & attributes of a generated program
		*/
		struct GeneratedProgramUserData {
			// Vertex shader attributes
			PLRenderer::ProgramAttribute *pVertexPosition;
			// Fragment shader uniforms
			PLRenderer::ProgramUniform *pTextureSize;
			PLRenderer::ProgramUniform *pColorTexture;
			PLRenderer::ProgramUniform *pDepthTexture;
			PLRenderer::ProgramUniform *pClipSpaceToWorldSpace;
			PLRenderer::ProgramUniform *pPreviousWorldSpaceToClipSpace;
			PLRenderer::ProgramUniform *pNumberOfSamples;
			PLRenderer::ProgramUniform *pVelocityFactor;
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		FullscreenQuad						*m_pFullscreenQuad;					/**< Fullscreen quad instance, can be a null pointer */
		PLRenderer::ProgramGenerator		*m_pProgramGenerator;				/**< Program generator, can be a null pointer */
		PLRenderer::ProgramGenerator::Flags	 m_cProgramFlags;					/**< Program flags as class member to reduce dynamic memory allocations */
		PLMath::Matrix4x4					 m_mPreviousWorldSpaceToClipSpace;	/**< Previous world space to clip space transform matrix */


	//[-------------------------------------------------------]
	//[ Protected virtual PLScene::SceneRendererPass functions ]
	//[-------------------------------------------------------]
	protected:
		virtual void Draw(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_GENERAL_MOTIONBLUR_H__
