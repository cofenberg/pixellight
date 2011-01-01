/*********************************************************\
 *  File: IEScale.h                                      *
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


#ifndef __PLGRAPHICS_IMAGEEFFECT_SCALE_H__
#define __PLGRAPHICS_IMAGEEFFECT_SCALE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3i.h>
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
*    Image effect: Apply scale
*
*  @note
*    - The color format "ColorPalette" is not supported
*/
class IEScale : public ImageEffect {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLGRAPHICS_RTTI_EXPORT, IEScale, "PLGraphics", PLGraphics::ImageEffect, "Image effect: Apply scale")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] vNewSize
		*    New size
		*  @param[in] bUseMipmaps
		*    If there are mipmaps and one of them matches the new dimension... is it allowed to
		*    just make this mipmap to the new base image and destroy the now unused other mipmaps?
		*    (extrem fast 'scale', but no set filters are applied and may cause problems on 'none standard'
		*    images)
		*/
		PLGRAPHICS_API IEScale(const PLMath::Vector3i &vNewSize, bool bUseMipmaps);

		/**
		*  @brief
		*    Destructor
		*/
		PLGRAPHICS_API virtual ~IEScale();

		/**
		*  @brief
		*    Get new size
		*
		*  @return
		*    New size
		*/
		PLGRAPHICS_API PLMath::Vector3i GetNewSize() const;

		/**
		*  @brief
		*    Is it allowed to use existing mipmaps to scale down?
		*
		*  @return
		*    'true' if it's allowed to use existing mipmaps to scale down, else 'false'
		*/
		PLGRAPHICS_API bool GetUseMipmaps() const;


	//[-------------------------------------------------------]
	//[ Public virtual ImageEffect functions                  ]
	//[-------------------------------------------------------]
	public:
		virtual bool Apply(Image &cImage) const;
		virtual bool Apply(ImageBuffer &cBuffer) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMath::Vector3i m_vNewSize;	/**< New size */
		bool			 m_bUseMipmaps;	/**< Is it allowed to use existing mipmaps to scale down? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics


#endif // __PLGRAPHICS_IMAGEEFFECT_SCALE_H__
