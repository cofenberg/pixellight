/*********************************************************\
 *  File: ImageEffects.inl                               *
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Create image effect dynamically
*/
inline ImageEffectWrapper ImageEffects::Effect(const PLCore::String &sEffect, const PLCore::String &sParameters)
{
	return ImageEffectWrapper(sEffect, sParameters);
}

/**
*  @brief
*    Create image filter
*/
inline IEFilter ImageEffects::Filter()
{
	return IEFilter();
}

/**
*  @brief
*    Create scale image effect
*/
inline IEScale ImageEffects::Scale(const PLMath::Vector3i &vNewSize, bool bUseMipmaps)
{
	return IEScale(vNewSize, bUseMipmaps);
}

/**
*  @brief
*    Create image conversion effect
*/
inline IEConvert ImageEffects::Convert(EDataFormat nDataFormat, EColorFormat nColorFormat)
{
	return IEConvert(nDataFormat, nColorFormat);
}

/**
*  @brief
*    Create monochrome image effect
*/
inline IEMonochrome ImageEffects::Monochrome()
{
	return IEMonochrome();
}

/**
*  @brief
*    Create color key image effect
*/
inline IEColorKey ImageEffects::ColorKey(const Color3 &cColor, float fTolerance)
{
	return IEColorKey(cColor, fTolerance);
}

/**
*  @brief
*    Create flip the image around the x axis image effect
*/
inline IEFlipXAxis ImageEffects::FlipXAxis()
{
	return IEFlipXAxis();
}

/**
*  @brief
*    Create flip the image around the y axis image effect
*/
inline IEFlipYAxis ImageEffects::FlipYAxis()
{
	return IEFlipYAxis();
}

/**
*  @brief
*    Create remove palette image effect
*/
inline IERemovePalette ImageEffects::RemovePalette()
{
	return IERemovePalette();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
