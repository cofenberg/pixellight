/*********************************************************\
 *  File: SNLineGrid.h                                   *
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


#ifndef __PLSCENE_SCENENODE_LINEGRID_H__
#define __PLSCENE_SCENENODE_LINEGRID_H__
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
*    Line grid scene node on the nodes local space x/y-plane
*/
class SNLineGrid : public SceneNode {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node flags (SceneNode flags extension)
		*/
		enum EFlags {
			NoDepthTest  = 1<<10,	/**< Do not perform a depth test */
			NoMainLines  = 1<<11,	/**< Do not draw the main lines */
			NoMinorLines = 1<<12	/**< Do not draw the minor lines */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneNode::EFlags)
			pl_enum_value(NoDepthTest,	"Do not perform a depth test")
			pl_enum_value(NoMainLines,	"Do not draw the main lines")
			pl_enum_value(NoMinorLines,	"Do not draw the minor lines")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNLineGrid, "PLScene", PLScene::SceneNode, "Line grid scene node on the nodes local space x/y-plane")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(NumOfXLines,	PLGeneral::uint32,		5,												ReadWrite,	DirectValue,	"Number of lines along each +/- x axis",								"")
		pl_attribute(NumOfYLines,	PLGeneral::uint32,		5,												ReadWrite,	DirectValue,	"Number of lines along each +/- y axis",								"")
		pl_attribute(MainWidth,		float,					1.0f,											ReadWrite,	DirectValue,	"Main lines width (if supported by the the used renderer API)",			"Min='1.0'")
		pl_attribute(MainColor,		PLGraphics::Color4,		PLGraphics::Color4(0.1f, 0.1f, 0.1f, 1.0f),		ReadWrite,	DirectValue,	"Main lines color (r/g/b/a)",											"")
		pl_attribute(MinorWidth,	float,					1.0f,											ReadWrite,	DirectValue,	"Minor lines width (if supported by the the used renderer API)",		"Min='1.0'")
		pl_attribute(MinorColor,	PLGraphics::Color4,		PLGraphics::Color4(0.55f, 0.55f, 0.55f, 1.0f),	ReadWrite,	DirectValue,	"Minor lines color (r/g/b/a)",											"")
		// Overwritten SceneNode variables
		pl_attribute(Flags,			pl_flag_type(EFlags),	0,												ReadWrite,	GetSet,			"Flags",																"")
		pl_attribute(AABBMin,		PLMath::Vector3,		PLMath::Vector3(-0.5f, -0.5f, -0.5f),			ReadWrite,	GetSet,			"Minimum position of the 'scene node space' axis aligned bounding box",	"")
		pl_attribute(AABBMax,		PLMath::Vector3,		PLMath::Vector3( 0.5f,  0.5f,  0.5f),			ReadWrite,	GetSet,			"Maximum position of the 'scene node space' axis aligned bounding box",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNLineGrid();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNLineGrid();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Draws the grid
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cVisNode
		*    The current visibility node of this scene node
		*/
		void DrawGrid(PLRenderer::Renderer &cRenderer, const VisNode &cVisNode);


	//[-------------------------------------------------------]
	//[ Public virtual SceneNode functions                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void DrawSolid(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = nullptr);
		PLS_API virtual void DrawTransparent(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = nullptr);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_LINEGRID_H__
