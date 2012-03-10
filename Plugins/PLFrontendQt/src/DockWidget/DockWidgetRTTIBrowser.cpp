/*********************************************************\
 *  File: DockWidgetRTTIBrowser.cpp                      *
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
#include <QtGui/qdockwidget.h>
#include <PLCore/Base/Class.h>
#include "PLFrontendQt/Widget/RTTIBrowserWidget.h"
#include "PLFrontendQt/DockWidget/DockWidgetRTTIBrowser.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(DockWidgetRTTIBrowser)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DockWidgetRTTIBrowser::DockWidgetRTTIBrowser(QMainWindow *pQMainWindow, DockWidgetManager *pDockWidgetManager) : DockWidget(reinterpret_cast<QWidget*>(pQMainWindow), pDockWidgetManager)
{
	// Get encapsulated Qt dock widget
	QDockWidget *pQDockWidget = GetQDockWidget();
	if (pQDockWidget) {
		// Create RTTI browser widget
		pQDockWidget->setWidget(new RTTIBrowserWidget());

		// Set window title
		pQDockWidget->setWindowTitle(pQDockWidget->tr(GetClass()->GetProperties().Get("Title")));

		// Add the created Qt dock widget to the given Qt main window and tabify it for better usability
		AddDockWidgetAndTabify(*pQMainWindow, Qt::BottomDockWidgetArea, *pQDockWidget);
	}
}

/**
*  @brief
*    Destructor
*/
DockWidgetRTTIBrowser::~DockWidgetRTTIBrowser()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
