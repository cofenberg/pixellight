/*********************************************************\
 *  File: SceneHierarchy.h                               *
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


#ifndef __PLSCENE_SCENEHIERARCHY_H__
#define __PLSCENE_SCENEHIERARCHY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/Pool.h>
#include <PLCore/Base/Object.h>
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class Vector3;
	class Matrix4x4;
}
namespace PLGraphics {
	class Color4;
}
namespace PLRenderer {
	class Renderer;
}
namespace PLScene {
	class SceneNode;
	class SceneContext;
	class SceneContainer;
	class SceneHierarchyNode;
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
*    Abstract scene hierarchy class (spatial database, Bounding Volume Hierarchies (BVHs))
*
*  @remarks
*    Manages scene nodes of one or more scene containers within a hierarchy.
*/
class SceneHierarchy : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SceneNode;
	friend class SceneContainer;
	friend class SceneHierarchyNode;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SceneHierarchy, "PLScene", PLCore::Object, "Abstract scene hierarchy class (spatial database, Bounding Volume Hierarchies (BVHs))")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the scene context the scene hierarchy is in
		*
		*  @return
		*    The scene context the scene hierarchy is in, can but shouldn't be a null pointer
		*/
		PLS_API SceneContext *GetSceneContext() const;

		/**
		*  @brief
		*    Returns the scene container this scene hierarchy operates on
		*
		*  @return
		*    The scene container this scene hierarchy operates on
		*/
		PLS_API SceneContainer &GetSceneContainer() const;

		/**
		*  @brief
		*    Returns the scene hierarchy root node
		*
		*  @return
		*    The scene hierarchy root node
		*/
		PLS_API SceneHierarchyNode &GetRootNode() const;

		/**
		*  @brief
		*    Initializes the hierarchy
		*
		*  @param[in] vMin
		*    Minimum axis aligned bounding box value
		*  @param[in] vMax
		*    Maximum axis aligned bounding box value
		*
		*  @note
		*    - Call this function before you add any scene nodes
		*/
		PLS_API void Init(const PLMath::Vector3 &vMin, const PLMath::Vector3 &vMax);

		/**
		*  @brief
		*    Returns the maximum allowed level (tree depth)
		*
		*  @return
		*    The maximum allowed level
		*/
		PLS_API PLGeneral::uint32 GetMaxLevel() const;

		/**
		*  @brief
		*    Sets the maximum allowed level (tree depth)
		*
		*  @param[in] nMaxLevel
		*    The maximum allowed level
		*/
		PLS_API void SetMaxLevel(PLGeneral::uint32 nMaxLevel = 16);

		/**
		*  @brief
		*    Returns the maximum allowed number of items per scene hierarchy node
		*
		*  @return
		*    The maximum allowed number of items per scene hierarchy node
		*/
		PLS_API PLGeneral::uint32 GetMaxNumOfNodeItems() const;

		/**
		*  @brief
		*    Sets the maximum allowed number of items per scene hierarchy node
		*
		*  @param[in] nMaxNumOfNodeItems
		*    The maximum allowed number of items per scene hierarchy node
		*/
		PLS_API void SetMaxNumOfNodeItems(PLGeneral::uint32 nMaxNumOfNodeItems = 16);

		/**
		*  @brief
		*    Returns the total number of scene hierarchy nodes (used or currently unused)
		*
		*  @return
		*    Total number of scene hierarchy nodes
		*/
		PLS_API PLGeneral::uint32 GetTotalNumOfNodes() const;

		/**
		*  @brief
		*    Returns the number of currently used scene hierarchy nodes
		*
		*  @return
		*    Total number of currently used scene hierarchy nodes
		*/
		PLS_API PLGeneral::uint32 GetNumOfNodes() const;

		/**
		*  @brief
		*    Returns the number of scene nodes within this hierarchy
		*
		*  @return
		*    The number of scene nodes within this hierarchy
		*/
		PLS_API PLGeneral::uint32 GetNumOfSceneNodes() const;

		/**
		*  @brief
		*    Draws the hierarchy
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cColor
		*    Color to use
		*  @param[in] mWorldViewProjection
		*    World view projection matrix to use
		*  @param[in] fLineWidth
		*    Line width
		*/
		PLS_API void Draw(PLRenderer::Renderer &cRenderer, const PLGraphics::Color4 &cColor, const PLMath::Matrix4x4 &mWorldViewProjection, float fLineWidth = 1.0f) const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		PLS_API SceneHierarchy();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SceneHierarchy();

		/**
		*  @brief
		*    Adds a scene node
		*
		*  @param[in] cSceneNode
		*    Scene node to add
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*    (maybe the given scene node is already within a hierarchy)
		*/
		PLS_API bool AddSceneNode(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Removes a scene node
		*
		*  @param[in] cSceneNode
		*    Scene node to remove
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLS_API bool RemoveSceneNode(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Refreshs a scene node
		*
		*  @param[in] cSceneNode
		*    Scene node to refresh
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*    (maybe the given scene node is within no hierarchy)
		*/
		PLS_API bool RefreshSceneNode(SceneNode &cSceneNode);


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Creates a hierarchy node
		*
		*  @return
		*    The created scene hierarchy node
		*/
		virtual SceneHierarchyNode &CreateNode() = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		SceneContainer	   *m_pSceneContainer;		/**< Scene container this scene hierarchy node operates on (NEVER a null pointer!) */
		SceneHierarchyNode *m_pRootNode;			/**< Scene hierarchy root node (NEVER a null pointer!) */
		PLGeneral::uint32   m_nTotalNumOfNodes;		/**< Total number of scene hierarchy nodes */
		PLGeneral::uint32   m_nNumOfSceneNodes;		/**< The number of scene nodes within this hierarchy */
		PLGeneral::uint32	m_nMaxLevel;			/**< Maximum allowed level (tree depth) */
		PLGeneral::uint32	m_nMaxNumOfNodeItems;	/**< Maximum allowed number of items per scene hierarchy node */

		/** List of currently unused scene hierarchy nodes */
		PLGeneral::Pool<SceneHierarchyNode*> m_lstFreeNodes;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENEHIERARCHY_H__
