/*********************************************************\
 *  File: DynLib.inl                                     *
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
#include "PLCore/System/DynLibImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loads a dynamic library
*/
inline bool DynLib::Load(const String &sFilename)
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
inline bool DynLib::IsLoaded() const
{
	// Return whether the library is loaded
	return m_pDynLibImpl->IsLoaded();
}

/**
*  @brief
*    Get the path (set within 'Load()') to the dynamic library
*/
inline String DynLib::GetPath() const
{
	// Return filename
	return m_cUrl.GetUrl();
}

/**
*  @brief
*    Get the absolute path to the dynamic library
*/
inline String DynLib::GetAbsPath() const
{
	return m_pDynLibImpl->GetAbsPath();
}

/**
*  @brief
*    Returns a pointer to a symbol in the library
*/
inline void *DynLib::GetSymbol(const String &sSymbol) const
{
	// Return symbol pointer
	return m_pDynLibImpl->GetSymbol(sSymbol);
}

/**
*  @brief
*    Unloads the dynamic library
*/
inline bool DynLib::Unload()
{
	// Unload library
	return m_pDynLibImpl->Unload();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
