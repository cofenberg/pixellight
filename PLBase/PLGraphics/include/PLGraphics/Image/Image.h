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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class ImagePart;
class ImageBuffer;
class ImageEffect;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Image class
*/
class Image : public PLCore::Loadable {


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
		*    Image part, or NULL if it doesn't exist
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
		*    Image part, or NULL if it doesn't exist
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
		*    Image part, or NULL on error
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
		*    Pointer to image buffer, NULL if the specified image buffer does not exist
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
