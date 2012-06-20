/*********************************************************\
 *  File: VolumeLoaderRAW.cpp                            *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLCore/File/File.h>
#include <PLMath/Vector3i.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include "PLVolume/Volume.h"
#include "PLVolume/Loader/VolumeLoaderRAW.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
namespace PLVolume {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(VolumeLoaderRAW)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool VolumeLoaderRAW::LoadParams(Volume &cVolume, File &cFile, uint8 nDataType, uint16 nWidth, uint16 nHeight, uint16 nDepth)
{
	// Get the image holding the volumtric data
	Image &cImage = cVolume.GetVolumeImage();

	// Create image buffer
	ImageBuffer *pImageBuffer = cImage.CreatePart()->CreateMipmap();
	pImageBuffer->CreateImage(static_cast<EDataFormat>(nDataType), ColorGrayscale, Vector3i(nWidth, nHeight, nDepth));

	// Read the data
	cFile.Read(pImageBuffer->GetData(), 1, pImageBuffer->GetDataSize());

	// Done
	return true;
}

bool VolumeLoaderRAW::Save(const Volume &cVolume, File &cFile)
{
	// Get the image holding the volumtric data
	const Image &cImage = cVolume.GetVolumeImage();

	// Get image buffer
	ImageBuffer *pImageBuffer = cImage.GetBuffer();
	if (pImageBuffer) {
		// Save the data
		cFile.Write(pImageBuffer->GetData(), 1, pImageBuffer->GetDataSize());

		// Done
		return true;
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
VolumeLoaderRAW::VolumeLoaderRAW()
{
}

/**
*  @brief
*    Destructor
*/
VolumeLoaderRAW::~VolumeLoaderRAW()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
