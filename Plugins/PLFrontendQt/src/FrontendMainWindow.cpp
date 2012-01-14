/*********************************************************\
 *  File: FrontendMainWindow.cpp                         *
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
#include <QtCore/QUrl>
#include <QtCore/qcoreevent.h>
#include <QtGui/qevent.h>
#include <QtGui/QBoxLayout>
#if defined(Q_WS_WIN)
	#include <PLCore/PLCoreWindowsIncludes.h>
	#include <QtGui/qwindowdefs_win.h>	// For QWidget::winEvent() usage
#endif
#include <PLCore/Tools/Timing.h>
#include <PLCore/Frontend/Frontend.h>
#include <PLCore/Frontend/FrontendContext.h>
#include "PLFrontendQt/Frontend.h"
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/FrontendRenderWindow.h"
#include "PLFrontendQt/DockWidget/DockWidgetManager.h"
#include "PLFrontendQt/FrontendMainWindow.h"
#if defined(Q_WS_X11)
#include <X11/Xlib.h> // For the X11 event type definitions
// undefine some identifier their names are also used by other headers
#undef Bool
#undef None
// put the X11 defines for FocusIn/Out event type into a enum and undefine the defines because the names are also used as names for enum values by Qt QEvent
enum X11
{
	FocusInX11 = FocusIn,
	FocusOutX11 = FocusOut
};
#undef FocusIn
#undef FocusOut
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the dock widget manager of this main window
*/
DockWidgetManager &FrontendMainWindow::GetDockWidgetManager()
{
	// If required, create the dock widget manager of this main window right now
	if (!m_pDockWidgetManager)
		m_pDockWidgetManager = new DockWidgetManager(this);

	// Return the dock widget manager of this main window
	return *m_pDockWidgetManager;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FrontendMainWindow::FrontendMainWindow(Frontend &cFrontendQt) :
	m_pFrontendQt(&cFrontendQt),
	m_bVisible(false),
	m_nWindowRedrawTimerID(startTimer(10)),	// An interval of 10 milliseconds should be enough
	m_pDockWidgetManager(nullptr)
{
	// Tell the frontend about this instance at once because it may already be required during frontend life cycle initialization
	m_pFrontendQt->SetMainWindow(this);
	// Create a dump QWidget as the central widget for the QMainWindow and add the FrontendRenderWindow as an child of this widget
	// This solves, in conjunction with the change that a DockWidget can receive input focus, the "problem" that the "render window"
	// processes mouse move input event while a user drags a QDockwidget.
	// Note: The centralWidget of an QMainWindow becomes the input focus, when an docked QDockWidget gets dragged by the user.
	QWidget *central = new QWidget(this);
	central->setLayout(new QVBoxLayout);
	m_pRenderWidget = new FrontendRenderWindow(this);
	// Set focus policy to ClickFocus. Normaly a QWidget doesn't get input focus via mouse click on the widget itself.
	// With this policy the widget gets input focus when the user does an mous click while the cursor is in the widget area.
	m_pRenderWidget->setFocusPolicy(Qt::ClickFocus);
	central->layout()->addWidget(m_pRenderWidget);
	
	// Install an event filter onto the render window
	// The event filter will do the frontend pause/resume cycle when the render window gets/loose the input focus
	m_pRenderWidget->installEventFilter(this);

	// Set central widget
	setCentralWidget(central);

	// Set window title and size
	setWindowTitle(m_pFrontendQt->GetFrontend() ? QtStringAdapter::PLToQt(m_pFrontendQt->GetFrontend()->GetContext().GetName()) : "");
	resize(640, 480);

	// Drop events are enabled for this widget
	setAcceptDrops(true);

	// Do the frontend life cycle thing - start
	m_pFrontendQt->OnStart();

	// If the widget is not visible yet, make it visible right now
	MakeVisible();
}

bool FrontendMainWindow::eventFilter(QObject *pQObject, QEvent *pQEvent)
{
	if (pQObject == m_pRenderWidget)
	{
		if (pQEvent->type() == QEvent::FocusIn)
		{
			m_pFrontendQt->OnResume();
		}
		else if (pQEvent->type() == QEvent::FocusOut)
		{
			m_pFrontendQt->OnPause();
		}
	}
	return false;
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

	// Destroy the dock widget manager of this main window, if there's one
	if (m_pDockWidgetManager)
		delete m_pDockWidgetManager;
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

		// Show the widget
		show();

		// Activate the window by giving it the focus
		m_pRenderWidget->setFocus(Qt::ActiveWindowFocusReason);
	}
}


//[-------------------------------------------------------]
//[ Protected virtual QObject functions                   ]
//[-------------------------------------------------------]
void FrontendMainWindow::timerEvent(QTimerEvent *pQTimerEvent)
{
	if (pQTimerEvent->timerId() == m_nWindowRedrawTimerID) {
		// Is the frontend still running?
		if (m_pFrontendQt->GetFrontend() && m_pFrontendQt->GetFrontend()->IsRunning()) {
			// Check if we're allowed to perform an update right now
			if (PLCore::Timing::GetInstance()->Update()) {
				// Let the frontend update it's states (do this before drawing else, e.g. the first frame may have an unwanted content)
				m_pFrontendQt->OnUpdate();
			}

			// Ask Qt politely to update (and repaint) the widget
			update();
		} else {
			// The frontend is no longer running -> Close this Qt widget
			close();
		}
	}
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

#if defined(Q_WS_X11)
	// The linux part of the workaround for the problem described by the comment of the FrontendMainWindow::winEvent
	// Under Linux the toplevel window becomes an FocusOut event, when the user moves/resize the window via windowmanager frame
	bool FrontendMainWindow::x11Event(XEvent * x11Event)
	{
		switch (x11Event->type) {
			case FocusInX11:
				// Do the frontend life cycle thing - resume. Only when the render window has the input focus to avoid a double call to OnResume.
				// Because the frontend life cycle thing is also done when the render window itself gets/loose the input focus
				if(m_pRenderWidget->hasFocus())
				{
					m_pFrontendQt->OnResume();
				}
				break;

			case FocusOutX11:
				// Do the frontend life cycle thing - pause.  Only when the render window has the input focus to avoid a double call to OnPause.
				// Because the frontend life cycle thing is also done when the render window itself gets/loose the input focus
				if(m_pRenderWidget->hasFocus())
				{
					m_pFrontendQt->OnPause();
				}
				break;
		}

		// Let the event being handled by Qt
		return false;
	}
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
