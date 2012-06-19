/*********************************************************\
 *  File: Connection.cpp                                 *
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
#include "PLInput/Input/Controller.h"
#include "PLInput/Input/Controls/Control.h"
#include "PLInput/Input/Controls/Button.h"
#include "PLInput/Input/Controls/Axis.h"
#include "PLInput/Input/Controls/LED.h"
#include "PLInput/Input/Controls/Effect.h"
#include "PLInput/Input/Connection/Connection.h"


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
Connection::Connection(Control *pInput, Control *pOutput, float fScale) :
	m_pInput(pInput),
	m_pOutput(pOutput),
	m_bValid(false),
	m_fScale(fScale)
{
	// Check if both controls are valid
	if (pInput && pOutput && pInput != pOutput) {
		// Check that the controls are either both input or both output controls
		if (pInput->IsInputControl() == pOutput->IsInputControl()) {
			// Check that the output control does *not* belong to a device
			if (pOutput->GetController()->GetType() != ControllerDevice) {
				// Connection is valid (can be changed by derived classes that have additional tests)
				m_bValid = true;
			}
		}
	}
}

/**
*  @brief
*    Destructor
*/
Connection::~Connection()
{
}

/**
*  @brief
*    Get input control
*/
Control *Connection::GetInputControl() const
{
	// Return controller
	return m_pInput;
}

/**
*  @brief
*    Get output control
*/
Control *Connection::GetOutputControl() const
{
	// Return controller
	return m_pOutput;
}

/**
*  @brief
*    Check if connection is value
*/
bool Connection::IsValid() const
{
	// Return valid-flag
	return m_bValid;
}


//[-------------------------------------------------------]
//[ Public virtual Connection functions                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Pass value from input to output
*/
void Connection::PassValue()
{
	// Check if connection is valid
	if (m_bValid) {
		// Pass value
		switch (m_pInput->GetType()) {
			case ControlButton:
				static_cast<Button*>(m_pOutput)->SetPressed(static_cast<Button*>(m_pInput)->IsPressed());
				break;

			case ControlAxis:
			{
				Axis *pInputAxis = static_cast<Axis*>(m_pInput);
				if (m_fScale != 1.0f)
					static_cast<Axis*>(m_pOutput)->SetValue(pInputAxis->GetValue() * m_fScale, pInputAxis->IsValueRelative());
				else
					static_cast<Axis*>(m_pOutput)->SetValue(pInputAxis->GetValue(), pInputAxis->IsValueRelative());
				break;
			}

			case ControlUnknown:
			case ControlLED:
			case ControlEffect:
			default:
				// There's nothing to pass on
				break;
		}
	}
}

/**
*  @brief
*    Pass value backwards from output to input
*/
void Connection::PassValueBackwards()
{
	// Check if connection is valid
	if (m_bValid) {
		// Pass value
		switch (m_pOutput->GetType()) {
			case ControlLED:
				static_cast<LED*>(m_pInput)->SetLEDs(static_cast<LED*>(m_pOutput)->GetLEDs());
				break;

			case ControlEffect:
				static_cast<Effect*>(m_pInput)->SetValue(static_cast<Effect*>(m_pOutput)->GetValue());
				break;

			case ControlUnknown:
			case ControlButton:
			case ControlAxis:
			default:
				// There's nothing to pass backwards
				break;
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
