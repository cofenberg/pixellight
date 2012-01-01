/*********************************************************\
 *  File: GuiNull.cpp                                    *
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
#include "PLGui/Backend/Null/WidgetNull.h"
#include "PLGui/Backend/Null/GraphicsNull.h"
#include "PLGui/Backend/Null/ImageNull.h"
#include "PLGui/Backend/Null/FontNull.h"
#include "PLGui/Backend/Null/CursorNull.h"
#include "PLGui/Backend/Null/TrayIconNull.h"
#include "PLGui/Backend/Null/ClipBoardNull.h"
#include "PLGui/Backend/Null/GuiNull.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
GuiNull::GuiNull(Gui *pGui) : GuiImpl(pGui)
{
}

/**
*  @brief
*    Destructor
*/
GuiNull::~GuiNull()
{
}


//[-------------------------------------------------------]
//[ Public virtual GuiImpl functions                      ]
//[-------------------------------------------------------]
bool GuiNull::HasPendingMessages()
{
	// Not implemented
	return false;
}

void GuiNull::ProcessMessage()
{
	// Not implemented
}

void GuiNull::PostMessage(const GuiMessage &cMessage)
{
	// Not implemented
}

void GuiNull::EnumerateScreens(List<Screen*> &lstScreens)
{
	// Not implemented
}

Vector2i GuiNull::GetScreenSize() const
{
	// Not implemented
	return Vector2i::Zero;
}

bool GuiNull::HasTaskbar()
{
	// Not implemented
	return false;
}

void GuiNull::SetMouseVisible(bool bVisible)
{
	// Not implemented
}

void GuiNull::ListFonts(List<FontInfo> &lstFonts) const
{
	// Not implemented
}

WidgetImpl *GuiNull::CreateWidgetImpl(Widget &cWidget) const
{
	// Create a Null widget
	return new WidgetNull(cWidget);
}

GraphicsImpl *GuiNull::CreateGraphicsImpl(Graphics &cGraphics) const
{
	// Create a Null graphics object
	return new GraphicsNull(cGraphics);
}

ImageImpl *GuiNull::CreateImageImpl(Image &cImage) const
{
	// Create a Null image object
	return new ImageNull(cImage);
}

FontImpl *GuiNull::CreateFontImpl(Font &cFont) const
{
	// Create a Null font object
	return new FontNull(cFont);
}

CursorImpl *GuiNull::CreateCursorImpl(Cursor &cCursor) const
{
	// Create a Null cursor object
	return new CursorNull(cCursor);
}

TrayIconImpl *GuiNull::CreateTrayIconImpl(TrayIcon &cTrayIcon) const
{
	// Create a Null tray-icon object
	return new TrayIconNull(cTrayIcon);
}

ClipBoardImpl *GuiNull::CreateClipBoardImpl(ClipBoard &cClipBoard) const
{
	// Create a Null clipboard object
	return new ClipBoardNull(cClipBoard);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
