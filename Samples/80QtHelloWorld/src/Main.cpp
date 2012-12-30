/*********************************************************\
 *  File: Main.cpp                                       *
 *      PixelLight Sample 80 - Qt
 *      Simple 'Hello World'-Application using PLFrontendQt
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLCore/ModuleMain.h>
#include <PLFrontendQt/QPLContext.h>
#include <PLFrontendQt/Application.h>
#include <PLFrontendQt/QPLRenderWindow.h>


//[-------------------------------------------------------]
//[ Module definition                                     ]
//[-------------------------------------------------------]
pl_module("80QtHelloWorld")
	pl_module_vendor("Copyright (C) 2002-2012 by The PixelLight Team")
	pl_module_license("GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version")
	pl_module_description("PixelLight Qt 80 - Hello world")
pl_module_end


//[-------------------------------------------------------]
//[ Program entry point                                   ]
//[-------------------------------------------------------]
int main(int argc, char **argv)
{
	// Create an "PLFrontendQt::Application"-instance
	PLFrontendQt::Application cApplication(argc, argv);

	// Create an "PLFrontendQt::QPLRenderWindow"-instance
	PLFrontendQt::QPLContext cContext;
	PLFrontendQt::QPLRenderWindow cWindow(&cContext);

	// Enable updating the renderer context via the application instance
	cApplication.EnableRendererContextUpdates(true);
	cApplication.SetContextForUpdate(&cContext);

	// Resize the window
	cWindow.resize(640, 480);

	// Make the window visible
	cWindow.show();

	// Start the event loop of Qt
	return cApplication.exec();
}
