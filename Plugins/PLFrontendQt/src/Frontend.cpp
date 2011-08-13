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
	m_pMainWindow(nullptr),
	m_bToggleFullscreenMode(true),
	m_bFullscreenAltTab(true),
	m_bIsFullscreen(false),
	m_pQCursorBlank(nullptr),
	m_bMouseVisible(true)
{
}

/**
*  @brief
*    Destructor
*/
Frontend::~Frontend()
{
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
int Frontend::Run(const String &sExecutableFilename, const Array<String> &lstArguments)
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
	const int nResult = Run(argc, argv);

	// Cleanup traditional C-arguments
	for (int i=0; i<argc; i++)
		delete argv[i];
	delete [] argv;

	// Done
	return nResult;
}

int Frontend::Run(int argc, char **argv)
{
	// Create the Qt application instance on the C runtime stack
	QApplication cQApplication(argc, argv);

	// Set application icon
	cQApplication.setWindowIcon(QIcon(":/pl_icon.png"));

	// Create the mouse cursors
	m_pQCursorBlank = new QCursor(Qt::BlankCursor);

	// Create and set the main window
	new FrontendMainWindow(*this);

	// Run the Qt application
	const int nResult = cQApplication.exec();

	// Delete the mouse cursors
	delete m_pQCursorBlank;
	m_pQCursorBlank = nullptr;

	// Done
	return nResult;
}

handle Frontend::GetNativeWindowHandle() const
{
	if (m_pMainWindow) {
		// Get window system identifier of the widget
		return (handle)(m_pMainWindow->window() ? m_pMainWindow->window()->winId() : m_pMainWindow->winId());
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

uint32 Frontend::GetWidth() const
{
	// Query the main window
	return m_pMainWindow ? m_pMainWindow->size().width() : 0;
}

uint32 Frontend::GetHeight() const
{
	// Query the main window
	return m_pMainWindow ? m_pMainWindow->size().height() : 0;
}

bool Frontend::GetToggleFullscreenMode() const
{
	return m_bToggleFullscreenMode;
}

void Frontend::SetToggleFullscreenMode(bool bToggleFullscreenMode)
{
	m_bToggleFullscreenMode = bToggleFullscreenMode;
}

bool Frontend::GetFullscreenAltTab() const
{
	return m_bFullscreenAltTab;
}

void Frontend::SetFullscreenAltTab(bool bAllowed)
{
	// Is there a state change?
	if (m_bFullscreenAltTab != bAllowed) {
		// Set the new state
		m_bFullscreenAltTab = bAllowed;

		// [TODO] Implement me
	}
}

bool Frontend::IsFullscreen() const
{
	return m_bIsFullscreen;
}

void Frontend::SetFullscreen(bool bFullscreen)
{
	// Is there a state change?
	if (m_bIsFullscreen != bFullscreen) {
		// Set the new state
		m_bIsFullscreen = bFullscreen;

		// [TODO] Enable/disable Alt-Tab

		// Inform that the fullscreen mode was changed
		OnFullscreenMode();

		// Set widget into fullscreen state?
		if (m_pMainWindow) {
			// ... just let Qt do the rest for us...
			if (bFullscreen)
				m_pMainWindow->showFullScreen();
			else
				m_pMainWindow->showNormal();
		}
	}
}

bool Frontend::IsMouseVisible() const
{
	return m_bMouseVisible;
}

void Frontend::SetMouseVisible(bool bVisible)
{
	// Check whether or not the mouse cursor is there
	if (m_pQCursorBlank) {
		// Backup the state
		m_bMouseVisible = bVisible;
		if (bVisible) {
			// This pops the last set cursor from the internal stack and restores the previous one
			// If no other cursor was on the stack then the default widget cursor is used
			// (see http://doc.qt.nokia.com/latest/qapplication.html#restoreOverrideCursor) 
			QApplication::restoreOverrideCursor();
		} else {
			// Set the mouse cursor
			// This pushes the cursor on an internal stack (see http://doc.qt.nokia.com/latest/qapplication.html#setOverrideCursor)
			QApplication::setOverrideCursor(*m_pQCursorBlank);
		}
	}
}

void Frontend::SetTrapMouse(bool bTrap)
{
	// [TODO] Implement me
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
