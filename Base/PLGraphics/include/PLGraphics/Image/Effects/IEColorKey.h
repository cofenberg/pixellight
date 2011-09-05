/*********************************************************\
 *  File: IEColorKey.h                                   *
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


#ifndef __PLGRAPHICS_IMAGEEFFECT_COLORKEY_H__
#define __PLGRAPHICS_IMAGEEFFECT_COLORKEY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGraphics/Color/Color3.h"
#include "PLGraphics/Image/ImageEffect.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Image effect: Apply color key
*
*  @note
*    - The color format "ColorPalette" is not supported
*    - The value in the alpha channel will be set to 0 if the RGB value at this pixel
*      is within the tolerance of the color key RGB value, else it is set to max value
*    - If the image has no alpha channel an alpha channel is add automatically
*/
class IEColorKey : public ImageEffect {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLGRAPHICS_RTTI_EXPORT, IEColorKey, "PLGraphics", PLGraphics::ImageEffect, "Image effect: Apply color key")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cColor
		*    Color
		*  @param[in] fTolerance
		*    fTolerance (0 .. 1)
		*/
		PLGRAPHICS_API IEColorKey(const Color3 &cColor, float fTolerance);

		/**
		*  @brief
		*    Destructor
		*/
		PLGRAPHICS_API virtual ~IEColorKey();

		/**
		*  @brief
		*    Get color
		*
		*  @return
		*    Color
		*/
		PLGRAPHICS_API Color3 GetColor() const;

		/**
		*  @brief
		*    Get tolerance
		*
		*  @return
		*    Tolerance (0 .. 1)
		*/
		PLGRAPHICS_API float GetTolerance() const;


	//[-------------------------------------------------------]
	//[ Public virtual ImageEffect functions                  ]
	//[-------------------------------------------------------]
	public:
		PLGRAPHICS_API virtual bool Apply(ImageBuffer &cBuffer) const override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Color3 m_cColor;		/**< Color used for transparent pixels */
		float  m_fTolerance;	/**< Tolerance */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics


#endif // __PLGRAPHICS_IMAGEEFFECT_COLORKEY_H__
