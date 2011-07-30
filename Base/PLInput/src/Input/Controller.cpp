/*********************************************************\
 *  File: Controller.cpp                                 *
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
#include "PLInput/Input/Controller.h"
#include "PLInput/Input/Controls/Button.h"
#include "PLInput/Input/Connection/Connection.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLInput {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(Controller)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Controller::Controller(EControllerType nType, const String &sName, const String &sDescription) :
	Type(this),
	Name(this),
	Description(this),
	Active(this),
	m_nType(nType),
	m_sName(sName),
	m_sDescription(sDescription),
	m_bConfirmed(false),
	m_bActive(true),
	m_bChanged(false),
	m_nChar(0)
{
}

/**
*  @brief
*    Destructor
*/
Controller::~Controller()
{
	// Destroy all connections
	while (m_lstConnections.GetNumOfElements() > 0)
		Disconnect(m_lstConnections[0]);
}

/**
*  @brief
*    Get controller type
*/
EControllerType Controller::GetType() const
{
	// Return type
	return m_nType;
}

/**
*  @brief
*    Get controller name
*/
String Controller::GetName() const
{
	// Return name
	return m_sName;
}

/**
*  @brief
*    Get controller description
*/
String Controller::GetDescription() const
{
	// Return description
	return m_sDescription;
}

/**
*  @brief
*    Check if controller is active
*/
bool Controller::GetActive() const
{
	// Return active-flag
	return m_bActive;
}

/**
*  @brief
*    Activate or deactivate controller
*/
void Controller::SetActive(bool bActive)
{
	// Only virtual controller can be activated/deactivated
	if (m_nType == ControllerVirtual) {
		// Set active-state
		m_bActive = bActive;

		// Emit event
		SignalOnActivate(m_bActive);
	}
}

/**
*  @brief
*    Check if the controller's state has changed (for polling)
*/
bool Controller::HasChanged() const
{
	// Get state
	bool bChanged = m_bChanged;

	// Reset state
	m_bChanged = false;

	// Return state
	return bChanged;
}

/**
*  @brief
*    Get all controls of the controller
*/
const List<Control*> &Controller::GetControls() const
{
	// Return control list
	return m_lstControls;
}

/**
*  @brief
*    Get all buttons
*/
const List<Button*> &Controller::GetButtons() const
{
	// Initialize button list
	if (m_lstButtons.GetNumOfElements() == 0)
		InitControlList(ControlButton);

	// Return button list
	return m_lstButtons;
}

/**
*  @brief
*    Get all axes
*/
const List<Axis*> &Controller::GetAxes() const
{
	// Initialize axes list
	if (m_lstAxes.GetNumOfElements() == 0)
		InitControlList(ControlAxis);

	// Return axes list
	return m_lstAxes;
}

/**
*  @brief
*    Get control with a specific name
*/
Control *Controller::GetControl(const String &sName) const
{
	// Return control
	return m_mapControls.Get(sName);
}

/**
*  @brief
*    Get character of last key that was hit
*/
char Controller::GetChar()
{
	// Get character
	char nChar = m_nChar;
	m_nChar = 0;

	// Return character
	return nChar;
}

/**
*  @brief
*    Get connections
*/
const List<Connection*> &Controller::GetConnections()
{
	// Return connection list
	return m_lstConnections;
}

/**
*  @brief
*    Connect to another controller
*/
void Controller::Connect(const String &sControl, Control *pControl, float fScale)
{
	// Get controls
	Control *pInput = pControl;
	Control *pOutput = GetControl(sControl);
	if (pInput && pOutput && pInput != pOutput && pInput->GetController() != pOutput->GetController()) {
		// Create connection
		Connection *pConnection = new Connection(pInput, pOutput, fScale);
		if (pConnection->IsValid()) {
			// Add connection to both controllers
			pControl->GetController()->AddConnection(pConnection);
			AddConnection(pConnection);
		} else {
			// Connection is invalid!
			// [TODO] Log entry
			delete pConnection;
		}
	}
}

