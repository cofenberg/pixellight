/*********************************************************\
 *  File: DockWidgetManager.cpp                          *
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
#include "PLFrontendQt/DockWidget/DockWidget.h"
#include "PLFrontendQt/DockWidget/DockWidgetManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(DockWidgetManager)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DockWidgetManager::DockWidgetManager(QMainWindow *pQMainWindow) :
	m_pQMainWindow(pQMainWindow)
{
}

/**
*  @brief
*    Destructor
*/
DockWidgetManager::~DockWidgetManager()
{
	// Inform all registered dock widgets that this dock widget manager is now gone (do not destroy the dock widgets in here!)
	for (uint32 i=0; i<m_lstDockWidgets.GetNumOfElements(); i++)
		m_lstDockWidgets[i]->m_pDockWidgetManager = nullptr;
}

/**
*  @brief
*    Shows a dock widget
*/
DockWidget *DockWidgetManager::ShowDockWidget(const String &sClassName)
{
	// Get the first dock widget instance which is an instance of the given class
	DockWidget *pDockWidget = GetFirstDockWidget(sClassName);
	if (pDockWidget) {
		// Get the encapsulated Qt dock widget
		QDockWidget *pQDockWidget = pDockWidget->GetQDockWidget();
		if (pQDockWidget) {
			pQDockWidget->show();
			pQDockWidget->activateWindow();
			pQDockWidget->raise();
		}
	} else {
		// Get the chosen dock widget RTTI class...
		const Class *pClass = ClassManager::GetInstance()->GetClass(sClassName);
		if (pClass && pClass->IsDerivedFrom("PLFrontendQt::DockWidget")) {
			// ... and create an instance of it (the dock widget will register itself within this dock widget manager)
			pDockWidget = reinterpret_cast<DockWidget*>(pClass->Create(Params<Object*, QMainWindow*, DockWidgetManager*>(m_pQMainWindow, this)));
		}
	}

	// Done
	return pDockWidget;
}

/**
*  @brief
*    Returns the first dock widget instance which is an instance of the given class
*/
DockWidget *DockWidgetManager::GetFirstDockWidget(const String &sClassName)
{
	// Look for the first instance of the given dock widget class
	for (uint32 i=0; i<m_lstDockWidgets.GetNumOfElements(); i++) {
		// Get the current dock widget instance
		DockWidget *pDockWidget = m_lstDockWidgets[i];

		// Is this an instance of the given class?
		if (pDockWidget->GetClass()->GetClassName() == sClassName)
			return pDockWidget;
	}

	// No instance of the given dock widget class found
	return nullptr;
}

/**
*  @brief
*    Hides all registered dock widgets
*/
void DockWidgetManager::HideDockWidgets()
{
	// Hide all registered dock widgets
	for (uint32 i=0; i<m_lstDockWidgets.GetNumOfElements(); i++) {
		// Get the encapsulated Qt dock widget
		QDockWidget *pQDockWidget = m_lstDockWidgets[i]->GetQDockWidget();
		if (pQDockWidget)
			pQDockWidget->hide();
	}
}

/**
*  @brief
*    Destroys all registered dock widgets (dock widget broadcast)
*/
void DockWidgetManager::DestroyDockWidgets()
{
	// Destroy one dock widget after another, each one will unregister it from this dock widget manager
	while (m_lstDockWidgets.GetNumOfElements())
		delete m_lstDockWidgets[0];
}

/**
*  @brief
*    Set dock widgets attribute value by using a given string value (dock widget broadcast)
*/
void DockWidgetManager::SetDockWidgetsAttribute(const String &sName, const String &sValue)
{
	for (uint32 i=0; i<m_lstDockWidgets.GetNumOfElements(); i++)
		m_lstDockWidgets[i]->SetAttribute(sName, sValue);
}

/**
*  @brief
*    Set dock widgets attribute value by using a given dynamic variable reference (dock widget broadcast)
*/
void DockWidgetManager::SetDockWidgetsAttribute(const String &sName, const DynVar &cVar)
{
	for (uint32 i=0; i<m_lstDockWidgets.GetNumOfElements(); i++)
		m_lstDockWidgets[i]->SetAttribute(sName, cVar);
}

/**
*  @brief
*    Set dock widgets attribute value by using a given dynamic variable pointer (dock widget broadcast)
*/
void DockWidgetManager::SetDockWidgetsAttribute(const String &sName, const DynVar *pVar)
{
	for (uint32 i=0; i<m_lstDockWidgets.GetNumOfElements(); i++)
		m_lstDockWidgets[i]->SetAttribute(sName, pVar);
}

/**
*  @brief
*    Set dock widgets attribute to it's default value (dock widget broadcast)
*/
void DockWidgetManager::SetDockWidgetsAttributeDefault(const String &sName)
{
	for (uint32 i=0; i<m_lstDockWidgets.GetNumOfElements(); i++)
		m_lstDockWidgets[i]->SetAttributeDefault(sName);
}

/**
*  @brief
*    Call dock widgets method with given dynamic parameters (dock widget broadcast)
*/
void DockWidgetManager::CallDockWidgetsMethod(const String &sName, DynParams &cParams)
{
	for (uint32 i=0; i<m_lstDockWidgets.GetNumOfElements(); i++)
		m_lstDockWidgets[i]->CallMethod(sName, cParams);
}

/**
*  @brief
*    Call dock widgets method with given constant dynamic parameters (dock widget broadcast)
*/
void DockWidgetManager::CallDockWidgetsMethod(const String &sName, const DynParams &cParams)
{
	for (uint32 i=0; i<m_lstDockWidgets.GetNumOfElements(); i++)
		m_lstDockWidgets[i]->CallMethod(sName, cParams);
}

/**
*  @brief
*    Call dock widgets method with parameters given as string (dock widget broadcast)
*/
void DockWidgetManager::CallDockWidgetsMethod(const String &sName, const String &sParams)
{
	for (uint32 i=0; i<m_lstDockWidgets.GetNumOfElements(); i++)
		m_lstDockWidgets[i]->CallMethod(sName, sParams);
}

/**
*  @brief
*    Call dock widgets method with parameters given as XML element (dock widget broadcast)
*/
void DockWidgetManager::CallDockWidgetsMethod(const String &sName, const XmlElement &cElement)
{
	for (uint32 i=0; i<m_lstDockWidgets.GetNumOfElements(); i++)
		m_lstDockWidgets[i]->CallMethod(sName, cElement);
}

/**
*  @brief
*    Set multiple dock widgets attribute values as a string at once (dock widget broadcast)
*/
void DockWidgetManager::SetDockWidgetsValues(const String &sVars)
{
	for (uint32 i=0; i<m_lstDockWidgets.GetNumOfElements(); i++)
		m_lstDockWidgets[i]->SetValues(sVars);
}

/**
*  @brief
*    Set dock widgets attribute values from XML (dock widget broadcast)
*/
void DockWidgetManager::SetDockWidgetsValuesXml(const XmlElement &cElement)
{
	for (uint32 i=0; i<m_lstDockWidgets.GetNumOfElements(); i++)
		m_lstDockWidgets[i]->SetValuesXml(cElement);
}

/**
*  @brief
*    Set all dock widgets attributes to default (dock widget broadcast)
*/
void DockWidgetManager::SetDockWidgetsDefaultValues()
{
	for (uint32 i=0; i<m_lstDockWidgets.GetNumOfElements(); i++)
		m_lstDockWidgets[i]->SetDefaultValues();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
