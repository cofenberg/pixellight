/*********************************************************\
 *  File: AbstractButton.cpp                             *
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
#include "PLGui/Gui/Base/Keys.h"
#include "PLGui/Widgets/Base/AbstractButton.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLGui {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(AbstractButton)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
AbstractButton::AbstractButton(Widget *pParent) : Widget(pParent),
	Text(this),
	ImageName(this),
	ImageSize(this),
	Repeat(this),
	RepeatDelay(this),
	RepeatInterval(this),
	SlotOnTimer(this),
	m_cImage(*GetGui()),
	m_vImageSize(16, 16),
	m_bRepeat(false),
	m_nRepeatDelay(500),
	m_nRepeatInterval(500),
	m_bPressed(false),
	m_bMouseIn(false),
	m_bMousePressed(false),
	m_cTimer(*pParent->GetGui())
{
	// Connect timer event
	m_cTimer.EventFire.Connect(&SlotOnTimer);

	// We accept focus and tabstop
	SetFocusStyle(AcceptFocus);
	SetTabStop(true);
}

/**
*  @brief
*    Destructor
*/
AbstractButton::~AbstractButton()
{
}

/**
*  @brief
*    Get widget state
*/
uint32 AbstractButton::GetWidgetState() const
{
	// Get widget state
	uint32 nWidgetState = 0;
	if (IsEnabled())	nWidgetState |= WidgetEnabled;
	if (IsActive())		nWidgetState |= WidgetActive;
	if (HasFocus())		nWidgetState |= WidgetFocus;
	if (IsMouseOver())	nWidgetState |= WidgetMouseOver;
	if (IsPressed())	nWidgetState |= WidgetPressed;

	// Return state
	return nWidgetState;
}

/**
*  @brief
*    Get button text
*/
String AbstractButton::GetText() const
{
	// Return text
	return m_sText;
}

/**
*  @brief
*    Set button text
*/
void AbstractButton::SetText(const String &sText)
{
	// Set text
	m_sText = sText;
}

/**
*  @brief
*    Get image
*/
const Image &AbstractButton::GetImage() const
{
	// Return image
	return m_cImage;
}

/**
*  @brief
*    Set image
*/
void AbstractButton::SetImage(const Image &cImage)
{
	// Set image
	m_cImage = cImage;
}

/**
*  @brief
*    Get image filename
*/
String AbstractButton::GetImageName() const
{
	// Return image filename
	return m_cImage.GetFilename();
}

/**
*  @brief
*    Set image filename
*/
void AbstractButton::SetImageName(const String &sImage)
{
	// Load image
	SetImage(Image(*GetGui(), sImage));
}

/**
*  @brief
*    Get image size
*/
const Vector2i &AbstractButton::GetImageSize() const
{
	// Return image size
	return m_vImageSize;
}

/**
*  @brief
*    Set image size
*/
void AbstractButton::SetImageSize(const Vector2i &vSize)
{
	// Set image size
	m_vImageSize = vSize;
}

/**
*  @brief
*    Get repeat-mode
*/
bool AbstractButton::GetRepeat() const
{
	// Return repeat-mode
	return m_bRepeat;
}

/**
*  @brief
*    Set repeat-mode
*/
void AbstractButton::SetRepeat(bool bRepeat)
{
	// Set repeat-mode
	m_bRepeat = bRepeat;
}

/**
*  @brief
*    Get repeat delay
*/
uint64 AbstractButton::GetRepeatDelay() const
{
	// Return repeat delay
	return m_nRepeatDelay;
}

/**
*  @brief
*    Set repeat delay
*/
void AbstractButton::SetRepeatDelay(uint64 nDelay)
{
	// Set repeat delay
	m_nRepeatDelay = nDelay;
}

/**
*  @brief
*    Get repeat interval
*/
uint64 AbstractButton::GetRepeatInterval() const
{
	// Return repeat interval
	return m_nRepeatInterval;
}

/**
*  @brief
*    Set repeat interval
*/
void AbstractButton::SetRepeatInterval(uint64 nInterval)
{
	// Set eturn repeat interval
	m_nRepeatInterval = nInterval;
}

/**
*  @brief
*    Returns whether the button is currently pressed or not
*/
bool AbstractButton::IsPressed() const
{
	// Return pressed-flag
	return m_bPressed;
}


