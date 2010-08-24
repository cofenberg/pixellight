/*********************************************************\
 *  File: TextureCreatorASCII3D.cpp                      *
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
#include <PLGeneral/Log/Log.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include "PLRenderer/RendererContext.h"
#include "PLRenderer/Texture/TextureManager.h"
#include "PLRenderer/Texture/Creator/TextureCreatorASCII3D.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(TextureCreatorASCII3D)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
TextureCreatorASCII3D::TextureCreatorASCII3D() :
	ASCIIFilename(this)
{
}

/**
*  @brief
*    Destructor
*/
TextureCreatorASCII3D::~TextureCreatorASCII3D()
{
}


//[-------------------------------------------------------]
//[ Private virtual TextureCreator functions              ]
//[-------------------------------------------------------]
Texture *TextureCreatorASCII3D::Create(TextureManager &cTextureManager, Texture *pTexture) const
{
	// Try to load the 2D ASCII texture
	Image cImage2D;
	if (cImage2D.Load(ASCIIFilename)) {
		// Get the image buffer
		ImageBuffer *p2DImageBuffer = cImage2D.GetBuffer();
		if (p2DImageBuffer) {
			// Create the texture
			pTexture = CreateTexture(cTextureManager, pTexture);

			// Create the image
			Image cImage;
			ImageBuffer *pImageBuffer = cImage.CreatePart()->CreateMipmap();
			pImageBuffer->CreateImage(DataByte, ColorGrayscale, Vector3i(16, 16, 256));

			const uint8 *src = p2DImageBuffer->GetData();
			float avg[256];
			for (uint32 j=0; j<16; j++) {
				for (uint32 i=0; i<16; i++) {
					avg[j*16 + i] = 0;

					uint32 base = j*256*16 + i*16;
					for (uint32 b=0; b<16; b++) {
						for (uint32 a=0; a<16; a++)
							avg[j*16 + i] += float(src[base + 256*b + a]);
					}
					avg[j*16 + i] *= 1.0f/(255.0f*16*16);
				}
			}

			uint8 *pixels = pImageBuffer->GetData();
			uint8 *dest = pixels;

			for (uint32 j=0; j<256; j++) {
				const float av = float(j)/255.0f;

				uint32 index = 0;
				float minDiff = 1e10f;
				for (uint32 i=0; i<256; i++) {
					const float d = Math::Abs(avg[i] - av);
					if (d < minDiff) {
						minDiff = d;
						index = i;
					}
				}

				const uint32 r    = index/16;
				const uint32 c    = index%16;
				const uint32 base = r*256*16 + c*16;
				for (uint32 b=0; b<16; b++) {
					for (uint32 a=0; a<16; a++)
						*dest++ = src[base + 256*b + a];
				}
			}

			// Create the 3D texture buffer
			pTexture->SetTextureBuffer((TextureBuffer*)cTextureManager.GetRendererContext().GetRenderer().CreateTextureBuffer3D(cImage));
		}

		// Return the created texture
		return pTexture;
	} else {
		PL_LOG(Error, "Can't open: " + ASCIIFilename)
	}

	// Error!
	return NULL;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
