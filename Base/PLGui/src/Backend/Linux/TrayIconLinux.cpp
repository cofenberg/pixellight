/*********************************************************\
 *  File: TrayIconLinux.cpp                              *
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
#include "PLGui/Gui/Gui.h"
#include "PLGui/Gui/TrayIcon.h"
#include "PLGui/Backend/Linux/GuiLinux.h"
#include "PLGui/Backend/Linux/TrayIconLinux.h"
#include "PLGui/Backend/Linux/TrayIconWidgetLinux.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLGui {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TrayIconLinux::TrayIconLinux(TrayIcon &cTrayIcon) : TrayIconImpl(cTrayIcon),
	m_pDisplay(static_cast<GuiLinux*>(cTrayIcon.GetGui()->GetImpl())->GetDisplay()),
	m_pWidget(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
TrayIconLinux::~TrayIconLinux()
{
}


//[-------------------------------------------------------]
//[ Private virtual TrayIconImpl functions                ]
//[-------------------------------------------------------]
void TrayIconLinux::CreateTrayIcon()
{
	// Create tray icon widget
	m_pWidget = new TrayIconWidgetLinux();
	m_pWidget->SetTrayIcon(m_pTrayIcon);
	m_pWidget->SetIcon(m_pTrayIcon->GetIcon());
	m_pWidget->EmbedIntoSysTray();
}

void TrayIconLinux::DestroyTrayIcon()
{
	// Destroy window
	if (m_pWidget) {
		m_pWidget->Destroy();
		m_pWidget = nullptr;
	}
}

void TrayIconLinux::SetVisible(bool bVisible)
{
	// Tray icon created?
	if (m_pWidget) {
		// Set visibility
		m_pWidget->SetVisible(bVisible);
	}
}

void TrayIconLinux::Update()
{
}

void TrayIconLinux::ShowNotification(const String &sTitle, const String &sText)
{
	// Tray icon created?
	if (m_pWidget) {
		// Show notification
		m_pWidget->ShowNotification(sTitle, sText);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
