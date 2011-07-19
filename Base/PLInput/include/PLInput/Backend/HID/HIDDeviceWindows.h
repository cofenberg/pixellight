/*********************************************************\
 *  File: HIDDeviceWindows.h                             *
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


#ifndef __PLINPUT_HIDDEVICE_WINDOWS_H__
#define __PLINPUT_HIDDEVICE_WINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Backend/HID/HIDDevice.h"
#include "PLInput/PLInputWindowsIncludes.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Windows implementation of 'HIDDevice'
*/
class HIDDeviceWindows : public HIDDevice {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class HIDWindows;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLINPUT_API HIDDeviceWindows();

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~HIDDeviceWindows();


	//[-------------------------------------------------------]
	//[ Protected virtual HIDDevice functions                 ]
	//[-------------------------------------------------------]
	protected:
		PLINPUT_API virtual void ParseInputReportData(const PLCore::uint8 *pInputReport, PLCore::uint32 nSize);
		PLINPUT_API virtual void SendOutputReportData();


	//[-------------------------------------------------------]
	//[ Public virtual ConnectionDevice functions             ]
	//[-------------------------------------------------------]
	public:
		PLINPUT_API virtual bool Open(PLCore::uint16 nOutputPort = 0, PLCore::uint16 nInputPort = 0);
		PLINPUT_API virtual bool Close();
		PLINPUT_API virtual bool IsOpen() const;
		PLINPUT_API virtual bool Read(PLCore::uint8 *pBuffer, PLCore::uint32 nSize);
		PLINPUT_API virtual bool Write(const PLCore::uint8 *pBuffer, PLCore::uint32 nSize);


	//[-------------------------------------------------------]
	//[ Private static functions                              ]
	//[-------------------------------------------------------]
	private:
		static void CALLBACK OnReadComplete (DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped);
		static void CALLBACK OnWriteComplete(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped);


	//[-------------------------------------------------------]
	//[ Private data types                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Data structure for asynchronous IO
		*/
		struct ExtendedOverlapped {
			OVERLAPPED		  sOverlapped;
			HIDDeviceWindows *pDevice;
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		HANDLE					m_hDevice;			/**< HID device handle */
		PHIDP_PREPARSED_DATA	m_pPreparsedData;	/**< HID preparsed data */
		ExtendedOverlapped		m_sOverlapped;		/**< Data for asynchronous IO */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_HIDDEVICE_WINDOWS_H__
