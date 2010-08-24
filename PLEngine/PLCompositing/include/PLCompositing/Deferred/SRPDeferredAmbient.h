/*********************************************************\
 *  File: SRPDeferredAmbient.h                           *
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


#ifndef __PLCOMPOSITING_DEFERRED_AMBIENT_H__
#define __PLCOMPOSITING_DEFERRED_AMBIENT_H__
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
*    Scene renderer pass for deferred rendering ambient
*/
class SRPDeferredAmbient : public SRPDeferred {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene renderer pass flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			NoAlbedo            = 1<<1,	/**< Ignore albedo data */
			NoAmbientOcclusion  = 1<<2,	/**< Ignore ambient occlusion data */
			NoSelfIllumination  = 1<<3,	/**< Ignore self illumination data */
			NoStencil           = 1<<4	/**< Ignore stencil buffer */
		};
		pl_enum(EFlags)
			pl_enum_base(SRPDeferred::EFlags)
			pl_enum_value(NoAlbedo,				"Ignore albedo data")
			pl_enum_value(NoAmbientOcclusion,	"Ignore ambient occlusion data")
			pl_enum_value(NoSelfIllumination,	"Ignore self illumination data")
			pl_enum_value(NoStencil,			"Ignore stencil buffer")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDeferredAmbient, "PLCompositing", PLCompositing::SRPDeferred, "Scene renderer pass for deferred rendering ambient")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(AmbientColor,	PLGraphics::Color3,		PLGraphics::Color3(0.2f, 0.2f, 0.2f),	ReadWrite,	DirectValue,	"Ambient color",	"")
		// Overwritten SceneRendererPass variables
		pl_attribute(Flags,			pl_flag_type(EFlags),	0,										ReadWrite,	GetSet,			"Flags",			"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPDeferredAmbient();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDeferredAmbient();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Returns the fragment shader for the requested visualisation mode
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] bAlbedo
		*    Albedo used?
		*  @param[in] bAmbientOcclusion
		*    Ambient occlusion used?
		*  @param[in] bSelfIllumination
		*    Self illumination used?
		*
		*  @return
		*    The fragment shader for the requested visualisation mode, NULL on error
		*/
		PLRenderer::Shader *GetFragmentShader(PLRenderer::Renderer &cRenderer, bool bAlbedo, bool bAmbientOcclusion, bool bSelfIllumination);

		/**
		*  @brief
		*    Destroys all currently used shaders
		*/
		void DestroyShaders();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool										m_bFragmentShader[2][2][2];	/**< Fragment shader build? [Albedo][AmbientOcclusion][SelfIllumination] */
		PLRenderer::ShaderHandler					m_cFragmentShader[2][2][2];	/**< Fragment shader mode [Albedo][AmbientOcclusion][SelfIllumination] */
		PLGeneral::List<PLRenderer::ShaderHandler*> m_lstShaders;				/**< List of all used shaders */


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


#endif // __PLCOMPOSITING_DEFERRED_AMBIENT_H__
