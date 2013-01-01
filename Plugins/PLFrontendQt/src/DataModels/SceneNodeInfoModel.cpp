/*********************************************************\
 *  File: SceneNodeInfoModel.cpp                         *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneNode.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include "PLFrontendQt/DataModels/SceneNodeInfoModel.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


SceneNodeInfoModel::SceneNodeInfoModel(QObject *parent) : PLIntrospectionModel(parent),
	m_curNode(nullptr),
	m_curNodeModifer(nullptr)
{
}

void SetSelected(PLScene::SceneNode *node, bool selected)
{
	PLCore::uint32 flagValue = node->GetDebugFlags();
	if (selected)
		flagValue |= PLScene::SceneNode::DebugEnabled;
	else
		flagValue &= ~PLScene::SceneNode::DebugEnabled;
	node->SetDebugFlags(flagValue);
}

PLScene::SceneNode *SceneNodeInfoModel::GetSceneNode() const
{
	return m_curNode;
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
} // PLFrontendQt
