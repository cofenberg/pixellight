/*********************************************************\
 *  File: CursorNull.cpp                                 *
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
#include "PLGui/Backend/Null/CursorNull.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
CursorNull::CursorNull(Cursor &cCursor) : CursorImpl(cCursor)
{
}

/**
*  @brief
*    Destructor
*/
CursorNull::~CursorNull()
{
}


//[-------------------------------------------------------]
//[ Public virtual CursorImpl functions                   ]
//[-------------------------------------------------------]
void CursorNull::Load(EMouseCursor nCursor)
{
	// Not implemented
}

void CursorNull::Load(const String &sFilename, const Vector2i &vHotspot)
{
	// Not implemented
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
