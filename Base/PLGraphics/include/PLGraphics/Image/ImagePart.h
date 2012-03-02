/*********************************************************\
 *  File: ImagePart.h                                    *
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


#ifndef __PLGRAPHICS_IMAGEPART_H__
#define __PLGRAPHICS_IMAGEPART_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/Array.h>
#include "PLGraphics/PLGraphics.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class ImageBuffer;
class ImageEffect;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Image part
*
*  @note
*    - An image part has usually at least one mipmap - the base map
*/
class ImagePart {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		inline ImagePart();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLGRAPHICS_API ImagePart(const ImagePart &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		inline ~ImagePart();

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
		PLGRAPHICS_API ImagePart &operator =(const ImagePart &cSource);

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
		*    Get semantics
		*
		*  @return
		*    Semantics ID
		*/
		inline PLCore::uint32 GetSemantics() const;

		/**
		*  @brief
		*    Set semantics
		*
		*  @param[in] nSemantics
		*    Semantics ID
		*/
		inline void SetSemantics(PLCore::uint32 nSemantics);

		/**
		*  @brief
		*    Check if the layer has mipmaps
		*
		*  @return
		*    'true' if the frame contains more than one mipmap
		*/
		inline bool HasMipmaps() const;

		/**
		*  @brief
		*    Get number of mipmaps
		*
		*  @return
		*    Number of mipmaps
		*/
		inline PLCore::uint32 GetNumOfMipmaps() const;

		/**
		*  @brief
		*    Get mipmap
		*
		*  @param[in] nIndex
		*    Index of mipmap
		*
		*  @return
		*    Image buffer, or a null pointer if it doesn't exist
		*/
		inline ImageBuffer *GetMipmap(PLCore::uint32 nIndex) const;

		/**
		*  @brief
		*    Get mipmaps
		*
		*  @return
		*    List of mipmaps
		*/
		inline const PLCore::Container<ImageBuffer*> &GetMipmaps() const;

		/**
		*  @brief
		*    Build mipmaps
		*
		*  @return
		*    'true' on success, else 'false'
		*/
		PLGRAPHICS_API bool BuildMipmaps();

		/**
		*  @brief
		*    Create new mipmap
		*
		*  @return
		*    Image buffer of mipmap, or a null pointer on error
		*/
		PLGRAPHICS_API ImageBuffer *CreateMipmap();

		/**
		*  @brief
		*    Delete mipmap
		*
		*  @param[in] cImageBuffer
		*    Image buffer of mipmap
		*
		*  @return
		*    'true' on success, ('cImageBuffer' is now no longer valid!) else 'false'
		*/
		PLGRAPHICS_API bool DeleteMipmap(ImageBuffer &cImageBuffer);

		/**
		*  @brief
		*    Deletes all mipmaps besides the first one (the base map)
		*/
		PLGRAPHICS_API void DeleteMipmaps();

		/**
		*  @brief
		*    Get size of image data in bytes, including all mipmaps
		*
		*  @return
		*    Size of image data in bytes
		*/
		PLGRAPHICS_API PLCore::uint32 GetDataSize() const;

		/**
		*  @brief
		*    Get size of compressed image data in bytes, including all mipmaps
		*
		*  @return
		*    Size of compressed image data in bytes
		*/
		PLGRAPHICS_API PLCore::uint32 GetCompressedDataSize() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::uint32			    m_nSemantics;	/**< Semantics ID */
		PLCore::Array<ImageBuffer*> m_lstMipmaps;	/**< Mipmaps */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGraphics/Image/ImagePart.inl"


#endif // __PLGRAPHICS_IMAGEPART_H__
