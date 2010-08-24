/*********************************************************\
 *  File: Main.cpp                                       *
 *      This is demo will show you how to render to texture. (RTT)
 *      The teapot from the teapot demo is rendered to a texture which is
 *      used by some colorful quadrangles similar to the triangle demo.
 *      Also multi render targets (MRT) are shown. Using MRT you can render to
 *      multiple textures at the same time using a fragmet shader. (MultiRenderTargets.cg)
 *      Further vertex streaming is shown. Vertex position and texture coordinate data is stored
 *      in another vertex buffer as the color data.
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Main.h>
#include <PLCore/ModuleMain.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Module implementation                                 ]
//[-------------------------------------------------------]
pl_module("PLDemoRendererRTT")
	pl_module_vendor("Copyright (C) 2002-2010 by The PixelLight Team")
	pl_module_license("GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version")
	pl_module_description("PixelLight render to texture demo")
pl_module_end


//[-------------------------------------------------------]
//[ Program entry point                                   ]
//[-------------------------------------------------------]
int PLMain(const String &sFilename, const Array<String> &lstArguments)
{
	Application cApplication;
	return cApplication.Run(sFilename, lstArguments);
}
