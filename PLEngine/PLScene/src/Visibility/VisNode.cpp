/*********************************************************\
 *  File: VisNode.cpp                                    *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneNodeHandler.h"
#include "PLScene/Visibility/SQCull.h"
#include "PLScene/Visibility/VisContainer.h"
#include "PLScene/Visibility/VisNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLScene {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the visibility root container
*/
const VisContainer *VisNode::GetVisRootContainer() const
{
	if (m_pParent) {
		const SQCull *pSceneQuery = NULL;
		if (m_pParent->IsContainer())
			pSceneQuery = ((VisContainer*)m_pParent)->GetCullQuery();
		else if (m_pParent->IsPortal())
			pSceneQuery = ((VisContainer*)m_pParent->GetParent())->GetCullQuery();
		return pSceneQuery ? pSceneQuery->GetVisRootContainer() : NULL;
	} else {
		return (VisContainer*)this;
	}
}

/**
*  @brief
*    Returns the parent visibility node
*/
const VisNode *VisNode::GetParent() const
{
	return m_pParent;
}

/**
*  @brief
*    Returns the scene node this visibility node links to
*/
SceneNode *VisNode::GetSceneNode() const
{
	return m_pSceneNodeHandler->GetElement();
}

/**
*  @brief
*    Returns the absolute world matrix of the scene node
*/
const Matrix3x4 &VisNode::GetWorldMatrix() const
{
	return m_mWorld;
}

// [TODO] VisNode refactoring -> currently, this method should not be used if possible because it doesn't update for example GetInverseWorldMatrix()
void VisNode::SetWorldMatrix(const Matrix3x4 &mWorld)
{
	m_mWorld = mWorld;
}

/**
*  @brief
*    Returns the absolute inverse world matrix of the scene node
*/
const Matrix3x4 &VisNode::GetInverseWorldMatrix() const
{
	return m_mInvWorld;
}

/**
*  @brief
*    Returns the absolute world view matrix of the scene node
*/
const Matrix4x4 &VisNode::GetWorldViewMatrix() const
{
	return m_mWorldView;
}

/**
*  @brief
*    Returns the absolute world view projection matrix of the scene node
*/
const Matrix4x4 &VisNode::GetWorldViewProjectionMatrix() const
{
	return m_mWorldViewProj;
}

/**
*  @brief
*    Returns the squared distance to the camera
*/
float VisNode::GetSquaredDistanceToCamera() const
{
	return m_fSquaredDistanceToCamera;
}


//[-------------------------------------------------------]
//[ Public virtual functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns whether or not this is a container visibility node (VisContainer, links to a SceneContainer scene node)
*/
bool VisNode::IsContainer() const
{
	return false;
}

/**
*  @brief
*    Returns whether or not this is a cell visibility node (VisContainer, links to a SNCell scene node)
*/
bool VisNode::IsCell() const
{
	return false;
}

/**
*  @brief
*    Returns whether or not this is a portal visibility node (VisPortal, links to a SNCellPortal scene node)
*/
bool VisNode::IsPortal() const
{
	return false;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
VisNode::VisNode(VisNode *pParent) :
	m_pParent(pParent),
	m_pSceneNodeHandler(new SceneNodeHandler()),
	m_fSquaredDistanceToCamera(0.0f)
{
}

/**
*  @brief
*    Destructor
*/
VisNode::~VisNode()
{
	delete m_pSceneNodeHandler;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
