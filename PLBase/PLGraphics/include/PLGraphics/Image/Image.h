/*********************************************************\
 *  File: Image.h                                        *
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


#ifndef __PLGRAPHICS_IMAGE_H__
#define __PLGRAPHICS_IMAGE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/Array.h>
#include <PLGeneral/Container/HashMap.h>
#include <PLCore/Tools/Loadable.h>
#include "PLGraphics/PLGraphics.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class Vector3i;
}
namespace PLGraphics {
	class ImagePart;
	class ImageBuffer;
	class ImageEffect;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Image class
*
*  @remarks
*  @verbatim
*    Usage example:
*
*    // Allocate image
*    Image cImage = Image::CreateImage(DataByte, ColorRGB, Vector3i(64, 32, 1));
*    ImageBuffer *pImageBuffer = cImage.GetBuffer();
*
*    // Fill image
*    uint8 *pData = pImageBuffer->GetData();
*    for (int i=0; i<pImageBuffer->GetSize().x*pImageBuffer->GetSize().y; i++, pData++)
*        *pData = static_cast<uint8>(Math::GetRand() % 255);
*  @endverbatim
*/
class Image : public PLCore::Loadable {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Create image
		*
		*  @param[in] nDataFormat
		*    Desired data format
		*  @param[in] nColorFormat
		*    Desired color format
		*  @param[in] vSize
		*    Image size
		*  @param[in] nCompression
		*    Compression type
		*  @param[in] pnData
		*    If not a null pointer, data to copy into the created image, must have enough bytes to fill the whole image!
		*
		*  @remarks
		*    Please note that a call to CreateImage() will not immediatly create the image buffer itself.
		*    The image buffer is created on the first call to ImageBuffer::GetData() or ImageBuffer::GetCompressedData() respectively.
		*
		*    Usage example: Write down the RGB byte image data given by "pnMyImageData" into a 64x32 tga image:
		*  @verbatim
		*    Image::CreateImage(DataByte, ColorRGB, Vector3i(64, 32, 1), CompressionNone, pnMyImageData).Save("MyImage.tga");
		*  @endverbatim
		*
		*    This is only an ease of use method doing nothing more than:
		*  @verbatim
		*    Image cImage;
		*    ImageBuffer *pImageBuffer = cImage.CreatePart()->CreateMipmap();
		*    pImageBuffer->CreateImage(nDataFormat, nColorFormat, vSize, CompressionNone);
		*    if (pnData && pImageBuffer->GetData())
		*        PLGeneral::MemoryManager::Copy(pImageBuffer->GetData(), pnData, pImageBuffer->GetDataSize());
		*  @endverbatim
		*/
		PLGRAPHICS_API static Image CreateImage(EDataFormat nDataFormat, EColorFormat nColorFormat, const PLMath::Vector3i &vSize, ECompression nCompression = CompressionNone, const PLGeneral::uint8 *pnData = nullptr);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGRAPHICS_API Image();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLGRAPHICS_API Image(const Image &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLGRAPHICS_API virtual ~Image();

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this object
		*/
		PLGRAPHICS_API Image &operator =(const Image &cSource);

		/**
		*  @brief
		*    Clear data
		*/
		PLGRAPHICS_API void Clear();

		/**
		*  @brief
		*    Apply image effect
		*
		*  @param[in] cEffect
		*    Image effect
		*/
		PLGRAPHICS_API void ApplyEffect(const ImageEffect &cEffect);

		/**
		*  @brief
		*    Check image for possible problems
		*
		*  @return
		*    Error code describing any problem found, 'CheckOk' if everything is fine
		*/
		PLGRAPHICS_API ECheckConsistency CheckConsistency() const;

		/**
		*  @brief
		*    Check if this image is a multi-part image (e.g. a CubeMap)
		*
		*  @return
		*    'true' if the image contains of more than one image part
		*/
		PLGRAPHICS_API bool IsMultiPart() const;

		/**
		*  @brief
		*    Get number of image parts
		*
		*  @return
		*    Number of image parts
		*/
		PLGRAPHICS_API PLGeneral::uint32 GetNumOfParts() const;

		/**
		*  @brief
		*    Get image part
		*
		*  @param[in] nIndex
		*    Index of image part
		*
		*  @return
		*    Image part, or a null pointer if it doesn't exist
		*/
		PLGRAPHICS_API ImagePart *GetPart(PLGeneral::uint32 nIndex) const;

		/**
		*  @brief
		*    Get image part by semantics
		*
		*  @param[in] nSemantics
		*    ID of image part
		*
		*  @return
		*    Image part, or a null pointer if it doesn't exist
		*/
		PLGRAPHICS_API ImagePart *GetPartBySemantics(PLGeneral::uint32 nSemantics) const;

		/**
		*  @brief
		*    Get image parts
		*
		*  @return
		*    List of image parts
		*/
		PLGRAPHICS_API const PLGeneral::Container<ImagePart*> &GetParts() const;

		/**
		*  @brief
		*    Create a new image part
		*
		*  @param[in] nSemantics
		*    ID of image part
		*
		*  @return
		*    Image part, or a null pointer on error
		*
		*  @remarks
		*    Chose a semantics ID that describes the role of the new image part (@see EImagePart).
		*    Please note that the semantics IDs has to be unique, so trying to create a new image part with an already
		*    used ID will cause an error.
		*/
		PLGRAPHICS_API ImagePart *CreatePart(PLGeneral::uint32 nSemantics = ImagePartStatic);

		/**
		*  @brief
		*    Delete image part
		*
		*  @param[in] cPart
		*    Image part
		*
		*  @return
		*    'true' on success, ('cPart' is now no longer valid!) else 'false'
		*/
		PLGRAPHICS_API bool DeletePart(ImagePart &cPart);

		/**
		*  @brief
		*    Get image buffer
		*
		*  @param[in] nPart
		*    Index of image part
		*  @param[in] nMipmap
		*    Index of mipmap
		*
		*  @return
		*    Pointer to image buffer, a null pointer if the specified image buffer does not exist
		*
		*  @remarks
		*    If GetBuffer() is called with default parameters, it will return the image buffer
		*    of the first subimage and first mipmap. So, for most images that contain of only one
		*    image part, it is sufficent to just call GetBuffer() in order to get the image buffer.
		*/
		PLGRAPHICS_API ImageBuffer *GetBuffer(PLGeneral::uint32 nPart = 0, PLGeneral::uint32 nMipmap = 0) const;

		/**
		*  @brief
		*    Create a test image
		*
		*  @param[in] nTestImage
		*    ID of test image
		*/
		PLGRAPHICS_API void CreateTestImage(ETestImage nTestImage = TestImage2DSimple);


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Loadable functions             ]
	//[-------------------------------------------------------]
	public:
		PLGRAPHICS_API virtual PLGeneral::String GetLoadableTypeName() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::Array<ImagePart*>					  m_lstParts;	/**< Image parts */
		PLGeneral::HashMap<PLGeneral::uint32, ImagePart*> m_mapParts;	/**< Hash map: ID -> ImagePart */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics


#endif // __PLGRAPHICS_IMAGE_H__
