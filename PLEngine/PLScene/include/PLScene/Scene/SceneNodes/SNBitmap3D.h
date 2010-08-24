/*********************************************************\
 *  File: SNBitmap3D.h                                   *
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


#ifndef __PLSCENE_SCENENODE_BITMAP3D_H__
#define __PLSCENE_SCENENODE_BITMAP3D_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneNodes/SNBitmap.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class IndexBuffer;
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
*    3D bitmap scene node
*
*  @note
*    - It's NOT recommended to use this scene node for example to create dense vegetation on a terrain!
*    - The axis aligned bounding box is centered around zero and each axis has a length of 1
*    - The bitmap is drawn on the x/y plane and 'looks' into the positive z axis
*/
class SNBitmap3D : public SNBitmap {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNBitmap3D, "PLScene", PLScene::SNBitmap, "3D bitmap scene node")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(PositionOffset,	PLMath::Vector3,	PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	GetSet,	"Position offset (scene node space)",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API const PLMath::Vector3 &GetPositionOffset() const;
		PLS_API void SetPositionOffset(const PLMath::Vector3 &vValue);
		PLS_API virtual void SetColor(const PLGraphics::Color4 &cValue);		// From SNBitmap
		PLS_API virtual void SetTexelStart(const PLMath::Vector2 &vValue);	// From SNBitmap
		PLS_API virtual void SetTexelEnd(const PLMath::Vector2 &vValue);		// From SNBitmap
		PLS_API virtual void SetFlags(PLGeneral::uint32 nValue);				// From SceneNode


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNBitmap3D();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNBitmap3D();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Create the bitmap shape
		*
		*  @note
		*    - Creates the index and vertex buffer
		*/
		void CreateShape();

		/**
		*  @brief
		*    Updates texture coordinates and color of the vertex buffer
		*
		*  @note
		*    - Vertex buffer MUST be valid AND locked!
		*/
		void UpdateTextureCoordinatesAndColor();

		/**
		*  @brief
		*    Draws the bitmap shape
		*
		*  @param[in] cRenderer
		*    The used renderer
		*  @param[in] cVisNode
		*    Used visibility node
		*/
		void DrawShape(PLRenderer::Renderer &cRenderer, const VisNode &cVisNode);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMath::Vector3				 m_vPositionOffset;				/**< Position offset (scene node space) */
		PLRenderer::IndexBuffer		*m_pIndexBuffer;				/**< Index buffer, can be NULL */
		PLRenderer::VertexBuffer	*m_pVertexBuffer;				/**< Vertex buffer, can be NULL */
		bool						 m_bUpdatePositionOffset;		/**< Update the position data of the vertex buffer? */
		bool						 m_bUpdateTextureCoordinates;	/**< Update the texture coordinate data of the vertex buffer? */
		bool						 m_bUpdateColor;				/**< Update the color data of the vertex buffer? */


	//[-------------------------------------------------------]
	//[ Public virtual SceneNode functions                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void DrawSolid(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = NULL);
		PLS_API virtual void DrawTransparent(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = NULL);


	//[-------------------------------------------------------]
	//[ Private virtual SceneNode functions                   ]
	//[-------------------------------------------------------]
	private:
		virtual void UpdateAABoundingBox();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_BITMAP3D_H__
