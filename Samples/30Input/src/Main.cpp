/*********************************************************\
 *  File: Main.cpp                                       *
 *      PixelLight Sample 30 - Input
 *      Sample application showing how to use input devices with PLInput
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
#include <PLCore/Main.h>
#include <PLCore/ModuleMain.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Module definition                                     ]
//[-------------------------------------------------------]
pl_module("30Input")
	pl_module_vendor("Copyright (C) 2002-2011 by The PixelLight Team")
	pl_module_license("GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version")
	pl_module_description("PixelLight Sample 30 - Input")
pl_module_end


//[-------------------------------------------------------]
//[ Program entry point                                   ]
//[-------------------------------------------------------]
int PLMain(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	Application cApplication;
	return cApplication.Run(sExecutableFilename, lstArguments);
}
