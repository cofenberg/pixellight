/*********************************************************\
 *  File: Application.h                                  *
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
#include "PluginManager.h"
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEditor {


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
int NullNumOfProgramArguments = 0;


//[-------------------------------------------------------]
//[ Public methods                                        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
Application::Application(int argc, char **argv) : QApplication(argc, argv),
	m_pPluginManager(new PluginManager())
{
	// Load in all plugins
	m_pPluginManager->loadPlugins();
}

/**
*  @brief
*    Destructor
*/
Application::~Application()
{
	// Destroy the plugin manager instance
	delete m_pPluginManager;
}

/**
*  @brief
*    Returns the instance of the plugin manager
*/
PluginManager &Application::getPluginManager()
{
	return *m_pPluginManager;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
Application::Application() : QApplication(NullNumOfProgramArguments, nullptr),
	m_pPluginManager(new PluginManager())
{
}

/**
*  @brief
*    Copy constructor
*/
Application::Application(const Application &cSource) : QApplication(NullNumOfProgramArguments, nullptr),
	m_pPluginManager(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Application &Application::operator =(const Application &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEditor
