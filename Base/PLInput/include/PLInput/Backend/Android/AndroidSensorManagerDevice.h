/*********************************************************\
 *  File: AndroidSensorManagerDevice.h                   *
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


#ifndef __PLINPUT_ANDROIDSENSORMANAGERDEVICE_H__
#define __PLINPUT_ANDROIDSENSORMANAGERDEVICE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Backend/UpdateDevice.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
struct ASensorManager;
typedef struct ASensorManager ASensorManager;
struct ASensorEventQueue;
typedef struct ASensorEventQueue ASensorEventQueue;
struct ASensor;
typedef struct ASensor ASensor;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sensor manager implementation for Android
*/
class AndroidSensorManagerDevice : public UpdateDevice {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		AndroidSensorManagerDevice();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~AndroidSensorManagerDevice();


	//[-------------------------------------------------------]
	//[ Public virtual UpdateDevice functions                 ]
	//[-------------------------------------------------------]
	public:
		virtual void Update() override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		ASensorManager    *m_pSensorManager;		/**< Android sensor manager, can be a null pointer */
		ASensorEventQueue *m_pSensorEventQueue;		/**< Sensor event queue, can be a null pointer */
		const ASensor     *m_pAccelerometerSensor;	/**< Accelerometer sensor, can be a null pointer */
		const ASensor     *m_pMagneticFieldSensor;	/**< Magnetic field sensor, can be a null pointer */
		const ASensor     *m_pGyroscopeSensor;		/**< Gyroscope sensor, can be a null pointer */
		const ASensor     *m_pLightSensor;			/**< Light sensor, can be a null pointer */
		const ASensor     *m_pProximitySensor;		/**< Proximity sensor, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_ANDROIDSENSORMANAGERDEVICE_H__
