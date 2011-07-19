/*********************************************************\
 *  File: Module.cpp                                     *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/System/DynLib.h"
#include "PLCore/Base/Module.h"


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
uint32 Module::GetModuleID() const
{
	// Return ID
	return m_nModuleID;
}

/**
*  @brief
*    Check if module is loaded as a plugin
*/
bool Module::IsPlugin() const
{
	// Return if module is plugin
	return m_bPlugin;
}

/**
*  @brief
*    Get dynamic library that contains the plugin
*/
DynLib *Module::GetDynLib() const
{
	// Return library
	return m_pDynLib;
}

/**
*  @brief
*    Get absolute filename of dynamic library that contains the plugin
*/
String Module::GetFilename() const
{
	// Return filename
	return m_sFilename;
}

/**
*  @brief
*    Get module name
*/
String Module::GetName() const
{
	// Return name
	return m_sName;
}

/**
*  @brief
*    Get module vendor
*/
String Module::GetVendor() const
{
	// Return vendor
	return m_sVendor;
}

/**
*  @brief
*    Get module license
*/
String Module::GetLicense() const
{
	// Return license
	return m_sLicense;
}

/**
*  @brief
*    Get module description
*/
String Module::GetDescription() const
{
	// Return description
	return m_sDescription;
}

/**
*  @brief
*    Get classes of module
*/
const List<const Class*> &Module::GetClasses() const
{
	// Return class list
	return m_lstClasses;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Module::Module(uint32 nModuleID) :
	m_nModuleID(nModuleID),
	m_bPlugin(false),
	m_pDynLib(nullptr),
	m_sName("Unknown"),
	m_sVendor("Unknown"),
	m_sLicense("Unknown"),
	m_sDescription("Unknown module")
{
}

/**
*  @brief
*    Destructor
*/
Module::~Module()
{
	// If there's a dynamic library instance, destroy it right now
	if (m_pDynLib)
		delete m_pDynLib;
}

/**
*  @brief
*    Set module information
*/
void Module::SetModuleInfo(const String &sName, const String &sVendor, const String &sLicense, const String &sDescription)
{
	// Save data
	m_sName			= sName;
	m_sVendor		= sVendor;
	m_sLicense		= sLicense;
	m_sDescription	= sDescription;
}

/**
*  @brief
*    Add class
*/
void Module::AddClass(const Class *pClass)
{
	// Add class to list
	m_lstClasses.Add(pClass);
}

/**
*  @brief
*    Remove class
*/
void Module::RemoveClass(const Class *pClass)
{
	// Remove class from list
	m_lstClasses.Remove(pClass);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
