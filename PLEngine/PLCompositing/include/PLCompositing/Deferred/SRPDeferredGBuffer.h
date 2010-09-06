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
#include <PLRenderer/Shader/ShaderManager.h>
#include "PLCompositing/Deferred/SRPDeferred.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Surface;
	class Material;
	class RenderStates;
	class SurfaceTextureBuffer;
	class TextureBufferRectangle;
}
namespace PLMesh {
	class Mesh;
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
*    - Glow:                       Glow factor, values 0.0...1.0=no glow...full glow, default: 0.0
*      - GlowMap:                  If 'Glow' is not 0, per fragment 'glow' control (2D, grayscale)
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
*    - Normal map compression using swizzled DXT5 (xGxR) and alternate XY swizzle LATC2 is supported
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
		pl_attribute(TextureFiltering,	pl_enum_type(ETextureFiltering),	Anisotropic8,	ReadWrite,	DirectValue,	"Texture filtering",	"")
		// Overwritten SceneRendererPass variables
		pl_attribute(Flags,				pl_flag_type(EFlags),				0,				ReadWrite,	GetSet,			"Flags",				"")
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
		*/
		void SetupTextureFiltering(PLRenderer::Renderer &cRenderer, PLGeneral::uint32 nStage) const;

		/**
		*  @brief
		*    Returns an ambient/emissive vertex shader
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] bDiffuseMap
		*    Diffuse map
		*  @param[in] bParallax
		*    Parallax mapping
		*  @param[in] bDisplacementMap
		*    Displacement mapping
		*  @param[in] bAmbientOcclusionMap
		*    Ambient occlusion map
		*  @param[in] bNormalMap
		*    Normal map
		*  @param[in] bEmissiveMap
		*    Emissive map
		*  @param[in] bReflection
		*    Reflecton
		*  @param[in] bLightMap
		*    Light map
		*  @param[in] bTwoSided
		*    Two sided
		*  @param[in] fAlphaReference
		*    Alpha reference
		*
		*  @return
		*    The shader with the requested features, NULL on error
		*/
		PLRenderer::Shader *GetVertexShader(PLRenderer::Renderer &cRenderer, bool bDiffuseMap, bool bParallax, bool bDisplacementMap, bool bAmbientOcclusionMap, bool bNormalMap, bool bEmissiveMap, bool bReflection, bool bLightMap, bool bTwoSided, float fAlphaReference);

