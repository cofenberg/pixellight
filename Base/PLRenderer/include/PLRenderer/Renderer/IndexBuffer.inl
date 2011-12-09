/*********************************************************\
 *  File: IndexBuffer.inl                                *
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
*    Returns the type of the buffer elements
*/
inline IndexBuffer::EType IndexBuffer::GetElementType() const
{
	return m_nElementType;
}

/**
*  @brief
*    Sets the type of the buffer elements
*/
inline bool IndexBuffer::SetElementType(EType nType)
{
	// Is the index buffer already allocated?
	if (IsAllocated())
		return false; // Error!

	// Set element type
	m_nElementType = nType;

	// Done
	return true;
}

/**
*  @brief
*    Sets the type of the buffer elements automatically by using a given maximum vertex index
*/
inline bool IndexBuffer::SetElementTypeByMaximumIndex(PLCore::uint32 nMaximumIndex)
{
	// Is the index buffer already allocated?
	if (IsAllocated())
		return false; // Error!

	// Set element type
	if (nMaximumIndex <= MaxVertexIndexUByte)
		m_nElementType = UByte;
	else
		m_nElementType = (nMaximumIndex <= MaxVertexIndexUShort) ? UShort : UInt;

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
