/*********************************************************\
 *  File: VisManager.cpp                                 *
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
#include <PLCore/Log/Log.h>
#include "PLScene/Scene/SceneNodeHandler.h"
#include "PLScene/Visibility/VisNode.h"
#include "PLScene/Visibility/VisManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLScene {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Resource cleanup
*/
void VisManager::Cleanup()
{
	// Destroy all nodes
	Iterator<VisNode*> cIterator = m_lstFreeNodes.GetIterator();
	while (cIterator.HasNext())
		delete cIterator.Next();
	m_lstFreeNodes.Clear();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
VisManager::VisManager()
{
	PL_LOG(Debug, "Create visibility manager")
}

/**
*  @brief
*    Destructor
*/
VisManager::~VisManager()
{
	PL_LOG(Debug, "Destroy visibility manager")
	Cleanup();
}

/**
*  @brief
*    Returns a free visibility node
*/
VisNode &VisManager::GetFreeNode()
{
	if (m_lstFreeNodes.IsEmpty())
		return *(new VisNode());
	else {
		VisNode *pNode = m_lstFreeNodes.Get(0);
		m_lstFreeNodes.RemoveAtIndex(0);
		return *pNode;
	}
}

/**
*  @brief
*    Frees a visibility node
*/
void VisManager::FreeNode(VisNode &cNode)
{
	m_lstFreeNodes.Add(&cNode);
	cNode.m_pSceneNodeHandler->SetElement();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