		/**
		*  @brief
		*    Returns an ambient/emissive fragment shader
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] bDiffuseMap
		*    Diffuse map
		*  @param[in] bSpecular
		*    Specular
		*  @param[in] bSpecularMap
		*    Specular map
		*  @param[in] bParallax
		*    Parallax mapping
		*  @param[in] bAmbientOcclusionMap
		*    Ambient occlusion map
		*  @param[in] bEmissiveMap
		*    Emissive map
		*  @param[in] b2DReflection
		*    2D reflecton (can't be set together with 'bCubeReflection'!)
		*  @param[in] bCubeReflection
		*    Cube reflecton (can't be set together with 'b2DReflection'!)
		*  @param[in] bReflectivityMap
		*    Reflectivity map
		*  @param[in] bLightMap
		*    Light map
		*  @param[in] bAlphaTest
		*    Alpha test
		*  @param[in] bNormalMap
		*    Normal map
		*  @param[in] bNormalMap_DXT5_xGxR
		*    DXT5 xGxR normal map
		*  @param[in] bDetailNormalMap
		*    Detail normal map
		*  @param[in] bDetailNormalMap_DXT5_xGxR
		*    DXT5 xGxR detail normal map
		*  @param[in] fAlphaReference
		*    Alpha reference
		*  @param[in] bFresnelReflection
		*    Use fresnel reflection?
		*  @param[in] bGlow
		*    Use glow?
		*  @param[in] bGlowMap
		*    Use glow map?
		*  @param[in] bGammaCorrection
		*    Use gamma correction?
		*
		*  @return
		*    The shader with the requested features, NULL on error
		*/
		PLRenderer::Shader *GetFragmentShader(PLRenderer::Renderer &cRenderer, bool bDiffuseMap, bool bSpecular, bool bSpecularMap, bool bParallax, bool bAmbientOcclusionMap, bool bEmissiveMap, bool b2DReflection, bool bCubeReflection, bool bReflectivityMap, bool bLightMap, bool bAOAlphaTest, bool bNormalMap, bool bNormalMap_DXT5_xGxR, bool bDetailNormalMap, bool bDetailNormalMap_DXT5_xGxR, float fAlphaReference, bool bFresnelReflection, bool bGlow, bool bGlowMap, bool bGammaCorrection);

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
		*/
		void DrawRec(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery);

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
		*/
		void DrawMesh(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery, const PLScene::VisNode &cVisNode, PLScene::SceneNode &cSceneNode, const PLMesh::MeshHandler &cMeshHandler, const PLMesh::Mesh &cMesh, const PLMesh::MeshLODLevel &cMeshLODLevel);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::SurfaceTextureBuffer   *m_pRenderTarget;			/**< Render target of the GBuffer, can be NULL */
		PLRenderer::TextureBufferRectangle *m_pColorTarget1;			/**< Color target 1, can be NULL */
		PLRenderer::TextureBufferRectangle *m_pColorTarget2;			/**< Color target 2, can be NULL */
		PLRenderer::TextureBufferRectangle *m_pColorTarget3;			/**< Color target 3, can be NULL */
		bool								m_bColorTarget3Used;		/**< Was the RGB color target 3 actually used when filling the current GBuffer content? */
		bool								m_bColorTarget3AlphaUsed;	/**< Was the alpha component of target 3 actually used when filling the current GBuffer content? */
		PLRenderer::Surface				   *m_pSurfaceBackup;			/**< Backup of the previously set render surface, can be NULL */
		PLScene::FullscreenQuad			   *m_pFullscreenQuad;			/**< Fullscreen quad instance, can be NULL */

		PLRenderer::RenderStates	*m_pRenderStates;		/**< Used to 'translate' render state strings, always valid! */
		PLGeneral::uint32			 m_nMaterialChanges;	/**< Number of material changes */
		const PLRenderer::Material	*m_pCurrentMaterial;	/**< Current used material, can be NULL */

		bool					  m_bVertexShader[2][2][2][2][2][2][2][2][2];										/**< [DiffuseMap][Parallax][DisplacementMap][AmbientOcclusionMap][TangentBinormal][EmissiveMap][Reflection][LightMap][TwoSided] */
		PLRenderer::ShaderHandler m_cVertexShader[2][2][2][2][2][2][2][2][2];										/**< [DiffuseMap][Parallax][DisplacementMap][AmbientOcclusionMap][TangentBinormal][EmissiveMap][Reflection][LightMap][TwoSided] */
		bool					  m_bFragmentShader[2][2][2][2][2][2][2][2][2][2][2][2][2][2][2][2][2][2][2][2];	/**< [DiffuseMap][Specular][SpecularMap][Parallax][AmbientOcclusionMap][EmissiveMap][2DReflectionMap][CubeReflectionMap][ReflectivityMap][LightMap][AOAlphaTest][NormalMap][NormalMap_DXT5_xGxR][DetailNormalMap][DetailNormalMap_DXT5_xGxR][FresnelReflection][Glow][GlowMap][Reflection][GammaCorrection] */
		PLRenderer::ShaderHandler m_cFragmentShader[2][2][2][2][2][2][2][2][2][2][2][2][2][2][2][2][2][2][2][2];	/**< [DiffuseMap][Specular][SpecularMap][Parallax][AmbientOcclusionMap][EmissiveMap][2DReflectionMap][CubeReflectionMap][ReflectivityMap][LightMap][AOAlphaTest][NormalMap][NormalMap_DXT5_xGxR][DetailNormalMap][DetailNormalMap_DXT5_xGxR][FresnelReflection][Glow][GlowMap][Reflection][GammaCorrection] */

		PLGeneral::List<PLRenderer::ShaderHandler*> m_lstShaders;	/**< List of all used shaders */


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
