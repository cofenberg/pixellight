/*********************************************************\
 *  File: Gui.cpp                                        *
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
#include <PLCore/PLCore.h>
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4127)	// "warning C4127: conditional expression is constant"
	#include <QtGui/qevent.h>
	#include <QtGui/qlabel.h>
	#include <QtGui/qmenubar.h>
	#include <QtGui/qstatusbar.h>
	#include <QtGui/qfiledialog.h>
PL_WARNING_POP
#include <PLCore/Log/Log.h>
#include <PLCore/Base/Class.h>
#include <PLCore/System/System.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneQueries/SQByClassName.h>
#include <PLFrontendQt/Frontend.h>
#include <PLFrontendQt/QtStringAdapter.h>
#include <PLFrontendQt/FrontendMainWindow.h>
#include <PLFrontendQt/ConstructFileFilter.h>
#include <PLFrontendQt/DockWidget/DockWidget.h>
#include <PLFrontendQt/DockWidget/DockWidgetManager.h>
#include "Application.h"
#include "GuiPicking.h"
#include "Gui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
using namespace PLFrontendQt;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Gui::Gui(Application &cApplication) :
	EventHandlerCameraFound(&Gui::OnCameraFound, this),
	m_pApplication(&cApplication),
	m_pGuiPicking(nullptr),
	// Menu bar
	m_pQMenuCamera(nullptr),
	m_pQActionGroupCamera(nullptr),
	m_pQMenuWindow(nullptr),
	m_pQActionGroupWindow(nullptr),
	// Status bar
	m_pQLabelStatusBar(nullptr)
{
	// Get the Qt main window
	FrontendMainWindow *pFrontendMainWindow = GetFrontendMainWindow();
	if (pFrontendMainWindow) {
		// Initialize the main window
		InitMainWindow(*pFrontendMainWindow);
	}
}

/**
*  @brief
*    Destructor
*/
Gui::~Gui()
{
	// Destroy the GUI picking instance
	if (m_pGuiPicking)
		delete m_pGuiPicking;
}

/**
*  @brief
*    Returns the owner application
*/
Application &Gui::GetApplication() const
{
	return *m_pApplication;
}

/**
*  @brief
*    Get frontend main window
*/
FrontendMainWindow *Gui::GetFrontendMainWindow() const
{
	// Get Qt frontend implementation
	PLFrontendQt::Frontend *pFrontendQt = static_cast<PLFrontendQt::Frontend*>(m_pApplication->GetFrontend().GetImpl());
	if (pFrontendQt) {
		// Return the frontend main window
		return pFrontendQt->GetMainWindow();
	}

	// Error!
	return nullptr;
}

/**
*  @brief
*    Sets whether or not the GUI is currently enabled
*/
void Gui::SetEnabled(bool bEnabled)
{
	// Get the Qt main window
	FrontendMainWindow *pFrontendMainWindow = GetFrontendMainWindow();
	if (pFrontendMainWindow)
		pFrontendMainWindow->setEnabled(bEnabled);

	// Create/destroy the GUI picking
	if (bEnabled) {
		if (!m_pGuiPicking)
			m_pGuiPicking = new GuiPicking(*this);
	} else {
		if (m_pGuiPicking) {
			delete m_pGuiPicking;
			m_pGuiPicking = nullptr;
		}
	}
}

/**
*  @brief
*    Sets the state text
*/
void Gui::SetStateText(const String &sText)
{
	// Update the Qt label shown in the status bar of the Qt main window
	if (m_pQLabelStatusBar)
		m_pQLabelStatusBar->setText(QtStringAdapter::PLToQt(sText));
}

/**
*  @brief
*    Updates the GUI
*/
void Gui::Update()
{
	// Perform the informativ picking
	if (m_pGuiPicking)
		m_pGuiPicking->PerformInformativPicking();
}


