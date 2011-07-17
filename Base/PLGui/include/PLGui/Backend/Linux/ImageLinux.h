/*********************************************************\
 *  File: ImageLinux.h                                   *
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


#ifndef __PLGUI_IMAGELINUX_H__
#define __PLGUI_IMAGELINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Backend/ImageImpl.h"
#include "PLGui/PLGuiLinuxIncludes.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGraphics {
	class Color3;
	class Color4;
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
*    Linux image implementation
*/
class ImageLinux : public ImageImpl {


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
		PLGUI_API ImageLinux(Image &cImage);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~ImageLinux();

		/**
		*  @brief
		*    Get pixmap
		*
		*  @return
		*    Pixmap
		*/
		PLGUI_API Pixmap GetPixmap() const;

		/**
		*  @brief
		*    Get mask pixmap
		*
		*  @return
		*    Pixmap
		*/
		PLGUI_API Pixmap GetMaskPixmap() const;


	//[-------------------------------------------------------]
	//[ Public virtual ImageImpl functions                    ]
	//[-------------------------------------------------------]
	public:
		virtual bool Load(const PLGeneral::String &sFilename);
		virtual bool LoadWithColorKey(const PLGeneral::String &sFilename, const PLGraphics::Color3 &cColor);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Load pixmap
		*
		*  @param[in] sFilename
		*    File name
		*  @param[in] cColorkey
		*    Color key to use (pass Color4::Transparent to use no color key)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadPixmap(const PLGeneral::String &sFilename, const PLGraphics::Color4 &cColorKey);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Display			  *m_pDisplay;		/**< X Display */
		Pixmap			   m_pPixmap;		/**< X pixmap */
		Pixmap			   m_pMaskPixmap;	/**< X mask pixmap */
		PLGraphics::Image *m_pImage;		/**< Image */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_IMAGELINUX_H__
