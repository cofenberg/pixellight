/*********************************************************\
 *  File: TextureManager.inl                             *
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
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the owner renderer context of this manager
*/
inline RendererContext &TextureManager::GetRendererContext() const
{
	return *m_pRendererContext;
}

/**
*  @brief
*    Returns the texture quality
*/
inline float TextureManager::GetTextureQuality() const
{
	return m_fTextureQuality;
}

/**
*  @brief
*    Returns whether the next lower valid texture size should be taken or the higher one
*/
inline bool TextureManager::GetTextureFit() const
{
	return m_bTextureFitLower;
}

/**
*  @brief
*    Sets whether the next lower valid texture size should be taken or the higher one
*/
inline void TextureManager::SetTextureFit(bool bLower)
{
	m_bTextureFitLower = bLower;
}

/**
*  @brief
*    Returns whether or not the usage of texture mipmaps is allowed
*/
inline bool TextureManager::AreTextureMipmapsAllowed() const
{
	return m_bTextureMipmapsAllowed;
}

/**
*  @brief
*    Sets whether or not the usage of texture mipmaps is allowed
*/
inline void TextureManager::SetTextureMipmapsAllowed(bool bAllowed)
{
	m_bTextureMipmapsAllowed = bAllowed;
}

/**
*  @brief
*    Returns whether or not the usage of texture compression is allowed
*/
inline bool TextureManager::IsTextureCompressionAllowed() const
{
	return m_bTextureCompressionAllowed;
}

/**
*  @brief
*    Sets whether or not the usage of texture compression is allowed
*/
inline void TextureManager::SetTextureCompressionAllowed(bool bAllowed)
{
	m_bTextureCompressionAllowed = bAllowed;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
