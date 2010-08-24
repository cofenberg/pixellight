/*********************************************************\
 *  File: SRPPostProcessing.h                            *
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


#ifndef __PLSCENE_COMPOSITING_GENERAL_POSTPROCESSING_H__
#define __PLSCENE_COMPOSITING_GENERAL_POSTPROCESSING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Compositing/SceneRendererPass.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Surface;
	class SurfaceTextureBuffer;
}
namespace PLScene {
	class SNCamera;
	class PostProcessor;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene renderer pass performing post processing (also known as 'composing')
*/
class SRPPostProcessing : public SceneRendererPass {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SRPPostProcessing, "PLScene", PLScene::SceneRendererPass, "Scene renderer pass performing post processing (also known as 'composing')")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SRPPostProcessing();

		/**
		*  @brief
		*    Destructur
		*/
		PLS_API virtual ~SRPPostProcessing();

		/**
		*  @brief
		*    Returns the post processor
		*
		*  @return
		*    The post processor, or NULL if currently no post processor is available
		*/
		PLS_API PostProcessor *GetPostProcessor();

		/**
		*  @brief
		*    Sets another render target if required
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*    - If you want to draw your scene first into a texture use this
		*      function to set the new render target (required for post processing)
		*    - You should backup the current render target in order to be able to restore it
		*/
		PLS_API bool SetRenderTarget(PLRenderer::Renderer &cRenderer);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Returns whether or not post processing is required
		*
		*  @param[in] cCamera
		*    Camera to use
		*
		*  @return
		*    'true' if post processing is required, else 'false'
		*/
		bool IsPostProcessingRequired(SNCamera &cCamera);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Private data
		PLRenderer::SurfaceTextureBuffer *m_pColorMap;		/**< Can be NULL */
		PostProcessor					 *m_pPostProcessor;	/**< Can be NULL */
		PLRenderer::Surface				 *m_pSurfaceT;		/**< Can be NULL */


	//[-------------------------------------------------------]
	//[ Private virtual SceneRendererPass functions           ]
	//[-------------------------------------------------------]
	private:
		virtual void Draw(PLRenderer::Renderer &cRenderer, const SQCull &cCullQuery);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_COMPOSITING_GENERAL_POSTPROCESSING_H__
