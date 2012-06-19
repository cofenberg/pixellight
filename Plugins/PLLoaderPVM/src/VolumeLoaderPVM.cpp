/*********************************************************\
 *  File: VolumeLoaderPVM.cpp                            *
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/File/File.h>
#include <PLMath/Vector3i.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLVolume/Volume.h>
#include "PLLoaderPVM/PVM_GPL_License/ddsbase.h"	// Lookout! GPL code!
#include "PLLoaderPVM/VolumeLoaderPVM.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLVolume;
namespace PLLoaderPVM {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(VolumeLoaderPVM)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool VolumeLoaderPVM::Load(Volume &cVolume, File &cFile)
{
	return LoadParams(cVolume, cFile, true);
}

bool VolumeLoaderPVM::LoadParams(Volume &cVolume, File &cFile, bool bForce8Bit)
{
	// Get the image holding the volumtric data
	Image &cImage = cVolume.GetVolumeImage();

	// [TODO] Just a test until transfer functions also properly work with 16 bit
	bForce8Bit = true;

	// Read the PVM volume
	unsigned int nWidth = 0, nHeight = 0, nDepth = 0, nComponents = 0;
	Vector3 vScale;
	unsigned char *pszPVMvolume = readPVMvolume(cFile.GetUrl().GetNativePath().GetASCII(), &nWidth, &nHeight, &nDepth, &nComponents, &vScale.x, &vScale.y, &vScale.z);
	if (pszPVMvolume) {
		// Force 8 bit?
		if (bForce8Bit && nComponents == 2) {
			// Quantize 16 bit volume to 8 bit using a non-linear mapping (by default, this function automatically frees the previous allocated memory)
			pszPVMvolume = quantize(pszPVMvolume, nWidth, nHeight, nDepth);
			nComponents = 1;
		}

		// We only support 8 bit and 16 bit
		if (nComponents == 1 || nComponents == 2) {
			// Create image - don't takeover the data because it was allocated using malloc
			cImage = Image::CreateImageAndCopyData((nComponents == 1) ? DataByte : DataWord, ColorGrayscale, Vector3i(nWidth, nHeight, nDepth), CompressionNone, pszPVMvolume);
		}

		// Cleanup
		MemoryManager::Deallocator(MemoryManager::Free, pszPVMvolume);

		// Set the size of one voxel (without metric, but usually one unit is equal to one meter)
		cVolume.SetVoxelSize(Volume::DefaultVoxelSize*vScale);

		// Done
		return true;
	}

	// Error!
	return false;
}

bool VolumeLoaderPVM::Save(const Volume &cVolume, File &cFile)
{
	// Get the image holding the volumtric data
	const Image &cImage = cVolume.GetVolumeImage();

	// Get image buffer, we only support the data type "byte" and "word"
	ImageBuffer *pImageBuffer = cImage.GetBuffer();
	if (pImageBuffer && (pImageBuffer->GetDataFormat() == DataByte || pImageBuffer->GetDataFormat() == DataWord)) {
		// Save the data
		const Vector3i &vSize = pImageBuffer->GetSize();
		writePVMvolume(cFile.GetUrl().GetNativePath().GetASCII(), pImageBuffer->GetData(), vSize.x, vSize.y, vSize.z, (pImageBuffer->GetDataFormat() == DataByte) ? 1 : 2);

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
VolumeLoaderPVM::VolumeLoaderPVM()
{
}

/**
*  @brief
*    Destructor
*/
VolumeLoaderPVM::~VolumeLoaderPVM()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLLoaderPVM
