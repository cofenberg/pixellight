/*********************************************************\
 *  File: BodyConvexHull.h                               *
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


#ifndef __PLPHYSICS_BODYCONVEXHULL_H__
#define __PLPHYSICS_BODYCONVEXHULL_H__
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
*    Abstract PL physics convex hull body
*
*  @remarks
*    Convex hulls are the solution to collision primitive that can not be easily represented
*    by and implicit solid. The implicit solid primitives (spheres, cubes, cylinders, capsules,
*    cones, etc.), have constant time complexity for contact calculation and are also extremely
*    efficient on memory usage, therefore the application get perfect smooth behavior. However
*    for cases where the shape is too difficult or a polygonal representation is desired convex
*    hulls are the ultimate solution. For example it is a mistake to model a 10000 point sphere
*    as a convex hull, when the perfect sphere is available.\n
*    There is not upper limit as to how many vertices the application can pass to make
*    a hull shape, however for performance and memory usage concern it is the application
*    responsibility to keep the max vertex at the possible minimum. The minimum number of vertices
*    should be equal or larger than 4 and it is the application responsibility that the points are
*    part of a solid geometry. Unpredictable results will occur if all points happen to be collinear
*    or coplanar.
*/
class BodyConvexHull : public Body {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~BodyConvexHull();

		/**
		*  @brief
		*    Returns the collision mesh
		*
		*  @return
		*    The collision mesh
		*/
		PLPHYSICS_API PLGeneral::String GetMesh() const;

		/**
		*  @brief
		*    Returns the mesh scale
		*
		*  @return
		*    The mesh scale
		*/
		PLPHYSICS_API const PLMath::Vector3 &GetMeshScale() const;


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
		*  @param[in] sMesh
		*    Collision mesh
		*  @param[in] vMeshScale
		*    Mesh scale
		*/
		PLPHYSICS_API BodyConvexHull(World &cWorld, BodyImpl &cBodyImpl, const PLGeneral::String &sMesh,
									 const PLMath::Vector3 &vMeshScale);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::String m_sMesh;		/**< Collision mesh */
		PLMath::Vector3	  m_vMeshScale;	/**< Mesh scale */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_BODYCONVEXHULL_H__
