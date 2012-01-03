/*********************************************************\
 *  File: SensorManager.h                                *
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


#ifndef __PLINPUT_SENSORMANAGER_H__
#define __PLINPUT_SENSORMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Input/Devices/Device.h"
#include "PLInput/Input/Controls/Axis.h"
#include "PLInput/Input/Controls/Button.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sensor manager input device
*
*  @remarks
*    The sensor manager is a collection of sensors usually available on a mobile device:
*    - Accelerometer
*    - Magnetic field
*    - Gyroscope
*    - Light
*    - Proximity
*
*    This class supports the following device backend types:
*    - UpdateDevice
*/
class SensorManager : public Device {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLINPUT_RTTI_EXPORT, SensorManager, "PLInput", PLInput::Device, "Sensor manager input controller")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Controller definition                                 ]
	//[-------------------------------------------------------]
	public:
		// Accelerometer
		PLInput::Axis	AccelerationX;	/**< X acceleration axis (Accelerometer) */
		PLInput::Axis	AccelerationY;	/**< Y acceleration axis (Accelerometer) */
		PLInput::Axis	AccelerationZ;	/**< Z acceleration axis (Accelerometer) */
		// Magnetic field
		PLInput::Axis	MagneticX;		/**< X magnetic axis (Magnetic field) */
		PLInput::Axis	MagneticY;		/**< Y magnetic axis (Magnetic field) */
		PLInput::Axis	MagneticZ;		/**< Z magnetic axis (Magnetic field) */
		// Gyroscope
		PLInput::Axis	RotationX;		/**< X rotation axis (Gyroscope) */
		PLInput::Axis	RotationY;		/**< Y rotation axis (Gyroscope) */
		PLInput::Axis	RotationZ;		/**< Z rotation axis (Gyroscope) */
		// Light
		PLInput::Axis	Light;			/**< Light */
		// Proximity
		PLInput::Axis	Proximity;		/**< Proximity */


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
		*    System specific device implementation, can, but shouldn't be a null pointer
		*/
		PLINPUT_API SensorManager(const PLCore::String &sName, DeviceImpl *pImpl);

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~SensorManager();


	//[-------------------------------------------------------]
	//[ Public virtual Controller functions                   ]
	//[-------------------------------------------------------]
	public:
		PLINPUT_API virtual void Update() override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_SENSORMANAGER_H__
