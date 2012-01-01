/*********************************************************\
 *  File: Module.cpp                                     *
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
#include "PLCore/System/DynLib.h"
#include "PLCore/Base/Module.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
