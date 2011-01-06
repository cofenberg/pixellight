/*********************************************************\
 *  File: SNLine.h                                       *
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


#ifndef __PLSCENE_SCENENODE_LINE_H__
#define __PLSCENE_SCENENODE_LINE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color4.h>
#include "PLScene/Scene/SceneNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Line scene node
*/
class SNLine : public SceneNode {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node flags (SceneNode flags extension)
		*/
		enum EFlags {
			No3DPosition = 1<<10,	/**< The line is not placed within 3D. If this flag is set, the node position is in 'screen space' between 0.0 and 1.0. */
			NoDepthTest  = 1<<11	/**< Do not perform a depth test */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneNode::EFlags)
			pl_enum_value(No3DPosition,	"The line is not placed within 3D. If this flag is set, the node position is in 'screen space' between 0.0 and 1.0.")
			pl_enum_value(NoDepthTest,	"Do not perform a depth test")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNLine, "PLScene", PLScene::SceneNode, "Line scene node")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(StartPosition,	PLMath::Vector3,		PLMath::Vector3(0.0f, 0.0f, 0.0f),			ReadWrite,	GetSet,			"Line start position (relative to this node)",				"")
		pl_attribute(EndPosition,	PLMath::Vector3,		PLMath::Vector3(0.0f, 0.0f, 1.0f),			ReadWrite,	GetSet,			"Line end position (relative to this node)",				"")
		pl_attribute(Width,			float,					1.0f,										ReadWrite,	DirectValue,	"Line width (if supported by the the used renderer API)",	"Min='1.0'")
		pl_attribute(Color,			PLGraphics::Color4,		PLGraphics::Color4(1.0f, 1.0f, 1.0f, 1.0f),	ReadWrite,	DirectValue,	"Line color (r/g/b/a)",										"")
		// Overwritten SceneNode variables
		pl_attribute(Flags,			pl_flag_type(EFlags),	0,											ReadWrite,	GetSet,			"Flags",													"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API const PLMath::Vector3 &GetStartPosition() const;
		PLS_API void SetStartPosition(const PLMath::Vector3 &vValue);
		PLS_API const PLMath::Vector3 &GetEndPosition() const;
		PLS_API void SetEndPosition(const PLMath::Vector3 &vValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNLine();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNLine();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMath::Vector3	m_vStartPosition;	/**< Line start position (relative to this node) */
		PLMath::Vector3 m_vEndPosition;		/**< Line end position (relative to this node) */


	//[-------------------------------------------------------]
	//[ Public virtual SceneNode functions                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void DrawSolid(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = nullptr);
		PLS_API virtual void DrawTransparent(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = nullptr);


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNode functions                 ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual void UpdateAABoundingBox();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_LINE_H__
