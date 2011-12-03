/*********************************************************\
 *  File: Pipe.inl                                       *
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
*    Constructor
*/
inline Pipe::Pipe()
{
	// Initialize handles
	m_hPipe[0] = INVALID_HANDLE;
	m_hPipe[1] = INVALID_HANDLE;
}

/**
*  @brief
*    Copy constructor
*/
inline Pipe::Pipe(const Pipe &cSource)
{
	// Copy Pipe
	m_sName		= cSource.m_sName;
	m_hPipe[0]  = cSource.m_hPipe[0];
	m_hPipe[1]  = cSource.m_hPipe[1];
}

/**
*  @brief
*    Destructor
*/
inline Pipe::~Pipe()
{
}

/**
*  @brief
*    Assignment operator
*/
inline Pipe &Pipe::operator =(const Pipe &cSource)
{
	// Copy Pipe
	m_sName		= cSource.m_sName;
	m_hPipe[0]  = cSource.m_hPipe[0];
	m_hPipe[1]  = cSource.m_hPipe[1];
	return *this;
}

/**
*  @brief
*    Comparison operator
*/
inline bool Pipe::operator ==(const Pipe &cSource) const
{
	// Compare
	return (m_sName == cSource.m_sName && m_hPipe[0] == cSource.m_hPipe[0] && m_hPipe[1] == cSource.m_hPipe[1]);
}

/**
*  @brief
*    Comparison operator
*/
inline bool Pipe::operator !=(const Pipe &cSource) const
{
	// Compare
	return (m_sName != cSource.m_sName || m_hPipe[0] != cSource.m_hPipe[0] || m_hPipe[1] != cSource.m_hPipe[1]);
}

/**
*  @brief
*    Open a pipe by file handles
*/
inline bool Pipe::Open(handle hRead, handle hWrite)
{
	// Save file handles
	m_hPipe[0] = hRead;
	m_hPipe[1] = hWrite;

	// Done
	return true;
}

/**
*  @brief
*    Close both sides of the pipe
*/
inline bool Pipe::Close()
{
	// Close read and write
	return (CloseRead() && CloseWrite());
}

/**
*  @brief
*    Get name of pipe
*/
inline String Pipe::GetName() const
{
	// Return name
	return m_sName;
}

/**
*  @brief
*    Get read handle for the pipe
*/
inline handle Pipe::GetReadHandle() const
{
	// Return read-end
	return m_hPipe[0];
}

/**
*  @brief
*    Get write handle for the pipe
*/
inline handle Pipe::GetWriteHandle() const
{
	// Return write-end
	return m_hPipe[1];
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
