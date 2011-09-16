/*********************************************************\
 *  File: SensorManager.cpp                              *
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
#include "PLInput/Backend/UpdateDevice.h"
#include "PLInput/Input/Devices/SensorManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLInput {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(SensorManager)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SensorManager::SensorManager(const String &sName, DeviceImpl *pImpl) : Device(sName, "Sensor manager input controller", pImpl),
	// Accelerometer
	AccelerationX	(this,	"AccelerationX",	"X acceleration axis (Accelerometer)"),
	AccelerationY	(this,	"AccelerationY",	"Y acceleration axis (Accelerometer)"),
	AccelerationZ	(this,	"AccelerationZ",	"Z acceleration axis (Accelerometer)"),
	// Magnetic field
	MagneticX		(this,	"MagneticX",		"X magnetic axis (Magnetic field)"),
	MagneticY		(this,	"MagneticY",		"Y magnetic axis (Magnetic field)"),
	MagneticZ		(this,	"MagneticZ",		"Z magnetic axis (Magnetic field)"),
	// Gyroscope
	RotationX		(this,	"RotationX",		"X rotation axis (Gyroscope)"),
	RotationY		(this,	"RotationY",		"Y rotation axis (Gyroscope)"),
	RotationZ		(this,	"RotationZ",		"Z rotation axis (Gyroscope)"),
	// Light
	Light			(this,	"Light",			"Light"),
	// Proximity
	Proximity		(this,	"Proximity",		"Proximity")
{
}

/**
*  @brief
*    Destructor
*/
SensorManager::~SensorManager()
{
}


//[-------------------------------------------------------]
//[ Public virtual Controller functions                   ]
//[-------------------------------------------------------]
void SensorManager::Update()
{
	// Update device backend
	if (m_pImpl && m_pImpl->GetBackendType() == BackendUpdateDevice) {
		static_cast<UpdateDevice*>(m_pImpl)->Update();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
