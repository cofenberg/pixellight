/*********************************************************\
 *  File: SHList.h                                       *
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


#ifndef __PLSCENE_SCENEHIERARCHY_LIST_H__
#define __PLSCENE_SCENEHIERARCHY_LIST_H__
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
*    Scene hierarchy which is in fact a simple list (a special case of a tree :)
*
*  @note
*    - Try to avoid using this hierarchy type for larger scenes because it's quite inefficient!
*    - Internally this 'hierarchy' will use the scene container nodes directly
*      (therefore no extra reference to the scene nodes required :)
*/
class SHList : public SceneHierarchy {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SHList, "PLScene", PLScene::SceneHierarchy, "Scene hierarchy which is in fact a simple list (a special case of a tree :)")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SHList();


	//[-------------------------------------------------------]
	//[ Private virtual SceneHierarchy functions              ]
	//[-------------------------------------------------------]
	private:
		virtual SceneHierarchyNode &CreateNode();


};

/**
*  @brief
*    List scene hierarchy node class
*/
class SHListNode : public SceneHierarchyNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SHList;


	//[-------------------------------------------------------]
	//[ Public virtual SceneHierarchyNode functions           ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void Touch(bool bRecursive = false);
		PLS_API virtual PLGeneral::uint32 GetNumOfNodes() const;
		PLS_API virtual SceneHierarchyNode *GetNode(PLGeneral::uint32 nIndex) const;


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
		SHListNode(SceneHierarchy &cHierarchy);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SHListNode();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENEHIERARCHY_LIST_H__
