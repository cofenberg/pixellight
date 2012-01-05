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
DockWidgetObject::DockWidgetObject(QMainWindow *pQMainWindow, DockWidgetManager *pDockWidgetManager) : DockWidget(pQMainWindow, pDockWidgetManager),
	SlotOnDestroyed(this),
	m_pPLIntrospectionModel(nullptr),
	m_pObject(nullptr)
{
	// Get encapsulated Qt dock widget
	QDockWidget *pQDockWidget = GetQDockWidget();
	if (pQDockWidget) {
		// Create tree view and set scene graph model
		QTreeView *pQTreeView = new QTreeView();
		pQDockWidget->setWidget(pQTreeView);
		m_pPLIntrospectionModel = new DataModels::PLIntrospectionModel(pQDockWidget);
		pQTreeView->setModel(m_pPLIntrospectionModel);
		pQTreeView->expandToDepth(0);

		// Set a default object to have a decent standard behaviour
		CoreApplication *pCoreApplication = CoreApplication::GetApplication();
		SelectObject(pCoreApplication);

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

/**
*  @brief
*    Selects the given object
*/
void DockWidgetObject::SelectObject(Object *pObject)
{
	// State change?
	if (m_pObject != pObject) {
		// Disconnect event handler
		if (m_pObject)
			m_pObject->SignalDestroyed.Disconnect(SlotOnDestroyed);

		// Backup the given object pointer
		m_pObject = pObject;

		// Connect event handler
		if (m_pObject)
			m_pObject->SignalDestroyed.Connect(SlotOnDestroyed);

		// Is there a PL introspection model instance?
		if (m_pPLIntrospectionModel) {
			// Set object
			m_pPLIntrospectionModel->SetObject(m_pObject);

			// Get encapsulated Qt dock widget and set a decent window title
			QDockWidget *pQDockWidget = GetQDockWidget();
			if (pQDockWidget) {
				// Set window title
				QString sQStringWindowTitle = pQDockWidget->tr(GetClass()->GetProperties().Get("Title"));
				if (m_pObject) { 
					// Append class name
					sQStringWindowTitle += ": ";
					sQStringWindowTitle += QtStringAdapter::PLToQt('\"' + m_pObject->GetClass()->GetClassName() + '\"');	// Put it into quotes to make it possible to see e.g. trailing spaces

					// An "PLCore::Object" itself has no "name", we could show the memory address but this wouldn't be that useful to the user
					// -> Try "GetAbsoluteName()"-method to get an absolute name
					// -> In case there's no name, check whether there's an name attribute
					// -> In case there's still no name, check whether or not there's an filename attribute
					String sName;
					{ // Try "GetAbsoluteName()"-method to get an absolute name
						// Get the typed dynamic parameters
						Params<String> cParams;

						// Call the RTTI method
						m_pObject->CallMethod("GetAbsoluteName", cParams);

						// Get the result
						sName = cParams.Return;
						if (sName.GetLength())
							sName = "Name = \"" + sName + '\"';	// Put it into quotes to make it possible to see e.g. trailing spaces
					}

					// Do we already have a name?
					if (!sName.GetLength()) {
						// Check whether there's an name attribute
						DynVar *pDynVar = m_pObject->GetAttribute("Name");
						if (pDynVar)
							sName = "Name = \"" + pDynVar->GetString() + '\"';	// Put it into quotes to make it possible to see e.g. trailing spaces

						// In case there's still no name, check whether or not there's an filename attribute
						if (!sName.GetLength()) {
							DynVar *pDynVar = m_pObject->GetAttribute("Filename");
							if (pDynVar)
								sName = "Filename = \"" + pDynVar->GetString() + '\"';	// Put it into quotes to make it possible to see e.g. trailing spaces
						}
					}

					// Use the name, if we have one
					if (sName.GetLength()) {
						// We have a representable name, show it to the user
						sQStringWindowTitle += ": ";
						sQStringWindowTitle += QtStringAdapter::PLToQt(sName);
					}
				}
				pQDockWidget->setWindowTitle(sQStringWindowTitle);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the object assigned with this dock widget was destroyed
*/
void DockWidgetObject::OnDestroyed()
{
	// Argh! Mayday! We lost our object!
	// -> Now no object is currently selected
	SelectObject(nullptr);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
