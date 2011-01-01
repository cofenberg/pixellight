/*********************************************************\
 *  File: SceneHierarchyNode.h                           *
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


#ifndef __PLSCENE_SCENEHIERARCHYNODE_H__
#define __PLSCENE_SCENEHIERARCHYNODE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/AABoundingBox.h>
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGraphics {
	class Color4;
}
namespace PLMath {
	class Line;
	class Plane;
	class PlaneSet;
}
namespace PLScene {
	class SceneNode;
	class SceneContext;
	class SceneHierarchy;
	class SceneHierarchyNodeItem;
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
*    Abstract scene hierarchy node class
*
*  @remarks
*    A scene hierarchy node can contain multiple scene hierarchy node items.
*/
class SceneHierarchyNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SceneHierarchy;
	friend class SceneHierarchyNodeItem;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the scene context the scene hierarchy node is in
		*
		*  @return
		*    The scene context the scene hierarchy node is in, can but shouldn't be NULL
		*/
		PLS_API SceneContext *GetSceneContext() const;

		/**
		*  @brief
		*    Returns the owner scene hierarchy
		*
		*  @return
		*    The owner scene hierarchy (NEVER NULL!)
		*/
		PLS_API SceneHierarchy *GetHierarchy() const;

		/**
		*  @brief
		*    Returns the parent scene hierarchy node
		*
		*  @return
		*    The parent scene hierarchy node, if NULL, this is the root
		*/
		PLS_API SceneHierarchyNode *GetParentNode() const;

		/**
		*  @brief
		*    Returns the unique ID of the scene hierarchy node
		*
		*  @return
		*    The unique ID of the scene hierarchy node
		*
		*  @remarks
		*    Some scene queries may need to hold some extra information per scene hierarchy node.
		*    In such cases, an unique node ID is quite useful to manage this information within for
		*    instance an array. SQCull for example may cache scene hierarchy node visibility information
		*    from the previous frame for the coherent hierarchical occlusion culling algorithm. In order
		*    to keep this unique node ID system working, ONLY SceneHierarchy::GetFreeNode() and
		*    SceneHierarchy::FreeNode() are used during runtime instead of new/delete. Have a look at
		*    the SceneHierarchy::GetFreeNode() documentation for more information about this.
		*/
		PLS_API PLGeneral::uint32 GetID() const;

		/**
		*  @brief
		*    Returns the level/tree depth of the scene hierarchy node
		*
		*  @return
		*    The level/tree depth of the scene hierarchy node
		*/
		PLS_API PLGeneral::uint8 GetLevel() const;

		/**
		*  @brief
		*    Returns the axis aligned bounding box of the scene hierarchy node
		*
		*  @return
		*    The axis aligned bounding box of the scene hierarchy node
		*/
		PLS_API const PLMath::AABoundingBox &GetAABoundingBox() const;

		/**
		*  @brief
		*    Checks whether the scene hierarchy node volume is intersecting the given line
		*
		*  @param[in] cLine
		*    Line to check against
		*
		*  @return
		*    'false' if the scene hierarchy node volume is not intersecting the given line, else 'true'
		*/
		PLS_API bool CheckLine(const PLMath::Line &cLine) const;

		/**
		*  @brief
		*    Checks whether the scene hierarchy node volume is within the given plane set
		*
		*  @param[in]  cPlaneSet
		*    Plane set to check against
		*  @param[out] pnOutClipMask
		*    If not NULL, this clip mask will receive the intersection state of a
		*    maximum number of 32 planes if the box intersects the plane set.
		*
		*  @return
		*    'false' if the scene hierarchy node volume is not within the given plane set, else 'true'
		*/
		PLS_API bool CheckPlaneSet(const PLMath::PlaneSet &cPlaneSet, PLGeneral::uint32 *pnOutClipMask = NULL) const;

		/**
		*  @brief
		*    Returns the side of the plane the scene hierarchy node volume is on
		*
		*  @param[in] cPlane
		*    Plane to check against
		*
		*  @return
		*    '-1' if of scene hierarchy node volume is behind the plane, '0' if it is
		*    intersecting the plane, '1' if the volume is in front of the plane
		*/
		PLS_API char GetPlaneSide(const PLMath::Plane &cPlane) const;

		/**
		*  @brief
		*    Returns the shortest distance from a given point to the scene hierarchy node volume
		*
		*  @param[in] vPoint
		*    Point to get the shortest distance from
		*
		*  @return
		*    Shortest distance (squared) from the given point to the scene hierarchy node volume
		*/
		PLS_API float GetShortestDistance(const PLMath::Vector3 &vPoint) const;

		/**
		*  @brief
		*    Returns the number of scene hierarchy node items
		*
		*  @return
		*    The number of scene hierarchy node items
		*/
		PLS_API PLGeneral::uint32 GetNumOfItems() const;

		/**
		*  @brief
		*    Returns the first scene hierarchy node item
		*
		*  @return
		*    The first scene hierarchy node item, NULL if there are no items
		*
		*  @note
		*    - Use SceneHierarchyNodeItem::GetPreviousItem()/SceneHierarchyNodeItem::GetNextItem()
		*      get the previous/next scene hierarchy node item
		*/
		PLS_API SceneHierarchyNodeItem *GetFirstItem() const;


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Touches the scene hierarchy scene node
		*
		*  @param[in] bRecursive
		*    Touch recursive?
		*
		*  @remarks
		*    Scene node distribution (splitt/merge) within the scene hierarchy is only performed if this function
		*    is called. If during for instance a visibility determination a scene hierarchy node is used the first
		*    time during this process, one should call this 'touch' function to inform the scene hierarchy that this
		*    scene hierarchy node is going to be used. This function will split a scene hierarchy node if certain conditions
		*    like a maximum number of items per scene hierarchy node are given. If other conditions are given a merge operation
		*    is performed which 'combines' scene hierarchy nodes instead of splitting them. As result of this function,
		*    normally only the scene hierarchy parts which are currently used will be updated. ("lazy evaluation" :)
		*    If 'bRecursive' is set to true, all child nodes are touched to - but this may only be useful for instance when
		*    initializing the scene hierarchy.
		*/
		virtual void Touch(bool bRecursive = false) = 0;

		/**
		*  @brief
		*    Returns the number of child scene hierarchy nodes
		*
		*  @return
		*    The number of child scene hierarchy nodes
		*/
		virtual PLGeneral::uint32 GetNumOfNodes() const = 0;

		/**
		*  @brief
		*    Returns a child scene hierarchy node
		*
		*  @param[in] nIndex
		*    Index of the requested child scene hierarchy node
		*
		*  @return
		*    The requested child scene hierarchy node, NULL on error
		*/
		virtual SceneHierarchyNode *GetNode(PLGeneral::uint32 nIndex) const = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cHierarchy
		*    The owner hierarchy
		*/
		PLS_API SceneHierarchyNode(SceneHierarchy &cHierarchy);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SceneHierarchyNode();

		/**
		*  @brief
		*    Returns a free scene hierarchy node
		*
		*  @return
		*    Free scene hierarchy node
		*
		*  @remarks
		*    This function will return a free scene hierarchy node. If there are no free nodes avaiable,
		*    a new one is created. After a node is no longer required it is put into the list of free nodes
		*    by using FreeNode() instead of destroying it. This way, frequently creation and destruction of
		*    nodes is avoided and the management of the unique node ID's becomes quite simple.
		*    See SceneHierarchyNode::GetID() for more information about the unique node ID's.
		*/
		PLS_API SceneHierarchyNode &GetFreeNode();

		/**
		*  @brief
		*    Marks a scene hierarchy node as free
		*
		*  @param[in] cNode
		*    Scene hierarchy node to mark as free
		*
		*  @see
		*    - GetFreeNode()
		*/
		PLS_API void FreeNode(SceneHierarchyNode &cNode);


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Initializes the scene hierarchy node variables
		*/
		PLS_API virtual void Init();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Adds a scene node to this scene hierarchy node
		*
		*  @param[in] cSceneNode
		*    Scene node to add
		*/
		void AddSceneNode(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Deletes all items attached to this scene hierarchy node
		*/
		void DeleteItems();

		/**
		*  @brief
		*    Draws the hierarchy node (for debugging)
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
		void Draw(PLRenderer::Renderer &cRenderer, const PLGraphics::Color4 &cColor, const PLMath::Matrix4x4 &mWorldViewProjection, float fLineWidth = 1.0f) const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		SceneHierarchy		   *m_pHierarchy;		/**< Owner hierarchy (always valid!) */
		SceneHierarchyNode	   *m_pParentNode;		/**< Parent scene hierarchy node, can be NULL */
		PLGeneral::uint32		m_nID;				/**< The unique ID of the scene hierarchy node */
		PLGeneral::uint8		m_nLevel;			/**< Scene hierarchy node level */
		PLMath::AABoundingBox   m_cAABoundingBox;	/**< Axis aligned bounding box of this scene hierarchy node */
		PLGeneral::uint32	    m_nNumOfItems;		/**< The number of scene hierarchy node items attached to this scene hierarchy node */
		SceneHierarchyNodeItem *m_pFirstItem;		/**< The first scene hierarchy node item, can be NULL */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENEHIERARCHYNODE_H__
