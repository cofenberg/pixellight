/*********************************************************\
 *  File: TextureCreatorHorizonMap3D.cpp                 *
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
#include <PLGeneral/Log/Log.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include "PLRenderer/RendererContext.h"
#include "PLRenderer/Texture/TextureManager.h"
#include "PLRenderer/Texture/Creator/TextureCreatorHorizonMap3D.h"


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
pl_implement_class(TextureCreatorHorizonMap3D)


//[-------------------------------------------------------]
//[ Internal helper functions                             ]
//[-------------------------------------------------------]
#define ROUND(x) (int)(x + 0.5f)
inline uint8 Pack2(float x)
{
	return (uint8)(255.0f*x);
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
TextureCreatorHorizonMap3D::TextureCreatorHorizonMap3D() :
	Filename2D(this),
	XSize(this),
	YSize(this),
	ZSize(this),
	Height(this)
{
}

/**
*  @brief
*    Destructor
*/
TextureCreatorHorizonMap3D::~TextureCreatorHorizonMap3D()
{
}


//[-------------------------------------------------------]
//[ Private virtual TextureCreator functions              ]
//[-------------------------------------------------------]
Texture *TextureCreatorHorizonMap3D::Create(TextureManager &cTextureManager, Texture *pTexture) const
{
	// Try to load the 2D ASCII texture
	Image cImage2D;
	if (cImage2D.Load(Filename2D)) {
		// Get the image buffer
		ImageBuffer *pImageBuffer = cImage2D.GetBuffer();
		if (pImageBuffer) {
			const uint8 *src = pImageBuffer->GetData();
			const uint32 w = pImageBuffer->GetSize().x;
			const uint32 h = pImageBuffer->GetSize().y;

			// Create the texture
			pTexture = CreateTexture(cTextureManager, pTexture);

			// Create the image
			Image cImage;
			pImageBuffer = cImage.CreatePart()->CreateMipmap();
			pImageBuffer->CreateImage(DataByte, ColorGrayscale, Vector3i(XSize, YSize, ZSize));

			// Create the buffer
			uint8 *pBuffer = pImageBuffer->GetData();
			uint8 *pDest = pBuffer;
			for (uint32 z=0; z<ZSize; z++) {
				float xv = Math::Cos(float(z*Math::Pi2/ZSize));
				float yv = Math::Sin(float(z*Math::Pi2/ZSize));

				const float invMax = 1.0f/Math::Max(Math::Abs(xv), Math::Abs(yv));
				xv *= invMax;
				yv *= invMax;

				const float len = Math::Sqrt(xv*xv + yv*yv);

				for (uint32 y=0; y<YSize; y++) {
					for (uint32 x=0; x<XSize; x++) {
						float maxAng = 0;

						float xp = float(x*w)/XSize;
						float yp = float(y*h)/YSize;

						const float bh = float(src[int(yp)*w + int(xp)]);

						float dist = 0;

						for (uint32 i=0; i<256; i++) {
							xp += xv;
							yp += yv;
							dist += len;

							int xt = ROUND(xp);
							int yt = ROUND(yp);

							while (xt < 0)
								xt += w;
							while (yt < 0)
								yt += h;

							xt %= w;
							yt %= h;

							const float ang = (float(src[yt*w + xt]) - bh)/dist;
							if (ang > maxAng)
								maxAng = ang;
						}

						*pDest++ = Pack2(Math::Sin(Math::ATan(Height*maxAng)));
					}
				}
			}

			// Create the 3D texture buffer
			pTexture->SetTextureBuffer((TextureBuffer*)cTextureManager.GetRendererContext().GetRenderer().CreateTextureBuffer3D(cImage));

			// Return the created texture
			return pTexture;
		}
	} else {
		PL_LOG(Error, "Can't open: " + Filename2D)
	}

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
