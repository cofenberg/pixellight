/*********************************************************\
 *  File: ImageLoaderRAW.cpp                             *
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
#include "PLVolume/Loader/ImageLoaderRAW.h"


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
pl_implement_class(ImageLoaderRAW)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool ImageLoaderRAW::LoadParams(Image &cImage, File &cFile, uint8 nDataType, uint16 nWidth, uint16 nHeight, uint16 nDepth)
{
	// Create image buffer
	ImageBuffer *pImageBuffer = cImage.CreatePart()->CreateMipmap();
	pImageBuffer->CreateImage(static_cast<EDataFormat>(nDataType), ColorGrayscale, Vector3i(nWidth, nHeight, nDepth));

	// Read the data
	cFile.Read(pImageBuffer->GetData(), 1, pImageBuffer->GetDataSize());

	// Done
	return true;
}

bool ImageLoaderRAW::Save(const Image &cImage, File &cFile)
{
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
ImageLoaderRAW::ImageLoaderRAW()
{
}

/**
*  @brief
*    Destructor
*/
ImageLoaderRAW::~ImageLoaderRAW()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
