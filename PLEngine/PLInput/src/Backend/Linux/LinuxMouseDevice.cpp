/*********************************************************\
 *  File: LinuxMouseDevice.cpp                           *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLInput/Input/Devices/Mouse.h"
#include "PLInput/Backend/Linux/LinuxMouseDevice.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLInput {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
LinuxMouseDevice::LinuxMouseDevice(::Display *pDisplay) :
	m_pDisplay(pDisplay),
	m_nMouseX(0),
	m_nMouseY(0)
{
	// Destroy device implementation automatically
	m_bDelete = true;
}

/**
*  @brief
*    Destructor
*/
LinuxMouseDevice::~LinuxMouseDevice()
{
}


//[-------------------------------------------------------]
//[ Public virtual UpdateDevice functions                 ]
//[-------------------------------------------------------]
void LinuxMouseDevice::Update()
{
	// Check if input device is valid
	if (m_pDevice) {
		// Get mouse device
		Mouse *pMouse = (Mouse*)m_pDevice;

		// Get mouse state
		::Window 	 nRootWindow, nChildWindow;
		int 		 nRootX, nRootY, nChildX, nChildY;
		unsigned int nMask;
		XLockDisplay(m_pDisplay);
		XQueryPointer(m_pDisplay, DefaultRootWindow(m_pDisplay), &nRootWindow, &nChildWindow, &nRootX, &nRootY, &nChildX, &nChildY, &nMask);
		XUnlockDisplay(m_pDisplay);

		// Update axes
		int nDeltaX = nRootX - m_nMouseX;
		int nDeltaY = nRootY - m_nMouseY;
		m_nMouseX = nRootX;
		m_nMouseY = nRootY;
		if (pMouse->X.GetValue() != nDeltaX)
			pMouse->X.SetValue(nDeltaX);
		if (pMouse->Y.GetValue() != nDeltaY)
			pMouse->Y.SetValue(nDeltaY);

		// Update buttons
		bool bPressed = ((nMask & Button1Mask) != 0);
		if (pMouse->Left.IsPressed() != bPressed)
			pMouse->Left.SetPressed(bPressed);
		bPressed = ((nMask & Button2Mask) != 0);
		if (pMouse->Right.IsPressed() != bPressed)
			pMouse->Right.SetPressed(bPressed);
		bPressed = ((nMask & Button3Mask) != 0);
		if (pMouse->Middle.IsPressed() != bPressed)
			pMouse->Middle.SetPressed(bPressed);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
