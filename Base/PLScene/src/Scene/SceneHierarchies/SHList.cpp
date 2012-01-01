/*********************************************************\
 *  File: SHList.cpp                                     *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneHierarchies/SHList.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SHList)




//[-------------------------------------------------------]
//[ SHList implementation                                 ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SHList::SHList()
{
	m_pRootNode = new SHListNode(*this);
}


//[-------------------------------------------------------]
//[ Private virtual SceneHierarchy functions              ]
//[-------------------------------------------------------]
SceneHierarchyNode &SHList::CreateNode()
{
	return *(new SHListNode(*this));
}




//[-------------------------------------------------------]
//[ SHListNode implementation                             ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Public virtual SceneHierarchyNode functions           ]
//[-------------------------------------------------------]
void SHListNode::Touch(bool bRecursive)
{
	// Nothing to do in here :)
}

uint32 SHListNode::GetNumOfNodes() const
{
	// Because this is just a simple list, there are ONLY items in here!
	return 0;
}

SceneHierarchyNode *SHListNode::GetNode(uint32 nIndex) const
{
	// Because this is just a simple list, there are ONLY items in here!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SHListNode::SHListNode(SceneHierarchy &cHierarchy) : SceneHierarchyNode(cHierarchy)
{
	// Empty
}

/**
*  @brief
*    Destructor
*/
SHListNode::~SHListNode()
{
	// This implementation is that booorrring! ;-)
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
