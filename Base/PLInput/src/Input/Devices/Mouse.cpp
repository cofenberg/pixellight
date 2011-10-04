/*********************************************************\
 *  File: Mouse.cpp                                      *
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
#include "PLInput/Input/Devices/Mouse.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLInput {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(Mouse)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Mouse::Mouse(const String &sName, DeviceImpl *pImpl) : Device(sName, "Mouse input controller", pImpl),
	X		(this, "X",			"X axis"),
	Y		(this, "Y",			"Y axis"),
	Wheel	(this, "Wheel",		"Mouse wheel"),
	Left	(this, "Left",		"Left mouse button (mouse button #0)"),
	Right	(this, "Right",		"Right mouse button (mouse button #1)"),
	Middle	(this, "Middle",	"Middle mouse button (mouse button #2)"),
	Button4	(this, "Button4",	"Mouse button #4"),
	Button5	(this, "Button5",	"Mouse button #5"),
	Button6	(this, "Button6",	"Mouse button #6"),
	Button7	(this, "Button7",	"Mouse button #7"),
	Button8	(this, "Button8",	"Mouse button #8"),
	Button9	(this, "Button9",	"Mouse button #9"),
	Button10(this, "Button10",	"Mouse button #10"),
	Button11(this, "Button11",	"Mouse button #11"),
	Button12(this, "Button12",	"Mouse button #12")
{
}

/**
*  @brief
*    Destructor
*/
Mouse::~Mouse()
{
}


//[-------------------------------------------------------]
//[ Public virtual Controller functions                   ]
//[-------------------------------------------------------]
void Mouse::Update()
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
