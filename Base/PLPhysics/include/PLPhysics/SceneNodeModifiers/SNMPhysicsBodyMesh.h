/*********************************************************\
 *  File: SNMPhysicsBodyMesh.h                           *
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


#ifndef __PLPHYSICS_SCENENODEMODIFIERS_BODYMESH_H__
#define __PLPHYSICS_SCENENODEMODIFIERS_BODYMESH_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsBody.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Physics mesh body scene node modifier
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
*    - When a tree collision is assigned to a body the mass of the body is ignored in all dynamics
*      calculations. This makes the body behave as a static body.
*/
class SNMPhysicsBodyMesh : public SNMPhysicsBody {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPHYSICS_RTTI_EXPORT, SNMPhysicsBodyMesh, "PLPhysics", PLPhysics::SNMPhysicsBody, "Physics mesh body scene node modifier")
		// Attributes
		pl_attribute(Mesh,		PLCore::String,	"",		ReadWrite,	GetSet,	"Collision mesh, if empty, the variable 'Mesh' (if available) of the scene node is used instead",								"Type='Mesh'")
		pl_attribute(Optimize,	bool,			false,	ReadWrite,	GetSet,	"Flag that indicates whether it should optimize this mesh. Set to 1 to optimize (may take some time!) the mesh, otherwise 0.",	"")
		// Constructors
		pl_constructor_1(ParameterConstructor,	PLScene::SceneNode&,	"Parameter constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICS_API PLCore::String GetMesh() const;
		PLPHYSICS_API void SetMesh(const PLCore::String &sValue);
		PLPHYSICS_API bool GetOptimize() const;
		PLPHYSICS_API void SetOptimize(bool bValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		PLPHYSICS_API SNMPhysicsBodyMesh(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~SNMPhysicsBodyMesh();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String m_sMesh;		/**< Collision mesh, if empty, the variable 'Mesh' (if available) of the scene node is used instead */
		bool		   m_bOptimize;	/**< Flag that indicates whether it should optimize this mesh. Set to 1 to optimize (may take some time!) the mesh, otherwise 0. */


	//[-------------------------------------------------------]
	//[ Private virtual SNMPhysicsBody functions              ]
	//[-------------------------------------------------------]
	private:
		virtual void CreatePhysicsBody();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SCENENODEMODIFIERS_BODYMESH_H__
