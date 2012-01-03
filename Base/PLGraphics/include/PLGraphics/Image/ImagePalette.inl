/*********************************************************\
 *  File: ImagePalette.inl                               *
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
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
inline ImagePalette::ImagePalette() :
	m_pData(nullptr),
	m_nSize(0),
	m_nColors(0)
{
}

/**
*  @brief
*    Destructor
*/
inline ImagePalette::~ImagePalette()
{
	// Clear data
	Clear();
}

/**
*  @brief
*    Clear data
*/
inline void ImagePalette::Clear()
{
	// Delete palette
	if (m_pData)
		delete [] m_pData;

	// Reset data
	m_pData   = nullptr;
	m_nSize   = 0;
	m_nColors = 0;
	m_mapColors.Clear();
}

/**
*  @brief
*    Get number of colors
*/
inline PLCore::uint32 ImagePalette::GetNumOfColors() const
{
	// Return number of colors
	return m_nColors;
}

/**
*  @brief
*    Get color
*/
inline Color3 ImagePalette::GetColor(PLCore::uint32 nIndex) const
{
	// Is index valid?
	if (nIndex < m_nColors)
		return Color3(m_pData[nIndex*3], m_pData[nIndex*3+1], m_pData[nIndex*3+2]);

	// Invalid index
	return Color3::Null;
}

/**
*  @brief
*    Add color
*/
inline PLCore::uint32 ImagePalette::AddColor(const Color3 &cColor)
{
	// Add color to next free place in palette
	const PLCore::uint32 nIndex = m_nColors;
	SetColor(nIndex, cColor);

	// Return color index
	return nIndex;
}

/**
*  @brief
*    Rebuild color index
*/
inline void ImagePalette::RebuildColorIndex()
{
	// Clear hash map. It will be rebuilt next time GetColorIndex() is called
	m_mapColors.Clear();
}

/**
*  @brief
*    Get color palette data
*/
inline PLCore::uint8 *ImagePalette::GetData() const
{
	// Return palette data
	return m_pData;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
