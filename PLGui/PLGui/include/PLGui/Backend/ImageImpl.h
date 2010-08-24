/*********************************************************\
 *  File: ImageImpl.h                                    *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLGUI_IMAGEIMPL_H__
#define __PLGUI_IMAGEIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Base/RefCount.h>
#include <PLGeneral/String/String.h>
#include <PLMath/Vector2i.h>
#include "PLGui/PLGui.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGraphics {
	class Color3;
};
namespace PLGui {
	class Image;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Image implementation base class
*
*  @remarks
*    This class is the base class for platform specific image implementations
*/
class ImageImpl : public PLGeneral::RefCount<ImageImpl> {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cImage
		*    Reference to platform independent image
		*/
		PLGUI_API ImageImpl(Image &cImage);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~ImageImpl();

		/**
		*  @brief
		*    Get image filename
		*
		*  @return
		*    Filename of image
		*/
		PLGUI_API PLGeneral::String GetFilename() const;

		/**
		*  @brief
		*    Get image size
		*
		*  @return
		*    Size of image
		*/
		PLGUI_API PLMath::Vector2i GetSize() const;

		/**
		*  @brief
		*    Get color depth
		*
		*  @return
		*    Color depth
		*/
		PLGUI_API PLGeneral::uint32 GetColorDepth() const;


	//[-------------------------------------------------------]
	//[ Public virtual ImageImpl function                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Load image
		*
		*  @param[in] sFilename
		*    Name of image file
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Load(const PLGeneral::String &sFilename) = 0;

		/**
		*  @brief
		*    Load image and apply a color key
		*
		*  @param[in] sFilename
		*    Name of image file
		*  @param[in] cColor
		*    Color that will be treated as transparent
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool LoadWithColorKey(const PLGeneral::String &sFilename, const PLGraphics::Color3 &cColor) = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Image			  *m_pImage;		/**< Pointer to the platform independent image object */
		PLGeneral::String  m_sFilename;		/**< Image name */
		PLMath::Vector2i   m_vSize;			/**< Image size */
		PLGeneral::uint32  m_nColorDepth;	/**< Color depth */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_IMAGEIMPL_H__
