/*********************************************************\
 *  File: FrontendMainWindow.cpp                         *
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
#include <QtCore/qurl.h>
#include <QtCore/qcoreevent.h>
#include <QtGui/qevent.h>
#if defined(Q_WS_WIN)
	#include <PLCore/PLCoreWindowsIncludes.h>
	#include <QtGui/qwindowdefs_win.h>	// For QWidget::winEvent() usage
#endif
#include <PLCore/Tools/Timing.h>
#include <PLCore/Frontend/Frontend.h>
#include <PLCore/Frontend/FrontendContext.h>
#include "PLFrontendQt/Frontend.h"
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/FrontendMainWindow.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FrontendMainWindow::FrontendMainWindow(Frontend &cFrontendQt) : QMainWindow(nullptr, Qt::MSWindowsOwnDC),	// Same settings as used in Qt's QGLWidget
	m_pFrontendQt(&cFrontendQt),
	m_bVisible(false),
	m_nWindowRedrawTimerID(startTimer(10))	// An interval of 10 milliseconds should be enough
{
	// Tell the frontend about this instance at once because it may already be required during frontend life cycle initialization
	m_pFrontendQt->SetMainWindow(this);

	// Disable window system background to avoid "white flickering" caused by automatic overdraw
	// (same settings as used in Qt's QGLWidget)
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);

	// Now, there's still "black flickering" - in order to get rid of this we're not using any built-in paint engines of Qt
	// -> Overwrite the "QPaintDevice::paintEngine()"-method and just return a null pointer
	// -> Set the following attribute
	setAttribute(Qt::WA_OpaquePaintEvent, true);

	// ... at this point, we should be finally flicker-free...

	// Set window title and size
	setWindowTitle(m_pFrontendQt->GetFrontend() ? QtStringAdapter::PLToQt(m_pFrontendQt->GetFrontend()->GetContext().GetName()) : "");
	resize(640, 480);

	// Drop events are enabled for this widget
	setAcceptDrops(true);

	// Do the frontend life cycle thing - start
	m_pFrontendQt->OnStart();

	// If the widget is not visible yet, make it visible right now
	MakeVisible();

	// Activate the window by giving it the focus
	setFocus(Qt::ActiveWindowFocusReason);
}

/**
*  @brief
*    Destructor
*/
FrontendMainWindow::~FrontendMainWindow()
{
	// Do the frontend life cycle thing - stop
	m_pFrontendQt->OnStop();

	// Stop window redraw timer
	if (m_nWindowRedrawTimerID)
		killTimer(m_nWindowRedrawTimerID);
}

/**
*  @brief
*    If the widget is not visible yet, make it visible right now
*/
void FrontendMainWindow::MakeVisible()
{
	if (!m_bVisible) {
		// The widget is now considered to be visible
		m_bVisible = true;

		// Show the widget, but do not activate it right now
		show();
	}
}


//[-------------------------------------------------------]
//[ Protected virtual QObject functions                   ]
//[-------------------------------------------------------]
void FrontendMainWindow::timerEvent(QTimerEvent *pQTimerEvent)
{
	if (pQTimerEvent->timerId() == m_nWindowRedrawTimerID) {
		// Check if we're allowed to perform an update right now
		if (PLCore::Timing::GetInstance()->Update()) {
			// Let the frontend update it's states (do this before drawing else, e.g. the first frame may have an unwanted content)
			m_pFrontendQt->OnUpdate();
		}

		// Ask Qt politely to update (and repaint) the widget
		update();
	}
}


//[-------------------------------------------------------]
//[ Protected virtual QPaintDevice functions              ]
//[-------------------------------------------------------]
QPaintEngine *FrontendMainWindow::paintEngine() const
{
	#if defined(Q_WS_WIN)
		// We're not using any built-in paint engines of Qt ("flickering"-avoidance)
		return nullptr;
	#else
		// On Linux there's no "flickering"-issue and when returning a null pointer in here
		// "QPainter::begin: Paint device returned engine == 0, type: 1" will be written
		// into the console - all the time.

		// Call base implementation
		return QMainWindow::paintEngine();
	#endif
}


//[-------------------------------------------------------]
//[ Protected virtual QWidget functions                   ]
//[-------------------------------------------------------]
void FrontendMainWindow::keyPressEvent(QKeyEvent *pQKeyEvent)
{
	// Is it allowed to toggle the fullscreen mode using hotkeys? If so, toggle fullscreen right now? (Alt-Return or AltGr-Return)
	if (m_pFrontendQt->GetToggleFullscreenMode() && pQKeyEvent->key() == Qt::Key_Return && (pQKeyEvent->modifiers() & Qt::AltModifier)) {
		// Toggle fullscreen mode
		m_pFrontendQt->SetFullscreen(!m_pFrontendQt->IsFullscreen());
	}
}

void FrontendMainWindow::focusInEvent(QFocusEvent *)
{
	// Do the frontend life cycle thing - resume
	m_pFrontendQt->OnResume();
}

void FrontendMainWindow::focusOutEvent(QFocusEvent *)
{
	// Do the frontend life cycle thing - pause
	m_pFrontendQt->OnPause();
}

void FrontendMainWindow::paintEvent(QPaintEvent *)
{
	// Qt only calls this method if the draw area isn't null

	// Let the frontend draw into it's window
	m_pFrontendQt->OnDraw();
}

void FrontendMainWindow::resizeEvent(QResizeEvent *)
{
	// Inform that the window size has been changed
	m_pFrontendQt->OnSize();
}

void FrontendMainWindow::dragEnterEvent(QDragEnterEvent *pQDragEnterEvent)
{
	// We're open minded for everything
	pQDragEnterEvent->acceptProposedAction();
}

void FrontendMainWindow::dropEvent(QDropEvent *pQDropEvent)
{
	const QMimeData *pQMimeData = pQDropEvent->mimeData();
	if (pQMimeData) {
		// Loop through the provided list
		PLCore::Array<PLCore::String> lstFiles;
		QList<QUrl> lstUrls = pQMimeData->urls();
		lstFiles.Resize(lstUrls.size());
		for (int i=0; i<lstUrls.size(); i++)
			lstFiles[i] = QtStringAdapter::QtToPL(lstUrls.at(i).toString());

		// Inform the frontend
		m_pFrontendQt->OnDrop(lstFiles);
	}
}

#if defined(Q_WS_WIN)
	// Qt doesn't have a WM_EXITSIZEMOVE/WM_ENTERSIZEMOVE (MS Windows) equivalent - so we have to use the native stuff in here
	//   Background: When moving/sizing the window, the application will also be paused during this period (WM_EXITSIZEMOVE/WM_ENTERSIZEMOVE MS Windows events)...
	//               it's just annoying when you move or size a window and the controlled scene camera is spinning around while you do so...
	bool FrontendMainWindow::winEvent(MSG *message, long *result)
	{
		switch (message->message) {
			case WM_EXITSIZEMOVE:
				// Do the frontend life cycle thing - resume
				m_pFrontendQt->OnResume();
				return true;	// Stop the event being handled by Qt

			case WM_ENTERSIZEMOVE:
				// Do the frontend life cycle thing - pause
				m_pFrontendQt->OnPause();
				return true;	// Stop the event being handled by Qt
		}

		// Let the event being handled by Qt
		return false;
	}
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
