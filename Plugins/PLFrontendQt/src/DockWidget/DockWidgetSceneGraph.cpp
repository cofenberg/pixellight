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
#include <PLScene/Scene/SceneContainer.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DataModels/SceneGraphTreeModel.h"
#include "PLFrontendQt/DockWidget/DockWidgetManager.h"
#include "PLFrontendQt/DockWidget/DockWidgetSceneGraphQObject.h"
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
	m_pSceneGraphTreeModel(nullptr),
	m_pSceneContainer(nullptr),
	m_pDockWidgetSceneGraphQObject(new DockWidgetSceneGraphQObject(*this))
{
	// Get encapsulated Qt dock widget
	QDockWidget *pQDockWidget = GetQDockWidget();
	if (pQDockWidget) {
		// Create tree view and set scene graph model
		QTreeView *pQTreeView = new QTreeView();
		m_pDockWidgetSceneGraphQObject->connect(pQTreeView, SIGNAL(doubleClicked(const QModelIndex&)), m_pDockWidgetSceneGraphQObject, SLOT(QtSlotTreeViewDoubleClicked(const QModelIndex&)));
		pQDockWidget->setWidget(pQTreeView);
		m_pSceneGraphTreeModel = new DataModels::SceneGraphTreeModel(pQDockWidget);
		pQTreeView->setModel(m_pSceneGraphTreeModel);
		pQTreeView->expandToDepth(0);

		// Add the created Qt dock widget to the given Qt main window
		pQMainWindow->addDockWidget(Qt::LeftDockWidgetArea, pQDockWidget);

		// Get a list of dock widgets registered within the same dock widget manager this dock widget is in
		const Array<DockWidget*> &lstDockWidgets = GetFellowDockWidgets();

		// Ask the RTTI dock widget fellows whether or not someone knows which is the currently used scene container
		for (uint32 i=0; i<lstDockWidgets.GetNumOfElements() && !m_pSceneContainer; i++) {
			// Get the dock widget, and ignore our own ego
			DockWidget *pDockWidget = lstDockWidgets[i];
			if (pDockWidget != this) {
				// Get the typed dynamic parameters
				Params<SceneContainer*> cParams;

				// Call the RTTI method
				pDockWidget->CallMethod("GetSceneContainer", cParams);

				// Get the result
				if (cParams.Return)
					SetSceneContainer(cParams.Return);
			}
		}

		{ // Ask the RTTI dock widget fellows whether or not someone knows which is the currently selected scene node or scene node modifier
			// Get a list of dock widgets registered within the same dock widget manager this dock widget is in
			Object *pObject = nullptr;
			for (uint32 i=0; i<lstDockWidgets.GetNumOfElements() && !pObject; i++) {
				// Get the dock widget, and ignore our own ego
				DockWidget *pDockWidget = lstDockWidgets[i];
				if (pDockWidget != this) {
					// Get the typed dynamic parameters
					Params<Object*> cParams;

					// Call the RTTI method
					pDockWidget->CallMethod("GetSelectedObject", cParams);

					// Get the result
					pObject = cParams.Return;
					if (pObject) {
						// This method handles the filtering
						SelectObject(pObject);

						// Get the now selected object, null pointer if the found object one was rejected
						pObject = GetSelectedObject();
					}
				}
			}
		}
	}
}

/**
*  @brief
*    Destructor
*/
DockWidgetSceneGraph::~DockWidgetSceneGraph()
{
	// Destroy the QObject instance for Qt's signal/slot mechanisms
	delete m_pDockWidgetSceneGraphQObject;
}

/**
*  @brief
*    Returns the used scene container
*/
SceneContainer *DockWidgetSceneGraph::GetSceneContainer() const
{
	return m_pSceneContainer;
}

/**
*  @brief
*    Sets the scene container to use
*/
void DockWidgetSceneGraph::SetSceneContainer(SceneContainer *pSceneContainer)
{
	// Is there a scene graph tree model instance?
	if (m_pSceneGraphTreeModel) {
		// Disconnect event handler
		if (m_pSceneContainer)
			m_pSceneContainer->SignalDestroy.Disconnect(SlotOnDestroy);

		// Backup the given scene container pointer
		m_pSceneContainer = pSceneContainer;

		// Connect event handler
		if (m_pSceneContainer)
			m_pSceneContainer->SignalDestroy.Connect(SlotOnDestroy);

		// Set the start scene node within the scene graph tree model instance
		m_pSceneGraphTreeModel->SetStartNode(m_pSceneContainer, true);

		// Get encapsulated Qt dock widget
		QDockWidget *pQDockWidget = GetQDockWidget();
		if (pQDockWidget) {
			// Set window title
			QString sQStringWindowTitle = pQDockWidget->tr(GetClass()->GetProperties().Get("Title"));
			if (m_pSceneContainer) {
				sQStringWindowTitle += ": ";
				sQStringWindowTitle += QtStringAdapter::PLToQt('\"' + m_pSceneContainer->GetAbsoluteName() + '\"');	// Put it into quotes to make it possible to see e.g. trailing spaces
			}
			pQDockWidget->setWindowTitle(sQStringWindowTitle);
		}
	}
}

/**
*  @brief
*    Returns the currently selected object
*/
Object *DockWidgetSceneGraph::GetSelectedObject() const
{
	// [TODO] Implement me
	return nullptr;
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
*    Called when the scene container assigned with this dock widget was destroyed
*/
void DockWidgetSceneGraph::OnDestroy()
{
	// Argh! Mayday! We lost our scene container!
	// -> Now no scene container is currently set
	SetSceneContainer(nullptr);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
