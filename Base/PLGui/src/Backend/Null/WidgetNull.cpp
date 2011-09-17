/*********************************************************\
 *  File: WidgetNull.cpp                                 *
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
#include "PLGui/Backend/Null/WidgetNull.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
WidgetNull::WidgetNull(Widget &cWidget) :
	WidgetImpl(cWidget)
{
}

/**
*  @brief
*    Destructor
*/
WidgetNull::~WidgetNull()
{
	// If not done already, destroy the widget
	Destroy();
}


//[-------------------------------------------------------]
//[ Public virtual WidgetImpl functions                   ]
//[-------------------------------------------------------]
void WidgetNull::CreateWidget()
{
	// Not implemented
}

void WidgetNull::CreateWrapperWidget(handle nNativeWindowHandle)
{
	// Not implemented
}

bool WidgetNull::IsDestroyed() const
{
	// Return destroyed-flag - not implemented
	return false;
}

void WidgetNull::Destroy()
{
	// Not implemented
}

handle WidgetNull::GetNativeWindowHandle() const
{
	// Return native window handle - not implemented
	return NULL_HANDLE;
}

void WidgetNull::SetParent(WidgetImpl *pParent)
{
	// Not implemented
}

bool WidgetNull::IsShowInTaskbar() const
{
	// Return taskbar flag - not implemented
	return false;
}

void WidgetNull::SetShowInTaskbar(bool bShowInTaskbar)
{
	// Not implemented
}

void WidgetNull::MoveToScreen(Screen &cScreen)
{
	// Not implemented
}

Vector2i WidgetNull::GetPos() const
{
	// Return position - not implemented
	return Vector2i::Zero;
}

void WidgetNull::SetPos(const Vector2i &vPos)
{
	// Not implemented
}

Vector2i WidgetNull::GetSize() const
{
	// Return size - not implemented
	return Vector2i::Zero;
}

void WidgetNull::SetSize(const Vector2i &vSize)
{
	// Not implemented
}

void WidgetNull::SetZPos(EZPos nZPos, Widget *pWidget)
{
	// Not implemented
}

bool WidgetNull::IsTopmost() const
{
	// Return topmost-state - not implemented
	return false;
}

void WidgetNull::SetTopmost(bool bTopmost)
{
	// Not implemented
}

EWindowState WidgetNull::GetWindowState() const
{
	// Not implemented
}

void WidgetNull::SetWindowState(EWindowState nWindowState)
{
	// Not implemented
}

void WidgetNull::SetTransparency(ETransparency nTransparency, const Color4 &cColor)
{
	// Not implemented
}

bool WidgetNull::IsVisible() const
{
	// Return visible-flag - not implemented
	return false;
}

void WidgetNull::SetVisible(bool bVisible)
{
	// Not implemented
}

bool WidgetNull::IsEnabled() const
{
	// Return enabled-flag - not implemented
	return false;
}

void WidgetNull::SetEnabled(bool bEnabled)
{
	// Not implemented
}

void WidgetNull::Activate()
{
	// Not implemented
}

void WidgetNull::SetFocus()
{
	// Not implemented
}

void WidgetNull::Redraw()
{
	// Not implemented
}

void WidgetNull::SetTrapMouse(bool bTrap)
{
	// Not implemented
}

void WidgetNull::SetCaptureMouse(bool bCapture)
{
	// Not implemented
}

uint32 WidgetNull::RegisterHotkey(uint32 nModKey, uint32 nKey)
{
	// Not implemented
	return 0;
}

void WidgetNull::UnregisterHotkey(uint32 nID)
{
	// Not implemented
}

void WidgetNull::SetTitle(const String &sTitle)
{
	// Not implemented
}

void WidgetNull::SetIcon(const Image &cIcon)
{
	// Not implemented
}

void WidgetNull::SetCursor(const Cursor &cCursor)
{
	// Not implemented
}

bool WidgetNull::GetMousePos(Vector2i &vPos)
{
	// Error - not implemented
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
