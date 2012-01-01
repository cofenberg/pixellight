/*********************************************************\
 *  File: TrayIconNull.cpp                               *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLGui/Backend/Null/TrayIconNull.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLGui {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TrayIconNull::TrayIconNull(TrayIcon &cTrayIcon) : TrayIconImpl(cTrayIcon)
{
}

/**
*  @brief
*    Destructor
*/
TrayIconNull::~TrayIconNull()
{
}


//[-------------------------------------------------------]
//[ Private virtual TrayIconImpl functions                ]
//[-------------------------------------------------------]
void TrayIconNull::CreateTrayIcon()
{
	// Not implemented
}

void TrayIconNull::DestroyTrayIcon()
{
	// Not implemented
}

void TrayIconNull::SetVisible(bool bVisible)
{
	// Not implemented
}

void TrayIconNull::Update()
{
	// Not implemented
}

void TrayIconNull::ShowNotification(const String &sTitle, const String &sText)
{
	// Not implemented
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
