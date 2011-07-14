/*********************************************************\
 *  File: TrayIcon.cpp                                   *
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
#include "PLGui/Backend/TrayIconImpl.h"
#include "PLGui/Gui/Gui.h"
#include "PLGui/Gui/TrayIcon.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TrayIcon::TrayIcon(Gui &cGui) :
	m_pGui(&cGui),
	m_pImpl(nullptr),
	m_bVisible(false),
	m_cIcon(*m_pGui)
{
}

/**
*  @brief
*    Destructor
*/
TrayIcon::~TrayIcon()
{
	// Delete tray icon implementation
	if (m_pImpl) {
		// Destroy tray icon
		m_pImpl->DestroyTrayIcon();

		// Delete implementation
		delete m_pImpl;
	}
}

/**
*  @brief
*    Get owner GUI
*/
Gui *TrayIcon::GetGui() const
{
	// Return GUI
	return m_pGui;
}

/**
*  @brief
*    Get implementation
*/
TrayIconImpl *TrayIcon::GetImpl() const
{
	// Return implementation
	return m_pImpl;
}

/**
*  @brief
*    Get visibility
*/
bool TrayIcon::IsVisible() const
{
	// Return visiblity-state
	return m_bVisible;
}

/**
*  @brief
*    Set visibility
*/
void TrayIcon::SetVisible(bool bVisible)
{
	// Set visiblity-state
	m_bVisible = bVisible;

	// Create implementation?
	if (m_pImpl == nullptr) {
		// We must have a valid GUI
		if (m_pGui) {
			// Create tray icon implementation
			m_pImpl = m_pGui->CreateTrayIconImpl(*this);

			// Create tray icon
			m_pImpl->CreateTrayIcon();
		}
	}

	// Call implementation
	if (m_pImpl) {
		m_pImpl->SetVisible(m_bVisible);
	}
}

/**
*  @brief
*    Get icon
*/
const Image &TrayIcon::GetIcon() const
{
	// Return icon
	return m_cIcon;
}

/**
*  @brief
*    Set icon
*/
void TrayIcon::SetIcon(const Image &cIcon)
{
	// Set icon
	m_cIcon = cIcon;

	// Call implementation
	if (m_pImpl) {
		m_pImpl->Update();
	}
}

/**
*  @brief
*    Get tooltip
*/
String TrayIcon::GetTooltip() const
{
	// Return tooltip
	return m_sTooltip;
}

/**
*  @brief
*    Set tooltip
*/
void TrayIcon::SetTooltip(const String &sTooltip)
{
	// Set tooltip
	m_sTooltip = sTooltip;

	// Call implementation
	if (m_pImpl) {
		m_pImpl->Update();
	}
}

/**
*  @brief
*    Show a notification text
*/
void TrayIcon::ShowNotification(const String &sTitle, const String &sText)
{
	// Call implementation
	if (m_pImpl) {
		m_pImpl->ShowNotification(sTitle, sText);
	}
}


//[-------------------------------------------------------]
//[ Public virtual TrayIcon functions                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the mouse is moved within the tray icon
*/
void TrayIcon::OnMouseMove(const Vector2i &vPos)
{
	// Call event
	EventMouseMove(vPos);
}

/**
*  @brief
*    Called when a mouse button is pressed
*/
void TrayIcon::OnMouseButtonDown(uint32 nButton, const Vector2i &vPos)
{
	// Call event
	EventMouseButtonDown(nButton, vPos);
}

/**
*  @brief
*    Called when a mouse button is released
*/
void TrayIcon::OnMouseButtonUp(uint32 nButton, const Vector2i &vPos)
{
	// Call event
	EventMouseButtonUp(nButton, vPos);
}

/**
*  @brief
*    Called when a mouse button is clicked
*/
void TrayIcon::OnMouseButtonClick(uint32 nButton, const Vector2i &vPos)
{
	// Call event
	EventMouseButtonClick(nButton, vPos);
}

/**
*  @brief
*    Called when a mouse button is double-clicked
*/
void TrayIcon::OnMouseButtonDoubleClick(uint32 nButton, const Vector2i &vPos)
{
	// Call event
	EventMouseButtonDoubleClick(nButton, vPos);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
