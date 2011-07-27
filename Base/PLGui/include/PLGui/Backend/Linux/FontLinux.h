/*********************************************************\
 *  File: FontLinux.h                                    *
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


#ifndef __PLGUI_FONTLINUX_H__
#define __PLGUI_FONTLINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Backend/FontImpl.h"
#include "PLGui/PLGuiLinuxIncludes.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linux font implementation
*/
class FontLinux : public FontImpl {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFont
		*    Reference to platform independent font
		*/
		PLGUI_API FontLinux(Font &cFont);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~FontLinux();

		/**
		*  @brief
		*    Get X font
		*
		*  @return
		*    Pointer to font, can be a null pointer
		*/
		PLGUI_API XFontStruct *GetXFont() const;

		/**
		*  @brief
		*    Get font height
		*
		*  @return
		*    Font height
		*/
		PLGUI_API PLCore::uint32 GetHeight() const;


	//[-------------------------------------------------------]
	//[ Public virtual FontImpl functions                     ]
	//[-------------------------------------------------------]
	public:
		virtual bool LoadFont(const PLCore::String &sFamily, PLCore::uint32 nHeight, PLCore::uint32 nWeight, EFontStyle nStyle) override;
		virtual bool LoadFont(const PLCore::String &sFilename, PLCore::uint32 nHeight) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Display		   *m_pDisplay;	/**< X Display */
		XFontStruct	   *m_pXFont;	/**< Pointer to X-Font, can be a null pointer */
		PLCore::uint32  m_nHeight;	/**< Font height */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_FONTLINUX_H__
