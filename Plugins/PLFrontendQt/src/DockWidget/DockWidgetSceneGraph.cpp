/*********************************************************\
 *  File: DockWidgetSceneGraph.cpp                       *
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
#include <QtGui/qtreeview.h>
#include <QtGui/qdockwidget.h>
#include <QtGui/qmainwindow.h>
#include <PLCore/Base/Class.h>
#include <PLEngine/Application/EngineApplication.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DataModels/SceneGraphTreeModel.h"
#include "PLFrontendQt/DockWidget/DockWidgetManager.h"
#include "PLFrontendQt/DockWidget/DockWidgetSceneGraph.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(DockWidgetSceneGraph)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DockWidgetSceneGraph::DockWidgetSceneGraph(QMainWindow *pQMainWindow, DockWidgetManager *pDockWidgetManager) : DockWidgetScene(pQMainWindow, pDockWidgetManager),
	SlotOnDestroy(this),
	m_pSceneGraphTreeModel(nullptr)
{
	// Get encapsulated Qt dock widget
	QDockWidget *pQDockWidget = GetQDockWidget();
	if (pQDockWidget) {
		// Create tree view and set scene graph model
		QTreeView *pQTreeView = new QTreeView();
		connect(pQTreeView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(QtSlotTreeViewDoubleClicked(const QModelIndex&)));
		pQDockWidget->setWidget(pQTreeView);
		m_pSceneGraphTreeModel = new DataModels::SceneGraphTreeModel(pQDockWidget);
		pQTreeView->setModel(m_pSceneGraphTreeModel);
		pQTreeView->expandToDepth(0);

		// Set a default start node to have a decent standard behaviour
		SceneNode *pSceneNode = nullptr;
		{
			CoreApplication *pApplication = CoreApplication::GetApplication();
			if (pApplication && pApplication->IsInstanceOf("PLEngine::EngineApplication"))
				pSceneNode = reinterpret_cast<SceneNode*>(static_cast<PLEngine::EngineApplication*>(pApplication)->GetScene());
			m_pSceneGraphTreeModel->SetStartNode(pSceneNode, true);
		}

		// Connect event handler
		if (pSceneNode)
			pSceneNode->SignalDestroy.Connect(SlotOnDestroy);

		// Set window title
		QString sQStringWindowTitle = pQDockWidget->tr(GetClass()->GetProperties().Get("Title"));
		if (pSceneNode) {
			sQStringWindowTitle += ": ";
			sQStringWindowTitle += QtStringAdapter::PLToQt('\"' + pSceneNode->GetAbsoluteName() + '\"');	// Put it into quotes to make it possible to see e.g. trailing spaces
		}
		pQDockWidget->setWindowTitle(sQStringWindowTitle);

		// Add the created Qt dock widget to the given Qt main window
		pQMainWindow->addDockWidget(Qt::LeftDockWidgetArea, pQDockWidget);
	}
}

/**
*  @brief
*    Destructor
*/
DockWidgetSceneGraph::~DockWidgetSceneGraph()
{
}

/**
*  @brief
*    Selects the given object
*/
void DockWidgetSceneGraph::SelectObject(Object *pObject)
{
	// We only know "PLScene::SceneNode"
	SceneNode *pSceneNode = nullptr;
	if (pObject && pObject->IsInstanceOf("PLScene::SceneNode"))
		pSceneNode = static_cast<SceneNode*>(pObject);
	if (pSceneNode) {
		// [TODO] Select the given scene node within the scene graph tree view
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node assigned with this dock widget was destroyed
*/
void DockWidgetSceneGraph::OnDestroy()
{
	// Argh! Mayday! We lost our start scene node!
	m_pSceneGraphTreeModel->SetStartNode(nullptr, true);
}


//[-------------------------------------------------------]
//[ Private Qt slots (MOC)                                ]
//[-------------------------------------------------------]
void DockWidgetSceneGraph::QtSlotTreeViewDoubleClicked(const QModelIndex &cQModelIndex)
{
	// Is there a scene graph tree model instance?
	if (m_pSceneGraphTreeModel) {
		// Get selected scene node
		Object *pObject = m_pSceneGraphTreeModel->GetSceneNodeFromIndex(cQModelIndex);
		if (!pObject) {
			// Hm, maybe it's an selected scene node modifier?
			pObject = reinterpret_cast<Object*>(m_pSceneGraphTreeModel->GetSceneNodeModifierFromIndex(cQModelIndex));
		}

		// Perform a dock widget manager broadcast (excludes this emitting dock widget)
		CallDockWidgetsMethod("SelectObject", Params<void, Object*>(pObject));
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
