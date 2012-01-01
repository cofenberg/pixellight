/*********************************************************\
 *  File: ImagePart.inl                                  *
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
inline ImagePart::ImagePart() :
	m_nSemantics(0)
{
}

/**
*  @brief
*    Destructor
*/
inline ImagePart::~ImagePart()
{
	// Clear data
	Clear();
}

/**
*  @brief
*    Get semantics
*/
inline PLCore::uint32 ImagePart::GetSemantics() const
{
	// Return semantics
	return m_nSemantics;
}

/**
*  @brief
*    Set semantics
*/
inline void ImagePart::SetSemantics(PLCore::uint32 nSemantics)
{
	// Set semantics
	m_nSemantics = nSemantics;
}

/**
*  @brief
*    Check if the layer has mipmaps
*/
inline bool ImagePart::HasMipmaps() const
{
	// Check if there is more than one mipmap
	return (m_lstMipmaps.GetNumOfElements() > 1);
}

/**
*  @brief
*    Get number of mipmaps
*/
inline PLCore::uint32 ImagePart::GetNumOfMipmaps() const
{
	// Return number of mipmaps
	return m_lstMipmaps.GetNumOfElements();
}

/**
*  @brief
*    Get mipmap
*/
inline ImageBuffer *ImagePart::GetMipmap(PLCore::uint32 nIndex) const
{
	// Return mipmap
	return m_lstMipmaps[nIndex];
}

/**
*  @brief
*    Get mipmaps
*/
inline const PLCore::Container<ImageBuffer*> &ImagePart::GetMipmaps() const
{
	// Return mipmap list
	return m_lstMipmaps;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
