/*********************************************************\
 *  File: FrontendAndroid.cpp                            *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
