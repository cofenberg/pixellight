/*********************************************************\
 *  File: LoadableType.inl                               *
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
*    Returns the name of the loadable type
*/
inline String LoadableType::GetName() const
{
	// Return description
	return m_sName;
}

/**
*  @brief
*    Returns the class of the loadable type
*/
inline const Class &LoadableType::GetClass() const
{
	return *m_pClass;
}


//[-------------------------------------------------------]
//[ Formats & loaders                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the number of supported formats
*/
inline uint32 LoadableType::GetNumOfFormats() const
{
	return m_lstFormats.GetNumOfElements();
}

/**
*  @brief
*    Returns a supported formats
*/
inline String LoadableType::GetFormat(uint32 nIndex) const
{
	return m_lstFormats.Get(nIndex);
}

/**
*  @brief
*    Returns the number of loaders
*/
inline uint32 LoadableType::GetNumOfLoaders() const
{
	return m_lstLoaders.GetNumOfElements();
}

/**
*  @brief
*    Returns a loader by using an index
*/
inline Loader *LoadableType::GetLoaderByIndex(uint32 nIndex) const
{
	return m_lstLoaders.Get(nIndex);
}

/**
*  @brief
*    Returns a loader by using a loadable extension
*/
inline Loader *LoadableType::GetLoaderByExtension(const String &sExtension) const
{
	return m_mapLoaders.Get(sExtension);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
