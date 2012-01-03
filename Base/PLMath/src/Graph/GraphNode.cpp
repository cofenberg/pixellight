/*********************************************************\
 *  File: GraphNode.cpp                                  *
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
#include "PLMath/Graph/GraphNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLMath {


//[-------------------------------------------------------]
//[ Main functions                                        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
GraphNode::GraphNode(const String &sName, ElementManager<GraphNode> *pManager) : Element<GraphNode>(sName, pManager)
{
}

/**
*  @brief
*    Constructor
*/
GraphNode::GraphNode(GraphNode &cSource)
{
	// Copy data
	*this = cSource;
}

/**
*  @brief
*    Destructor
*/
GraphNode::~GraphNode()
{
	ClearNeighbours();
}


//[-------------------------------------------------------]
//[ Neighbours                                            ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the number of neighbours
*/
uint32 GraphNode::GetNumOfNeighbours() const
{
	return m_lstNeighbours.GetNumOfElements();
}

/**
*  @brief
*    Clears all neighbour connectivity
*/
void GraphNode::ClearNeighbours()
{
	{ // Update neighbour connections
		Iterator<GraphNode*> cIterator = m_lstIsNeighbourFrom.GetIterator();
		while (cIterator.HasNext()) {
			// Remove this node from the neighbours connectivity list
			cIterator.Next()->RemoveNeighbour(*this);
		}
	}
	m_lstIsNeighbourFrom.Clear();

	{ // Clear neighbours
		Iterator<Neighbour*> cIterator = m_lstNeighbours.GetIterator();
		while (cIterator.HasNext()) {
			Neighbour *pNN = cIterator.Next();
			pNN->pNode->m_lstIsNeighbourFrom.Remove(this);
			delete pNN;
		}
	}
	m_lstNeighbours.Clear();
}

/**
*  @brief
*    Returns whether a node is a neighbour of this node or not
*/
bool GraphNode::IsNeighbour(const GraphNode &cNode) const
{
	// Check whether the given node is a neighbour of this node or not
	Iterator<Neighbour*> cIterator = m_lstNeighbours.GetIterator();
	while (cIterator.HasNext()) {
		if (cIterator.Next()->pNode == &cNode) {
			// The given node is a neighbour of this node
			return true;
		}
	}

	// The given node is no neighbour of this node
	return false;
}

/**
*  @brief
*    Returns a neighbour
*/
const GraphNode *GraphNode::GetNeighbour(uint32 nNeighbour) const
{
	const Neighbour *pNeighbour = m_lstNeighbours[nNeighbour];
	return pNeighbour ? pNeighbour->pNode : nullptr;
}

/**
*  @brief
*    Returns a neighbour
*/
GraphNode *GraphNode::GetNeighbour(uint32 nNeighbour)
{
	Neighbour *pNeighbour = m_lstNeighbours[nNeighbour];
	return pNeighbour ? pNeighbour->pNode : nullptr;
}

/**
*  @brief
*    Returns the distance to a neighbour
*/
float GraphNode::GetNeighbourDistance(uint32 nNeighbour) const
{
	const Neighbour *pNeighbour = m_lstNeighbours[nNeighbour];
	return pNeighbour ? pNeighbour->fDistance : -1.0f;
}

/**
*  @brief
*    Adds a neighbour connection
*/
bool GraphNode::AddNeighbour(GraphNode &cNode, float fDistance)
{
	// Is this node already a neighbour of this node?
	if (!IsNeighbour(cNode)) {
		// Add node
		Neighbour *pNeighbour = new Neighbour();
		m_lstNeighbours.Add(pNeighbour);
		pNeighbour->pNode     = &cNode;
		pNeighbour->fDistance = (fDistance < 0.0f) ? GetDistance(cNode) : fDistance;
		cNode.m_lstIsNeighbourFrom.Add(this);

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Removes a neighbour connection
*/
bool GraphNode::RemoveNeighbour(GraphNode &cNode)
{
	// Find neighbour list entry
	Neighbour *pNeighbour = nullptr;
	{
		Iterator<Neighbour*> cIterator = m_lstNeighbours.GetIterator();
		while (cIterator.HasNext()) {
			Neighbour *pNeighbourT = cIterator.Next();
			if (pNeighbourT->pNode == &cNode) {
				pNeighbour = pNeighbourT;
				break;
			}
		}
	}

	// Remove
	if (pNeighbour) {
		cNode.m_lstIsNeighbourFrom.Remove(this);
		delete pNeighbour;
		m_lstNeighbours.Remove(pNeighbour);

		// Done
		return true;
	} else return false; // Error!
}

/**
*  @brief
*    Removes a neighbour connection at the given index
*/
bool GraphNode::RemoveNeighbourAtIndex(uint32 nNeighbour)
{
	Neighbour *pNeighbour = m_lstNeighbours[nNeighbour];
	if (pNeighbour) {
		pNeighbour->pNode->m_lstIsNeighbourFrom.Remove(this);
		delete pNeighbour;
		m_lstNeighbours.RemoveAtIndex(nNeighbour);

		// Done
		return true;
	} else return false; // Error!
}


//[-------------------------------------------------------]
//[ Position                                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the node position
*/
const Vector3 &GraphNode::GetPos() const
{
	return m_vPos;
}

/**
*  @brief
*    Sets the node position
*/
void GraphNode::SetPos(const Vector3 &vPos)
{
	SetPos(vPos.x, vPos.y, vPos.z);
}

/**
*  @brief
*    Sets the node position
*/
void GraphNode::SetPos(float fX, float fY, float fZ)
{
	// Set new position
	m_vPos.SetXYZ(fX, fY, fZ);

	{ // Calculate all node distances
		Iterator<Neighbour*> cIterator = m_lstNeighbours.GetIterator();
		while (cIterator.HasNext()) {
			Neighbour *pNeighbour = cIterator.Next();
			pNeighbour->fDistance = GetDistance(*pNeighbour->pNode);
		}
	}

	{ // Update all neighbour node distances
		Iterator<GraphNode*> cIterator = m_lstIsNeighbourFrom.GetIterator();
		while (cIterator.HasNext()) {
			// Find this node within the neighbour
			Iterator<Neighbour*> cNeighbourIterator = cIterator.Next()->m_lstNeighbours.GetIterator();
			while (cNeighbourIterator.HasNext()) {
				Neighbour *pNeighbour = cNeighbourIterator.Next();
				if (pNeighbour->pNode == this) {
					pNeighbour->fDistance = GetDistance(*pNeighbour->pNode);
					break;
				}
			}
		}
	}
}

/**
*  @brief
*    Returns the distance between two graph nodes
*/
float GraphNode::GetDistance(const GraphNode &cNode) const
{
	return (cNode.GetPos()-m_vPos).GetLength();
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Element functions              ]
//[-------------------------------------------------------]
GraphNode &GraphNode::operator =(const GraphNode &cSource)
{
	// Call base function
	*static_cast<Element<GraphNode>*>(this) = cSource;

	// Copy data
	m_vPos = cSource.m_vPos;

	// Return this
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
