/*********************************************************\
 *  File: ContextEmulator.h                              *
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
#include <PLCore/Log/Log.h>
#include "PLRendererOpenGLES2/ContextEmulator.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Public methods                                        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ContextEmulator::ContextEmulator(Renderer &cRenderer) : Context(cRenderer)
{
	// We're linking against the emulator libaries, so, nothing to do in here
}

/**
*  @brief
*    Destructor
*/
ContextEmulator::~ContextEmulator()
{
	// Release all resources allocated by the shader compiler
	glReleaseShaderCompiler();

	// Return EGL to it's state at thread initialization
	if (eglReleaseThread() == EGL_FALSE) {
		// Error!
		PL_LOG(Error, "Failed to release the EGL thread!")
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
