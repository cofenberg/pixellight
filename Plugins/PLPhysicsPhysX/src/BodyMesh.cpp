/*********************************************************\
 *  File: BodyMesh.cpp                                   *
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


// [TODO] Implement me


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPhysicsPhysX/BodyImpl.h"
#include "PLPhysicsPhysX/World.h"
#include "PLPhysicsPhysX/BodyMesh.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLPhysicsPhysX {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
BodyMesh::~BodyMesh()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BodyMesh::BodyMesh(PLPhysics::World &cWorld, const String &sMesh, const Vector3 &vMeshScale, bool bOptimize) :
	PLPhysics::BodyMesh(cWorld, ((World&)cWorld).CreateBodyImpl(), sMesh, vMeshScale, bOptimize)
{
	// Get the PhysX physics scene
//	NxScene *pPhysXScene = ((World&)cWorld).GetPhysXScene();
//	if (pPhysXScene)
		// Initialize the PhysX physics actor
//		((BodyImpl&)GetBodyImpl()).InitializePhysXActor(*this, *pPhysXActor);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsPhysX
