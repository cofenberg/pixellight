/*********************************************************\
 *  File: TextureCreatorSpot2D.cpp                       *
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
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include "PLRenderer/RendererContext.h"
#include "PLRenderer/Texture/TextureManager.h"
#include "PLRenderer/Texture/Creator/TextureCreatorSpot2D.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(TextureCreatorSpot2D)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
TextureCreatorSpot2D::TextureCreatorSpot2D() :
	Width(this),
	Height(this),
	Brightness(this)
{
}

/**
*  @brief
*    Destructor
*/
TextureCreatorSpot2D::~TextureCreatorSpot2D()
{
}


//[-------------------------------------------------------]
//[ Private virtual TextureCreator functions              ]
//[-------------------------------------------------------]
Texture *TextureCreatorSpot2D::Create(TextureManager &cTextureManager, Texture *pTexture) const
{
	// Create the texture
	pTexture = CreateTexture(cTextureManager, pTexture);

	// Create the image
	Image cImage = Image::CreateImage(DataByte, ColorGrayscale, Vector3i(Width, Height, 1));
	ImageBuffer *pImageBuffer = cImage.GetBuffer();

	// Create the texture data
	const float fWidthHalf  = static_cast<float>(Width/2)-0.5f;
	const float fHeightHalf = static_cast<float>(Height/2)-0.5f;
	uint8 *pData = pImageBuffer->GetData();
	for (uint32 j=0; j<Width; j++) {
		for (uint32 i=0; i<Height; i++) {
			const float x = (i - fWidthHalf)/fWidthHalf;
			const float y = (j - fHeightHalf)/fHeightHalf;

			const float ls = Math::Max(1 - (x*x + y*y), 0.0f);
			pData[j*Width+i] = static_cast<uint8>(Brightness*ls);
		}
	}

	// Create the 2D texture buffer
	pTexture->SetTextureBuffer(reinterpret_cast<TextureBuffer*>(cTextureManager.GetRendererContext().GetRenderer().CreateTextureBuffer2D(cImage)));

	// Return the created texture
	return pTexture;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
