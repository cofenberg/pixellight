/*********************************************************\
 *  File: SRPLightingMaterial.h                          *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLCOMPOSITING_GENERAL_LIGHTING_MATERIAL_H__
#define __PLCOMPOSITING_GENERAL_LIGHTING_MATERIAL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
#include <PLGraphics/Color/Color3.h>
#include <PLRenderer/Renderer/ProgramGenerator.h>
#include "PLCompositing/PLCompositing.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Material;
	class Renderer;
	class Parameter;
	class ProgramUniform;
	class ProgramAttribute;
	class ProgramGenerator;
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
*    SRPLighting-material
*/
class SRPLightingMaterial {


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
		/**
		*  @brief
		*    Texture filtering modes
		*/
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
		*    Environment flags
		*/
		enum EEnvironmentFlags {
			EnvironmentVertexNormal				= 1<<0,	/**< There are vertex normals available */
			EnvironmentVertexTexCoord0			= 1<<1,	/**< Texture coordinates at stage 0 are available */
			EnvironmentNormalMappingPossible	= 1<<2,	/**< Normal mapping is possible (normal & tangent & binormal data available) */
			EnvironmentDirectionalLight			= 1<<3,	/**< Directional light */
			EnvironmentProjectivePointLight		= 1<<4,	/**< Projective point light */
			EnvironmentSpotLight				= 1<<5,	/**< Spot light */
			EnvironmentProjectiveSpotLight		= 1<<6,	/**< Projective spot light */
			EnvironmentSpotLightCone			= 1<<7,	/**< Spot light cone */
			EnvironmentSpotLightSmoothCone		= 1<<8,	/**< Spot light smooth cone */
			EnvironmentShadow					= 1<<9	/**< Shadow */
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
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cMaterial
		*    Owner material
		*  @param[in] cProgramGenerator
		*    Program generator
		*/
		SRPLightingMaterial(PLRenderer::Material &cMaterial, PLRenderer::ProgramGenerator &cProgramGenerator);

		/**
		*  @brief
		*    Destructur
		*/
		~SRPLightingMaterial();

		/**
		*  @brief
		*    Makes this material to the currently used one
		*
		*  @param[in] nRendererFlags
		*    SRPLighting-flags to use
		*  @param[in] nEnvironmentFlags
		*    Environment flags to use (see EEnvironmentFlags)
		*  @param[in] nTextureFiltering
		*    Texture filtering
		*  @param[in] fLightingIntensity
		*    Lighting intensity
		*
		*  @return
		*    Generated program user data, do NOT delete the memory the pointer points to
		*/
		GeneratedProgramUserData *MakeMaterialCurrent(PLGeneral::uint32 nRendererFlags, PLGeneral::uint32 nEnvironmentFlags, ETextureFiltering nTextureFiltering, float fLightingIntensity);


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
				FS_NORMALMAP_DXT5_XGXR			= 1<<14,	/**< DXT5 XGXR compressed normal map (FS_NORMALMAP should be defined and FS_NORMALMAP_LATC2 not!) */
				FS_NORMALMAP_LATC2				= 1<<15,	/**< LATC2 compressed normal map (FS_NORMALMAP should be defined and FS_NORMALMAP_DXT5_XGXR not!) */
				FS_DETAILNORMALMAP				= 1<<16,	/**< Take detail normal map into account (FS_NORMALMAP should be defined!) */
				FS_DETAILNORMALMAP_DXT5_XGXR	= 1<<17,	/**< DXT5 XGXR compressed detail normal map (FS_NORMALMAP & FS_DETAILNORMALMAP should be defined and FS_DETAILNORMALMAP_LATC2 not!) */
				FS_DETAILNORMALMAP_LATC2		= 1<<18,	/**< LATC2 compressed detail normal map (FS_NORMALMAP & FS_DETAILNORMALMAP should be defined and FS_DETAILNORMALMAP_DXT5_XGXR not!) */
			FS_SPECULAR							= 1<<19,	/**< Use specular */
				FS_SPECULARMAP					= 1<<20,	/**< Take specular map into account (FS_SPECULAR should be set, too) */
				FS_SPECULARRAMPMAP				= 1<<21,	/**< Take specular ramp map into account (FS_LIGHTING and FS_SPECULAR should be set, too) */
			FS_EDGERAMPMAP						= 1<<22,	/**< Use edge ramp map */
			FS_DIRECTIONAL						= 1<<23,	/**< Directional light */
			FS_PROJECTIVE_POINT					= 1<<24,	/**< Projective point light */
			FS_SPOT								= 1<<25,	/**< Spot light */
				FS_SPOT_PROJECTIVE				= 1<<26,	/**< Projective spot light (FS_SPOT should be set, too) */
				FS_SPOT_CONE					= 1<<27,	/**< Spot light with a cone (FS_SPOT should be set, too) */
					FS_SPOT_SMOOTHCONE			= 1<<28,	/**< Spot light with a smooth cone (FS_SPOT & FS_SPOT_CONE should be set, too) */
			FS_SHADOWMAPPING					= 1<<29,	/**< Perform shadow mapping */
				FS_SOFTSHADOWMAPPING			= 1<<30,	/**< Perform soft shadow mapping (FS_SHADOWMAPPING should be set, too) */
			FS_DISCARD							= 1<<31		/**< Use discard */
		};


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		// Material parameter
		static const PLGeneral::String TwoSided;
		static const PLGeneral::String AlphaReference;
		static const PLGeneral::String DiffuseRampMap;
		static const PLGeneral::String IndexOfRefraction;
		static const PLGeneral::String FresnelReflectionPower;
		static const PLGeneral::String ReflectionColor;
		static const PLGeneral::String Reflectivity;
		static const PLGeneral::String NormalMapBumpiness;
		static const PLGeneral::String DetailNormalMap;
		static const PLGeneral::String DetailNormalMapBumpiness;
		static const PLGeneral::String DetailNormalMapUVScale;
		static const PLGeneral::String Parallax;
		static const PLGeneral::String SpecularColor;
		static const PLGeneral::String SpecularExponent;
		static const PLGeneral::String SpecularRampMap;
		static const PLGeneral::String EdgeRampMap;
		// Shader parameter
		static const PLGeneral::String DiffuseColor;
		static const PLGeneral::String VertexPosition;
		static const PLGeneral::String VertexTexCoord0;
		static const PLGeneral::String VertexNormal;
		static const PLGeneral::String VertexTangent;
		static const PLGeneral::String VertexBinormal;
		static const PLGeneral::String NormalScale;
		static const PLGeneral::String ObjectSpaceToViewSpaceMatrix;
		static const PLGeneral::String ObjectSpaceToClipSpaceMatrix;
		static const PLGeneral::String EyePos;
		// static const PLGeneral::String AlphaReference;	// Already defined
		static const PLGeneral::String FresnelConstants;
		static const PLGeneral::String ViewSpaceToWorldSpace;
		static const PLGeneral::String ParallaxScaleBias;
		static const PLGeneral::String LightDirection;
		static const PLGeneral::String LightPosition;
		static const PLGeneral::String LightRadius;
		static const PLGeneral::String ProjectivePointCubeMap;
		static const PLGeneral::String ViewSpaceToCubeMapSpace;
		static const PLGeneral::String ProjectiveSpotMap;
		static const PLGeneral::String ViewSpaceToSpotMapSpace;
		static const PLGeneral::String SpotConeCos;
		static const PLGeneral::String ShadowMap;
		static const PLGeneral::String ViewSpaceToShadowMapSpace;
		static const PLGeneral::String ViewSpaceToShadowCubeMapSpace;
		static const PLGeneral::String InvLightRadius;
		static const PLGeneral::String TexelSize;
		static const PLGeneral::String LightColor;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Synchronize this material cache with the owner
		*
		*  @param[in] nRendererFlags
		*    SRPLighting-flags to use
		*  @param[in] nEnvironmentFlags
		*    Environment flags to use (see EEnvironmentFlags)
		*/
		void Synchronize(PLGeneral::uint32 nRendererFlags, PLGeneral::uint32 nEnvironmentFlags);

