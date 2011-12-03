/*********************************************************\
 *  File: Host.inl                                       *
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
*    Check if the host is currently listening for new connections
*/
inline bool Host::IsListening() const
{
	// Return listening status
	return m_bListening;
}

/**
*  @brief
*    Close host (close all connections and stop listening for new connections)
*/
inline void Host::Close()
{
	// Close port (stop listening)
	ClosePort();

	// Close all connections
	CloseConnections();
}

/**
*  @brief
*    Returns the currently used port number
*/
inline uint32 Host::GetPort() const
{
	// Return host port
	return m_nPort;
}

/**
*  @brief
*    Returns the maximum number of allowed connections
*/
inline uint32 Host::GetMaxConnections() const
{
	// Return maximum number of connections
	return m_nMaxConnections;
}

/**
*  @brief
*    Sets the maximum number of allowed connections
*/
inline void Host::SetMaxConnections(uint32 nMaxConnections)
{
	// Set maximum number of connections
	m_nMaxConnections = nMaxConnections;
}

/**
*  @brief
*    Get list of active connection
*/
inline const Container<Connection*> &Host::GetConnections() const
{
	// Return connection list
	return m_lstConnections;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Adds a connection
*/
inline void Host::AddConnection(Connection *pConnection)
{
	// Check if connection pointer is valid
	if (pConnection) {
		// Add connection
		m_lstConnections.Add(pConnection);
	}
}

/**
*  @brief
*    Removes a connection
*/
inline void Host::RemoveConnection(Connection *pConnection)
{
	// Check if connection pointer is valid
	if (pConnection) {
		// Remove connection
		m_lstConnections.Remove(pConnection);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
