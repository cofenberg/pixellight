/*********************************************************\
 *  File: SCMirror.h                                     *
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


#ifndef __PLSCENE_SCENENODE_MIRROR_H__
#define __PLSCENE_SCENENODE_MIRROR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Polygon.h>
#include "PLScene/Scene/SceneNodes/SCRenderToTexture.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Planar mirror scene node
*
*  @note
*    - The vertices of the mirror plane are on the x/y axis
*    - If the mirror is drawn, it will set the mirror texture automatically at the first
*      texture stage
*    - If the variable 'CameraName' is not set or the given camera is invalid, the mirror
*      will create a camera with the name 'Virtual camera' within it's container
*    - The camera defined through the variable 'CameraName' will be updated automatically by
*      the mirror
*    - If the mirror is rendered more than once per frame (multiple views, mirrored in another mirror etc.)
*      do NOT use a FPS limit - because the mirror only has ONE texture it will render in, this texture can't
*      used over multiple frames if the mirror is render more than once per frame!
*/
class SCMirror : public SCRenderToTexture {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SCMirror, "PLScene", PLScene::SCRenderToTexture, "Planar mirror scene node")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(Material,		PLGeneral::String,	"",										ReadWrite,	DirectValue,	"Material to use",																				"Type='Material Effect Image TextureAni'")
		pl_attribute(DynamicMap,	PLGeneral::String,	"DynamicMap",							ReadWrite,	DirectValue,	"Name of the material/effect parameter to assign the dynamic texture with",						"")
		pl_attribute(Vertices,		PLGeneral::String,	"1.0 -1.0 -1.0 -1.0 -1.0 1.0 1.0 1.0",	ReadWrite,	DirectValue,	"The vertices (x/y position) defining the mirror polygon. Each vertex has 3 components. (xyz)",	"")
		pl_attribute(NearScale,		float,				1.0f,									ReadWrite,	DirectValue,	"Virtual camera near plane scale",																"")
		pl_attribute(Far,			float,				1000.0f,								ReadWrite,	DirectValue,	"Virtual camera far plane",																		"")
		// Overwritten SCRenderToTexture variables
		pl_attribute(FPSLimit,		float,				0.0f,									ReadWrite,	ModifyAttr,		"Frames per second limitation, if 0, there's no limitation",									"Min='0.0'")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SCMirror();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SCMirror();

		/**
		*  @brief
		*    Returns the mirror polygon
		*
		*  @return
		*    The mirror polygon
		*
		*  @note
		*    - After manipulating the vertices of the polygon you should call the polygon
		*      function ComputePlane() to calculate the plane the mirror polygon is on.
		*      Further call UpdateBoundingBox() to calculate the new mirror bounding box.
		*/
		PLS_API PLMath::Polygon &GetPolygon();

		/**
		*  @brief
		*    Updates the surrounding bounding box of the mirror
		*/
		PLS_API void UpdateBoundingBox();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Updates the virtual camera
		*/
		void UpdateVirtualCamera();

		/**
		*  @brief
		*    Sets the dynamic mirror texture
		*/
		void SetDynamicTexture();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float				 m_fWidth;			/**< Mirror width */
		float				 m_fHeight;			/**< Mirror height */
		PLMath::Polygon		 m_cPolygon;		/**< Mirror polygon */
		PLMesh::MeshHandler *m_pMeshHandler;	/**< Mirror mesh handler, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Public virtual SceneNode functions                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual PLMesh::MeshHandler *GetMeshHandler();
		PLS_API virtual void DrawPre(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = nullptr);
		PLS_API virtual void DrawSolid(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = nullptr);
		PLS_API virtual void DrawTransparent(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = nullptr);


	//[-------------------------------------------------------]
	//[ Private virtual SceneNode functions                   ]
	//[-------------------------------------------------------]
	private:
		virtual void InitFunction();
		virtual void UpdateAABoundingBox();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_MIRROR_H__
