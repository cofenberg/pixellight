/*********************************************************\
 *  File: SRPDeferredGBufferDebug.h                      *
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


#ifndef __PLCOMPOSITING_DEFERRED_GBUFFERDEBUG_H__
#define __PLCOMPOSITING_DEFERRED_GBUFFERDEBUG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color3.h>
#include <PLRenderer/Shader/ShaderManager.h>
#include "PLCompositing/Deferred/SRPDeferred.h"


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
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(Mode,	pl_enum_type(EMode),	ShowAlbedo,	ReadWrite,	DirectValue,	"Debug mode",	"")
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
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Returns the fragment shader for the requested debug mode
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] bBlack
		*    Just draw black?
		*
		*  @return
		*    The fragment shader for the requested debug mode, NULL on error
		*/
		PLRenderer::Shader *GetFragmentShader(PLRenderer::Renderer &cRenderer, bool bBlack);

		/**
		*  @brief
		*    Destroys all currently used shaders
		*/
		void DestroyShaders();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool										m_bFragmentShader[NumOfModes];	/**< Fragment shader per debug mode build? */
		PLRenderer::ShaderHandler					m_cFragmentShader[NumOfModes];	/**< Fragment shader per debug mode */
		PLGeneral::List<PLRenderer::ShaderHandler*> m_lstShaders;					/**< List of all used shaders */


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
