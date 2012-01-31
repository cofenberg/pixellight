/*********************************************************\
 *  File: DockWidgetSceneGraphQObject.cpp                *
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
#include "PLFrontendQt/Widget/SceneGraphMenu.h"
#include "PLFrontendQt/DataModels/SceneGraphTreeModel.h"
#include "PLFrontendQt/DataModels/TreeSortAndFilterProxyModel.h"
#include "PLFrontendQt/DockWidget/DockWidgetSceneGraph.h"
#include "PLFrontendQt/DockWidget/DockWidgetSceneGraphQObject.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DockWidgetSceneGraphQObject::DockWidgetSceneGraphQObject(DockWidgetSceneGraph &cDockWidgetSceneGraph) :
	m_pDockWidgetSceneGraph(&cDockWidgetSceneGraph)
{
}

/**
*  @brief
*    Destructor
*/
DockWidgetSceneGraphQObject::~DockWidgetSceneGraphQObject()
{
}


//[-------------------------------------------------------]
//[ Private Qt slots (MOC)                                ]
//[-------------------------------------------------------]
void DockWidgetSceneGraphQObject::QtSlotTreeViewDoubleClicked(const QModelIndex &cQModelIndex)
{
	// Use the given Qt model index to figure out the currently selected RTTI class instance
	Object *pObject = m_pDockWidgetSceneGraph->GetObjectByQModelIndex(cQModelIndex);

	// Perform a dock widget manager broadcast (excludes this emitting dock widget)
	m_pDockWidgetSceneGraph->CallDockWidgetsMethod("SelectObject", Params<void, Object*>(pObject));
}

void DockWidgetSceneGraphQObject::QtSlotCustomContextMenuRequested(const QPoint &cQPoint)
{
	// Show the scene graph context menu
	if (m_pDockWidgetSceneGraph->m_pQTreeView) {
		// We could use
		//   "Object *pObject = m_pDockWidgetSceneGraph->GetSelectedObject();"
		// in here, but it looks odd to be able to add a context menu for
		// an item while the mouse is far, far away from the item itself
		// -> So, we're asking Qt for a model index below the given point
		const QModelIndex cQModelIndex = m_pDockWidgetSceneGraph->m_pQTreeView->indexAt(cQPoint);

		// Use the resulting Qt model index to figure out the currently selected RTTI class instance
		Object *pObject = cQModelIndex.isValid() ? m_pDockWidgetSceneGraph->GetObjectByQModelIndex(cQModelIndex) : nullptr;

		// Show the scene graph context menu
		if (pObject) {
			SceneGraphMenu menu(*pObject);
			QAction* pAction = menu.exec(reinterpret_cast<QWidget*>(m_pDockWidgetSceneGraph->m_pQTreeView)->mapToGlobal(cQPoint));
			if(pAction) {
				// Update the scene graph tree view because the probability is high that it's content was changed
				QVariant cUserData = pAction->data();
				DockWidgetSceneGraph::UpdateTreeReason updateReason = DockWidgetSceneGraph::Unknwon;
				if (cUserData.isValid())
					updateReason = static_cast<DockWidgetSceneGraph::UpdateTreeReason>(pAction->data().value<int>());
				m_pDockWidgetSceneGraph->UpdateTreeView(updateReason, menu.GetCreatedObject());
			}
		}
	}
}

void DockWidgetSceneGraphQObject::QtSlotFilterTypeChanged(int filterId)
{
	m_pDockWidgetSceneGraph->m_pSortAndFilterModel->setFilterRole((filterId == ByClassName) ? DataModels::SceneGraphTreeModel::ClassNameRole : static_cast<int>(Qt::DisplayRole));
}

void DockWidgetSceneGraphQObject::QtSlotFilterChanged(const QString &text)
{
	m_pDockWidgetSceneGraph->m_pSortAndFilterModel->setFilterWildcard(text);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
