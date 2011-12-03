/*********************************************************\
 *  File: TextureCreatorNormalizationCubeMap.cpp         *
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
#include "PLRenderer/Texture/Creator/TextureCreatorNormalizationCubeMap.h"


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
pl_implement_class(TextureCreatorNormalizationCubeMap)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
TextureCreatorNormalizationCubeMap::TextureCreatorNormalizationCubeMap() :
	Size(this)
{
}

/**
*  @brief
*    Destructor
*/
TextureCreatorNormalizationCubeMap::~TextureCreatorNormalizationCubeMap()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/*
*  @brief
*    Returns a cube vector
*/
Vector3 TextureCreatorNormalizationCubeMap::GetCubeVector(uint8 i, uint32 x, uint32 y) const
{
	const float s = (static_cast<float>(x) + 0.5f)/static_cast<float>(Size)*2.0f - 1.0f;
	const float t = (static_cast<float>(y) + 0.5f)/static_cast<float>(Size)*2.0f - 1.0f;
	Vector3 v;
	switch (i) {
		case 0:
			v = Vector3( 1.0f,    -t,    -s);
			break;

		case 1:
			v = Vector3(-1.0f,    -t,     s);
			break;

		case 2:
			v = Vector3(    s,  1.0f,     t);
			break;

		case 3:
			v = Vector3(    s, -1.0f,    -t);
			break;

		case 4:
			v = Vector3(    s,    -t,  1.0f);
			break;

		case 5:
			v = Vector3(   -s,    -t, -1.0f);
			break;
	}
	v.Normalize();

	// Return the cube vector
	return v;
}


//[-------------------------------------------------------]
//[ Private virtual TextureCreator functions              ]
//[-------------------------------------------------------]
Texture *TextureCreatorNormalizationCubeMap::Create(TextureManager &cTextureManager, Texture *pTexture) const
{
	// Create the texture
	pTexture = CreateTexture(cTextureManager, pTexture);

	// Create the normalization cube map data
	Image cImage;
	for (uint8 i=0; i<6; i++) {
		ImageBuffer *pImageBuffer = cImage.CreatePart(static_cast<uint32>(ImagePartCubeSidePosX) + i)->CreateMipmap();
		pImageBuffer->CreateImage(DataByte, ColorRGB, Vector3i(Size, Size, 1));

		uint8 *d = pImageBuffer->GetData();
		for (uint32 y=0; y<Size; y++) {
			for (uint32 x=0; x<Size; x++) {
				Vector3 vDir = GetCubeVector(i, x, y);
				vDir = (vDir + Vector3::One)*0.5f;
				*d++ = static_cast<uint8>(vDir.x*255.0f);
				*d++ = static_cast<uint8>(vDir.y*255.0f);
				*d++ = static_cast<uint8>(vDir.z*255.0f);
			}
		}
	}

	// Create the cube texture buffer
	pTexture->SetTextureBuffer(reinterpret_cast<TextureBuffer*>(cTextureManager.GetRendererContext().GetRenderer().CreateTextureBufferCube(cImage, TextureBuffer::Unknown, 0)));

	// Return the created texture
	return pTexture;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
