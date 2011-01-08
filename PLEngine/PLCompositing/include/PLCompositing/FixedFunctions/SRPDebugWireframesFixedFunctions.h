/*********************************************************\
 *  File: SRPDebugWireframesFixedFunctions.h             *
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


#ifndef __PLCOMPOSITING_FIXEDFUNCTIONS_WIREFRAMES_H__
#define __PLCOMPOSITING_FIXEDFUNCTIONS_WIREFRAMES_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCompositing/SRPDebugWireframes.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMesh {
	class MeshHandler;
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
*    Fixed functions based scene renderer pass drawing just simple wireframes
*/
class SRPDebugWireframesFixedFunctions : public SRPDebugWireframes {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDebugWireframesFixedFunctions, "PLCompositing", PLCompositing::SRPDebugWireframes, "Fixed functions based scene renderer pass drawing just simple wireframes")
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
		PLCOM_API SRPDebugWireframesFixedFunctions();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDebugWireframesFixedFunctions();


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
		*/
		void DrawRec(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery) const;

		/**
		*  @brief
		*    Draws a mesh
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cVisNode
		*    Visibility node to use
		*  @param[in] cMeshHandler
		*    Mesh handler to use
		*/
		void DrawMesh(PLRenderer::Renderer &cRenderer, const PLScene::VisNode &cVisNode, const PLMesh::MeshHandler &cMeshHandler) const;


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


#endif // __PLCOMPOSITING_FIXEDFUNCTIONS_WIREFRAMES_H__
