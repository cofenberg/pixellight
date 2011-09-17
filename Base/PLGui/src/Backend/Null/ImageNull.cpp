/*********************************************************\
 *  File: ImageNull.cpp                                  *
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
#include "PLGui/Backend/Null/ImageNull.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLGraphics;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ImageNull::ImageNull(Image &cImage) : ImageImpl(cImage)
{
}

/**
*  @brief
*    Destructor
*/
ImageNull::~ImageNull()
{
}


//[-------------------------------------------------------]
//[ Public virtual ImageImpl functions                    ]
//[-------------------------------------------------------]
bool ImageNull::Load(const String &sFilename)
{
	// Error - not implemented
	return false;
}

bool ImageNull::LoadWithColorKey(const String &sFilename, const Color3 &cColor)
{
	// Error - not implemented
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
