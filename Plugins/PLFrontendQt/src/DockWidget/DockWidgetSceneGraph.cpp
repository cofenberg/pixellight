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
#include <QtGui/qboxlayout.h>
#include <QtGui/qdockwidget.h>
#include <QtGui/qmainwindow.h>
#include <PLCore/Base/Class.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DataModels/SceneGraphTreeModel.h"
#include "PLFrontendQt/DataModels/TreeSortAndFilterProxyModel.h"
#include "PLFrontendQt/DockWidget/DockWidgetManager.h"
#include "PLFrontendQt/DockWidget/DockWidgetSceneGraphQObject.h"
#include "PLFrontendQt/DockWidget/DockWidgetSceneGraph.h"
#include "PLFrontendQt/Widget/FilterWidgetWithFilterTypSelector.h"


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
	m_pQTreeView(nullptr),
	m_pSceneGraphTreeModel(nullptr),
	m_pSceneContainer(nullptr),
	m_pDockWidgetSceneGraphQObject(new DockWidgetSceneGraphQObject(*this)),
	m_pSortAndFilterModel(nullptr)
{
	// Get encapsulated Qt dock widget
	QDockWidget *pQDockWidget = GetQDockWidget();
	if (pQDockWidget) {
		{ // Create tree view and set scene graph model
			// Create tree view widget
			m_pQTreeView = new QTreeView(pQDockWidget);
			m_pDockWidgetSceneGraphQObject->connect(m_pQTreeView, SIGNAL(doubleClicked(const QModelIndex&)), m_pDockWidgetSceneGraphQObject, SLOT(QtSlotTreeViewDoubleClicked(const QModelIndex&)));

			// Setup tree view widget context menu
			m_pQTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
			m_pDockWidgetSceneGraphQObject->connect(m_pQTreeView, SIGNAL(customContextMenuRequested(const QPoint&)), m_pDockWidgetSceneGraphQObject, SLOT(QtSlotCustomContextMenuRequested(const QPoint&)));

			// Create filter widget
			FilterWidgetWithFilterTypSelector *pFilterWidget = new FilterWidgetWithFilterTypSelector(pQDockWidget);
			pFilterWidget->AddFilterType(pQDockWidget->tr("By Scene Node Name"), DockWidgetSceneGraphQObject::BySceneNodeName, true);
			pFilterWidget->AddFilterType(pQDockWidget->tr("By Class Name"), DockWidgetSceneGraphQObject::ByClassName);
			m_pDockWidgetSceneGraphQObject->connect(pFilterWidget, SIGNAL(filterTypeChanged(int)), m_pDockWidgetSceneGraphQObject, SLOT(QtSlotFilterTypeChanged(int)));
			m_pDockWidgetSceneGraphQObject->connect(pFilterWidget, SIGNAL(filterChanged(const QString)), m_pDockWidgetSceneGraphQObject, SLOT(QtSlotFilterChanged(const QString)));

			// Create host widget combining tree view widget and filter widget
			QWidget *pQWidgetHost = new QWidget(pQDockWidget);
			pQWidgetHost->setLayout(new QVBoxLayout);
			pQWidgetHost->layout()->addWidget(pFilterWidget);
			pQWidgetHost->layout()->addWidget(m_pQTreeView);
			pQDockWidget->setWidget(pQWidgetHost);

			// Set models
			m_pSceneGraphTreeModel = new DataModels::SceneGraphTreeModel(pQDockWidget);
			m_pSortAndFilterModel = new DataModels::TreeSortAndFilterProxyModel(pQDockWidget);
			m_pSortAndFilterModel->setSourceModel(m_pSceneGraphTreeModel);
			m_pSortAndFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
			m_pQTreeView->setModel(m_pSortAndFilterModel);

			// Hide the root
			m_pQTreeView->expandToDepth(0);
		}

		// Add the created Qt dock widget to the given Qt main window
		pQMainWindow->addDockWidget(Qt::LeftDockWidgetArea, pQDockWidget);

		// Set the used scene container and object
		SetSceneContainerAndObject();
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
		// -> Hiding the start node would be nice, but then it would not be possible to manipulate it :/
		m_pSceneGraphTreeModel->SetStartNode(m_pSceneContainer);

		// At least expand the first depth by default
		m_pQTreeView->expandToDepth(0);

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
	// Is there a Qt tree widget instance?
	if (m_pQTreeView) {
		// Get the selected model index
		// -> We only support one selected item at the same time
		const QModelIndex cQModelIndex = m_pQTreeView->selectionModel()->currentIndex();
		if (cQModelIndex.isValid()) {
			// Use the Qt model index to figure out the currently selected RTTI class instance
			return GetObjectByQModelIndex(cQModelIndex);
		}
	}

	// Error!
	return nullptr;
}

/**
*  @brief
*    Selects the given object (post-broadcast)
*/
void DockWidgetSceneGraph::PostSelectObject(Object *pObject)
{
	// Is there a scene graph tree model and tree view instance
	if (m_pSceneGraphTreeModel && m_pSortAndFilterModel && m_pQTreeView) {
		// The model index for the given scene node or scene node modifier
		QModelIndex cSourceIndex;

		// Object given?
		if (pObject) {
			// Is it a scene node?
			if (pObject->IsInstanceOf("PLScene::SceneNode")) {
				// Get the model index for the given scene node
				cSourceIndex = m_pSceneGraphTreeModel->GetModelIndexForSceneNode(static_cast<SceneNode*>(pObject));

			// Is it a scene node modifier?
			} else if (pObject->IsInstanceOf("PLScene::SceneNodeModifier")) {
				// Get the model index for the given scene node modifier
				cSourceIndex = m_pSceneGraphTreeModel->GetModelIndexForSceneNodeModifier(static_cast<SceneNodeModifier*>(pObject));
			}
		}

		// Is the Qt model index valid?
		if (cSourceIndex.isValid()) {
			// We use an QSortAndFilterProxyModel so we have to map the model index of the SceneGraphTreeModel to an index of the proxy model
			const QModelIndex cFilterModelIndex = m_pSortAndFilterModel->mapFromSource(cSourceIndex);

			// Select the item as the current one
			// -> We only support one selected item at the same time
			m_pQTreeView->selectionModel()->select(cFilterModelIndex, QItemSelectionModel::ClearAndSelect);

			// Make the selected item visible if needed
			// -> This has to be done after the main-broadcast is through
			// -> Usability: By default it's ensured that the selection will be visible, the item may
			//    be on top of our tree view or on the bottom. In case it's e.g. a scene node with
			//    expanded scene node modifiers and the selected item is placed at the bottom of the
			//    widget one has to scroll before it's possible to access a modifier. By asking Qt
			//    to place the item at the center of the widget the item is always at the same position
			//    and it's easier for the eye to quickly find the selection, need for scrolling is also reduced.
			m_pQTreeView->scrollTo(cFilterModelIndex, QAbstractItemView::PositionAtCenter);
		}
	}
}

/**
*  @brief
*    An object was added
*/
void DockWidgetSceneGraph::AddedObject(Object &cObject, int nPosition)
{
	// Is there a scene graph tree model instance?
	if (m_pSceneGraphTreeModel) {
		// Scene node
		if (cObject.IsInstanceOf("PLScene::SceneNode")) {
			// Get scene node instance
			SceneNode &cSceneNode = static_cast<SceneNode&>(cObject);

			// Ignore automatically generated stuff
			if (!(cSceneNode.GetFlags() & SceneNode::Automatic)) {
				// Get the scene container
				SceneContainer *pSceneContainer = cSceneNode.GetContainer();
				if (pSceneContainer) {
					// Add the new scene node modifier to the tree view
					m_pSceneGraphTreeModel->AddSceneNode(pSceneContainer, &cSceneNode, nPosition);
				}
			}

		// Scene node modifier
		} else if (cObject.IsInstanceOf("PLScene::SceneNodeModifier")) {
			// Get scene node modifier instance
			SceneNodeModifier &cSceneNodeModifier = static_cast<SceneNodeModifier&>(cObject);

			// Ignore automatically generated stuff
			if (!(cSceneNodeModifier.GetFlags() & SceneNodeModifier::Automatic)) {
				// Add the new scene node modifier to the tree view
				m_pSceneGraphTreeModel->AddSceneNodeModifier(&cSceneNodeModifier.GetSceneNode(), &cSceneNodeModifier, nPosition);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets the used scene container and object
*/
void DockWidgetSceneGraph::SetSceneContainerAndObject()
{
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
					PostSelectObject(pObject);

					// Get the now selected object, null pointer if the found object one was rejected
					pObject = GetSelectedObject();
				}
			}
		}
	}
}

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

/**
*  @brief
*    Returns an object by using a given Qt model index
*/
Object *DockWidgetSceneGraph::GetObjectByQModelIndex(const QModelIndex &cQModelIndex) const
{
	// Is there a scene graph tree model instance?
	if (m_pSceneGraphTreeModel && m_pSortAndFilterModel) {
		// We have been provided with a filter model index, what we need is an index which can be used within the original tree view
		const QModelIndex cQModelIndexSource = m_pSortAndFilterModel->mapToSource(cQModelIndex);

		// Get selected scene node
		Object *pObject = reinterpret_cast<Object*>(m_pSceneGraphTreeModel->GetSceneNodeFromIndex(cQModelIndexSource));
		if (!pObject) {
			// Hm, maybe it's an selected scene node modifier?
			pObject = reinterpret_cast<Object*>(m_pSceneGraphTreeModel->GetSceneNodeModifierFromIndex(cQModelIndexSource));
		}

		// Return the RTTI class instance
		return pObject;
	}

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
