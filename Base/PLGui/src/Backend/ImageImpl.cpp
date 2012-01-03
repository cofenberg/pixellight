/*********************************************************\
 *  File: ImageImpl.cpp                                  *
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
#include "PLGui/Backend/ImageImpl.h"


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
ImageImpl::ImageImpl(Image &cImage) :
	m_pImage(&cImage),
	m_nColorDepth(0)
{
}

/**
*  @brief
*    Destructor
*/
ImageImpl::~ImageImpl()
{
}

/**
*  @brief
*    Get image name
*/
String ImageImpl::GetFilename() const
{
	// Return filename
	return m_sFilename;
}

/**
*  @brief
*    Get image size
*/
Vector2i ImageImpl::GetSize() const
{
	// Return size
	return m_vSize;
}

/**
*  @brief
*    Get color depth
*/
uint32 ImageImpl::GetColorDepth() const
{
	// Return color depth
	return m_nColorDepth;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
