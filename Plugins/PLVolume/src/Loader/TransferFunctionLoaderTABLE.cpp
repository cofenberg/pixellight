/*********************************************************\
 *  File: TransferFunctionLoaderTABLE.cpp                *
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
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include "PLVolume/TransferFunction.h"
#include "PLVolume/Loader/TransferFunctionLoaderTABLE.h"


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
pl_implement_class(TransferFunctionLoaderTABLE)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool TransferFunctionLoaderTABLE::Load(TransferFunction &cTransferFunction, File &cFile)
{
	// Get the image holding the transfer function
	Image &cImage = cTransferFunction.GetImage();

	// A "table"-file (simple ASCII) looks like this
	/*
		1 1 1 1
		baseOpacity: 0.698039
		NoTags
		0 0 0 0
		. . . .
		. . . .
		. . . .
	*/

	// Use the tokenizer in order to gather all required informaton, ignore the rest
	// Startup the tokenizer
	Tokenizer cTokenizer;
	cTokenizer.Start(cFile.GetContentAsString());

	// Ignore the first line ("1 1 1 1")
	cTokenizer.GetNextToken();
	cTokenizer.GetNextToken();
	cTokenizer.GetNextToken();
	cTokenizer.GetNextToken();

	// Ignore base opacity ("baseOpacity: 0.698039")
	cTokenizer.GetNextToken();
	cTokenizer.GetNextToken();

	// Ignore tags to keep this loader simple ("NoTags")
	cTokenizer.GetNextToken();

	// Create image buffer
	ImageBuffer *pImageBuffer = cImage.CreatePart()->CreateMipmap();
	pImageBuffer->CreateImage(DataByte, ColorRGBA, Vector3i(256, 1, 1));

	// Read in the palette
	uint8 *pImageData = pImageBuffer->GetData();
	for (uint32 i=0; i<256; i++) {
		// Read RGBA entry
		*pImageData = cTokenizer.GetNextToken().GetUInt8();
		pImageData++;
		*pImageData = cTokenizer.GetNextToken().GetUInt8();
		pImageData++;
		*pImageData = cTokenizer.GetNextToken().GetUInt8();
		pImageData++;
		*pImageData = cTokenizer.GetNextToken().GetUInt8();
		pImageData++;
	}

	// Done
	return true;
}

bool TransferFunctionLoaderTABLE::Save(const TransferFunction &cTransferFunction, File &cFile)
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
TransferFunctionLoaderTABLE::TransferFunctionLoaderTABLE()
{
}

/**
*  @brief
*    Destructor
*/
TransferFunctionLoaderTABLE::~TransferFunctionLoaderTABLE()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
