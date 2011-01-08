/*********************************************************\
 *  File: Ray.h                                          *
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


#ifndef __PLMATH_RAY_H__
#define __PLMATH_RAY_H__
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
*    Ray class
*/
class Ray {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor setting all position and direction components to 0
		*/
		inline Ray();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		inline Ray(const Ray &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		inline ~Ray();

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
		inline Ray &operator =(const Ray &cSource);

		/**
		*  @brief
		*    Set the current ray using a line
		*
		*  @param[in] vLineStartPos
		*    Line start position
		*  @param[in] vLineEndPos
		*    Line end position
		*/
		inline void Set(const Vector3 &vLineStartPos, const Vector3 &vLineEndPos);

		/**
		*  @brief
		*    Returns the current position
		*
		*  @return
		*    Current position
		*/
		inline const Vector3 &GetPos() const;

		/**
		*  @brief
		*    Set the current position
		*
		*  @param[in] fX
		*    X component of the new position
		*  @param[in] fY
		*    Y component of the new position
		*  @param[in] fZ
		*    Z component of the new position
		*/
		inline void SetPos(float fX = 0.0f, float fY = 0.0f, float fZ = 0.0f);

		/**
		*  @brief
		*    Set the current position
		*
		*  @param[in] vPos
		*    New position
		*/
		inline void SetPos(const Vector3 &vPos);

		/**
		*  @brief
		*    Returns the ray direction
		*
		*  @return
		*    Ray direction
		*/
		inline const Vector3 &GetDir() const;

		/**
		*  @brief
		*    Set the ray direction
		*
		*  @param[in] fX
		*    X component of the new direction vector
		*  @param[in] fY
		*    Y component of the new direction vector
		*  @param[in] fZ
		*    Z component of the new direction vector
		*/
		inline void SetDir(float fX = 0.0f, float fY = 0.0f, float fZ = 0.0f);

		/**
		*  @brief
		*    Set the ray direction
		*
		*  @param[in] vDir
		*    New ray direction
		*/
		inline void SetDir(const Vector3 &vDir);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Vector3 m_vPos;	/**< Ray origin */
		Vector3 m_vDir;	/**< Ray direction */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLMath/Ray.inl"


#endif // __PLMATH_RAY_H__
