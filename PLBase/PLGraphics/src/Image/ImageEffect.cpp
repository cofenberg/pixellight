/*********************************************************\
 *  File: ImageEffect.cpp                                *
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
#include <PLCore/Base/Class.h>
#include "PLGraphics/Image/Image.h"
#include "PLGraphics/Image/ImagePart.h"
#include "PLGraphics/Image/ImageBuffer.h"
#include "PLGraphics/Image/ImageEffect.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ImageEffect)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
ImageEffect::ImageEffect()
{
}

/**
*  @brief
*    Destructor
*/
ImageEffect::~ImageEffect()
{
}

/**
*  @brief
*    Get effect description
*/
String ImageEffect::GetDescription() const
{
	// [TODO] New RTTI usage: Remove this method?
	const PLCore::Class *pClass = GetClass();
	return (pClass != nullptr) ? pClass->GetDescription() : "";
}


//[-------------------------------------------------------]
//[ Public virtual functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Apply effect to image
*/
bool ImageEffect::Apply(Image &cImage) const
{
	// Usually, applying an image effect to an image means to apply it to every part
	if (cImage.GetNumOfParts() > 0) {
		// Apply to all parts
		bool bResult = true;
		for (uint32 i=0; i<cImage.GetNumOfParts(); i++) {
			// Get part
			ImagePart *pPart = cImage.GetPart(i);
			if (pPart) {
				// Apply effect
				if (!Apply(*pPart))
					bResult = false;
			}
		}

		// Return result
		return bResult;
	}

	// No parts available
	return false;
}

/**
*  @brief
*    Apply effect to image part
*/
bool ImageEffect::Apply(ImagePart &cImagePart) const
{
	// Usually, applying an image effect to a part means to apply it to the first image buffer and rebuild mipmaps
	ImageBuffer *pBuffer = cImagePart.GetMipmap(0);
	if (pBuffer) {
		// Apply effect
		bool bResult = Apply(*pBuffer);

		// Rebuild mipmaps
		if (cImagePart.GetNumOfMipmaps() > 1)
			cImagePart.BuildMipmaps();

		// Return result
		return bResult;
	}

	// No image buffers available
	return false;
}

/**
*  @brief
*    Apply effect to image buffer
*/
bool ImageEffect::Apply(ImageBuffer &cImageBuffer) const
{
	// Not implemented
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
