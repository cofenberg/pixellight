/*********************************************************\
 *  File: VolumeLoaderDDS.cpp                            *
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
#include <PLGraphics/Image/Image.h>
#include <PLRenderer/Renderer/TextureBuffer.h>
#include "PLVolume/Volume.h"
#include "PLVolume/Loader/VolumeLoaderDDS.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
namespace PLVolume {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(VolumeLoaderDDS)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool VolumeLoaderDDS::Load(Volume &cVolume, File &cFile)
{
	return LoadParams(cVolume, cFile, Volume::DefaultVoxelSize.x, Volume::DefaultVoxelSize.y, Volume::DefaultVoxelSize.z);
}

bool VolumeLoaderDDS::LoadParams(Volume &cVolume, File &cFile, float fVoxelSizeX, float fVoxelSizeY, float fVoxelSizeZ)
{
	// Load in the dds image
	if (cVolume.GetVolumeImage().LoadByFile(cFile)) {
		// Set the size of one voxel (without metric, but usually one unit is equal to one meter)
		cVolume.SetVoxelSize(Vector3(fVoxelSizeX, fVoxelSizeY, fVoxelSizeZ));

		// Done
		return true;
	}

	// Error!
	return false;
}

bool VolumeLoaderDDS::Save(const Volume &cVolume, File &cFile)
{
	// First: Try to save the volume texture buffer from the GPU
	TextureBuffer *pTextureBuffer = cVolume.GetVolumeTextureBuffer();
	if (pTextureBuffer) {
		// Download the texture buffer data from the GPU and save it
		Image cImage;
		pTextureBuffer->CopyDataToImage(cImage);
		return cImage.SaveByFile(cFile);
	} else {
		// Second: Try to save the CPU side volume image
		return const_cast<Image&>(cVolume.GetVolumeImage()).SaveByFile(cFile);	// Ugly const-cast, this volume loader is just a wrapper
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
VolumeLoaderDDS::VolumeLoaderDDS()
{
}

/**
*  @brief
*    Destructor
*/
VolumeLoaderDDS::~VolumeLoaderDDS()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
