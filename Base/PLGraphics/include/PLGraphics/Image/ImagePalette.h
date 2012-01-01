/*********************************************************\
 *  File: ImagePalette.h                                 *
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


#ifndef __PLGRAPHICS_IMAGEPALETTE_H__
#define __PLGRAPHICS_IMAGEPALETTE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/HashMap.h>
#include "PLGraphics/Color/Color3.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Color palette (also known as "color index")
*/
class ImagePalette {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		inline ImagePalette();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLGRAPHICS_API ImagePalette(const ImagePalette &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		inline ~ImagePalette();

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
		PLGRAPHICS_API ImagePalette &operator =(const ImagePalette &cSource);

		/**
		*  @brief
		*    Clear data
		*/
		inline void Clear();

		/**
		*  @brief
		*    Create palette
		*
		*  @param[in] nColors
		*    Number of colors
		*/
		PLGRAPHICS_API void Create(PLCore::uint32 nColors);

		/**
		*  @brief
		*    Get number of colors
		*
		*  @return
		*    Number of colors
		*/
		inline PLCore::uint32 GetNumOfColors() const;

		/**
		*  @brief
		*    Get color
		*
		*  @param[in] nIndex
		*    Index of color
		*
		*  @return
		*    Color, if index is invalid, Color3::Null (-1 -1 -1) is returned
		*/
		inline Color3 GetColor(PLCore::uint32 nIndex) const;

		/**
		*  @brief
		*    Get index of color
		*
		*  @param[in] cColor
		*    Color
		*
		*  @return
		*    Index of that color, or -1 if color is not found
		*
		*  @remarks
		*    When this function is called for the first time, a hash-list of color->index is created to speed
		*    up any subsequent call to this function
		*/
		PLGRAPHICS_API int GetColorIndex(const Color3 &cColor) const;

		/**
		*  @brief
		*    Set color
		*
		*  @param[in] nIndex
		*    Index of color
		*  @param[in] cColor
		*    Color
		*
		*  @remarks
		*    If nIndex is greater than the palette size, it is automatically extended
		*/
		PLGRAPHICS_API void SetColor(PLCore::uint32 nIndex, const Color3 &cColor);

		/**
		*  @brief
		*    Add color
		*
		*  @param[in] cColor
		*    Color
		*
		*  @return
		*    Index of new color
		*/
		inline PLCore::uint32 AddColor(const Color3 &cColor);

		/**
		*  @brief
		*    Rebuild color index
		*
		*  @remarks
		*    Use this function to invalidate the color index hash map (see GetColorIndex).
		*    This only needs to be done if you changed the image data by yourself, e.g.
		*    by calling GetData() and manipulation the palette directly. If you use
		*    SetColor() or AddColor() instead, this will be done for you automatically.
		*/
		inline void RebuildColorIndex();

		/**
		*  @brief
		*    Get color palette data
		*
		*  @return
		*    Pointer to color palette, a null pointer on error
		*
		*  @remarks
		*    If you use this function to change the palette data by yourself, be sure to call
		*    RebuildColorIndex() to invalidate the index->color hash map!
		*/
		inline PLCore::uint8 *GetData() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Resize palette
		*
		*  @param[in] nColors
		*    Number of colors
		*/
		void Resize(PLCore::uint32 nColors);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::uint8								 *m_pData;		/**< Palette data, can be a null pointer */
		PLCore::uint32								  m_nSize;		/**< Actual size of color array (Number of colors, not bytes!) */
		PLCore::uint32								  m_nColors;	/**< Number of colors (<= m_nSize) */
		mutable PLCore::HashMap<PLCore::uint32, int>  m_mapColors;	/**< Hash map: Color -> Index */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGraphics/Image/ImagePalette.inl"


#endif // __PLGRAPHICS_IMAGEPALETTE_H__
