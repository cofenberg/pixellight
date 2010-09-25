/*********************************************************\
 *  File: SRPDeferredGBuffer.h                           *
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


#ifndef __PLCOMPOSITING_DEFERRED_GBUFFER_H__
#define __PLCOMPOSITING_DEFERRED_GBUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/Pool.h>
#include <PLMath/Rectangle.h>
#include <PLRenderer/Renderer/ProgramGenerator.h>
#include "PLCompositing/Deferred/SRPDeferred.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Surface;
	class Material;
	class IndexBuffer;
	class VertexBuffer;
	class ProgramUniform;
	class ProgramAttribute;
	class SurfaceTextureBuffer;
	class TextureBufferRectangle;
}
namespace PLMesh {
	class Mesh;
	class Geometry;
	class MeshHandler;
	class MeshLODLevel;
}
namespace PLScene {
	class SQCull;
	class VisNode;
	class SceneNode;
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
*    Scene renderer pass for deferred rendering GBuffer (Geometry Buffer) fill
*
*  @remarks
*    This scene renderer pass can deal with the following material parameters:
*    - TwoSided:                   Backface culling active? If 1, both sides of polygons are visible, default: 0
*    - DiffuseColor:               Use this 3 floating point values to set the diffuse color, default: 1.0 1.0 1.0
*    - DiffuseMap:                 Diffuse map (2D, RGB, other usual name: 'decal map')
*      - AlphaReference:           Alpha reference 0.0-1.0, only used if the diffuse map has an alpha channel, if 0 no alpha test is performed at all
*    - SpecularColor:              Multiplied with the final specular term, normally values from 0-1, default: 1 for all components. If all 0, there's no specular lighting at all.
*      - SpecularExponent:         The 'power' of the specular lighting, normally values from 1-128, default: 45
*      - SpecularMap:              Specular control map (2D, RGB, if there's an alpha channel it's used for specular power control)
*    - NormalMap:                  Normal map (sometimes also called 'Dot3 bump map') required for 'per pixel lighting' (2D, RGB, tangent space)
*      - NormalMapBumpiness:       The 'bumpiness' of the normal map, normally values from 0-2, default: 1
*    - DetailNormalMap:            For more detailed 'per pixel lighting' (2D, RGB, tangent space)
*      - DetailNormalMapBumpiness: The 'bumpiness' of the detail normal map, normally values from 0-2, default: 1
*      - DetailNormalMapUVScale:   Texture coordinate scale factor for the detail normal map, default: 4.0 4.0
*    - HeightMap:                  Height map required for 'per pixel lighting' with "Parallax Mapping" or also called "Offset Normal Mapping" or "Virtual Displacement Mapping" (2D, grayscale, other usual name: 'bump map')
*      - Parallax:                 Controls the 'depth' of the material if parallax mapping is used, normally values from 0.01-0.04, default: 0.04. Parallax mapping can ONLY be used if a height map is given!
*    - DisplacementMap:            Displacement map (2D, grayscale)
*      - DisplacementScale:        Displacement scale, default: 0.1
*      - DisplacementBias:         Displacement bias, default: 0.0
*    - AmbientOcclusionMap:        'Static global ambient occlusion', not influenced by any light but influcences the lighting (2D, grayscale)
*      - AmbientOcclusionFactor:   If there's a 'AmbientOcclusionMap', use this floating point value to set the ambient occlusion factor, default: 1.0
*    - LightMap:                   'Static lighting/shadowing', not influenced by any light (2D, RGB)
*      - LightMapColor:            If there's a 'LightMap', use this 3 floating point values to set the light map color, default: 1.0 1.0 1.0
*    - EmissiveMap:                'Emissive lighting', not influenced by any lighting (2D, RGB, other usual name: 'self illumination map'), emissive materials will not automatically glow, for glow you need to set 'Glow', too
*      - EmissiveMapColor:         If there's a 'EmissiveMap', use this 3 floating point values to set the emissive map color, default: 1.0 1.0 1.0
*      - Glow:                     Glow factor, values 0.0...1.0=no glow...full glow, default: 0.0 - glowing materials also need a EmissiveMap
*        - GlowMap:                If 'Glow' is not 0, per fragment 'glow' control (2D, grayscale)
*    - IndexOfRefraction:          Index of refraction (IOR), used for Fresnel reflection, <= 0.0 means no Fresnel reflection, default: 0.0 (List of refractive indices: http://en.wikipedia.org/wiki/List_of_refractive_indices, the index of refaction of the "from" material is set to air=1.0)
*      - FresnelReflectionPower:   If 'IndexOfRefraction' is > 0.0, this is the Fresnel reflection power, default: 5.0
*    - ReflectionColor:            If 'IndexOfRefraction' is > 0.0 or if there's a 'ReflectionMap', use this 3 floating point values to set the reflection color, default: 1.0 1.0 1.0
*    - Reflectivity:               If 'IndexOfRefraction' is > 0.0 or if there's a 'ReflectionMap', reflectivity factor can be used, 0.0...1.0=no reflection...full reflection, default: 1.0
*    - ReflectivityMap:            Per fragment 'reflectivity' control (2D, grayscale)
*    - ReflectionMap:             'Reflections', not influenced by any light, 2D (spherical environment mapping) or cube map (cubic environment mapping), RGB
*
*    Example:
*  @verbatim
*    <?xml version="1.0"?>
*    <Material Version="1">
*        <Float Name="TwoSided">0.0</Float>
*        <Float3 Name="DiffuseColor">1.0 1.0 1.0</Float3>
*        <Texture Name="DiffuseMap">Data/Textures/My_DiffuseMap.dds</Texture>
*        <Float Name="AlphaReference">0.5</Float>
*        <Float3 Name="SpecularColor">1.0 1.0 1.0</Float3>
*        <Float Name="SpecularExponent">45.0</Float>
*        <Texture Name="SpecularMap">Data/Textures/My_SpecularMap.dds</Texture>
*        <Texture Name="NormalMap">Data/Textures/My_NormalMap.dds</Texture>
*        <Float Name="NormalMapBumpiness">1.0</Float>
*        <Texture Name="DetailNormalMap">Data/Textures/My_DetailNormalMap.dds</Texture>
*        <Float Name="DetailNormalMapBumpiness">1.0</Float>
*        <Float2 Name="DetailNormalMapUVScale">4.0 4.0</Float2>
*        <Texture Name="HeightMap">Data/Textures/My_HeightMap.dds</Texture>
*        <Float Name="Parallax">0.04</Float>
*        <Texture Name="DisplacementMap">Data/Textures/My_DisplacementMap.dds</Texture>
*        <Float Name="DisplacementScale">0.1</Float>
*        <Float Name="DisplacementBias">0.0</Float>
*        <Texture Name="AmbientOcclusionMap">Data/Textures/My_AmbientOcclusionMap.dds</Texture>
*        <Float Name="AmbientOcclusionFactor">1.0</Float>
*        <Texture Name="LightMap">Data/Textures/My_LightMap.dds</Texture>
*        <Float3 Name="LightMapColor">1.0 1.0 1.0</Float3>
*        <Texture Name="EmissiveMap">Data/Textures/My_EmissiveMap.dds</Texture>
*        <Float3 Name="EmissiveMapColor">1.0 1.0 1.0</Float3>
*        <Float Name="Glow">0.0</Float>
*        <Texture Name="GlowMap">Data/Textures/My_GlowMap.dds</Texture>
*        <Float Name="IndexOfRefraction">0.0</Float>
*        <Float Name="FresnelReflectionPower">5.0</Float>
*        <Float3 Name="ReflectionColor">1.0 1.0 1.0</Float3>
*        <Float Name="Reflectivity">1.0</Float>
*        <Texture Name="ReflectivityMap">Data/Textures/My_ReflectivityMap.dds</Texture>
*        <Texture Name="ReflectionMap">Data/Textures/My_ReflectionMap.dds</Texture>
*    </Material>
*  @endverbatim
*
*  @note
*    - Geometry/attributes stage
*    - Another known name "fat frame buffer"
*    - Normal map compression using swizzled DXT5 (xGxR), LATC2 and alternate XY swizzle LATC2 is supported
*    - By default, this scene renderer pass writes into the stencil buffer whether or not a pixel has valid content.
*      1 within the stencil buffer means: The GBuffer has no information about the pixel because no geometry is covering it.
*/
class SRPDeferredGBuffer : public SRPDeferred {


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
		*    Scene renderer pass flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			Float32               = 1<<1,	/**< Use 32 bit floating point render targets instead of 16 bit ones */
			NoDiffuseMap          = 1<<2,	/**< Ignore diffuse map */
			NoSpecular            = 1<<3,	/**< No specular */
			NoSpecularMap         = 1<<4,	/**< Ignore specular maps */
			NoNormalMap           = 1<<5,	/**< Ignore normal maps */
			NoDetailNormalMap     = 1<<6,	/**< Ignore detail normal maps */
			NoParallaxMapping     = 1<<7,	/**< No parallax mapping (also called 'Photonic Mapping', 'Offset Mapping' or 'Virtual Displacement Mapping') */
			NoDisplacementMapping = 1<<8,	/**< No displacement mapping */
			NoAmbientOcclusionMap = 1<<9,	/**< Ignore ambient occlusion maps */
			NoLightMap            = 1<<10,	/**< Ignore light maps */
			NoEmissiveMap         = 1<<11,	/**< Ignore emissive maps */
			NoGlow                = 1<<12,	/**< No glow */
			NoGlowMap             = 1<<13,	/**< Ignore glow maps */
			NoFresnelReflection   = 1<<14,	/**< Ignore fresnel reflection */
			NoReflectivityMap     = 1<<15,	/**< Ignore reflectivity map */
			NoReflectionMap       = 1<<16,	/**< Ignore reflection map */
			NoStencil             = 1<<17,	/**< Ignore stencil buffer */
			NoGammaCorrection     = 1<<18	/**< Do not perform gamma correction (in general gamma correction done for: DiffuseMap, LightMap, EmissiveMap, ReflectionMap) - if gamma correction is enabled, there should be a gamma correction at the end of the render pipeline */
		};
		pl_enum(EFlags)
			pl_enum_base(SRPDeferred::EFlags)
			pl_enum_value(Float32,					"Use 32 bit floating point render targets instead of 16 bit ones")
			pl_enum_value(NoDiffuseMap,				"Ignore diffuse map")
			pl_enum_value(NoSpecular,				"No specular")
			pl_enum_value(NoSpecularMap,			"Ignore specular maps")
			pl_enum_value(NoNormalMap,				"Ignore normal maps")
			pl_enum_value(NoDetailNormalMap,		"Inore detail normal maps")
			pl_enum_value(NoParallaxMapping,		"No parallax mapping (also called 'Photonic Mapping', 'Offset Mapping' or 'Virtual Displacement Mapping')")
			pl_enum_value(NoDisplacementMapping,	"No displacement mapping")
			pl_enum_value(NoAmbientOcclusionMap,	"Ignore ambient occlusion maps")
			pl_enum_value(NoLightMap,				"Ignore light maps")
			pl_enum_value(NoEmissiveMap,			"Ignore emissive maps")
			pl_enum_value(NoGlow,					"No glow")
			pl_enum_value(NoGlowMap,				"Ignore glow maps")
			pl_enum_value(NoFresnelReflection,		"Ignore fresnel reflection")
			pl_enum_value(NoReflectivityMap,		"Ignore reflectivity map")
			pl_enum_value(NoReflectionMap,			"Ignore reflection map")
			pl_enum_value(NoStencil,				"Ignore stencil buffer")
			pl_enum_value(NoGammaCorrection,		"Do not perform gamma correction (in general gamma correction done for: DiffuseMap, LightMap, EmissiveMap, ReflectionMap) - if gamma correction is enabled, there should be a gamma correction at the end of the render pipeline")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDeferredGBuffer, "PLCompositing", PLCompositing::SRPDeferred, "Scene renderer pass for deferred rendering GBuffer (Geometry Buffer) fill")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(ShaderLanguage,	PLGeneral::String,					"",				ReadWrite,	DirectValue,	"Shader language to use (for example \"GLSL\" or \"Cg\"), if empty string, the default shader language of the renderer will be used",	"")
		pl_attribute(TextureFiltering,	pl_enum_type(ETextureFiltering),	Anisotropic8,	ReadWrite,	DirectValue,	"Texture filtering",																													"")
		// Overwritten SceneRendererPass variables
		pl_attribute(Flags,				pl_flag_type(EFlags),				0,				ReadWrite,	GetSet,			"Flags",																																"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPDeferredGBuffer();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDeferredGBuffer();

		/**
		*  @brief
		*    Returns a render target texture buffer of the GBuffer
		*
		*  @param[in] nIndex
		*    Index of the render target texture to return
		*
		*  @return
		*    A render target texture buffer of the GBuffer, can be NULL
		*/
		PLCOM_API PLRenderer::TextureBufferRectangle *GetRenderTargetTextureBuffer(PLGeneral::uint32 nIndex) const;

		// [TODO] Remove this!
		PLCOM_API PLRenderer::SurfaceTextureBuffer *GetRenderTarget() const;

		/**
		*  @brief
		*    Returns whether or not color target 3 has real information
		*
		*  @return
		*    'true' if color target 3 has real information, else 'false'
		*
		*  @note
		*    - Color target 3 stores emissive map, light map. If nothing using such information was drawn,
		*      the content is black and you may skip some further calculations.
		*/
		PLCOM_API bool IsColorTarget3Used() const;

		/**
		*  @brief
		*    Returns whether or not the alpha channel target 3 has real information
		*
		*  @return
		*    'true' if the alpha channel target 3 has real information, else 'false'
		*
		*  @note
		*    - The alpha channel target 3 stores glow information. If nothing using such information was drawn,
		*      the content is black and you may skip some further calculations.
		*/
		PLCOM_API bool IsColorTarget3AlphaUsed() const;

		/**
		*  @brief
		*    Returns a shared fullscreen quad instance
		*
		*  @return
		*    Fullscreen quad instance, NULL on error
		*/
		PLCOM_API PLScene::FullscreenQuad *GetFullscreenQuad() const;


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Vertex shader flags, flag names become to source code definitions
		*/
		enum EVertexShaderFlags {
			VS_TWOSIDED					= 1<<0,	/**< Two sided material */
			VS_DISPLACEMENTMAP			= 1<<1,	/**< Displacement map */
			VS_SECONDTEXTURECOORDINATE	= 1<<2,	/**< Second texture coordinate */
			VS_TANGENT_BINORMAL			= 1<<3,	/**< Tangent and binormal vectors */
			VS_VIEWSPACEPOSITION		= 1<<4	/**< Calculate viewspace position */
		};

		/**
		*  @brief
		*    Fragment shader flags, flag names become to source code definitions
		*/
		enum EFragmentShaderFlags {
			FS_DIFFUSEMAP							= 1<<0,		/**< Take diffuse map into account */
				FS_ALPHATEST						= 1<<1,		/**< Use alpha test to discard fragments (FS_DIFFUSEMAP must be defined!) */
			FS_SPECULAR								= 1<<2,		/**< Use specular */
				FS_SPECULARMAP						= 1<<3,		/**< Take specular map into account (FS_SPECULAR must be set, too) */
			FS_NORMALMAP							= 1<<4,		/**< Take normal map into account */
				FS_NORMALMAP_DXT5_XGXR				= 1<<5,		/**< DXT5 XGXR compressed normal map (FS_NORMALMAP must be defined and FS_NORMALMAP_LATC2 not!) */
				FS_NORMALMAP_LATC2					= 1<<6,		/**< LATC2 compressed normal map (FS_NORMALMAP must be defined and FS_NORMALMAP_DXT5_XGXR not!) */
				FS_DETAILNORMALMAP					= 1<<7,		/**< Take detail normal map into account (FS_NORMALMAP must be defined!) */
					FS_DETAILNORMALMAP_DXT5_XGXR	= 1<<8,		/**< DXT5 XGXR compressed detail normal map (FS_NORMALMAP & FS_DETAILNORMALMAP must be defined and FS_DETAILNORMALMAP_LATC2 not!) */
					FS_DETAILNORMALMAP_LATC2		= 1<<9,		/**< LATC2 compressed detail normal map (FS_NORMALMAP & FS_DETAILNORMALMAP must be defined and FS_DETAILNORMALMAP_DXT5_XGXR not!) */
			FS_PARALLAXMAPPING						= 1<<10,	/**< Perform parallax mapping */
			FS_AMBIENTOCCLUSIONMAP					= 1<<11,	/**< Use ambient occlusion map */
			FS_LIGHTMAP								= 1<<12,	/**< Use light map */
			FS_EMISSIVEMAP							= 1<<13,	/**< Use emissive map */
			FS_GLOW									= 1<<14,	/**< Use glow */
				FS_GLOWMAP							= 1<<15,	/**< Use glow map (FS_GLOW must be defined!) */
			FS_REFLECTION							= 1<<16,	/**< Use reflection */
				FS_FRESNELREFLECTION				= 1<<17,	/**< Use fresnel reflection (FS_REFLECTION must be defined!) */
				FS_REFLECTIVITYMAP					= 1<<18,	/**< Use reflectivity map (FS_REFLECTION and FS_FRESNELREFLECTION or FS_2DREFLECTIONMAP or FS_CUBEREFLECTIONMAP must be defined!) */
				FS_2DREFLECTIONMAP					= 1<<19,	/**< Use 2D reflection mapping (FS_REFLECTION must be defined, can't be set together with FS_CUBEREFLECTIONMAP!) */
				FS_CUBEREFLECTIONMAP				= 1<<20,	/**< Use cube reflection mapping (FS_REFLECTION must be defined, can't be set together with FS_2DREFLECTIONMAP!) */
			FS_GAMMACORRECTION						= 1<<21		/**< Use gamma correction (sRGB to linear space) */
		};

		/**
		*  @brief
		*    Direct pointers to uniforms & attributes of a generated program
		*/
		struct GeneratedProgramUserData {
			// Vertex shader attributes
			PLRenderer::ProgramAttribute *pVertexPosition;
			PLRenderer::ProgramAttribute *pVertexTexCoord0;
			PLRenderer::ProgramAttribute *pVertexTexCoord1;
			PLRenderer::ProgramAttribute *pVertexNormal;
			PLRenderer::ProgramAttribute *pVertexTangent;
			PLRenderer::ProgramAttribute *pVertexBinormal;
			// Vertex shader uniforms
			PLRenderer::ProgramUniform *pNormalScale;
			PLRenderer::ProgramUniform *pEyePos;
			PLRenderer::ProgramUniform *pWorldVP;
			PLRenderer::ProgramUniform *pWorldV;
			PLRenderer::ProgramUniform *pDisplacementMap;
			PLRenderer::ProgramUniform *pDisplacementScaleBias;
			// Fragment shader uniforms
			PLRenderer::ProgramUniform *pDiffuseColor;
			PLRenderer::ProgramUniform *pDiffuseMap;
			PLRenderer::ProgramUniform *pAlphaReference;
			PLRenderer::ProgramUniform *pSpecularColor;
			PLRenderer::ProgramUniform *pSpecularExponent;
			PLRenderer::ProgramUniform *pSpecularMap;
			PLRenderer::ProgramUniform *pNormalMap;
			PLRenderer::ProgramUniform *pNormalMapBumpiness;
			PLRenderer::ProgramUniform *pDetailNormalMap;
			PLRenderer::ProgramUniform *pDetailNormalMapBumpiness;
			PLRenderer::ProgramUniform *pDetailNormalMapUVScale;
			PLRenderer::ProgramUniform *pHeightMap;
			PLRenderer::ProgramUniform *pParallaxScaleBias;
			PLRenderer::ProgramUniform *pAmbientOcclusionMap;
			PLRenderer::ProgramUniform *pAmbientOcclusionFactor;
			PLRenderer::ProgramUniform *pLightMap;
			PLRenderer::ProgramUniform *pLightMapColor;
			PLRenderer::ProgramUniform *pEmissiveMap;
			PLRenderer::ProgramUniform *pEmissiveMapColor;
			PLRenderer::ProgramUniform *pGlowFactor;
			PLRenderer::ProgramUniform *pGlowMap;
			PLRenderer::ProgramUniform *pReflectionColor;
			PLRenderer::ProgramUniform *pReflectivity;
			PLRenderer::ProgramUniform *pReflectivityMap;
			PLRenderer::ProgramUniform *pFresnelConstants;
			PLRenderer::ProgramUniform *pReflectionMap;
			PLRenderer::ProgramUniform *pViewSpaceToWorldSpace;
		};

		/**
		*  @brief
		*    Mesh batch
		*/
		struct MeshBatch {
			const PLRenderer::Material		*pMaterial;			/**< Used material, always valid! */
				  PLRenderer::VertexBuffer	*pVertexBuffer;		/**< Used vertex buffer, always valid! */
				  PLRenderer::IndexBuffer	*pIndexBuffer;		/**< Used index buffer, always valid! */
			const PLMesh::Geometry			*pGeometry;			/**< Used geometry, always valid! */
			const PLScene::SQCull			*pCullQuery;		/**< Used cull query, always valid! */
			const PLScene::VisNode			*pVisNode;			/**< Used visibility node, always valid! */
				  PLMath::Rectangle			 sScissorRectangle;	/**< Scissor rectangle */
		};


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Collect mesh batches recursive
		*
		*  @param[in] cCullQuery
		*    Cull query to use
		*/
		void CollectMeshBatchesRec(const PLScene::SQCull &cCullQuery);

		/**
		*  @brief
		*    Makes a material to the currently used one
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cMaterial
		*    Material to use
		*
		*  @return
		*    Generated program user data
		*/
		GeneratedProgramUserData *MakeMaterialCurrent(PLRenderer::Renderer &cRenderer, const PLRenderer::Material &cMaterial);

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
		*    Draws a mesh batch
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cGeneratedProgramUserData
		*    Generated program user data for the mesh batch material
		*  @param[in] cMeshBatch
		*    Mesh batch to use
		*/
		void DrawMeshBatch(PLRenderer::Renderer &cRenderer, GeneratedProgramUserData &cGeneratedProgramUserData, MeshBatch &cMeshBatch) const;

		/**
		*  @brief
		*    Returns a free mesh batch
		*
		*  @return
		*    Free mesh batch
		*
		*  @note
		*    - Use FreeMeshBatch() if you no longer need this mesh batch
		*/
		MeshBatch &GetFreeMeshBatch();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::SurfaceTextureBuffer			 *m_pRenderTarget;			/**< Render target of the GBuffer, can be NULL */
		PLRenderer::TextureBufferRectangle			 *m_pColorTarget1;			/**< Color target 1, can be NULL */
		PLRenderer::TextureBufferRectangle			 *m_pColorTarget2;			/**< Color target 2, can be NULL */
		PLRenderer::TextureBufferRectangle			 *m_pColorTarget3;			/**< Color target 3, can be NULL */
		bool										  m_bColorTarget3Used;		/**< Was the RGB color target 3 actually used when filling the current GBuffer content? */
		bool										  m_bColorTarget3AlphaUsed;	/**< Was the alpha component of target 3 actually used when filling the current GBuffer content? */
		PLRenderer::Surface							 *m_pSurfaceBackup;			/**< Backup of the previously set render surface, can be NULL */
		PLScene::FullscreenQuad						 *m_pFullscreenQuad;		/**< Fullscreen quad instance, can be NULL */
		PLGeneral::Pool<const PLRenderer::Material*>  m_lstMaterials;			/**< List of currently used materials */
		PLGeneral::Pool<MeshBatch*>					  m_lstFreeMeshBatches;		/**< List of currently free mesh batches */
		PLGeneral::Pool<MeshBatch*>					  m_lstMeshBatches;			/**< List of currently used mesh batches */
		PLRenderer::ProgramGenerator				 *m_pProgramGenerator;		/**< Program generator, can be NULL */
		PLRenderer::ProgramGenerator::Flags			  m_cProgramFlags;			/**< Program flags as class member to reduce dynamic memory allocations */


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


#endif // __PLCOMPOSITING_DEFERRED_GBUFFER_H__
