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


#ifndef __PLPHYSICSNEWTON_BODYMESH_H__
#define __PLPHYSICSNEWTON_BODYMESH_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLPhysics/BodyMesh.h>
#include "PLPhysicsNewton/PLPhysicsNewton.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class File;
}
namespace PLMesh {
	class MeshManager;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsNewton {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Newton physics mesh body implementation
*/
class BodyMesh : public PLPhysics::BodyMesh {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class World;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICSNEWTON_API virtual ~BodyMesh();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cWorld
		*    World this body is in
		*  @param[in] cMeshManager
		*    Mesh manager to use
		*  @param[in] sMesh
		*    Collision mesh
		*  @param[in] vMeshScale
		*    Mesh scale
		*  @param[in] bOptimize
		*    Allow the physics API to optimize the mesh? (if supported)
		*/
		BodyMesh(PLPhysics::World &cWorld, PLMesh::MeshManager &cMeshManager, const PLGeneral::String &sMesh, const PLMath::Vector3 &vMeshScale, bool bOptimize);

		/**
		*  @brief
		*    Opens a file
		*
		*  @param[in] cWorld
		*    World this body is in
		*  @param[in] sFilename
		*    Filename of the file to open
		*  @param[in] bCreate
		*    Create the file if it doen't exist?
		*
		*  @return
		*    The opened file, a null pointer on error (or maybe caching is not activated)
		*/
		PLGeneral::File *OpenFile(PLPhysics::World &cWorld, const PLGeneral::String &sFilename, bool bCreate = false) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton


#endif // __PLPHYSICSNEWTON_BODYMESH_H__
