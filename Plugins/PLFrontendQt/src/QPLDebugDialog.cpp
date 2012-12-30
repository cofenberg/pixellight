/*********************************************************\
 *  File: QPLDebugDialog.cpp                             *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SceneContainer.h>
#include "PLFrontendQt/DataModels/SceneNodeInfoModel.h"
#include "PLFrontendQt/DataModels/SceneGraphTreeModel.h"
#include "PLFrontendQt/DataModels/PLTreeItemsDelegate.h"
#include "PLFrontendQt/DataModels/SceneGraphNodeTreeItemBase.h"
#include "PLFrontendQt/QPLSceneContext.h"
#include "PLFrontendQt/QPLDebugDialog.h"
#include "ui_QPLDebugDialog.h"	// Automatically created by Qt's uic (output directory is "build/GeneratedQtFiles" within the hand configured Visual Studio files, another directory when using CMake)


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
using namespace DataModels;


QPLDebugDialog::QPLDebugDialog(QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f),
	m_context(nullptr),
	ui(new Ui::DebugView),
	graphModel(nullptr),
	nodeInfoModel(nullptr),
	EventHandlerSceneContextUpdate(&QPLDebugDialog::OnSceneContextUpdate, this),
	m_hideSceneStartNode(false)
{
	ui->setupUi(this);

	graphModel = new SceneGraphTreeModel(this);
	nodeInfoModel = new SceneNodeInfoModel(this);

	ui->sceneTree->setModel(graphModel);
	ui->sceneTree->expandToDepth(0);
	ui->sceneNodeTree->setModel(nodeInfoModel);
	ui->sceneNodeTree->setItemDelegate(new PLTreeItemsDelegate);
}

void QPLDebugDialog::SetContext(QPLSceneContext *context, bool hideSceneStartNode)
{
	if (m_context) {
		//m_context->GetSceneContext()->EventUpdate.Disconnect(&EventHandlerSceneContextUpdate);
		m_context->disconnect(this);
	}

	m_context = context;
	m_hideSceneStartNode = hideSceneStartNode;

	if (m_context) {
		connect(m_context, SIGNAL(ContextChanged()), this, SLOT(onSceneChanged()));
		connect(m_context, SIGNAL(BeginContextChange()), this, SLOT(onBeginSceneChanged()));
		//connect(m_context, SIGNAL(BeginContextChange()), this, SLOT(onSceneChanged()));
		// m_context->GetSceneContext()->EventUpdate.Connect(&EventHandlerSceneContextUpdate);
		onSceneChanged();
	}
}

void QPLDebugDialog::on_sceneTree_activated(QModelIndex index)
{
	SceneGraphNodeTreeItemBase *item = graphModel->GetSceneTreeItemFromIndex(index);
	if (item->IsSceneNode())
		nodeInfoModel->SetSceneNode((PLScene::SceneNode*)item->GetObject());
	else
		nodeInfoModel->SetSceneNodeModifier((PLScene::SceneNodeModifier*)item->GetObject());
}

void QPLDebugDialog::OnSceneContextUpdate()
{
	nodeInfoModel->UpdateModel();
}

void QPLDebugDialog::onSceneChanged()
{
	graphModel->SetStartNode(m_context->GetScene(), m_hideSceneStartNode);
}

void QPLDebugDialog::onBeginSceneChanged()
{
	graphModel->SetStartNode(nullptr);
	nodeInfoModel->SetSceneNode(nullptr);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
