/*********************************************************\
 *  File: Image.inl                                      *
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
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
inline Image::Image()
{
}

/**
*  @brief
*    Destructor
*/
inline Image::~Image()
{
	// Clear data
	Unload();
}

/**
*  @brief
*    Check if this image is a multi-part image (e.g. a CubeMap)
*/
inline bool Image::IsMultiPart() const
{
	// Check if there is more than one part
	return (m_lstParts.GetNumOfElements() > 1);
}

/**
*  @brief
*    Get number of image parts
*/
inline PLCore::uint32 Image::GetNumOfParts() const
{
	// Return number of parts
	return m_lstParts.GetNumOfElements();
}

/**
*  @brief
*    Get image part
*/
inline ImagePart *Image::GetPart(PLCore::uint32 nIndex) const
{
	// Return part
	return m_lstParts[nIndex];
}

/**
*  @brief
*    Get image part by semantics
*/
inline ImagePart *Image::GetPartBySemantics(PLCore::uint32 nSemantics) const
{
	// Return part
	return m_mapParts.Get(nSemantics);
}

/**
*  @brief
*    Get image parts
*/
inline const PLCore::Container<ImagePart*> &Image::GetParts() const
{
	// Return part list
	return m_lstParts;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
