/*********************************************************\
 *  File: OSWindowMacOSX.mm                              *
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
	m_pFrontendOS(&cFrontendOS)
{
	// Tell the frontend about this instance at once because it may already be required during frontend life cycle initialization
	m_pFrontendOS->m_pOSWindow = this;

	// [TODO] Create the OS window

	// Do the frontend life cycle thing - start
	m_pFrontendOS->OnStart();

	// If the window is not visible yet, make it visible right now
	MakeVisible();
}

/**
*  @brief
*    Destructor
*/
OSWindowMacOSX::~OSWindowMacOSX()
{
}

/**
*  @brief
*    If the window is not visible yet, make it visible right now
*/
void OSWindowMacOSX::MakeVisible()
{
	// [TODO] Implement me
}


//[-------------------------------------------------------]
//[ Private virtual OSWindow functions                    ]
//[-------------------------------------------------------]
handle OSWindowMacOSX::GetNativeWindowHandle() const
{
	// [TODO] Implement me
	return NULL_HANDLE;
}

void OSWindowMacOSX::Redraw()
{
	// [TODO] Implement me
}

bool OSWindowMacOSX::Ping()
{
	// [TODO] Implement me

	// Done
	return true;
}

String OSWindowMacOSX::GetTitle() const
{
	// [TODO] Implement me

	// Error!
	return "";
}

void OSWindowMacOSX::SetTitle(const String &sTitle)
{
	// [TODO] Implement me
}

int OSWindowMacOSX::GetX() const
{
	// [TODO] Implement me

	// Error!
	return 0;
}

int OSWindowMacOSX::GetY() const
{
	// [TODO] Implement me

	// Error!
	return 0;
}

uint32 OSWindowMacOSX::GetWidth() const
{
	// [TODO] Implement me

	// Error!
	return 0;
}

uint32 OSWindowMacOSX::GetHeight() const
{
	// [TODO] Implement me

	// Error!
	return 0;
}

void OSWindowMacOSX::SetPositionSize(int nX, int nY, uint32 nWidth, uint32 nHeight)
{
	// [TODO] Implement me
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
	return false;
}

int OSWindowMacOSX::GetMousePositionX() const
{
	// [TODO] Implement me

	// Error, the mouse cursor is currently not over this window
	return -1;
}

int OSWindowMacOSX::GetMousePositionY() const
{
	// [TODO] Implement me

	// Error, the mouse cursor is currently not over this window
	return -1;
}

bool OSWindowMacOSX::IsMouseVisible() const
{
	// [TODO] Implement me
	return false;
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
