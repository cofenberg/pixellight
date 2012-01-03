/*********************************************************\
 *  File: Texture.inl                                    *
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
*    Returns the texture manager this texture is in
*/
inline TextureManager &Texture::GetTextureManager() const
{
	// There MUST always be a manager!
	return reinterpret_cast<TextureManager&>(*m_pManager);
}

/**
*  @brief
*    Returns the texture compression hint
*/
inline Texture::ECompressionFormat Texture::GetCompressionHint() const
{
	return m_nCompressionHint;
}

/**
*  @brief
*    Sets the texture compression hint
*/
inline void Texture::SetCompressionHint(ECompressionFormat nFormat)
{
	m_nCompressionHint = nFormat;
}

/**
*  @brief
*    Returns the original texture size
*/
inline const PLMath::Vector3i &Texture::GetOriginalSize() const
{
	return m_vOriginalSize;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
