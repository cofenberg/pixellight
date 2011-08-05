/*********************************************************\
 *  File: OSWindowLinux.cpp                              *
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
#include "PLFrontendOS/Frontend.h"
#include "PLFrontendOS/OSWindowLinux.h"
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <cstring>

//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendOS {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
OSWindowLinux::OSWindowLinux(Frontend &cFrontendOS)
	: m_pFrontendOS(&cFrontendOS)
{
	// Tell the frontend about this instance at once because it may already be required during frontend lifecycle initialization
	m_pFrontendOS->m_pOSWindow = this;
	m_width = 640;
	m_height = 480;
	
	m_pDisplay = XOpenDisplay(NULL); 
	m_screen = DefaultScreen(m_pDisplay);
	m_pVisual = DefaultVisual(m_pDisplay,m_screen);
	m_depth  = DefaultDepth(m_pDisplay,m_screen);
	
	m_attributes.event_mask = ExposureMask | StructureNotifyMask | EnterWindowMask | LeaveWindowMask | FocusChangeMask | VisibilityChangeMask;

	m_window = XCreateWindow(m_pDisplay, XRootWindow(m_pDisplay,m_screen),
                   0,0, m_width,m_height,0, m_depth, InputOutput, m_pVisual,
                   CWEventMask ,&m_attributes);
	m_wmDelete = XInternAtom(m_pDisplay, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(m_pDisplay, m_window, &m_wmDelete, 1);
		
	XTextProperty windowName;
	windowName.value    = (unsigned char *) "PLFrontendOS_OSWindowLinuxX11";
	windowName.encoding = XA_STRING;
	windowName.format   = 8;
	windowName.nitems   = strlen((char *) windowName.value);
	
	XSetWMName(m_pDisplay, m_window, &windowName );
	XMapRaised(m_pDisplay, m_window);
	
	// Do the frontend lifecycle thing - start
	m_pFrontendOS->OnStart();
	// Connect Linux signals
//	signal(SIGINT,  CoreApplication::SignalHandler);
//	signal(SIGTERM, CoreApplication::SignalHandler);
}

/**
*  @brief
*    Destructor
*/
OSWindowLinux::~OSWindowLinux()
{
	// Check if the window has already been destroyed
	if (!m_bDestroyed) {
		// Send destroy message to window
		XDestroyWindow(m_pDisplay, m_window);
	}
}


//[-------------------------------------------------------]
//[ Private virtual OSWindow functions                    ]
//[-------------------------------------------------------]
handle OSWindowLinux::GetNativeWindowHandle() const
{
	// [TODO] handle is a int but Window (X11) is under linux an unsigned long
	return static_cast<handle>(m_window);
}

void OSWindowLinux::Redraw()
{
	if (m_window)
	{
		// Call directly OnDraw. It isn't needed to go via the X11 event loop to trigger an redraw
		// (if done via the X11 event loop, then the window reacts slow on close and Focus change events)
		m_pFrontendOS->OnDraw();
	}
}

bool OSWindowLinux::Ping()
{
	XEvent event;
	bool bQuit = false;
	while (XPending(m_pDisplay) > 0)
	{
		XNextEvent(m_pDisplay, &event);
		switch (event.type) {
			case Expose:
				if (event.xexpose.count != 0)
					break;
				//std::cout<<"onDraw"<<std::endl;
				m_pFrontendOS->OnDraw();
				break;
			case ConfigureNotify:
				if ((event.xconfigure.width != m_width) ||
						(event.xconfigure.height != m_height)) {
					m_width = event.xconfigure.width;
					m_height = event.xconfigure.height;
				}
				break;
			case DestroyNotify:
				// Do the frontend lifecycle thing - stop
				m_pFrontendOS->OnStop();

				// Mark window destroyed
				m_bDestroyed = true;
				m_window = 0;
				bQuit = True;
				break;
			case UnmapNotify:
			case FocusOut:
				m_pFrontendOS->OnPause();
				break;
			case MapNotify:
			case FocusIn:
				m_pFrontendOS->OnResume();
				break;
			case ClientMessage:
				if (event.xclient.data.l[0] == m_wmDelete) {
					bQuit = True;
				}
				break;
			default:
				break;
		}
	}
	return bQuit;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendOS
