/*********************************************************\
 *  File: SceneNode.inl                                  *
 *      Scene node inline implementation
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Gets the node transform
*/
inline const PLMath::Transform3 &SceneNode::GetTransform() const
{
	return m_cTransform;
}

inline PLMath::Transform3 &SceneNode::GetTransform()
{
	return m_cTransform;
}

/**
*  @brief
*    Returns whether this scene node is a scene container (SceneContainer) or not
*/
inline bool SceneNode::IsContainer() const
{
	return ((m_nInternalFlags & ClassContainer) != 0);
}

/**
*  @brief
*    Returns whether this scene node is a cell (SCCell) or not
*/
inline bool SceneNode::IsCell() const
{
	return ((m_nInternalFlags & ClassCell) != 0);
}

/**
*  @brief
*    Returns whether this scene node is a portal (SNPortal) or not
*/
inline bool SceneNode::IsPortal() const
{
	return ((m_nInternalFlags & ClassPortal) != 0);
}

/**
*  @brief
*    Returns whether this scene node is a camera (SNCamera) or not
*/
inline bool SceneNode::IsCamera() const
{
	return ((m_nInternalFlags & ClassCamera) != 0);
}

/**
*  @brief
*    Returns whether this scene node is a light (SNLight) or not
*/
inline bool SceneNode::IsLight() const
{
	return ((m_nInternalFlags & ClassLight) != 0);
}

/**
*  @brief
*    Returns whether this scene node is a fog (SNFog) or not
*/
inline bool SceneNode::IsFog() const
{
	return ((m_nInternalFlags & ClassFog) != 0);
}

/**
*  @brief
*    Returns the index of the given modifier
*/
inline int SceneNode::GetModifierIndex(SceneNodeModifier &cModifier) const
{
	return m_lstModifiers.GetIndex(&cModifier);
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    The current axis align bounding box is dirty and must be updated if used next time
*/
inline void SceneNode::DirtyAABoundingBox()
{
	// We have to recalculate the current axis align bounding box in 'scene node space'
	m_nInternalFlags |= RecalculateAABoundingBox;

	// We have to recalculate the current axis align bounding box in 'scene container space' because this data is derived from the axis align bounding box
	m_nInternalFlags |= RecalculateContainerAABoundingBox;

	// We have to recalculate the bounding sphere in 'sphere node space' because this data is derived from the axis align bounding box
	m_nInternalFlags |= RecalculateBoundingSphere;

	// We have to recalculate the current bounding sphere in 'sphere container space' because this data is derived from the axis align bounding box
	m_nInternalFlags |= RecalculateContainerBoundingSphere;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
