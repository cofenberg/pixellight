/*********************************************************\
 *  File: Control.h                                     *
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


#ifndef __PLINPUT_CONTROL_H__
#define __PLINPUT_CONTROL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/PLInput.h"
#include "PLInput/PLInputDefinitions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Controller;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Input control base class
*
*  @remarks
*    A control is part of an input controller, e.g. a button or an axis.
*/
class Control {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pController
		*    Owning controller
		*  @param[in] nType
		*    Control type
		*  @param[in] sName
		*    Control name
		*  @param[in] sDescription
		*    Control description
		*/
		PLINPUT_API Control(Controller *pController, EControlType nType, const PLGeneral::String &sName, const PLGeneral::String &sDescription);

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~Control();

		/**
		*  @brief
		*    Get controller
		*
		*  @return
		*    Pointer to controller that owns the control
		*/
		PLINPUT_API Controller *GetController() const;

		/**
		*  @brief
		*    Get control type
		*
		*  @return
		*    Type of control
		*/
		PLINPUT_API EControlType GetType() const;

		/**
		*  @brief
		*    Check if control is input or output control
		*
		*  @return
		*    'true' if control is input control, 'false' if output
		*/
		PLINPUT_API bool IsInputControl() const;

		/**
		*  @brief
		*    Get control name
		*
		*  @return
		*    Name
		*/
		PLINPUT_API PLGeneral::String GetName() const;

		/**
		*  @brief
		*    Get control description
		*
		*  @return
		*    Description
		*/
		PLINPUT_API PLGeneral::String GetDescription() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Inform input manager that control has been changed
		*/
		PLINPUT_API void InformUpdate();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Control data
		Controller			*m_pController;		/**< Owning controller */
		EControlType		 m_nType;			/**< Control type */
		PLGeneral::String	 m_sName;			/**< Control name */
		PLGeneral::String	 m_sDescription;	/**< Control description */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_CONTROL_H__
