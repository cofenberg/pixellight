/*********************************************************\
 *  File: SRPEndHDR.h                                    *
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


#ifndef __PLCOMPOSITING_HDR_END_H__
#define __PLCOMPOSITING_HDR_END_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color3.h>
#include <PLRenderer/Shader/ShaderManager.h>
#include <PLScene/Compositing/General/SRPEnd.h>
#include "PLCompositing/PLCompositing.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLScene {
	class FullscreenQuad;
}
namespace PLCompositing {
	class HDRBloom;
	class HDRLightAdaptation;
	class HDRAverageLuminance;
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
*    HDR render pipeline finishing scene renderer pass
*
*  @note
*    - This scene renderer pass should be at the very bottom of the HDR scene render pipeline,
*      but it's not required that it's at the very bottom of the whole scene render pipeline
*    - Shader based
*    - Using Reinhard tone mapping as descriped within http://www.cs.ucf.edu/~reinhard/cdrom/
*    - HDR logarithmic average luminance calculation
*    - HDR light adaptation
*    - HDR bloom effect
*    - Performs gamma correction (linear space -> sRGB space)
*/
class SRPEndHDR : public PLScene::SRPEnd {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene renderer pass flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			NoToneMapping               = 1<<1,	/**< Do not perform tone mapping */
			NoAutomaticAverageLuminance = 1<<2,	/**< Do not calculate the average luminance automatically (used for tone mapping) */
			NoLightAdaptation           = 1<<3,	/**< Do not perform light adaptation (used for tone mapping with automatically calculated average luminance) */
			NoBloom                     = 1<<4,	/**< Do not add bloom */
			NoGammaCorrection           = 1<<5,	/**< Do not perform gamma correction */
			WriteToOriginalSurface      = 1<<6,	/**< The result is drawn into the given original render surface (for example a render window) and there's no further need for an additional SRPEnd instance, if not set, the current render pipeline is continued */
			ShowBloomTexture            = 1<<7	/**< Show the bloom texture (for debugging) */
		};
		pl_enum(EFlags)
			pl_enum_base(PLScene::SRPEnd::EFlags)
			pl_enum_value(NoToneMapping,				"Do not perform tone mapping")
			pl_enum_value(NoAutomaticAverageLuminance,	"Do not calculate the average luminance automatically (used for tone mapping)")
			pl_enum_value(NoLightAdaptation,			"Do not perform light adaptation (used for tone mapping with automatically calculated average luminance)")
			pl_enum_value(NoBloom,						"Do not add bloom")
			pl_enum_value(NoGammaCorrection,			"Do not perform gamma correction")
			pl_enum_value(WriteToOriginalSurface,		"The result is drawn into the given original render surface (for example a render window) and there's no further need for an additional SRPEnd instance, if not set, the current render pipeline is continued")
			pl_enum_value(ShowBloomTexture,				"Show the bloom texture (for debugging)")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPEndHDR, "PLCompositing", PLScene::SRPEnd, "HDR render pipeline finishing scene renderer pass")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(LuminanceConvert,		PLGraphics::Color3,		PLGraphics::Color3(0.2125f, 0.7154f, 0.0721f),	ReadWrite,	DirectValue,	"Luminance convert (tone mapping)",																											"")
		pl_attribute(Key,					float,					0.72f,											ReadWrite,	DirectValue,	"Key value, midzone luminance (tone mapping)",																								"")
		pl_attribute(WhiteLevel,			float,					100.0f,											ReadWrite,	DirectValue,	"The smallest luminance that will be mapped to pure white, values above 'burn out' (tone mapping)",											"")
		pl_attribute(AverageLuminance,		float,					0.02f,											ReadWrite,	DirectValue,	"User set average luminance (tone mapping, only used if NoAutomaticAverageLuminance is set)",												"")
		pl_attribute(Tau,					float,					0.5f,											ReadWrite,	DirectValue,	"Light adaptation 'tau', lower value for longer light adaption time (tone mapping, only used if NoAutomaticAverageLuminance is not set)",	"")
		pl_attribute(BloomBrightThreshold,	float,					0.5f,											ReadWrite,	DirectValue,	"Bloom bright threshold, only color components >= this value bloom (only used if NoBloom is not set)",										"")
		pl_attribute(BloomFactor,			float,					1.0f,											ReadWrite,	DirectValue,	"Bloom factor (only used if NoBloom is not set)",																							"")
		pl_attribute(BloomBlurPasses,		PLGeneral::uint32,		4,												ReadWrite,	DirectValue,	"Number of bloom blur passes, should be a multiple of 2 (only used if NoBloom is not set)",													"")
		pl_attribute(BloomDownscale,		float,					8.0f,											ReadWrite,	DirectValue,	"Bloom downscale factor, should be a multiple of 2 (only used if NoBloom is not set)",														"Min='1'")
		pl_attribute(Gamma,					float,					2.2f,											ReadWrite,	DirectValue,	"Gamma correction value, higher values lighten the image, smaller values darken the image",													"")
		// Overwritten SceneRendererPass variables
		pl_attribute(Flags,					pl_flag_type(EFlags),	0,												ReadWrite,	GetSet,			"Flags",																																	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPEndHDR();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPEndHDR();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Returns the fragment shader
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] bToneMapping
		*    Perform tone mapping
		*  @param[in] bAutomaticAverageLuminance
		*    Automatic average luminance
		*  @param[in] bBloom
		*    Add bloom
		*  @param[in] bGammaCorrection
		*    Perform gamma correction
		*
		*  @return
		*    The fragment shader, NULL on error
		*/
		PLRenderer::Shader *GetFragmentShader(PLRenderer::Renderer &cRenderer, bool bToneMapping, bool bAutomaticAverageLuminance, bool bBloom, bool bGammaCorrection);

		/**
		*  @brief
		*    Destroys all currently used shaders
		*/
		void DestroyShaders();


	//[-------------------------------------------------------]
	//[ Protected virtual PLScene::SceneRendererPass functions ]
	//[-------------------------------------------------------]
	protected:
		virtual void Draw(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLScene::FullscreenQuad						*m_pFullscreenQuad;				/**< Fullscreen quad instance, can be NULL */
		HDRAverageLuminance							*m_pHDRAverageLuminance;		/**< HDR logarithmic average luminance calculation component, can be NULL */
		HDRLightAdaptation							*m_pHDRLightAdaptation;			/**< HDR light adaptation calculation component, can be NULL */
		HDRBloom									*m_pHDRBloom;					/**< HDR bloom calculation component, can be NULL */
		bool										 m_bFragmentShader[2][2][2][2];	/**< Fragment shader build? [ToneMapping][AutomaticAverageLuminance][Bloom][GammaCorrection] */
		PLRenderer::ShaderHandler					 m_cFragmentShader[2][2][2][2];	/**< Fragment shader mode [ToneMapping][AutomaticAverageLuminance][Bloom][GammaCorrection] */
		PLGeneral::List<PLRenderer::ShaderHandler*>  m_lstShaders;					/**< List of all used shaders */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_HDR_END_H__
