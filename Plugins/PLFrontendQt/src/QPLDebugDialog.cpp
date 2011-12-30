/*********************************************************\
 *  File: QPLDebugDialog.cpp                             *
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
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SceneContainer.h>
#include "PLFrontendQt/DataModels/SceneNodeInfoModel.h"
#include "PLFrontendQt/DataModels/SceneGraphTreeModel.h"
#include "PLFrontendQt/DataModels/SceneNodeInfoDelegate.h"
#include "PLFrontendQt/DataModels/SceneGraphNodeTreeItemBase.h"
#include "PLFrontendQt/QPLSceneContext.h"
#include "PLFrontendQt/QPLDebugDialog.h"
#include "ui_QPLDebugDialog.h"	// Automatically created by Qt's uic, output directory is "build/GeneratedQtFiles"


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
	EventHandlerSceneContextUpdate(&QPLDebugDialog::OnSceneContextUpdate, this)
{
	ui->setupUi(this);

	graphModel = new SceneGraphTreeModel(this);
	nodeInfoModel = new SceneNodeInfoModel(this);

	ui->sceneTree->setModel(graphModel);
	ui->sceneTree->expandToDepth(0);
	ui->sceneNodeTree->setModel(nodeInfoModel);
	ui->sceneNodeTree->setItemDelegate(new SceneNodeInfoDelegate);
}

void QPLDebugDialog::SetContext(QPLSceneContext *context)
{
	if (m_context) {
		//m_context->GetSceneContext()->EventUpdate.Disconnect(&EventHandlerSceneContextUpdate);
		m_context->disconnect(this);
	}

	m_context = context;

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
	graphModel->SetStartNode(m_context->GetScene());
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
