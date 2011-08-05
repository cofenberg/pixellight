/*********************************************************\
 *  File: Frontend.cpp                                   *
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
#include <QtGui/qapplication.h>
#include <PLCore/String/UTF8Tools.h>
#include "PLFrontendQt/FrontendMainWindow.h"
#include "PLFrontendQt/Frontend.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Frontend)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Frontend::Frontend() :
	m_cFrontend(*this),
	m_pMainWindow(nullptr)
{
	// Do the frontend lifecycle thing - let the world know that we have been created
	OnCreate();
}

/**
*  @brief
*    Destructor
*/
Frontend::~Frontend()
{
	// Do the frontend lifecycle thing - let the world know that we're going to die
	OnDestroy();
}

/**
*  @brief
*    Get main window
*/
QWidget *Frontend::GetMainWindow() const
{
	// Return pointer to main window
	return m_pMainWindow;
}

/**
*  @brief
*    Set main window
*/
void Frontend::SetMainWindow(QWidget *pMainWindow)
{
	// Set pointer to main window
	m_pMainWindow = pMainWindow;
}


//[-------------------------------------------------------]
//[ Protected virtual PLCore::FrontendImpl functions      ]
//[-------------------------------------------------------]
int Frontend::Run(const String &sExecutableFilename, const Array<String> &lstArguments, const String &sApplicationClass)
{
	// Get traditional C-arguments
	const int argc = 1 + lstArguments.GetNumOfElements();
	char **argv = new char *[argc];
	{ // Fill C-arguments
		{ // First one is the executable filename
			const char *pszExecutableFilename = sExecutableFilename.GetUTF8();
			const uint32 nNumOfExecutableFilenameBytes = UTF8Tools::GetNumOfStringBytes(pszExecutableFilename);
			argv[0] = new char[nNumOfExecutableFilenameBytes + 1];	// +1 for the terminating zero
			MemoryManager::Copy(argv[0], pszExecutableFilename, nNumOfExecutableFilenameBytes);
			argv[0][nNumOfExecutableFilenameBytes] = '\0';	// The terminating zero
		}

		// ... and now the arguments...
		for (uint32 i=0; i<lstArguments.GetNumOfElements(); i++) {
			const char *pszArgument = lstArguments[i].GetUTF8();
			const uint32 nNumOfArgumentBytes = UTF8Tools::GetNumOfStringBytes(pszArgument);
			argv[i + 1] = new char[nNumOfArgumentBytes + 1];	// +1 for the terminating zero
			MemoryManager::Copy(argv[i + 1], pszArgument, nNumOfArgumentBytes);
			argv[i + 1][nNumOfArgumentBytes] = '\0';	// The terminating zero
		}
	}

	// Run the frontend
	const int nResult = Run(argc, argv, sApplicationClass);

	// Cleanup traditional C-arguments
	for (int i=0; i<argc; i++)
		delete argv[i];
	delete [] argv;

	// Done
	return nResult;
}

int Frontend::Run(int argc, char **argv, const String &sApplicationClass)
{
	// Create the Qt application instance on the C runtime stack
	QApplication cQApplication(argc, argv);

	// Create and set the main window
	new FrontendMainWindow(*this);

	// Run the Qt application
	return cQApplication.exec();
}

handle Frontend::GetNativeWindowHandle() const
{
	if (m_pMainWindow) {
		// Get window system identifier of the widget
		return reinterpret_cast<handle>(m_pMainWindow->window() ? m_pMainWindow->window()->winId() : m_pMainWindow->winId());
	} else {
		// There's no native window handle
		return NULL_HANDLE;
	}
}

void Frontend::Redraw()
{
	// Ask Qt politly to update (and repaint) the widget
	if (m_pMainWindow)
		m_pMainWindow->update();
}

void Frontend::Ping()
{
	// Check if there are system messages waiting (non-blocking)
	if (QApplication::instance()->hasPendingEvents()) {
		// Process all waiting messages
		QApplication::instance()->processEvents();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