		/**
		*  @brief
		*    Sets correct texture filtering modes
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] nStage
		*    Texture stage
		*  @param[in] nTextureFiltering
		*    Texture filtering
		*/
		void SetupTextureFiltering(PLRenderer::Renderer &cRenderer, PLGeneral::uint32 nStage, ETextureFiltering nTextureFiltering) const;

		/**
		*  @brief
		*    Called when a parameter has been changed (created, destroyed, value changed)
		*
		*  @param[in] cParameter
		*    The changed parameter
		*/
		void NotifyParameterChanged(PLRenderer::Parameter &cParameter);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<PLRenderer::Parameter&> EventHandlerParameterChanged;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// General
		PLRenderer::Material				*m_pMaterial;			/**< Owner material, always valid! */
		PLRenderer::ProgramGenerator		*m_pProgramGenerator;	/**< Program generator, always valid! */
		PLGeneral::uint32					 m_nRendererFlags;		/**< Used SRPLighting-flags */
		PLGeneral::uint32					 m_nEnvironmentFlags;	/**< Used environment flags (see EEnvironmentFlags) */
		bool								 m_bSynchronized;		/**< Synchronized? */
		// Generated program
		PLRenderer::ProgramGenerator::Flags	 m_cProgramFlags;		/**< Program flags as class member to reduce dynamic memory allocations */
		// Synchronized data
			// Two sided
		bool					   m_bTwoSided;
			// Diffuse map and alpha reference
		PLGraphics::Color3		   m_cDiffuseColor;
		float					   m_fAlphaReference;
		PLRenderer::Parameter	  *m_pDiffuseMap;
			// Diffuse ramp map
		PLRenderer::Parameter	  *m_pDiffuseRampMap;
			// Index of refraction and fresnel reflection power
		float					   m_fIndexOfRefraction;
		float					   m_fFresnelReflectionPower;
			// (2D/cube) reflection map
		PLRenderer::Parameter	  *m_pReflectionMap;
		bool					   m_b2DReflectionMap;
			// Figure out whether or not there's reflection on this material
		bool m_bReflection;
			// Reflection parameters
		PLRenderer::Parameter	  *m_pReflectivityMap;
		float					   m_fReflectivity;
		PLGraphics::Color3		   m_cReflectionColor;
			// Normal map
		PLRenderer::Parameter	  *m_pNormalMap;
		float					   m_fNormalMapBumpiness;
			// Detail normal map
		PLRenderer::Parameter	  *m_pDetailNormalMap;
		float					   m_fDetailNormalMapBumpiness;
		PLMath::Vector2			   m_vDetailNormalMapUVScale;
			// Parallax mapping settings
		float					   m_fParallax;
		PLRenderer::Parameter	  *m_pHeightMap;
			// Specular
		PLGraphics::Color3		   m_cSpecularColor;
		PLRenderer::Parameter	  *m_pSpecularMap;
		float					   m_fSpecularExponent;
			// Specular ramp map
		PLRenderer::Parameter	  *m_pSpecularRampMap;
			// Edge ramp map
		PLRenderer::Parameter	  *m_pEdgeRampMap;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_GENERAL_LIGHTING_MATERIAL_H__
