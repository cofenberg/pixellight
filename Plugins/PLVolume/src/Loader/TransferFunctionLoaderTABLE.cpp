/*********************************************************\
 *  File: TransferFunctionLoaderTABLE.cpp                *
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
