/*********************************************************\
 *  File: ImageLoaderJPG.cpp                             *
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
#include <PLGeneral/File/StdIo.h> // Required for "jpg/jpeglib.h"
extern "C" {
	#include <jpeglib.h>
}
#include <PLGeneral/File/File.h>
#include "PLGraphics/Image/Image.h"
#include "PLGraphics/Image/ImagePart.h"
#include "PLGraphics/Image/ImageBuffer.h"
#include "PLGraphics/Image/Loader/ImageLoaderJPG.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ImageLoaderJPG)


//[-------------------------------------------------------]
//[ Ugly global stuff for reading                         ]
//[-------------------------------------------------------]
typedef struct {
	struct jpeg_source_mgr  sPublic;		/**< Public fields */
	File				   *pFile;			/**< PixelLight file object */
	JOCTET				   *pBuffer;		/**< Start of buffer */
	bool					bStartOfFile;	/**< Have we gotten any data yet? */
} JpgReadStruct;
const uint32 InputBufferSize = 4096;
// [TODO] Error handling?
//static bool jpgErrorOccured = false;

// Overrides libjpeg's stupid error/warning handlers. =P
void ExitErrorHandle (struct jpeg_common_struct *JpegInfo)
{
	// jpgErrorOccured = true;
	return;
}

void init_source(j_decompress_ptr cinfo)
{
	// Cast to JpgReadStruct
	JpgReadStruct *pJpgReadStruct = reinterpret_cast<JpgReadStruct*>(cinfo->src);

	// Initialize
	pJpgReadStruct->bStartOfFile = true;
}

boolean fill_input_buffer(j_decompress_ptr cinfo)
{
	// Cast to JpgReadStruct
	JpgReadStruct *pJpgReadStruct = reinterpret_cast<JpgReadStruct*>(cinfo->src);

	// Read bytes from file
	uint32 nReadBytes = pJpgReadStruct->pFile->Read(pJpgReadStruct->pBuffer, 1, InputBufferSize);
	if (!nReadBytes) {
		if (pJpgReadStruct->bStartOfFile) {
			// Treat empty input file as fatal error
//			jpgErrorOccured = true;
		}

		// Insert a fake EOI marker
		pJpgReadStruct->pBuffer[0] = static_cast<JOCTET>(0xFF);
		pJpgReadStruct->pBuffer[1] = static_cast<JOCTET>(JPEG_EOI);
		nReadBytes = 2;

		return false;
	}
	if (nReadBytes < InputBufferSize) {
		// Nothing to do
	}

	pJpgReadStruct->sPublic.next_input_byte = pJpgReadStruct->pBuffer;
	pJpgReadStruct->sPublic.bytes_in_buffer = nReadBytes;
	pJpgReadStruct->bStartOfFile			= false;

	return true;
}

void skip_input_data(j_decompress_ptr cinfo, long num_bytes)
{
	// Cast to JpgReadStruct
	JpgReadStruct *pJpgReadStruct = reinterpret_cast<JpgReadStruct*>(cinfo->src);

	// Skip
	if (num_bytes > 0) {
		while (num_bytes > static_cast<long>(pJpgReadStruct->sPublic.bytes_in_buffer)) {
			num_bytes -= static_cast<long>(pJpgReadStruct->sPublic.bytes_in_buffer);
			fill_input_buffer(cinfo);
		}
		pJpgReadStruct->sPublic.next_input_byte += static_cast<size_t>(num_bytes);
		pJpgReadStruct->sPublic.bytes_in_buffer -= static_cast<size_t>(num_bytes);
	}
}

void term_source(j_decompress_ptr cinfo)
{
	// Nothing to do in here
}

