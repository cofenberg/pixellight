/*********************************************************\
 *  File: WiiMote.h                                      *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLINPUT_WIIMOTE_H__
#define __PLINPUT_WIIMOTE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
#include <PLMath/Vector3.h>
#include <PLCore/Base/Event/EventHandler.h>
#include "PLInput/Input/Controls/Button.h"
#include "PLInput/Input/Controls/Axis.h"
#include "PLInput/Input/Controls/LED.h"
#include "PLInput/Input/Controls/Effect.h"
#include "PLInput/Input/Devices/Device.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class ConnectionDevice;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    WiiMote input device
*
*  @remarks
*    This class supports the following device backend types:
*    - ConnectionDevice
*/
class WiiMote : public Device {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLINPUT_RTTI_EXPORT, WiiMote, "PLInput", PLInput::Device, "WiiMote input controller")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Controller definition                                 ]
	//[-------------------------------------------------------]
	public:
		// LEDs and effects
		LED		LEDs;				/**< LEDs */
		Effect	Rumble1;			/**< Rumble effect (motor #1) */

		// Main buttons
		Button  Button1;			/**< Button '1' */
		Button  Button2;			/**< Button '2' */
		Button  ButtonA;			/**< Button 'A' */
		Button  ButtonB;			/**< Button 'B' */
		Button  ButtonMinus;		/**< Button 'Minus' */
		Button  ButtonPlus;			/**< Button 'Plus' */
		Button  ButtonHome;			/**< Button 'Home' */
		Button  ButtonLeft;			/**< Button 'Left' */
		Button  ButtonRight;		/**< Button 'Right' */
		Button  ButtonUp;			/**< Button 'Up' */
		Button  ButtonDown;			/**< Button 'Down' */

		// Main values
		Axis	AccX;				/**< Acceleration (X) */
		Axis	AccY;				/**< Acceleration (Y) */
		Axis	AccZ;				/**< Acceleration (Z) */
		Axis	OrientX;			/**< Orientation (X) */
		Axis	OrientY;			/**< Orientation (Y) */
		Axis	OrientZ;			/**< Orientation (Z) */
		Axis	Roll;				/**< Rotation (roll) */
		Axis	Pitch;				/**< Rotation (pitch) */
		Axis	PointerX;			/**< Pointer (X) */
		Axis	PointerY;			/**< Pointer (Y) */

		// Nunchuk
		Button  NunchukButtonC;		/**< Nunchuk Button 'C' */
		Button  NunchukButtonZ;		/**< Nunchuk Button 'Z' */
		Axis	NunchukAccX;		/**< Nunchuk Acceleration (X) */
		Axis	NunchukAccY;		/**< Nunchuk Acceleration (Y) */
		Axis	NunchukAccZ;		/**< Nunchuk Acceleration (Z) */
		Axis	NunchukOrientX;		/**< Nunchuk Orientation (X) */
		Axis	NunchukOrientY;		/**< Nunchuk Orientation (Y) */
		Axis	NunchukOrientZ;		/**< Nunchuk Orientation (Z) */
		Axis	NunchukRoll;		/**< Nunchuk Rotation (roll) */
		Axis	NunchukPitch;		/**< Nunchuk Rotation (pitch) */
		Axis	NunchukX;			/**< Nunchuk joystick (X) */
		Axis	NunchukY;			/**< Nunchuk joystick (Y) */


	//[-------------------------------------------------------]
	//[ Public data types                                     ]
	//[-------------------------------------------------------]
	public:
		// Definitions
		enum EProductID {
			// HID definitions
			VendorID  = 0x057e,		/**< 'Nintendo' */
			ProductID = 0x0306,		/**< 'Wiimote' */

			// Bluetooth definitions
			DeviceClass0 = 0x04,
			DeviceClass1 = 0x25,
			DeviceClass2 = 0x00
		};

		/**
		*  @brief
		*    Report type
		*/
		enum EReport {
			ReportStatus			= 0x20,		/**< Status report */
			ReportReadMemory		= 0x21,		/**< Data from memory */
			ReportButtons			= 0x30,		/**< Buttons */
			ReportButtonsAccel		= 0x31,		/**< Buttons and acceleration */
			ReportButtonsAccelIR	= 0x33,		/**< Buttons, acceleration and IR (extended) */
			ReportButtonsAccelExt	= 0x35,		/**< Buttons, acceleration and extension */
			ReportButtonsAccelIRExt	= 0x37		/**< Buttons, acceleration, IR (basic) and extension */
		};

		/**
		*  @brief
		*    Infrared sensor mode
		*/
		enum EIRMode {
			IROff					= 0x00,		/**< IR off */
			IRBasic					= 0x01,		/**< Basic IR mode */
			IRExtended				= 0x03,		/**< Extended IR mode */
			IRFull					= 0x05		/**< Full IR mode */
		};

		/**
		*  @brief
		*    WiiMote extension
		*/
		enum EExtension {
			ExtNone					= 0x0000,	/**< No extension */
			ExtNunchuk				= 0xfefe,	/**< Nunchuk */
			ExtClassic				= 0xfdfd,	/**< Classic controller */
			ExtPartiallyInserted	= 0xffff	/**< Extension not inserted correctly */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sName
		*    Device name
		*  @param[in] pImpl
		*    System specific device implementation, must be valid!
		*/
		PLINPUT_API WiiMote(const PLGeneral::String &sName, DeviceImpl *pImpl);

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~WiiMote();

		/**
		*  @brief
		*    Get report mode
		*
		*  @return
		*    Report mode
		*/
		PLINPUT_API EReport GetReportMode() const;

		/**
		*  @brief
		*    Set report mode
		*
		*  @param[in] nReportMode
		*    Report mode
		*  @param[in] bContinuous
		*    Continous updates?
		*/
		PLINPUT_API void SetReportMode(EReport nReportMode, bool bContinuous = false);

		/**
		*  @brief
		*    Get infrared mode
		*
		*  @return
		*    Infrared mode
		*/
		PLINPUT_API EIRMode GetIRMode() const;

		/**
		*  @brief
		*    Set infrared mode
		*
		*  @param[in] nIRMode
		*    Infrared mode
		*/
		PLINPUT_API void SetIRMode(EIRMode nIRMode);

		/**
		*  @brief
		*    Get extension
		*
		*  @return
		*    Extension type
		*/
		PLINPUT_API EExtension GetExtension() const;

		/**
		*  @brief
		*    Get battery state
		*
		*  @return
		*    Battery state
		*/
		PLINPUT_API PLGeneral::uint8 GetBattery() const;

		/**
		*  @brief
		*    Calibrate device
		*/
		PLINPUT_API void Calibrate();


	//[-------------------------------------------------------]
	//[ Public virtual Controller functions                   ]
	//[-------------------------------------------------------]
	public:
		PLINPUT_API virtual void UpdateOutputControl(Control *pControl);


	//[-------------------------------------------------------]
	//[ Private data types                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Acceleration data
		*/
		struct SAcceleration {
			// Status
			int nUpdateNearG;		/**< Update counter when acceleration is near 1G */

			// Status
			float fAccX;			/**< Acceleration: X */
			float fAccY;			/**< Acceleration: Y */
			float fAccZ;			/**< Acceleration: Z */
			float fOrientX;			/**< Orientation:  X */
			float fOrientY;			/**< Orientation:  Y */
			float fOrientZ;			/**< Orientation:  Z */
			float fRoll;			/**< Angle:        Roll */
			float fPitch;			/**< Angle:        Pitch */

			// Calibration
			PLGeneral::uint8 nX0;	/**< Calibration: X0 */
			PLGeneral::uint8 nY0;	/**< Calibration: Y0 */
			PLGeneral::uint8 nZ0;	/**< Calibration: Z0 */
			PLGeneral::uint8 nXG;	/**< Calibration: XG */
			PLGeneral::uint8 nYG;	/**< Calibration: YG */
			PLGeneral::uint8 nZG;	/**< Calibration: ZG */

			// Calculate orientation from acceleration data
			void CalculateOrientation();
		};

		/**
		*  @brief
		*    Nunchuk joystick data
		*/
		struct SJoystick {
			// Status
			float fX;				/**< X position */
			float fY;				/**< Y position */

			// Calibration
			PLGeneral::uint8 nMinX;	/**< Calibration: Minimum X */
			PLGeneral::uint8 nMidX;	/**< Calibration: Middle  X */
			PLGeneral::uint8 nMaxX;	/**< Calibration: Maximum X */
			PLGeneral::uint8 nMinY;	/**< Calibration: Minimum Y */
			PLGeneral::uint8 nMidY;	/**< Calibration: Middle  Y */
			PLGeneral::uint8 nMaxY;	/**< Calibration: Maximum Y */
		};

		/**
		*  @brief
		*    IR sensor dot
		*/
		struct SDot {
			bool  bFound;	/**< The dot has been found */
			int   nRawX;	/**< Raw X position */
			int   nRawY;	/**< Raw Y position */
			float fX;		/**< X position (0..1) */
			float fY;		/**< Y position (0..1) */
			int   nSize;	/**< Dot size */
		};


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the HID device has been connected
		*/
		void OnDeviceConnect();

		/**
		*  @brief
		*    Called when the HID device has been disconnected
		*/
		void OnDeviceDisconnect();

		/**
		*  @brief
		*    Called when the HID device has read some data
		*/
		void OnDeviceRead();

		/**
		*  @brief
		*    Data from the WiiMote has been received
		*/
		void OnReadData();

		/**
		*  @brief
		*    Data from memory received
		*/
		void OnReadMemory();

		/**
		*  @brief
		*    Calibration data received
		*/
		void OnReadCalibration();

		/**
		*  @brief
		*    Extension information received
		*/
		void OnReadExtensionType();

		/**
		*  @brief
		*    Nunchuk calibration data received
		*/
		void OnReadNunchukCalibration();

		/**
		*  @brief
		*    Classic calibration data received
		*/
		void OnReadClassicCalibration();

		/**
		*  @brief
		*    Status information received
		*/
		void OnReadStatus();

		/**
		*  @brief
		*    Button status received
		*/
		void OnReadButtons();

		/**
		*  @brief
		*    Acceleration status received
		*/
		void OnReadAccel();

		/**
		*  @brief
		*    IR status received
		*/
		void OnReadIR();

		/**
		*  @brief
		*    Extension status received
		*/
		void OnReadExtension(PLGeneral::uint32 nOffset);

		/**
		*  @brief
		*    Nunchuk status received
		*/
		void OnReadNunchuk(PLGeneral::uint32 nOffset);

		/**
		*  @brief
		*    Classic-controller status received
		*/
		void OnReadClassic(PLGeneral::uint32 nOffset);

		/**
		*  @brief
		*    Read from WiiMote memory
		*
		*  @param[in] nAddress
		*    Address to read from
		*  @param[in] nSize
		*    Size to read
		*/
		void ReadMemory(int nAddress, PLGeneral::uint8 nSize);

		/**
		*  @brief
		*    Write to WiiMote memory
		*
		*  @param[in] nAddress
		*    Address to write to
		*  @param[in] pBuffer
		*    Buffer containing the data
		*  @param[in] nSize
		*    Size to write
		*/
		void WriteMemory(int nAddress, const PLGeneral::uint8* pBuffer, PLGeneral::uint8 nSize);

		/**
		*  @brief
		*    Write a single byte to WiiMote memory
		*
		*  @param[in] nAddress
		*    Address to write to
		*  @param[in] nData
		*    Byte to write
		*/
		void WriteMemory(int nAddress, PLGeneral::uint8 nData);

		/**
		*  @brief
		*    Clear output report
		*/
		void ClearReport();

		/**
		*  @brief
		*    Send data to WiiMote device
		*
		*  @param[in] pBuffer
		*    Pointer to buffer (must be valid!)
		*  @param[in] nSize
		*    Size of buffer
		*/
		void Send(PLGeneral::uint8 *pBuffer, PLGeneral::uint32 nSize);

		/**
		*  @brief
		*    Decrypt data
		*
		*  @param[in] nOffset
		*    Start address inside m_nWriteBuffer
		*  @param[in] nSize
		*    Size inside m_nWriteBuffer
		*/
		void DecryptBuffer(PLGeneral::uint32 nOffset, PLGeneral::uint32 nSize);

		/**
		*  @brief
		*    Get WiiMote status
		*/
		void SendStatusRequest();

		/**
		*  @brief
		*    Get calibration information
		*/
		void SendCalibrationRequest();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Event handlers
		PLCore::EventHandler<> EventHandlerOnDeviceConnect;
		PLCore::EventHandler<> EventHandlerOnDeviceDisconnect;
		PLCore::EventHandler<> EventHandlerOnDeviceRead;

		// HID connection
		ConnectionDevice	*m_pConnectionDevice;		/**< Connection device, always valid! */
		PLGeneral::uint8	*m_pInputBuffer;			/**< Input buffer */
		PLGeneral::uint8	*m_pOutputBuffer;			/**< Output buffer */

		// WiiMote options
		EReport				 m_nReportMode;				/**< Report mode */
		EIRMode				 m_nIRMode;					/**< IR mode */
		EExtension			 m_nExtension;				/**< Extension type */

		// WiiMote status
		PLGeneral::uint8	 m_nBattery;				/**< Battery (percent) */
		PLGeneral::uint8	 m_nLEDs;					/**< LEDs status */
		PLGeneral::uint8	 m_nRumble;					/**< Rumble state (1=on, 0=off) */
		PLGeneral::uint16	 m_nButtons;				/**< WiiMote Buttons */
		SAcceleration		 m_sAcc;					/**< Acceleration sensor */
		SDot				 m_sDots[2];				/**< IR dots */
		PLMath::Vector2		 m_vIRPos;					/**< IR position (X, Y between 0..1) */

		// Nunchuk status
		PLGeneral::uint16	 m_nNunchukButtons;			/**< Nunchuk buttons */
		SAcceleration		 m_sNunchukAcc;				/**< Nunchuk acceleration sensor */
		SJoystick			 m_sNunchukJoy;				/**< Nunchuk joystick */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_WIIMOTE_H__
