/*********************************************************\
 *  File: Main.cpp                                       *
 *      PixelLight sample showing how to use "PLEngine::ScriptApplication" in order to load in and execute a scripted stand-alone application
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
#include <PLCore/Frontend/FrontendMain.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Module definition                                     ]
//[-------------------------------------------------------]
pl_module("45ScriptApplication")
	pl_module_vendor("Copyright (C) 2002-2013 by The PixelLight Team")
	pl_module_license("\"MIT License\" which is also known as \"X11 License\" or \"MIT X License\" (mit-license.org)")
	pl_module_description("PixelLight sample showing how to use \"PLEngine::ScriptApplication\" in order to load in and execute a scripted stand-alone application")
pl_module_end


//[-------------------------------------------------------]
//[ Program entry point                                   ]
//[-------------------------------------------------------]
int PLMain(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// Scan PL-runtime directory for compatible plugins and load them in as well as scan for compatible data and register it
	if (Runtime::ScanDirectoryPluginsAndData()) {
		// Setup the frontend context
		FrontendContext cFrontendContext;
		cFrontendContext.SetExecutableFilename(sExecutableFilename);
		cFrontendContext.SetArguments(lstArguments);
		cFrontendContext.SetName("45ScriptApplication");
		cFrontendContext.SetFrontendParameters("ApplicationClass=\"PLEngine::ScriptApplication\" ApplicationConstructor=\"ParameterConstructor2\" ApplicationConstructorParameters=\"ScriptFilename='Data/Scripts/45ScriptApplication.lua'\"");

		// ... hm, what would be an appropriate comment for this line of code? Maybe "Run script"...? *g*
		return Frontend::Run(cFrontendContext);
	} else {
		// Error!
		return -1;
	}
}
