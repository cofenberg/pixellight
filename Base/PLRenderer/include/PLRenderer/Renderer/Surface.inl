/*********************************************************\
 *  File: Surface.inl                                    *
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
*    Returns the owner renderer
*/
inline Renderer &Surface::GetRenderer() const
{
	return *m_pRenderer;
}

/**
*  @brief
*    Returns the surface type
*/
inline Surface::EType Surface::GetType() const
{
	return m_nType;
}

/**
*  @brief
*    Returns whether the surface is active or not
*/
inline bool Surface::IsActive() const
{
	return m_bActive;
}

/**
*  @brief
*    Sets whether the surface is active or not
*/
inline void Surface::SetActive(bool bActive)
{
	m_bActive = bActive;
}

/**
*  @brief
*    Returns the surface painter
*/
inline SurfacePainter *Surface::GetPainter() const
{
	return m_pPainter;
}

/**
*  @brief
*    Returns the whether the surface is flipped along the y axis
*/
inline bool Surface::IsSwapY() const
{
	return m_bSwapY;
}

/**
*  @brief
*    Sets the whether the surface is flipped along the y axis
*/
inline void Surface::SetSwapY(bool bSwapY)
{
	m_bSwapY = bSwapY;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
