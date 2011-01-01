/*********************************************************\
 *  File: ImageToolsWindows.h                            *
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


#ifndef __PLGRAPHICS_IMAGETOOLS_WINDOWS_H__
#define __PLGRAPHICS_IMAGETOOLS_WINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneral.h>
#include <PLGeneral/PLGeneralWindowsIncludes.h>
#include "PLGraphics/PLGraphics.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Image;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static class with some useful Windows image tools
*/
class ImageToolsWindows {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns a Windows-friendly bitmap handle
		*
		*  @param[in] cImage
		*    Image to use
		*  @param[in] hDC
		*    The device context that you want to receive the HBITMAP
		*
		*  @return
		*    Windows-friendly bitmap handle
		*
		*  @note
		*    - Creates a Windows bitmap handle (HBITMAP) copy of the current image, for
		*      direct use in Windows
		*    - Use the windows function DeleteObject() to free the bitmap
		*/
		PLGRAPHICS_API static HBITMAP ConvertToHBitmap(Image &cImage, HDC hDC);

		/**
		*  @brief
		*    Sets the current image to be a copy of a Windows bitmap
		*
		*  @param[in] cImage
		*    Image to use
		*  @param[in] hBitmap
		*    Bitmap to copy to the given image
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*    Copies hBitmap to the given image in a 'normal' format we can
		*    understand. The image can then be used just as if you had loaded an image
		*    via Image::Load(). This function is the opposite of ConvertToHBitmap().
		*/
		PLGRAPHICS_API static bool SetHBitmap(Image &cImage, HBITMAP hBitmap);

		/**
		*  @brief
		*    Copies the Windows clipboard to the current image
		*
		*  @param[in] cImage
		*    Image to use
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*    Copies the contents of the Windows clipboard into the given image,
		*    resizing as necessary.
		*/
		PLGRAPHICS_API static bool GetWinClipboard(Image &cImage);

		/**
		*  @brief
		*    Copies an image to the Windows clipboard
		*
		*  @param[in] cImage
		*    Image to use
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @return
		*    Copies the given image to the Windows clipboard
		*/
		PLGRAPHICS_API static bool SetWinClipboard(Image &cImage);

		/**
		*  @brief
		*    Loads a Windows resource as the current image
		*
		*  @param[in] cImage
		*    Image to use
		*  @param[in] hInst
		*    The application's HINSTANCE
		*  @param[in] nID
		*    The resource identifier of the resource to be loaded
		*  @param[in] sResourceType
		*    The type of user-defined resource (name used when creating)
		*  @param[in] sFileType
		*    The type of image to be loaded, e.g. "bmp". Pass empty string
		*    to let the type be determined automatically
		*
		*  @return
		*   'true' if all went fine, else 'false'
		*
		*  @remarks
		*    Windows-specific function that loads a resource as the given image.
		*    This feature allows you to have images directly in your .exe and not worry
		*    whether a particular file is present on the user's harddrive.
		*/
		PLGRAPHICS_API static bool LoadResource(Image &cImage, HINSTANCE hInst, int nID, const PLGeneral::String &sResourceType, const PLGeneral::String &sFileType);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Convert a 32 bit image with alpha map to a window HBITMAP
		*
		*  @param[in] cImage
		*    Image to use
		*  @param[in] hDC
		*    The device context that you want to receive the HBITMAP
		*
		*  @return
		*    Windows-friendly bitmap handle
		*
		*  @note
		*    - This function is used to convert 32 bit images with RGBA data, because
		*      the devil function strips the A information from the data
		*/
		static HBITMAP PLConvertToHBitmap(Image &cImage, HDC hDC);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics


#endif // __PLGRAPHICS_IMAGETOOLS_WINDOWS_H__
