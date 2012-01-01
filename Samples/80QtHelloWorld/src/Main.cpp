/*********************************************************\
 *  File: Main.cpp                                       *
 *      PixelLight Sample 80 - Qt
 *      Simple 'Hello World'-Application using PLFrontendQt
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
