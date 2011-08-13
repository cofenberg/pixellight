/*********************************************************\
 *  File: FrontendApplication.cpp                        *
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
#include "PLCore/Frontend/FrontendApplication.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(FrontendApplication)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the frontend this application is running in
*/
Frontend &FrontendApplication::GetFrontend() const
{
	// Return reference to the frontend
	return *m_pFrontend;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FrontendApplication::FrontendApplication(Frontend &cFrontend) : CoreApplication(),
	m_pFrontend(&cFrontend)
{
	// Set application title
	SetTitle("PixelLight frontend application");

	// Set running state
	m_bRunning = true;
}

/**
*  @brief
*    Destructor
*/
FrontendApplication::~FrontendApplication()
{
}


//[-------------------------------------------------------]
//[ Protected virtual AbstractFrontend functions          ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the window size has been changed
*/
void FrontendApplication::OnSize()
{
	// No default implementation
}

/**
*  @brief
*    Called when the display mode was changed
*/
void FrontendApplication::OnDisplayMode()
{
	// No default implementation
}

/**
*  @brief
*    Called when the fullscreen mode was changed
*/
void FrontendApplication::OnFullscreenMode()
{
	// No default implementation
}

/**
*  @brief
*    Called to let the frontend draw into it's window
*/
void FrontendApplication::OnDraw()
{
	// No default implementation
}

/**
*  @brief
*    Called to let the frontend update it's states
*/
void FrontendApplication::OnUpdate()
{
	// No default implementation
}

/**
*  @brief
*    Called when string data has been dropped onto the frontend window
*/
void FrontendApplication::OnDrop(const Container<String> &lstFiles)
{
	// No default implementation
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
