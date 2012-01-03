/*********************************************************\
 *  File: Buffer.inl                                     *
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
*    Returns the number of buffer elements
*/
inline PLCore::uint32 Buffer::GetNumOfElements() const
{
	return m_nElements;
}

/**
*  @brief
*    Returns the buffer size
*/
inline PLCore::uint32 Buffer::GetSize() const
{
	return m_nSize;
}

/**
*  @brief
*    Returns the usage flag
*/
inline Usage::Enum Buffer::GetUsage() const
{
	return m_nUsage;
}

/**
*  @brief
*    Returns whether the buffer is managed or not
*/
inline bool Buffer::IsManaged() const
{
	return m_bManaged;
}

/**
*  @brief
*    Returns the lock count
*/
inline PLCore::uint16 Buffer::GetLockCount() const
{
	return m_nLockCount;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Forces immediately vertex buffer unlock
*/
inline bool Buffer::ForceUnlock()
{
	// Is the buffer locked?
	if (!m_nLockCount)
		return false; // Error!

	// Force unlock now!
	m_nLockCount = 1;
	return Unlock();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
