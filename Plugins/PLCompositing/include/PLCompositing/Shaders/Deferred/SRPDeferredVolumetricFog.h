/*********************************************************\
 *  File: SRPDeferredVolumetricFog.h                     *
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


#ifndef __PLCOMPOSITING_DEFERRED_VOLUMETRICFOG_H__
#define __PLCOMPOSITING_DEFERRED_VOLUMETRICFOG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/ProgramGenerator.h>
#include "PLCompositing/Shaders/Deferred/SRPDeferred.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class ProgramUniform;
	class ProgramAttribute;
}
namespace PLScene {
	class VisNode;
	class SNSphereFog;
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
*    Deferred rendering based volumetric fog scene renderer pass implementation
*/
class SRPDeferredVolumetricFog : public SRPDeferred {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDeferredVolumetricFog, "PLCompositing", PLCompositing::SRPDeferred, "Deferred rendering based volumetric fog scene renderer pass implementation")
		// Attributes
		pl_attribute(ShaderLanguage,	PLCore::String,	"",	ReadWrite,	DirectValue,	"Shader language to use (for example \"GLSL\" or \"Cg\"), if empty string, the default shader language of the renderer will be used",	"")
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
		PLCOM_API SRPDeferredVolumetricFog();

		/**
		*  @brief
		*    Destructor
		*/
		PLCOM_API virtual ~SRPDeferredVolumetricFog();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
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
		*    Renders a fog
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cCullQuery
		*    Cull query to use
		*  @param[in] cSRPDeferredGBuffer
		*    "SRPDeferredGBuffer" scene renderer pass to use
		*  @param[in] cFog
		*    Used fog node
		*  @param[in] cFogVisNode
		*    The fog visibility node
		*/
		void RenderFog(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery, SRPDeferredGBuffer &cSRPDeferredGBuffer, PLScene::SNSphereFog &cFog, const PLScene::VisNode &cFogVisNode);

		/**
		*  @brief
		*    Renderer setup
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cSRPDeferredGBuffer
		*    "SRPDeferredGBuffer" scene renderer pass to use
		*/
		void RendererSetup(PLRenderer::Renderer &cRenderer, SRPDeferredGBuffer &cSRPDeferredGBuffer);


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Direct pointers to uniforms & attributes of a generated program
		*/
		struct GeneratedProgramUserData {
			// Vertex shader attributes
			PLRenderer::ProgramAttribute *pVertexPosition;
			// Fragment shader uniforms
			PLRenderer::ProgramUniform *pFogPosition;
			PLRenderer::ProgramUniform *pFogInvRadius;
			PLRenderer::ProgramUniform *pFogColor0;
			PLRenderer::ProgramUniform *pFogColor1;
			PLRenderer::ProgramUniform *pInvFocalLen;
			PLRenderer::ProgramUniform *pResolution;
			PLRenderer::ProgramUniform *pNormalDepthMap;
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::ProgramGenerator		*m_pProgramGenerator;	/**< Program generator, can be a null pointer */
		PLRenderer::ProgramGenerator::Flags	 m_cProgramFlags;		/**< Program flags as class member to reduce dynamic memory allocations */
		bool								 m_bFirstFog;			/**< Is this the first for rendered in the current pass? */


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneRendererPass functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void Draw(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_DEFERRED_VOLUMETRICFOG_H__
