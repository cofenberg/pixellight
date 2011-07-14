/*********************************************************\
 *  File: BodyMesh.h                                     *
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


#ifndef __PLPHYSICS_BODYMESH_H__
#define __PLPHYSICS_BODYMESH_H__
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
*    Abstract PL physics mesh body
*
*  @remarks
*    Tree collision is the preferred method for collision with polygonal meshes
*    of arbitrary complexity. The mesh must be made of flat non-intersecting polygons, but they
*    do not explicitly need to be triangles. Tree collision can be serialized by the application
*    to/from an arbitrary storage device.\n
*    If concave polygons are added to the tree collision, the variable 'Optimize' must be set to 1.
*    With the optimize variable set to 1, we will optimize the collision mesh by removing non
*    essential edges from adjacent flat polygons. We will not change the topology of the mesh but
*    significantly reduces the number of polygons in the mesh. The reduction factor of the number of
*    polygons in the mesh depends upon the irregularity of the mesh topology. A reduction factor of
*    1.5 to 2 is common. If the variable optimize is set to zero, will leave the mesh geometry unaltered.
*
*  @note
*    - When a mesh is assigned to a body the mass of the body is ignored in all dynamics
*      calculations. This makes the body behave as a static body.
*    - The "TwoSided" material parameter should be supported
*/
class BodyMesh : public Body {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~BodyMesh();

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

		/**
		*  @brief
		*    Returns whether the physics API is allowed to optimize the mesh or not (if supported)
		*
		*  @return
		*    'true' if the physics API is allowed to optimize the mesh, else 'false'
		*/
		PLPHYSICS_API bool GetOptimize() const;


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
		*  @param[in] bOptimize
		*    Allow the physics API to optimize the mesh? (if supported)
		*/
		PLPHYSICS_API BodyMesh(World &cWorld, BodyImpl &cBodyImpl, const PLGeneral::String &sMesh,
							   const PLMath::Vector3 &vMeshScale, bool bOptimize);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::String m_sMesh;		/**< Collision mesh */
		PLMath::Vector3	  m_vMeshScale;	/**< Mesh scale */
		bool			  m_bOptimize;	/**< Allow the physics API to optimize the mesh? (if supported) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_BODYMESH_H__
