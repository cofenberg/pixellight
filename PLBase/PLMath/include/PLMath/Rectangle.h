/*********************************************************\
 *  File: Rectangle.h                                    *
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


#ifndef __PLMATH_RECTANGLE_H__
#define __PLMATH_RECTANGLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLMath/Vector2.h"
#include "PLMath/Vector4.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Rectangle (2D axis aligned bounding box) class
*/
class Rectangle {


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		Vector2 vMin;	/**< Minimum position */
		Vector2 vMax;	/**< Maximum position */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor setting all minimum and maximum components to 0
		*/
		inline Rectangle();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		inline Rectangle(const Rectangle &cSource);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] vMin
		*    Minimum position
		*  @param[in] vMax
		*    Maximum position
		*/
		inline Rectangle(const Vector2 &vMin, const Vector2 &vMax);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] fMinX
		*    X component of the minimum position
		*  @param[in] fMinY
		*    Y component of the minimum position
		*  @param[in] fMaxX
		*    X component of the maximum position
		*  @param[in] fMaxY
		*    Y component of the maximum position
		*/
		inline Rectangle(float fMinX, float fMinY, float fMaxX, float fMaxY);

		/**
		*  @brief
		*    Destructor
		*/
		inline ~Rectangle();

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
		inline Rectangle &operator =(const Rectangle &cSource);

		/**
		*  @brief
		*    Returns the center of the rectangle
		*
		*  @return
		*    Center of the rectangle ((vMax+vMin)/2)
		*/
		inline Vector2 GetCenter() const;

		/**
		*  @brief
		*    Returns the x position
		*
		*  @return
		*    X position
		*/
		inline float GetX() const;

		/**
		*  @brief
		*    Returns the y position
		*
		*  @return
		*    Y position
		*/
		inline float GetY() const;

		/**
		*  @brief
		*    Returns the width
		*
		*  @return
		*    Width
		*/
		inline float GetWidth() const;

		/**
		*  @brief
		*    Returns the height
		*
		*  @return
		*    Height
		*/
		inline float GetHeight() const;

		/**
		*  @brief
		*    Calculates the surface of the rectangle
		*
		*  @return
		*    Surface of the rectangle
		*/
		inline float CalculateSurface() const;

		/**
		*  @brief
		*    Clips this rectangle with another one
		*
		*  @param[in] cEnclosed
		*    Rectangle to clip this rectangle with
		*/
		inline void ClipByRectangle(const Rectangle &cEnclosed);

		/**
		*  @brief
		*    Appends a vertex to the rectangle
		*
		*  @param[in] vV
		*    Vertex to append
		*/
		inline void AppendToRectangle(const Vector2 &vV);

		/**
		*  @brief
		*    Combines two rectangles
		*
		*  @param[in] cRectangle
		*    Rectangle to combine with this rectangle
		*/
		inline void CombineRectangles(const Rectangle &cRectangle);

		/**
		*  @brief
		*    Calculates the screen-space bounding rectangle of the given array of points
		*
		*  @param[in] lstPoints
		*    Array of points
		*  @param[in] bZCull
		*    Determines whether or not the function should also return 'false' if the rectangle
		*    lies outside the depth range
		*  @param[in] mMVP
		*    Concatenated modelview/projection matrix
		*  @param[in] nX
		*    X screen position
		*  @param[in] nY
		*    Y screen position
		*  @param[in] nWidth
		*    Screen width
		*  @param[in] nHeight
		*    Screen height
		*
		*  @remarks
		*    If all went fine, this rectangle will receive the screen-space bounding rectangle of the given array of points.
		*
		*  @return
		*    'false' if the rectangle is entirely off-screen, else 'true'
		*/
		PLMATH_API bool ScreenRectangle(const PLGeneral::Array<Vector3> &lstPoints, bool bZCull, const Matrix4x4 &mMVP,
										PLGeneral::uint32 nX, PLGeneral::uint32 nY, PLGeneral::uint32 nWidth, PLGeneral::uint32 nHeight);

		/**
		*  @brief
		*    Calculates the screen-space bounding rectangle of the given array of points
		*
		*  @param[in] lstPoints
		*    Array of points
		*  @param[in] bZCull
		*    Determines whether or not the function should also return 'false' if the rectangle
		*    lies outside the depth range
		*  @param[in] mMVP
		*    Concatenated modelview/projection matrix
		*  @param[in] nX
		*    X screen position
		*  @param[in] nY
		*    Y screen position
		*  @param[in] nWidth
		*    Screen width
		*  @param[in] nHeight
		*    Screen height
		*
		*  @remarks
		*    If all went fine, this rectangle will receive the screen-space bounding rectangle of the given array of points.
		*
		*  @return
		*    'false' if the rectangle is entirely off-screen, else 'true'
		*/
		PLMATH_API bool ScreenRectangle(const PLGeneral::Array<Vector4> &lstPoints, bool bZCull, const Matrix4x4 &mMVP,
										PLGeneral::uint32 nX, PLGeneral::uint32 nY, PLGeneral::uint32 nWidth, PLGeneral::uint32 nHeight);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLMath/Rectangle.inl"


#endif // __PLMATH_RECTANGLE_H__
