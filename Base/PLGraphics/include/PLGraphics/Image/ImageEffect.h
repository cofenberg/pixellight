/*********************************************************\
 *  File: ImageEffect.h                                  *
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


#ifndef __PLGRAPHICS_IMAGEEFFECT_H__
#define __PLGRAPHICS_IMAGEEFFECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include "PLGraphics/PLGraphics.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Image;
class ImagePart;
class ImageFrame;
class ImageLayer;
class ImageBuffer;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract image effect base class
*/
class ImageEffect : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLGRAPHICS_RTTI_EXPORT, ImageEffect, "PLGraphics", PLCore::Object, "Abstract image effect base class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLGRAPHICS_API ImageEffect();

		/**
		*  @brief
		*    Destructor
		*/
		PLGRAPHICS_API virtual ~ImageEffect();

		/**
		*  @brief
		*    Get effect description
		*
		*  @return
		*    Effect description
		*/
		PLGRAPHICS_API PLCore::String GetDescription() const;


	//[-------------------------------------------------------]
	//[ Public virtual ImageEffect functions                  ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Apply effect to image
		*
		*  @param[in,out] cImage
		*    Image
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Apply(Image &cImage) const;

		/**
		*  @brief
		*    Apply effect to image part
		*
		*  @param[in,out] cPart
		*    Image part
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Apply(ImagePart &cPart) const;

		/**
		*  @brief
		*    Apply effect to image buffer
		*
		*  @param[in,out] cBuffer
		*    Image buffer
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Apply(ImageBuffer &cBuffer) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics


#endif // __PLGRAPHICS_IMAGEEFFECT_H__
