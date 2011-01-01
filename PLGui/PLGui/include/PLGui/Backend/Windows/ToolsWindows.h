/*********************************************************\
 *  File: ToolsWindows.h                                 *
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


#ifndef __PLGUI_TOOLSWINDOWS_H__
#define __PLGUI_TOOLSWINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneralWindowsIncludes.h>
#include "PLGui/PLGui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Tool functions for the Windows GUI implementation
*/
class ToolsWindows {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Create AND and XOR masks from a HBITMAP
		*
		*  @param[in]  hBitmap
		*    Source bitmap
		*  @param[in]  sColorTransparent
		*    Transparent color
		*  @param[out] hMaskAnd
		*    And bitmap mask
		*  @param[out] hMaskXor
		*    Xor bitmap mask
		*
		*  @note
		*    - Pass bitmaps having standard cursor sizes like 16*16, 32*32...
		*/
		PLGUI_API static void GetMaskBitmaps(HBITMAP hBitmap, COLORREF sColorTransparent, HBITMAP &hMaskAnd, HBITMAP &hMaskXor);

		/**
		*  @brief
		*    Create an icon from a HBITMAP
		*
		*  @param[in] hBitmap
		*    Source bitmap
		*
		*  @return
		*    Icon handle
		*/
		PLGUI_API static HICON CreateIconFromBitmap(HBITMAP hBitmap);

		/**
		*  @brief
		*    Create a cursor from a HBITMAP
		*
		*  @param[in] hBitmap
		*    Source bitmap
		*  @param[in] sColorTransparent
		*    Transparent color
		*  @param[in] nHotspotX
		*    Hot spot x position
		*  @param[in] nHotspotY
		*    Hot spot y position
		*
		*  @return
		*    The converted HBITMAP
		*/
		PLGUI_API static HCURSOR CreateCursorFromBitmap(HBITMAP hBitmap, COLORREF sColorTransparent, DWORD nHotspotX, DWORD nHotspotY);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_TOOLSWINDOWS_H__
