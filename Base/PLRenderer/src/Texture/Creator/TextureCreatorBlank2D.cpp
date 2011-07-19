/*********************************************************\
 *  File: TextureCreatorBlank2D.cpp                      *
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
#include "PLRenderer/Texture/Creator/TextureCreatorBlank2D.h"


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
pl_implement_class(TextureCreatorBlank2D)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
TextureCreatorBlank2D::TextureCreatorBlank2D() :
	Width(this),
	Height(this),
	Components(this),
	Color(this)
{
}

/**
*  @brief
*    Destructor
*/
TextureCreatorBlank2D::~TextureCreatorBlank2D()
{
}


//[-------------------------------------------------------]
//[ Private virtual TextureCreator functions              ]
//[-------------------------------------------------------]
Texture *TextureCreatorBlank2D::Create(TextureManager &cTextureManager, Texture *pTexture) const
{
	// Create the texture
	pTexture = CreateTexture(cTextureManager, pTexture);

	// Create the image
	Image cImage = Image::CreateImage(DataByte, ColorRGB, Vector3i(Width, Height, 1));
	ImageBuffer *pImageBuffer = cImage.GetBuffer();

	// Get the color
	const Color4 &cColor = Color.Get();

	// Create the texture data
	uint8 *pData = pImageBuffer->GetData();
	const uint8 nRed   = cColor.GetRInt();
	const uint8 nGreen = cColor.GetGInt();
	const uint8 nBlue  = cColor.GetBInt();
	const uint8 nAlpha = cColor.GetAInt();
	const uint32 nNumOfPixels = Width*Height;
	switch (Components) {
		case 1:
			for (uint32 i=0; i<nNumOfPixels; i++) {
				*pData = nRed;
				pData++;
			}
			break;

		case 2:
			for (uint32 i=0; i<nNumOfPixels; i++) {
				*pData = nRed;
				pData++;
				*pData = nGreen;
				pData++;
			}
			break;

		case 3:
			for (uint32 i=0; i<nNumOfPixels; i++) {
				*pData = nRed;
				pData++;
				*pData = nGreen;
				pData++;
				*pData = nBlue;
				pData++;
			}
			break;

		case 4:
			for (uint32 i=0; i<nNumOfPixels; i++) {
				*pData = nRed;
				pData++;
				*pData = nGreen;
				pData++;
				*pData = nBlue;
				pData++;
				*pData = nAlpha;
				pData++;
			}
			break;
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
