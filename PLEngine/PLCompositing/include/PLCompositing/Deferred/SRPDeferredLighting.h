/*********************************************************\
 *  File: SRPDeferredLighting.h                          *
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


#ifndef __PLCOMPOSITING_DEFERRED_LIGHTING_H__
#define __PLCOMPOSITING_DEFERRED_LIGHTING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Shader/ShaderManager.h>
#include <PLRenderer/Texture/TextureHandler.h>
#include "PLCompositing/Deferred/SRPDeferred.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLScene {
	class SNLight;
	class VisNode;
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
*    Scene renderer pass for deferred rendering lighting
*
*  @note
*    - SceneNode::ReceiveShadow is not supported
*/
class SRPDeferredLighting : public SRPDeferred {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Texture filtering modes
		*/
		enum ETextureFiltering {
			NoFiltering   = 0,	/**< No filtering */
			Bilinear      = 1,	/**< Bilinear filtering */
			Anisotropic2  = 2,	/**< Anisotropic x2 */
			Anisotropic4  = 4,	/**< Anisotropic x4 */
			Anisotropic8  = 8,	/**< Anisotropic x8 */
			Anisotropic16 = 16	/**< Anisotropic x16 */
		};
		pl_enum(ETextureFiltering)
			pl_enum_value(NoFiltering,		"No filtering")
			pl_enum_value(Bilinear,			"Bilinear")
			pl_enum_value(Anisotropic2,		"Anisotropic x2")
			pl_enum_value(Anisotropic4,		"Anisotropic x4")
			pl_enum_value(Anisotropic8,		"Anisotropic x8")
			pl_enum_value(Anisotropic16,	"Anisotropic x16")
		pl_enum_end

		/**
		*  @brief
		*    Scene renderer pass flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			NoShadow                = 1<<1,		/**< Do not render shadows */
			NoSoftShadow            = 1<<2,		/**< No soft shadows */
			NoShadowLOD             = 1<<3,		/**< Do not use level of detail for shadow maps, with LOD on, shadows far away will have a lower resolution */
			NoAlbedo                = 1<<4,		/**< Ignore albedo data */
			NoAmbientOcclusion      = 1<<5,		/**< Ignore ambient occlusion data */
			NoSpecular              = 1<<6,		/**< No specular */
			NoSpecularColor         = 1<<7,		/**< Ignore specular color data */
			NoSpecularExponent      = 1<<8,		/**< Ignore specular exponent data */
			NoProjectivePointLights = 1<<9,		/**< No projective point lights */
			NoProjectiveSpotLights  = 1<<10,	/**< No projective spot lights */
			NoDiscard               = 1<<11,	/**< Disable discard (may result in better or worse performance) */
			NoGammaCorrection       = 1<<12		/**< Do not perform gamma correction (for projective lights) - if gamma correction is enabled, there should be a gamma correction at the end of the render pipeline */
		};
		pl_enum(EFlags)
			pl_enum_base(SRPDeferred::EFlags)
			pl_enum_value(NoShadow,					"Do not render shadows")
			pl_enum_value(NoSoftShadow,				"No soft shadows")
			pl_enum_value(NoShadowLOD,				"Do not use level of detail for shadow maps, with LOD on, shadows far away will have a lower resolution")
			pl_enum_value(NoAlbedo,					"Ignore albedo data")
			pl_enum_value(NoAmbientOcclusion,		"Ignore ambient occlusion data")
			pl_enum_value(NoSpecular,				"No specular")
			pl_enum_value(NoSpecularColor,			"Ignore specular color data")
			pl_enum_value(NoSpecularExponent,		"Ignore specular exponent data")
			pl_enum_value(NoProjectivePointLights,	"No projective point lights")
			pl_enum_value(NoProjectiveSpotLights,	"No projective spot lights")
			pl_enum_value(NoDiscard,				"Disable discard (may result in better or worse performance)")
			pl_enum_value(NoGammaCorrection,		"Do not perform gamma correction (for projective lights) - if gamma correction is enabled, there should be a gamma correction at the end of the render pipeline")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDeferredLighting, "PLCompositing", PLCompositing::SRPDeferred, "Scene renderer pass for deferred rendering lighting")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(TextureFiltering,	pl_enum_type(ETextureFiltering),	Anisotropic8,					ReadWrite,	DirectValue,	"Texture filtering, used for projective lights",	"")
		// Overwritten SceneRendererPass variables
		pl_attribute(Flags,				pl_flag_type(EFlags),				NoShadowLOD|NoAmbientOcclusion,	ReadWrite,	GetSet,			"Flags",											"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLCOM_API virtual void SetFlags(PLGeneral::uint32 nValue);	// From SceneRendererPass


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPDeferredLighting();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDeferredLighting();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Sets correct texture filtering modes
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] nStage
		*    Texture stage
		*  @param[in] nTextureFiltering
		*    Texture filtering mode to use
		*/
		void SetupTextureFiltering(PLRenderer::Renderer &cRenderer, PLGeneral::uint32 nStage, PLGeneral::uint32 nTextureFiltering) const;

		/**
		*  @brief
		*    Returns the vertex shader
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*
		*  @return
		*    The vertex shader with the requested features, NULL on error
		*/
		PLRenderer::Shader *GetVertexShader(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Returns the fragment shader for the requested visualisation mode
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] bDirectional
		*    Directional light
		*  @param[in] bProjectivePoint
		*    Projective point light
		*  @param[in] bSpot
		*    Spot light
		*  @param[in] bProjectiveSpot
		*    Projective spot light
		*  @param[in] bSpotCone
		*    Spot light with cone
		*  @param[in] bSpotSmoothCone
		*    Spot light with a smooth cone
		*  @param[in] bShadowMapping
		*    Shadow mapping
		*  @param[in] bDiscard
		*    Use discard
		*  @param[in] bGammaCorrection
		*    Use gamma correction
		*
		*  @return
		*    The fragment shader for the requested visualisation mode, NULL on error
		*/
		PLRenderer::Shader *GetFragmentShader(PLRenderer::Renderer &cRenderer, bool bDirectional, bool bProjectivePoint, bool bSpot, bool bProjectiveSpot, bool bSpotCone, bool bSpotSmoothCone, bool bShadowMapping, bool bDiscard, bool bGammaCorrection);

		/**
		*  @brief
		*    Destroys all currently used shaders
		*/
		void DestroyShaders();

		/**
		*  @brief
		*    Draws recursive
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cCullQuery
		*    Cull query to use
		*  @param[in] cSRPDeferredGBuffer
		*    "SRPDeferredGBuffer" scene renderer pass to use
		*/
		void DrawRec(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery, SRPDeferredGBuffer &cSRPDeferredGBuffer);

		/**
		*  @brief
		*    Renders a light
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cCullQuery
		*    Cull query to use
		*  @param[in] cSRPDeferredGBuffer
		*    "SRPDeferredGBuffer" scene renderer pass to use
		*  @param[in] cLight
		*    Used light node
		*  @param[in] cLightVisNode
		*    The light visibility node
		*/
		void RenderLight(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery, SRPDeferredGBuffer &cSRPDeferredGBuffer, PLScene::SNLight &cLight, const PLScene::VisNode &cLightVisNode);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool										m_bVertexShader;								/**< Generic vertex shader already build? */
		PLRenderer::ShaderHandler					m_cVertexShader;								/**< Generic vertex shader */
		bool										m_bFragmentShader[2][2][2][2][2][2][2][2][2];	/**< Fragment shader build? [Directional][ProjectivePoint][Spot][ProjectiveSpot][SpotCone][SpotSmoothCone][ShadowMapping][Discard][GammaCorrection] */
		PLRenderer::ShaderHandler					m_cFragmentShader[2][2][2][2][2][2][2][2][2];	/**< Fragment shader mode [Directional][ProjectivePoint][Spot][ProjectiveSpot][SpotCone][SpotSmoothCone][ShadowMapping][Discard][GammaCorrection] */
		PLGeneral::List<PLRenderer::ShaderHandler*> m_lstShaders;									/**< List of all used shaders */
		PLRenderer::TextureHandler					m_cSpotMapHandler;								/**< Texture handler for the default spot map */
		PLRenderer::TextureHandler					m_cCubeMapHandler;								/**< Texture handler for the default cube map */


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


#endif // __PLCOMPOSITING_DEFERRED_LIGHTING_H__
