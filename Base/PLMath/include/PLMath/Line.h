/*********************************************************\
 *  File: Line.h                                         *
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


#ifndef __PLMATH_LINE_H__
#define __PLMATH_LINE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLMath/Vector3.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Line class (finite length)
*/
class Line {


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		Vector3 vStart;	/**< Line start point */
		Vector3 vEnd;	/**< Line end point */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor setting all start- and end-position components to 0
		*/
		inline Line();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		inline Line(const Line &cSource);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] vStartPoint
		*    Start point
		*  @param[in] vEndPoint
		*    End point
		*/
		inline Line(const Vector3 &vStartPoint, const Vector3 &vEndPoint);

		/**
		*  @brief
		*    Destructor
		*/
		inline ~Line();

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
		inline Line &operator =(const Line &cSource);

		/**
		*  @brief
		*    Sets the start and end position of the line
		*
		*  @param[in] vStart
		*    Line start position
		*  @param[in] vEnd
		*    Line end position
		*/
		inline void Set(const Vector3 &vStart, const Vector3 &vEnd);

		//[-------------------------------------------------------]
		//[ Transformation                                        ]
		//[-------------------------------------------------------]
		PLMATH_API Line  operator *(const Matrix3x3 &mRot) const;
		PLMATH_API Line  operator *(const Matrix3x4 &mTrans) const;
		PLMATH_API Line  operator *(const Matrix4x4 &mTrans) const;
		PLMATH_API Line &operator *=(const Matrix3x3 &mRot);
		PLMATH_API Line &operator *=(const Matrix3x4 &mTrans);
		PLMATH_API Line &operator *=(const Matrix4x4 &mTrans);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLMath/Line.inl"


#endif // __PLMATH_LINE_H__
