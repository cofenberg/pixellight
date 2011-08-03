/*********************************************************\
 *  File: Frontend.cpp                                   *
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
#include "PLFrontendNull/Frontend.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendNull {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Frontend)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Frontend::Frontend() :
	m_cFrontend(*this)
{
	// Do the frontend lifecycle thing - let the world know that we have been created
	OnCreate();
}

/**
*  @brief
*    Destructor
*/
Frontend::~Frontend()
{
	// Do the frontend lifecycle thing - let the world know that we're going to die
	OnDestroy();
}


//[-------------------------------------------------------]
//[ Public virtual PLFrontend::FrontendImpl functions     ]
//[-------------------------------------------------------]
handle Frontend::GetNativeWindowHandle() const
{
	// There's no window handle!
	return NULL_HANDLE;
}


//[-------------------------------------------------------]
//[ Private virtual PLFrontend::FrontendImpl functions    ]
//[-------------------------------------------------------]
int Frontend::Run(const String &sApplicationClass, const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// Do the frontend lifecycle thing - initialize
	OnStart();
	OnResume();

	// The frontend main loop
	while (m_cFrontend.IsRunning()) {
		// [TODO] Update stuff
		OnDraw();
	}

	// Do the frontend lifecycle thing - de-initialize
	OnPause();
	OnStop();

	// Done
	return 0;
}

void Frontend::Redraw()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendNull
