/*********************************************************\
 *  File: ImageNull.h                                    *
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


#ifndef __PLGUI_IMAGENULL_H__
#define __PLGUI_IMAGENULL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Backend/ImageImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Null image implementation
*/
class ImageNull : public ImageImpl {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cImage
		*    Reference to platform independent image
		*/
		PLGUI_API ImageNull(Image &cImage);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~ImageNull();


	//[-------------------------------------------------------]
	//[ Public virtual ImageImpl functions                    ]
	//[-------------------------------------------------------]
	public:
		virtual bool Load(const PLCore::String &sFilename) override;
		virtual bool LoadWithColorKey(const PLCore::String &sFilename, const PLGraphics::Color3 &cColor) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_IMAGENULL_H__
