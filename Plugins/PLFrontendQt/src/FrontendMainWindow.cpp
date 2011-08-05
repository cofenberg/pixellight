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
#include <QtCore/qcoreevent.h>
#if defined(Q_WS_WIN)
	#include <PLCore/PLCoreWindowsIncludes.h>
	#include <QtGui/qwindowdefs_win.h>	// For QWidget::winEvent() usage
#endif
#include "PLFrontendQt/Frontend.h"
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
	m_nWindowRedrawTimerID(startTimer(10))	// An interval of 10 milliseconds should be enough
{
	// Tell the frontend about this instance at once because it may already be required during frontend lifecycle initialization
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

	// Set window size
	resize(640, 480);

	// Show the window, but do not activate it right now
	show();

	// Do the frontend lifecycle thing - start
	m_pFrontendQt->OnStart();

	// Activate the window by giving it the focus
	setFocus(Qt::ActiveWindowFocusReason);
}

/**
*  @brief
*    Destructor
*/
FrontendMainWindow::~FrontendMainWindow()
{
	// Do the frontend lifecycle thing - stop
	m_pFrontendQt->OnStop();

	// Stop window redraw timer
	if (m_nWindowRedrawTimerID) {
		killTimer(m_nWindowRedrawTimerID);
		m_nWindowRedrawTimerID = 0;
	}
}


//[-------------------------------------------------------]
//[ Protected virtual QObject functions                   ]
//[-------------------------------------------------------]
void FrontendMainWindow::timerEvent(QTimerEvent *pQTimerEvent)
{
	if (pQTimerEvent->timerId() == m_nWindowRedrawTimerID) {
		// Ask Qt politly to update (and repaint) the widget
		update();
	}
}


//[-------------------------------------------------------]
//[ Protected virtual QPaintDevice functions              ]
//[-------------------------------------------------------]
QPaintEngine *FrontendMainWindow::paintEngine() const
{
	// We're not using any built-in paint engines of Qt ("flickering"-avoidance)
	return nullptr;
}


//[-------------------------------------------------------]
//[ Protected virtual QWidget functions                   ]
//[-------------------------------------------------------]
void FrontendMainWindow::focusInEvent(QFocusEvent *)
{
	// Do the frontend lifecycle thing - resume
	m_pFrontendQt->OnResume();
}

void FrontendMainWindow::focusOutEvent(QFocusEvent *)
{
	// Do the frontend lifecycle thing - pause
	m_pFrontendQt->OnPause();
}

void FrontendMainWindow::paintEvent(QPaintEvent *)
{
	// [TODO] Update stuff
	m_pFrontendQt->OnDraw();
}

#if defined(Q_WS_WIN)
	// Qt doesn't have a WM_EXITSIZEMOVE/WM_ENTERSIZEMOVE (MS Windows) equivalent - so we have to use the native stuff in here
	//   Background: When moving/sizing the window, the application will also be paused during this period (WM_EXITSIZEMOVE/WM_ENTERSIZEMOVE MS Windows events)...
	//               it's just annyoing when you move or size a window and the controlled scene camera is spinning around while you do so...
	bool FrontendMainWindow::winEvent(MSG *message, long *result)
	{
		switch (message->message) {
			case WM_EXITSIZEMOVE:
				// Do the frontend lifecycle thing - resume
				m_pFrontendQt->OnResume();
				return true;	// Stop the event being handled by Qt

			case WM_ENTERSIZEMOVE:
				// Do the frontend lifecycle thing - pause
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
