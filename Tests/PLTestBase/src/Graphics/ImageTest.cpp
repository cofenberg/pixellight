/*********************************************************\
 *  File: ImageTest.cpp                                  *
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
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLGraphics/Image/ImageEffects.h>
#include "PLTestBase/Graphics/ImageTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLGraphics;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *ImageTest::GetName() const
{
	return "Image";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void ImageTest::Test()
{
	bool bResult = true;

	// Load(const String &sFilename)
	Image cImage;
	StartTask("Load(const String &sFilename)");
	if (!cImage.LoadByFilename("test.tga"))
		bResult = false;

	// Get the image buffer
	ImageBuffer *pImageBuffer = cImage.GetBuffer();
	if (pImageBuffer) {
		// Check the image size
		if (pImageBuffer->GetSize().x != 512 || pImageBuffer->GetSize().y != 512 || pImageBuffer->GetSize().z != 1)
			bResult = false;

		// The image is using a palette, remove the palette!
		if (pImageBuffer->GetColorFormat() == ColorPalette) {
			// Convert the image buffer into grayscale
			if (!ImageEffects::Convert(DataByte, ColorGrayscale).Apply(*pImageBuffer))
				bResult = false;
		} else {
			bResult = false;
		}
	} else {
		bResult = false;
	}
	EndTask(bResult);

	// Save(const String &sFilename)
	StartTask("Save(const String &sFilename)");
	EndTask(cImage.SaveByFilename("test_saved.tga"));
}