void jpeg_read_init(j_decompress_ptr cinfo, File *pFile)
{
	// Get to JpgReadStruct
	JpgReadStruct *pJpgReadStruct = reinterpret_cast<JpgReadStruct*>(cinfo->src);
	if (!pJpgReadStruct) {
		// First time for this JPEG object
		cinfo->src = static_cast<struct jpeg_source_mgr*>((*cinfo->mem->alloc_small)(reinterpret_cast<j_common_ptr>(cinfo), JPOOL_PERMANENT, sizeof(JpgReadStruct)));
		pJpgReadStruct = reinterpret_cast<JpgReadStruct*>(cinfo->src);
		pJpgReadStruct->pFile   = pFile;
		pJpgReadStruct->pBuffer = static_cast<JOCTET*>((*cinfo->mem->alloc_small)(reinterpret_cast<j_common_ptr>(cinfo), JPOOL_PERMANENT, InputBufferSize*sizeof(JOCTET)));
	}

	// Setup
	pJpgReadStruct->sPublic.init_source			= init_source;
	pJpgReadStruct->sPublic.fill_input_buffer	= fill_input_buffer;
	pJpgReadStruct->sPublic.skip_input_data		= skip_input_data;
	pJpgReadStruct->sPublic.resync_to_restart	= jpeg_resync_to_restart; // Use default method
	pJpgReadStruct->sPublic.term_source			= term_source;
	pJpgReadStruct->sPublic.bytes_in_buffer		= 0;					  // Forces fill_input_buffer on first read
	pJpgReadStruct->sPublic.next_input_byte		= nullptr;				  // Until buffer loaded
}


//[-------------------------------------------------------]
//[ Ugly global stuff for writing                         ]
//[-------------------------------------------------------]
typedef struct
{
	struct jpeg_destination_mgr	 sPublic;	/**< Public fields */
	File						*pFile;		/**< PixelLight file object */
	JOCTET						*pBuffer;	/**< Start of buffer */
} JpgWriteStruct;
const uint32 OutputBufferSize = 4096;

void init_destination(j_compress_ptr cinfo)
{
	// Cast to JpgWriteStruct
	JpgWriteStruct *pJpgWriteStruct = reinterpret_cast<JpgWriteStruct*>(cinfo->dest);

	// Setup
	pJpgWriteStruct->pBuffer				  = static_cast<JOCTET*>((*cinfo->mem->alloc_small)(reinterpret_cast<j_common_ptr>(cinfo), JPOOL_IMAGE, OutputBufferSize*sizeof(JOCTET)));
	pJpgWriteStruct->sPublic.next_output_byte = pJpgWriteStruct->pBuffer;
	pJpgWriteStruct->sPublic.free_in_buffer	  = OutputBufferSize;
}

boolean empty_output_buffer(j_compress_ptr cinfo)
{
	// Cast to JpgWriteStruct
	JpgWriteStruct *pJpgWriteStruct = reinterpret_cast<JpgWriteStruct*>(cinfo->dest);

	// Write
	pJpgWriteStruct->pFile->Write(pJpgWriteStruct->pBuffer, 1, OutputBufferSize);
	pJpgWriteStruct->sPublic.next_output_byte = pJpgWriteStruct->pBuffer;
	pJpgWriteStruct->sPublic.free_in_buffer   = OutputBufferSize;

	return 1;
}

void term_destination(j_compress_ptr cinfo)
{
	// Cast to JpgWriteStruct
	JpgWriteStruct *pJpgWriteStruct = reinterpret_cast<JpgWriteStruct*>(cinfo->dest);

	// Write
	pJpgWriteStruct->pFile->Write(pJpgWriteStruct->pBuffer, 1, OutputBufferSize - pJpgWriteStruct->sPublic.free_in_buffer);
}

void jpeg_write_init(j_compress_ptr cinfo, File *pFile)
{
	// Get to JpgWriteStruct
	JpgWriteStruct *pJpgWriteStruct = reinterpret_cast<JpgWriteStruct*>(cinfo->dest);
	if (!pJpgWriteStruct) {
		// First time for this JPEG object
		cinfo->dest = static_cast<struct jpeg_destination_mgr*>((*cinfo->mem->alloc_small)(reinterpret_cast<j_common_ptr>(cinfo), JPOOL_PERMANENT, sizeof(JpgWriteStruct)));
		pJpgWriteStruct = reinterpret_cast<JpgWriteStruct*>(cinfo->dest);
		pJpgWriteStruct->pFile = pFile;
	}

	// Setup
	pJpgWriteStruct->sPublic.init_destination	 = init_destination;
	pJpgWriteStruct->sPublic.empty_output_buffer = empty_output_buffer;
	pJpgWriteStruct->sPublic.term_destination	 = term_destination;
}


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool ImageLoaderJPG::Load(Image &cImage, File &cFile)
{
	return LoadParams(cImage, cFile, false, false);
}

