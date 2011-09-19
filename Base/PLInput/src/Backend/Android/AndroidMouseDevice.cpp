/*********************************************************\
 *  File: AndroidMouseDevice.cpp                         *
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
#include <android/input.h>
#include "PLInput/Input/Devices/Mouse.h"
#include "PLInput/Backend/Android/AndroidMouseDevice.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
AndroidMouseDevice::AndroidMouseDevice() :
	m_bTouched(false),
	m_fPreviousMousePositionX(0.0f),
	m_fPreviousMousePositionY(0.0f),
	m_fMousePositionX(0.0f),
	m_fMousePositionY(0.0f),
	m_bLeftMouseButton(false)
{
	// Destroy device implementation automatically
	m_bDelete = true;
}

/**
*  @brief
*    Destructor
*/
AndroidMouseDevice::~AndroidMouseDevice()
{
}

/**
*  @brief
*    Call this to process the next motion input event
*/
void AndroidMouseDevice::OnMotionInputEvent(const struct AInputEvent &cAMotionInputEvent)
{
	// Get the number of pointers of data contained in this event
	const size_t nAndroidPointerCount = AMotionEvent_getPointerCount(&cAMotionInputEvent);
	if (nAndroidPointerCount) {
		// Get the current X and Y coordinate of this event for the given pointer index
		m_fMousePositionX = AMotionEvent_getX(&cAMotionInputEvent, 0);
		m_fMousePositionY = AMotionEvent_getY(&cAMotionInputEvent, 0);

		// Get the combined motion event action code and pointer index
		const int32_t nAndroidAction = AMotionEvent_getAction(&cAMotionInputEvent);
		if ((nAndroidAction & AMOTION_EVENT_ACTION_MASK) == AMOTION_EVENT_ACTION_UP) {
			// The left mouse button is now no longer down
			m_bLeftMouseButton = false;

			// We're no longer touched
			m_bTouched = false;
		} else {
			// Touch started?
			if ((nAndroidAction & AMOTION_EVENT_ACTION_MASK) == AMOTION_EVENT_ACTION_DOWN) {
				m_fPreviousMousePositionX = m_fMousePositionX;
				m_fPreviousMousePositionY = m_fMousePositionY;

				// We're now touched
				m_bTouched = true;
			}

			// Get the current pressure of this event for the given pointer index, ranges from 0 (no pressure at all) to 1 (normal pressure)
			const float fPressure = AMotionEvent_getPressure(&cAMotionInputEvent, 0);
			if (fPressure > 0.3f) {
				// The left mouse button is now down
				m_bLeftMouseButton = true;
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Public virtual UpdateDevice functions                 ]
//[-------------------------------------------------------]
void AndroidMouseDevice::Update()
{
	// Check if input device is valid
	if (m_pDevice) {
		// Get mouse device
		Mouse *pMouse = static_cast<Mouse*>(m_pDevice);

		// Are we currently touched?
		if (m_bTouched) {
			// Update axes
			const float fDeltaX = m_fMousePositionX - m_fPreviousMousePositionX;
			const float fDeltaY = m_fMousePositionY - m_fPreviousMousePositionY;
			m_fPreviousMousePositionX = m_fMousePositionX;
			m_fPreviousMousePositionY = m_fMousePositionY;
			if (pMouse->X.GetValue() != fDeltaX)
				pMouse->X.SetValue(fDeltaX, true);
			if (pMouse->Y.GetValue() != fDeltaY)
				pMouse->Y.SetValue(fDeltaY, true);
		}

		// Update buttons
		if (pMouse->Left.IsPressed() != m_bLeftMouseButton)
			pMouse->Left.SetPressed(m_bLeftMouseButton);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
