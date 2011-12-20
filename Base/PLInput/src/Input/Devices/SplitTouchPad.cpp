/*********************************************************\
 *  File: SplitTouchPad.cpp                              *
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
#include "PLInput/Input/Devices/SplitTouchPad.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLInput {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(SplitTouchPad)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SplitTouchPad::SplitTouchPad(const String &sName, DeviceImpl *pImpl) : Device(sName, "Gamepad device emulation by using a touch screen making it possible to e.g. move & look at the same time", pImpl),
	LeftX	(this, "LeftX",		"Absolute x axis on the left touchscreen side"),
	LeftY	(this, "LeftY",		"Absolute y axis on the left touchscreen side"),
	RightX	(this, "RightX",	"Absolute x axis on the right touchscreen side"),
	RightY	(this, "RightY",	"Absolute y axis on the right touchscreen side")
{
}

/**
*  @brief
*    Destructor
*/
SplitTouchPad::~SplitTouchPad()
{
}


//[-------------------------------------------------------]
//[ Public virtual Controller functions                   ]
//[-------------------------------------------------------]
void SplitTouchPad::Update()
{
	// Update device backend
	if (m_pImpl && m_pImpl->GetBackendType() == BackendUpdateDevice)
		static_cast<UpdateDevice*>(m_pImpl)->Update();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