/**
*  @brief
*    Connect to another controller
*/
void Controller::ConnectAll(Controller *pController, const String &sPrefixOut, const String &sPrefixIn)
{
	// Get all controls of input controller
	const List<Control*> &lstControls = pController->GetControls();
	for (uint32 i=0; i<lstControls.GetNumOfElements(); i++) {
		// Get control
		Control *pInput = lstControls[i];

		// Check if input control has the right prefix
		String sNameIn = pInput->GetName();
		if (sPrefixIn.GetLength() == 0 || sNameIn.IndexOf(sPrefixIn) == 0) {
			// Get output name
			String sRoot = sNameIn.GetSubstring(sPrefixIn.GetLength());
			String sNameOut = sPrefixOut + sRoot;

			// Try to create connection
			Connect(sNameOut, pInput);
		}
	}
}

/**
*  @brief
*    Disconnect connection
*/
void Controller::Disconnect(Connection *pConnection)
{
	// Check connection
	if (pConnection && m_lstConnections.IsElement(pConnection)) {
		// Get other contoller
		Controller *pController = pConnection->GetInputControl()->GetController();
		if (pController == this) pController = pConnection->GetOutputControl()->GetController();

		// Remove connection from both controllers
		pController->RemoveConnection(pConnection);
		RemoveConnection(pConnection);

		// Destroy connection
		delete pConnection;
	}
}


//[-------------------------------------------------------]
//[ Public virtual Controller functions                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Update device once per frame
*/
void Controller::Update()
{
	// Do nothing by default
}

/**
*  @brief
*    Update output controls (LEDs, effects etc.)
*/
void Controller::UpdateOutputControl(Control *pControl)
{
	// Do nothing by default
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Add control
*/
void Controller::AddControl(Control *pControl)
{
	// Check if control is valid
	if (pControl) {
		// Add control to list
		m_lstControls.Add(pControl);

		// Add control to hash map
		m_mapControls.Add(pControl->GetName(), pControl);
	}
}

/**
*  @brief
*    Inform controller that a control has changed it's state
*/
void Controller::InformControl(Control *pControl)
{
	// Check if controller is active and control is valid
	if (m_bActive && pControl) {
		// Set changed-flag
		m_bChanged = true;

		// Check if a button was hit
		if (pControl->GetType() == ControlButton && static_cast<Button*>(pControl)->CheckHit()) {
			// Save key character
			m_nChar = static_cast<Button*>(pControl)->GetCharacter();
		}

		// Check if an output value was changed
		if (pControl->GetType() == ControlLED || pControl->GetType() == ControlEffect) {
			// Update output control
			UpdateOutputControl(pControl);
		}

		// Emit event
		SignalOnControl(pControl);

		// Check connections
		for (uint32 i=0; i<m_lstConnections.GetNumOfElements(); i++) {
			// Get connection
			Connection *pConnection = m_lstConnections[i];

			// Check 'direction' that we must take
			if (pControl->IsInputControl() && pConnection->GetInputControl() == pControl) {
				// Input control, pass from connection-input to connection-output
				pConnection->PassValue();
			} else if (!pControl->IsInputControl() && pConnection->GetOutputControl() == pControl) {
				// Output control, pass backwards: from connection-output to connection-input
				pConnection->PassValueBackwards();
			}
		}
	}
}

/**
*  @brief
*    Init control list
*/
void Controller::InitControlList(EControlType nType) const
{
	// Clear list
		 if (nType == ControlButton)	m_lstButtons.Clear();
	else if (nType == ControlAxis)		m_lstAxes.Clear();

	// Loop over all controls
	for (uint32 i=0; i<m_lstControls.GetNumOfElements(); i++) {
		// Get control
		Control *pControl = m_lstControls[i];

		// Add control to appropriate list
		if (pControl->GetType() == nType) {
				 if (nType == ControlButton)	m_lstButtons.Add(static_cast<Button*>(pControl));
			else if (nType == ControlAxis)		m_lstAxes   .Add(reinterpret_cast<Axis*>(pControl));
		}
	}
}

/**
*  @brief
*    Add connection
*/
void Controller::AddConnection(Connection *pConnection)
{
	// Check connection
	if (pConnection && !m_lstConnections.IsElement(pConnection)) {
		// Add connection
		m_lstConnections.Add(pConnection);
	}
}

/**
*  @brief
*    Remove connection
*/
void Controller::RemoveConnection(Connection *pConnection)
{
	// Check connection
	if (pConnection && m_lstConnections.IsElement(pConnection)) {
		// Remove connection
		m_lstConnections.Remove(pConnection);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
