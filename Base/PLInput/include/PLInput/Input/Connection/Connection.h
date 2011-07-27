/*********************************************************\
 *  File: Connection.h                                   *
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


#ifndef __PLINPUT_CONNECTION_H__
#define __PLINPUT_CONNECTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/PLInput.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Control;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Connection between two controllers/controls
*/
class Connection {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pInput
		*    Input control, can be a null pointer
		*  @param[in] pOutput
		*    Output control, can be a null pointer
		*  @param[in] fScale
		*    Scale factor
		*/
		PLINPUT_API Connection(Control *pInput, Control *pOutput, float fScale = 1.0f);

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~Connection();

		/**
		*  @brief
		*    Get input control
		*
		*  @return
		*    Pointer to control that is on the input side of the connection, can be a null pointer
		*/
		PLINPUT_API Control *GetInputControl() const;

		/**
		*  @brief
		*    Get output control
		*
		*  @return
		*    Pointer to control that is on the output side of the connection, can be a null pointer
		*/
		PLINPUT_API Control *GetOutputControl() const;

		/**
		*  @brief
		*    Check if connection is value
		*
		*  @return
		*    'true' if connection is valid, else 'false'
		*
		*  @remarks
		*    A connection is invalid e.g. when you try to connect different types of controls
		*    without using the proper connection type (see derived classes for connection classes
		*    that can convert values into other types).
		*    It is also not valid to use a control of a device as an output, because devices can only be
		*    used as input, not as output of controls (a device is controlled by the physical device only).
		*/
		PLINPUT_API bool IsValid() const;


	//[-------------------------------------------------------]
	//[ Public virtual Connection functions                   ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Pass value from input to output
		*/
		PLINPUT_API virtual void PassValue();

		/**
		*  @brief
		*    Pass value backwards from output to input
		*/
		PLINPUT_API virtual void PassValueBackwards();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Control data
		Control	*m_pInput;		/**< Input control, can be a null pointer */
		Control	*m_pOutput;		/**< Output control, can be a null pointer */
		bool	 m_bValid;		/**< 'true' if connection is valid, else 'false' */
		float	 m_fScale;		/**< Scale factor */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_CONNECTION_H__
