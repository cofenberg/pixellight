/*********************************************************\
 *  File: VertexBuffer.inl                               *
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Core/MemoryManager.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the number of vertex attributes
*/
inline PLCore::uint32 VertexBuffer::GetNumOfVertexAttributes() const
{
	return m_lstVertexAttributes.GetNumOfElements();
}

/**
*  @brief
*    Returns a vertex attribute
*/
inline const VertexBuffer::Attribute *VertexBuffer::GetVertexAttribute(PLCore::uint32 nIndex) const
{
	return m_lstVertexAttributes[nIndex];
}

/**
*  @brief
*    Returns the vertex size in bytes
*/
inline PLCore::uint32 VertexBuffer::GetVertexSize() const
{
	return m_nVertexSize;
}

/**
*  @brief
*    Copies data from a given buffer into this vertex buffer
*/
inline void VertexBuffer::CopyFrom(const void *pData)
{
	// Lock the vertex buffer
	if (Lock(Lock::WriteOnly)) {
		// Copy over all the vertex data at once
		PLCore::MemoryManager::Copy(GetData(), pData, GetSize());

		// Unlock the vertex buffer
		Unlock();
	}
}

/**
*  @brief
*    Copies data from this vertex buffer into a given buffer
*/
inline void VertexBuffer::CopyTo(void *pData)
{
	// Lock the vertex buffer
	if (Lock(Lock::ReadOnly)) {
		// Copy over all the vertex data at once
		PLCore::MemoryManager::Copy(pData, GetData(), GetSize());

		// Unlock the vertex buffer
		Unlock();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
