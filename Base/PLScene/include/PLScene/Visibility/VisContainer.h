/*********************************************************\
 *  File: VisContainer.h                                 *
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


#ifndef __PLSCENE_VISIBILITY_VISCONTAINER_H__
#define __PLSCENE_VISIBILITY_VISCONTAINER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/Pool.h>
#include <PLCore/Base/Event/EventHandler.h>
#include <PLMath/Rectangle.h>
#include "PLScene/Visibility/VisNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class SQCull;
class SceneNode;
class VisPortal;
class VisManager;
class SceneQueryHandler;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Container of the visibility tree
*/
class VisContainer : public VisNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SQCull;
	friend class VisPortal;


	//[-------------------------------------------------------]
	//[ Public structures                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Projection information
		*/
		struct Projection {
			PLMath::Rectangle cRectangle;	/**< Screen space rectangle */
			float			  fZNear;		/**< Near depth value */
			float			  fZFar;		/**< Far depth value */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the cull scene query of this visibility container
		*
		*  @return
		*    The cull scene query of this visibility container, a null pointer if there's no such query
		*/
		PLS_API const SQCull *GetCullQuery() const;

		/**
		*  @brief
		*    Returns the list of visibililty nodes
		*
		*  @return
		*    List of visibililty nodes
		*/
		PLS_API const PLCore::Pool<VisNode*> &GetVisNodes() const;

		/**
		*  @brief
		*    Returns projection information
		*
		*  @return
		*    Projection information
		*/
		PLS_API const Projection &GetProjection() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pParent
		*    The parent visibility node, a null pointer if this is the root
		*/
		VisContainer(VisNode *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~VisContainer();

		/**
		*  @brief
		*    Adds a scene node to this visibility container
		*
		*  @param[in] cSceneNode
		*    Scene node to add
		*  @param[in] fSquaredDistanceToCamera
		*    Squared distance of the given scene node to the camera
		*
		*  @return
		*    The added visibility node linking to the given scene node, a null pointer on error
		*/
		VisNode *AddSceneNode(SceneNode &cSceneNode, float fSquaredDistanceToCamera);

		/**
		*  @brief
		*    Frees all visibility nodes
		*/
		void FreeNodes();

		/**
		*  @brief
		*    Called when the scene node assigned with this visibililty container was destroyed
		*/
		void OnDestroy();

		/**
		*  @brief
		*    Returns the visibility manager
		*
		*  @return
		*    The visibility manager, a null pointer on error
		*/
		VisManager *GetVisManager() const;


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerDestroy;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		SceneQueryHandler							   *m_pQueryHandler;	/**< The cull scene query of this visibility container (always valid!) */
		PLCore::Pool<VisNode*>							m_lstNodes;			/**< List of currently used visibililty nodes */
		PLCore::HashMap<PLCore::String, VisContainer*>  m_mapContainers;	/**< Map with all child visibilty containers of this container */
		PLCore::HashMap<PLCore::String, VisPortal*>	    m_mapPortals;		/**< Map with all visibilty portals of this container */
		Projection										m_sProjection;		/**< Projection information */


	//[-------------------------------------------------------]
	//[ Public virtual VisNode functions                      ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual bool IsContainer() const;
		PLS_API virtual bool IsCell() const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_VISIBILITY_VISCONTAINER_H__
