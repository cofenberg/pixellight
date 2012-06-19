/*********************************************************\
 *  File: ImageTools.h                                   *
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
