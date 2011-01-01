/*********************************************************\
 *  File: Sphere.h                                       *
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


#ifndef __PLMATH_SPHERE_H__
#define __PLMATH_SPHERE_H__
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
*    Sphere class
*/
class Sphere {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor setting all position components and the radius to 0
		*/
		PLMATH_API Sphere();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLMATH_API Sphere(const Sphere &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLMATH_API ~Sphere();

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
		PLMATH_API Sphere &operator =(const Sphere &cSource);

		/**
		*  @brief
		*    Returns the radius of the sphere
		*
		*  @return
		*    Sphere radius
		*/
		PLMATH_API float GetRadius() const;

		/**
		*  @brief
		*    Sets the radius of the sphere
		*
		*  @param[in] fRadius
		*    Sphere radius
		*/
		PLMATH_API void SetRadius(float fRadius = 0.0f);

		/**
		*  @brief
		*    Returns the current position
		*
		*  @return
		*    Current position
		*/
		PLMATH_API const Vector3 &GetPos() const;

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
		PLMATH_API void SetPos(float fX = 0.0f, float fY = 0.0f, float fZ = 0.0f);

		/**
		*  @brief
		*    Set the current position
		*
		*  @param[in] vPos
		*    New position
		*/
		PLMATH_API void SetPos(const Vector3 &vPos);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float   m_fRadius;	/**< Sphere radius */
		Vector3 m_vPos;		/**< Sphere position */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath


#endif // __PLMATH_SPHERE_H__
