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
#include <PLFrontendQt/Frontend.h>
#include <PLFrontendQt/QtStringAdapter.h>
#include <PLFrontendQt/FrontendMainWindow.h>
#include "Application.h"
#include "Gui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLFrontendQt;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Gui::Gui(Application &cApplication) :
	m_pApplication(&cApplication)
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
	Frontend *pFrontendQt = static_cast<Frontend*>(m_pApplication->GetFrontend().GetImpl());
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
			pQAction->setShortcut(cQMainWindow.tr("Ctrl+M"));
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
}

//[-------------------------------------------------------]
//[ Private Qt slots (MOC)                                ]
//[-------------------------------------------------------]
void Gui::QtSlotLoad()
{
	// Open a file dialog were the user can choose a filename
	// [TODO] Use the RTTI to fill the file filter
	const QString sQFilename = QFileDialog::getOpenFileName(GetFrontendMainWindow(), "", "", "Scenes (*.scene)");

	// Filename chosen?
	if (sQFilename.length())
		m_pApplication->LoadResource(QtStringAdapter::QtToPL(sQFilename));
}

void Gui::QtSlotExit()
{
	// Shut down the application
	m_pApplication->Exit(0);
}
