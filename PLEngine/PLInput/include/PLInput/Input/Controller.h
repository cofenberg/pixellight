/*********************************************************\
 *  File: Controller.h                                   *
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


#ifndef __PLINPUT_CONTROLLER_H__
#define __PLINPUT_CONTROLLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLCore/Base/Object.h>
#include "PLInput/PLInput.h"
#include "PLInput/PLInputDefinitions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Control;
class Button;
class Axis;
class Connection;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Input controller
*
*  @remarks
*    A controller represents an input device, which can either be a real device like e.g. a mouse or joystick,
*    or a virtual device that is used to map real input devices to virtual axes and keys. A controller consists
*    of a list of controls, e.g. buttons or axes and provides methods to obtain the status.
*/
class Controller : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class InputManager;
	friend class Provider;
	friend class Control;


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLINPUT_RTTI_EXPORT, Controller, "PLInput", PLCore::Object, "Input controller base class")
		// Events
		pl_signal_1(OnActivate,		bool,		"Controller has been activated or deactivated", "")
		pl_signal_1(OnControl,		Control*,	"Control event has occured",					"")
		pl_signal_0(OnChanged,					"Controller state has changed",					"")

		// Attributes
		pl_attribute(Type,			pl_enum_type(EControllerType),	ControllerVirtual,	ReadOnly,  GetSet, "Controller type",			"")
		pl_attribute(Name,			PLGeneral::String,				"",					ReadOnly,  GetSet, "Controller name",			"")
		pl_attribute(Description,	PLGeneral::String,				"",					ReadOnly,  GetSet, "Controller description",	"")
		pl_attribute(Active,		bool,							true,				ReadWrite, GetSet, "State of controller",		"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nType
		*    Controller type
		*  @param[in] sName
		*    Controller name
		*  @param[in] sDescription
		*    Controller description
		*/
		PLINPUT_API Controller(EControllerType nType, const PLGeneral::String &sName, const PLGeneral::String &sDescription);

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~Controller();

		/**
		*  @brief
		*    Get controller type
		*
		*  @return
		*    Controller type
		*/
		PLINPUT_API EControllerType GetType() const;

		/**
		*  @brief
		*    Get controller name
		*
		*  @return
		*    Name
		*/
		PLINPUT_API PLGeneral::String GetName() const;

		/**
		*  @brief
		*    Get controller description
		*
		*  @return
		*    Description
		*/
		PLINPUT_API PLGeneral::String GetDescription() const;

		/**
		*  @brief
		*    Check if controller is active
		*
		*  @return
		*    'true' if controller is active, else 'false'
		*
		*  @remarks
		*    If a controller is active, it sends out signals when the state of it's controls has changed.
		*    If a controller is not active, no state changes will occur and all input events from connected
		*    devices will be discarded.
		*/
		PLINPUT_API bool GetActive() const;

		/**
		*  @brief
		*    Activate or deactivate controller
		*
		*  @param[in] bActive
		*    'true' if controller is active, else 'false'
		*
		*  @remarks
		*    Virtual controllers can be activated or deactivated, real input devices
		*    are always active and can not be deactivated.
		*/
		PLINPUT_API void SetActive(bool bActive);

		/**
		*  @brief
		*    Check if the controller's state has changed (for polling)
		*
		*  @return
		*    'true', if the state has changed, else 'false'
		*/
		PLINPUT_API bool HasChanged() const;

		/**
		*  @brief
		*    Get all controls of the controller
		*
		*  @return
		*    List of controls
		*/
		PLINPUT_API const PLGeneral::List<Control*> &GetControls() const;

		/**
		*  @brief
		*    Get all buttons
		*
		*  @return
		*    List of buttons
		*/
		PLINPUT_API const PLGeneral::List<Button*> &GetButtons() const;

		/**
		*  @brief
		*    Get all axes
		*
		*  @return
		*    List of axes
		*/
		PLINPUT_API const PLGeneral::List<Axis*> &GetAxes() const;

		/**
		*  @brief
		*    Get control with a specific name
		*
		*  @param[in] sName
		*    Name of control
		*
		*  @return
		*    Control, or NULL if no control with that name could be found
		*/
		PLINPUT_API Control* GetControl(const PLGeneral::String &sName) const;

		/**
		*  @brief
		*    Get character of last button that was hit
		*
		*  @return
		*    Button character (ASCII), can be '\0'
		*
		*  @remarks
		*    This function returns the character code of the last button that was hit (not pressed!).
		*    The character will then be reset to '\0', so the next call will return '\0', until
		*    a new button is first pressed and then released.
		*/
		PLINPUT_API char GetChar();

		/**
		*  @brief
		*    Get connections
		*
		*  @return
		*    List of connections (both incoming and outgoing)
		*
		*  @remarks
		*    To determine whether a connection is incoming or outgoing, you can check e.g.
		*    GetOutputControl()->GetController() == this or something similar.
		*/
		PLINPUT_API const PLGeneral::List<Connection*> &GetConnections();

		/**
		*  @brief
		*    Connect to another controller
		*
		*  @param[in] sControl
		*    Name of control of this controller (output control)
		*  @param[in] pControl
		*    Pointer to control (input control)
		*  @param[in] fScale
		*    Scale factor
		*/
		PLINPUT_API void Connect(const PLGeneral::String &sControl, Control *pControl, float fScale = 1.0f);

		/**
		*  @brief
		*    Connect to another controller
		*
		*  @param[in] pController
		*    Pointer to controller containing the input controls
		*  @param[in] sPrefixOut
		*    Prefix for controls of this controller
		*  @param[in] sPrefixIn
		*    Prefix for controls of the other controller
		*
		*  @remarks
		*    This connects all controls of the input controller (pController) to the controls of the output
		*    controller (this), if their names are equal, e.g. pController->"Left" will be connected to this->"Left".
		*    You can also provide a prefix for either or both sides, e.g.: ConnectAll(pOtherController, "", "Camera")
		*    will connect pController->"CameraLeft" to this->"Left".
		*/
		PLINPUT_API void ConnectAll(Controller *pController, const PLGeneral::String &sPrefixOut, const PLGeneral::String &sPrefixIn);

		/**
		*  @brief
		*    Disconnect connection
		*
		*  @param[in] pConnection
		*    Connection (must be valid!)
		*/
		PLINPUT_API void Disconnect(Connection *pConnection);


	//[-------------------------------------------------------]
	//[ Public virtual Controller functions                   ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Update device once per frame
		*
		*  @remarks
		*    This function can be used e.g. to reset any data of a device once per frame. Usually this is
		*    not needed, but some devices (e.g. RawInput mice etc.) need to reset their data once per frame.
		*/
		PLINPUT_API virtual void Update();

		/**
		*  @brief
		*    Update output controls (LEDs, effects etc.)
		*
		*  @param[in] pControl
		*    Output control that has been changed
		*
		*  @remarks
		*    This function is called whenever an output control such as LED or Effect has been changed.
		*    A device should use this function to update the specific control state on the device (or update
		*    all output controls at the same time)
		*/
		PLINPUT_API virtual void UpdateOutputControl(Control *pControl);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Add control
		*
		*  @param[in] pControl
		*    Pointer to control, must be valid!
		*/
		PLINPUT_API void AddControl(Control *pControl);

		/**
		*  @brief
		*    Inform controller that a control has changed it's state
		*
		*  @param[in] pControl
		*    Pointer to control, must be valid!
		*/
		PLINPUT_API void InformControl(Control *pControl);

		/**
		*  @brief
		*    Init control list
		*
		*  @param[in] nType
		*    Type of list that is to be filled
		*/
		PLINPUT_API void InitControlList(EControlType nType) const;

		/**
		*  @brief
		*    Add connection
		*
		*  @param[in] pConnection
		*    Connection (must be valid!)
		*/
		PLINPUT_API void AddConnection(Connection *pConnection);

		/**
		*  @brief
		*    Remove connection
		*
		*  @param[in] pConnection
		*    Connection (must be valid!)
		*/
		PLINPUT_API void RemoveConnection(Connection *pConnection);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Controller information and state
		EControllerType									m_nType;			/**< Controller type */
		PLGeneral::String								m_sName;			/**< Controller name */
		PLGeneral::String								m_sDescription;		/**< Controller description */
		bool											m_bConfirmed;		/**< Confirmation flag for DetectDevices() */
		bool											m_bActive;			/**< Is the controller active? */
		mutable bool									m_bChanged;			/**< Has the controller's state changed? */

		// Controls
		PLGeneral::List<Control*>						m_lstControls;		/**< List of all controls */
		PLGeneral::HashMap<PLGeneral::String, Control*>	m_mapControls;		/**< Hash map of name -> control */
		mutable PLGeneral::List<Button*>				m_lstButtons;		/**< List of buttons (filled on use) */
		mutable PLGeneral::List<Axis*>					m_lstAxes;			/**< List of absolute axes (filled on use) */
		char											m_nChar;			/**< Last hit key character */

		// Connections
		PLGeneral::List<Connection*>					m_lstConnections;	/**< List of connections */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_CONTROLLER_H__
