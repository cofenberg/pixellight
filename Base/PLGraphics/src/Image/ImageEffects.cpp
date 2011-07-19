/*********************************************************\
 *  File: ImageEffects.cpp                               *
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
#include "PLGraphics/Image/ImageEffects.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Create image effect dynamically
*/
ImageEffectWrapper ImageEffects::Effect(const String &sEffect, const String &sParameters)
{
	return ImageEffectWrapper(sEffect, sParameters);
}

/**
*  @brief
*    Create image filter
*/
IEFilter ImageEffects::Filter()
{
	return IEFilter();
}

/**
*  @brief
*    Create scale image effect
*/
IEScale ImageEffects::Scale(const Vector3i &vNewSize, bool bUseMipmaps)
{
	return IEScale(vNewSize, bUseMipmaps);
}

/**
*  @brief
*    Create image conversion effect
*/
IEConvert ImageEffects::Convert(EDataFormat nDataFormat, EColorFormat nColorFormat)
{
	return IEConvert(nDataFormat, nColorFormat);
}

/**
*  @brief
*    Create monochrome image effect
*/
IEMonochrome ImageEffects::Monochrome()
{
	return IEMonochrome();
}

/**
*  @brief
*    Create color key image effect
*/
IEColorKey ImageEffects::ColorKey(const Color3 &cColor, float fTolerance)
{
	return IEColorKey(cColor, fTolerance);
}

/**
*  @brief
*    Create flip the image around the x axis image effect
*/
IEFlipXAxis ImageEffects::FlipXAxis()
{
	return IEFlipXAxis();
}

/**
*  @brief
*    Create flip the image around the y axis image effect
*/
IEFlipYAxis ImageEffects::FlipYAxis()
{
	return IEFlipYAxis();
}

/**
*  @brief
*    Create remove palette image effect
*/
IERemovePalette ImageEffects::RemovePalette()
{
	return IERemovePalette();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
