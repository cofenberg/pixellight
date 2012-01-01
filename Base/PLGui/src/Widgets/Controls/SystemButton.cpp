/*********************************************************\
 *  File: SystemButton.cpp                               *
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
#include <PLGraphics/Color/Color4.h>
#include "PLGui/Themes/Theme.h"
#include "PLGui/Gui/Resources/Timer.h"
#include "PLGui/Widgets/Controls/SystemButton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
namespace PLGui {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(SystemButton)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SystemButton::SystemButton(Widget *pParent) : AbstractButton(pParent),
	SystemCommand(this),
	m_nSystemCommand(CommandRestore)
{
	// Don't draw a background
	SetBackgroundColor(Color4::Transparent);

	// Don't accept keyboard focus
	SetFocusStyle(NoFocus);
}

/**
*  @brief
*    Destructor
*/
SystemButton::~SystemButton()
{
}

/**
*  @brief
*    Get widget state
*/
uint32 SystemButton::GetWidgetState() const
{
	// Get widget state
	uint32 nWidgetState = 0;
	if (IsEnabled())									nWidgetState |= WidgetEnabled;
	if (GetParent() ? GetParent()->IsActive() : true)	nWidgetState |= WidgetActive;
	if (HasFocus())										nWidgetState |= WidgetFocus;
	if (IsMouseOver())									nWidgetState |= WidgetMouseOver;
	if (IsPressed())									nWidgetState |= WidgetPressed;

	// Return state
	return nWidgetState;
}

/**
*  @brief
*    Get system command that the button represents
*/
ESystemCommand SystemButton::GetSystemCommand() const
{
	// Return system command
	return m_nSystemCommand;
}

/**
*  @brief
*    Set system command that the button represents
*/
void SystemButton::SetSystemCommand(ESystemCommand nSystemCommand)
{
	// Set system command
	m_nSystemCommand = nSystemCommand;
}


//[-------------------------------------------------------]
//[ Private virtual AbstractButton functions              ]
//[-------------------------------------------------------]
void SystemButton::OnButtonClicked()
{
	// Execute system command
	Widget *pWidget = GetParent();
	if (m_nSystemCommand == CommandMinimize) {
		pWidget->SetWindowState(StateMinimized);
	} else if (m_nSystemCommand == CommandMaximize) {
		pWidget->SetWindowState(StateMaximized);
	} else if (m_nSystemCommand == CommandRestore) {
		pWidget->SetWindowState(StateNormal);
	} else if (m_nSystemCommand == CommandClose) {
		pWidget->Close();
	}
}


//[-------------------------------------------------------]
//[ Private virtual WidgetFunctions functions             ]
//[-------------------------------------------------------]
void SystemButton::OnDraw(Graphics &cGraphics)
{
	// Draw system button
	m_pTheme->DrawSystemButton(cGraphics, Vector2i::Zero, GetSystemCommand(), GetWidgetState());
}

Vector2i SystemButton::OnPreferredSize(const Vector2i &vRefSize) const
{
	// Return static size
	return Vector2i(16, 16);
}

void SystemButton::OnMouseEnter()
{
	// Call base function
	AbstractButton::OnMouseEnter();

	// Redraw button
	Redraw();
}

void SystemButton::OnMouseLeave()
{
	// Call base function
	AbstractButton::OnMouseLeave();

	// Redraw button
	Redraw();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
