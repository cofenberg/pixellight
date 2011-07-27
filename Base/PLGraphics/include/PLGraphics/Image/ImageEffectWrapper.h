/*********************************************************\
 *  File: ImageEffectWrapper.h                           *
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


#ifndef __PLGRAPHICS_IMAGEEFFECT_WRAPPER_H__
#define __PLGRAPHICS_IMAGEEFFECT_WRAPPER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
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
*    Image effect wrapper
*/
class ImageEffectWrapper: public ImageEffect {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLGRAPHICS_RTTI_EXPORT, ImageEffectWrapper, "PLGraphics", PLGraphics::ImageEffect, "Image effect wrapper")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sEffect
		*    Image effect class name
		*  @param[in] sParameters
		*    Image effect parameters
		*/
		PLGRAPHICS_API ImageEffectWrapper(const PLCore::String &sEffect, const PLCore::String &sParameters);

		/**
		*  @brief
		*    Destructor
		*/
		PLGRAPHICS_API virtual ~ImageEffectWrapper();

		/**
		*  @brief
		*    Get wrapped image effect
		*
		*  @return
		*    Pointer to wrapped image effect, can be a null pointer
		*/
		PLGRAPHICS_API ImageEffect *GetImageEffect() const;


	//[-------------------------------------------------------]
	//[ Public virtual ImageEffect functions                  ]
	//[-------------------------------------------------------]
	public:
		virtual bool Apply(Image &cImage) const override;
		virtual bool Apply(ImagePart &cPart) const override;
		virtual bool Apply(ImageBuffer &cBuffer) const override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		ImageEffect	*m_pImageEffect;	/**< The wrapped image effect, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics


#endif // __PLGRAPHICS_IMAGEEFFECT_WRAPPER_H__
