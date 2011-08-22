/*********************************************************\
 *  File: ImageEffects.h                                 *
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


#ifndef __PLGRAPHICS_IMAGEEFFECTS_H__
#define __PLGRAPHICS_IMAGEEFFECTS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGraphics/Image/ImageEffectWrapper.h"
#include "PLGraphics/Image/Effects/IEConvert.h"
#include "PLGraphics/Image/Effects/IEFilter.h"
#include "PLGraphics/Image/Effects/IEScale.h"
#include "PLGraphics/Image/Effects/IEMonochrome.h"
#include "PLGraphics/Image/Effects/IEColorKey.h"
#include "PLGraphics/Image/Effects/IEFlipXAxis.h"
#include "PLGraphics/Image/Effects/IEFlipYAxis.h"
#include "PLGraphics/Image/Effects/IERemovePalette.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Color3;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static image effects class
*/
class ImageEffects {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Create image effect dynamically
		*
		*  @param[in] sEffect
		*    Image effect class name
		*  @param[in] sParameters
		*    Image effect parameters
		*
		*  @return
		*    Image effect
		*/
		PLGRAPHICS_API static ImageEffectWrapper Effect(const PLCore::String &sEffect, const PLCore::String &sParameters);

		/**
		*  @brief
		*    Create image filter
		*
		*  @return
		*    Image filter
		*/
		PLGRAPHICS_API static IEFilter Filter();

		/**
		*  @brief
		*    Create scale image effect
		*
		*  @param[in] vNewSize
		*    The new size
		*  @param[in] bUseMipmaps
		*    If there are mipmaps and one of them matches the new dimension... is it allowed to
		*    just make this mipmap to the new base image and destroy the now unused other mipmaps?
		*    (extremely fast 'scale', but no set filters are applied and may cause problems on 'none standard'
		*    images)
		*
		*  @return
		*    Scale image effect
		*/
		PLGRAPHICS_API static IEScale Scale(const PLMath::Vector3i &vNewSize, bool bUseMipmaps);

		/**
		*  @brief
		*    Create image conversion effect
		*
		*  @param[in] nDataFormat
		*    Desired data format
		*  @param[in] nColorFormat
		*    Desired color format
		*
		*  @return
		*    Image conversion effect
		*/
		PLGRAPHICS_API static IEConvert Convert(EDataFormat nDataFormat, EColorFormat nColorFormat);

		/**
		*  @brief
		*    Create monochrome image effect
		*
		*  @return
		*    Monochrome image effect
		*/
		PLGRAPHICS_API static IEMonochrome Monochrome();

		/**
		*  @brief
		*    Create color key image effect
		*
		*  @param[in] cColor
		*    Color
		*  @param[in] fTolerance
		*    Tolerance (0 .. 1)
		*
		*  @return
		*    Color key image effect
		*/
		PLGRAPHICS_API static IEColorKey ColorKey(const Color3 &cColor, float fTolerance);

		/**
		*  @brief
		*    Create flip the image around the x axis image effect
		*
		*  @return
		*    Flip the image around the x axis image effect
		*/
		PLGRAPHICS_API static IEFlipXAxis FlipXAxis();

		/**
		*  @brief
		*    Create flip the image around the y axis image effect
		*
		*  @return
		*    Flip the image around the y axis image effect
		*/
		PLGRAPHICS_API static IEFlipYAxis FlipYAxis();

		/**
		*  @brief
		*    Create remove palette image effect
		*
		*  @return
		*    Remove palette image effect
		*/
		PLGRAPHICS_API static IERemovePalette RemovePalette();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics


#endif // __PLGRAPHICS_IMAGEEFFECTS_H__
