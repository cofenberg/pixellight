/*********************************************************\
 *  File: VolumeLoaderDCM_GDCM.cpp                       *
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
#include <PLCore/Log/Log.h>
#include <PLCore/File/File.h>
#include <PLCore/File/Directory.h>
#include <PLMath/Vector3i.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLVolume/Volume.h>
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4530)	// "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	PL_WARNING_DISABLE(4541)	// "warning C4541: 'dynamic_cast' used on polymorphic type 'gdcm::Value' with /GR-; unpredictable behavior may result"
	PL_WARNING_DISABLE(4512)	// "warning C4512: 'gdcm::ByteSwapFilter' : assignment operator could not be generated"
	#include <gdcm/common/gdcmDirectory.h>
	#include <gdcm/MediaStorageAndFileFormat/gdcmScanner.h>
	#include <gdcm/MediaStorageAndFileFormat/gdcmIPPSorter.h>
	#include <gdcm/MediaStorageAndFileFormat/gdcmImageReader.h>
PL_WARNING_POP
#include "PLVolumeLoaderDICOM_GDCM/Context_GDCM.h"
#include "PLVolumeLoaderDICOM_GDCM/VolumeLoaderDCM_GDCM.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLVolume;
namespace PLVolumeLoaderDICOM_GDCM {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(VolumeLoaderDCM_GDCM)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool VolumeLoaderDCM_GDCM::Load(Volume &cVolume, File &cFile)
{
	return LoadParams(cVolume, cFile, true);
}

bool VolumeLoaderDCM_GDCM::LoadParams(Volume &cVolume, File &cFile, bool bForce8Bit)
{
	// [TODO] bForce8Bit

	// Get the image holding the volumtric data
	Image &cImage = cVolume.GetVolumeImage();

	// Load in the DICOM image
	// [TODO] Check: Is there a way to overwrite the file handling in DCMTK?
	const String sFilename = cFile.GetUrl().GetNativePath();
	gdcm::ImageReader gdcmImageReader;
	gdcmImageReader.SetFileName(sFilename.GetASCII());
	if (!gdcmImageReader.Read()) {
		// Error!
		// [TODO] Error description?
		PL_LOG(Error, "Failed to load in DICOM file \"" + sFilename + '\"')
//		PL_LOG(Error, "Failed to load in DICOM file \"" + sFilename + "\" (" + cOFCondition.text() + ')')

		// Error! Get us out of here right now!
		return false;
	}

	// Get the DICOM image
	const gdcm::Image &gdcmImage = gdcmImageReader.GetImage();

	// Get the DICOM image dimension
	const unsigned long nWidth  = gdcmImage.GetDimensions()[0];
	const unsigned long nHeight = gdcmImage.GetDimensions()[1];

	// Allocate the DICOM image buffer
	char *gdcmImageBuffer = new char[gdcmImage.GetBufferLength()];
	gdcmImage.GetBuffer(gdcmImageBuffer);

//	gdcm::PixelFormat::ScalarType gdcmPixelFormatScalarType = gdcmImage.GetPixelFormat();

	// Let's start with the easy case:
	if (gdcmImage.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::RGB) {
		if (gdcmImage.GetPixelFormat() != gdcm::PixelFormat::UINT8) {
			// [TODO] Handle this case
		} else {
			// Create image and takeover the data
			cImage = Image::CreateImageAndTakeoverData(DataByte, ColorRGB, Vector3i(nWidth, nHeight, 1), CompressionNone, reinterpret_cast<uint8*>(gdcmImageBuffer));
			gdcmImageBuffer = nullptr;
		}
	} else if (gdcmImage.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::MONOCHROME2) {
		if (gdcmImage.GetPixelFormat() == gdcm::PixelFormat::UINT8) {
			// Create image and takeover the data
			cImage = Image::CreateImageAndTakeoverData(DataByte, ColorGrayscale, Vector3i(nWidth, nHeight, 1), CompressionNone, reinterpret_cast<uint8*>(gdcmImageBuffer));
			gdcmImageBuffer = nullptr;
		} else if (gdcmImage.GetPixelFormat() == gdcm::PixelFormat::UINT16) {
			// Create image and takeover the data
			cImage = Image::CreateImageAndTakeoverData(DataWord, ColorGrayscale, Vector3i(nWidth, nHeight, 1), CompressionNone, reinterpret_cast<uint8*>(gdcmImageBuffer));
			gdcmImageBuffer = nullptr;
		} else {
			// [TODO] Handle this case
			const gdcm::PixelFormat &gdcmPixelFormat = gdcmImage.GetPixelFormat();
		//	std::cerr << "Pixel Format is: " << gdcmImage.GetPixelFormat() << std::endl;
			return false;
		}
	} else {
			// [TODO] Handle this case
//		std::cerr << "Unhandled PhotometricInterpretation: " << gimage.GetPhotometricInterpretation() << std::endl;
		return false;
	}

	// Deallocate the DICOM image buffer
	if (gdcmImageBuffer)
		delete [] gdcmImageBuffer;

	// Done
	return true;
}

bool VolumeLoaderDCM_GDCM::LoadDirectory(Volume &cVolume, Directory &cDirectory)
{
	return LoadDirectoryParams(cVolume, cDirectory, true);
}

bool VolumeLoaderDCM_GDCM::LoadDirectoryParams(Volume &cVolume, Directory &cDirectory, bool bForce8Bit)
{
	// Get the image holding the volumtric data
	Image &cImage = cVolume.GetVolumeImage();

	// Load the directory
	const String sDirectory = cDirectory.GetUrl().GetNativePath();
	gdcm::Directory gdcmDirectory;
	// [TODO] Check: Is this ASCII or UTF8?
	if (!gdcmDirectory.Load(sDirectory.GetASCII(), true)) {
//	if (!gdcmDirectory.Load(sDirectory.GetASCII(), false)) {
		// Error! Empty directory...
		return false;
	}

	// Sort the found DICOM filenames, if this fails, fallback to unsorted filenames (it's important to still see at least "anything")
	// -> This step is important: While some DICOM datasets may work correctly without sorting, other datasets may end up in an messed up volume
	const gdcm::Directory::FilenamesType *gdcmDirectoryFilenamesType = &gdcmDirectory.GetFilenames();
	float fZSpacing = 0.0f;
	gdcm::IPPSorter gdcmIPPSorter;
	gdcmIPPSorter.SetComputeZSpacing(true);
	gdcmIPPSorter.SetZSpacingTolerance(1e-3);
	if (gdcmIPPSorter.Sort(gdcmDirectory.GetFilenames())) {
		// Yeah, we not have properly sorted filenames :D
		gdcmDirectoryFilenamesType = &gdcmIPPSorter.GetFilenames();
		fZSpacing = static_cast<float>(gdcmIPPSorter.GetZSpacing());
	} else {
		// Error! Failed to sort the filenames... the resulting volume is potentially messed up...
		PL_LOG(Warning, "Failed to sort the DICOM filenames")
		Context_GDCM::FlushTraceToLog();
	}
	const unsigned int nNumOfFiles = static_cast<unsigned int>(gdcmDirectoryFilenamesType->size());

	// Load in the DICOM slices
	bool bResult = true;
	ImageBuffer *pImageBuffer = nullptr;
	char *gdcmImageBuffer = nullptr;
	unsigned long nGDCMImageGetBufferLength = 0;
	for (unsigned int i=0; i<nNumOfFiles; i++) {
		std::string sFilename = gdcmDirectoryFilenamesType->at(i);

		// Load in the DICOM image
		gdcm::ImageReader gdcmImageReader;
		gdcmImageReader.SetFileName(sFilename.c_str());
		if (!gdcmImageReader.Read()) {
			// Error!
			// [TODO] Error description?
//			PL_LOG(Error, "Failed to load in DICOM file \"" + sFilename + '\"')
	//		PL_LOG(Error, "Failed to load in DICOM file \"" + sFilename + "\" (" + cOFCondition.text() + ')')

			// Error! Get us out of here right now!
			return false;
		}

		// Get the DICOM image
		const gdcm::Image &gdcmImage = gdcmImageReader.GetImage();

		// Get the DICOM image dimension
		const unsigned long nWidth  = gdcmImage.GetDimensions()[0];
		const unsigned long nHeight = gdcmImage.GetDimensions()[1];

		// Allocate the DICOM image buffer
		if (gdcmImageBuffer) {
			// Check buffer size (had once a DICOM dataset with varying sizes... ?!)
			if (nGDCMImageGetBufferLength != gdcmImage.GetBufferLength()) {
				// Error! We don't support this!
				PL_LOG(Error, '\"' + sDirectory + "\": Failed to load the DICOM dataset due to varying sizes")
				i = nNumOfFiles;
				bResult = false;
				continue;	// Get us out of here right now!
			}
		} else {
			// Allocate the DICOM image buffer
			gdcmImageBuffer = new char[gdcmImage.GetBufferLength()];
			nGDCMImageGetBufferLength = gdcmImage.GetBufferLength();
		}

		// Spacing
		if (i == 0) {
			// Get a 3-tuples specifying the spacing of the DICIM image - only the first DICOM image controls the spacing in our volume
			const double *pfSpacing = gdcmImage.GetSpacing();

			//						  mm to cm    cm to m
			static const float Scale = (0.1f    *   0.01f);

			// Set the size of one voxel (without metric, but usually one unit is equal to one meter)
			Vector3 vSpacing = Volume::DefaultVoxelSize;
			if (pfSpacing) {
				vSpacing.x = static_cast<float>(pfSpacing[0]*Scale);
				vSpacing.y = static_cast<float>(pfSpacing[1]*Scale);
				vSpacing.z = (fZSpacing ? fZSpacing : static_cast<float>(pfSpacing[2]))*Scale;
			}
			cVolume.SetVoxelSize(vSpacing);
		}
		gdcmImage.GetBuffer(gdcmImageBuffer);

		// Let's start with the easy case:
		if (gdcmImage.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::RGB) {
			if (gdcmImage.GetPixelFormat() != gdcm::PixelFormat::UINT8) {
				// [TODO] Handle this case
			} else {
				if (!pImageBuffer) {
					pImageBuffer = cImage.CreatePart()->CreateMipmap();
					pImageBuffer->CreateImage(DataByte, ColorRGB, Vector3i(nWidth, nHeight, nNumOfFiles));
				}
				uint8 *pImageData = pImageBuffer->GetData() + pImageBuffer->GetBytesPerPixel()*nWidth*nHeight*i;
				MemoryManager::Copy(pImageData, gdcmImageBuffer, gdcmImage.GetBufferLength());
			}
		} else if (gdcmImage.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::MONOCHROME2) {
			if (gdcmImage.GetPixelFormat() == gdcm::PixelFormat::UINT8) {
				if (!pImageBuffer) {
					pImageBuffer = cImage.CreatePart()->CreateMipmap();
					pImageBuffer->CreateImage(DataByte, ColorGrayscale, Vector3i(nWidth, nHeight, nNumOfFiles));
				}
				uint8 *pImageData = pImageBuffer->GetData() + pImageBuffer->GetBytesPerPixel()*nWidth*nHeight*i;
				MemoryManager::Copy(pImageData, gdcmImageBuffer, gdcmImage.GetBufferLength());
			} else if (gdcmImage.GetPixelFormat() == gdcm::PixelFormat::UINT16) {
				if (bForce8Bit) {
					if (!pImageBuffer) {
						pImageBuffer = cImage.CreatePart()->CreateMipmap();
						pImageBuffer->CreateImage(DataByte, ColorGrayscale, Vector3i(nWidth, nHeight, nNumOfFiles));
					}
					const uint32 nNumOfLayerPixels = nWidth*nHeight;
					uint8 *pImageData = pImageBuffer->GetData() + pImageBuffer->GetBytesPerPixel()*nNumOfLayerPixels*i;
					const short *gdcmImageBufferCurrent = reinterpret_cast<short*>(gdcmImageBuffer);
					for (uint32 i=0; i<nNumOfLayerPixels; i++) {
						// The "ConvertToQImage"-example from GDCM states:
						//	"Scalar Range of gdcmData/012345.002.050.dcm is [0,192], we could simply do:"
						//	"*pubuffer++ = *buffer16;"
						// [TODO] Correct conversion
//						*pImageData++ = (*gdcmImageBufferCurrent)/256;
						//*pImageData++ = (float(*gdcmImageBufferCurrent)/256.0f)*15;
						*pImageData++ = (float(*gdcmImageBufferCurrent)/4096.0f)*255;	// 4096 -> 12 bit
						gdcmImageBufferCurrent++;
					}
				} else {
					if (!pImageBuffer) {
						pImageBuffer = cImage.CreatePart()->CreateMipmap();
						pImageBuffer->CreateImage(DataWord, ColorGrayscale, Vector3i(nWidth, nHeight, nNumOfFiles));
					}
					uint8 *pImageData = pImageBuffer->GetData() + pImageBuffer->GetBytesPerPixel()*nWidth*nHeight*i;
					MemoryManager::Copy(pImageData, gdcmImageBuffer, gdcmImage.GetBufferLength());
				}
			} else {
				// [TODO] Handle this case
				const gdcm::PixelFormat &gdcmPixelFormat = gdcmImage.GetPixelFormat();
			//	std::cerr << "Pixel Format is: " << gdcmImage.GetPixelFormat() << std::endl;
				i = nNumOfFiles;
				bResult = false;
			}
		} else {
				// [TODO] Handle this case
	//		std::cerr << "Unhandled PhotometricInterpretation: " << gimage.GetPhotometricInterpretation() << std::endl;
			i = nNumOfFiles;
			bResult = false;
		}
	}

	// Deallocate the DICOM image buffer
	if (gdcmImageBuffer)
		delete [] gdcmImageBuffer;

	// Done
	return bResult;
}

bool VolumeLoaderDCM_GDCM::Save(const Volume &cVolume, File &cFile)
{
	// Not implemented

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
VolumeLoaderDCM_GDCM::VolumeLoaderDCM_GDCM()
{
	// Add a context reference
	Context_GDCM::AddReference();
}

/**
*  @brief
*    Destructor
*/
VolumeLoaderDCM_GDCM::~VolumeLoaderDCM_GDCM()
{
	// Release a context reference
	Context_GDCM::ReleaseReference();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeLoaderDICOM_GDCM
