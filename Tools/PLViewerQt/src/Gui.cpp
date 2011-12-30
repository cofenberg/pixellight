/*********************************************************\
 *  File: Gui.cpp                                        *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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
	#include <QtGui/qmenubar.h>
	#include <QtGui/qfiledialog.h>
PL_WARNING_POP
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneQueries/SQByClassName.h>
#include <PLFrontendQt/Frontend.h>
#include <PLFrontendQt/QtStringAdapter.h>
#include <PLFrontendQt/FrontendMainWindow.h>
#include <PLFrontendQt/ConstructFileFilter.h>
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
	m_pQMenuCamera(nullptr),
	m_pQActionGroupCamera(nullptr)
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
		// more complex solution e.g. updating the menu entries as soon as there's a change within the scene
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
