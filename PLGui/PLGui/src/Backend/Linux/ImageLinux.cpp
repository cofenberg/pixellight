/*********************************************************\
 *  File: ImageLinux.cpp                                 *
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
#include "PLGui/Widgets/Widget.h"	// We really need to include this before the other one because else the Linux headers
									// will cause compiler errors (stupid stupid OS defines!)
#include <PLGraphics/Color/Color4.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include "PLGui/Gui/Gui.h"
#include "PLGui/Gui/Resources/Image.h"
#include "PLGui/Backend/Linux/ToolsLinux.h"
#include "PLGui/Backend/Linux/GuiLinux.h"
#include "PLGui/Backend/Linux/ImageLinux.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGraphics;
using namespace PLMath;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ImageLinux::ImageLinux(Image &cImage) : ImageImpl(cImage),
	m_pDisplay(((GuiLinux*)cImage.GetGui()->GetImpl())->GetDisplay()),
	m_pPixmap(XLib::None),
	m_pMaskPixmap(XLib::None),
	m_pImage(new PLGraphics::Image())
{
}

/**
*  @brief
*    Destructor
*/
ImageLinux::~ImageLinux()
{
	// Free pixmap
	if (m_pPixmap)		XFreePixmap(m_pDisplay, m_pPixmap);
	if (m_pMaskPixmap)	XFreePixmap(m_pDisplay, m_pMaskPixmap);

	// Delete image
	if (m_pImage) delete m_pImage;
}

/**
*  @brief
*    Get pixmap
*/
Pixmap ImageLinux::GetPixmap() const
{
	// Return pixmap
	return m_pPixmap;
}

/**
*  @brief
*    Get mask pixmap
*/
Pixmap ImageLinux::GetMaskPixmap() const
{
	// Return mask pixmap
	return m_pMaskPixmap;
}


//[-------------------------------------------------------]
//[ Public virtual ImageImpl functions                    ]
//[-------------------------------------------------------]
bool ImageLinux::Load(const String &sFilename)
{
	// Load without color key
	return LoadPixmap(sFilename, Color4::Transparent);
}

bool ImageLinux::LoadWithColorKey(const String &sFilename, const Color3 &cColor)
{
	// Load with color key
	return LoadPixmap(sFilename, Color4(cColor));
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Load pixmap
*/
bool ImageLinux::LoadPixmap(const PLGeneral::String &sFilename, const PLGraphics::Color4 &cColorKey)
{
	// Free pixmap
	if (m_pPixmap)		XFreePixmap(m_pDisplay, m_pPixmap);
	if (m_pMaskPixmap)	XFreePixmap(m_pDisplay, m_pMaskPixmap);
	m_pPixmap	  = NULL_HANDLE;
	m_pMaskPixmap = NULL_HANDLE;
	m_pImage	  = nullptr;

	// Check file name
	if (sFilename.GetLength()) {
		// Load image
		m_pImage = new PLGraphics::Image();
		if (m_pImage->Load(sFilename)) {
			// Convert to pixmap
			if (ToolsLinux::CreatePixmapFromImage(m_pDisplay, *m_pImage, m_pPixmap, m_pMaskPixmap, cColorKey)) {
				// Image loaded
				m_sFilename	  = sFilename;
				m_vSize.x	  = m_pImage->GetBuffer()->GetSize().x;
				m_vSize.y	  = m_pImage->GetBuffer()->GetSize().y;
				m_nColorDepth = m_pImage->GetBuffer()->GetBytesPerPixel() * 8;
				return true;
			}
		}

		// Error, free pixmap
		if (m_pPixmap)		XFreePixmap(m_pDisplay, m_pPixmap);
		if (m_pMaskPixmap)	XFreePixmap(m_pDisplay, m_pMaskPixmap);
		m_pPixmap	  = NULL_HANDLE;
		m_pMaskPixmap = NULL_HANDLE;
		m_pImage	  = nullptr;
	}

	// Error!
	m_sFilename   = "";
	m_vSize.x	  = 0;
	m_vSize.y	  = 0;
	m_nColorDepth = 0;
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
