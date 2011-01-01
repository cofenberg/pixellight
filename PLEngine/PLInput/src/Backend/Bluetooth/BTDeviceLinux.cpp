/*********************************************************\
 *  File: BTDeviceLinux.cpp                              *
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <memory.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <PLGeneral/Core/MemoryManager.h>
#include "PLInput/Backend/Bluetooth/BTDevice.h"
#include "PLInput/Backend/Bluetooth/BTDeviceLinux.h"


//[-------------------------------------------------------]
//[ Bluetooth definitions                                 ]
//[-------------------------------------------------------]
#include <asm/byteorder.h>

#define htobs(a)        __cpu_to_le16(a)
#define BTPROTO_L2CAP   0

typedef struct {
	unsigned char b[6];
} __attribute__((packed)) bdaddr_t;

struct sockaddr_l2 {
	sa_family_t     l2_family;
	unsigned short  l2_psm;
	bdaddr_t        l2_bdaddr;
};


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
/**
*  @brief
*    Bluetooth transport types
*/
enum ETrans {
	TransHandshake				= 0x00,		// Handshake request
	TransSetReport				= 0x50,		// Report request
	TransData					= 0xA0		// Data request
};

/**
*  @brief
*    Bluetooth parameters
*/
enum EParam {
	ParamInput					= 0x01,		// Input
	ParamOutput					= 0x02,		// Output
	ParamFeature				= 0x03		// Feature
};

/**
*  @brief
*    Bluetooth handshake responses
*/
enum EResult {
	ResultSuccess				= 0x00,		// Handshake OK
	ResultNotReady				= 0x01,		// Device not ready
	ResultErrInvalidReportID	= 0x02,		// Error: Invalid report ID
	ResultErrUnsupportedRequest	= 0x03,		// Error: Unsupported Request
	ResultErrInvalidParameter	= 0x04,		// Error: Invalid parameter
	ResultErrUnknown			= 0x0E,		// Error: Unknown error
	ResultErrFatal				= 0x0F		// Error: Fatal error
};

// Internals
static const int BufferSize		= 128;		// Size of temporary read/write buffer


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLInput {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BTDeviceLinux::BTDeviceLinux() :
	m_nCtrlSocket(0),
	m_nIntSocket(0)
{
	// Do not destroy device implementation automatically, because this is managed by BTLinux
	m_bDelete = false;
}

/**
*  @brief
*    Destructor
*/
BTDeviceLinux::~BTDeviceLinux()
{
}

/**
*  @brief
*    Read handshake response
*/
bool BTDeviceLinux::ReadHandshake()
{
	unsigned char nHandshake;
	if (read(m_nCtrlSocket, &nHandshake, 1) != 1) {
		// Error: Could not read handshake
		return false;
	} else if ((nHandshake & 0xF0) != TransHandshake) {
		// Error: Did not receive handshake
		return false;
	} else if ((nHandshake & 0x0F) != ResultSuccess) {
		// Error: Handshake non-successul
		switch (nHandshake & 0x0F) {
			case ResultNotReady:
			case ResultErrInvalidReportID:
			case ResultErrUnsupportedRequest:
			case ResultErrInvalidParameter:
			case ResultErrUnknown:
			case ResultErrFatal:
				break;
		}
		return false;
	}

	// Handshake successful
	return true;
}


//[-------------------------------------------------------]
//[ Public virtual ConnectionDevice functions             ]
//[-------------------------------------------------------]
bool BTDeviceLinux::Open(uint16 nOutputPort, uint16 nInputPort)
{
	// Create socket address for control socket
	struct sockaddr_l2 sCtrlAddr;
	MemoryManager::Set(&sCtrlAddr, 0, sizeof(sCtrlAddr));
	sCtrlAddr.l2_family		 = AF_BLUETOOTH;
	sCtrlAddr.l2_bdaddr.b[0] = GetAddress(0);
	sCtrlAddr.l2_bdaddr.b[1] = GetAddress(1);
	sCtrlAddr.l2_bdaddr.b[2] = GetAddress(2);
	sCtrlAddr.l2_bdaddr.b[3] = GetAddress(3);
	sCtrlAddr.l2_bdaddr.b[4] = GetAddress(4);
	sCtrlAddr.l2_bdaddr.b[5] = GetAddress(5);
	sCtrlAddr.l2_psm		 = htobs(nOutputPort);

	// Create socket address for interrupt socket
	struct sockaddr_l2 sIntAddr;
	MemoryManager::Set(&sIntAddr, 0, sizeof(sIntAddr));
	sIntAddr.l2_family		= AF_BLUETOOTH;
	sIntAddr.l2_bdaddr.b[0] = GetAddress(0);
	sIntAddr.l2_bdaddr.b[1] = GetAddress(1);
	sIntAddr.l2_bdaddr.b[2] = GetAddress(2);
	sIntAddr.l2_bdaddr.b[3] = GetAddress(3);
	sIntAddr.l2_bdaddr.b[4] = GetAddress(4);
	sIntAddr.l2_bdaddr.b[5] = GetAddress(5);
	sIntAddr.l2_psm			= htobs(nInputPort);

	// Create output socket
	m_nCtrlSocket = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
	if (connect(m_nCtrlSocket, (struct sockaddr*)&sCtrlAddr, sizeof(sCtrlAddr)) == 0) {
		// Create input socket
		m_nIntSocket = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
		if (connect(m_nIntSocket, (struct sockaddr*)&sIntAddr, sizeof(sIntAddr)) == 0) {
			// Connection successful
			int nFlags = fcntl(m_nIntSocket, F_GETFL, 0);
			fcntl(m_nIntSocket, F_SETFL, nFlags | O_NONBLOCK);

			// Start read-thread
			InitThread();

			// Device connected
			EventOnConnect.Emit();

			return true;
		}
	}

	// Error!
	return false;
}

bool BTDeviceLinux::Close()
{
	// Stop read-thread
	StopThread();

	// Device disconnected
	EventOnDisconnect.Emit();

	// Close sockets
	close(m_nCtrlSocket);
	close(m_nIntSocket);
	return true;
}

bool BTDeviceLinux::IsOpen() const
{
	// Check sockets
	return (m_nCtrlSocket != 0 && m_nIntSocket != 0);
}

bool BTDeviceLinux::Read(uint8 *pBuffer, uint32 nSize)
{
	// Read data
	LockMutex();
	uint8 nTemp[BufferSize];
	int nRes = read(m_nIntSocket, nTemp, nSize+1);
	if (nRes > 0) {
		if (nTemp[0] == (TransData | ParamInput)) {
			memcpy(pBuffer, &nTemp[1], nRes-1);
			UnlockMutex();
			EventOnRead.Emit();
			return true;
		}
	}

	// Error!
	UnlockMutex();
	return false;
}

bool BTDeviceLinux::Write(const uint8 *pBuffer, uint32 nSize)
{
	// Write data
	LockMutex();
	uint8 nTemp[BufferSize];
	nTemp[0] = TransSetReport | ParamOutput;
	MemoryManager::Copy(nTemp+1, pBuffer, nSize);
	int nRes = write(m_nCtrlSocket, nTemp, nSize+1);
	ReadHandshake();
	UnlockMutex();
	if (nRes > 0) return ((uint32)nRes - 1 == nSize);
	else		  return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
