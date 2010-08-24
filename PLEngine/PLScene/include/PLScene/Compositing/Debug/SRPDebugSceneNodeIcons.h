/*********************************************************\
 *  File: SRPDebugSceneNodeIcons.h                       *
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


#ifndef __PLSCENE_COMPOSITING_DEBUG_SCENENODEICONS_H__
#define __PLSCENE_COMPOSITING_DEBUG_SCENENODEICONS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Compositing/Debug/SRPDebug.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class VisNode;
class SceneNode;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene renderer pass drawing just simple scene node icons
*/
class SRPDebugSceneNodeIcons : public SRPDebug {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SRPDebugSceneNodeIcons, "PLScene", PLScene::SRPDebug, "Abstract scene renderer pass drawing just simple scene node icons")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(Size,				float,	30.0f,	ReadWrite,	DirectValue,	"Icon size",																				"Min='1.0'")
		pl_attribute(MaxDrawDistance,	float,	20.0f,	ReadWrite,	DirectValue,	"Maximum draw distance of icons to the camera, if less or equal 0, there's no limitation",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SRPDebugSceneNodeIcons();

		/**
		*  @brief
		*    Destructur
		*/
		PLS_API virtual ~SRPDebugSceneNodeIcons();


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
		void DrawRec(PLRenderer::Renderer &cRenderer, const SQCull &cCullQuery) const;

		/**
		*  @brief
		*    Draws a scene node icon
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cCullQuery
		*    Cull query to use
		*  @param[in] cVisNode
		*    Visibility node to use
		*  @param[in] cSceneNode
		*    Scene node to use
		*/
		void DrawIcon(PLRenderer::Renderer &cRenderer, const SQCull &cCullQuery, const VisNode &cVisNode, const SceneNode &cSceneNode) const;


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneRendererPass functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void Draw(PLRenderer::Renderer &cRenderer, const SQCull &cCullQuery);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_COMPOSITING_DEBUG_SCENENODEICONS_H__
