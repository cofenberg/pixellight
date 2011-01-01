/*********************************************************\
 *  File: TextureCreatorAngleCubeMap.cpp                 *
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
#include "PLRenderer/Texture/Creator/TextureCreatorAngleCubeMap.h"


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
pl_implement_class(TextureCreatorAngleCubeMap)


//[-------------------------------------------------------]
//[ Internal helper functions                             ]
//[-------------------------------------------------------]
inline uint8 Pack1(float x)
{
	return (uint8)(255.0f*Math::Abs(x));
}

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
TextureCreatorAngleCubeMap::TextureCreatorAngleCubeMap() :
	Size(this)
{
}

/**
*  @brief
*    Destructor
*/
TextureCreatorAngleCubeMap::~TextureCreatorAngleCubeMap()
{
}


//[-------------------------------------------------------]
//[ Private virtual TextureCreator functions              ]
//[-------------------------------------------------------]
Texture *TextureCreatorAngleCubeMap::Create(TextureManager &cTextureManager, Texture *pTexture) const
{
	// Create the texture
	pTexture = CreateTexture(cTextureManager, pTexture);

	// Create the image parts
	Image cImage;
	for (int i=0; i<6; i++) {
		ImageBuffer *pImageBuffer = cImage.CreatePart(ImagePartCubeSidePosX + i)->CreateMipmap();
		pImageBuffer->CreateImage(DataByte, ColorRGB, Vector3i(Size, Size, 1));
	}

	float mid = 0.5f*(Size - 1);
	uint8 *pDestPos = cImage.GetPartBySemantics(ImagePartCubeSidePosX)->GetMipmap(0)->GetData();
	uint8 *pDestNeg = cImage.GetPartBySemantics(ImagePartCubeSideNegX)->GetMipmap(0)->GetData();
	for (uint32 y=0; y<Size; y++) {
		for (uint32 z=0; z<Size; z++) {
			float vx = mid;
			float vy = mid - y;
			float vz = mid - z;

			float ang0 = float(Math::ATan2(vy, vx)/Math::Pi);
			float ang1 = Vector3(vx, vz, vy).Normalize().DotProduct(Vector3(vx, 0.0f, vy).Normalize());
			ang1 = Math::Sqrt(Math::Abs(1 - ang1*ang1));

			*pDestPos++ = Pack2(ang1*(vz > 0));
			*pDestPos++ = Pack1(ang0);
			*pDestPos++ = 0;

			*pDestNeg++ = Pack2(ang1*(vz < 0));
			*pDestNeg++ = Pack1(ang0 - Math::Sign(vy));
			*pDestNeg++ = 0;
		}
	}

	pDestPos = cImage.GetPartBySemantics(ImagePartCubeSidePosY)->GetMipmap(0)->GetData();
	pDestNeg = cImage.GetPartBySemantics(ImagePartCubeSideNegY)->GetMipmap(0)->GetData();
	for (uint32 z=0; z<Size; z++) {
		for (uint32 x=0; x<Size; x++) {
			float vx = x - mid;
			float vy = mid;
			float vz = z - mid;

			float ang0 = float(Math::ATan2(vy, vx)/Math::Pi);
			float ang1 = Vector3(vx, vz, vy).Normalize().DotProduct(Vector3(vx, 0.0f, vy).Normalize());
			ang1 = Math::Sqrt(Math::Abs(1 - ang1*ang1));

			*pDestPos++ = Pack2(ang1*(vz > 0));
			*pDestPos++ = Pack1(ang0);
			*pDestPos++ = 0;

			*pDestNeg++ = Pack2(ang1*(vz < 0));
			*pDestNeg++ = Pack1(-ang0);
			*pDestNeg++ = 0;
		}
	}

	pDestPos = cImage.GetPartBySemantics(ImagePartCubeSidePosZ)->GetMipmap(0)->GetData();
	pDestNeg = cImage.GetPartBySemantics(ImagePartCubeSideNegZ)->GetMipmap(0)->GetData();
	for (uint32 y=0; y<Size; y++) {
		for (uint32 x=0; x<Size; x++) {
			float vx = x - mid;
			float vy = mid - y;
			float vz = mid;

			float ang0 = float(Math::ATan2(vy, vx)/Math::Pi);
			float ang1 = Vector3(vx, vz, vy).Normalize().DotProduct(Vector3(vx, 0.0f, vy).Normalize());
			ang1 = Math::Sqrt(Math::Abs(1 - ang1*ang1));

			*pDestPos++ = Pack2(ang1);
			*pDestPos++ = Pack1(ang0);
			*pDestPos++ = 0;

			*pDestNeg++ = 0;
			*pDestNeg++ = Pack1(Math::Sign(vy) - ang0);
			*pDestNeg++ = 0;
		}
	}

	// Create the cube texture buffer
	pTexture->SetTextureBuffer((TextureBuffer*)cTextureManager.GetRendererContext().GetRenderer().CreateTextureBufferCube(cImage, TextureBuffer::Unknown, 0));

	// Return the created texture
	return pTexture;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
