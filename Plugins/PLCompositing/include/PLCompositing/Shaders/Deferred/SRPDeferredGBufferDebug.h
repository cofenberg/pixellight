/*********************************************************\
 *  File: SRPDeferredGBufferDebug.h                      *
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


#ifndef __PLCOMPOSITING_DEFERRED_GBUFFERDEBUG_H__
#define __PLCOMPOSITING_DEFERRED_GBUFFERDEBUG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color3.h>
#include <PLRenderer/Renderer/ProgramGenerator.h>
#include "PLCompositing/Shaders/Deferred/SRPDeferred.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class ProgramUniform;
	class ProgramAttribute;
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
*    Scene renderer pass for deferred rendering GBuffer debug
*/
class SRPDeferredGBufferDebug : public SRPDeferred {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Debug modes
		*/
		enum EMode {
			ShowAlbedo           = 0,	/**< Show albedo data (RGB) */
			ShowAmbientOcclusion = 1,	/**< Show ambient occlusion data (Grayscale) */
			ShowNormals          = 2,	/**< Show normal data (RGB, view space) */
			ShowDepth            = 3,	/**< Show depth data (Grayscale, view space linear depth, dark=near, brigh=far -> may look just black if the distance between far and near plane is to high) */
			ShowSpecularColor    = 4,	/**< Show specular color data (RGB) */
			ShowSpecularExponent = 5,	/**< Show specular exponent data (Grayscale) */
			ShowSelfIllumination = 6,	/**< Show self illumination (RGB, emissive maps, light maps) */
			ShowGlow             = 7,	/**< Show glow (Grayscale) */
			UnknownMode          = 8,	/**< Unknown debug mode (just black result) */
			NumOfModes           = 9	/**< Number of debug modes */
		};
		pl_enum(EMode)
			pl_enum_value(ShowAlbedo,			"Show albedo data (RGB)")
			pl_enum_value(ShowAmbientOcclusion,	"Show ambient occlusion data (Grayscale)")
			pl_enum_value(ShowNormals,			"Show normal data (RGB, view space)")
			pl_enum_value(ShowDepth,			"Show depth data (Grayscale, view space linear depth, dark=near, brigh=far -> may look just black if the distance between far and near plane is to high)")
			pl_enum_value(ShowSpecularColor,	"Show specular color data (RGB)")
			pl_enum_value(ShowSpecularExponent,	"Show specular exponent data (Grayscale)")
			pl_enum_value(ShowSelfIllumination,	"Show self illumination (RGB, emissive maps, light maps)")
			pl_enum_value(ShowGlow,				"Show glow (Grayscale)")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDeferredGBufferDebug, "PLCompositing", PLCompositing::SRPDeferred, "Scene renderer pass for deferred rendering GBuffer debug")
		// Attributes
		pl_attribute(ShaderLanguage,	PLCore::String,			"",			ReadWrite,	DirectValue,	"Shader language to use (for example \"GLSL\" or \"Cg\"), if empty string, the default shader language of the renderer will be used",	"")
		pl_attribute(Mode,				pl_enum_type(EMode),	ShowAlbedo,	ReadWrite,	DirectValue,	"Debug mode",																															"")
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
		PLCOM_API SRPDeferredGBufferDebug();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDeferredGBufferDebug();


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Fragment shader flags, flag names become to source code definitions
		*/
		enum EFragmentShaderFlags {
			FS_SHOW_ALBEDO			  = 1<<0,	/**< Show albedo */
			FS_SHOW_AMBIENTOCCLUSION  = 1<<1,	/**< Show ambient occlusion */
			FS_SHOW_NORMALS			  = 1<<2,	/**< Show normals */
			FS_SHOW_DEPTH			  = 1<<3,	/**< Show depth */
			FS_SHOW_SPECULAR_COLOR	  = 1<<4,	/**< Show specular color */
			FS_SHOW_SPECULAR_EXPONENT = 1<<5,	/**< Show specular exponent */
			FS_SHOW_SELFILLUMINATION  = 1<<6,	/**< Show self illumination */
			FS_SHOW_GLOW			  = 1<<7,	/**< Show glow */
			FS_SHOW_BLACK			  = 1<<8	/**< Show black */
		};

		/**
		*  @brief
		*    Direct pointers to uniforms & attributes of a generated program
		*/
		struct GeneratedProgramUserData {
			// Vertex shader attributes
			PLRenderer::ProgramAttribute *pVertexPosition;
			// Vertex shader uniforms
			PLRenderer::ProgramUniform *pTextureSize;
			// Fragment shader uniforms
			PLRenderer::ProgramUniform *pNearPlane;
			PLRenderer::ProgramUniform *pRange;
			PLRenderer::ProgramUniform *pMap;
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::ProgramGenerator		*m_pProgramGenerator;	/**< Program generator, can be a null pointer */
		PLRenderer::ProgramGenerator::Flags	 m_cProgramFlags;		/**< Program flags as class member to reduce dynamic memory allocations */


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


#endif // __PLCOMPOSITING_DEFERRED_GBUFFERDEBUG_H__