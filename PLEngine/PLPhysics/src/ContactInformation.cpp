/*********************************************************\
 *  File: ContactInformation.cpp                         *
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
#include "PLPhysics/ContactInformation.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ContactInformation::ContactInformation(Body &cFirstBody, Body &cSecondBody) :
	m_pFirstBody(&cFirstBody),
	m_pSecondBody(&cSecondBody),
	m_bIgnoreContact(false)
{
}

/**
*  @brief
*    Destructor
*/
ContactInformation::~ContactInformation()
{
	// Nothing to do in here
}

/**
*  @brief
*    Returns the first physics body
*/
Body &ContactInformation::GetFirstBody() const
{
	return *m_pFirstBody;
}

/**
*  @brief
*    Returns the first second body
*/
Body &ContactInformation::GetSecondBody() const
{
	return *m_pSecondBody;
}

/**
*  @brief
*    Returns whether or not the contact is marked to be ignored
*/
bool ContactInformation::IsContactIgnored() const
{
	return m_bIgnoreContact;
}

/**
*  @brief
*    Marks the contact to be ignored
*/
void ContactInformation::IgnoreContact()
{
	m_bIgnoreContact = true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
