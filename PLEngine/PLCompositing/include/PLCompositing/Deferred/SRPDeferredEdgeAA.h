/*********************************************************\
 *  File: SRPDeferredEdgeAA.h                            *
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


#ifndef __PLCOMPOSITING_DEFERRED_EDGEAA_H__
#define __PLCOMPOSITING_DEFERRED_EDGEAA_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
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
*    Scene renderer pass for deferred rendering anti-aliasing using resolution-independent edge detection
*
*  @note
*    - The technique described in http://http.developer.nvidia.com/GPUGems3/gpugems3_ch19.html is used
*/
class SRPDeferredEdgeAA : public SRPDeferred {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene renderer pass flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			MoreSamples   = 1<<1,	/**< Take more samples */
			ShowEdges     = 1<<2,	/**< Show edges (for debugging) */
			ShowEdgesOnly = 1<<3	/**< Show only edges (for debugging) */
		};
		pl_enum(EFlags)
			pl_enum_base(SRPDeferred::EFlags)
			pl_enum_value(MoreSamples,		"Take more samples")
			pl_enum_value(ShowEdges,		"Show edges (for debugging)")
			pl_enum_value(ShowEdgesOnly,	"Show only edges (for debugging)")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDeferredEdgeAA, "PLCompositing", PLCompositing::SRPDeferred, "Scene renderer pass for deferred rendering anti-aliasing using resolution-independent edge detection")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(WeightScale,	float,					1.0f,	ReadWrite,	DirectValue,	"Weight scale",	"")
		// Overwritten SceneRendererPass variables
		pl_attribute(Flags,			pl_flag_type(EFlags),	0,		ReadWrite,	GetSet,			"Flags",		"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPDeferredEdgeAA();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDeferredEdgeAA();


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
		*  @param[in] bMoreSamples
		*    Take more samples
		*  @param[in] bShowEdges
		*    Show edges (and do not perform anti-aliasing)
		*  @param[in] bShowEdgesOnly
		*    Show edges only (and do not perform anti-aliasing)
		*
		*  @return
		*    The fragment shader, NULL on error
		*/
		PLRenderer::Shader *GetFragmentShader(PLRenderer::Renderer &cRenderer, bool bMoreSamples, bool bShowEdges, bool bShowEdgesOnly);

		/**
		*  @brief
		*    Destroys all currently used shaders
		*/
		void DestroyShaders();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool										m_bFragmentShader[2][2][2];	/**< Fragment shader build? [MoreSamples][ShowEdges][ShowEdgesOnly] */
		PLRenderer::ShaderHandler					m_cFragmentShader[2][2][2];	/**< Fragment shader mode [MoreSamples][ShowEdges][ShowEdgesOnly] */
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


#endif // __PLCOMPOSITING_DEFERRED_EDGEAA_H__
