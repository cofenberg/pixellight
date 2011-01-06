/*********************************************************\
 *  File: ImageWindows.cpp                               *
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
#include <PLGraphics/Color/Color3.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLGraphics/Image/ImageToolsWindows.h>
#include <PLGraphics/Image/ImageEffects.h>
#include "PLGui/Backend/Windows/ToolsWindows.h"
#include "PLGui/Backend/Windows/ImageWindows.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGraphics;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ImageWindows::ImageWindows(Image &cImage) : ImageImpl(cImage),
	m_hBitmap(nullptr),
	m_hIcon(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
ImageWindows::~ImageWindows()
{
	// Clean up
	Unload();
}

/**
*  @brief
*    Get bitmap handle
*/
HBITMAP ImageWindows::GetBitmapHandle() const
{
	// Return image handle
	return m_hBitmap;
}

/**
*  @brief
*    Get icon handle of the image
*/
HICON ImageWindows::GetIconHandle()
{
	// Has the icon already been created?
	if (m_hBitmap != nullptr && m_hIcon == nullptr) {
		// Create icon
		m_hIcon = ToolsWindows::CreateIconFromBitmap(m_hBitmap);
	}

	// Return icon handle
	return m_hIcon;
}

/**
*  @brief
*    Unload image
*/
void ImageWindows::Unload()
{
	// Delete icon
	if (m_hIcon) {
		DeleteObject(m_hIcon);
		m_hIcon = nullptr;
	}

	// Delete bitmap
	if (m_hBitmap) {
		DeleteObject(m_hBitmap);
		m_hBitmap = nullptr;
	}
}


//[-------------------------------------------------------]
//[ Public virtual ImageImpl functions                    ]
//[-------------------------------------------------------]
bool ImageWindows::Load(const String &sFilename)
{
	// Check parameter
	if (sFilename.GetLength()) {
		// Delete bitmap
		Unload();

		// Load the image
		PLGraphics::Image cImage;
		if (cImage.Load(sFilename)) {
			// Get the image buffer
			const PLGraphics::ImageBuffer *pImageBuffer = cImage.GetBuffer();
			if (pImageBuffer) {
				// Convert to Windows bitmap
				m_hBitmap = ImageToolsWindows::ConvertToHBitmap(cImage, GetDC(nullptr));
				if (m_hBitmap) {
					// Save attributes
					m_sFilename = sFilename;

					// Find bitmap dimensions
					BITMAP sBitmap;
					::GetObject(m_hBitmap, sizeof(BITMAP), &sBitmap);
					m_vSize.x = sBitmap.bmWidth;
					m_vSize.y = sBitmap.bmHeight;
					m_nColorDepth = pImageBuffer->GetComponentsPerPixel() * 8;

					// Done
					return true;
				}
			}
		}
	}

	// Error!
	m_sFilename		= "";
	m_vSize.x		= 0;
	m_vSize.y		= 0;
	m_nColorDepth	= 0;
	m_hBitmap		= nullptr;
	return false;
}

bool ImageWindows::LoadWithColorKey(const String &sFilename, const Color3 &cColor)
{
	// Check parameter
	if (sFilename.GetLength()) {
		// Delete bitmap
		Unload();

		// Load the image
		PLGraphics::Image cImage;
		if (cImage.Load(sFilename)) {
			// Apply color key
			cImage.ApplyEffect(ImageEffects::ColorKey(cColor, 0.0f));

			// Get the image buffer
			const PLGraphics::ImageBuffer *pImageBuffer = cImage.GetBuffer();
			if (pImageBuffer) {
				// Convert to Windows bitmap
				m_hBitmap = ImageToolsWindows::ConvertToHBitmap(cImage, GetDC(nullptr));
				if (m_hBitmap) {
					// Save attributes
					m_sFilename = sFilename;

					// Find bitmap dimensions
					BITMAP sBitmap;
					::GetObject(m_hBitmap, sizeof(BITMAP), &sBitmap);
					m_vSize.x = sBitmap.bmWidth;
					m_vSize.y = sBitmap.bmHeight;
					m_nColorDepth = pImageBuffer->GetComponentsPerPixel() * 8;

					// Done
					return true;
				}
			}
		}
	}

	// Error!
	m_sFilename		= "";
	m_vSize.x		= 0;
	m_vSize.y		= 0;
	m_nColorDepth	= 0;
	m_hBitmap		= nullptr;
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
