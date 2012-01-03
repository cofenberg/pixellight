/*********************************************************\
 *  File: FontGlyph.h                                    *
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


#ifndef __PLRENDERER_FONTGLYPH_H__
#define __PLRENDERER_FONTGLYPH_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
#include <PLMath/Vector2i.h>
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract renderer font glyph
*/
class FontGlyph {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~FontGlyph();

		/**
		*  @brief
		*    Returns the size (in pixel) of the glyph
		*
		*  @return
		*    The size (in pixel) of the glyph
		*/
		inline const PLMath::Vector2i &GetSize() const;

		/**
		*  @brief
		*    Returns the distance (in pixel) from the current pen position to the glyph bitmap
		*
		*  @return
		*    The distance (in pixel) from the current pen position to the glyph bitmap
		*/
		inline const PLMath::Vector2 &GetCorner() const;

		/**
		*  @brief
		*    Returns the object space pen advance
		*
		*  @return
		*    The object space pen advance
		*/
		inline const PLMath::Vector2 &GetPenAdvance() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLRENDERER_API FontGlyph();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLMath::Vector2i m_nSize;		/**< Size (in pixel) of the glyph */
		PLMath::Vector2  m_vCorner;		/**< Distance (in pixel) from the current pen position to the glyph bitmap */
		PLMath::Vector2  m_vPenAdvance;	/**< Object space pen advance */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		FontGlyph(const FontGlyph &cSource);

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
		FontGlyph &operator =(const FontGlyph &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLRenderer/Renderer/FontGlyph.inl"


#endif // __PLRENDERER_FONTGLYPH_H__
