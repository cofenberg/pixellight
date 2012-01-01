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
	#include <QtGui/qlabel.h>
	#include <QtGui/qmenubar.h>
	#include <QtGui/qstatusbar.h>
	#include <QtGui/qfiledialog.h>
PL_WARNING_POP
#include <PLCore/Base/Class.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneQueries/SQByClassName.h>
#include <PLFrontendQt/Frontend.h>
#include <PLFrontendQt/QtStringAdapter.h>
#include <PLFrontendQt/FrontendMainWindow.h>
#include <PLFrontendQt/ConstructFileFilter.h>
#include <PLFrontendQt/DockWidget/DockWidget.h>
#include "Application.h"
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
*    Sets the state text
*/
void Gui::SetStateText(const String &sText)
{
	// Update the Qt label shown in the status bar of the Qt main window
	if (m_pQLabelStatusBar)
		m_pQLabelStatusBar->setText(QtStringAdapter::PLToQt(sText));
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
	{ // Setup the file menu
		QMenu *pQMenu = cQMainWindow.menuBar()->addMenu(cQMainWindow.tr("&File"));

		{ // Setup the load action
			QAction *pQAction = new QAction(cQMainWindow.tr("L&oad"), &cQMainWindow);
			connect(pQAction, SIGNAL(triggered()), this, SLOT(QtSlotLoad()));
			pQAction->setShortcut(cQMainWindow.tr("Ctrl+L"));
			pQMenu->addAction(pQAction);
		}

		// Add a separator
		pQMenu->addSeparator();

		{ // Setup the exit action
			QAction *pQAction = new QAction(cQMainWindow.tr("E&xit"), &cQMainWindow);
			pQAction->setShortcuts(QKeySequence::Quit);
			connect(pQAction, SIGNAL(triggered()), this, SLOT(QtSlotExit()));
			pQAction->setShortcut(cQMainWindow.tr("Ctrl+Q"));
			pQMenu->addAction(pQAction);
		}
	}

	{ // Setup the camera menu
		m_pQMenuCamera = cQMainWindow.menuBar()->addMenu(cQMainWindow.tr("&Camera"));
		connect(m_pQMenuCamera, SIGNAL(aboutToShow()), this, SLOT(QtSlotMenuCameraAboutToShow()));

		// Menu is filled when it's about to show
	}

	{ // Setup the window menu
		m_pQMenuWindow = cQMainWindow.menuBar()->addMenu(cQMainWindow.tr("&Window"));
		connect(m_pQMenuWindow, SIGNAL(aboutToShow()), this, SLOT(QtSlotMenuWindowAboutToShow()));

		// Menu is filled when it's about to show
	}

	{ // Status bar
		// Create the Qt label shown in the status bar of the Qt main window
		m_pQLabelStatusBar = new QLabel();

		// Set Qt main window status bar
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
void Gui::QtSlotLoad()
{
	// Fill the file filter (filter example: "Scene (*.scene *.SCENE);;Script (*.lua *.LUA)")
	String sFileFilter = ConstructFileFilter::ByLoadableType(QtStringAdapter::QtToPL(tr("Scene")), "Scene");
	sFileFilter += ";;";
	sFileFilter += ConstructFileFilter::ByScriptLanguages(QtStringAdapter::QtToPL(tr("Script")));

	// Open a file dialog were the user can choose a filename
	const QString sQFilename = QFileDialog::getOpenFileName(GetFrontendMainWindow(), "", "", QtStringAdapter::PLToQt(sFileFilter));

	// Filename chosen?
	if (sQFilename.length())
		m_pApplication->LoadResource(QtStringAdapter::QtToPL(sQFilename));
}

void Gui::QtSlotExit()
{
	// Shut down the application
	m_pApplication->Exit(0);
}

void Gui::QtSlotMenuCameraAboutToShow()
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

void Gui::QtSlotMenuWindowAboutToShow()
{
	// Window Qt menu there?
	if (m_pQMenuWindow) {
		// Clear the previous content - this is not performance critical so there's no reason to implement a
		// more complex solution like e.g. updating the menu entries as soon as there's a change within the scene
		m_pQMenuWindow->clear();
		if (m_pQActionGroupWindow)
			delete m_pQActionGroupWindow;
		m_pQActionGroupWindow = new QActionGroup(GetFrontendMainWindow());
		m_pQActionGroupWindow->setExclusive(false);
		connect(m_pQActionGroupWindow, SIGNAL(selected(QAction*)), this, SLOT(QtSlotSelectedWindow(QAction*)));

		// Automatically fill the Qt window menu by using RTTI information
		FillMenuWindowRec(*m_pQMenuWindow, "PLFrontendQt::DockWidget");
	}
}

void Gui::QtSlotSelectedWindow(QAction *pQAction)
{
	// Get the Qt main window
	FrontendMainWindow *pFrontendMainWindow = GetFrontendMainWindow();
	if (pFrontendMainWindow) {
		// Get the chosen dock widget RTTI class...
		const Class *pClass = ClassManager::GetInstance()->GetClass(QtStringAdapter::QtToPL(pQAction->data().toString()));
		if (pClass) {
			// [TODO] Avoid instancing a RTTI dock widget which is currently just hidden
			// [TODO] Avoid instancing one RTTI dock widget multiple times

			// ... and create an instance of it
			DockWidget *pDockWidget = reinterpret_cast<DockWidget*>(pClass->Create(Params<Object*, QWidget*>(pFrontendMainWindow)));
		}
	}
}
