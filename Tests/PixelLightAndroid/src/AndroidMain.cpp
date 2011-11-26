/*********************************************************\
 *  File: FrontendAndroid.cpp                            *
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
#include <PLCore/Frontend/FrontendContext.h>
#include <PLFrontendOS/FrontendAndroid.h>


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Program entry point
*
*  @remarks
*    This is the main entry point of a native application that is using
*    android_native_app_glue. It runs in its own thread, with its own
*    event loop for receiving input events and doing other things.
*/
void android_main(struct android_app* state)
{
	// Make sure glue isn't stripped
	app_dummy();

	// Setup the frontend context and tell it about the RTTI class name of the application to start
	PLCore::FrontendContext cFrontendContext;
	cFrontendContext.SetFrontendParameters("ApplicationClass=\"Application67\"");

	// Create a frontend instance on the C runtime stack
	PLFrontendOS::FrontendAndroid cFrontendAndroid(cFrontendContext, *state);

	// Finish the given activity
	ANativeActivity_finish(state->activity);
}
