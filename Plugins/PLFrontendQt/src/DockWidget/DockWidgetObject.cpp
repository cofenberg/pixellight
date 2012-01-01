/*********************************************************\
 *  File: DockWidgetObject.cpp                           *
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
#include <PLCore/Application/CoreApplication.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DataModels/PLIntrospectionModel.h"
#include "PLFrontendQt/DockWidget/DockWidgetObject.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(DockWidgetObject)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DockWidgetObject::DockWidgetObject(QMainWindow *pQMainWindow) : DockWidget(pQMainWindow)
{
	// Get encapsulated Qt dock widget
	QDockWidget *pQDockWidget = GetQDockWidget();
	if (pQDockWidget) {
		// Create tree view and set scene graph model
		QTreeView *pQTreeView = new QTreeView();
		pQDockWidget->setWidget(pQTreeView);
		DataModels::PLIntrospectionModel *pPLIntrospectionModel = new DataModels::PLIntrospectionModel(pQDockWidget);
		pQTreeView->setModel(pPLIntrospectionModel);
		pQTreeView->expandToDepth(0);

		// Set a default object to have a decent standard behaviour
		CoreApplication *pCoreApplication = CoreApplication::GetApplication();
		pPLIntrospectionModel->SetObject(pCoreApplication);

		// Set window title
		QString sQStringWindowTitle = pQDockWidget->tr(GetClass()->GetProperties().Get("Title"));
		if (pCoreApplication && pCoreApplication->GetClass()) {
			sQStringWindowTitle += ": ";
			sQStringWindowTitle += QtStringAdapter::PLToQt('\"' + pCoreApplication->GetClass()->GetClassName() + '\"');	// Put it into quotes to make it possible to see e.g. trailing spaces
		}
		pQDockWidget->setWindowTitle(sQStringWindowTitle);

		// Add the created Qt dock widget to the given Qt main window
		pQMainWindow->addDockWidget(Qt::BottomDockWidgetArea, pQDockWidget);
	}
}

/**
*  @brief
*    Destructor
*/
DockWidgetObject::~DockWidgetObject()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
