/*********************************************************\
 *  File: Main.cpp                                       *
 *      PixelLight Sample 82 - Qt
 *      Simple input handling application using PLQt
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
#include <PLCore/ModuleMain.h>
#include <PLQt/Application.h>
#include "MySceneContext.h"
#include "MyRenderWindow.h"


//[-------------------------------------------------------]
//[ Module definition                                     ]
//[-------------------------------------------------------]
pl_module("82QtInputHandling")
	pl_module_vendor("Copyright (C) 2002-2011 by The PixelLight Team")
	pl_module_license("GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version")
	pl_module_description("PixelLight Qt 82 - Input handling")
pl_module_end


//[-------------------------------------------------------]
//[ Program entry point                                   ]
//[-------------------------------------------------------]
int main(int argc, char **argv)
{
	// Create an "PLQt::Application"-instance
	PLQt::Application cApplication(argc, argv);

	// Create the scene context
	MySceneContext cContext;

	// Enable updating the renderer context via the application instance
	cApplication.EnableRendererContextUpdates(true);
	cApplication.SetContextForUpdate(&cContext);

	// Create two "PLQt::QPLRenderWindow"-instances
	MyRenderWindow cWindow1(cContext, "FreeCamera1");
	cWindow1.resize(640, 480);											// Resize the first window
	cWindow1.show();													// Make first window visible
	MyRenderWindow cWindow2(cContext, "FreeCamera2");
	cWindow2.resize(640, 480);											// Resize the second window
	cWindow2.move(cWindow1.pos() + QPoint(cWindow1.size().width(), 0));	// Place the second window
	cWindow2.show();													// Make second window visible

	// Start the event loop of Qt
	return cApplication.exec();
}
