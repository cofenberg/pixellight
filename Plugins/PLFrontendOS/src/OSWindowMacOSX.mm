/*********************************************************\
 *  File: OSWindowMacOSX.mm                              *
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
#import <Cocoa/Cocoa.h>
#include <PLCore/Frontend/Frontend.h>
#include <PLCore/Frontend/FrontendContext.h>
#include "PLFrontendOS/Frontend.h"
#include "PLFrontendOS/OSWindowMacOSX.h"


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
OSWindowMacOSX::OSWindowMacOSX(Frontend &cFrontendOS) :
	m_pFrontendOS(&cFrontendOS),
	m_pNSApplication([[NSApplication alloc] init]),
	m_pNSWindow(nullptr)
{
	// Tell the frontend about this instance at once because it may already be required during frontend life cycle initialization
	m_pFrontendOS->m_pOSWindow = this;

	// Create NSWindow instance
	m_pNSWindow = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 640, 480)
									styleMask:(NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask)
									backing:NSBackingStoreBuffered
									defer:NO];

	// Set the window title
	SetTitle(m_pFrontendOS->GetFrontend() ? m_pFrontendOS->GetFrontend()->GetContext().GetName() : m_pFrontendOS->GetFrontend());

	// Do the frontend life cycle thing - start
	m_pFrontendOS->OnStart();

	// If the window is not visible yet, make it visible right now
	MakeVisible();
}

/*
*  @brief
*    Destructor
*/
OSWindowMacOSX::~OSWindowMacOSX()
{
	// Destroy the NSWindow implementation
	[static_cast<NSWindow*>(m_pNSWindow) release];

	// Destroy the NSApplication implementation
	[static_cast<NSApplication*>(m_pNSApplication) release];
}

/**
*  @brief
*    If the window is not visible yet, make it visible right now
*/
void OSWindowMacOSX::MakeVisible()
{
	// Get NSWindow instance
	NSWindow *pNSWindow = static_cast<NSWindow*>(m_pNSWindow);

	// Bring the NSWindow into the foreground
	[pNSWindow setLevel:NSMainMenuWindowLevel];

	// Make the NSWindow visible
	[pNSWindow makeKeyAndOrderFront:nil];
}


//[-------------------------------------------------------]
//[ Private virtual OSWindow functions                    ]
//[-------------------------------------------------------]
handle OSWindowMacOSX::GetNativeWindowHandle() const
{
	return reinterpret_cast<handle>(m_pNSWindow);
}

void OSWindowMacOSX::Redraw()
{
	// [TODO] Implement me
}

bool OSWindowMacOSX::Ping()
{
	// Process all waiting OS events (non-blocking)
	NSEvent *pNSEvent = nil;
	do {
		// Get waiting event
		pNSEvent = [NSApp nextEventMatchingMask:NSAnyEventMask untilDate:[NSDate distantPast] inMode:NSDefaultRunLoopMode dequeue:YES];

		// Process event
		[NSApp sendEvent: pNSEvent];
	}
	while (nil != pNSEvent);
}

String OSWindowMacOSX::GetTitle() const
{
	// Get the title of the NSWindow as NSString
	// [TODO] Memory: pNSString delete? The NSWindow::title documentation does not mention it
	const NSString *pNSString = [static_cast<NSWindow*>(m_pNSWindow) title];

	// Get a UTF8 representation of the NSWindow title
	// -> Memory: The documentation of NSString::UTF8String states that the UTF8 string the returned pointer is pointing to is automatically freed
	return String::FromUTF8([pNSString UTF8String]);
}

void OSWindowMacOSX::SetTitle(const String &sTitle)
{
	// Get the window title to set as NSString 
	NSString *pNSString = [NSString stringWithCString:sTitle.GetUTF8() encoding:NSUTF8StringEncoding];

	// Set the title of the NSWindow
	[static_cast<NSWindow*>(m_pNSWindow) setTitle: pNSString];

	// Release our NSString instance
	[pNSString release];
}

int OSWindowMacOSX::GetX() const
{
	// Get the x position of the NSWindow content area, meaning excluding the window border and title bar
	return [static_cast<NSWindow*>(m_pNSWindow) frame].origin.x;
}

int OSWindowMacOSX::GetY() const
{
	// Get the y position of the NSWindow content area, meaning excluding the window border and title bar
	return [static_cast<NSWindow*>(m_pNSWindow) frame].origin.y;
}

uint32 OSWindowMacOSX::GetWidth() const
{
	// Get the width of the NSWindow content area, meaning excluding the window border and title bar
	return [[static_cast<NSWindow*>(m_pNSWindow) contentView] frame].size.width;
}

uint32 OSWindowMacOSX::GetHeight() const
{
	// Get the width of the NSWindow content area, meaning excluding the window border and title bar
	return [[static_cast<NSWindow*>(m_pNSWindow) contentView] frame].size.height;
}

void OSWindowMacOSX::SetWindowPositionSize(int nX, int nY, uint32 nWidth, uint32 nHeight)
{
	const NSRect sNSRect = { nX, nY, nWidth, nHeight};
	[static_cast<NSWindow*>(m_pNSWindow) setFrame:sNSRect display:YES];
}

void OSWindowMacOSX::SetFullscreenAltTab(bool bAllowed)
{
	// [TODO] Implement me
}

void OSWindowMacOSX::SetFullscreen(bool bFullscreen)
{
	// [TODO] Implement me
}

void OSWindowMacOSX::RefreshFullscreen()
{
	// [TODO] Implement me
}

bool OSWindowMacOSX::IsMouseOver() const
{
	// [TODO] Implement me
	return true;
}

int OSWindowMacOSX::GetMousePositionX() const
{
	// Get NSWindow instance
	NSWindow *pNSWindow = static_cast<NSWindow*>(m_pNSWindow);

	// Get the mouse cursor position inside this window
	return [pNSWindow mouseLocationOutsideOfEventStream].x;
}

int OSWindowMacOSX::GetMousePositionY() const
{
	// Get NSWindow instance
	NSWindow *pNSWindow = static_cast<NSWindow*>(m_pNSWindow);

	// Get the mouse cursor position inside this window
	// -> Window origin is left/bottom, so we need to flip the y-axis
	return GetHeight() - [pNSWindow mouseLocationOutsideOfEventStream].y;
}

bool OSWindowMacOSX::IsMouseVisible() const
{
	// [TODO] Implement me
	return true;
}

void OSWindowMacOSX::SetMouseVisible(bool bVisible)
{
	// [TODO] Implement me
}

void OSWindowMacOSX::SetTrapMouse(bool bTrap)
{
	// [TODO] Implement me
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendOS
