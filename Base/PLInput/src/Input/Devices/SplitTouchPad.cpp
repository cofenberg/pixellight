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
SplitTouchPad::SplitTouchPad(const String &sName, DeviceImpl *pImpl) : Device(sName, "Splitscreen input for touchscreen devices", pImpl),
	LeftX	(this, "LeftX",		"X axis on the left touchscreen side (movement data, no absolute data)"),
	LeftY	(this, "LeftY",		"Y axis on the left touchscreen side (movement data, no absolute data)"),
	RightX	(this, "RightX",	"X axis on the right touchscreen side (movement data, no absolute data)"),
	RightY	(this, "RightY",	"Y axis on the right touchscreen side (movement data, no absolute data)")
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
