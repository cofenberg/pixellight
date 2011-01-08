/*********************************************************\
 *  File: ToolsWindows.cpp                               *
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
#include "PLGui/Backend/Windows/ToolsWindows.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Create AND and XOR masks from a HBITMAP
*/
void ToolsWindows::GetMaskBitmaps(HBITMAP hBitmap, COLORREF sColorTransparent, HBITMAP &hMaskAnd, HBITMAP &hMaskXor)
{
	// Create device contexts
	HDC hDC			= ::GetDC(nullptr);
	HDC hMainDC		= ::CreateCompatibleDC(hDC);
	HDC hAndMaskDC	= ::CreateCompatibleDC(hDC);
	HDC hXorMaskDC	= ::CreateCompatibleDC(hDC);

	// Get the dimensions of the source bitmap
	BITMAP sBitmap;
	::GetObject(hBitmap, sizeof(BITMAP), &sBitmap);

	// Create mask bitmaps
	hMaskAnd = ::CreateCompatibleBitmap(hDC, sBitmap.bmWidth, sBitmap.bmHeight);
	hMaskXor = ::CreateCompatibleBitmap(hDC, sBitmap.bmWidth, sBitmap.bmHeight);

	// Select the bitmaps to DC
	HBITMAP hOldMainBitmap    = (HBITMAP)::SelectObject(hMainDC,    hBitmap);
	HBITMAP hOldAndMaskBitmap = (HBITMAP)::SelectObject(hAndMaskDC, hMaskAnd);
	HBITMAP hOldXorMaskBitmap = (HBITMAP)::SelectObject(hXorMaskDC, hMaskXor);

	// Scan each pixel of the souce bitmap and create the masks
	COLORREF MainBitPixel;
	for (int x=0; x<sBitmap.bmWidth; x++) {
		for (int y=0; y<sBitmap.bmHeight; y++) {
			MainBitPixel = ::GetPixel(hMainDC,x,y);
			if (MainBitPixel == sColorTransparent) {
				::SetPixel(hAndMaskDC, x, y, RGB(255, 255, 255));
				::SetPixel(hXorMaskDC, x, y, RGB(0, 0, 0));
			} else {
				::SetPixel(hAndMaskDC, x, y, RGB(0, 0, 0));
				::SetPixel(hXorMaskDC, x, y, MainBitPixel);
			}
		}
	}

	// Select bitmaps
	::SelectObject(hMainDC, hOldMainBitmap);
	::SelectObject(hAndMaskDC, hOldAndMaskBitmap);
	::SelectObject(hXorMaskDC, hOldXorMaskBitmap);

	// Destroy device contexts
	::DeleteDC(hXorMaskDC);
	::DeleteDC(hAndMaskDC);
	::DeleteDC(hMainDC);
	::ReleaseDC(nullptr, hDC);
}

/**
*  @brief
*    Create an icon from a HBITMAP
*/
HICON ToolsWindows::CreateIconFromBitmap(HBITMAP hBitmap)
{
	// Get bitmap size
	BITMAP sBitmap;
	::GetObject(hBitmap, sizeof(BITMAP), &sBitmap);

	// Create mask
	HBITMAP hMask = ::CreateCompatibleBitmap(::GetDC(nullptr), sBitmap.bmWidth, sBitmap.bmHeight);

	// Create icon
	ICONINFO sIconInfo;
	sIconInfo.fIcon		= TRUE;
	sIconInfo.hbmColor	= hBitmap;
	sIconInfo.hbmMask	= hMask;
	HICON hIcon = ::CreateIconIndirect(&sIconInfo);

	// Release bitmap mask
	::DeleteObject(hMask);

	// Return icon
	return hIcon;
}

/**
*  @brief
*    Create a cursor from a HBITMAP
*/
HCURSOR ToolsWindows::CreateCursorFromBitmap(HBITMAP hBitmap, COLORREF sColorTransparent, DWORD nHotspotX, DWORD nHotspotY)
{
	// Check if the bitmap handle is valid
	if (hBitmap) {
		// Create the AND and XOR masks for the bitmap
		HBITMAP hAndMask = nullptr;
		HBITMAP hXorMask = nullptr;
		GetMaskBitmaps(hBitmap, sColorTransparent, hAndMask, hXorMask);
		if (hAndMask && hXorMask) {
			// Create the cursor using the masks and the hotspot values provided
			ICONINFO iconinfo = {0};
			iconinfo.fIcon    = FALSE;
			iconinfo.xHotspot = nHotspotX;
			iconinfo.yHotspot = nHotspotY;
			iconinfo.hbmMask  = hAndMask;
			iconinfo.hbmColor = hXorMask;

			// Create and return new cursor
			return ::CreateIconIndirect(&iconinfo);
		}
	}

	// Error
	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