bool ImageLoaderJPG::LoadParams(Image &cImage, File &cFile, bool bBlockSmoothing, bool bFancyUpsampling)
{
	jpeg_decompress_struct sInfo;
	jpeg_error_mgr sError;

	sInfo.err = jpeg_std_error(&sError);
	sInfo.err->error_exit = ExitErrorHandle;

	jpeg_create_decompress(&sInfo);

	// Set the user given parameters
	sInfo.do_block_smoothing  = bBlockSmoothing;
	sInfo.do_fancy_upsampling = bFancyUpsampling;

	jpeg_read_init(&sInfo, &cFile);

	jpeg_read_header(&sInfo, TRUE);
	jpeg_start_decompress(&sInfo);

	// Get the color format
	EColorFormat nColorFormat;
	switch (sInfo.num_components){
		case 1:
			nColorFormat = ColorGrayscale;
			break;

		case 3:
			nColorFormat = ColorRGB;
			break;

		case 4:
			nColorFormat = ColorRGBA;
			break;

		default:
			// Error: Unsupported color format
			return false;
	}

	// Create image buffer
	cImage.Clear();
	ImageBuffer *pImageBuffer = cImage.CreatePart()->CreateMipmap();
	pImageBuffer->CreateImage(DataByte, nColorFormat, Vector3i(sInfo.output_width, sInfo.output_height, 1));

	// Read in the data
	uint8 *pCurrentData = pImageBuffer->GetData();
	while (sInfo.output_scanline < sInfo.output_height){
		jpeg_read_scanlines(&sInfo, &pCurrentData, 1);
		pCurrentData += pImageBuffer->GetRowSize();
	}

	// Cleanup
	jpeg_finish_decompress(&sInfo);
	jpeg_destroy_decompress(&sInfo);

	// Done
	return true;
}

bool ImageLoaderJPG::Save(const Image &cImage, File &cFile)
{
	return SaveParams(cImage, cFile, 100);
}

bool ImageLoaderJPG::SaveParams(const Image &cImage, File &cFile, uint32 nQuality)
{
	// Get the image buffer
	ImageBuffer *pImageBuffer = cImage.GetBuffer();
	if (pImageBuffer && pImageBuffer->GetRowSize()) {
		// We only support 1 or 3 byte per pixel component
		if (pImageBuffer->GetBytesPerPixelComponent() == 1 || pImageBuffer->GetBytesPerPixelComponent() == 3) {
			jpeg_compress_struct sInfo;
			jpeg_error_mgr sError;

			sInfo.err = jpeg_std_error(&sError);
			sInfo.err->error_exit = ExitErrorHandle;
			jpeg_create_compress(&sInfo);

			const int nComponents = pImageBuffer->GetComponentsPerPixel();

			sInfo.in_color_space = (nComponents == 1)? JCS_GRAYSCALE : JCS_RGB;
			jpeg_set_defaults(&sInfo);

			sInfo.input_components	= nComponents;
			sInfo.num_components	= nComponents;
			sInfo.image_width		= pImageBuffer->GetSize().x;
			sInfo.image_height		= pImageBuffer->GetSize().y;
			sInfo.data_precision	= 8;
			sInfo.input_gamma		= 1.0;

			// Set the user given parameter
			jpeg_set_quality(&sInfo, nQuality, FALSE);

			jpeg_write_init(&sInfo, &cFile);
			jpeg_start_compress(&sInfo, TRUE);

			// Write the data
			uint8 *pCurrentData = pImageBuffer->GetData();
			for (int y=0; y<pImageBuffer->GetSize().y; y++) {
				jpeg_write_scanlines(&sInfo, &pCurrentData, 1);
				pCurrentData += pImageBuffer->GetRowSize();
			}

			// Cleanup
			jpeg_finish_compress(&sInfo);
			jpeg_destroy_compress(&sInfo);

			// Done
			return true;
		} else {
			// Error: Unsupported number of bytes per pixel component
		}
	} else {
		// Error: Failed to get image buffer
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
ImageLoaderJPG::ImageLoaderJPG() :
	MethodLoad(this),
	MethodLoadParams(this),
	MethodSave(this),
	MethodSaveParams(this)
{
}

/**
*  @brief
*    Destructor
*/
ImageLoaderJPG::~ImageLoaderJPG()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
