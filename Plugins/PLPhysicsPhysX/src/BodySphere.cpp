/*********************************************************\
 *  File: BodySphere.cpp                                 *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPhysicsPhysX/BodyImpl.h"
#include "PLPhysicsPhysX/World.h"
#include "PLPhysicsPhysX/BodySphere.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsPhysX {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
BodySphere::~BodySphere()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BodySphere::BodySphere(PLPhysics::World &cWorld, float fRadius, bool bStatic) :
	PLPhysics::BodySphere(cWorld, ((World&)cWorld).CreateBodyImpl(), fRadius)
{
	// Get the PhysX physics scene
	NxScene *pPhysXScene = ((World&)cWorld).GetPhysXScene();
	if (pPhysXScene) {
		// Create body
		NxBodyDesc BodyDesc;
		BodyDesc.angularDamping = 0.5f;
		// [TODO] Do we need this setting?
	//	BodyDesc.maxAngularVelocity = 10.0f;

		NxSphereShapeDesc SphereDesc;
		SphereDesc.radius = m_fRadius;

		NxActorDesc ActorDesc;
		ActorDesc.shapes.pushBack(&SphereDesc);
		if (!bStatic)
			ActorDesc.body = &BodyDesc;
		ActorDesc.density = 10.0f;
		// [TODO] Do we need this setting?
	//	ActorDesc.globalPose.t  = pos;
		NxActor *pPhysXActor = pPhysXScene->createActor(ActorDesc);

		// Initialize the PhysX physics actor
		((BodyImpl&)GetBodyImpl()).InitializePhysXActor(*this, *pPhysXActor);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsPhysX
