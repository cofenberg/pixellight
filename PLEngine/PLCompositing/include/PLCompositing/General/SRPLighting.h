/*********************************************************\
 *  File: SRPLighting.h                                  *
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


#ifndef __PLCOMPOSITING_GENERAL_LIGHTING_H__
#define __PLCOMPOSITING_GENERAL_LIGHTING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Texture/TextureHandler.h>
#include <PLRenderer/Renderer/ProgramGenerator.h>
#include <PLScene/Compositing/SceneRendererPass.h>
#include "PLCompositing/PLCompositing.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class VertexBuffer;
	class ProgramUniform;
	class ProgramAttribute;
}
namespace PLMesh {
	class Mesh;
	class MeshHandler;
	class MeshLODLevel;
}
namespace PLScene {
	class VisNode;
	class SNLight;
	class SceneNode;
	class ShadowMapManager;
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
*    Shaders based lighting scene renderer pass implementation
*
*  @remarks
*    This scene renderer pass can deal with the following material parameters:
*    - TwoSided:                   Backface culling active? If 1, both sides of polygons are visible, default: 0
*    - DiffuseColor:               Use this 3 floating point values to set the diffuse color, default: 1.0 1.0 1.0
*    - DiffuseMap:                 Diffuse map (2D, RGB, other usual name: 'decal map')
*      - AlphaReference:           Alpha reference 0.0-1.0, only used if the diffuse map has an alpha channel, if 0 no alpha test is performed at all
*    - DiffuseRampMap:             Can be used for 'cell shading' (1D, grayscale)
*    - IndexOfRefraction:          Index of refraction (IOR), used for Fresnel reflection, <= 0.0 means no Fresnel reflection, default: 0.0 (List of refractive indices: http://en.wikipedia.org/wiki/List_of_refractive_indices, the index of refaction of the "from" material is set to air=1.0)
*      - FresnelReflectionPower:   If 'IndexOfRefraction' is > 0.0, this is the Fresnel reflection power, default: 5.0
*    - ReflectionColor:            If 'IndexOfRefraction' is > 0.0 or if there's a 'ReflectionMap', use this 3 floating point values to set the reflection color, default: 1.0 1.0 1.0
*    - Reflectivity:               If 'IndexOfRefraction' is > 0.0 or if there's a 'ReflectionMap', reflectivity factor can be used, 0.0...1.0=no reflection...full reflection, default: 1.0
*    - ReflectivityMap:            Per fragment 'reflectivity' control (2D, grayscale)
*    - ReflectionMap:             'Reflections', not influenced by any light, 2D (spherical environment mapping) or cube map (cubic environment mapping), RGB
*    - NormalMap:                  Normal map (sometimes also called 'Dot3 bump map') required for 'per pixel lighting' (2D, RGB, tangent space)
*      - NormalMapBumpiness:       The 'bumpiness' of the normal map, normally values from 0-2, default: 1
*    - DetailNormalMap:            For more detailed 'per pixel lighting' (2D, RGB, tangent space)
*      - DetailNormalMapBumpiness: The 'bumpiness' of the detail normal map, normally values from 0-2, default: 1
*      - DetailNormalMapUVScale:   Texture coordinate scale factor for the detail normal map, default: 4.0 4.0
*    - HeightMap:                  Height map required for 'per pixel lighting' with "Parallax Mapping" or also called "Offset Normal Mapping" or "Virtual Displacement Mapping" (2D, grayscale, other usual name: 'bump map')
*      - Parallax:                 Controls the 'depth' of the material if parallax mapping is used, normally values from 0.01-0.04, default: 0.04. Parallax mapping can ONLY be used if a height map is given!
*    - SpecularColor:              Multiplied with the final specular term, normally values from 0-1, default: 1 for all components. If all 0, there's no specular lighting at all.
*      - SpecularExponent:         The 'power' of the specular lighting, normally values from 1-128, default: 45
*      - SpecularMap:              Specular control map (2D, RGB, if there's an alpha channel it's used for specular power control)
*      - SpecularRampMap:          Can be used for 'cell shading' (1D, grayscale)
*    - EdgeRampMap:                Can be used for cartoon silhouettes (1D, grayscale)
*
*    Example:
*  @verbatim
*    <?xml version="1.0"?>
*    <Material Version="1">
*        <Float Name="TwoSided">0.0</Float>
*        <Float3 Name="DiffuseColor">1.0 1.0 1.0</Float3>
*        <Texture Name="DiffuseMap">Data/Textures/My_DiffuseMap.dds</Texture>
*        <Texture Name="DiffuseRampMap">Data/Textures/My_DiffuseRampMap.dds</Texture>
*        <Float Name="AlphaReference">0.5</Float>
*        <Float Name="IndexOfRefraction">0.0</Float>
*        <Float Name="FresnelReflectionPower">5.0</Float>
*        <Float3 Name="ReflectionColor">1.0 1.0 1.0</Float3>
*        <Float Name="Reflectivity">1.0</Float>
*        <Texture Name="ReflectivityMap">Data/Textures/My_ReflectivityMap.dds</Texture>
*        <Texture Name="ReflectionMap">Data/Textures/My_ReflectionMap.dds</Texture>
*        <Texture Name="NormalMap">Data/Textures/My_NormalMap.dds</Texture>
*        <Float Name="NormalMapBumpiness">1.0</Float>
*        <Texture Name="DetailNormalMap">Data/Textures/My_DetailNormalMap.dds</Texture>
*        <Float Name="DetailNormalMapBumpiness">1.0</Float>
*        <Float2 Name="DetailNormalMapUVScale">4.0 4.0</Float2>
*        <Texture Name="HeightMap">Data/Textures/My_HeightMap.dds</Texture>
*        <Float Name="Parallax">0.04</Float>
*        <Float3 Name="SpecularColor">1.0 1.0 1.0</Float3>
*        <Float Name="SpecularExponent">45.0</Float>
*        <Texture Name="SpecularRampMap">Data/Textures/My_SpecularRampMap.dds</Texture>
*        <Texture Name="SpecularMap">Data/Textures/My_SpecularMap.dds</Texture>
*        <Texture Name="SpecularRampMap">Data/Textures/My_SpecularRampMap.dds</Texture>
*        <Texture Name="EdgeRampMap">Data/Textures/My_EdgeRampMap.dds</Texture>
*    </Material>
*  @endverbatim
*
*  @note
*    - Normal map compression using swizzled DXT5 (xGxR) is supported
*    - If there's an SRPDirectionalLighting instance, "SRPDirectionalLighting::GetUsedLight()" will be called to ask for
*      an already drawn directional light source (*the primary light source*)... if such a light exists, this scene renderer
*      pass automatically skipts the light rendering so that this light source is not rendered twice!
*/
class SRPLighting : public PLScene::SceneRendererPass {


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
			Bilinear      = 1,	/**< Bilinear */
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
		*    Scene renderer pass flags (PLScene::SceneRendererPass flags extension)
		*/
		enum EFlags {
			NoGammaCorrection       = 1<<1,		/**< Do not perform gamma correction (in general gamma correction done for: DiffuseMap, ReflectionMap) - if gamma correction is enabled, there should be a gamma correction at the end of the render pipeline */
			NoDiffuseMap            = 1<<2,		/**< Ignore diffuse map */
			NoFresnelReflection     = 1<<3,		/**< Ignore fresnel reflection */
			NoReflectivityMap       = 1<<4,		/**< Ignore reflectivity map */
			NoReflectionMap         = 1<<5,		/**< Ignore reflection map */
			NoNormalMap             = 1<<6,		/**< Ignore normal maps */
			NoDetailNormalMap       = 1<<7,		/**< Ignore detail normal maps */
			NoParallaxMapping       = 1<<8,		/**< No parallax mapping (also called 'Photonic Mapping', 'Offset Mapping' or 'Virtual Displacement Mapping') */
			NoSpecular              = 1<<9,		/**< No specular */
			NoSpecularMap           = 1<<10,	/**< Ignore specular maps */
			NoDiffuseRampMap        = 1<<11,	/**< Ignore diffuse ramp maps */
			NoSpecularRampMap       = 1<<12,	/**< Ignore specular ramp maps */
			NoEdgeRampMap           = 1<<13,	/**< Ignore edge ramp maps */
			NoShadow                = 1<<14,	/**< Do not render shadows */
			NoSoftShadow            = 1<<15,	/**< No soft shadows */
			NoProjectivePointLights = 1<<16,	/**< No projective point lights */
			NoProjectiveSpotLights  = 1<<17,	/**< No projective spot lights */
			NoDiscard               = 1<<18		/**< Disable discard (may result in better or worse performance) */
		};
		pl_enum(EFlags)
			pl_enum_base(PLScene::SceneRendererPass::EFlags)
			pl_enum_value(NoGammaCorrection,		"Do not perform gamma correction (in general gamma correction done for: DiffuseMap, ReflectionMap) - if gamma correction is enabled, there should be a gamma correction at the end of the render pipeline")
			pl_enum_value(NoDiffuseMap,				"Ignore diffuse map")
			pl_enum_value(NoFresnelReflection,		"Ignore fresnel reflection")
			pl_enum_value(NoReflectivityMap,		"Ignore reflectivity map")
			pl_enum_value(NoReflectionMap,			"Ignore reflection map")
			pl_enum_value(NoNormalMap,				"Ignore normal maps")
			pl_enum_value(NoDetailNormalMap,		"Inore detail normal maps")
			pl_enum_value(NoParallaxMapping,		"No parallax mapping (also called 'Photonic Mapping', 'Offset Mapping' or 'Virtual Displacement Mapping')")
			pl_enum_value(NoSpecular,				"No specular")
			pl_enum_value(NoSpecularMap,			"Ignore specular maps")
			pl_enum_value(NoDiffuseRampMap,			"Ignore diffuse ramp maps")
			pl_enum_value(NoSpecularRampMap,		"Ignore specular ramp maps")
			pl_enum_value(NoEdgeRampMap,			"Ignore edge ramp maps")
			pl_enum_value(NoShadow,					"Do not render shadows")
			pl_enum_value(NoSoftShadow,				"No soft shadows")
			pl_enum_value(NoProjectivePointLights,	"No projective point lights")
			pl_enum_value(NoProjectiveSpotLights,	"No projective spot lights")
			pl_enum_value(NoDiscard,				"Disable discard (may result in better or worse performance)")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPLighting, "PLCompositing", PLScene::SceneRendererPass, "Shaders based lighting scene renderer pass implementation")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(TextureFiltering,	pl_enum_type(ETextureFiltering),	Anisotropic8,	ReadWrite,	DirectValue,	"Texture filtering",																													"")
		pl_attribute(ShaderLanguage,	PLGeneral::String,					"",				ReadWrite,	DirectValue,	"Shader language to use (for example \"GLSL\" or \"Cg\"), if empty string, the default shader language of the renderer will be used",	"")
		pl_attribute(LightingIntensity,	float,								1.0f,			ReadWrite,	DirectValue,	"General lighting intensity",																											"")
		// Overwritten PLScene::SceneRendererPass variables
		pl_attribute(Flags,				pl_flag_type(EFlags),				0,				ReadWrite,	GetSet,			"Flags",																																"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCOM_API SRPLighting();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPLighting();


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Vertex shader flags, flag names become to source code definitions
		*/
		enum EVertexShaderFlags {
			VS_TEXCOORD0				= 1<<0,	/**< Use texture coordinate 0 */
			VS_NORMAL					= 1<<1,	/**< Use vertex normal */
				VS_TWOSIDEDLIGHTING		= 1<<2,	/**< Two sided lighting possible? (VS_NORMAL should be defined!) */
				VS_TANGENT_BINORMAL		= 1<<3,	/**< Use vertex tangent and binormal (VS_NORMAL should be defined!) */
					VS_PARALLAXMAPPING	= 1<<4	/**< Perform parallax mapping (VS_NORMAL and VS_TANGENT_BINORMAL should be defined!) */
		};

		/**
		*  @brief
		*    Fragment shader flags, flag names become to source code definitions
		*/
		enum EFragmentShaderFlags {
			FS_TEXCOORD0						= 1<<0,		/**< Use texture coordinate 0 */
			FS_NORMAL							= 1<<1,		/**< Use vertex normal */
				FS_TANGENT_BINORMAL				= 1<<2,		/**< Use vertex tangent and binormal (FS_NORMAL should be defined!) */
					FS_PARALLAXMAPPING			= 1<<3,		/**< Perform parallax mapping (FS_NORMAL and FS_TANGENT_BINORMAL should be defined!) */
			FS_GAMMACORRECTION					= 1<<4,		/**< Use gamma correction (sRGB to linear space) */
			FS_DIFFUSEMAP						= 1<<5,		/**< Take diffuse map into account */
				FS_ALPHATEST					= 1<<6,		/**< Use alpha test to discard fragments (FS_DIFFUSEMAP should be defined!) */
			FS_DIFFUSERAMPMAP					= 1<<7,		/**< Use diffuse ramp map */
			FS_REFLECTION						= 1<<8,		/**< Use reflection */
				FS_FRESNELREFLECTION			= 1<<9,		/**< Use fresnel reflection (FS_REFLECTION should be defined!) */
				FS_REFLECTIVITYMAP				= 1<<10,	/**< Use reflectivity map (FS_REFLECTION and FS_FRESNELREFLECTION or FS_2DREFLECTIONMAP or FS_CUBEREFLECTIONMAP should be defined!) */
				FS_2DREFLECTIONMAP				= 1<<11,	/**< Use 2D reflection mapping (FS_REFLECTION should be defined, can't be set together with FS_CUBEREFLECTIONMAP!) */
				FS_CUBEREFLECTIONMAP			= 1<<12,	/**< Use cube reflection mapping (FS_REFLECTION should be defined, can't be set together with FS_2DREFLECTIONMAP!) */
			FS_NORMALMAP						= 1<<13,	/**< Take normal map into account */
				FS_NORMALMAP_DXT5_XGXR			= 1<<14,	/**< Compressed normal map (FS_NORMALMAP should be defined!) */
				FS_DETAILNORMALMAP				= 1<<15,	/**< Take detail normal map into account (FS_NORMALMAP should be defined!) */
				FS_DETAILNORMALMAP_DXT5_XGXR	= 1<<16,	/**< Compressed detail normal map (FS_NORMALMAP & FS_DETAILNORMALMAP should be defined!) */
			FS_SPECULAR							= 1<<17,	/**< Use specular */
				FS_SPECULARMAP					= 1<<18,	/**< Take specular map into account (FS_SPECULAR should be set, too) */
				FS_SPECULARRAMPMAP				= 1<<19,	/**< Take specular ramp map into account (FS_LIGHTING and FS_SPECULAR should be set, too) */
			FS_EDGERAMPMAP						= 1<<20,	/**< Use edge ramp map */
			FS_DIRECTIONAL						= 1<<21,	/**< Directional light */
			FS_PROJECTIVE_POINT					= 1<<22,	/**< Projective point light */
			FS_SPOT								= 1<<23,	/**< Spot light */
				FS_SPOT_PROJECTIVE				= 1<<24,	/**< Projective spot light (FS_SPOT should be set, too) */
				FS_SPOT_CONE					= 1<<25,	/**< Spot light with a cone (FS_SPOT should be set, too) */
					FS_SPOT_SMOOTHCONE			= 1<<26,	/**< Spot light with a smooth cone (FS_SPOT & FS_SPOT_CONE should be set, too) */
			FS_SHADOWMAPPING					= 1<<27,	/**< Perform shadow mapping */
				FS_SOFTSHADOWMAPPING			= 1<<28,	/**< Perform soft shadow mapping (FS_SHADOWMAPPING should be set, too) */
			FS_DISCARD							= 1<<29		/**< Use discard */
		};

		/**
		*  @brief
		*    Direct pointers to uniforms & attributes of a generated program
		*/
		struct GeneratedProgramUserData {
			// Vertex shader attributes
			PLRenderer::ProgramAttribute *pVertexPosition;
			PLRenderer::ProgramAttribute *pVertexTexCoord0;
			PLRenderer::ProgramAttribute *pVertexNormal;
			PLRenderer::ProgramAttribute *pVertexTangent;
			PLRenderer::ProgramAttribute *pVertexBinormal;
			// Vertex shader uniforms
			PLRenderer::ProgramUniform *pNormalScale;
			PLRenderer::ProgramUniform *pObjectSpaceToViewSpaceMatrix;
			PLRenderer::ProgramUniform *pObjectSpaceToClipSpaceMatrix;
			PLRenderer::ProgramUniform *pEyePos;
			// Fragment shader uniforms
			PLRenderer::ProgramUniform *pDiffuseColor;
			PLRenderer::ProgramUniform *pDiffuseMap;
			PLRenderer::ProgramUniform *pAlphaReference;
			PLRenderer::ProgramUniform *pDiffuseRampMap;
			PLRenderer::ProgramUniform *pReflectionColor;
			PLRenderer::ProgramUniform *pReflectivity;
			PLRenderer::ProgramUniform *pReflectivityMap;
			PLRenderer::ProgramUniform *pFresnelConstants;
			PLRenderer::ProgramUniform *pReflectionMap;
			PLRenderer::ProgramUniform *pViewSpaceToWorldSpace;
			PLRenderer::ProgramUniform *pNormalMap;
			PLRenderer::ProgramUniform *pNormalMapBumpiness;
			PLRenderer::ProgramUniform *pDetailNormalMap;
			PLRenderer::ProgramUniform *pDetailNormalMapBumpiness;
			PLRenderer::ProgramUniform *pDetailNormalMapUVScale;
			PLRenderer::ProgramUniform *pHeightMap;
			PLRenderer::ProgramUniform *pParallaxScaleBias;
			PLRenderer::ProgramUniform *pLightDirection;
			PLRenderer::ProgramUniform *pLightPosition;
			PLRenderer::ProgramUniform *pLightRadius;
			PLRenderer::ProgramUniform *pProjectivePointCubeMap;
			PLRenderer::ProgramUniform *pViewSpaceToCubeMapSpace;
			PLRenderer::ProgramUniform *pProjectiveSpotMap;
			PLRenderer::ProgramUniform *pViewSpaceToSpotMapSpace;
			PLRenderer::ProgramUniform *pSpotConeCos;
			PLRenderer::ProgramUniform *pShadowMap;
			PLRenderer::ProgramUniform *pViewSpaceToShadowMapSpace;
			PLRenderer::ProgramUniform *pViewSpaceToShadowCubeMapSpace;
			PLRenderer::ProgramUniform *pInvLightRadius;
			PLRenderer::ProgramUniform *pTexelSize;
			PLRenderer::ProgramUniform *pLightColor;
			PLRenderer::ProgramUniform *pSpecularColor;
			PLRenderer::ProgramUniform *pSpecularExponent;
			PLRenderer::ProgramUniform *pSpecularMap;
			PLRenderer::ProgramUniform *pSpecularRampMap;
			PLRenderer::ProgramUniform *pEdgeRampMap;
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::ProgramGenerator		*m_pProgramGenerator;	/**< Program generator, can be NULL */
		PLRenderer::ProgramGenerator::Flags	 m_cProgramFlags;		/**< Program flags as class member to reduce dynamic memory allocations */
		PLScene::SNLight					*m_pIgnoredLight;		/**< Do not render this light, it may have already been rendered by for instance "PLCompositing::SRPDirectionalLighting", can be NULL */
		PLRenderer::TextureHandler			 m_cSpotMapHandler;		/**< Texture handler for the default spot map */
		PLRenderer::TextureHandler			 m_cCubeMapHandler;		/**< Texture handler for the default cube map */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Sets the initial render states
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*/
		void SetInitialRenderStates(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Sets correct texture filtering modes
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] nStage
		*    Texture stage
		*/
		void SetupTextureFiltering(PLRenderer::Renderer &cRenderer, PLGeneral::uint32 nStage) const;

		/**
		*  @brief
		*    Draws recursive
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cCullQuery
		*    Cull query to use
		*/
		void DrawRec(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery);

		/**
		*  @brief
		*    Renders a light
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cCullQuery
		*    Cull query to use
		*  @param[in] cLight
		*    Used light node
		*  @param[in] cLightVisNode
		*    The light visibility node
		*/
		void RenderLight(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery, PLScene::SNLight &cLight, const PLScene::VisNode &cLightVisNode);

		/**
		*  @brief
		*    Renders a light recursive
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cCullQuery
		*    Cull query to use
		*  @param[in] cLight
		*    Used light node
		*  @param[in] cLightVisNode
		*    The light visibility node
		*  @param[in] pShadowMapManager
		*    Shadow map manager to use, can be NULL
		*/
		void RenderLightRec(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery, PLScene::SNLight &cLight, const PLScene::VisNode &cLightVisNode, PLScene::ShadowMapManager *pShadowMapManager);

		/**
		*  @brief
		*    Draws a mesh
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cCullQuery
		*    Cull query to use
		*  @param[in] cVisNode
		*    Visibility node to use
		*  @param[in] cSceneNode
		*    Mesh owner scene node
		*  @param[in] cMeshHandler
		*    Mesh handler to use
		*  @param[in] cMesh
		*    Mesh to draw
		*  @param[in] cMeshLODLevel
		*    LOD level of the mesh to draw
		*  @param[in] cVertexBuffer
		*    Vertex buffer to use
		*  @param[in] cLight
		*    Used light node
		*  @param[in] cLightVisNode
		*    The light visibility node
		*  @param[in] pShadowMapManager
		*    Shadow map manager to use, can be NULL
		*/
		void DrawMesh(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery, const PLScene::VisNode &cVisNode, PLScene::SceneNode &cSceneNode, const PLMesh::MeshHandler &cMeshHandler,
					  const PLMesh::Mesh &cMesh, const PLMesh::MeshLODLevel &cMeshLODLevel, PLRenderer::VertexBuffer &cVertexBuffer, PLScene::SNLight &cLight, const PLScene::VisNode &cLightVisNode, PLScene::ShadowMapManager *pShadowMapManager);


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


#endif // __PLCOMPOSITING_GENERAL_LIGHTING_H__
