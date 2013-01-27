/*********************************************************\
 *  File: BodySphere.cpp                                 *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
