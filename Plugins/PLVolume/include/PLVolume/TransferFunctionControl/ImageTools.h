/*********************************************************\
 *  File: ImageTools.h                                   *
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


#ifndef __PLVOLUME_IMAGETOOLS_H__
#define __PLVOLUME_IMAGETOOLS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLVolume/PLVolume.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGraphics {
	class Color3;
	class ImageBuffer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolume {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Image tools
*/
class ImageTools {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cImageBuffer
		*    Image buffer to work on, must stay valid and unchanged as long as this image tool instance exists
		*/
		PLVOLUME_API ImageTools(PLGraphics::ImageBuffer &cImageBuffer);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLVOLUME_API ImageTools(const ImageTools &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUME_API ~ImageTools();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		PLVOLUME_API ImageTools &operator =(const ImageTools &cSource);

		/**
		*  @brief
		*    Draws a Bresenham line
		*
		*  @param[in] cColor
		*    RGB color to use
		*  @param[in] nXStart
		*    X component of the start coordinate
		*  @param[in] nYStart
		*    Y component of the start coordinate
		*  @param[in] nXEnd
		*    X component of the end coordinate
		*  @param[in] nYEnd
		*    Y component of the end coordinate
		*/
		PLVOLUME_API void DrawBresenhamLine(const PLGraphics::Color3 &cColor, int nXStart, int nYStart, int nXEnd, int nYEnd);

		/**
		*  @brief
		*    Draws a Bresenham circle (aka "midpoint circle algorithm")
		*
		*  @param[in] cColor
		*    RGB color to use
		*  @param[in] nX
		*    X component of the coordinate
		*  @param[in] nY
		*    Y component of the coordinate
		*  @param[in] nRadius
		*    Radius of the circle
		*/
		PLVOLUME_API void DrawBresenhamCircle(const PLGraphics::Color3 &cColor, int nX, int nY, int nRadius);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Draws a pixel using the current settings
		*
		*  @param[in] nX
		*    X coordinate
		*  @param[in] nY
		*    Y coordinate
		*/
		PLVOLUME_API void DrawPixel(int nX, int nY) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGraphics::ImageBuffer *m_pImageBuffer;	/**< Image buffer to work on, always valid! */
		// Cached
		int						 m_nWidth;			/**< Image width from "m_pImageBuffer" */
		int						 m_nHeight;			/**< Image height from "m_pImageBuffer" */
		PLCore::uint8			*m_pImageData;		/**< Image data from "m_pImageBuffer" */
		PLCore::uint32			 m_nBytesPerPixel;	/**< Bytes per pixel from "m_pImageBuffer" */
		PLCore::uint8			 m_nRed;			/**< Red component of the currently used color */
		PLCore::uint8			 m_nGreen;			/**< Green component of the currently used color */
		PLCore::uint8			 m_nBlue;			/**< Blue component of the currently used color */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume


#endif // __PLVOLUME_IMAGETOOLS_H__
