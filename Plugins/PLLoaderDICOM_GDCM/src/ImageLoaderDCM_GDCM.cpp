/*********************************************************\
 *  File: ImageLoaderDCM_GDCM.cpp                        *
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
#include <PLCore/Log/Log.h>
#include <PLCore/File/File.h>
#include <PLMath/Vector3i.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4530)	// "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	PL_WARNING_DISABLE(4541)	// "warning C4541: 'dynamic_cast' used on polymorphic type 'gdcm::Value' with /GR-; unpredictable behavior may result"
	PL_WARNING_DISABLE(4512)	// "warning C4512: 'gdcm::ByteSwapFilter' : assignment operator could not be generated"
	#include <gdcm/MediaStorageAndFileFormat/gdcmImageReader.h>
PL_WARNING_POP
#include "PLLoaderDICOM_GDCM/Context_GDCM.h"
#include "PLLoaderDICOM_GDCM/ImageLoaderDCM_GDCM.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
namespace PLLoaderDICOM_GDCM {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ImageLoaderDCM_GDCM)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool ImageLoaderDCM_GDCM::Load(Image &cImage, File &cFile)
{
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

bool ImageLoaderDCM_GDCM::Save(const Image &cImage, File &cFile)
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
ImageLoaderDCM_GDCM::ImageLoaderDCM_GDCM()
{
	// Add a context reference
	Context_GDCM::AddReference();
}

/**
*  @brief
*    Destructor
*/
ImageLoaderDCM_GDCM::~ImageLoaderDCM_GDCM()
{
	// Release a context reference
	Context_GDCM::ReleaseReference();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLLoaderDICOM_GDCM
