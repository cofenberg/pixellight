/*********************************************************\
 *  File: SceneHierarchy.cpp                             *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneContainer.h"
#include "PLScene/Scene/SceneHierarchyNode.h"
#include "PLScene/Scene/SceneHierarchyNodeItem.h"
#include "PLScene/Scene/SceneHierarchy.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SceneHierarchy)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the scene context the scene hierarchy is in
*/
SceneContext *SceneHierarchy::GetSceneContext() const
{
	return m_pSceneContainer->GetSceneContext();
}

/**
*  @brief
*    Returns the scene container this scene hierarchy operates on
*/
SceneContainer &SceneHierarchy::GetSceneContainer() const
{
	return *m_pSceneContainer;
}

/**
*  @brief
*    Returns the scene hierarchy root node
*/
SceneHierarchyNode &SceneHierarchy::GetRootNode() const
{
	return *m_pRootNode;
}

/**
*  @brief
*    Initializes the hierarchy
*/
void SceneHierarchy::Init(const Vector3 &vMin, const Vector3 &vMax)
{
	m_pRootNode->m_cAABoundingBox.vMin = vMin;
	m_pRootNode->m_cAABoundingBox.vMax = vMax;
}

/**
*  @brief
*    Returns the maximum allowed level (tree depth)
*/
uint32 SceneHierarchy::GetMaxLevel() const
{
	return m_nMaxLevel;
}

/**
*  @brief
*    Sets the maximum allowed level (tree depth)
*/
void SceneHierarchy::SetMaxLevel(uint32 nMaxLevel)
{
	m_nMaxLevel = nMaxLevel;
}

/**
*  @brief
*    Returns the maximum allowed number of items per scene hierarchy node
*/
uint32 SceneHierarchy::GetMaxNumOfNodeItems() const
{
	return m_nMaxNumOfNodeItems;
}

/**
*  @brief
*    Sets the maximum allowed number of items per scene hierarchy node
*/
void SceneHierarchy::SetMaxNumOfNodeItems(uint32 nMaxNumOfNodeItems)
{
	m_nMaxNumOfNodeItems = nMaxNumOfNodeItems;
}

/**
*  @brief
*    Returns the total number of scene hierarchy nodes (used or currently unused)
*/
uint32 SceneHierarchy::GetTotalNumOfNodes() const
{
	return m_nTotalNumOfNodes;
}

/**
*  @brief
*    Returns the number of currently used scene hierarchy nodes
*/
uint32 SceneHierarchy::GetNumOfNodes() const
{
	return m_nTotalNumOfNodes-m_lstFreeNodes.GetNumOfElements();
}

/**
*  @brief
*    Returns the number of scene nodes within this hierarchy
*/
uint32 SceneHierarchy::GetNumOfSceneNodes() const
{
	return m_nNumOfSceneNodes;
}

/**
*  @brief
*    Draws the hierarchy
*/
void SceneHierarchy::Draw(Renderer &cRenderer, const Color4 &cColor, const Matrix4x4 &mWorldViewProjection, float fLineWidth) const
{
	// Draw the root node
	m_pRootNode->Draw(cRenderer, cColor, mWorldViewProjection, fLineWidth);
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SceneHierarchy::SceneHierarchy() :
	m_pSceneContainer(nullptr),
	m_pRootNode(nullptr),
	m_nTotalNumOfNodes(0),
	m_nNumOfSceneNodes(0),
	m_nMaxLevel(16),
	m_nMaxNumOfNodeItems(16)
{
}

/**
*  @brief
*    Destructor
*/
SceneHierarchy::~SceneHierarchy()
{
	// Destroy the scene hierarchy root node
	delete m_pRootNode;

	// Clear the list of free nodes
	SceneHierarchyNode *pNode = m_lstFreeNodes.Get(0);
	while (pNode) {
		delete pNode;
		m_lstFreeNodes.RemoveAtIndex(0);

		// Next free node, please
		pNode = m_lstFreeNodes.Get(0);
	}
}

/**
*  @brief
*    Adds a scene node
*/
bool SceneHierarchy::AddSceneNode(SceneNode &cSceneNode)
{
	// Check parameter and is the given scene node already within a hierarchy?
	if (cSceneNode.m_pFirstSceneHierarchyNodeItem) {
		// Error!
		return false;
	} else {
		// Add the scene node to this hierarchy
		m_nNumOfSceneNodes++;
		m_pRootNode->AddSceneNode(cSceneNode);

		// Done
		return true;
	}
}

/**
*  @brief
*    Removes a scene node
*/
bool SceneHierarchy::RemoveSceneNode(SceneNode &cSceneNode)
{
	// Check parameter and is the given scene node within a hierarchy?
	if (cSceneNode.m_pFirstSceneHierarchyNodeItem) {
		// Remove the scene node from this hierarchy
		m_nNumOfSceneNodes--;

		// Delete all scene hierarchy node items (the item class will do the rest for us :)
		while (cSceneNode.m_pFirstSceneHierarchyNodeItem)
			delete cSceneNode.m_pFirstSceneHierarchyNodeItem;

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

/**
*  @brief
*    Refreshes a scene node
*/
bool SceneHierarchy::RefreshSceneNode(SceneNode &cSceneNode)
{
	// Is the given scene node within a hierarchy?
	const SceneHierarchyNodeItem *pNodeItem = cSceneNode.m_pFirstSceneHierarchyNodeItem;
	if (pNodeItem) {
		SceneHierarchyNode *pNode = pNodeItem->m_pSceneHierarchyNode;
		if (pNode) {
			// If the scene node is still within the same hierarchy  node we do not need to refresh anything
			const AABoundingBox &cSceneNodeAABox = cSceneNode.GetContainerAABoundingBox();
			const AABoundingBox *pNodeAABox      = &pNode->m_cAABoundingBox;
			if (cSceneNodeAABox.vMin.x < pNodeAABox->vMin.x || cSceneNodeAABox.vMin.y < pNodeAABox->vMin.y ||
				cSceneNodeAABox.vMin.z < pNodeAABox->vMin.z || cSceneNodeAABox.vMax.x > pNodeAABox->vMax.x ||
				cSceneNodeAABox.vMax.y > pNodeAABox->vMax.y || cSceneNodeAABox.vMax.z > pNodeAABox->vMax.z) {
				// Change to the parent hierarchy node until we have found one which can contain the whole scene node
				// (or break if the root hierarchy node was found :)
				while ((pNode->m_pParentNode != nullptr) &&
					   (cSceneNodeAABox.vMin.x < pNodeAABox->vMin.x || cSceneNodeAABox.vMin.y < pNodeAABox->vMin.y ||
						cSceneNodeAABox.vMin.z < pNodeAABox->vMin.z || cSceneNodeAABox.vMax.x > pNodeAABox->vMax.x ||
						cSceneNodeAABox.vMax.y > pNodeAABox->vMax.y || cSceneNodeAABox.vMax.z > pNodeAABox->vMax.z)) {
					pNode      = pNode->m_pParentNode;
					pNodeAABox = &pNode->m_cAABoundingBox;
				}

				// Detach the scene node from the previous hierarchy node (the item class will do the rest for us :)
				while (cSceneNode.m_pFirstSceneHierarchyNodeItem)
					delete cSceneNode.m_pFirstSceneHierarchyNodeItem;

				// Attach the scene node to the new found hierarchy node. It's also possible to add the scene node to the
				// scene hierarchy root node, but this would be slower...
				pNode->AddSceneNode(cSceneNode);
			}

			// Done
			return true;
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
