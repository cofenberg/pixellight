/*********************************************************\
 *  File: TextureCreatorTurbulence3D.cpp                 *
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
#include <PLMath/PerlinNoise.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include "PLRenderer/RendererContext.h"
#include "PLRenderer/Texture/TextureManager.h"
#include "PLRenderer/Texture/Creator/TextureCreatorTurbulence3D.h"


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
pl_implement_class(TextureCreatorTurbulence3D)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
TextureCreatorTurbulence3D::TextureCreatorTurbulence3D() :
	XSize(this),
	YSize(this),
	ZSize(this),
	Scale(this)
{
}

/**
*  @brief
*    Destructor
*/
TextureCreatorTurbulence3D::~TextureCreatorTurbulence3D()
{
}


//[-------------------------------------------------------]
//[ Private virtual TextureCreator functions              ]
//[-------------------------------------------------------]
Texture *TextureCreatorTurbulence3D::Create(TextureManager &cTextureManager, Texture *pTexture) const
{
	// Create the texture
	pTexture = CreateTexture(cTextureManager, pTexture);

	// Initialize perlin noise
	PLInitPerlin();

	// Get scale
	const Vector3 &vScale = Scale.Get();

	// Create the image
	Image cImage;
	ImageBuffer *pImageBuffer = cImage.CreatePart()->CreateMipmap();
	pImageBuffer->CreateImage(DataByte, ColorGrayscale, Vector3i(XSize, YSize, ZSize));

	// Create the buffer
	uint8 *pTurbBuffer = pImageBuffer->GetData();
	uint8 *pDest = pTurbBuffer;
	uint32 nMin = 255, nMax = 0;
	for (uint32 nZ=0; nZ<ZSize; nZ++) {
		for (uint32 nY=0; nY<YSize; nY++) {
			for (uint32 nX=0; nX<XSize; nX++) {
				const uint8 nT = static_cast<uint8>(127.5f*(1 + PLTileableTurbulence3(vScale.x*nX, vScale.y*nY, vScale.z*nZ, XSize*vScale.x, YSize*vScale.y, ZSize*vScale.z, 16)));
				if (nT > nMax)
					nMax = nT;
				if (nT < nMin)
					nMin = nT;
				*pDest++ = nT;
			}
		}
	}
	const uint32 nNumOfPixels = XSize*YSize*ZSize;
	pDest = pTurbBuffer;
	for (uint32 i=0; i<nNumOfPixels; i++, pDest++)
		*pDest = static_cast<uint8>((255*(*pDest - nMin))/(nMax - nMin));

	// Create the 3D texture buffer
	pTexture->SetTextureBuffer(reinterpret_cast<TextureBuffer*>(cTextureManager.GetRendererContext().GetRenderer().CreateTextureBuffer3D(cImage)));

	// Return the created texture
	return pTexture;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
