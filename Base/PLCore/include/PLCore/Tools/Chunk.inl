/*********************************************************\
 *  File: Chunk.inl                                      *
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
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the semantic
*/
inline Chunk::ESemantic Chunk::GetSemantic() const
{
	return m_nSemantic;
}

/**
*  @brief
*    Sets the semantic
*/
inline void Chunk::SetSemantic(ESemantic nSemantic)
{
	m_nSemantic = nSemantic;
}

/**
*  @brief
*    Returns the chunk data
*/
inline uint8 *Chunk::GetData()
{
	return m_pData;
}

/**
*  @brief
*    Returns the chunk data
*/
inline const uint8 *Chunk::GetData() const
{
	return m_pData;
}

/**
*  @brief
*    Returns the chunk element component data
*/
inline uint8 *Chunk::GetElementComponentData(uint32 nElement, uint32 nComponent)
{
	return &m_pData[nElement*GetNumOfBytesPerElement() + nComponent*GetNumOfBytesPerElementComponent()];
}

/**
*  @brief
*    Returns the chunk element component data
*/
inline const uint8 *Chunk::GetElementComponentData(uint32 nElement, uint32 nComponent) const
{
	return &m_pData[nElement*GetNumOfBytesPerElement() + nComponent*GetNumOfBytesPerElementComponent()];
}

/**
*  @brief
*    Returns the element type
*/
inline Chunk::EElementType Chunk::GetElementType() const
{
	return m_nElementType;
}

/**
*  @brief
*    Returns the number of components per element
*/
inline uint32 Chunk::GetNumOfComponentsPerElement() const
{
	return m_nNumOfComponentsPerElement;
}

/**
*  @brief
*    Returns the number of elements
*/
inline uint32 Chunk::GetNumOfElements() const
{
	return m_nNumOfElements;
}

/**
*  @brief
*    Returns the number of bytes per element
*/
inline uint32 Chunk::GetNumOfBytesPerElement() const
{
	return GetNumOfBytesPerElementComponent()*m_nNumOfComponentsPerElement;
}

/**
*  @brief
*    Returns the total number of bytes of the chunk data
*/
inline uint32 Chunk::GetTotalNumOfBytes() const
{
	return GetNumOfBytesPerElement()*m_nNumOfElements;
}

/**
*  @brief
*    Returns the total number of components (all elements summed up) within the chunk
*/
inline uint32 Chunk::GetTotalNumOfComponents() const
{
	return m_nNumOfComponentsPerElement*m_nNumOfElements;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
