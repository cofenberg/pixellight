/*********************************************************\
 *  File: ImageToolsWindows.cpp                          *
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
#include "PLGraphics/Color/Color3.h"
#include "PLGraphics/Image/Image.h"
#include "PLGraphics/Image/ImageBuffer.h"
#include "PLGraphics/Image/ImagePalette.h"
#include "PLGraphics/Image/ImageToolsWindows.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns a Windows-friendly bitmap handle
*/
HBITMAP ImageToolsWindows::ConvertToHBitmap(Image &cImage, HDC hDC)
{
	return PLConvertToHBitmap(cImage, hDC);
}

/**
*  @brief
*    Sets the current image to be a copy of a Windows bitmap
*/
bool ImageToolsWindows::SetHBitmap(Image &cImage, HBITMAP hBitmap)
{
	// [TODO] implement
	return false;
}

/**
*  @brief
*    Copies the Windows clipboard to the current image
*/
bool ImageToolsWindows::GetWinClipboard(Image &cImage)
{
	// [TODO] implement
	return false;
}

/**
*  @brief
*    Copies an image to the Windows clipboard
*/
bool ImageToolsWindows::SetWinClipboard(Image &cImage)
{
	// [TODO] implement
	return false;
}

/**
*  @brief
*    Loads a Windows resource as the current image
*/
bool ImageToolsWindows::LoadResource(Image &cImage, HINSTANCE hInst, int nID, const String &sResourceType, const String &sFileType)
{
	// [TODO] implement
	return false;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Convert a 32 bit image with alpha map to a window HBITMAP
*/
HBITMAP ImageToolsWindows::PLConvertToHBitmap(Image &cImage, HDC hDC)
{
	// Get image buffer
	const ImageBuffer &cImageBuffer = *cImage.GetBuffer();

	// Get image size and data
	const int   nWidth  = cImageBuffer.GetSize().x;
	const int   nHeight = cImageBuffer.GetSize().y;
	const BYTE *pBitmap = cImageBuffer.GetData();

	// Allocate temporary buffer and convert bitmap data
	DWORD *pBuffer = new DWORD[nWidth*nHeight];
	const BYTE *pPixel = pBitmap;
	int nComponents;
	switch (cImageBuffer.GetColorFormat()) {
		case ColorRGB:
			nComponents = 3;
			break;

		case ColorRGBA:
			nComponents = 4;
			break;

		case ColorBGR:
			nComponents = 3;
			break;

		case ColorBGRA:
			nComponents = 4;
			break;

		case ColorGrayscale:
			nComponents = 1;
			break;

		case ColorPalette:
			nComponents = 1;
			break;

		default:
			nComponents = 0;
			break;
	}

	// Fill the buffer
	for (int i=0; i<nWidth*nHeight; i++) {
		// Get color
		int r = 0;
		int g = 0;
		int b = 0;
		int a = 0;
		switch (cImageBuffer.GetColorFormat()) {
			case ColorRGB:
				r = pPixel[0];
				g = pPixel[1];
				b = pPixel[2];
				a = 255;
				break;

			case ColorRGBA:
				r = pPixel[0];
				g = pPixel[1];
				b = pPixel[2];
				a = pPixel[3];
				break;

			case ColorBGR:
				r = pPixel[2];
				g = pPixel[1];
				b = pPixel[0];
				a = 255;
				break;

			case ColorBGRA:
				r = pPixel[2];
				g = pPixel[1];
				b = pPixel[0];
				a = pPixel[3];
				break;

			case ColorGrayscale:
				r = pPixel[0];
				g = pPixel[0];
				b = pPixel[0];
				a = 255;
				break;

			case ColorPalette:
			{
				const Color3 cColor = cImageBuffer.GetPalette()->GetColor(pPixel[0]);
				r = cColor.GetRInt();
				g = cColor.GetGInt();
				b = cColor.GetBInt();
				a = 255;
				break;
			}
		}

		// Pre-multiply alpha values
		if (a < 255) {
			r = (r*a)/255;
			g = (g*a)/255;
			b = (b*a)/255;
		}

		// Set color
		pBuffer[i] = ((a << 24) | (r << 16) | (g << 8) | (b));
		pPixel += nComponents;
	}

	// Create gdi bitmap
	BITMAPINFO sBitmap;
	ZeroMemory(&sBitmap, sizeof(BITMAPINFO));
	sBitmap.bmiHeader.biSize		= sizeof(BITMAPINFOHEADER);
	sBitmap.bmiHeader.biBitCount	= 32;
	sBitmap.bmiHeader.biCompression	= BI_RGB;
	sBitmap.bmiHeader.biWidth		=  nWidth;
	sBitmap.bmiHeader.biHeight		= -nHeight;
	sBitmap.bmiHeader.biSizeImage	= nWidth * nHeight * 4;
	sBitmap.bmiHeader.biPlanes		= 1;
	HBITMAP hBitmap = CreateDIBitmap(hDC, &sBitmap.bmiHeader, CBM_INIT, pBuffer, &sBitmap, DIB_RGB_COLORS);

	// Clean up buffer
	delete [] pBuffer;

	// Return bitmap
	return hBitmap;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
