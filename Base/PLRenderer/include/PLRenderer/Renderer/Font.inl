/*********************************************************\
 *  File: Font.inl                                       *
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the creating font manager
*/
inline FontManager &Font::GetFontManager() const
{
	return *m_pFontManager;
}

/**
*  @brief
*    Returns the filename of the font file the data came from
*/
inline PLCore::String Font::GetFilename() const
{
	return m_sFilename;
}

/**
*  @brief
*    Returns the font size in points (72 points per inch)
*/
inline PLCore::uint32 Font::GetSize() const
{
	return m_nSize;
}

/**
*  @brief
*    Returns the horizontal and vertical resolution in DPI
*/
inline PLCore::uint32 Font::GetResolution() const
{
	return m_nResolution;
}

/**
*  @brief
*    Returns the font size in pixels
*/
inline PLCore::uint32 Font::GetSizeInPixels() const
{
	return static_cast<PLCore::uint32>(m_nSize/72.0f*m_nResolution);
}

/**
*  @brief
*    Returns the font height in pixels
*/
inline PLCore::uint32 Font::GetHeightInPixels() const
{
	return static_cast<PLCore::uint32>(GetHeight()/72.0f*m_nResolution);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
