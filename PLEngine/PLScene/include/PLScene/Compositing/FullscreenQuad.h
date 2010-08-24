/*********************************************************\
 *  File: FullscreenQuad.h                               *
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


#ifndef __PLSCENE_COMPOSITING_FULLSCREENQUAD_H__
#define __PLSCENE_COMPOSITING_FULLSCREENQUAD_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2i.h>
#include <PLRenderer/Shader/ShaderManager.h>
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Renderer;
	class VertexBuffer;
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
*    Fullscreen quad
*
*  @remarks
*    The default content of the vertex buffer is a fullscreen quad consisting of 4 vertices:
*    Vertex 0 - lower/left corner
*      - Position:             (-1.0f, -1.0f, 0.0f, 1.0f)
*      - Texture coordinate 0: ( 0.0f,  0.0f)
*    Vertex 1 - lower/right corner
*      - Position:             ( 1.0f, -1.0f, 0.0f, 1.0f)
*      - Texture coordinate 0: ( 1.0f,  0.0f)
*    Vertex 2 - upper/left corner
*      - Position:             (-1.0f,  1.0f, 0.0f, 1.0f)
*      - Texture coordinate 0: ( 0.0f,  1.0f)
*    Vertex 3 - upper/right corner
*      - Position:             ( 1.0f,  1.0f, 0.0f, 1.0f)
*      - Texture coordinate 0: ( 1.0f,  1.0f)
*/
class FullscreenQuad {


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
		PLS_API FullscreenQuad(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructur
		*/
		PLS_API ~FullscreenQuad();

		/**
		*  @brief
		*    Returns the vertex buffer of this fullscreen quad
		*
		*  @return
		*    The vertex buffer of this fullscreen quad, NULL on error
		*/
		PLS_API PLRenderer::VertexBuffer *GetVertexBuffer();

		/**
		*  @brief
		*    Returns the vertex shader of this fullscreen quad
		*
		*  @param[in] bSizeContol
		*    Size control enabled?
		*
		*  @return
		*    The vertex shader of this fullscreen quad, NULL on error
		*/
		PLS_API PLRenderer::Shader *GetVertexShader(bool bSizeContol);

		/**
		*  @brief
		*    Draws the fullscreen quad
		*
		*  @param[in] vTextureSize
		*    Texture size in texel
		*  @param[in] vSize
		*    Quad size in pixel, if any component is <= 0 a fullscreen quad is drawn (default)
		*
		*  @note
		*    - Sets the vertex buffer of the fullscreen quad
		*    - Sets the vertex shader of the fullscreen quad
		*    - Sets required render states
		*    - Draws the fullscreen quad
		*/
		PLS_API void Draw(const PLMath::Vector2i &vTextureSize, const PLMath::Vector2i &vSize = PLMath::Vector2i::Zero);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::Renderer	  *m_pRenderer;			/**< Renderer to use, always valid! */
		PLRenderer::VertexBuffer  *m_pVertexBuffer;		/**< Vertex buffer, can be NULL */
		bool					   m_bVertexShader[2];	/**< Vertex shader already build? [SizeContol] */
		PLRenderer::ShaderHandler  m_cVertexShader[2];	/**< Vertex shader [SizeContol] */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_COMPOSITING_FULLSCREENQUAD_H__
