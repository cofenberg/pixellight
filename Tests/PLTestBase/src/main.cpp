/*********************************************************\
 *  File: main.cpp                                       *
 *      Base tests
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
#include <stdio.h>
#include <PLGeneral/Main.h>
#include <PLCore/Core.h>
#include <PLCore/ModuleMain.h>
#include "PLTestBase/General/General.h"
#include "PLTestBase/Core/Core.h"
#include "PLTestBase/Math/Math.h"
#include "PLTestBase/Graphics/Graphics.h"
#include "PLTestBase/Database/Database.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;


//[-------------------------------------------------------]
//[ Module definition                                     ]
//[-------------------------------------------------------]
pl_module("PLTestBase")
	pl_module_vendor("Copyright (C) 2002-2011 by The PixelLight Team")
	pl_module_license("GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version")
	pl_module_description("PixelLight basic test")
pl_module_end


//[-------------------------------------------------------]
//[ Program entry point                                   ]
//[-------------------------------------------------------]
int PLMain(const String &sFilename, const Array<String> &lstArguments)
{
	{ // Add plugins
		// Scan for plugins within in the current plugins directory
		ClassManager::GetInstance()->ScanPlugins("Plugins/");

		// Get the PixelLight runtime directory
		String sPLDirectory = Core::GetRuntimeDirectory();
		if (sPLDirectory.GetLength() > 0) {
			// Add the plugins within the PixelLight runtime plugins directory
			ClassManager::GetInstance()->ScanPlugins(sPLDirectory + "/Plugins/");
		}
	}

	// Perform general tests
	GeneralTests();

	// Perform core tests
	CoreTests();

	// Perform math tests
	MathTests();

	// Perform graphics tests
	GraphicsTests();

	// Perform database tests
	DatabaseTests();

	// Wait for any key hit...
	printf("\nPress any key to quit...\n");
	getchar();

	// Done
	return 0;
}
