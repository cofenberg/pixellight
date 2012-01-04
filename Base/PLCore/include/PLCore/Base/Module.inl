/*********************************************************\
 *  File: Module.inl                                     *
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
*    Get module ID
*/
inline uint32 Module::GetModuleID() const
{
	// Return ID
	return m_nModuleID;
}

/**
*  @brief
*    Check if module is loaded as a plugin
*/
inline bool Module::IsPlugin() const
{
	// Return if module is plugin
	return m_bPlugin;
}

/**
*  @brief
*    Get dynamic library that contains the plugin
*/
inline DynLib *Module::GetDynLib() const
{
	// Return library
	return m_pDynLib;
}

/**
*  @brief
*    Get absolute filename of dynamic library or executable that contains the plugin
*/
inline String Module::GetFilename() const
{
	// Return filename
	return m_sFilename;
}

/**
*  @brief
*    Get module name
*/
inline String Module::GetName() const
{
	// Return name
	return m_sName;
}

/**
*  @brief
*    Get module vendor
*/
inline String Module::GetVendor() const
{
	// Return vendor
	return m_sVendor;
}

/**
*  @brief
*    Get module license
*/
inline String Module::GetLicense() const
{
	// Return license
	return m_sLicense;
}

/**
*  @brief
*    Get module description
*/
inline String Module::GetDescription() const
{
	// Return description
	return m_sDescription;
}

/**
*  @brief
*    Get classes of module
*/
inline const List<const Class*> &Module::GetClasses() const
{
	// Return class list
	return m_lstClasses;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Add class
*/
inline void Module::AddClass(const Class *pClass)
{
	// Add class to list
	m_lstClasses.Add(pClass);
}

/**
*  @brief
*    Remove class
*/
inline void Module::RemoveClass(const Class *pClass)
{
	// Remove class from list
	m_lstClasses.Remove(pClass);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
