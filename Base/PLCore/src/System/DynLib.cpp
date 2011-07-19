/*********************************************************\
 *  File: DynLib.cpp                                     *
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
#include "PLCore/File/Url.h"
#if defined(WIN32)
	#include "PLCore/System/DynLibWindows.h"
#elif defined(LINUX)
	#include "PLCore/System/DynLibLinux.h"
#endif
#include "PLCore/System/DynLib.h"


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
DynLib::DynLib() :
	m_pDynLibImpl(nullptr)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pDynLibImpl = new DynLibWindows();
	#elif defined(LINUX)
		// Create Linux implementation
		m_pDynLibImpl = new DynLibLinux();
	#else
		// Unknown system
		#error "Unsupported platform"
	#endif
}

/**
*  @brief
*    Destructor
*/
DynLib::~DynLib()
{
	// Destroy system specific implementation
	if (m_pDynLibImpl)
		delete m_pDynLibImpl;
}

/**
*  @brief
*    Loads a dynamic library
*/
bool DynLib::Load(const String &sFilename)
{
	// Save filename
	m_cUrl = sFilename;

	// Call system implementation
	return m_pDynLibImpl->Load(m_cUrl);
}

/**
*  @brief
*    Returns if the dynamic library has been loaded
*/
bool DynLib::IsLoaded() const
{
	// Return whether the library is loaded
	return m_pDynLibImpl->IsLoaded();
}

/**
*  @brief
*    Get the path (set within 'Load()') to the dynamic library
*/
String DynLib::GetPath() const
{
	// Return filename
	return m_cUrl.GetNativePath();
}

/**
*  @brief
*    Get the absolute path to the dynamic library
*/
String DynLib::GetAbsPath() const
{
	return m_pDynLibImpl->GetAbsPath();
}

/**
*  @brief
*    Returns a pointer to a symbol in the library
*/
void *DynLib::GetSymbol(const String &sSymbol) const
{
	// Return symbol pointer
	return m_pDynLibImpl->GetSymbol(sSymbol);
}

/**
*  @brief
*    Unloads the dynamic library
*/
bool DynLib::Unload()
{
	// Unload library
	return m_pDynLibImpl->Unload();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
DynLib::DynLib(const DynLib &cSource) :
	m_pDynLibImpl(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
DynLib &DynLib::operator =(const DynLib &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
