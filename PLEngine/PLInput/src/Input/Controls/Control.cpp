/*********************************************************\
 *  File: Control.cpp                                    *
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
#include "PLInput/Input/InputManager.h"
#include "PLInput/Input/Controller.h"
#include "PLInput/Input/Controls/Control.h"


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
Control::Control(Controller *pController, EControlType nType, const PLGeneral::String &sName, const PLGeneral::String &sDescription) :
	m_pController(pController),
	m_nType(nType),
	m_sName(sName),
	m_sDescription(sDescription)
{
	// Check that controller is valid
	if (pController) {
		// Add control to controller
		pController->AddControl(this);
	}
}

/**
*  @brief
*    Destructor
*/
Control::~Control()
{
}

/**
*  @brief
*    Get controller
*/
Controller *Control::GetController() const
{
	// Return controller
	return m_pController;
}

/**
*  @brief
*    Get control type
*/
EControlType Control::GetType() const
{
	// Return type of control
	return m_nType;
}

/**
*  @brief
*    Check if control is input or output control
*/
bool Control::IsInputControl() const
{
	// Input controls are:  Axis and Button
	// Output controls are: Effect and LED
	return (m_nType == ControlAxis || m_nType == ControlButton);
}

/**
*  @brief
*    Get control name
*/
String Control::GetName() const
{
	// Return name
	return m_sName;
}

/**
*  @brief
*    Get control description
*/
String Control::GetDescription() const
{
	// Return description
	return m_sDescription;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Inform input manager that control has been changed
*/
void Control::InformUpdate()
{
	// Inform input manager
	InputManager::GetInstance()->UpdateControl(this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
