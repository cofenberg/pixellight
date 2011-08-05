/*********************************************************\
 *  File: OSWindowLinux.cpp                              *
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
#include "PLFrontendOS/Frontend.h"
#include "PLFrontendOS/OSWindowLinux.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendOS {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
OSWindowLinux::OSWindowLinux(Frontend &cFrontendOS)
{
	// Tell the frontend about this instance at once because it may already be required during frontend lifecycle initialization
	m_pFrontendOS->m_pOSWindow = this;

	// Connect Linux signals
//	signal(SIGINT,  CoreApplication::SignalHandler);
//	signal(SIGTERM, CoreApplication::SignalHandler);
}

/**
*  @brief
*    Destructor
*/
OSWindowLinux::~OSWindowLinux()
{
}


//[-------------------------------------------------------]
//[ Private virtual OSWindow functions                    ]
//[-------------------------------------------------------]
handle OSWindowLinux::GetNativeWindowHandle() const
{
	return NULL_HANDLE;
}

void OSWindowLinux::Redraw()
{
}

bool OSWindowLinux::Ping()
{
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendOS
