/*********************************************************\
 *  File: SHKdTree.h                                     *
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


#ifndef __PLSCENE_SCENEHIERARCHY_KDTREE_H__
#define __PLSCENE_SCENEHIERARCHY_KDTREE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneHierarchy.h"
#include "PLScene/Scene/SceneHierarchyNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Kd tree scene hierarchy (axis aligned binary tree)
*
*  @remarks
*    A node has two children. The node can be either an interior node (i.e., left and
*    right child) or a leaf node, which holds the actual scene nodes.
*/
class SHKdTree : public SceneHierarchy {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SHKdTree, "PLScene", PLScene::SceneHierarchy, "Kd tree scene hierarchy (axis aligned binary tree)")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SHKdTree();


	//[-------------------------------------------------------]
	//[ Private virtual SceneHierarchy functions              ]
	//[-------------------------------------------------------]
	private:
		virtual SceneHierarchyNode &CreateNode();


};

/**
*  @brief
*    Kd tree scene hierarchy node class
*/
class SHKdTreeNode : public SceneHierarchyNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SHKdTree;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cHierarchy
		*    The owner hierarchy
		*/
		SHKdTreeNode(SceneHierarchy &cHierarchy);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SHKdTreeNode();

		/**
		*  @brief
		*    Merges the items of the scene hierarchy child nodes to this nodes if required
		*/
		void Merge();

		/**
		*  @brief
		*    Splits this scene hierarchy node
		*/
		void Split();


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Split axis
		*/
		enum EAxis {
			AxisX = 0,
			AxisY = 1,
			AxisZ = 2,
			Leaf  = 3
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		SHKdTreeNode *m_pLeftNode;		/**< Left scene hierarchy node, can be NULL */
		SHKdTreeNode *m_pRightNode;		/**< Right scene hierarchy node, can be NULL */
		EAxis		  m_nSplitAxis;		/**< Split axis */
		float		  m_fSplitValue;	/**< Split value */


	//[-------------------------------------------------------]
	//[ Public virtual SceneHierarchyNode functions           ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void Touch(bool bRecursive = false);
		PLS_API virtual PLGeneral::uint32 GetNumOfNodes() const;
		PLS_API virtual SceneHierarchyNode *GetNode(PLGeneral::uint32 nIndex) const;


	//[-------------------------------------------------------]
	//[ Private virtual SceneHierarchyNode functions          ]
	//[-------------------------------------------------------]
	private:
		virtual void Init();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENEHIERARCHY_KDTREE_H__
