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
#include "PLCore/Tools/Timing.h"
#include "PLCore/System/System.h"
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
*    Get frontend
*/
Frontend *FrontendApplication::GetFrontend() const
{
	// Return pointer to frontend
	return m_pFrontend;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FrontendApplication::FrontendApplication() : CoreApplication(),
	m_pFrontend(nullptr)	// Set by FrontendPixelLight
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
	// Check if we're allowed to perform an update right now
	uint64 nTimeToWait = 0;
	if (!Timing::GetInstance()->Update(&nTimeToWait)) {
		// [TODO] This in here might also be the job of the frontend
		// Let the system some time to process other system tasks etc.
		// If this isn't done the CPU usage is always up to 100%!!
		// Please note that there's no guaranty that the resulting FPS always reaches
		// exactly the maximum FPS limit.
		// System::GetInstance()->Sleep(nTimeToWait);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
