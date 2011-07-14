/*********************************************************\
 *  File: ContactInformation.h                           *
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


#ifndef __PLPHYSICS_CONTACTINFORMATION_H__
#define __PLPHYSICS_CONTACTINFORMATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPhysics/PLPhysics.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Body;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Contact information class
*/
class ContactInformation {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFirstBody
		*    The first physics body
		*  @param[in] cSecondBody
		*    The second physics body
		*/
		PLPHYSICS_API ContactInformation(Body &cFirstBody, Body &cSecondBody);

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API ~ContactInformation();

		/**
		*  @brief
		*    Returns the first physics body
		*
		*  @return
		*    The first physics body
		*/
		PLPHYSICS_API Body &GetFirstBody() const;

		/**
		*  @brief
		*    Returns the first second body
		*
		*  @return
		*    The second physics body
		*/
		PLPHYSICS_API Body &GetSecondBody() const;

		/**
		*  @brief
		*    Returns whether or not the contact is marked to be ignored
		*
		*  @return
		*    'true' if the contact is marked as to be ignored, else 'false'
		*/
		PLPHYSICS_API bool IsContactIgnored() const;

		/**
		*  @brief
		*    Marks the contact to be ignored
		*
		*  @remarks
		*    By default, detected contacts are used by the physics. Using this function one can
		*    tell the physics not to use this contact.
		*/
		PLPHYSICS_API void IgnoreContact();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Body *m_pFirstBody;		/**< The first physics body, always valid! */
		Body *m_pSecondBody;	/**< The second physics body, always valid! */
		bool  m_bIgnoreContact;	/**< Is the contact marked to be ignored? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_CONTACTINFORMATION_H__
