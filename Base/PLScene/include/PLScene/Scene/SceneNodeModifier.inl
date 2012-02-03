/*********************************************************\
 *  File: SceneNodeModifier.inl                          *
 *      Scene node modifier inline implementation
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
*    Returns the owner scene node
*/
inline SceneNode &SceneNodeModifier::GetSceneNode() const
{
	return *m_pSceneNode;
}

/**
*  @brief
*    Returns the index of the given modifier
*/
inline int SceneNodeModifier::GetSceneNodeIndex()
{
	return m_pSceneNode->m_lstModifiers.GetIndex(this);
}

/**
*  @brief
*    Returns the scene context the owner scene node is in
*/
inline SceneContext *SceneNodeModifier::GetSceneContext() const
{
	// There's always a valid owner scene node, so we don't need to check for a null pointer!
	return m_pSceneNode->GetSceneContext();
}

/**
*  @brief
*    Is the scene node modifier active?
*/
inline bool SceneNodeModifier::IsActive() const
{
	return !(m_nFlags & Inactive);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
