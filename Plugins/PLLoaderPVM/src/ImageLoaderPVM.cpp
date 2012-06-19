/*********************************************************\
 *  File: ImageLoaderPVM.cpp                             *
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
#include <PLGraphics/Image/ImageBuffer.h>
#include "PLLoaderPVM/PVM_GPL_License/ddsbase.h"	// Lookout! GPL code!
#include "PLLoaderPVM/ImageLoaderPVM.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
namespace PLLoaderPVM {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ImageLoaderPVM)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool ImageLoaderPVM::Load(Image &cImage, File &cFile)
{
	return LoadParams(cImage, cFile, true);
}

bool ImageLoaderPVM::LoadParams(Image &cImage, File &cFile, bool bForce8Bit)
{
	// Read the PVM volume
	unsigned int nWidth = 0, nHeight = 0, nDepth = 0, nComponents = 0;
	unsigned char *pszPVMvolume = readPVMvolume(cFile.GetUrl().GetNativePath().GetASCII(), &nWidth, &nHeight, &nDepth, &nComponents);
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

		// Done
		return true;
	}

	// Error!
	return false;
}

bool ImageLoaderPVM::Save(const Image &cImage, File &cFile)
{
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
ImageLoaderPVM::ImageLoaderPVM()
{
}

/**
*  @brief
*    Destructor
*/
ImageLoaderPVM::~ImageLoaderPVM()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLLoaderPVM
