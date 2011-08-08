/*********************************************************\
 *  File: Main.cpp                                       *
 *      PixelLight sample showing how to use "PLEngine::ScriptApplication" in order to load in and execute a scripted stand-alone application
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
#include <PLCore/Frontend/FrontendMain.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Module definition                                     ]
//[-------------------------------------------------------]
pl_module("45ScriptApplication")
	pl_module_vendor("Copyright (C) 2002-2011 by The PixelLight Team")
	pl_module_license("GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version")
	pl_module_description("PixelLight sample showing how to use \"PLEngine::ScriptApplication\" in order to load in and execute a scripted stand-alone application")
pl_module_end


//[-------------------------------------------------------]
//[ Program entry point                                   ]
//[-------------------------------------------------------]
int PLMain(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// ... hm, what would be an appropriate comment for this line of code? Maybe "Run script"...? *g*
	return Frontend::Run(// Absolute application executable filename
						 sExecutableFilename,
						 // List of arguments to the program
						 lstArguments,
						 // Frontend - Name of the frontend RTTI class to use
						 "PLCore::FrontendPixelLight",
						 // Frontend - Name of the frontend RTTI class constructor to use
						 "",
						 // Frontend - Parameters for the frontend RTTI class constructor
						 "",
						 // Frontend - Parameters for the instanced frontend RTTI class
						 "ApplicationClass=\"PLEngine::ScriptApplication\" ApplicationConstructor=\"ParameterConstructor2\" ApplicationConstructorParameters=\"ScriptFilename='Data/Scripts/45ScriptApplication.lua'\"",
						 // Frontend implementation - Name of the frontend implementation RTTI class to use
						 "PLFrontendOS::Frontend",
						 // Frontend implementation - Name of the frontend implementation RTTI class constructor to use
						 "",
						 // Frontend implementation - Parameters for the frontend implementation RTTI class constructor
						 "",
						 // Frontend implementation - Parameters for the instanced frontend implementation RTTI class
						 "");
}
