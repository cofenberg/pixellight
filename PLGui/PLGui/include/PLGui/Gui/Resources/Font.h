/*********************************************************\
 *  File: Font.h                                         *
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


#ifndef __PLGUI_FONT_H__
#define __PLGUI_FONT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include "PLGui/PLGui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Gui;
class FontInfo;
class FontImpl;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Font class
*/
class Font {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cGui
		*    Owner GUI
		*/
		PLGUI_API Font(Gui &cGui);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cGui
		*    Owner GUI
		*  @param[in] sFamily
		*    Font famliy name
		*  @param[in] nHeight
		*    Font height
		*  @param[in] nWeight
		*    Font weight (@see EFontWeight)
		*  @param[in] nStyle
		*    Font style
		*/
		PLGUI_API Font(Gui &cGui, const PLGeneral::String &sFamily, PLGeneral::uint32 nHeight = 0, EFontWeight nWeight = WeightNormal, EFontStyle nStyle = StyleNormal);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cGui
		*    Owner GUI
		*  @param[in] cFontInfo
		*    Font information
		*/
		PLGUI_API Font(Gui &cGui, const FontInfo &cFontInfo);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cFont
		*    Font that is copied
		*/
		PLGUI_API Font(const Font &cFont);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API ~Font();

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] cFont
		*    Font that is copied
		*/
		PLGUI_API Font &operator =(const Font &cFont);

		/**
		*  @brief
		*    Get owner GUI
		*
		*  @return
		*    Pointer to GUI object (never NULL)
		*/
		PLGUI_API Gui *GetGui() const;

		/**
		*  @brief
		*    Get implementation
		*
		*  @return
		*    Pointer to platform specific implementation
		*/
		PLGUI_API FontImpl *GetImpl() const;

		/**
		*  @brief
		*    Load font
		*
		*  @param[in] sFamily
		*    Font family name
		*  @param[in] nHeight
		*    Font height
		*  @param[in] nWeight
		*    Font weight (@see EFontWeight)
		*  @param[in] nStyle
		*    Font style
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLGUI_API bool Load(const PLGeneral::String &sFamily, PLGeneral::uint32 nHeight = 0, EFontWeight nWeight = WeightNormal, EFontStyle nStyle = StyleNormal);

		/**
		*  @brief
		*    Load font from file
		*
		*  @param[in] sFilename
		*    Font filename
		*  @param[in] nHeight
		*    Font height
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLGUI_API bool LoadFromFile(const PLGeneral::String &sFilename, PLGeneral::uint32 nHeight = 0);

		/**
		*  @brief
		*    Get font information
		*
		*  @return
		*    Font info
		*/
		PLGUI_API FontInfo GetFontInfo() const;

		/**
		*  @brief
		*    Get font file name
		*
		*  @return
		*    File name
		*
		*  @remarks
		*    Will only return a file name if the font has been created using the according constructor
		*/
		PLGUI_API PLGeneral::String GetFilename() const;

		/**
		*  @brief
		*    Get font family
		*
		*  @return
		*    Font family name
		*/
		PLGUI_API PLGeneral::String GetFamily() const;

		/**
		*  @brief
		*    Set font family
		*
		*  @param[in] sFamily
		*    Font family name
		*/
		PLGUI_API void SetFamily(const PLGeneral::String &sFamily);

		/**
		*  @brief
		*    Get font height
		*
		*  @return
		*    Font height
		*/
		PLGUI_API PLGeneral::uint32 GetHeight() const;

		/**
		*  @brief
		*    Set font height
		*
		*  @param[in] nHeight
		*    Font height
		*/
		PLGUI_API void SetHeight(PLGeneral::uint32 nHeight);

		/**
		*  @brief
		*    Get font weight
		*
		*  @return
		*    Font weight
		*/
		PLGUI_API EFontWeight GetWeight() const;

		/**
		*  @brief
		*    Set font weight
		*
		*  @param[in] nWeight
		*    Font weight (@see EFontWeight)
		*/
		PLGUI_API void SetWeight(EFontWeight nWeight);

		/**
		*  @brief
		*    Get font style
		*
		*  @return
		*    Font style
		*/
		PLGUI_API EFontStyle GetStyle() const;

		/**
		*  @brief
		*    Set font style
		*
		*  @param[in] nStyle
		*    Font style
		*/
		PLGUI_API void SetStyle(EFontStyle nStyle);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Gui				  *m_pGui;		/**< Pointer to GUI */
		FontImpl		  *m_pFontImpl;	/**< Font implementation */
		PLGeneral::String  m_sFamily;	/**< Font family */
		PLGeneral::uint32  m_nHeight;	/**< Font height */
		EFontWeight		   m_nWeight;	/**< Font weight */
		EFontStyle		   m_nStyle;	/**< Font style (normal, italics, ...) */
		PLGeneral::String  m_sFilename;	/**< Filename for directly loaded fonts */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_FONT_H__
