/*********************************************************\
 *  File: SNSystem.h                                     *
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


#ifndef __SPARK_PL_SNSPARK_H__
#define __SPARK_PL_SNSPARK_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneNode.h>
#include "SPARK_PL/SPARK_PL.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace SPK {
	class System;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract SPARK particle system scene node base class
*/
class SNSystem : public PLScene::SceneNode {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node flags (PLScene::SceneNode flags extension)
		*/
		enum EFlags {
			UpdateInvisible = 1<<10,	/**< Do also update the particle system if it's currently not visible */
			NoAutomaticAABB = 1<<11		/**< Do not automatically update the axis aligned bounding box */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneNode::EFlags)
			pl_enum_value(UpdateInvisible,	"Do also update the particle system if it's currently not visible")
			pl_enum_value(NoAutomaticAABB,	"Do not automatically update the axis aligned bounding box")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(SPARK_PL_RTTI_EXPORT, SNSystem, "SPARK_PL", PLScene::SceneNode, "Abstract SPARK particle system scene node base class")
		// Overwritten PLScene::SceneNode variables
		pl_attribute(Flags,	pl_flag_type(EFlags),	0,	ReadWrite,	GetSet,	"Flags",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		SPARK_PL_API SNSystem();

		/**
		*  @brief
		*    Destructor
		*/
		SPARK_PL_API virtual ~SNSystem();


	//[-------------------------------------------------------]
	//[ Public virtual PLScene::SceneNode functions           ]
	//[-------------------------------------------------------]
	public:
		SPARK_PL_API virtual void DrawTransparent(PLRenderer::Renderer &cRenderer, const PLScene::VisNode *pVisNode = nullptr);


	//[-------------------------------------------------------]
	//[ Protected virtual SNSystem functions                  ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called just before the particle system is updated
		*
		*  @note
		*    - The default implementation is empty
		*/
		SPARK_PL_API virtual void Update();


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneNode functions          ]
	//[-------------------------------------------------------]
	private:
		virtual void OnActivate(bool bActivate);
		virtual void UpdateAABoundingBox();
		virtual void OnAddedToVisibilityTree(PLScene::VisNode &cVisNode);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void NotifyUpdate();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerUpdate;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		SPK::System	*m_pParticleSystem;	/**< SPARK particle system, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool m_bUpdate;	/**< Perform an update the next time? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


#endif // __SPARK_PL_SNSPARK_H__
