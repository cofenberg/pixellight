/*********************************************************\
 *  File: BodyBox.cpp                                    *
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
#include "PLPhysicsPhysX/BodyBox.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLPhysicsPhysX {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
BodyBox::~BodyBox()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BodyBox::BodyBox(PLPhysics::World &cWorld, const Vector3 &vDimension, bool bStatic) :
	PLPhysics::BodyBox(cWorld, ((World&)cWorld).CreateBodyImpl(), vDimension)
{
	// Get the PhysX physics scene
	NxScene *pPhysXScene = ((World&)cWorld).GetPhysXScene();
	if (pPhysXScene) {
		// Create body
		NxBodyDesc BodyDesc;
		BodyDesc.angularDamping = 0.5f;
		// [TODO] Do we need this setting?
	//	BodyDesc.maxAngularVelocity = 10.0f;

		NxBoxShapeDesc BoxDesc;
		BoxDesc.dimensions = NxVec3(m_vDimension.x/2, m_vDimension.y/2, m_vDimension.z/2);

		NxActorDesc ActorDesc;
		ActorDesc.shapes.pushBack(&BoxDesc);
		if (!bStatic)
			ActorDesc.body = &BodyDesc;
		ActorDesc.density = 10.0f;
		NxActor *pPhysXActor = pPhysXScene->createActor(ActorDesc);

		// Initialize the PhysX physics actor
		((BodyImpl&)GetBodyImpl()).InitializePhysXActor(*this, *pPhysXActor);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsPhysX
