/*********************************************************\
 *  File: BodyBox.cpp                                    *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLPhysicsODE/BodyBox.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLPhysicsODE {


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
BodyBox::BodyBox(PLPhysics::World &cWorld, const Vector3 &vDimension) :
	PLPhysics::BodyBox(cWorld, static_cast<World&>(cWorld).CreateBodyImpl(), vDimension)
{
	// Create the ODE physics geometry
	dGeomID pODEGeomID = dCreateBox(static_cast<World&>(cWorld).GetODESpace(), m_vDimension.x, m_vDimension.y, m_vDimension.z);

	// Initialize the ODE physics geometry
	static_cast<BodyImpl&>(GetBodyImpl()).InitializeODEGeometry(*this, pODEGeomID);
}


//[-------------------------------------------------------]
//[ Public virtual PLPhysics::Body functions              ]
//[-------------------------------------------------------]
void BodyBox::SetMass(float fMass)
{
	// Call base implementation
	PLPhysics::BodyBox::SetMass(fMass);

	// Adjust the mass of the body according to it's body type
	if (fMass) {
		dMass sMass;
		dMassSetBoxTotal(&sMass, fMass, m_vDimension.x, m_vDimension.y, m_vDimension.z);
		static_cast<BodyImpl&>(GetBodyImpl()).SetODEMass(sMass);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsODE
