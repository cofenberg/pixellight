/*********************************************************\
 *  File: Connection.inl                                 *
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
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get host that owns this connection
*/
inline const Host &Connection::GetHost() const
{
	// Return host
	return *m_pHost;
}

/**
*  @brief
*    Get host that owns this connection
*/
inline Host &Connection::GetHost()
{
	// Return host
	return *m_pHost;
}

/**
*  @brief
*    Get name of connected host
*/
inline String Connection::GetHostname() const
{
	// Return host name
	return m_sHostname;
}

/**
*  @brief
*    Get port
*/
inline uint32 Connection::GetPort() const
{
	// Return port number
	return m_nPort;
}

/**
*  @brief
*    Get socket
*/
inline const Socket &Connection::GetSocket() const
{
	// Return socket
	return m_cSocket;
}

/**
*  @brief
*    Get socket
*/
inline Socket &Connection::GetSocket()
{
	// Return socket
	return m_cSocket;
}

/**
*  @brief
*    Check if connection is active
*/
inline bool Connection::IsConnected() const
{
	// Return state
	return m_bConnected;
}

/**
*  @brief
*    Get receive mode
*/
inline Connection::EReceiveMode Connection::GetReceiveMode() const
{
	// Return receive mode
	return m_nReceiveMode;
}

/**
*  @brief
*    Set receive mode
*/
inline void Connection::SetReceiveMode(EReceiveMode nReceiveMode)
{
	// Set receive mode
	m_nReceiveMode = nReceiveMode;
}

/**
*  @brief
*    Send data
*/
inline int Connection::Send(const char *pBuffer, uint32 nSize) const
{
	// Send data buffer
	return (pBuffer && nSize > 0) ? m_cSocket.Send(pBuffer, nSize) : -1;
}

/**
*  @brief
*    Send string
*/
inline int Connection::Send(const String &sString) const
{
	// Check if string is not empty
	if (sString.GetLength()) {
		// Send string
		// [TODO] What's with Unicode strings?? Check \0 at the end...
		return Send(sString.GetASCII(), sString.GetLength());
	}

	// Error, invalid string
	return -1;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
