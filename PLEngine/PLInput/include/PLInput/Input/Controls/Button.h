/*********************************************************\
 *  File: Button.h                                       *
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


#ifndef __PLINPUT_BUTTON_H__
#define __PLINPUT_BUTTON_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Input/Controls/Control.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Button control
*/
class Button : public Control {


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
		*  @param[in] sName
		*    Control name
		*  @param[in] sDescription
		*    Control description
		*  @param[in] nCharacter
		*    Character associated with the button, '\0' if none
		*/
		PLINPUT_API Button(Controller *pController, const PLGeneral::String &sName, const PLGeneral::String &sDescription, char nCharacter = '\0');

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cOther
		*    Other button
		*/
		PLINPUT_API Button(const Button &cOther);

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~Button();

		/**
		*  @brief
		*    Comparison operator
		*
		*  @param[in] cOther
		*    Button to compare with
		*
		*  @return
		*    'true', if both buttons are equal, else 'false'
		*/
		PLINPUT_API bool operator ==(const Button &cOther) const;

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cOther
		*    Other button
		*
		*  @return
		*    Reference to this button
		*/
		PLINPUT_API Button &operator =(const Button &cOther);

		/**
		*  @brief
		*    Get character
		*
		*  @return
		*    Character associated with the button, '\0' if none
		*/
		PLINPUT_API char GetCharacter() const;

		/**
		*  @brief
		*    Get button status
		*
		*  @return
		*    'true', if the button is currently pressed, else 'false'
		*/
		PLINPUT_API bool IsPressed() const;

		/**
		*  @brief
		*    Set button status
		*
		*  @param[in] bPressed
		*    'true', if the button is pressed, else 'false'
		*/
		PLINPUT_API void SetPressed(bool bPressed);

		/**
		*  @brief
		*    Check if the button has been hit
		*
		*  @return
		*    'true', if the button has been hit since the last call of this function, else 'false'
		*
		*  @remarks
		*    This will return the hit-state of the button and also reset it immediatly (so the next call
		*    to IsHit() will return false). If you only want to check, but not reset the hit-state of
		*    a button, you should call CheckHit().
		*/
		PLINPUT_API bool IsHit();

		/**
		*  @brief
		*    Check if the button has been hit
		*
		*  @return
		*    'true', if the button has been hit since the last call of this function, else 'false'
		*
		*  @remarks
		*    This function will NOT reset the hit-state after being called (see IsHit()).
		*/
		PLINPUT_API bool CheckHit();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Button info
		char m_nCharacter;	/**< Character associated with the button, '\0' if none */

		// Button status
		bool m_bPressed;	/**< Is the button currently pressed? */
		bool m_bHit;		/**< Has the button been hit in the meantime? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_BUTTON_H__
