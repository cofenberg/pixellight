/*********************************************************\
 *  File: Main.cpp                                       *
 *      Application entry point
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Main.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Plugin implementation                                 ]
//[-------------------------------------------------------]
DEFINE_MODULE("[!output PROJECT_NAME]")
	MODULE_VENDOR("Copyright (C) <fill me>")
	MODULE_LICENSE("<fill me>")
	MODULE_DESCRIPTION("<fill me>")
END_MODULE()


//[-------------------------------------------------------]
//[ Program entry point                                   ]
//[-------------------------------------------------------]
int PLMain(const String &sFilename, const Array<String> &lstArguments)
{
	Application cApplication;
	return cApplication.Run(sFilename, lstArguments);
}
