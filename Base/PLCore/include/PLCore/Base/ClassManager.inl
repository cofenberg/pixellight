/*********************************************************\
 *  File: ClassManager.inl                               *
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get all registered modules
*/
inline const List<const Module*> &ClassManager::GetModules() const
{
	// Return module list
	return m_lstModules;
}

/**
*  @brief
*    Get module by ID
*/
inline const Module *ClassManager::GetModuleByID(uint32 nModuleID) const
{
	// Get module with given ID (can be a null pointer)
	return m_mapModules.Get(nModuleID);
}

/**
*  @brief
*    Get all registered classes
*/
inline const List<const Class*> &ClassManager::GetClasses() const
{
	// Return class list
	return m_lstClasses;
}

/**
*  @brief
*    Get class
*/
inline const Class *ClassManager::GetClass(const String &sClass) const
{
	// Get class
	return m_mapClasses.Get(sClass);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
