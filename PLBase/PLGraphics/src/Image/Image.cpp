/*********************************************************\
 *  File: Image.cpp                                      *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Core/MemoryManager.h>
#include "PLGraphics/Image/ImageEffect.h"
#include "PLGraphics/Image/Image.h"
#include "PLGraphics/Image/ImagePart.h"
#include "PLGraphics/Image/ImageBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Image::Image()
{
}

/**
*  @brief
*    Copy constructor
*/
Image::Image(const Image &cSource)
{
	// Copy parts
	for (uint32 i=0; i<cSource.m_lstParts.GetNumOfElements(); i++) {
		// Create copy of part
		ImagePart *pImagePart = new ImagePart(*cSource.m_lstParts[i]);
		m_lstParts.Add(pImagePart);
		m_mapParts.Add(pImagePart->GetSemantics(), pImagePart);
	}
}

/**
*  @brief
*    Destructor
*/
Image::~Image()
{
	// Clear data
	Clear();
}

/**
*  @brief
*    Assignment operator
*/
Image &Image::operator =(const Image &cSource)
{
	// Clear data
	Clear();

	// Copy parts
	for (uint32 i=0; i<cSource.m_lstParts.GetNumOfElements(); i++) {
		// Create copy of part
		ImagePart *pImagePart = new ImagePart(*cSource.m_lstParts[i]);
		m_lstParts.Add(pImagePart);
		m_mapParts.Add(pImagePart->GetSemantics(), pImagePart);
	}

	// Copy filename and URL from the Loadable class
	m_sFilename = cSource.m_sFilename;
	m_sUrl      = cSource.m_sUrl;

	// Return this
	return *this;
}

/**
*  @brief
*    Clear data
*/
void Image::Clear()
{
	// Destroy parts
	for (uint32 i=0; i<m_lstParts.GetNumOfElements(); i++) {
		delete m_lstParts[i];
	}

	// Clear frame list
	m_lstParts.Clear();
	m_mapParts.Clear();
}

/**
*  @brief
*    Apply image effect
*/
void Image::ApplyEffect(const ImageEffect &cEffect)
{
	cEffect.Apply(*this);
}

/**
*  @brief
*    Check image for possible problems
*/
ECheckConsistency Image::CheckConsistency() const
{
	// Check if image has at least one part
	if (m_lstParts.GetNumOfElements() == 0) {
		// Image has no parts
		return CheckImageEmpty;
	}

	// Check if a cubemap is defined
	bool bCubemap    = false;
	bool bSideOther  = false;
	bool bSideDouble = false;
	bool bSide[6]    = {false, false, false, false, false, false};
	for (uint32 i=0; i<m_lstParts.GetNumOfElements(); i++) {
		// Check cubemap side
		uint32 nSemantics = m_lstParts[i]->GetSemantics();
		switch (nSemantics) {
			case ImagePartCubeSidePosX:		if (bSide[0]) bSideDouble = true; bSide[0] = true; break;
			case ImagePartCubeSideNegX:		if (bSide[1]) bSideDouble = true; bSide[1] = true; break;
			case ImagePartCubeSidePosY:		if (bSide[2]) bSideDouble = true; bSide[2] = true; break;
			case ImagePartCubeSideNegY:		if (bSide[3]) bSideDouble = true; bSide[3] = true; break;
			case ImagePartCubeSidePosZ:		if (bSide[4]) bSideDouble = true; bSide[4] = true; break;
			case ImagePartCubeSideNegZ:		if (bSide[5]) bSideDouble = true; bSide[5] = true; break;
			default:						bSideOther = true; break;
		}
	}
	bCubemap = bSide[0] || bSide[1] || bSide[2] || bSide[3] || bSide[4] || bSide[5];

	// Check cubemap consistency
	// [TODO] Are all cubemap sides of the same size?
	if (bCubemap) {
		// A cubemap side is missing
		if (!bSide[0] || !bSide[1] || !bSide[2] || !bSide[3] || !bSide[4] || !bSide[5])
			return CheckCubemapSideMissing;

		// Part found that is not a cubemap side
		if (bSideOther)
			return CheckCubemapSideInvalid;

		// Two parts found that have the same cubemap side ID
		if (bSideDouble)
			return CheckCubemapSideDouble;
	}

	// Check parts consistency
	for (uint32 i=0; i<m_lstParts.GetNumOfElements(); i++) {
		// Check consistency of ImageFrame
		const ECheckConsistency nCheck = m_lstParts[i]->CheckConsistency();
		if (nCheck != CheckOk) return nCheck;
	}

	// No problem found
	return CheckOk;
}

/**
*  @brief
*    Check if this image is a multi-part image (e.g. a CubeMap)
*/
bool Image::IsMultiPart() const
{
	// Check if there is more than one part
	return (m_lstParts.GetNumOfElements() > 1);
}

/**
*  @brief
*    Get number of image parts
*/
uint32 Image::GetNumOfParts() const
{
	// Return number of parts
	return m_lstParts.GetNumOfElements();
}

/**
*  @brief
*    Get image part
*/
ImagePart *Image::GetPart(uint32 nIndex) const
{
	// Return part
	return m_lstParts[nIndex];
}

/**
*  @brief
*    Get image part by semantics
*/
ImagePart *Image::GetPartBySemantics(uint32 nSemantics) const
{
	// Return part
	return m_mapParts.Get(nSemantics);
}

/**
*  @brief
*    Get image parts
*/
const Container<ImagePart*> &Image::GetParts() const
{
	// Return part list
	return m_lstParts;
}

/**
*  @brief
*    Create a new image part
*/
ImagePart *Image::CreatePart(uint32 nSemantics)
{
	// Create if semantics ID is already used
	if (m_mapParts.Get(nSemantics) == NULL) {
		// Create image part
		ImagePart *pPart = new ImagePart();
		pPart->SetSemantics(nSemantics);

		// Add image part to list
		m_lstParts.Add(pPart);
		m_mapParts.Add(nSemantics, pPart);

		// Return image part
		return pPart;
	}

	// Error!
	return NULL;
}

/**
*  @brief
*    Delete image part
*/
bool Image::DeletePart(ImagePart &cPart)
{
	// Check part
	ImagePart *pPart = &cPart;
	if (m_lstParts.IsElement(pPart)) {
		// Remove and delete part
		m_lstParts.Remove(pPart);
		m_mapParts.Remove(pPart->GetSemantics());
		delete pPart;

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Get image buffer
*/
ImageBuffer *Image::GetBuffer(uint32 nPart, uint32 nMipmap) const
{
	// Get image part
	const ImagePart *pPart = GetPart(nPart);
	if (pPart) {
		// Get mipmap
		ImageBuffer *pBuffer = pPart->GetMipmap(nMipmap);
		if (pBuffer) {
			// Return buffer
			return pBuffer;
		}
	}

	// Invalid buffer requested
	return NULL;
}

/**
*  @brief
*    Create a test image
*/
void Image::CreateTestImage(ETestImage nTestImage)
{
	// Clear data
	Clear();

	// Get test image ID
	switch (nTestImage) {
		// 2D test images
		case TestImage2DSimple:
		case TestImage2DGradient:
		case TestImage2DCheckers:
			CreatePart()->CreateMipmap()->CreateTestImage(nTestImage);
			break;

		// Cube map
		case TestImageCubeMap:
			// [TODO] implement
			break;
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Loadable functions             ]
//[-------------------------------------------------------]
String Image::GetLoadableTypeName() const
{
	static const String sString = "Image";
	return sString;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
