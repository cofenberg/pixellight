/*********************************************************\
 *  File: LoadableManager.inl                            *
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
*    Returns the number of loadable types
*/
inline uint32 LoadableManager::GetNumOfTypes()
{
	RegisterClasses();
	return m_lstTypes.GetNumOfElements();
}

/**
*  @brief
*    Returns a loadable type by using an index
*/
inline LoadableType *LoadableManager::GetTypeByIndex(uint32 nIndex)
{
	RegisterClasses();
	return m_lstTypes.Get(nIndex);
}

/**
*  @brief
*    Returns a loadable type by using it's name
*/
inline LoadableType *LoadableManager::GetTypeByName(const String &sName)
{
	RegisterClasses();
	return m_mapTypes.Get(sName);
}

/**
*  @brief
*    Returns a loadable type by using a loadable extension
*/
inline LoadableType *LoadableManager::GetTypeByExtension(const String &sExtension)
{
	RegisterClasses();
	return m_mapTypesByExtension.Get(sExtension);
}

/**
*  @brief
*    Returns the number of loaders
*/
inline uint32 LoadableManager::GetNumOfLoaders()
{
	RegisterClasses();
	return m_lstLoaders.GetNumOfElements();
}

/**
*  @brief
*    Returns a loader by using an index
*/
inline Loader *LoadableManager::GetLoaderByIndex(uint32 nIndex)
{
	RegisterClasses();
	return m_lstLoaders.Get(nIndex);
}

/**
*  @brief
*    Returns a loader by using a extension
*/
inline Loader *LoadableManager::GetLoaderByExtension(const String &sExtension)
{
	RegisterClasses();
	return m_mapLoaders.Get(sExtension);
}

/**
*  @brief
*    Returns the number of supported formats
*/
inline uint32 LoadableManager::GetNumOfFormats()
{
	RegisterClasses();
	return m_lstFormats.GetNumOfElements();
}

/**
*  @brief
*    Returns a supported format
*/
inline String LoadableManager::GetFormat(uint32 nIndex)
{
	RegisterClasses();
	return m_lstFormats.Get(nIndex);
}

/**
*  @brief
*    Returns the number of base directories
*/
inline uint32 LoadableManager::GetNumOfBaseDirs() const
{
	return m_lstBaseDirs.GetNumOfElements();
}

/**
*  @brief
*    Returns one of the base directories
*/
inline String LoadableManager::GetBaseDir(uint32 nNum) const
{
	// Get directory
	return m_lstBaseDirs[nNum];
}

/**
*  @brief
*    Removes all base directories
*/
inline bool LoadableManager::ClearBaseDirs()
{
	// Delete all base dirs
	m_lstBaseDirs.Clear();

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
