/*********************************************************\
 *  File: SceneHierarchyNodeItem.h                       *
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


#ifndef __PLSCENE_SCENEHIERARCHYITEM_H__
#define __PLSCENE_SCENEHIERARCHYITEM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class SceneNode;
class SceneHierarchyNode;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene hierarchy node item class
*
*  @remarks
*    A scene hierarchy node item connects scene nodes and hierarchy nodes. One scene node can have
*    multiple hierarchy node items linking them to different hierarchy nodes and one hierarchy node can have
*    multiple hierarchy node items within it linking to different scene nodes.
*/
class SceneHierarchyNodeItem {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SceneHierarchy;
	friend class SceneHierarchyNode;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the scene node this scene hierarchy node item is linked to
		*
		*  @return
		*    The scene node this scene hierarchy node item is linked to, a null pointer on error
		*    (currently not linked to a scene node?)
		*/
		PLS_API SceneNode *GetSceneNode() const;

		/**
		*  @brief
		*    Returns the scene hierarchy node this scene hierarchy node item is attached to
		*
		*  @return
		*    The scene hierarchy node this scene hierarchy node item is attached to, a null pointer on error
		*    (currently not attached to a scene hierarchy node?)
		*/
		PLS_API SceneHierarchyNode *GetHierarchyNode() const;

		/**
		*  @brief
		*    Returns the previous scene hierarchy node item
		*
		*  @return
		*    The previous scene hierarchy node item, a null pointer if there's no previous item
		*/
		PLS_API SceneHierarchyNodeItem *GetPreviousItem() const;

		/**
		*  @brief
		*    Returns the next scene hierarchy node item
		*
		*  @return
		*    The next scene hierarchy node item, a null pointer if there's no next item
		*/
		PLS_API SceneHierarchyNodeItem *GetNextItem() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	// [TODO] How to make this proceted but available for classes like SHKdTreeNode??
	public:
//	private:
		/**
		*  @brief
		*    Constructor
		*/
		PLS_API SceneHierarchyNodeItem();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API ~SceneHierarchyNodeItem();

		/**
		*  @brief
		*    Links this scene hierarchy node item with a scene node
		*
		*  @param[in] cSceneNode
		*    Scene node where link this scene hierarchy node item to
		*
		*  @return
		*    'true' if all went fine, else 'false' (currently already linked?)
		*/
		PLS_API bool Link(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Unlinks this scene hierarchy node item from the scene node
		*
		*  @return
		*    'true' if all went fine, else 'false' (currently not linked?)
		*/
		PLS_API bool Unlink();

		/**
		*  @brief
		*    Attaches this scene hierarchy node item to a scene hierarchy node
		*
		*  @param[in] cSceneHierarchyNode
		*    Scene hierarchy node where to attach this scene hierarchy node item
		*
		*  @return
		*    'true' if all went fine, else 'false' (currently already attached?)
		*/
		PLS_API bool Attach(SceneHierarchyNode &cSceneHierarchyNode);

		/**
		*  @brief
		*    Detaches this scene hierarchy node item from it's scene hierarchy node
		*
		*  @return
		*    'true' if all went fine, else 'false' (currently not attached?)
		*/
		PLS_API bool Detach();

		/**
		*  @brief
		*    Returns a clone of this scene hierarchy node item
		*
		*  @return
		*    A clone of this scene hierarchy node item
		*
		*  @note
		*    - The clone is already linked to the same scene node, but not attached to
		*      any scene hierarchy node
		*/
		PLS_API SceneHierarchyNodeItem &Clone() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Scene node
		SceneNode			   *m_pSceneNode;						/**< Scene node this scene hierarchy node item is linked with, can be a null pointer */
		SceneHierarchyNodeItem *m_pPreviousSceneNodeItem;			/**< Next scene node item, can be a null pointer */
		SceneHierarchyNodeItem *m_pNextSceneNodeItem;				/**< Previous scene node item, can be a null pointer */
		// Scene hierarchy node
		SceneHierarchyNode	   *m_pSceneHierarchyNode;				/**< Scene hierarchy node this scene hierarchy node item is attached to, can be a null pointer */
		SceneHierarchyNodeItem *m_pPreviousSceneHierarchyNodeItem;	/**< Next scene hierarchy node item, can be a null pointer */
		SceneHierarchyNodeItem *m_pNextSceneHierarchyNodeItem;		/**< Previous scene hierarchy node item, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENEHIERARCHYITEM_H__
