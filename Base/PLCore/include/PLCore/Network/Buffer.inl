/*********************************************************\
 *  File: Buffer.inl                                     *
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
*    Destructor
*/
inline Buffer::~Buffer()
{
	// Destroy buffer
	Clear();
}

/**
*  @brief
*    Get option for removing line delimiters
*/
inline bool Buffer::GetRemoveLineDelimiters() const
{
	// Return option
	return m_bRemoveDelimiters;
}

/**
*  @brief
*    Set option for removing line delimiters
*/
inline void Buffer::SetRemoveLineDelimiters(bool bRemoveDelimiters)
{
	// Set option
	m_bRemoveDelimiters = bRemoveDelimiters;
}

/**
*  @brief
*    Get current buffer size
*/
inline uint32 Buffer::GetSize() const
{
	// Return size
	return m_nSize;
}

/**
*  @brief
*    Get data
*/
inline const char *Buffer::GetData() const
{
	// Return data pointer
	return m_pBuffer;
}

/**
*  @brief
*    Get data
*/
inline char *Buffer::GetData()
{
	// Return data pointer
	return m_pBuffer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
