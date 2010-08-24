/*********************************************************\
 *  File: ImageWindows.h                                 *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLGUI_IMAGEWINDOWS_H__
#define __PLGUI_IMAGEWINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneralWindowsIncludes.h>
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
*    Windows image implementation
*/
class ImageWindows : public ImageImpl {


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
		PLGUI_API ImageWindows(Image &cImage);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~ImageWindows();

		/**
		*  @brief
		*    Get bitmap handle
		*
		*  @return
		*    Bitmap handle, can be NULL
		*/
		PLGUI_API HBITMAP GetBitmapHandle() const;

		/**
		*  @brief
		*    Get icon handle of the image
		*
		*  @return
		*    Icon handle, can be NULL
		*/
		PLGUI_API HICON GetIconHandle();

		/**
		*  @brief
		*    Unload image
		*/
		PLGUI_API void Unload();


	//[-------------------------------------------------------]
	//[ Public virtual ImageImpl functions                    ]
	//[-------------------------------------------------------]
	public:
		virtual bool Load(const PLGeneral::String &sFilename);
		virtual bool LoadWithColorKey(const PLGeneral::String &sFilename, const PLGraphics::Color3 &cColor);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		HBITMAP m_hBitmap;		/**< Bitmap handle, can be NULL */
		HICON	m_hIcon;		/**< Icon handle of bitmap */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_IMAGEWINDOWS_H__
