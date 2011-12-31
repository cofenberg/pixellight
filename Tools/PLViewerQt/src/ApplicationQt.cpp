/*********************************************************\
 *  File: ApplicationQt.cpp                              *
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
#include "Gui.h"
#include "ApplicationQt.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ApplicationQt)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ApplicationQt::ApplicationQt(Frontend &cFrontend) : Application(cFrontend),
	m_pGui(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
ApplicationQt::~ApplicationQt()
{
	// GUI instance has to be destroyed in "ApplicationQt::OnDeInit()" which is guaranteed to be called
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::CoreApplication functions     ]
//[-------------------------------------------------------]
void ApplicationQt::OnInit()
{
	// Initialize the GUI (no "m_pGui" security checks required, the application lifecycle is guaranteed)
	m_pGui = new Gui(*this);

	// Call base implementation
	Application::OnInit();
}

void ApplicationQt::OnDeInit()
{
	// De-initialize the GUI (no "m_pGui" security checks required, the application lifecycle is guaranteed)
	delete m_pGui;
	m_pGui = nullptr;

	// Call base implementation
	Application::OnInit();
}
