/*********************************************************\
 *  File: PGPhysics.cpp                                  *
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
#include <PLPhysics/World.h>
#include <PLPhysics/SceneNodes/SCPhysicsWorld.h>
#include "PLParticleGroups/PGPhysics.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
using namespace PLScene;
using namespace PLPhysics;
namespace PLParticleGroups {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(PGPhysics)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the gravity vector
*/
Vector3 PGPhysics::GetGravity() const
{
	// Get the PL physics world this scene node is in
	SceneContainer *pContainer = GetContainer();
	while (pContainer && !pContainer->IsInstanceOf("PLPhysics::SCPhysicsWorld"))
		pContainer = pContainer->GetContainer();

	// Get the gravity vector
	Vector3 vGravity;
	if (pContainer && static_cast<SCPhysicsWorld*>(pContainer)->GetWorld())
		static_cast<SCPhysicsWorld*>(pContainer)->GetWorld()->GetGravity(vGravity);
	else
		vGravity.SetXYZ(0.0f, -9.81f, 0.0f);

	// Return the gravity vector
	return vGravity;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PGPhysics::PGPhysics()
{
}

/**
*  @brief
*    Destructor
*/
PGPhysics::~PGPhysics()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLParticleGroups
