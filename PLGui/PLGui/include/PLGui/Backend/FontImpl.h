/*********************************************************\
 *  File: FontImpl.h                                     *
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


#ifndef __PLGUI_FONTIMPL_H__
#define __PLGUI_FONTIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Base/RefCount.h>
#include <PLGeneral/String/String.h>
#include "PLGui/PLGui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Font;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Font implementation base class
*
*  @remarks
*    This class is the base class for platform specific font implementations
*/
class FontImpl : public PLGeneral::RefCount<FontImpl> {


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
		PLGUI_API FontImpl(Font &cFont);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~FontImpl();


	//[-------------------------------------------------------]
	//[ Public virtual FontImpl functions                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Load font
		*
		*  @param[in] sFamily
		*    Font famliy name
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
		virtual bool LoadFont(const PLGeneral::String &sFamily, PLGeneral::uint32 nHeight, PLGeneral::uint32 nWeight, EFontStyle nStyle) = 0;

		/**
		*  @brief
		*    Load font
		*
		*  @param[in] sFilename
		*    Font filename
		*  @param[in] nHeight
		*    Font height
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool LoadFont(const PLGeneral::String &sFilename, PLGeneral::uint32 nHeight) = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Font *m_pFont;		/**< Pointer to the platform independent font object */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_FONTIMPL_H__
