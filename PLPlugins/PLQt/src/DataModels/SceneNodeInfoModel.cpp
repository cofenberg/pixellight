/*********************************************************\
 *  File: SceneNodeInfoModel.cpp                         *
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
#include <PLScene/Scene/SceneNode.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include "PLQt/DataModels/SceneNodeInfoModel.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLQt {
namespace DataModels {


SceneNodeInfoModel::SceneNodeInfoModel(QObject *parent) : PLIntrospectionModel(parent),
	m_curNode(nullptr),
	m_curNodeModifer(nullptr)
{
}

void SetSelected(PLScene::SceneNode *node, bool selected)
{
	PLGeneral::uint32 flagValue = node->GetDebugFlags();
	if (selected)
		flagValue |= PLScene::SceneNode::DebugEnabled;
	else
		flagValue &= ~PLScene::SceneNode::DebugEnabled;
	node->SetDebugFlags(flagValue);
}

void SceneNodeInfoModel::SetSceneNode(PLScene::SceneNode *nodeObj)
{
	if (m_curNode != nodeObj) {
		if (m_curNode)
			SetSelected(m_curNode, false);

		if (m_curNodeModifer)
			m_curNodeModifer = nullptr;

		SetObject(nodeObj);

		m_curNode = nodeObj;
	}
}

void SceneNodeInfoModel::SetSceneNodeModifier(PLScene::SceneNodeModifier *nodeObj)
{
	if (m_curNodeModifer != nodeObj) {
		if (m_curNode) {
			SetSelected(m_curNode, false);
			m_curNode = nullptr;
		}

		SetObject(nodeObj);

		m_curNodeModifer = nodeObj;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLQt
