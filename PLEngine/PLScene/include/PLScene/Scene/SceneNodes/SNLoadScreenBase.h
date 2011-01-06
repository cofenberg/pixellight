/*********************************************************\
 *  File: SNLoadScreenBase.h                             *
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


#ifndef __PLSCENE_SCENENODE_LOADSCREENBASE_H__
#define __PLSCENE_SCENENODE_LOADSCREENBASE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
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
*    Abstract load screen base scene node
*
*  @remarks
*    This scene node listens to the 'load progress'-event of its parent and visualizes it. If
*    the progress is NOT between 0.0-1.0 the load screen will hide itself.
*/
class SNLoadScreenBase : public SceneNode {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNLoadScreenBase, "PLScene", PLScene::SceneNode, "Abstract load screen base scene node")
		// Overwritten SceneNode variables
		pl_attribute(Flags,	pl_flag_type(EFlags),	NoCulling,	ReadWrite,	GetSet,	"Flags",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNLoadScreenBase();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNLoadScreenBase();

		/**
		*  @brief
		*    Returns the current load progress
		*
		*  @return
		*    The current load progress between 0.0-1.0
		*/
		PLS_API float GetLoadProgress() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node container changed
		*/
		void NotifyContainer();

		/**
		*  @brief
		*    Called on load progress
		*
		*  @param[in] fLoadProgress
		*    Load progress (0.0-1.0)
		*/
		void NotifyLoadProgress(float fLoadProgress);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<>		EventHandlerContainer;
		PLCore::EventHandler<float>	EventHandlerLoadProgress;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		SceneContainer *m_pContainer;		/**< Current parent container, can be a null pointer */
		float			m_fLoadProgress;	/**< Current load progress (0.0-1.0) */


	//[-------------------------------------------------------]
	//[ Public virtual SceneNode functions                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void DrawPost(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = nullptr);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_LOADSCREENBASE_H__