//[-------------------------------------------------------]
//[ Private virtual AbstractButton functions              ]
//[-------------------------------------------------------]
void AbstractButton::OnButtonPressed()
{
}

void AbstractButton::OnButtonReleased()
{
}

void AbstractButton::OnButtonClicked()
{
}


//[-------------------------------------------------------]
//[ Private virtual Widget functions                      ]
//[-------------------------------------------------------]
void AbstractButton::OnDisable()
{
	// Deactivate timer
	if (m_cTimer.IsActive()) m_cTimer.Stop();

	// Update states
	m_bPressed      = false;
	m_bMouseIn      = false;
	m_bMousePressed = false;
}

void AbstractButton::OnGetFocus()
{
	// Redraw window
	Redraw();
}

void AbstractButton::OnLooseFocus()
{
	// Redraw window
	Redraw();
}

void AbstractButton::OnMouseEnter()
{
	// If mouse is pressed, press button
	if (IsEnabled() && m_bMousePressed) PressButton();

	// Mouse is inside the button now
	m_bMouseIn = true;
}

void AbstractButton::OnMouseLeave()
{
	// Release button
	if (m_bPressed) ReleaseButton(false);

	// Mouse is outside the button now
	m_bMouseIn = false;
}

void AbstractButton::OnMouseMove(const Vector2i &vPos)
{
	// If the mouse button is pressed, we have captured the mouse and don't get enter/leave messages
	if (m_bMousePressed) {
		// Check if the mouse is inside the button area
		if (vPos.x < 0 || vPos.y < 0 || vPos.x > GetSize().x || vPos.y > GetSize().y) {
			// Send leave-message
			if (m_bMouseIn) OnMouseLeave();
		} else {
			// Send enter-message
			if (!m_bMouseIn) OnMouseEnter();
		}
	}
}

void AbstractButton::OnMouseButtonDown(uint32 nButton, const Vector2i &vPos)
{
	// Only do something if the button is enabled
	if (IsEnabled() && nButton == 0) {
		// Mouse button is pressed
		m_bMousePressed = true;
		SetCaptureMouse(true);

		// Press button
		PressButton();
	}
}

void AbstractButton::OnMouseButtonUp(uint32 nButton, const Vector2i &vPos)
{
	// Only do something if the button is enabled
	if (IsEnabled() && nButton == 0) {
		// Mouse button has been released
		m_bMousePressed = false;
		SetCaptureMouse(false);

		// Release button
		ReleaseButton(m_bMouseIn);
	}
}

void AbstractButton::OnKeyDown(uint32 nKey, uint32 nParameters)
{
	// Press button
	if (nKey == PLGUIKEY_SPACE) {
		PressButton();
	}
}

void AbstractButton::OnKeyUp(uint32 nKey, uint32 nParameters)
{
	// Release button
	if (nKey == PLGUIKEY_SPACE) {
		ReleaseButton(true);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Press button down
*/
void AbstractButton::PressButton()
{
	// Button changed?
	if (!m_bPressed) {
		// Button is pressed now
		m_bPressed = true;

		// Send pressed-event
		EventPressed();

		// Call virtual function
		OnButtonPressed();

		// Start auto-repeat
		if (m_bRepeat) {
			m_cTimer.Start(m_nRepeatDelay);
		}
	}

	// Redraw, please
	Redraw();
}

/**
*  @brief
*    Release button
*/
void AbstractButton::ReleaseButton(bool bClick)
{
	// Button changed?
	if (m_bPressed) {
		// Button has been released
		m_bPressed = false;

		// Send released-event
		EventReleased();

		// Call virtual function
		OnButtonReleased();

		// Stop auto-repeat
		m_cTimer.Stop();

		// Button clicked
		if (bClick) {
			// Send clicked-event
			EventClicked();

			// Call virtual function
			OnButtonClicked();
		}
	}

	// Redraw, please
	Redraw();
}

/**
*  @brief
*    Called when the timer has fired
*/
void AbstractButton::OnTimer()
{
	// Switch timer interval after first delay
  	if (m_cTimer.GetTimeout() != m_nRepeatInterval) {
		m_cTimer.Stop();
		m_cTimer.Start(m_nRepeatInterval);
	}

	// Send clicked-event
	EventClicked();

	// Call virtual function
	OnButtonClicked();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
