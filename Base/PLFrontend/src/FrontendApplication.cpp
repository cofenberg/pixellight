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
#include "PLFrontend/FrontendApplication.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontend {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(FrontendApplication)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FrontendApplication::FrontendApplication(const String &sFrontend) : ConsoleApplication(),
	m_pFrontend(nullptr)
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
//[ Protected virtual FrontendApplication functions       ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called to let the frontend application draw into it's window
*/
void FrontendApplication::OnDraw()
{
	// No default implementation
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontend
