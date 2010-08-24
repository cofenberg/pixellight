/*********************************************************\
 *  File: BodySphere.cpp                                 *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPhysicsODE/World.h"
#include "PLPhysicsODE/BodyImpl.h"
#include "PLPhysicsODE/BodySphere.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsODE {


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
BodySphere::BodySphere(PLPhysics::World &cWorld, float fRadius) :
	PLPhysics::BodySphere(cWorld, ((World&)cWorld).CreateBodyImpl(), fRadius)
{
	// Create the ODE physics geometry
	dGeomID pODEGeomID = dCreateSphere(((World&)cWorld).GetODESpace(), m_fRadius);

	// Initialize the ODE physics geometry
	((BodyImpl&)GetBodyImpl()).InitializeODEGeometry(*this, pODEGeomID);
}


//[-------------------------------------------------------]
//[ Public virtual PLPhysics::Body functions              ]
//[-------------------------------------------------------]
void BodySphere::SetMass(float fMass)
{
	// Call base implementation
	PLPhysics::BodySphere::SetMass(fMass);

	// Adjust the mass of the body according to it's body type
	if (fMass) {
		dMass sMass;
		dMassSetSphereTotal(&sMass, fMass, m_fRadius);
		((BodyImpl&)GetBodyImpl()).SetODEMass(sMass);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsODE
