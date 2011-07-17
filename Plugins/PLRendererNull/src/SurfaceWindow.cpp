/*********************************************************\
 *  File: SurfaceWindow.cpp                              *
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
#ifdef WIN32
	#include <PLGeneral/PLGeneralWindowsIncludes.h>
#endif
#include "PLRendererNull/SurfaceWindow.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLRendererNull {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
SurfaceWindow::~SurfaceWindow()
{
	DeInit();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SurfaceWindow::SurfaceWindow(PLRenderer::SurfaceWindowHandler &cHandler, handle nWindow, bool bFullscreen) :
	PLRenderer::SurfaceWindow(cHandler, nWindow, bFullscreen)
{
	// Init
	Init();
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::SurfaceWindow functions    ]
//[-------------------------------------------------------]
bool SurfaceWindow::GetGamma(float &fRed, float &fGreen, float &fBlue) const
{
	// Error!
	return false;
}

bool SurfaceWindow::SetGamma(float fRed, float fGreen, float fBlue)
{
	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Surface functions          ]
//[-------------------------------------------------------]
Vector2i SurfaceWindow::GetSize() const
{
	if (GetWindow()) {
		#ifdef WIN32
			RECT sRect;
			GetClientRect(reinterpret_cast<HWND>(GetWindow()), &sRect);
			return Vector2i(sRect.right, sRect.bottom);
		#endif
		// [TODO] Linux
	} else {
		return Vector2i::Zero;
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Surface functions         ]
//[-------------------------------------------------------]
bool SurfaceWindow::Init()
{
	// Done
	return true;
}

void SurfaceWindow::DeInit()
{
}

bool SurfaceWindow::MakeCurrent(uint8 nFace)
{
	// Done
	return true;
}

bool SurfaceWindow::UnmakeCurrent()
{
	// Done
	return true;
}

bool SurfaceWindow::Present()
{
	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererNull
