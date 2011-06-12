/*********************************************************\
 *  File: SRPDeferred.h                                  *
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


#ifndef __PLCOMPOSITING_DEFERRED_H__
#define __PLCOMPOSITING_DEFERRED_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Compositing/SceneRendererPass.h>
#include "PLCompositing/PLCompositing.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class VertexBuffer;
}
namespace PLCompositing {
	class SRPDeferredGBuffer;
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
*    Abstract scene renderer pass for deferred rendering
*
*  @note
*    - There must be an SRPDeferredGBuffer instance within the render pipeline
*/
class SRPDeferred : public PLScene::SceneRendererPass {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDeferred, "PLCompositing", PLScene::SceneRendererPass, "Abstract scene renderer pass for deferred rendering")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the first found instance of a SRPDeferredGBuffer scene renderer pass instance within the scene renderer pipeline
		*
		*  @return
		*    The first found instance of a SRPDeferredGBuffer scene renderer pass instance within the scene renderer pipeline, can be a null pointer
		*/
		PLCOM_API SRPDeferredGBuffer *GetGBuffer() const;

		/**
		*  @brief
		*    Returns the vertex buffer of this deferred scene renderer pass
		*
		*  @return
		*    The vertex buffer of this deferred scene renderer pass, a null pointer on error
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
		PLCOM_API PLRenderer::VertexBuffer *GetVertexBuffer();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		PLCOM_API SRPDeferred();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDeferred();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::VertexBuffer *m_pVertexBuffer;	/**< Vertex buffer, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_DEFERRED_H__
