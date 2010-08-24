/*********************************************************\
 *  File: HDRLightAdaptation.h                           *
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


#ifndef __PLCOMPOSITING_HDR_LIGHTADAPTION_H__
#define __PLCOMPOSITING_HDR_LIGHTADAPTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Shader/ShaderManager.h>
#include "PLCompositing/PLCompositing.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class TextureBuffer;
	class TextureBuffer2D;
	class SurfaceTextureBuffer;
	class TextureBufferRectangle;
}
namespace PLScene {
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
*    HDR light adaptation component
*
*  @note
*    - The Pattanaik technique described in http://www.coretechniques.info/PostFX.zip is used
*/
class HDRLightAdaptation {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*/
		PLCOM_API HDRLightAdaptation(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API ~HDRLightAdaptation();

		/**
		*  @brief
		*    Calculates the light adaptation
		*
		*  @param[in] cAverageLuminanceTextureBuffer2D
		*    Current average luminance texture buffer
		*  @param[in] fTauTimeDifference
		*    Tau multiplied with the current time difference
		*
		*  @note
		*    - Use GetTextureBuffer() to receive the result of the calculation
		*/
		PLCOM_API void CalculateLightAdaptation(PLRenderer::TextureBuffer &cAverageLuminanceTextureBuffer2D, float fTauTimeDifference);

		/**
		*  @brief
		*    Returns the 1x1 2D texture buffer storing the light adaptation
		*
		*  @return
		*    The 1x1 2D texture buffer storing the light adaptation, NULL on error
		*
		*  @note
		*    - The texture buffer is only valid after CalculateLightAdaptation() was called
		*/
		PLCOM_API PLRenderer::TextureBuffer *GetTextureBuffer() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Returns the fragment shader
		*
		*  @return
		*    The fragment shader, NULL on error
		*/
		PLRenderer::Shader *GetFragmentShader();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::Renderer			 *m_pRenderer;							/**< Renderer to use, always valid! */
		PLScene::FullscreenQuad			 *m_pFullscreenQuad;					/**< Fullscreen quad instance, can be NULL */
		bool							  m_bFragmentShader;					/**< Fragment shader build? */
		PLRenderer::ShaderHandler		  m_cFragmentShader;					/**< Fragment shader mode */
		PLRenderer::SurfaceTextureBuffer *m_pLightAdaptationTextureBuffer2D[2];	/**< 1x1 2D texture buffer storing the previous and current light adaptation */
		bool							  m_bPreviousIndex;						/**< Index of the previous 2D light adaptation texture buffer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_HDR_LIGHTADAPTION_H__
