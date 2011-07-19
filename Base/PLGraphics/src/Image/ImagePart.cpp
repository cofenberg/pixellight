/*********************************************************\
 *  File: ImagePart.cpp                                  *
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
#include "PLGraphics/Image/ImageEffect.h"
#include "PLGraphics/Image/ImageBuffer.h"
#include "PLGraphics/Image/ImagePart.h"


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
*    Constructor
*/
ImagePart::ImagePart() :
	m_nSemantics(0)
{
}

/**
*  @brief
*    Copy constructor
*/
ImagePart::ImagePart(const ImagePart &cSource) :
	m_nSemantics(cSource.m_nSemantics)
{
	// Copy mipmaps
	for (uint32 i=0; i<cSource.m_lstMipmaps.GetNumOfElements(); i++) {
		// Create copy of mipmap
		ImageBuffer *pImageBuffer = new ImageBuffer(*cSource.m_lstMipmaps[i]);
		m_lstMipmaps.Add(pImageBuffer);
	}
}

/**
*  @brief
*    Destructor
*/
ImagePart::~ImagePart()
{
	// Clear data
	Clear();
}

/**
*  @brief
*    Assignment operator
*/
ImagePart &ImagePart::operator =(const ImagePart &cSource)
{
	// Clear data
	Clear();

	// Copy data
	m_nSemantics = cSource.m_nSemantics;

	// Copy mipmaps
	for (uint32 i=0; i<cSource.m_lstMipmaps.GetNumOfElements(); i++) {
		// Create copy of mipmap
		ImageBuffer *pImageBuffer = new ImageBuffer(*cSource.m_lstMipmaps[i]);
		m_lstMipmaps.Add(pImageBuffer);
	}

	// Return this
	return *this;
}

/**
*  @brief
*    Clear data
*/
void ImagePart::Clear()
{
	// Destroy mipmaps
	for (uint32 i=0; i<m_lstMipmaps.GetNumOfElements(); i++) {
		delete m_lstMipmaps[i];
	}

	// Clear mipmap list
	m_lstMipmaps.Clear();
}

/**
*  @brief
*    Apply image effect
*/
void ImagePart::ApplyEffect(const ImageEffect &cEffect)
{
	cEffect.Apply(*this);
}

/**
*  @brief
*    Check image for possible problems
*/
ECheckConsistency ImagePart::CheckConsistency() const
{
	// Check if part has at least one mipmap
	if (m_lstMipmaps.GetNumOfElements() == 0) {
		// Part has no image buffers
		return CheckPartEmpty;
	}

	// Check mipmap consistency
	// [TODO] Is every mipmap smaller than the last one?	-> CheckMipmapInconsistent
	// [TODO] Is every mipmap power-of-two?					-> CheckMipmapsNotPowerOfTwo
	// [TODO] Are all mipmaps down to 1x1 defined?			-> CheckMipmapsNot1x1
	const EDataFormat  nDataFormat  = m_lstMipmaps[0]->GetDataFormat();
	const EColorFormat nColorFormat = m_lstMipmaps[0]->GetColorFormat();
	for (uint32 i=0; i<m_lstMipmaps.GetNumOfElements(); i++) {
		// Check consistency of ImageBuffer
		const ECheckConsistency nCheck = m_lstMipmaps[i]->CheckConsistency();
		if (nCheck != CheckOk)
			return nCheck;

		// Check data format
		if (m_lstMipmaps[i]->GetDataFormat() != nDataFormat) {
			// Inconsistent data format
			return CheckInconsistentDataFormat;
		}

		// Check color format
		if (m_lstMipmaps[i]->GetColorFormat() != nColorFormat) {
			// Inconsistent color format
			return CheckInconsistentColorFormat;
		}
	}

	// No problem found
	return CheckOk;
}

/**
*  @brief
*    Get semantics
*/
uint32 ImagePart::GetSemantics() const
{
	// Return semantics
	return m_nSemantics;
}

/**
*  @brief
*    Set semantics
*/
void ImagePart::SetSemantics(uint32 nSemantics)
{
	// Set semantics
	m_nSemantics = nSemantics;
}

/**
*  @brief
*    Check if the layer has mipmaps
*/
bool ImagePart::HasMipmaps() const
{
	// Check if there is more than one mipmap
	return (m_lstMipmaps.GetNumOfElements() > 1);
}

/**
*  @brief
*    Get number of mipmaps
*/
uint32 ImagePart::GetNumOfMipmaps() const
{
	// Return number of mipmaps
	return m_lstMipmaps.GetNumOfElements();
}

/**
*  @brief
*    Get mipmap
*/
ImageBuffer *ImagePart::GetMipmap(uint32 nIndex) const
{
	// Return mipmap
	return m_lstMipmaps[nIndex];
}

/**
*  @brief
*    Get mipmaps
*/
const Container<ImageBuffer*> &ImagePart::GetMipmaps() const
{
	// Return mipmap list
	return m_lstMipmaps;
}

/**
*  @brief
*    Build mipmaps
*/
bool ImagePart::BuildMipmaps()
{
	// Destroy all mipmaps - besides the first one (our base map)
	DeleteMipmaps();

	// [TODO] Implement
	return false;
}

/**
*  @brief
*    Create new mipmap
*/
ImageBuffer *ImagePart::CreateMipmap()
{
	// Create mipmap
	ImageBuffer *pBuffer = new ImageBuffer();

	// Add mipmap to list
	m_lstMipmaps.Add(pBuffer);

	// Return mipmap
	return pBuffer;
}

/**
*  @brief
*    Delete mipmap
*/
bool ImagePart::DeleteMipmap(ImageBuffer &cImageBuffer)
{
	// Remove and delete mipmap
	if (m_lstMipmaps.Remove(&cImageBuffer)) {
		delete &cImageBuffer;

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Deletes all mipmaps besides the first one (the base map)
*/
void ImagePart::DeleteMipmaps()
{
	// Are there any mipmaps?
	if (m_lstMipmaps.GetNumOfElements()) {
		for (uint32 i=1; i<m_lstMipmaps.GetNumOfElements(); i++)
			delete m_lstMipmaps[i];
		m_lstMipmaps.Resize(1);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
