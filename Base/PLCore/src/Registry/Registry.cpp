/*********************************************************\
 *  File: Registry.cpp                                   *
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
#if defined(WIN32)
	#include "PLCore/Registry/RegistryWindows.h"
#endif
#include "PLCore/Registry/Registry.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Registry::Registry() :
	m_pRegistryImpl(nullptr)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pRegistryImpl = new RegistryWindows();
	#endif
}

/**
*  @brief
*    Constructor
*/
Registry::Registry(EKey nKey, const String &sSubKey, uint32 nAccess) :
	m_pRegistryImpl(nullptr)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pRegistryImpl = new RegistryWindows();
	#endif

	// Open registry key
	if (m_pRegistryImpl)
		m_pRegistryImpl->Open(nKey, sSubKey, nAccess);
}

/**
*  @brief
*    Copy constructor
*/
Registry::Registry(const Registry &cRegistry) :
	m_pRegistryImpl(nullptr)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pRegistryImpl = new RegistryWindows();
	#endif

	// Open the same key again
	if (m_pRegistryImpl)
		Open(cRegistry.GetOpenKey(), cRegistry.GetOpenSubKey(), cRegistry.GetOpenAccessMode());
}

/**
*  @brief
*    Destructor
*/
Registry::~Registry()
{
	// Delete system implementation
	if (m_pRegistryImpl)
		delete m_pRegistryImpl;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
