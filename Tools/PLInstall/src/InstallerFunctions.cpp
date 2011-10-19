/*********************************************************\
 *  File: InstallerFunctions.cpp                                     *
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
#if defined(WIN32)
	#include "InstallerFunctionsWindows.h"
//[TODO] implement linux functions
//#elif defined(LINUX)
//	#include "InstallerFunctionsLinux.h"
//[TODO] implement apple functions
//#elif defined(APPLE)
//	#include "InstallerFunctionsApple.h"
#endif
#include "InstallerFunctions.h"


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
InstallerFunctions::InstallerFunctions() :
	m_pInstallerFunctionsImpl(nullptr)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pInstallerFunctionsImpl = new InstallerFunctionsWindows();
	//[TODO] implement linux functions
	//#elif defined(LINUX)
	//	// Create Linux implementation
	//	m_pInstallerFunctionsImpl = new InstallerFunctionsLinux();
	//[TODO] implement apple functions
	//#elif defined(APPLE)
	//	// Create Linux implementation
	//	m_pInstallerFunctionsImpl = new InstallerFunctionsApple();
	#else
		// Unknown system
		#error "Unsupported platform"
	#endif

}

/**
*  @brief
*    Destructor
*/
InstallerFunctions::~InstallerFunctions()
{
	// Destroy system specific implementation
	if (m_pInstallerFunctionsImpl)
		delete m_pInstallerFunctionsImpl;
}

void InstallerFunctions::connectProgressEventHandler(PLCore::EventHandler<int> *pProgressEventHandler)
{
	m_pInstallerFunctionsImpl->getProgressUpdateEvent()->Connect(*pProgressEventHandler);
}

bool InstallerFunctions::installRuntime()
{
	return m_pInstallerFunctionsImpl->installRuntime();
}

int InstallerFunctions::getInstallRuntimeProgressSteps()
{
	return m_pInstallerFunctionsImpl->getInstallRuntimeProgressSteps();
}

bool InstallerFunctions::checkRuntimeInstallation()
{
	return m_pInstallerFunctionsImpl->checkRuntimeInstallation();
}

int InstallerFunctions::getCheckRuntimeProgressSteps()
{
	return m_pInstallerFunctionsImpl->getCheckRuntimeProgressSteps();
}

//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]



