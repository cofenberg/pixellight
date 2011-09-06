/*********************************************************\
 *  File: ImageLoaderEXR.cpp                             *
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
#include <PLCore/PLCore.h>
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4244) // "'conversion' conversion from 'type1' to 'type2', possible loss of data"
	PL_WARNING_DISABLE(4530) // "C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	PL_WARNING_DISABLE(4541) // "'identifier' used on polymorphic type 'type' with /GR-; unpredictable behaviour may result"
	#include <ImfRgbaFile.h>
	#include <ImfStringAttribute.h>
	#include <ImfMatrixAttribute.h>
	#include <ImfArray.h>
	#include <iostream>
	#include <cmath>
	#include <ImfOutputFile.h>
	#include <ImfInputFile.h>
	#include <ImfChannelList.h>
	#include <ImfStringAttribute.h>
	#include <ImfMatrixAttribute.h>
	#include <ImfArray.h>
PL_WARNING_POP
#include <PLCore/File/File.h>
#include <PLCore/Log/Log.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include "PLImageLoaderEXR/ImageLoaderEXR.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace Imf;
using namespace Imath;
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
namespace PLImageLoaderEXR {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ImageLoaderEXR)


//[-------------------------------------------------------]
//[ Internal helper classes                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Input stream
*/
class EXRIStream : public Imf::IStream {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		EXRIStream(File &cFile, const char *pszFilename) :
			Imf::IStream(pszFilename),
			m_cFile(cFile)
		{
		}

		virtual bool read(char c[], int n) override
		{
			return m_cFile.Read(c, n, 1) > 0;
		}

		virtual Imf::Int64 tellg() override
		{
			return m_cFile.Tell();
		}

		virtual void seekg(Imf::Int64 pos) override
		{
			m_cFile.Seek((long)pos);
		}

		virtual void clear() override
		{
		}


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		File &m_cFile;


};

/**
*  brief
*    Output stream
*/
class EXROStream : public Imf::OStream {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		EXROStream(File &cFile, const char *pszFilename) :
			Imf::OStream(pszFilename),
			m_cFile(cFile)
		{
		}

		virtual void write(const char c[], int n) override
		{
			m_cFile.Write(c, n, 1);
		}

		virtual Imf::Int64 tellp() override
		{
			return m_cFile.Tell();
		}

		virtual void seekp(Imf::Int64 pos) override
		{
			m_cFile.Seek((long)pos);
		}


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		File &m_cFile;


};


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool ImageLoaderEXR::Load(Image &cImage, File &cFile)
{
	// [TODO] Do these functions support ZIP or HTTP? Or only local files?

	// Read
	EXRIStream str(cFile, cFile.GetUrl().GetUrl());
	InputFile file(str);

	Box2i dw          = file.header().dataWindow();
	int   nWidth      = dw.max.x - dw.min.x + 1;
	int   nHeight     = dw.max.y - dw.min.y + 1;
	int   nComponents = 3;

	// Alpha channel present?
	const ChannelList &channels = file.header().channels();
	if (channels.findChannel("A"))
		nComponents = 4;

	// Create the image and read in the RGB/RGBA components
	ImageBuffer *pImageBuffer = cImage.CreatePart()->CreateMipmap();
	pImageBuffer->CreateImage(DataFloat, nComponents ? ColorRGB : ColorRGBA, Vector3i(nWidth, nHeight, 1));

	// Construct frame buffer
	uint8 *pPixels = pImageBuffer->GetData();
	FrameBuffer frameBuffer;
	frameBuffer.insert("R",						// name
				Slice(Imf::FLOAT,				// type
					((char*)pPixels)+0,			// base
					4*nComponents,				// xStride
					4*nComponents*nWidth));		// yStride
	frameBuffer.insert("G",						// name
				Slice(Imf::FLOAT,				// type
					((char*)pPixels)+4,			// base
					4*nComponents,				// xStride
					4*nComponents*nWidth));		// yStride
	frameBuffer.insert("B",						// name
				Slice(Imf::FLOAT,				// type
					((char*)pPixels)+8,			// base
					4*nComponents,				// xStride
					4*nComponents*nWidth));		// yStride
	if (nComponents==4) {
		frameBuffer.insert("A",					// name
					Slice(Imf::FLOAT,			// type
						((char*)pPixels)+12,	// base
						4*nComponents,			// xStride
						4*nComponents*nWidth));	// yStride
	}

	file.setFrameBuffer(frameBuffer);
	file.readPixels(dw.min.y, dw.max.y);

	// Done
	return true;
}

bool ImageLoaderEXR::Save(const Image &cImage, File &cFile)
{
	// Get the image buffer
	ImageBuffer *pImageBuffer = cImage.GetBuffer();
	if (pImageBuffer) {
		// Check image type
		if (pImageBuffer->GetDataFormat() == DataFloat) {
			// Check image format mode
			if (pImageBuffer->GetColorFormat() == ColorRGB) {
				// [TODO] Do these functions support ZIP or HTTP? Or only local files?

				// Write file
				int nWidth      = pImageBuffer->GetSize().x;
				int nHeight     = pImageBuffer->GetSize().y;
				int nComponents = pImageBuffer->GetComponentsPerPixel();
				EXROStream ost(cFile, cFile.GetUrl().GetUrl());
				const float *pfPixels = (float*)pImageBuffer->GetData();

				Header header(nWidth, nHeight);
				header.channels().insert("R", Channel (HALF));
				header.channels().insert("G", Channel (HALF));
				header.channels().insert("B", Channel (HALF));
				if (nComponents == 4)
					header.channels().insert("A", Channel (HALF));

				// Convert data to half
				const uint32 nNumOfElements = nWidth*nHeight*nComponents;
				half *pData = new half[nNumOfElements];
				for (uint32 i=0; i<nNumOfElements; i++)
					pData[i] = pfPixels[i];

				// And save it
				OutputFile file(ost, header);
				FrameBuffer frameBuffer;

				frameBuffer.insert("R",						// name
							Slice(HALF,						// type
							   ((char*)pData)+0,			// base
							   2*nComponents,				// xStride
							   2*nComponents*nWidth));		// yStride
				frameBuffer.insert("G",						// name
							Slice(HALF,						// type
							   ((char*)pData)+2,			// base
							   2*nComponents,				// xStride
							   2*nComponents*nWidth));		// yStride
				frameBuffer.insert("B",						// name
							Slice(HALF,						// type
							   ((char*)pData)+4,			// base
							   2*nComponents,				// xStride
							   2*nComponents*nWidth));		// yStride
				if (nComponents == 4) {
					frameBuffer.insert("A",					// name
								Slice(HALF,					// type
								   ((char*)pData)+6,		// base
								   2*nComponents,			// xStride
								   2*nComponents*nWidth));	// yStride
				}

				file.setFrameBuffer(frameBuffer);
				file.writePixels(nHeight);
				delete [] pData;

				// Done
				return true;
			} else {
				// Error!
				PL_LOG(Error, "The image format mode must be RGB!")
			}
		} else {
			// Error!
			PL_LOG(Error, "The image type must be float!")
		}
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
ImageLoaderEXR::ImageLoaderEXR()
{
}

/**
*  @brief
*    Destructor
*/
ImageLoaderEXR::~ImageLoaderEXR()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLImageLoaderEXR
