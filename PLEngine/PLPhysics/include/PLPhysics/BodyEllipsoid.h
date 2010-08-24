/*********************************************************\
 *  File: BodyEllipsoid.h                                *
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


#ifndef __PLPHYSICS_BODYELLIPSOID_H__
#define __PLPHYSICS_BODYELLIPSOID_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include "PLPhysics/Body.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract PL physics ellipsoid body
*
*  @remarks
*    Sphere collision are generalized ellipsoids, the application can create many different kind
*    of objects by just playing with dimensions of the radius. For example to make a sphere set all
*    tree radius to the same value, to make a ellipse of revolution just set two of the tree radius
*    to the same value.\n
*    General ellipsoids are very good hull geometries to represent the outer shell of avatars in a game.
*/
class BodyEllipsoid : public Body {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~BodyEllipsoid();

		/**
		*  @brief
		*    Returns the ellipsoid radius along each axis
		*
		*  @return
		*    The ellipsoid radius along each axis
		*/
		PLPHYSICS_API const PLMath::Vector3 &GetRadius() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cWorld
		*    World this body is in
		*  @param[in] cBodyImpl
		*    Reference to the physics API specific body implementation
		*  @param[in] vRadius
		*    Ellipsoid radius along each axis
		*/
		PLPHYSICS_API BodyEllipsoid(World &cWorld, BodyImpl &cBodyImpl, const PLMath::Vector3 &vRadius);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLMath::Vector3 m_vRadius;	/**< Ellipsoid radius along each axis */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_BODYELLIPSOID_H__
