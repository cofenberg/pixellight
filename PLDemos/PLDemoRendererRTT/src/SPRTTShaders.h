/*********************************************************\
 *  File: SPRTTShaders.h                                 *
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


#ifndef __PLDEMORENDERERRTT_SURFACEPAINTER_SHADERS_H__
#define __PLDEMORENDERERRTT_SURFACEPAINTER_SHADERS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "SPRTT.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Program;
	class VertexShader;
	class FragmentShader;
	class TextureBuffer2D;
	class SurfaceTextureBuffer;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Shaders based render to texture surface painter
*/
class SPRTTShaders : public SPRTT {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SPRTTShaders, "", SPRTT, "Shaders based render to texture surface painter")
		pl_constructor_1(ParameterConstructor, PLRenderer::Renderer&, "Parameter constructor", "")
	pl_class_end


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
		SPRTTShaders(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SPRTTShaders();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Draws the scene
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*/
		void DrawScene(PLRenderer::Renderer &cRenderer);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::SurfaceTextureBuffer *m_pRenderTarget;			/**< The render target the teapot is rendered in, can be a null pointer */
		PLRenderer::TextureBuffer2D		 *m_pColorTarget1;			/**< Color target 1, can be a null pointer */
		PLRenderer::TextureBuffer2D		 *m_pColorTarget2;			/**< Color target 2, can be a null pointer */
		PLRenderer::TextureBuffer2D		 *m_pColorTarget3;			/**< Color target 3, can be a null pointer */
		PLRenderer::VertexShader		 *m_pSceneVertexShader;		/**< Scene vertex shader, can be a null pointer */
		PLRenderer::FragmentShader		 *m_pSceneFragmentShader;	/**< Scene fragment shader, can be a null pointer */
		PLRenderer::Program				 *m_pSceneProgram;			/**< Scene GPU program, can be a null pointer */
		PLRenderer::VertexShader		 *m_pVertexShader;			/**< Vertex shader, can be a null pointer */
		PLRenderer::FragmentShader		 *m_pFragmentShader;		/**< Fragment shader, can be a null pointer */
		PLRenderer::Program				 *m_pProgram;				/**< GPU program, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::SurfacePainter functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void OnPaint(PLRenderer::Surface &cSurface);


};


#endif // __PLDEMORENDERERRTT_SURFACEPAINTER_SHADERS_H__