//[-------------------------------------------------------]
//[ Public virtual QObject methods                        ]
//[-------------------------------------------------------]
bool Gui::eventFilter(QObject *pQObject, QEvent *pQEvent)
{
	// Get the Qt main window
	FrontendMainWindow *pFrontendMainWindow = GetFrontendMainWindow();

	// Handle Qt main window events
	if (pQObject == pFrontendMainWindow) {
		// Mouse button double click (QMouseEvent)
		if (pQEvent->type() == QEvent::MouseButtonDblClick) {
			// Cast the received event to QMouseEvent
			QMouseEvent *pQMouseEvent = static_cast<QMouseEvent*>(pQEvent);

			// Left mouse button?
			if (pQMouseEvent->button() == Qt::LeftButton) {
				// Perform picking
				if (m_pGuiPicking) {
					SceneNode *pSceneNode = m_pGuiPicking->PerformPicking();

					// Perform a dock widget manager broadcast
					pFrontendMainWindow->GetDockWidgetManager().CallDockWidgetsMethod("SelectSceneNode", Params<void, SceneNode*>(pSceneNode));

					// Scene node picked?
					if (pSceneNode) {
						// [TODO] Currently we just toggle the scene node debug mode to see some action
						// Toggle the debug mode of the picked scene node
						if (pSceneNode->GetDebugFlags() & SceneNode::DebugEnabled) {
							// Disable debug mode
							pSceneNode->SetDebugFlags(pSceneNode->GetDebugFlags() & ~SceneNode::DebugEnabled);
						} else {
							// Enable debug mode
							pSceneNode->SetDebugFlags(pSceneNode->GetDebugFlags() |SceneNode::DebugEnabled);
						}
					}

					// Done - filter the event out, i.e. stop it being handled further
					return true;
				}
			}
		}
	}

	// Pass the event on to the parent class
	return QObject::eventFilter(pQObject, pQEvent);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initializes the main window
*/
void Gui::InitMainWindow(QMainWindow &cQMainWindow)
{
	// This Qt object should receive events from the Qt main window
	cQMainWindow.installEventFilter(this);

	{ // Menu bar
		{ // Setup the file menu
			QMenu *pQMenu = cQMainWindow.menuBar()->addMenu(tr("&File"));

			{ // Setup the load action
				QAction *pQAction = new QAction(tr("L&oad"), &cQMainWindow);
				connect(pQAction, SIGNAL(triggered()), this, SLOT(QtSlotTriggeredLoad()));
				pQAction->setShortcut(tr("Ctrl+L"));
				pQMenu->addAction(pQAction);
			}

			// Add a separator
			pQMenu->addSeparator();

			{ // Setup the exit action
				QAction *pQAction = new QAction(tr("E&xit"), &cQMainWindow);
				pQAction->setShortcuts(QKeySequence::Quit);
				connect(pQAction, SIGNAL(triggered()), this, SLOT(QtSlotTriggeredExit()));
				pQAction->setShortcut(tr("Ctrl+Q"));
				pQMenu->addAction(pQAction);
			}
		}

		{ // Setup the camera menu
			m_pQMenuCamera = cQMainWindow.menuBar()->addMenu(tr("&Camera"));
			connect(m_pQMenuCamera, SIGNAL(aboutToShow()), this, SLOT(QtSlotAboutToShowMenuCamera()));

			// Menu is filled when it's about to show
		}

		{ // Setup the window menu
			m_pQMenuWindow = cQMainWindow.menuBar()->addMenu(tr("&Window"));
			connect(m_pQMenuWindow, SIGNAL(aboutToShow()), this, SLOT(QtSlotAboutToShowMenuWindow()));

			// Menu is filled when it's about to show
		}

		{ // Setup the tools menu
			QMenu *pQMenu = cQMainWindow.menuBar()->addMenu(tr("&Tools"));

			{ // Setup the log action
				QAction *pQAction = new QAction(tr("Open log file"), &cQMainWindow);
				connect(pQAction, SIGNAL(triggered()), this, SLOT(QtSlotTriggeredOpenLogFile()));
				pQMenu->addAction(pQAction);
			}
		}
	}

	{ // Status bar
		// Create the Qt label shown in the status bar of the Qt main window and add it to Qt main window status bar
		m_pQLabelStatusBar = new QLabel();
		cQMainWindow.statusBar()->addWidget(m_pQLabelStatusBar);
	}
}

/**
*  @brief
*    Called when a camera scene node was found
*/
void Gui::OnCameraFound(SceneQuery &cQuery, SceneNode &cSceneNode)
{
	// Camera Qt menu there?
	if (m_pQMenuCamera) {
		// Add camera to the menu
		QAction *pQAction = m_pQMenuCamera->addAction(QtStringAdapter::PLToQt(cSceneNode.GetAbsoluteName()));
		pQAction->setCheckable(true);
		if (reinterpret_cast<SceneNode*>(m_pApplication->GetCamera()) == &cSceneNode)
			pQAction->setChecked(true);
		m_pQActionGroupCamera->addAction(pQAction);
	}
}

/**
*  @brief
*    Fills the window menu recursivity
*/
void Gui::FillMenuWindowRec(QMenu &cQMenu, const String &sBaseClass)
{
	// Get a list of RTTI classes derived from the current base class
	List<const Class*> lstClasses;
	ClassManager::GetInstance()->GetClasses(lstClasses, sBaseClass, NonRecursive, NoBase, IncludeAbstract);
	ConstIterator<const Class*> cIterator = lstClasses.GetConstIterator();
	while (cIterator.HasNext()) {
		// Get the current RTTI class
		const Class *pClass = cIterator.Next();

		// Abstract class?
		if (pClass->HasConstructor()) {
			// Class can be instanced

			// Add action
			QAction *pQAction = cQMenu.addAction(tr(pClass->GetProperties().Get("Title")));
			pQAction->setCheckable(true);
			pQAction->setData(QtStringAdapter::PLToQt(pClass->GetClassName()));
			m_pQActionGroupWindow->addAction(pQAction);

			// One can also derive from classes which can be instanced, but by convention this should not be done for RTTI dock widgets

			// Get the Qt main window
			FrontendMainWindow *pFrontendMainWindow = GetFrontendMainWindow();

			// Is there currently an instance of this dock widget already visible?
			DockWidget *pDockWidget = pFrontendMainWindow ? pFrontendMainWindow->GetDockWidgetManager().GetFirstDockWidget(pClass->GetClassName()) : nullptr;
			pQAction->setChecked(pDockWidget ? pDockWidget->IsQDockWidgetVisible() : false);
		} else {
			// Abstract class

			// Add sub-menu
			QMenu *pQMenuSub = cQMenu.addMenu(tr(pClass->GetProperties().Get("Title")));

			// Automatically fill the Qt window menu by using RTTI information
			FillMenuWindowRec(*pQMenuSub, pClass->GetClassName());
		}
	}
}


//[-------------------------------------------------------]
//[ Private Qt slots (MOC)                                ]
//[-------------------------------------------------------]
void Gui::QtSlotTriggeredLoad()
{
	// Fill the file filter (filter example: "Scene (*.scene *.SCENE);;Script (*.lua *.LUA)")
	String sFileFilter = ConstructFileFilter::ByLoadableType(QtStringAdapter::QtToPL(tr("Scene")), "Scene");
	sFileFilter += ";;";
	sFileFilter += ConstructFileFilter::ByScriptLanguages(QtStringAdapter::QtToPL(tr("Script")));
	sFileFilter += ";;";
	sFileFilter += ConstructFileFilter::ByLoadableType(QtStringAdapter::QtToPL(tr("Mesh")), "Mesh");
	sFileFilter += ";;";
	sFileFilter += ConstructFileFilter::ByLoadableType(QtStringAdapter::QtToPL(tr("Material")), "Material");
	sFileFilter += ";;";
	sFileFilter += ConstructFileFilter::ByLoadableType(QtStringAdapter::QtToPL(tr("Image")), "Image");

	// Open a file dialog were the user can choose a filename
	const QString sQFilename = QFileDialog::getOpenFileName(GetFrontendMainWindow(), "", "", QtStringAdapter::PLToQt(sFileFilter));

	// Filename chosen?
	if (sQFilename.length())
		m_pApplication->LoadResource(QtStringAdapter::QtToPL(sQFilename));
}

void Gui::QtSlotTriggeredExit()
{
	// Shut down the application
	m_pApplication->Exit(0);
}

void Gui::QtSlotAboutToShowMenuCamera()
{
	// Camera Qt menu there?
	if (m_pQMenuCamera) {
		// Clear the previous content - this is not performance critical so there's no reason to implement a
		// more complex solution like e.g. updating the menu entries as soon as there's a change within the scene
		m_pQMenuCamera->clear();
		if (m_pQActionGroupCamera)
			delete m_pQActionGroupCamera;
		m_pQActionGroupCamera = new QActionGroup(GetFrontendMainWindow());
		connect(m_pQActionGroupCamera, SIGNAL(selected(QAction*)), this, SLOT(QtSlotSelectedCamera(QAction*)));

		// Automatically fill the Qt camera menu by using the cameras which are within the scene

		// Get the scene container with our 'concrete scene'
		SceneContainer *pSceneContainer = m_pApplication->GetScene();
		if (pSceneContainer) {
			// Create a scene query instance
			SQByClassName *pSceneQuery = static_cast<SQByClassName*>(pSceneContainer->CreateQuery("PLScene::SQByClassName"));
			if (pSceneQuery) {
				// Setup the regular expression of the scene query
				pSceneQuery->SetRegEx(RegEx("PLScene::SNCamera"));

				// Connect event handler
				pSceneQuery->SignalSceneNode.Connect(EventHandlerCameraFound);

				// Perform the scene query
				pSceneQuery->PerformQuery();

				// Destroy scene query instance
				pSceneContainer->DestroyQuery(*pSceneQuery);
			}
		}
	}
}

void Gui::QtSlotSelectedCamera(QAction *pQAction)
{
	// Get the scene container with our 'concrete scene'
	SceneContainer *pSceneContainer = m_pApplication->GetScene();
	if (pSceneContainer) {
		// Get the chosen camera scene node
		SceneNode *pSceneNode = pSceneContainer->GetByName(QtStringAdapter::QtToPL(pQAction->text()));
		if (pSceneNode && pSceneNode->IsCamera()) {
			// Set the new application camera
			m_pApplication->SetCamera(reinterpret_cast<SNCamera*>(pSceneNode));
		}
	}
}

void Gui::QtSlotAboutToShowMenuWindow()
{
	// Window Qt menu there?
	if (m_pQMenuWindow) {
		// Get the Qt main window
		FrontendMainWindow *pFrontendMainWindow = GetFrontendMainWindow();

		// Clear the previous content - this is not performance critical so there's no reason to implement a
		// more complex solution like e.g. updating the menu entries as soon as there's a change within the scene
		m_pQMenuWindow->clear();
		if (m_pQActionGroupWindow)
			delete m_pQActionGroupWindow;
		m_pQActionGroupWindow = new QActionGroup(pFrontendMainWindow);
		m_pQActionGroupWindow->setExclusive(false);
		connect(m_pQActionGroupWindow, SIGNAL(selected(QAction*)), this, SLOT(QtSlotSelectedWindow(QAction*)));

		{ // Setup the hide all action
			QAction *pQAction = new QAction(tr("Hide all"), pFrontendMainWindow);
			connect(pQAction, SIGNAL(triggered()), this, SLOT(QtSlotTriggeredWindowHideAll()));
			m_pQMenuWindow->addAction(pQAction);
		}

		// Add a separator
		m_pQMenuWindow->addSeparator();

		// Automatically fill the Qt window menu by using RTTI information
		FillMenuWindowRec(*m_pQMenuWindow, "PLFrontendQt::DockWidget");
	}
}

void Gui::QtSlotTriggeredWindowHideAll()
{
	// Get the Qt main window
	FrontendMainWindow *pFrontendMainWindow = GetFrontendMainWindow();
	if (pFrontendMainWindow) {
		// All registered dock widgets
		pFrontendMainWindow->GetDockWidgetManager().HideDockWidgets();
	}
}

void Gui::QtSlotSelectedWindow(QAction *pQAction)
{
	// Get the Qt main window
	FrontendMainWindow *pFrontendMainWindow = GetFrontendMainWindow();
	if (pFrontendMainWindow) {
		// Show the requested dock widget
		pFrontendMainWindow->GetDockWidgetManager().ShowDockWidget(QtStringAdapter::QtToPL(pQAction->data().toString()));
	}
}

void Gui::QtSlotTriggeredOpenLogFile()
{
	// Use "PLCore::System::Execute()" to open the log file which is usually a simple text file
	// -> "QDesktopServices::openUrl(QtStringAdapter::PLToQt(Log::GetInstance()->GetFilename()));" didn't work for me
	System::GetInstance()->Execute(Log::GetInstance()->GetFilename(), "");
}
