/*********************************************************\
 *  File: Image.cpp                                      *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2i.h>
#include "PLGui/Gui/Resources/Image.h"
#include "PLGui/Gui/Gui.h"
#include "PLGui/Backend/ImageImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
namespace PLGui {


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Image::Image(Gui &cGui, const String &sFilename) :
	m_pGui(&cGui),
	m_pImageImpl(nullptr)
{
	// Load image
	if (sFilename.GetLength()) {
		Load(sFilename);
	}
}

/**
*  @brief
*    Copy constructor
*/
Image::Image(const Image &cImage) :
	m_pGui(cImage.m_pGui),
	m_pImageImpl(cImage.m_pImageImpl),
	m_sFilename(cImage.m_sFilename)
{
	// Increase reference count for image
	if (m_pImageImpl) {
		m_pImageImpl->AddReference();
	}
}

/**
*  @brief
*    Destructor
*/
Image::~Image()
{
	// Release image
	if (m_pImageImpl) {
		m_pImageImpl->Release();
	}
}

/**
*  @brief
*    Assignment operator
*/
Image &Image::operator =(const Image &cImage)
{
	// Release image
	if (m_pImageImpl) {
		m_pImageImpl->Release();
		m_pImageImpl = nullptr;
	}

	// Copy image
	m_pImageImpl = cImage.m_pImageImpl;
	m_sFilename  = cImage.m_sFilename;
	if (m_pImageImpl) {
		m_pImageImpl->AddReference();
	}

	// Return reference to this font
	return *this;
}

/**
*  @brief
*    Get owner GUI
*/
Gui *Image::GetGui() const
{
	// Return GUI
	return m_pGui;
}

/**
*  @brief
*    Get implementation
*/
ImageImpl *Image::GetImpl() const
{
	// Return image implementation
	return m_pImageImpl;
}

/**
*  @brief
*    Check if image has been loaded
*/
bool Image::IsEmpty() const
{
	// Check if an image implementation is present
	return (m_pImageImpl == nullptr);
}

/**
*  @brief
*    Load image
*/
bool Image::Load(const String &sFilename)
{
	// Release image
	if (m_pImageImpl) {
		m_pImageImpl->Release();
		m_pImageImpl = nullptr;
	}

	// Store filename
	m_sFilename = sFilename;

	// Create image
	m_pImageImpl = m_pGui->CreateImageImpl(*this);
	m_pImageImpl->AddReference();

	// Load image
	return m_pImageImpl->Load(sFilename);
}

/**
*  @brief
*    Load image and apply a color key
*/
bool Image::LoadWithColorKey(const String &sFilename, const PLGraphics::Color3 &cColor)
{
	// Release image
	if (m_pImageImpl) {
		m_pImageImpl->Release();
		m_pImageImpl = nullptr;
	}

	// Store filename
	m_sFilename = sFilename;

	// Create image
	m_pImageImpl = m_pGui->CreateImageImpl(*this);
	m_pImageImpl->AddReference();

	// Load image
	return m_pImageImpl->LoadWithColorKey(sFilename, cColor);
}

/**
*  @brief
*    Get image name
*/
String Image::GetFilename() const
{
	// Return filename
	return m_sFilename;
}

/**
*  @brief
*    Get image size
*/
Vector2i Image::GetSize() const
{
	// Return size
	return (m_pImageImpl ? m_pImageImpl->GetSize() : Vector2i::Zero);
}

/**
*  @brief
*    Get color depth
*/
uint32 Image::GetColorDepth() const
{
	// Return color depth
	return (m_pImageImpl ? m_pImageImpl->GetColorDepth() : 0);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
