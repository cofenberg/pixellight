/*********************************************************\
 *  File: Class.cpp                                      *
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
#include "PLCore/Base/ClassManager.h"
#include "PLCore/Base/Class.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get derived classes
*/
void Class::GetDerivedClasses(List<const Class*> &lstClasses) const
{
	// Get list of derived classes
	ClassManager::GetInstance()->GetClasses(lstClasses, m_pClassImpl->GetClassName(), NonRecursive, NoBase, IncludeAbstract);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Class::Class(ClassImpl &cClassImpl) :
	m_pClassImpl(&cClassImpl)
{
	// Tell the class implementation about the class instance wrapping it
	m_pClassImpl->m_pClass = this;
}

/**
*  @brief
*    Copy constructor
*/
Class::Class(const Class &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Destructor
*/
Class::~Class()
{
	// Don't destroy the class implementation in here, it's the job of the class manager to take care of that
}

/**
*  @brief
*    Copy operator
*/
Class &Class::operator =(const Class &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
